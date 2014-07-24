namespace MarbleLibrary.CustomControls
{
    using System.Windows;
    using System.Windows.Controls;

    public class FocusableListViewItem : ListViewItem
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FocusableListViewItem"/> class.
        /// </summary>
        public FocusableListViewItem()
        {
            this.GotFocus += new RoutedEventHandler(this.FocusableListViewItem_GotFocus);
        }

        private void FocusableListViewItem_GotFocus(object sender, RoutedEventArgs e)
        {
            object obj = this.ParentListView.ItemContainerGenerator.ItemFromContainer(this);
            this.ParentListView.SelectedItem = obj;
        }

        private ListView ParentListView { get { return (ItemsControl.ItemsControlFromItemContainer(this) as ListView); } }
    }
}
