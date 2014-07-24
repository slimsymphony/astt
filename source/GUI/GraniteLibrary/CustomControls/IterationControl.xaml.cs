using System;
using System.Windows;
using System.Windows.Controls;

namespace MarbleLibrary.CustomControls
{
    /// <summary>
    /// Interaction logic for IterationControl.xaml
    /// </summary>
    public partial class IterationControl : UserControl
    {
        public event EventHandler AddItem;
        public event EventHandler RemoveItem;
        public event EventHandler MoveFirst;
        public event EventHandler MoveLast;
        public event EventHandler MovePrevious;
        public event EventHandler MoveNext;

        public IterationControl()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty IterationCountProperty = DependencyProperty.Register("IterationCount", typeof(int), typeof(IterationControl),
            new PropertyMetadata(IterationsChanged));

        public static readonly DependencyProperty IterationIndexProperty = DependencyProperty.Register("IterationIndex", typeof(int), typeof(IterationControl),
            new PropertyMetadata(IterationsChanged));

        public static void IterationsChanged(DependencyObject dependencyObject, DependencyPropertyChangedEventArgs prop)
        {
            IterationControl control = dependencyObject as IterationControl;
            if (control != null)
            {
                control.ResetControlsState();
            }
        }

        public int IterationCount
        {
            get
            {
                return (int)GetValue(IterationCountProperty);
            }
            set
            {
                SetValue(IterationCountProperty, value);
            }
        }

        public int IterationIndex
        {
            get
            {
                return (int)GetValue(IterationIndexProperty);
            }
            set
            {
                SetValue(IterationIndexProperty, value);
            }
        }

        private void ResetControlsState()
        {
            if (IterationCount > 0 && IterationIndex >= 0 && IterationIndex < IterationCount)
            {
                _beginButton.IsEnabled = true;
                _previousButton.IsEnabled = true;
                _nextButton.IsEnabled = true;
                _endButton.IsEnabled = true;
                _addButton.IsEnabled = true;
                _removeButton.IsEnabled = true;

                if (IterationIndex == 0)
                {
                     _beginButton.IsEnabled = false;
                    _previousButton.IsEnabled = false;
                }

                if (IterationIndex == IterationCount - 1)
                {
                    _nextButton.IsEnabled = false;
                    _endButton.IsEnabled = false;
                }

                if (IterationCount == 1)
                {
                    _removeButton.IsEnabled = false;
                }

                _indexText.Text = string.Format("{0} of {1}", IterationIndex + 1, IterationCount);
            }
            else
            {
                _beginButton.IsEnabled = false;
                _previousButton.IsEnabled = false;
                _nextButton.IsEnabled = false;
                _endButton.IsEnabled = false;
                _addButton.IsEnabled = false;
                _removeButton.IsEnabled = false;

                _indexText.Text = "";
            }
        }

        private void OnButtonClick(object sender, RoutedEventArgs e)
        {
            Button button = sender as Button;
            if (button == _addButton && AddItem != null)
            {
                AddItem(this, new EventArgs());
            }
            else if (button == _removeButton && RemoveItem != null)
            {
                RemoveItem(this, new EventArgs());
            }
            else if (button == _beginButton && MoveFirst != null)
            {
                MoveFirst(this, new EventArgs());
            }
            else if (button == _previousButton && MovePrevious != null)
            {
                MovePrevious(this, new EventArgs());
            }
            else if (button == _nextButton && MoveNext != null)
            {
                MoveNext(this, new EventArgs());
            }
            else if (button == _endButton && MoveLast != null)
            {
                MoveLast(this, new EventArgs());
            }
        }
    }
}
