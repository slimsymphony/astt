using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Xml.Linq;
using Marble.Model;
using MarbleLibrary.Utilities;

namespace Marble.Views
{
    using System.ComponentModel;
    using System.Globalization;
    using System.Windows.Threading;
    using System.Xml;

    using ICSharpCode.AvalonEdit.CodeCompletion;
    using ICSharpCode.AvalonEdit.Highlighting;
    using ICSharpCode.AvalonEdit.Highlighting.Xshd;

    using Marble.Utilities;
    using Marble.ViewModel;

    using MarbleLibrary.Commands;

    /// <summary>
    /// Interaction logic for CaptureTool.xaml
    /// </summary>
    public partial class CaptureTool : Window, INotifyPropertyChanged
    {
        /// <summary>
        /// Collection of the route points for gestures.
        /// </summary>
        private PointCollection pointCollection = new PointCollection();

        private double elementTableColumnWidth = 300;
        private double elementTableColumnMinWidth = 100;

        /// <summary>
        /// Gets Display element from which the drag gesture is started.
        /// </summary>
        public DisplayElement DraggedDisplayElement
        {
            get
            {
                return this.draggedDisplayElement;
            }
            private set
            {
                this.draggedDisplayElement = value;

                if (this.viewModel != null) this.viewModel.DraggedDisplayElement = value;
            }
        }

        /// <summary>
        /// Flag to indicate whether a display element is being dragged.
        /// </summary>
        private bool dragStarted = false;

        /// <summary>
        /// Flag to indicate whether a display element is being dragged using right mouse button.
        /// </summary>
        private bool dragUsingRightMouseButtonStarted = false;

        /// <summary>
        /// Start time of the left mouse button click.
        /// Used to determinate whether long click is used instead of normal (short) click.
        /// </summary>
        private DateTime clickStart = DateTime.MinValue;

        /// <summary>
        /// True when right mouse button have been clicked over the real capture.
        /// Used for keeping drawn display elements visible.
        /// They would otherwise be cleared in mouse leave event handler.
        /// </summary>
        private bool contextMenuOpening = false;

        /// <summary>
        /// Pinch direction vector.
        /// Used for keeping arrows drawn when mouse cursor is exatcly
        /// over the center point of the real capture.
        /// </summary>
        private Vector previousPinchDirection;

        private Point startPosition;

        private DisplayElement draggedDisplayElement;

        /// <summary>
        /// Center point of the pinch.
        /// </summary>
        private Point pinchCenter;

        /// <summary>
        /// Start position of the mouse down for swipes and gestures.
        /// </summary>
        protected Point StartPosition
        {
            get
            {
                return this.startPosition;
            }
            private set
            {
                this.startPosition = value;

                if (this.viewModel != null)
                {
                    this.viewModel.CurrentStartCoordinates = value;
                    ////this.viewModel.CurrentDisplayElement = this.viewModel.SelectSmallestDisplayElement(value);
                }
            }
        }

        private CaptureToolViewModel viewModel { get; set; }

        private CompletionWindow completionWindow;

        public CaptureTool()
        {
            InitializeComponent();

            this.viewModel = new CaptureToolViewModel();
            this.viewModel.CanvasRealCapture = this.canvasRealCapture;
            this.DataContext = this.viewModel;

            // Disable pasting in cell width textbox
            DataObject.AddPastingHandler(this.textBoxGridWidth, this.OnCancelCommand);

            this.avalonEditCommandHistory.SyntaxHighlighting = HighlightingLoader.Load(new XmlTextReader(MarblePaths.PythonSyntaxHighlightingDataFile), HighlightingManager.Instance);
            this.AvalonEditPythonParser.SyntaxHighlighting = HighlightingLoader.Load(new XmlTextReader(MarblePaths.PythonSyntaxHighlightingDataFile), HighlightingManager.Instance);

            this.avalonEditCommandHistory.TextArea.SelectionChanged += this.AvalonEditCommandHistory_OnSelectionChanged;
            App.ViewModel.MarbleConnector.PropertyChanged += this.AvalonEditCommandHistory_OnSelectionChanged;

            this.viewModel.CommandHistoryChanged += viewModel_CommandHistoryChanged;

            this.AvalonEditPythonParser.TextArea.TextEntered += TextAreaOnTextEntered;
            this.AvalonEditPythonParser.TextArea.TextEntering += TextAreaOnTextEntering;
            this.AvalonEditPythonParser.KeyDown += AvalonEditPythonParserOnKeyDown;
        }

        private void AvalonEditPythonParserOnKeyDown(object sender, KeyEventArgs keyEventArgs)
        {
            if (keyEventArgs.Key == Key.Enter && completionWindow != null)
            {
                completionWindow.CompletionList.RequestInsertion(null);
            }
        }

        private void TextAreaOnTextEntering(object sender, TextCompositionEventArgs textCompositionEventArgs)
        {
            if (this.CheckBoxCommandHistoryAutoCompleteEnabled.IsChecked == false) return;

            if (textCompositionEventArgs.Text.Length > 0 && completionWindow != null)
            {
                if (!char.IsLetterOrDigit(textCompositionEventArgs.Text[0]))
                {
                    // Whenever a non-letter is typed while the completion window is open,
                    // insert the currently selected element.
                    completionWindow.CompletionList.RequestInsertion(textCompositionEventArgs);
                }
            }
            // Do not set e.Handled=true.
            // We still want to insert the character that was typed.
        }

