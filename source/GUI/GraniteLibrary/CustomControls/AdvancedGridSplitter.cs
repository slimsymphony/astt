// -----------------------------------------------------------------------
// <copyright file="AdvancedGridSplitter.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.CustomControls
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Controls.Primitives;
    using System.Windows.Media.Animation;
    using System.Windows.Shapes;

    using MarbleLibrary.Utilities;

    // Grid splitter must have HorizontalAlignment="Stretch" VerticalAlignment="Center" when in Row mode and
    // HorizontalAlignment="Center" VerticalAlignment="Stretch" when in Column mode.

    /// <summary>
    /// Enum for collapse mode.
    /// None -> GridSplitter can not collapse.
    /// Previous -> GridSplitter collapses GridColumn or GridRow before GridSplitter when collapsing.
    /// Next -> GridSplitter collapses GridColumn or GridRow after GridSplitter when collapsing.
    /// </summary>
    public enum CollapseMode
    {
        /// <summary>
        /// GridSplitter can not collapse.
        /// </summary>
        None = 0,

        /// <summary>
        /// GridSplitter collapses GridColumn or GridRow before GridSplitter when collapsing.
        /// </summary>
        Previous = 1,

        /// <summary>
        /// GridSplitter collapses GridColumn or GridRow after GridSplitter when collapsing.
        /// </summary>
        Next = 2
    }

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    [TemplatePart(Name = expandCollapseButton, Type = typeof(ToggleButton))]
    [TemplatePart(Name = backgroundGridSplitter, Type = typeof(FrameworkElement))]
    public class AdvancedGridSplitter : GridSplitter
    {
        private const string expandCollapseButton = "ExpandCollapseButton";
        private const string backgroundGridSplitter = "GridSplitterBackground";
        private const string expandCollapseButtonStylePrevious = "ExpandCollapseButtonStylePreviousColumn";
        private const string expandCollapseButtonStyleNext = "ExpandCollapseButtonStyleNextColumn";
        private const string expandCollapseButtonStylePreviousRow = "ExpandCollapseButtonStylePreviousRow";
        private const string expandCollapseButtonStyleNextRow = "ExpandCollapseButtonStyleNextRow";
        private const string gridSplitterVerticalRectangle = "GridSplitterVerticalRectangle";
        private const string gridSplitterHorizontalRectangle = "GridSplitterHorizontalRectangle";
        private const double expandCollapseButtonLength = 60;

        private ToggleButton buttonExpandCollapse;
        
        private GridLength previousGridWidth;
        private GridLength previousGridHeight;
        private double previousGridSplitterActualLength;
        private double previousGridActualWidth;
        private double previousGridActualHeight;
        private ColumnDefinition animationColumn;
        private RowDefinition animationRow;
        private double minGridLength;

        private Rectangle rectangleGridSplitterBackground;

        internal Rectangle RectangleGridSplitterBackground
        {
            get
            {
                if (this.rectangleGridSplitterBackground == null)
                    return new Rectangle();
                return this.rectangleGridSplitterBackground;
            }
            set
            {
                this.rectangleGridSplitterBackground = value;
            }
        }

        /// <summary>
        /// Gets or sets the collapse mode of the AdvancedGridSplitter.
        /// </summary>
        public CollapseMode CollapseMode
        {
            get { return (CollapseMode)GetValue(CollapseModeProperty); }
            set { SetValue(CollapseModeProperty, value); }
        }

        public static readonly DependencyProperty CollapseModeProperty = DependencyProperty.Register(
            "CollapseMode",
            typeof(CollapseMode),
            typeof(AdvancedGridSplitter),
            new PropertyMetadata(CollapseMode.None, new PropertyChangedCallback(OnCollapseModePropertyChanged)));

        private static void OnCollapseModePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            AdvancedGridSplitter gridSplitter = d as AdvancedGridSplitter;

            CollapseMode collapseMode = (CollapseMode)e.NewValue;
        }

        /// <summary>
        /// Gets or sets bool which states if AdvancedGridSplitter is collapsed.
        /// </summary>
        public bool IsCollapsed
        {
            get { return (bool)GetValue(IsCollapsedProperty); }
            set { SetValue(IsCollapsedProperty, value); }
        }

        public static readonly DependencyProperty IsCollapsedProperty = DependencyProperty.Register(
            "IsCollapsed",
            typeof(bool),
            typeof(AdvancedGridSplitter),
            new PropertyMetadata(new PropertyChangedCallback(OnIsCollapsedPropertyChanged)));

        private static void OnIsCollapsedPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            AdvancedGridSplitter AdvancedGridSplitter = d as AdvancedGridSplitter;
            AdvancedGridSplitter.OnIsCollapsedChanged((bool)e.NewValue);
            AdvancedGridSplitter.OnIsCollapsedValueChanged();
        }

        /// <summary>
        /// Routed event for which is raised when IsCollapsedValue has changed.
        /// </summary>
        public static RoutedEvent IsCollapsedValueChangedEvent;

        /// <summary>
        /// Routed event handler IsCollapsedValueChanged.
        /// </summary>
        public event RoutedEventHandler IsCollapsedValueChanged
        {
            add { AddHandler(IsCollapsedValueChangedEvent, value); }
            remove { RemoveHandler(IsCollapsedValueChangedEvent, value); }
        }

        /// <summary>
        /// Called when [is collapsed value changed].
        /// </summary>
        protected virtual void OnIsCollapsedValueChanged()
        {
            RoutedEventArgs args = new RoutedEventArgs();
            args.RoutedEvent = IsCollapsedValueChangedEvent;
            RaiseEvent(args);
        }

        /// <summary>
        /// Initializes a new instance of the AdvancedGridSplitter class.
        /// </summary>
        public AdvancedGridSplitter()
        {
            DefaultStyleKey = typeof(AdvancedGridSplitter);

            this.CollapseMode = CollapseMode.Previous;

            if (IsCollapsedValueChangedEvent == null)
                IsCollapsedValueChangedEvent = EventManager.RegisterRoutedEvent("IsCollapsedValueChanged", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(AdvancedGridSplitter));

            this.IsEnabledChanged += delegate { this.updateBackgroundEnabledDisabledStyle(); };
            this.Loaded += delegate { if (this.IsCollapsed) this.collapseGridSplitter(false); };
        }

        private double AnimationColumnWidth
        {
            get { return (double)GetValue(AnimationColumnWidthProperty); }
            set { SetValue(AnimationColumnWidthProperty, value); }
        }

        private static readonly DependencyProperty AnimationColumnWidthProperty = DependencyProperty.Register(
            "AnimationColumnWidth",
            typeof(double),
            typeof(AdvancedGridSplitter),
            new PropertyMetadata(new PropertyChangedCallback(AnimationColumnWidthChanged)));

        private static void AnimationColumnWidthChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            AdvancedGridSplitter advancedGridSplitter = d as AdvancedGridSplitter;

            if (advancedGridSplitter == null) return;

            advancedGridSplitter.animationColumn.Width = new GridLength((double)e.NewValue);
        }

        private double AnimationRowHeight
        {
            get { return (double)GetValue(AnimationRowHeightProperty); }
            set { SetValue(AnimationRowHeightProperty, value); }
        }

        private static readonly DependencyProperty AnimationRowHeightProperty = DependencyProperty.Register(
            "AnimationRowHeight",
            typeof(double),
            typeof(AdvancedGridSplitter),
            new PropertyMetadata(new PropertyChangedCallback(AnimationRowHeightChanged)));

        private static void AnimationRowHeightChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            AdvancedGridSplitter advancedGridSplitter = d as AdvancedGridSplitter;

            if (advancedGridSplitter == null) return;

            advancedGridSplitter.animationRow.Height = new GridLength((double)e.NewValue);
        }

        /// <summary>
        /// Method called when template for the GridSplitter is applied.
        /// </summary>
        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            ResourceDictionary resourceDictionary = new ResourceDictionary();
            resourceDictionary.Source = new Uri("pack://application:,,,/MarbleLibrary;component/Templates/AdvancedGridSplitter.xaml", UriKind.Absolute);

            this.buttonExpandCollapse = GetTemplateChild(expandCollapseButton) as ToggleButton;
            this.RectangleGridSplitterBackground = GetTemplateChild(backgroundGridSplitter) as Rectangle;

            if (this.CollapseMode != CollapseMode.None)
            {
                this.buttonExpandCollapse.Checked += new RoutedEventHandler(this.buttonExpandCollapse_Checked);
                this.buttonExpandCollapse.Unchecked += new RoutedEventHandler(this.buttonExpandCollapse_Unchecked);

                this.minGridLength = this.Width;
            }
            else
            {
                this.buttonExpandCollapse.Visibility = Visibility.Hidden;
            }

            if (this.ResizeDirection == GridResizeDirection.Columns)
            {
                this.buttonExpandCollapse.Height = expandCollapseButtonLength;

                if (this.IsCollapsed)
                    this.RectangleGridSplitterBackground.Style = resourceDictionary[gridSplitterVerticalRectangle + "Disabled"] as Style;
                else
                    this.RectangleGridSplitterBackground.Style = resourceDictionary[gridSplitterVerticalRectangle] as Style;

                if (this.CollapseMode == CollapseMode.Previous)
                    this.buttonExpandCollapse.Style = resourceDictionary[expandCollapseButtonStylePrevious] as Style;
                if (this.CollapseMode == CollapseMode.Next)
                    this.buttonExpandCollapse.Style = resourceDictionary[expandCollapseButtonStyleNext] as Style;
            }
            else if (this.ResizeDirection == GridResizeDirection.Rows)
            {
                this.buttonExpandCollapse.Width = expandCollapseButtonLength;

                if (this.IsCollapsed)
                    this.RectangleGridSplitterBackground.Style = resourceDictionary[gridSplitterHorizontalRectangle + "Disabled"] as Style;
                else
                    this.RectangleGridSplitterBackground.Style = resourceDictionary[gridSplitterHorizontalRectangle] as Style;

                if (this.CollapseMode == CollapseMode.Previous)
                    this.buttonExpandCollapse.Style = resourceDictionary[expandCollapseButtonStylePreviousRow] as Style;
                if (this.CollapseMode == CollapseMode.Next)
                    this.buttonExpandCollapse.Style = resourceDictionary[expandCollapseButtonStyleNextRow] as Style;
            }

            if (this.IsCollapsed) this.collapseGridSplitter(true);

            this.IsVisibleChanged += delegate { this.collapseExpandOnVisibileChanged(true); };
        }

        private void collapseExpandOnVisibileChanged(bool useAnimation)
        {
            if (this.Visibility == Visibility.Collapsed)
            {
                this.collapseGridSplitter(useAnimation);
                this.RectangleGridSplitterBackground.IsHitTestVisible = true;
            }
            else
            {
                this.expandAnimation(useAnimation);
                this.RectangleGridSplitterBackground.IsHitTestVisible = true;
            }
        }

        private void updateBackgroundEnabledDisabledStyle()
        {
            ResourceDictionary resourceDictionary = new ResourceDictionary();
            resourceDictionary.Source =
                new Uri("pack://application:,,,/MarbleLibrary;component/Templates/AdvancedGridSplitter.xaml", UriKind.Absolute);

            this.RectangleGridSplitterBackground = GetTemplateChild(backgroundGridSplitter) as Rectangle;

            if (this.RectangleGridSplitterBackground == null) return;

            switch (this.ResizeDirection)
            {
                case GridResizeDirection.Columns:
                    if (this.IsCollapsed || !this.IsEnabled)
                    {
                        this.RectangleGridSplitterBackground.Style =
                            resourceDictionary[gridSplitterVerticalRectangle + "Disabled"] as Style;

                        if (this.CollapseMode == CollapseMode.None)
                        {
                            this.previousGridSplitterActualLength = this.Width;
                            this.Width = 0;
                        }
                    }
                    else
                    {
                        this.RectangleGridSplitterBackground.Style =
                            resourceDictionary[gridSplitterVerticalRectangle] as Style;

                        if (this.CollapseMode == CollapseMode.None) this.Width = this.previousGridSplitterActualLength;
                    }
                    break;

                case GridResizeDirection.Rows:
                    if (this.IsCollapsed || !this.IsEnabled)
                    {
                        this.RectangleGridSplitterBackground.Style =
                            resourceDictionary[gridSplitterHorizontalRectangle + "Disabled"] as Style;

                        if (this.CollapseMode == CollapseMode.None)
                        {
                            this.previousGridSplitterActualLength = this.Height;
                            this.Height = 0;
                        }
                    }
                    else
                    {
                        this.RectangleGridSplitterBackground.Style =
                            resourceDictionary[gridSplitterHorizontalRectangle] as Style;

                        if (this.CollapseMode == CollapseMode.None) this.Height = this.previousGridSplitterActualLength;
                    }
                    break;
            }
        }

        private void buttonExpandCollapse_Checked(object sender, RoutedEventArgs e)
        {
            this.collapseGridSplitter(true);
            this.IsCollapsed = true;
            this.updateBackgroundEnabledDisabledStyle();
        }

        private void buttonExpandCollapse_Unchecked(object sender, RoutedEventArgs e)
        {

            this.expandGridSplitter(true);
            this.IsCollapsed = false;
            this.updateBackgroundEnabledDisabledStyle();
        }

        /// <summary>
        /// Called when [is collapsed changed].
        /// </summary>
        /// <param name="isCollapsed">if set to <c>true</c> [is collapsed].</param>
        protected virtual void OnIsCollapsedChanged(bool isCollapsed)
        {
            if (this.buttonExpandCollapse == null) return;

            this.buttonExpandCollapse.IsChecked = isCollapsed;
            this.OnPropertyChanged(new DependencyPropertyChangedEventArgs(IsCollapsedProperty, !isCollapsed, isCollapsed));
        }

        private void collapseGridSplitter(bool useAnimation)
        {
            // Grid splitter is collapsed when it is checked.
            Grid parentGrid = base.Parent as Grid;

            if (this.ResizeDirection == GridResizeDirection.Columns)
            {
                int splitterIndex = (int)base.GetValue(Grid.ColumnProperty);
                ColumnDefinition collapsedColumn;

                if (this.CollapseMode == CollapseMode.Previous)
                    collapsedColumn = parentGrid.ColumnDefinitions[splitterIndex - 1];
                else
                    collapsedColumn = parentGrid.ColumnDefinitions[splitterIndex + 1];

                this.previousGridWidth = collapsedColumn.Width;
                this.previousGridActualWidth = collapsedColumn.ActualWidth;

                if (useAnimation)
                    this.collapseAnimation(collapsedColumn);
                else
                    collapsedColumn.SetValue(ColumnDefinition.WidthProperty, new GridLength(0));


                //Storyboard sb = (Storyboard)buttonExpandCollapse.FindResource("RotateArrow");
                ////Storyboard sb = GetTemplateChild("RotateArrow") as Storyboard;
                //sb.Begin(); 

                this.RectangleGridSplitterBackground.IsHitTestVisible = false;
            }
            else if (this.ResizeDirection == GridResizeDirection.Rows)
            {
                int splitterIndex = (int)base.GetValue(Grid.RowProperty);
                RowDefinition collapsedRow;

                if (this.CollapseMode == CollapseMode.Previous)
                    collapsedRow = parentGrid.RowDefinitions[splitterIndex - 1];
                else
                    collapsedRow = parentGrid.RowDefinitions[splitterIndex + 1];

                this.previousGridHeight = collapsedRow.Height;
                this.previousGridActualHeight = collapsedRow.ActualHeight;

                if (useAnimation)
                    this.collapseAnimation(collapsedRow);
                else
                    collapsedRow.SetValue(RowDefinition.HeightProperty, new GridLength(0));

                this.RectangleGridSplitterBackground.IsHitTestVisible = false;
            }
        }

        private void expandGridSplitter(bool useAnimation)
        {
            // Grid splitter is expanded when it is unchecked.
            Grid parentGrid = base.Parent as Grid;

            if (this.ResizeDirection == GridResizeDirection.Columns)
            {
                int splitterIndex = (int)base.GetValue(Grid.ColumnProperty);
                ColumnDefinition expandedColumn;

                if (this.CollapseMode == CollapseMode.Previous)
                    expandedColumn = parentGrid.ColumnDefinitions[splitterIndex - 1];
                else
                    expandedColumn = parentGrid.ColumnDefinitions[splitterIndex + 1];

                if (useAnimation)
                    this.expandAnimation(expandedColumn);
                else
                    expandedColumn.SetValue(ColumnDefinition.WidthProperty, this.previousGridWidth);

                this.RectangleGridSplitterBackground.IsHitTestVisible = true;
            }
            else if (this.ResizeDirection == GridResizeDirection.Rows)
            {
                int splitterIndex = (int)base.GetValue(Grid.RowProperty);
                RowDefinition expandedRow;

                if (this.CollapseMode == CollapseMode.Previous)
                    expandedRow = parentGrid.RowDefinitions[splitterIndex - 1];
                else
                    expandedRow = parentGrid.RowDefinitions[splitterIndex + 1];

                if (useAnimation)
                    this.expandAnimation(expandedRow);
                else
                    expandedRow.SetValue(RowDefinition.HeightProperty, this.previousGridHeight);

                this.RectangleGridSplitterBackground.IsHitTestVisible = true;
            }
        }

        private void collapseAnimation(object rowOrColumnDefinition)
        {
            if (!(rowOrColumnDefinition is RowDefinition) && !(rowOrColumnDefinition is ColumnDefinition)) return;

            if (this.ResizeDirection == GridResizeDirection.Columns)
            {
                this.animationColumn = rowOrColumnDefinition as ColumnDefinition;
                this.animateGridLengthChange(rowOrColumnDefinition, this.animationColumn.ActualWidth, 0);
            }
            else if (this.ResizeDirection == GridResizeDirection.Rows)
            {
                this.animationRow = rowOrColumnDefinition as RowDefinition;
                this.animateGridLengthChange(rowOrColumnDefinition, this.animationRow.ActualHeight, 0);
            }
        }

        private void expandAnimation(object rowOrColumnDefinition)
        {
            if (this.ResizeDirection == GridResizeDirection.Columns)
                this.animateGridLengthChange(rowOrColumnDefinition, 0, this.previousGridActualWidth);
            else if (this.ResizeDirection == GridResizeDirection.Rows)
                this.animateGridLengthChange(rowOrColumnDefinition, 0, this.previousGridActualHeight);
        }

        private void animateGridLengthChange(object rowOrColumnDefinition, double startValue, double endValue)
        {
            if (!(rowOrColumnDefinition is RowDefinition) && !(rowOrColumnDefinition is ColumnDefinition)) return;

            Storyboard storyboard = new Storyboard();
            DoubleAnimation gridLengthChangeAnimation = new DoubleAnimation()
            {
                Duration = new Duration(TimeSpan.FromMilliseconds(100))
            };

            storyboard.Children.Add(gridLengthChangeAnimation);

            if (rowOrColumnDefinition is ColumnDefinition)
            {
                this.animationColumn = rowOrColumnDefinition as ColumnDefinition;
                Storyboard.SetTarget(gridLengthChangeAnimation, this);
                Storyboard.SetTargetProperty(gridLengthChangeAnimation, new PropertyPath("AnimationColumnWidth"));
            }
            else if (rowOrColumnDefinition is RowDefinition)
            {
                this.animationRow = rowOrColumnDefinition as RowDefinition;
                Storyboard.SetTarget(gridLengthChangeAnimation, this);
                Storyboard.SetTargetProperty(gridLengthChangeAnimation, new PropertyPath("AnimationRowHeight"));
            }

            gridLengthChangeAnimation.From = startValue;
            gridLengthChangeAnimation.To = endValue;

            storyboard.Begin();
        }
    }
}
