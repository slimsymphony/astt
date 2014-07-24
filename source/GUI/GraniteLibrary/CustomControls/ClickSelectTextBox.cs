// -----------------------------------------------------------------------
// <copyright file="ClickSelectTextBox.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.CustomControls
{
    using System;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;
    using System.Windows.Media;

    /// <summary>
    /// ClickSelectTextBox class.
    /// </summary>
    public class ClickSelectTextBox : TextBox
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ClickSelectTextBox"/> class. 
        /// </summary>
        public ClickSelectTextBox()
        {
            this.AddHandler(PreviewMouseLeftButtonDownEvent, new MouseButtonEventHandler(SelectivelyIgnoreMouseButton), true);
            this.AddHandler(GotKeyboardFocusEvent, new RoutedEventHandler(SelectAllText), true);
            this.AddHandler(MouseDoubleClickEvent, new RoutedEventHandler(SelectAllText), true);
            this.AddHandler(PreviewDragOverEvent, new RoutedEventHandler(PrevievDragOver), true);
        }

        private static void PrevievDragOver(object sender, RoutedEventArgs e)
        {
            // Enabled dragging and dropping to the ClickSelectTextBox.
            e.Handled = true;
        }

        private static void SelectivelyIgnoreMouseButton(object sender, MouseButtonEventArgs e)
        {
            // Find the TextBox
            DependencyObject parent = e.OriginalSource as UIElement;

            while (parent != null && !(parent is TextBox))
            {
                parent = VisualTreeHelper.GetParent(parent);
            }

            if (parent == null) return;

            TextBox textBox = (TextBox)parent;

            if (textBox.IsKeyboardFocusWithin) return;

            // If the text box is not yet focussed, give it the focus and
            // stop further processing of this click event.
            textBox.Focus();
            e.Handled = true;
        }

        private static void SelectAllText(object sender, RoutedEventArgs e)
        {
            TextBox textBox = e.OriginalSource as TextBox;

            if (textBox != null) textBox.SelectAll();
        }

    }
}