        private void TextAreaOnTextEntered(object sender, TextCompositionEventArgs textCompositionEventArgs)
        {
            if (this.CheckBoxCommandHistoryAutoCompleteEnabled.IsChecked == false) return;

            if (textCompositionEventArgs.Text == ".")
            {
                // Open code completion after the user has pressed dot:
                completionWindow = new CompletionWindow(AvalonEditPythonParser.TextArea);
                IList<ICompletionData> data = completionWindow.CompletionList.CompletionData;
                
                string wordBeforeDot = this.AvalonEditPythonParser.GetWordBeforeDot();

                if (wordBeforeDot == "self")
                {
                    foreach (var completionData in PythonScriptCommands.GetParserCompletionDataListForSelf())
                    {
                        data.Add(completionData);
                    }
                }
                else
                {
                    return;
                }

                completionWindow.Show();
                completionWindow.Closed += delegate
                {
                    completionWindow = null;
                };
            }
            else if (textCompositionEventArgs.Text == "(")
            {
                if (this.AvalonEditPythonParser.CaretOffset <= 1) return;

                // Open code completion after the user has pressed dot:
                completionWindow = new CompletionWindow(AvalonEditPythonParser.TextArea);
                IList<ICompletionData> data = completionWindow.CompletionList.CompletionData;
                int previousWordStartIndex = this.AvalonEditPythonParser.Text.LastIndexOf("(", this.AvalonEditPythonParser.CaretOffset - 2, System.StringComparison.Ordinal) + 1;

                if (previousWordStartIndex < 0)
                    previousWordStartIndex = 0;

                if (this.AvalonEditPythonParser.Text.Substring(
                    previousWordStartIndex, this.AvalonEditPythonParser.CaretOffset - previousWordStartIndex) == "self.")
                {
                    foreach (var completionData in PythonScriptCommands.GetParserCompletionDataList(AvailableMarblePythonCommands.self))
                    {
                        data.Add(completionData);
                    }
                }
                else
                {
                    return;
                }

                completionWindow.Show();
                completionWindow.Closed += delegate
                {
                    completionWindow = null;
                };
            }
            else if (textCompositionEventArgs.Text.ToLower() == "s")
            {
                int previousCharIndex = this.AvalonEditPythonParser.CaretOffset - 2;

                if (previousCharIndex < 0) 
                    previousCharIndex = 0;

                string charBeforeDot = this.AvalonEditPythonParser.Text[previousCharIndex].ToString(CultureInfo.InvariantCulture);

                if (previousCharIndex > 0 && !string.IsNullOrWhiteSpace(charBeforeDot) && charBeforeDot != "(") return;

                // Open code completion after the user has pressed dot:
                completionWindow = new CompletionWindow(AvalonEditPythonParser.TextArea);
                IList<ICompletionData> data = completionWindow.CompletionList.CompletionData;
                data.Add(new PythonParserCompletionData("self".Substring(textCompositionEventArgs.Text.Length)) { Content = "self", Description = "" });
                
                completionWindow.Show();
                completionWindow.Closed += delegate
                {
                    completionWindow = null;
                };
            }
        }

        private void viewModel_CommandHistoryChanged(object sender, EventArgs e)
        {
            this.avalonEditCommandHistory.Text = this.viewModel.CommandHistory;
            this.avalonEditCommandHistory.ScrollToEnd();

            this.textBlockInfoText.Text = TextUtilities.GetLastLine(this.avalonEditCommandHistory.Text);
        }

        /// <summary>
        /// Handler for cancelling the paste command for textBoxGridWidth
        /// </summary>
        /// <param name="sender">Not used</param>
        /// <param name="e">Not used</param>
        private void OnCancelCommand(object sender, DataObjectEventArgs e)
        {
            e.CancelCommand();
        }

        /// <summary>
        /// Performs one display capture from the connected phone.
        /// CaptureCommand is put to connector queue for execution.
        /// CaptureDone is called when connector is finished.
        /// </summary>
        /// <remarks>
        /// capture tool\temp\xml\temp_capture.xml containing the display dump is created to working directory.
        /// capture tool\temp\captured bitmaps\capture_x.png contains the real image.
        /// </remarks>
        /// <param name="sender">Not used</param>
        /// <param name="e">Not used</param>
        private void OnCaptureButtonClick(object sender, RoutedEventArgs e)
        {
            this.textBlockInfoText.Text = string.Empty;
            this.viewModel.SendCaptureCommand();
            this.Focus();
        }

        /// <summary>
        /// Displays an open file dialog with png filter.
        /// Selected image is displayed along with display elements if they are found.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnOpenButtonClick(object sender, RoutedEventArgs e)
        {
            this.viewModel.OpenSavedImage();
        }

        /// <summary>
        /// Draws grid to the capture canvas.
        /// </summary>
        public void DrawGrid()
        {
            int width;
            int.TryParse(this.textBoxGridWidth.Text, out width);
            this.viewModel.DrawGrid(this.canvasRealCapture, width);
        }

