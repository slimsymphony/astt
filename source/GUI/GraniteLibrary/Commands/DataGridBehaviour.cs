namespace MarbleLibrary.Commands
{
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;

    /// <summary>
    /// Routes DataGrid events to commands. Only for routed events.
    /// </summary>
    public static class DataGridBehaviour
    {
        #region DataGridDoubleClick

        public static readonly DependencyProperty DataGridMouseDoubleClickCommand =
            RoutedEventBehaviourFactory.CreateCommandExecutionEventBehaviour(DataGrid.MouseDoubleClickEvent, "DataGridMouseDoubleClickCommand", typeof(DataGridBehaviour)); 

        public static void SetDataGridMouseDoubleClickCommand(DependencyObject o, ICommand value)
        {
            if (o != null)
            {
                o.SetValue(DataGridMouseDoubleClickCommand, value);
            }
        }

        public static ICommand GetDataGridMouseDoubleClickCommand(DependencyObject o)
        {
            return o == null ? null : o.GetValue(DataGridMouseDoubleClickCommand) as ICommand;
        }

        #endregion

        #region DataGridSelectionChanged

        public static readonly DependencyProperty DataGridSelectionChangedCommand =
            RoutedEventBehaviourFactory.CreateCommandExecutionEventBehaviour(DataGrid.SelectionChangedEvent, "DataGridSelectionChangedCommand", typeof(DataGridBehaviour));

        public static void SetDataGridSelectionChangedCommand(DependencyObject o, ICommand value)
        {
            if (o != null)
                o.SetValue(DataGridSelectionChangedCommand, value);
        }

        public static ICommand GetDataGridSelectionChangedCommand(DependencyObject o)
        {
            return o == null ? null : o.GetValue(DataGridSelectionChangedCommand) as ICommand;
        }

        public static readonly DependencyProperty DataGridSelectionChangedCommandParameter =
            RoutedEventBehaviourFactory.CreateCommandParameter(DataGridSelectionChangedCommand);

        public static void SetDataGridSelectionChangedCommandParameter (DependencyObject o, object value)
        {
            if (o != null)
                o.SetValue(DataGridSelectionChangedCommandParameter, value);
        }

        public static object GetDataGridSelectionChangedCommandCommandParameter(DependencyObject o)
        {
            if (o != null)
                return o.GetValue(DataGridSelectionChangedCommandParameter);
            
            return null;
        }

        #endregion

        #region DataGridDrop

        public static readonly DependencyProperty DataGridDropCommand =
            RoutedEventBehaviourFactory.CreateCommandExecutionEventBehaviour(DataGrid.DropEvent, "DataGridDropCommand", typeof(DataGridBehaviour));

        public static void SetDataGridDropCommand(DependencyObject o, ICommand value)
        {
            if (o != null)
                o.SetValue(DataGridDropCommand, value);
        }

        public static ICommand GetDataGridDropCommand(DependencyObject o)
        {
            return o == null ? null : o.GetValue(DataGridDropCommand) as ICommand;
        }

        #endregion
    }
}
