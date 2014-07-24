namespace MarbleLibrary.Commands
{
    using System.ComponentModel;
    using System.Windows;
    using System.Windows.Input;

    /// <summary>
    /// Routes the windows closing event through to a command.
    /// </summary>
    /// <example>
    /// To use this class in the view in order to bind the window closing 
    /// event to a command, update the XAML for the window as follows:
    /// <code>
    /// &lt;Window x:Class="MainWindow"
    ///     ...
    ///     xmlns:command="clr-namespace:MarbleLibrary.Commands;assembly=MarbleLibrary"
    ///     command:WindowClosingBehaviour.Closing="{Binding MainWindowClosingCommand}"     
    ///     ... &gt;
    ///     ...
    /// &lt;/Window&gt;
    /// </code>
    /// </example>
    public class WindowClosingBehaviour
    {
        /// <summary>
        /// Gets the command to call when the window is closing.
        /// </summary>
        /// <param name="dependencyObject">Window with the closing event.</param>
        /// <returns>The command to call when the window is closing.</returns>
        public static ICommand GetClosing(DependencyObject dependencyObject)
        {
            return (ICommand)dependencyObject.GetValue(ClosingProperty);
        }

        /// <summary>
        /// Sets the command to call when the window is closing.
        /// </summary>
        /// <param name="dependencyObject">Window with the closing event.</param>
        /// <param name="value">The command to call when the window is closing.</param>
        public static void SetClosing(DependencyObject dependencyObject, ICommand value)
        {
            dependencyObject.SetValue(ClosingProperty, value);
        }

        /// <summary>
        /// Property that registers the closing event with the method to call.
        /// </summary>
        public static readonly DependencyProperty ClosingProperty = DependencyProperty.RegisterAttached(
            "Closing", typeof(ICommand), typeof(WindowClosingBehaviour),
            new UIPropertyMetadata(ClosingChanged));

        /// <summary>
        /// Called when hooking or unhooking the closing event.
        /// </summary>
        /// <param name="target">Window with the closing event to be hooked up.</param>
        /// <param name="e">Event arguments.</param>
        private static void ClosingChanged(DependencyObject target, DependencyPropertyChangedEventArgs e)
        {
            Window window = target as Window;

            // If the target is a window
            if (window != null)
            {
                if (e.NewValue != null)
                {
                    // Hook up the closing event
                    window.Closing += WindowClosing;
                }
                else
                {
                    // Unhook the closing event
                    window.Closing -= WindowClosing;
                }
            }
        }

        /// <summary>
        /// Called when the window is closing.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        static void WindowClosing(object sender, CancelEventArgs e)
        {
            ICommand closing = GetClosing(sender as Window);
            if (closing != null)
            {
                // If we can execute the closing command
                if (closing.CanExecute(null))
                {
                    // Execute the closing command
                    closing.Execute(null);
                }

                // Else we cannot execute the closing command
                else
                {
                    // Cancel the closing command
                    e.Cancel = true;
                }
            }
        }
    }
}