        /// <summary>
        /// Main method for drawing all the shapes over the captured image
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRealCaptureMouseMove(object sender, MouseEventArgs e)
        {
            // Clear existing shapes and selection
            this.clearCanvas();
            this.dataGridElementTable.UnselectAll();
            
            // Get mouse position as integer coordinates and display it in a textbox
            Point mousePos = new Point((int)e.GetPosition(this.canvasRealCapture).X, (int)e.GetPosition(this.canvasRealCapture).Y);

            string absoluteCoordinatesText = string.Format("({0}, {1})", mousePos.X, mousePos.Y);
            //string relativeCoordinatesText = string.Format("({0:0.###}", Math.Round(mousePos.X / this.canvasRealCapture.Width * 100, 2) + ", " + string.Format("{0:0.###}", mousePos.Y / this.canvasRealCapture.Height * 100) + ")";
            string relativeCoordinatesText = string.Format("({0:P1}, {1:P1})",
                                                           mousePos.X/this.canvasRealCapture.Width,
                                                           mousePos.Y/this.canvasRealCapture.Height);

            this.textBlockCoordinatesText.Text = absoluteCoordinatesText + " - " + relativeCoordinatesText;

            // DISPLAY ELEMENT selection mode
            if (this.radioButtonElement.IsChecked == true)
            {
                // Dragging of display element with left mouse button.
                if ((e.LeftButton == MouseButtonState.Pressed || e.RightButton == MouseButtonState.Pressed) && this.DraggedDisplayElement != null)
                {
                    // Drag ongoing
                    if (this.dragStarted || this.dragUsingRightMouseButtonStarted)
                    {
                        Vector displacement = mousePos - this.StartPosition;

                        // Draw a gray rectangle.
                        Rectangle rect = new Rectangle
                            {
                                Width = this.DraggedDisplayElement.Rectangle.Width,
                                Height = this.DraggedDisplayElement.Rectangle.Height,
                                Stroke = new SolidColorBrush(Colors.Gray),
                                IsHitTestVisible = false
                            };

                        Canvas.SetLeft(rect, this.DraggedDisplayElement.Rectangle.X + displacement.X);
                        Canvas.SetTop(rect, this.DraggedDisplayElement.Rectangle.Y + displacement.Y);
                        this.canvasRealCapture.Children.Add(rect);

                        // Draw a red arrow from the middle of the start element to current position
                        this.viewModel.DrawArrow(this.DraggedDisplayElement.Center, this.DraggedDisplayElement.Center + displacement, this.canvasRealCapture);
                    }

                    // Start the drag when mouse (with left button down) has moved 5 pixels
                    else if (CaptureToolViewModel.GetDistance(mousePos, this.StartPosition) > 5)
                    {
                        if (e.RightButton == MouseButtonState.Pressed) 
                            this.dragUsingRightMouseButtonStarted = true;
                        else
                            this.dragStarted = true;
                    }
                }
                else
                {
                    bool isCursorOnElement = false;

                    // Draw a red rectangle over all the display elements under the current mouse position
                    foreach (var dElem in this.viewModel.DisplayElements)
                    {
                        if (dElem.Rectangle.Contains((int)mousePos.X, (int)mousePos.Y))
                        {
                            isCursorOnElement = true;
                            this.dataGridElementTable.SelectedItems.Add(dElem);
                            this.viewModel.DrawDisplayElement(dElem, this.canvasRealCapture);
                        }
                    }

                    // Change cursor to hand if it is on any display element
                    this.canvasRealCapture.Cursor = isCursorOnElement ? Cursors.Hand : Cursors.Arrow;
                }
            }

            // LONG SELECT mode
            else if (this.radioButtonLongSelect.IsChecked == true)
            {
                bool isCursorOnElement = false;

                // Draw a red rectangle over all the display elements under the current mouse position
                foreach (var dElem in this.viewModel.DisplayElements)
                {
                    if (dElem.Rectangle.Contains((int)mousePos.X, (int)mousePos.Y))
                    {
                        isCursorOnElement = true;
                        this.dataGridElementTable.SelectedItems.Add(dElem);
                        this.viewModel.DrawDisplayElement(dElem, this.canvasRealCapture);
                    }
                }

                // Change cursor to hand if it is on any display element
                this.canvasRealCapture.Cursor = isCursorOnElement ? Cursors.Hand : Cursors.Arrow;
            }

            // PINCH mode
            else if (this.radioButtonPinch.IsChecked == true)
            {
                // The first step of the pinch: center point selection
                if (!this.viewModel.PinchStarted)
                {
                    this.viewModel.DrawScope(mousePos, this.canvasRealCapture);
                }
                // The second step of the pinch: pinch creation by drag
                else
                {
                    // Pinch creation is ongoing
                    if (e.LeftButton != MouseButtonState.Pressed)
                    {
                        // Draw an ellipse to the center point of the pinch
                        this.viewModel.DrawEllipse(this.pinchCenter, 5);

                        // Draw dashed arrows from the current mouse position to symbolise drags towards or away from the center
                        Vector centerToMousePos = mousePos - this.pinchCenter;

                        var outwards = centerToMousePos * 30 / centerToMousePos.Length;
                        var inwards = centerToMousePos.Length < 30
                                          ? centerToMousePos
                                          : outwards;

                        this.viewModel.DrawArrow(mousePos, mousePos + outwards, this.canvasRealCapture, 3);
                        this.viewModel.DrawArrow(mousePos, mousePos - inwards, this.canvasRealCapture, 3);

                        // Draw dashed ellipse to indicate the border of the pinch creation
                        this.viewModel.DrawEllipse(this.pinchCenter, (this.pinchCenter - mousePos).Length, 3);

                    }
                    // Pinch creation is not yet started
                    else
                    {
                        // Calculate the distance of the pinch start position to the center of the pinch
                        double startDistance = (this.StartPosition - this.pinchCenter).Length;

                        // Create vector from center of the pinch to the current mouse position
                        Vector centerToMousePos = mousePos - this.pinchCenter;

                        // Handle undeterminable direction on exactly over the center point
                        // Store current direction
                        if (Math.Abs(centerToMousePos.Length - 0) > Double.Epsilon)
                            this.previousPinchDirection = centerToMousePos;
                        // Previous direction is used
                        else
                            centerToMousePos = this.previousPinchDirection;

                        // Calculate vector to current direction which is as long as the start distance
                        Vector centerToMousePosStart = centerToMousePos * (startDistance / centerToMousePos.Length);

                        // Calculate generated pinches
                        Vector pinch1 = centerToMousePos - centerToMousePosStart;
                        Vector pinch2 = CaptureToolViewModel.RotateVector(pinch1, 180);

                        // Pinch in (towards the center)
                        if (startDistance > centerToMousePos.Length)
                        {
                            this.viewModel.DrawArrow(this.pinchCenter + pinch1, this.pinchCenter, this.canvasRealCapture);
                            this.viewModel.DrawArrow(this.pinchCenter + pinch2, this.pinchCenter, this.canvasRealCapture);
                        }
                        // Pinch out (away from the center)
                        else
                        {
                            this.viewModel.DrawArrow(this.pinchCenter, this.pinchCenter + pinch1, this.canvasRealCapture);
                            this.viewModel.DrawArrow(this.pinchCenter, this.pinchCenter + pinch2, this.canvasRealCapture);
                        }

                        // Display current pinch in place of the coordinates
                        this.textBlockCoordinatesText.Text = this.viewModel.CreatePinchString(
                                this.pinchCenter, mousePos, this.StartPosition,
                                new Point(this.canvasRealCapture.Width, this.canvasRealCapture.Height));

                        // Draw dashed border ellipse
                        this.viewModel.DrawEllipse(this.pinchCenter, (this.pinchCenter - this.StartPosition).Length, 3);
                    }
                }
            }

            // SWIPE selection mode
            else if (this.radioButtonSwipe.IsChecked == true && e.LeftButton == MouseButtonState.Pressed)
            {
                // Draw an arrow to visualize the swipe
                this.viewModel.DrawArrow(this.StartPosition, mousePos, this.canvasRealCapture);
            }

            // GESTURE selection mode
            else if (this.radioButtonGesture.IsChecked == true && e.LeftButton == MouseButtonState.Pressed)
            {
                if (this.pointCollection.Count == 0)
                    this.pointCollection.Add(mousePos);

                // Include current mouse position only if the distance to the last included point is sufficient
                else if (CaptureToolViewModel.GetDistance(this.pointCollection.Last(), mousePos) > this.GranularitySlider.Value)
                    this.pointCollection.Add(mousePos);

                // Draw a red polyline indicating the traversed route
                Polyline polyLine = new Polyline
                    {
                        Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                        StrokeThickness = 2,
                        FillRule = FillRule.EvenOdd,
                        Points = this.pointCollection,
                        IsHitTestVisible = false
                    };

                this.canvasRealCapture.Children.Add(polyLine);
            }

            this.OnPropertyChanged("CurrentDisplayElement");
        }

