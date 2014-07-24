// -----------------------------------------------------------------------
// <copyright file="UcBase.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Views
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;

    /// <summary>
    /// Base class for UserControl. Contains command for closing the parent window of the UserControl.
    /// </summary>
    public class UcBase : UserControl
    {
        private static DependencyProperty ParentWindowProperty;

        /// <summary>
        /// Gets or sets the parent window of the UserControl.
        /// </summary>
        public Window ParentWindow
        {
            get { return (Window)GetValue(ParentWindowProperty); }
            set { SetValue(ParentWindowProperty, value); }
        }

        /// <summary>
        /// Initializes static members of the <see cref="UcBase"/> class.
        /// </summary>
        static UcBase()
        {
            FrameworkPropertyMetadata frameworkPropertyMetadata = new FrameworkPropertyMetadata();
            ParentWindowProperty = DependencyProperty.Register(
                "ParentWindow", typeof(Window), typeof(UcBase), frameworkPropertyMetadata, null);
        }

        /// <summary>
        /// Handler for Close command. Closes parent window.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The event arguments.</param>
        protected virtual void CloseCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            if (this.ParentWindow == null) return;

            this.ParentWindow.Content = null;
            this.ParentWindow.Close();
        }
    }
}
