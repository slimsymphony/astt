// -----------------------------------------------------------------------
// <copyright file="MessageListener.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Text;
    using System.Windows;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class MessageListener : DependencyObject
    {
        /// <summary>
        /// Gets or sets a received message.
        /// </summary>
        public string Message
        {
            get { return (string)GetValue(MessageProperty); }
            set { SetValue(MessageProperty, value); }
        }

        private static MessageListener mInstance;

        /// <summary>
        /// Prevents a default instance of the <see cref="MessageListener"/> class from being created.
        /// </summary>
        private MessageListener()
        {
        }

        /// <summary>
        /// Get MessageListener instance
        /// </summary>
        public static MessageListener Instance { get { return mInstance ?? (mInstance = new MessageListener()); } }

        /// <summary>
        /// </summary>
        /// <param name="message">
        /// The message.
        /// </param>
        public void ReceiveMessage(string message)
        {
            this.Message = message;
            Debug.WriteLine(this.Message);
            DispatcherHelper.DoEvents();
        }

        public static readonly DependencyProperty MessageProperty = DependencyProperty.Register("Message", typeof(string), typeof(MessageListener), new UIPropertyMetadata(null));
    }
}