        /// <summary>
        /// Ends drag, swipe and gesture drawing.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRealCaptureMouseLeave(object sender, MouseEventArgs e)
        {
            if (this.contextMenuOpening)
            {
                this.contextMenuOpening = false;
                return;
            }

            this.clearCanvas();

            this.dataGridElementTable.UnselectAll();
            this.textBlockCoordinatesText.Text = string.Empty;

            // Display element being dragged
            if (this.dragStarted)
            {
                Point mousePos = e.GetPosition(this.canvasRealCapture);
                Vector displacement = mousePos - this.StartPosition;

                this.CopyToClipboard(
                    string.Format(
                        "self.gesture.drag('{0}', ({1:0.0000},{2:0.0000}))",
                        this.DraggedDisplayElement.SelectedTranslation.Replace("'", @"\'"),
                        Math.Round((this.DraggedDisplayElement.Center.X + displacement.X) / this.canvasRealCapture.Width, 4),
                        Math.Round((this.DraggedDisplayElement.Center.Y + displacement.Y) / this.canvasRealCapture.Height, 4)));
                this.dragStarted = false;
                this.dragUsingRightMouseButtonStarted = false;
                this.DraggedDisplayElement = null;
            }
            else if (this.dragUsingRightMouseButtonStarted)
            {
                if (this.radioButtonElement.IsChecked == true && this.DraggedDisplayElement != null)
                {
                    Point endPoint = new Point(this.DraggedDisplayElement.Center.X + e.GetPosition(this.canvasRealCapture).X - this.StartPosition.X,
                                               this.DraggedDisplayElement.Center.Y + e.GetPosition(this.canvasRealCapture).Y - this.StartPosition.Y);

                    this.viewModel.CurrentEndCoordinates = endPoint;

                    ContextMenu dragContextMenu =
                        this.canvasRealCapture.Resources["ContextMenuCanvasRealCaptureDrag"] as ContextMenu;

                    if (dragContextMenu != null)
                    {
                        this.canvasRealCapture.IsHitTestVisible = false;
                        dragContextMenu.DataContext = this.viewModel;
                        this.canvasRealCapture.ContextMenu = dragContextMenu;
                        this.canvasRealCapture.ContextMenu.IsOpen = true;
                    }
                }
                else
                {
                    this.dragStarted = false;
                    this.dragUsingRightMouseButtonStarted = false;

                    this.DraggedDisplayElement = null;
                }


                return;

                Point mousePos = e.GetPosition(this.canvasRealCapture);
                Vector displacement = mousePos - this.StartPosition;

                this.CopyToClipboard(
                    string.Format(
                        "self.gesture.drag('{0}', ({1:0.0000},{2:0.0000}))",
                        this.DraggedDisplayElement.SelectedTranslation.Replace("'", @"\'"),
                        Math.Round((this.DraggedDisplayElement.Center.X + displacement.X) / this.canvasRealCapture.Width, 4),
                        Math.Round((this.DraggedDisplayElement.Center.Y + displacement.Y) / this.canvasRealCapture.Height, 4)));
                this.dragStarted = false;
                this.DraggedDisplayElement = null;
            }
            // Pinch being drawn
            else if (this.radioButtonPinch.IsChecked == true && e.LeftButton == MouseButtonState.Pressed)
            {
                this.CopyToClipboard(this.viewModel.CreatePinchString(this.pinchCenter,
                                                                      e.GetPosition(this.canvasRealCapture),
                                                                      this.StartPosition,
                                                                      new Point(this.canvasRealCapture.Width,
                                                                                this.canvasRealCapture.Height)));
                this.clearCanvas();
                this.viewModel.PinchStarted = false;
            }
            // Swipe being drawn
            else if (e.LeftButton == MouseButtonState.Pressed && this.radioButtonSwipe.IsChecked == true)
            {
                this.CopyToClipboard(
                    string.Format(
                        "self.gesture.swipe(({0:0.0000},{1:0.0000}), ({2:0.0000},{3:0.0000}))",
                        Math.Round(this.StartPosition.X / this.canvasRealCapture.Width, 4),
                        Math.Round(this.StartPosition.Y / this.canvasRealCapture.Height, 4),
                        Math.Round(e.GetPosition(this.canvasRealCapture).X / this.canvasRealCapture.Width, 4),
                        Math.Round(e.GetPosition(this.canvasRealCapture).Y / this.canvasRealCapture.Height, 4)));
                this.clearCanvas();
            }
            // Gesture being drawn
            else if (e.LeftButton == MouseButtonState.Pressed && this.radioButtonGesture.IsChecked == true)
            {
                ////Clipboard.SetText(this.pointCollection.ToString());
                Clipboard.SetDataObject(this.pointCollection.ToString());
                this.textBlockInfoText.Text = string.Format("Gesture with {0} points", this.pointCollection.Count);
                this.pointCollection.Clear();
                this.SendGeneratedScriptCommand();
                this.clearCanvas();
            }

            this.OnPropertyChanged("CurrentDisplayElement");
        }

        /// <summary>
        /// Displays selected item and copies it to clipboard.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRealCaptureMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            // Element
            if (this.radioButtonElement.IsChecked == true)
            {
                // Coordinates are used when element is not available and best possible selection method is active
                // OR when coordinates are selected as default selection method.
                if (((this.dataGridElementTable.SelectedIndex < 0 && this.radioButtonDefaultSelectBestPossible.IsChecked == true) || this.radioButtonDefaultSelectCoordinates.IsChecked == true)
                    && !this.dragStarted)
                {
                    if (DateTime.Now - this.clickStart < new TimeSpan(0, 0, 1))
                    {
                        this.CopyToClipboard(
                            "self.select((" +
                            string.Format("{0:0.0000}", Math.Round((int)e.GetPosition(this.canvasRealCapture).X / this.canvasRealCapture.Width, 4)) + ", " +
                            string.Format("{0:0.0000}", Math.Round((int)e.GetPosition(this.canvasRealCapture).Y / this.canvasRealCapture.Height, 4)) + "))");
                    }
                    else
                    {
                        this.CopyToClipboard(
                            "self.select.long((" +
                            string.Format("{0:0.0000}", Math.Round((int)e.GetPosition(this.canvasRealCapture).X / this.canvasRealCapture.Width, 4)) + ", " +
                            string.Format("{0:0.0000}", Math.Round((int)e.GetPosition(this.canvasRealCapture).Y / this.canvasRealCapture.Height, 4)) + "))");
                    }

                    return;
                }

                ////// Display element being dragged or Display element clicked
                ////this.CopyToClipboard(
                ////    this.dragStarted
                ////        ? this.GetDragResult(e.GetPosition(this.canvasRealCapture))
                ////        : this.GetSelectResult());

                if (this.dragStarted)
                {
                    // NOTE: FIX
                    this.CopyToClipboard(this.GetDragResult(e.GetPosition(this.canvasRealCapture)));
                }
                else
                {
                    this.viewModel.CurrentDisplayElement =
                        this.viewModel.SelectSmallestDisplayElement(
                            e.GetPosition(this.canvasRealCapture), DisplayElementType.Node);

                    // If display element is checkable, it is toggled by default.
                    if (this.viewModel.CurrentDisplayElement != null
                        && this.viewModel.CurrentDisplayElement.IsCheckable == true
                        && this.viewModel.ToggleCommand.CanExecute(new Tuple<DisplayElement, ElementSelectionMethod, bool?>(this.viewModel.CurrentDisplayElement, this.viewModel.DefaultSelectionMethod, null)))
                    {
                        this.viewModel.ToggleCommand.Execute(new Tuple<DisplayElement, ElementSelectionMethod, bool?>(this.viewModel.CurrentDisplayElement, this.viewModel.DefaultSelectionMethod, null));

                        return;
                    }

                    this.viewModel.CurrentStartCoordinates = new Point(
                        (int)e.GetPosition(this.canvasRealCapture).X, (int)e.GetPosition(this.canvasRealCapture).Y);

                    // Selects by default selection method.
                    if (this.viewModel.SelectByDefaultSelectionMethodCommand.CanExecute(false)) 
                        this.viewModel.SelectByDefaultSelectionMethodCommand.Execute(false);

                    string clipboardText = Clipboard.GetText();

                    if (!string.IsNullOrEmpty(clipboardText) && clipboardText != this.textBlockInfoText.Text)
                        this.textBlockInfoText.Text = clipboardText;
                }
            }

