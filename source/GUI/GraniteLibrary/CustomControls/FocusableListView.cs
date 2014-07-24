namespace MarbleLibrary.CustomControls
{
    using System.Windows.Controls;

    public class FocusableListView : ListView
    {
        /// <summary>
        /// Determines whether an object is a <see cref="T:System.Windows.Controls.ListViewItem"/>.
        /// </summary>
        /// <param name="item">The object to evaluate.</param>
        /// <returns>True if the <paramref name="item"/> is a <see cref="T:System.Windows.Controls.ListViewItem"/>; otherwise, false.</returns>
        protected override bool IsItemItsOwnContainerOverride(object item)
        {
            return (item is FocusableListViewItem);
        }

        /// <summary>
        /// Creates and returns a new <see cref="T:System.Windows.Controls.ListViewItem"/> container.
        /// </summary>
        /// <returns>A new <see cref="T:System.Windows.Controls.ListViewItem"/> control.</returns>
        protected override System.Windows.DependencyObject GetContainerForItemOverride()
        {
            return new FocusableListViewItem();
        }
    }
}
