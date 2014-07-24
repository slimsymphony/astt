// -----------------------------------------------------------------------
// <copyright file="BindableRun.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.CustomControls
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Documents;

    /// <summary>
    /// Allows data binding for Run element.
    /// </summary>
    public class BindableRun : Run
    {
        /// <summary>
        /// The bound text property.
        /// </summary>
        public static readonly DependencyProperty TextBindingProperty = DependencyProperty.Register(
            "TextBinding",
            typeof(string),
            typeof(BindableRun),
            new PropertyMetadata(new PropertyChangedCallback(BindableRun.onTextBindingChanged)));

        private static void onTextBindingChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((Run)d).Text = e.NewValue.ToString();
        }

        /// <summary>
        /// Gets or sets the text bound to Run element.
        /// </summary>
        public string TextBinding
        {
            get
            {
                return this.GetValue(TextBindingProperty).ToString();
            }
            set
            {
                this.SetValue(TextBindingProperty, value);
            }

        }
    }
}