            // Long Select
            else if (this.radioButtonLongSelect.IsChecked == true)
            {
                this.viewModel.CurrentDisplayElement = this.viewModel.SelectSmallestDisplayElement(e.GetPosition(this.canvasRealCapture), DisplayElementType.Node);

                ////// If display element is checkable, it is toggled by default.
                ////if (this.viewModel.CurrentDisplayElement != null
                ////    && this.viewModel.CurrentDisplayElement.IsCheckable == true
                ////    && this.viewModel.ToggleCommand.CanExecute(new Tuple<DisplayElement, ElementSelectionMethod, bool?>(this.viewModel.CurrentDisplayElement, this.viewModel.DefaultSelectionMethod, null)))
                ////{
                ////    this.viewModel.ToggleCommand.Execute(new Tuple<DisplayElement, ElementSelectionMethod, bool?>(this.viewModel.CurrentDisplayElement, this.viewModel.DefaultSelectionMethod, null));

                ////    return;
                ////}

                this.viewModel.CurrentStartCoordinates = new Point((int)e.GetPosition(this.canvasRealCapture).X, (int)e.GetPosition(this.canvasRealCapture).Y);

                // Selects by default selection method.
                if (this.viewModel.SelectByDefaultSelectionMethodCommand.CanExecute(true))
                    this.viewModel.SelectByDefaultSelectionMethodCommand.Execute(true);

                string clipboardText = Clipboard.GetText();

                if (!string.IsNullOrEmpty(clipboardText) && clipboardText != this.textBlockInfoText.Text)
                    this.textBlockInfoText.Text = clipboardText;
            }

            // Pinch
            else if (this.radioButtonPinch.IsChecked == true)
            {
                if (!this.viewModel.PinchStarted)
                {
                    this.pinchCenter = e.GetPosition(this.canvasRealCapture);
                    this.viewModel.PinchStarted = true;
                    this.clearCanvas();

                    // Draw an ellipse to indicate the center point of the pinch
                    this.viewModel.DrawEllipse(this.pinchCenter, 5);
                }
                else
                {
                    this.CopyToClipboard(this.viewModel.CreatePinchString(this.pinchCenter,
                                                                          e.GetPosition(this.canvasRealCapture),
                                                                          this.StartPosition,
                                                                          new Point(this.canvasRealCapture.Width,
                                                                                        this.canvasRealCapture.Height)));
                    this.viewModel.PinchStarted = false;
                    this.clearCanvas();
                }

            }
            // Swipe
            else if (this.radioButtonSwipe.IsChecked == true)
            {
                this.CopyToClipboard(
                    string.Format(
                        "self.gesture.swipe(({0:0.0000},{1:0.0000}), ({2:0.0000},{3:0.0000}))",
                        Math.Round(this.StartPosition.X / this.canvasRealCapture.Width, 4),
                        Math.Round(this.StartPosition.Y / this.canvasRealCapture.Height, 4),
                        Math.Round(e.GetPosition(this.canvasRealCapture).X / this.canvasRealCapture.Width, 4),
                        Math.Round(e.GetPosition(this.canvasRealCapture).Y / this.canvasRealCapture.Height, 4)));

                this.clearCanvas();
            }
            // Gesture
            else if (this.radioButtonGesture.IsChecked == true)
            {
                ////Clipboard.SetText(this.pointCollection.ToString());
                Clipboard.SetDataObject(this.pointCollection.ToString());
                this.textBlockInfoText.Text = string.Format("Gesture with {0} points", this.pointCollection.Count);
                this.pointCollection.Clear();
                this.SendGeneratedScriptCommand();
                this.clearCanvas();
            }

            this.DraggedDisplayElement = null;
        }

        /// <summary>
        /// Sets contextMenuOpening variable to true.
        /// So drawn display elements are not cleared in OnRealCaptureMouseLeave event handler.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RealCapture_MouseRightButtonUp(object sender, MouseButtonEventArgs e)
        {
            ////this.contextMenuOpening = true;

            if (this.radioButtonElement.IsChecked == true && this.dragUsingRightMouseButtonStarted && this.DraggedDisplayElement != null)
            {
                Point endPoint = new Point(this.DraggedDisplayElement.Center.X + e.GetPosition(this.canvasRealCapture).X - this.StartPosition.X,
                                           this.DraggedDisplayElement.Center.Y + e.GetPosition(this.canvasRealCapture).Y - this.StartPosition.Y);

                this.viewModel.CurrentEndCoordinates = endPoint;

                ContextMenu dragContextMenu =
                    this.canvasRealCapture.Resources["ContextMenuCanvasRealCaptureDrag"] as ContextMenu;

                if (dragContextMenu != null)
                {
                    this.canvasRealCapture.IsHitTestVisible = false;
                    dragContextMenu.DataContext = this.viewModel;
                    this.canvasRealCapture.ContextMenu = dragContextMenu;
                    this.canvasRealCapture.ContextMenu.IsOpen = true;
                }
            }
            else
            {
                this.dragStarted = false;
                this.dragUsingRightMouseButtonStarted = false;

                this.DraggedDisplayElement = null;
            }
        }

        /// <summary>
        /// Creates the script command (string) for drag.
        /// </summary>
        /// <param name="mousePosition">Current mouse position over the captured image (canvas).</param>
        /// <returns>Script command for drag e.g. self.gesture.drag('cat.png', (10, 20))</returns>
        private string GetDragResult(Point mousePosition)
        {
            Vector displacement = mousePosition - this.StartPosition;

            string textToReturn = string.Format(
                "self.gesture.drag('{0}', ({1},{2}))",
                this.viewModel.GetDisplayElementIdentifier(this.DraggedDisplayElement),
                Math.Round((this.DraggedDisplayElement.Center.X + displacement.X) / this.canvasRealCapture.Width, 4),
                Math.Round((this.DraggedDisplayElement.Center.Y + displacement.Y) / this.canvasRealCapture.Height, 4));
            this.dragStarted = false;
            this.clearCanvas();

            return textToReturn;
        }

