namespace MarbleLibrary.Utilities
{
    using System.Windows;

    /// <summary>
    /// Binding proxy class is used for creating static resources which use binding proxy to enable binding to controls which are not part of the visual tree.
    /// </summary>
    public class BindingProxy : Freezable
    {
        /// <summary>
        /// Using a DependencyProperty as the backing store for Data.  This enables animation, styling, binding, etc...
        /// </summary>
        public static readonly DependencyProperty DataProperty = DependencyProperty.Register("Data", typeof(object), typeof(BindingProxy), new UIPropertyMetadata(null));

        /// <summary>
        /// Gets or sets data object.
        /// </summary>
        public object Data
        {
            get { return (object)GetValue(DataProperty); }
            set { SetValue(DataProperty, value); }
        }

        #region Overrides of Freezable

        /// <summary>
        /// Overrides CreateInstaceCore().
        /// </summary>
        /// <returns>New BindingProxy object.</returns>
        protected override Freezable CreateInstanceCore()
        {
            return new BindingProxy();
        }

        #endregion
    }
}
