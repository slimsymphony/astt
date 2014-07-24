namespace MarbleLibrary.CustomControls
{
    using System.Windows;
    using System.Windows.Controls;

    /// <summary>
    /// TextBox control that allows to set a limit to how many lines can be displayed.
    /// After set limit is reached, certain amount of lines are removed from the start.
    /// </summary>
    public class TextBoxBuffered : TextBox
    {
        static TextBoxBuffered()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(TextBoxBuffered), new FrameworkPropertyMetadata(typeof(TextBoxBuffered)));
        }

        public TextBoxBuffered()
        {
            this.IsUndoEnabled = false;
            this.UndoLimit = 0;
        }

        public static DependencyProperty BufferLimitProperty = DependencyProperty.Register(
            "BufferLimit",
            typeof(int),
            typeof(TextBoxBuffered),
            new PropertyMetadata(100));

        public int BufferLimit
        {
            get { return (int)this.GetValue(BufferLimitProperty); }
            set 
            { 
                this.SetValue(BufferLimitProperty, value);
                this.MaxLines = value;
            }
        }

        protected override void OnTextChanged(TextChangedEventArgs e)
        {
            base.OnTextChanged(e);

            if (this.LineCount > this.BufferLimit)
            {
                // Remove specified amount of text from TextBox if buffer limit is reached.
                double cutSize = this.Text.Length * 0.2;
                this.Text = this.Text.Remove(0, this.Text.IndexOf('\n', (int)cutSize) + 1);
            }

            e.Handled = true;
        }
    }
}