        /// <summary>
        /// Creates the script command (string) for select or long select
        /// </summary>
        /// <returns>Script command for select e.g. self.select('cat.png')</returns>
        private string GetSelectResult()
        {
            DisplayElement selectedDisplayElement = null;

            // Select the DisplayElement with smallest area
            foreach (DisplayElement displayElement in this.dataGridElementTable.SelectedItems)
            {
                if (selectedDisplayElement == null ||
                    selectedDisplayElement.Rectangle.Width * selectedDisplayElement.Rectangle.Height >
                        displayElement.Rectangle.Width * displayElement.Rectangle.Height)
                    selectedDisplayElement = displayElement;
            }

            // Click duration less than a second = normal (short) click, else Long click, more than a second.
            return
                string.Format(
                    DateTime.Now - this.clickStart < new TimeSpan(0, 0, 1)
                        ? "self.select('{0}')"
                        : "self.select.long('{0}')", selectedDisplayElement.SelectedTranslation.Replace("'", @"\'"));
        }

        /// <summary>
        /// Store the start coordinate of the mouse operation.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRealCaptureMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            ////this.StartPosition.X = (int)e.GetPosition(this.canvasRealCapture).X;
            ////this.StartPosition.Y = (int)e.GetPosition(this.canvasRealCapture).Y;
            this.StartPosition = e.GetPosition(this.canvasRealCapture);
            this.pointCollection.Clear();
            this.pointCollection.Add(this.StartPosition);
            this.clickStart = DateTime.Now;

