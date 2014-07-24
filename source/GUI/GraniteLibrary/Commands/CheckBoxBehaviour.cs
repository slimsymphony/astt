namespace MarbleLibrary.Commands
{
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;

    /// <summary>
    /// Routes CheckBox events to commands.
    /// </summary>
    public static class CheckBoxBehaviour
    {
        public static readonly DependencyProperty CheckBoxCheckCommand = RoutedEventBehaviourFactory.CreateCommandExecutionEventBehaviour(CheckBox.CheckedEvent, "CheckBoxCheckCommand", typeof(CheckBoxBehaviour));

        public static void SetCheckBoxCheckCommand(DependencyObject o, ICommand value)
        {
            if (o == null)
                return;

            o.SetValue(CheckBoxCheckCommand, value);
        }

        public static ICommand GetCheckBoxCheckCommand(DependencyObject o)
        {
            if (o == null)
                return null;

            return o.GetValue(CheckBoxCheckCommand) as ICommand;
        }

        public static readonly DependencyProperty CheckBoxUnCheckCommand = RoutedEventBehaviourFactory.CreateCommandExecutionEventBehaviour(CheckBox.UncheckedEvent, "CheckBoxUnCheckCommand", typeof(CheckBoxBehaviour));

        public static void SetCheckBoxUnCheckCommand(DependencyObject o, ICommand value)
        {
            if (o == null)
                return;

            o.SetValue(CheckBoxUnCheckCommand, value);
        }

        public static ICommand GetCheckBoxUnCheckCommand(DependencyObject o)
        {
            if (o == null)
                return null;

            return o.GetValue(CheckBoxUnCheckCommand) as ICommand;
        }
    }
}
