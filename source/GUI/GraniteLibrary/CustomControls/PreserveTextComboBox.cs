using System.Windows.Controls;

namespace MarbleLibrary.CustomControls
{
    /// <summary>
    /// The PreserveTextComboBox behaves like a standard <see cref="System.Windows.Controls.ComboBox"/> 
    /// except that it preserves the <see cref="System.Windows.Controls.ComboBox.Text"/> property that the
    /// user selected.
    /// </summary>
    /// <remarks><para>With a standard <see cref="System.Windows.Controls.ComboBox"/> if the user selects 
    /// an item and then the items are dynamically updated and the item that the user selected is removed 
    /// from the list, the <see cref="System.Windows.Controls.ComboBox.Text"/> property is automatically
    /// cleared, even if the <see cref="IsEditable"/> property set to <c>true</c>.</para>
    /// <para>This class instead preserves the users' original selection in the 
    /// <see cref="System.Windows.Controls.ComboBox.Text"/> property if the 
    /// <see cref="System.Windows.Controls.ComboBox.IsEditable"/> property is set to <c>true</c>.</para>
    /// </remarks>
    public class PreserveTextComboBox : ComboBox
    {
        /// <summary>
        /// Responds to a <see cref="System.Windows.Controls.ComboBox"/> selection change by raising
        /// a <see cref="System.Windows.Controls.Primitives.Selector.SelectionChanged"/> event.
        /// </summary>
        /// <param name="e">Provides data for <see cref="System.Windows.Controls.SelectionChangedEventArgs"/>.</param>
        /// <remarks>If the <see cref="IsEditable"/> property is set to <c>true</c> this method shall prevent the
        /// <see cref="Text"/> property from being cleared even if the item in the <see cref="Text"/> has been
        /// removed from the list of items.</remarks>
        protected override void OnSelectionChanged(SelectionChangedEventArgs e)
        {
            if (!IsEditable || (e.AddedItems.Count > 0))
            {
                base.OnSelectionChanged(e);
            }
            e.Handled = true;
        }
    }
}