            if (this.radioButtonElement.IsChecked == true)
            {
                // Select the DisplayElement with smallest area
                foreach (DisplayElement displayElement in this.dataGridElementTable.SelectedItems)
                {
                    if (this.DraggedDisplayElement == null ||
                        this.DraggedDisplayElement.Rectangle.Width * this.DraggedDisplayElement.Rectangle.Height >
                        displayElement.Rectangle.Width * displayElement.Rectangle.Height)
                        this.DraggedDisplayElement = displayElement;
                }
            }
        }

        /// <summary>
        /// Store information from right button drag.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RealCapture_OnMouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.StartPosition = e.GetPosition(this.canvasRealCapture);
            this.pointCollection.Clear();
            this.pointCollection.Add(this.StartPosition);
            this.clickStart = DateTime.Now;

            if (this.radioButtonElement.IsChecked == true)
            {
                // Select the DisplayElement with smallest area
                foreach (DisplayElement displayElement in this.dataGridElementTable.SelectedItems)
                {
                    if (this.DraggedDisplayElement == null ||
                        this.DraggedDisplayElement.Rectangle.Width * this.DraggedDisplayElement.Rectangle.Height >
                        displayElement.Rectangle.Width * displayElement.Rectangle.Height)
                        this.DraggedDisplayElement = displayElement;
                }
            }
        }

        /// <summary>
        /// Store the start position of the swipe if the left mouse button is pressed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRealCaptureMouseEnter(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed && this.radioButtonSwipe.IsChecked == true)
                this.StartPosition = e.GetPosition(this.canvasRealCapture);
        }

        /// <summary>
        /// Displays a save file dialog for saving the captured image.
        /// Stores display elements into image as a meta data.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnSaveButtonClick(object sender, RoutedEventArgs e)
        {
            this.viewModel.SaveCaptureImage();
        }

        /// <summary>
        /// Closes the capture tool window.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnButtonCloseClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Selects a row under the mouse cursor and draws the corresponding display element.
        /// Other selections and display elements are cleared.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnElementTable_MouseMove(object sender, MouseEventArgs e)
        {
            DependencyObject dep = (DependencyObject)e.OriginalSource;

            // Iteratively traverse the visual tree
            while ((dep != null) && !(dep is DataGridRow))
                dep = VisualTreeHelper.GetParent(dep);

            if (dep == null) return;

            DataGridRow row = dep as DataGridRow;

            // Select new row and draw the display element
            if (row.IsMouseOver && !row.IsSelected)
            {
                this.dataGridElementTable.UnselectAll();
                this.clearCanvas();
                row.IsSelected = true;
                this.viewModel.DrawDisplayElement(row.Item as DisplayElement, this.viewModel.CanvasRealCapture);
            }
        }

        /// <summary>
        /// Copies the display element content to clip board.
        /// Prevents manual selection of cells or rows from the table.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ElementTable_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            DependencyObject dep = (DependencyObject)e.OriginalSource;

            // Iteratively traverse the visual tree.
            while ((dep != null) && !((dep is DataGridRow) || (dep is System.Windows.Controls.Primitives.ToggleButton)))
                dep = VisualTreeHelper.GetParent(dep);

            if (dep == null || dep is System.Windows.Controls.Primitives.ToggleButton) return;

            // Copy DisplayElement content to clipboard and display it
            DataGridRow row = dep as DataGridRow;
            string content = (row.Item as DisplayElement).SelectedTranslation;
            this.CopyToClipboard(content, false);

            // Prevent cell/row selection by mouse click
            e.Handled = true;
        }

        /// <summary>
        /// Unselects all display elements from the table and from the real capture.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ElementTable_MouseLeave(object sender, MouseEventArgs e)
        {
            this.dataGridElementTable.UnselectAll();
            this.clearCanvas();
        }

        /// <summary>
        /// Handler for the "Copy image to clipboard" context menu item
        /// Real capture image is copied to the clipboard.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CopyImageToClipboard_Click(object sender, RoutedEventArgs e)
        {
            Clipboard.SetImage(new BitmapImage(new Uri(this.viewModel.ImagePath, UriKind.Relative)));
        }

        /// <summary>
        /// Hides/Shows context menu items depending on whether mouse is over a display element.
        /// Stores the click position.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ContextMenu_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            if (sender == this.dataGridElementTable)
            {
                if (this.dataGridElementTable.SelectedItem == null) return;

                DisplayElement selectedDisplayElement = this.dataGridElementTable.SelectedItem as DisplayElement;

                if (selectedDisplayElement == null) return;

                this.StartPosition = new Point(selectedDisplayElement.Rectangle.X, selectedDisplayElement.Rectangle.Y);

                this.viewModel.CurrentDisplayElement = selectedDisplayElement;
            }
            else
            {
                this.canvasRealCapture.IsHitTestVisible = false;

                this.StartPosition = new Point((int)e.CursorLeft, (int)e.CursorTop);

                // Current display element is set when context menu is opened.
                this.viewModel.CurrentDisplayElement = this.viewModel.SelectSmallestDisplayElement(this.StartPosition, DisplayElementType.Node);
            }

            if (this.viewModel.CurrentDisplayElement == null)
                this.viewModel.SelectSmallestDisplayElement(this.StartPosition);

            // Show expect and notExpect menu items
            if (this.radioButtonElement.IsChecked == true &&
                this.viewModel.DisplayElements.Any(dElem => dElem.Rectangle.Contains((int)this.StartPosition.X, (int)this.StartPosition.Y)))
            {
                ExpectContextMenuItem.Visibility = Visibility.Visible;
                DontExpectContextMenuItem.Visibility = Visibility.Visible;
            }
            // Hide expect and notExpect menu items
            else
            {
                ExpectContextMenuItem.Visibility = Visibility.Collapsed;
                DontExpectContextMenuItem.Visibility = Visibility.Collapsed;
            }

            this.addIndexWarningsForMenuItems();
        }

        private void addIndexWarningsForMenuItems()
        {
            this.removeIndexWarningsForMenuItems();

            if (this.CurrentDisplayElement == null) return;

            var warningImage = new System.Windows.Controls.Image
                { Source = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/warning.shadow.icon.16x16.png", UriKind.RelativeOrAbsolute)) };

            if (!string.IsNullOrEmpty(this.CurrentDisplayElement.Description) &&
                this.viewModel.GetElementCount(new ElementSelectionParams() { Parameter = this.CurrentDisplayElement.Description, SelectionMethod = ElementSelectionMethod.Description }) > 1)
            {
                this.MenuItemSelectDescription.Icon = warningImage;
                this.StackPanelMenuItemSelectDescriptionWarning.Visibility = Visibility.Visible;
            }
            if (!string.IsNullOrEmpty(this.CurrentDisplayElement.ResourceId) &&
                this.viewModel.GetElementCount(new ElementSelectionParams() { Parameter = this.CurrentDisplayElement.ResourceId, SelectionMethod = ElementSelectionMethod.ResourceId }) > 1)
            {
                this.MenuItemSelectResourceId.Icon = warningImage;
                this.StackPanelMenuItemSelectResourceIdWarning.Visibility = Visibility.Visible;
            }
            if (!string.IsNullOrEmpty(this.CurrentDisplayElement.Text) &&
                this.viewModel.GetElementCount(new ElementSelectionParams() { Parameter = this.CurrentDisplayElement.Text, SelectionMethod = ElementSelectionMethod.Text }) > 1)
            {
                this.MenuItemSelectText.Icon = warningImage;
                this.StackPanelMenuItemSelectTextWarning.Visibility = Visibility.Visible;
            }
            if (!string.IsNullOrEmpty(this.CurrentDisplayElement.IndexTree) &&
                this.viewModel.GetElementCount(new ElementSelectionParams() { Parameter = this.CurrentDisplayElement.IndexTree, SelectionMethod = ElementSelectionMethod.IndexTree }) > 1)
            {
                this.MenuItemSelectIndexTree.Icon = warningImage;
                this.StackPanelMenuItemSelectIndexTreeWarning.Visibility = Visibility.Visible;
            }
        }

        private void removeIndexWarningsForMenuItems()
        {
            this.MenuItemSelectDescription.Icon = null;
            this.MenuItemSelectIndexTree.Icon = null;
            this.MenuItemSelectResourceId.Icon = null;
            this.MenuItemSelectText.Icon = null;

            this.StackPanelMenuItemSelectDescriptionWarning.Visibility = Visibility.Collapsed;
            this.StackPanelMenuItemSelectResourceIdWarning.Visibility = Visibility.Collapsed;
            this.StackPanelMenuItemSelectTextWarning.Visibility = Visibility.Collapsed;
            this.StackPanelMenuItemSelectIndexTreeWarning.Visibility = Visibility.Collapsed;
        }

        /// <summary>
        /// Displays and copies to clipboard selected method and display element.
        /// Smallest display element under the mouse position is selected.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ExpectContextMenuItem_Click(object sender, RoutedEventArgs e)
        {
            DisplayElement displayElement = this.viewModel.SelectSmallestDisplayElement(this.StartPosition);
            
            if (displayElement == null) return;

            // Expect menu item selected, else NotExpect menu item selected
            this.CopyToClipboard(
                string.Format(
                    (sender as MenuItem).Name == "ExpectContextMenuItem"
                        ? "self.expect('{0}')"
                        : "self.notExpect('{0}')", displayElement.SelectedTranslation.Replace("'", @"\'")));
        }

        /// <summary>
        /// Unselects and clears drawn display elements.
        /// Draws grid lines if needed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RealCapture_ContextMenuClosing(object sender, ContextMenuEventArgs e)
        {
            this.canvasRealCapture.IsHitTestVisible = true;

            this.clearCanvas();

            this.dataGridElementTable.UnselectAll();
            this.textBlockCoordinatesText.Text = string.Empty;
        }

        /// <summary>
        /// Clears canvas and draws grid, if it is activated.
        /// </summary>
        private void clearCanvas()
        {
            this.canvasRealCapture.Children.Clear();

            if (this.checkBoxDrawGrid.IsChecked == true)
                this.DrawGrid();
        }

        /// <summary>
        /// Copies text to clipboard and sets copied text as info text.
        /// </summary>
        /// <param name="textToCopy">Text that is copied to clip board and shown in Capture Tool.</param>
        /// <param name="executeText">Whether to send given text as an iron python command to the phone.</param>
        private void CopyToClipboard(string textToCopy, bool executeText=true)
        {
            ////Clipboard.SetText(textToCopy);
            Clipboard.SetDataObject(textToCopy);
            this.textBlockInfoText.Text = textToCopy;
            if (executeText)
                this.SendGeneratedScriptCommand();
        }

        /// <summary>
        /// Sends created script command to phone and re-captures the phone screen.
        /// If phone controls is enabled and clipboard contains texts.
        /// </summary>
        private void SendGeneratedScriptCommand()
        {
            if (Clipboard.ContainsText())
                this.viewModel.SendScriptCommand(Clipboard.GetText());
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        public void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]

        private void MenuItemCopyAllCommandHistory_Click(object sender, RoutedEventArgs e)
        {
            int selectionStart = this.avalonEditCommandHistory.SelectionStart;
            int selectionLenght = this.avalonEditCommandHistory.SelectionLength;

            this.avalonEditCommandHistory.SelectAll();
            this.avalonEditCommandHistory.Copy();
            this.avalonEditCommandHistory.Select(selectionStart, selectionLenght);

            //Clipboard.SetText(this.avalonEditCommandHistory.Text);
        }

        public DisplayElement CurrentDisplayElement
        {
            get
            {
                if (!this.IsLoaded || this.dataGridElementTable == null) return null;

                DisplayElement currentDisplayElement = null;

                foreach (DisplayElement selectedItem in this.dataGridElementTable.SelectedItems)
                {
                    if (currentDisplayElement == null)
                    {
                        currentDisplayElement = selectedItem;
                        continue;
                    }

                    // Display Element with smallest area is considered currently highlighted.
                    if ((selectedItem.Rectangle.Size.Width * selectedItem.Rectangle.Size.Height)
                        <= (currentDisplayElement.Rectangle.Size.Width * currentDisplayElement.Rectangle.Size.Height)) currentDisplayElement = selectedItem;
                }

                return currentDisplayElement;
            }
        }

        private void ToggleButtonRadioButtonAction_Click(object sender, RoutedEventArgs e)
        {
            if (sender == this.ToggleButtonSelect)
                this.radioButtonElement.IsChecked = true;
            else if (sender == this.ToggleButtonLongSelect) 
                this.radioButtonLongSelect.IsChecked = true;
            else if (sender == this.ToggleButtonPinch)
                this.viewModel.IsPinchToolInUse = true;
            else if (sender == this.ToggleButtonCoordinates)
                this.radioButtonDefaultSelectCoordinates.IsChecked = true;
            else if (sender == this.ToggleButtonSwipe)
                this.radioButtonSwipe.IsChecked = true;
            else if (sender == this.ToggleButtonGesture)
                this.radioButtonGesture.IsChecked = true;
        }

        private void ContextMenuCanvasRealCaptureDrag_OnClosed(object sender, RoutedEventArgs e)
        {
            this.DraggedDisplayElement = null;
            this.dragStarted = false;
            this.dragUsingRightMouseButtonStarted = false;

            this.canvasRealCapture.ContextMenu = this.ContextMenuCanvasRealCapture;
            this.canvasRealCapture.IsHitTestVisible = true;
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            this.viewModel.ToggleCommand.Execute(this.DraggedDisplayElement);
        }

        private void MenuItemButton_Click_CloseContextMenu(object sender, RoutedEventArgs e)
        {
            this.canvasRealCapture.ContextMenu.IsOpen = false;
        }

        private void AvalonEditCommandHistory_OnSelectionChanged(object sender, EventArgs e)
        {
            this.Dispatcher.BeginInvoke(DispatcherPriority.Normal, new Action(this.refreshButtonExecuteSelectedPython));
        }

        private void refreshButtonExecuteSelectedPython()
        {
            if ((int)App.ViewModel.MarbleConnector.State != (int)Marble.Communication.ConnectorState.Idle
                && (int)App.ViewModel.MarbleConnector.State != (int)Marble.Communication.ConnectorState.FrameworkReady)
            {
                this.ButtonExecuteSelectedPython.IsEnabled = false;
                return;
            }

            if (string.IsNullOrEmpty(this.avalonEditCommandHistory.SelectedText))
            {
                this.ButtonExecuteSelectedPython.IsEnabled = false;
                return;
            }

            string pythonScript = this.avalonEditCommandHistory.SelectedText.Trim();

            this.ButtonExecuteSelectedPython.IsEnabled =
                pythonScript.StartsWith(PythonScriptCommands.PythonScriptCommonPrefix)
                && pythonScript.EndsWith(PythonScriptCommands.PythonScriptCommonPostfix);
        }

        private void ButtonExecuteSelectedPython_OnClick(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(this.avalonEditCommandHistory.SelectedText))
            {
                return;
            }

            this.viewModel.ExecuteSelectedPythonCommand.Execute(this.avalonEditCommandHistory.SelectedText);
        }

        private void AvalonEditPythonParser_OnPreviewKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    if (completionWindow != null) return;

                    // When there's no text in parser, screen capture is updated.
                    if (string.IsNullOrWhiteSpace(this.AvalonEditPythonParser.Text))
                        if (this.CaptureButton.IsEnabled) 
                            this.OnCaptureButtonClick(sender, null);
                    else
                        this.executePythonParserCommand();

                    e.Handled = true;
                    break;
                case Key.Up:
                    if (string.IsNullOrEmpty(this.AvalonEditPythonParser.Text))
                        this.AvalonEditPythonParser.Text = TextUtilities.GetLastLine(this.avalonEditCommandHistory.Text);
                    this.AvalonEditPythonParser.Focus();
                    break;
            }
        }

        void FocusWhenConnectorReady_MarbleConnector_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            //this.Dispatcher.BeginInvoke(DispatcherPriority.Normal, new Action(() => this.TextBoxPythonParser.Focus()));
            this.Dispatcher.BeginInvoke(DispatcherPriority.Normal, new Action(() => this.AvalonEditPythonParser.Focus()));
            this.Dispatcher.BeginInvoke(DispatcherPriority.Normal, new Action(() => this.Focus()));
            App.ViewModel.MarbleConnector.PropertyChanged -= this.FocusWhenConnectorReady_MarbleConnector_PropertyChanged;
        }

        private void AvalonEditCommandHistory_OnTextChanged(object sender, EventArgs e)
        {
            this.viewModel.CommandHistoryChanged -= viewModel_CommandHistoryChanged;
            this.viewModel.CommandHistory = this.avalonEditCommandHistory.Text;
            this.viewModel.CommandHistoryChanged += viewModel_CommandHistoryChanged;
        }

        private void executePythonParserCommand()
        {
            this.viewModel.SendScriptCommand(this.AvalonEditPythonParser.Text);
            this.AvalonEditPythonParser.Text = string.Empty;

            App.ViewModel.MarbleConnector.PropertyChanged += this.FocusWhenConnectorReady_MarbleConnector_PropertyChanged;
        }

        private void ButtonExecutePythonParserCommand_Click(object sender, RoutedEventArgs e)
        {
            this.executePythonParserCommand();
        }

        private void canvasRealCapture_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.Height = this.stackPanelLeft.ActualHeight + this.GridWindowBottomBar.ActualHeight + 72;
            this.Width = this.ItemsControlLeftSideMenu.ActualWidth + this.stackPanelLeft.ActualWidth + this.ColumnDefinitionCommandHistory.MinWidth + 32;

            if (this.ToggleButtonShowElementTable.IsChecked == true)
            {
                this.Width += this.AdvancedGridSplitterElementTable.ActualWidth + this.elementTableColumnWidth;
            }
        }

        private void ToggleButtonShowElementTable_Click(object sender, RoutedEventArgs e)
        {
            this.storeAndRestoreElementTableColumnWidth();
        }

        private void storeAndRestoreElementTableColumnWidth()
        {
            if (this.ColumnDefinitionElementTable.Visible)
            {
                // Element table width and min width are restored.
                this.ColumnDefinitionElementTable.MinWidth = elementTableColumnMinWidth;

                this.Width += this.AdvancedGridSplitterElementTable.ActualWidth + this.elementTableColumnWidth;
                
                this.ColumnDefinitionElementTable.Width = new GridLength(1, GridUnitType.Star);
                this.dataGridElementTable.Width = double.NaN;
            }
            else
            {
                // Element table width and min width are stored.
                elementTableColumnWidth = this.ColumnDefinitionElementTable.ActualWidth;
                elementTableColumnMinWidth = this.ColumnDefinitionElementTable.MinWidth;

                this.ColumnDefinitionElementTable.MinWidth = 0;
                this.ColumnDefinitionElementTable.Width = new GridLength(0);

                this.Width -= this.AdvancedGridSplitterElementTable.Width + this.elementTableColumnWidth;
            }
        }

        /// <summary>
        /// Handles only Escape-key. Restarts pinch creation if center point is selected.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void windowCaptureTool_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape && this.viewModel.PinchStarted)
            {
                this.viewModel.PinchStarted = false;
                this.clearCanvas();
            }
        }
    }
}
