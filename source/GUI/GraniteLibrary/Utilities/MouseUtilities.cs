using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MarbleLibrary.Utilities
{
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;
    using System.Windows.Interactivity;

    /// <summary>
    /// Captures and eats MouseWheel events so that a nested ListBox does not
    /// prevent an outer scrollable control from scrolling.
    /// </summary>
    public sealed class IgnoreMouseWheelBehavior : Behavior<UIElement>
    {
        protected override void OnAttached()
        {
            base.OnAttached();
            AssociatedObject.PreviewMouseWheel += AssociatedObject_PreviewMouseWheel;
        }

        protected override void OnDetaching()
        {
            AssociatedObject.PreviewMouseWheel -= AssociatedObject_PreviewMouseWheel;
            base.OnDetaching();
        }

        void AssociatedObject_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
        {
            e.Handled = true;

            ////ItemsControl itemsControl = sender as ItemsControl;

            ////if (itemsControl != null)
            ////{
            ////    ScrollViewer scrollViewer = GuiUtilities.FindVisualChild<ScrollViewer>(itemsControl);

            ////    if (scrollViewer != null)
            ////    {
            ////        if (e.Delta > 0)
            ////            scrollViewer.PageUp();
            ////        else
            ////            scrollViewer.PageDown();
            ////    }
            ////}

            var newEventArgs = new MouseWheelEventArgs(e.MouseDevice, e.Timestamp, e.Delta);
            newEventArgs.RoutedEvent = UIElement.MouseWheelEvent;

            AssociatedObject.RaiseEvent(newEventArgs);
        }
    }
}
