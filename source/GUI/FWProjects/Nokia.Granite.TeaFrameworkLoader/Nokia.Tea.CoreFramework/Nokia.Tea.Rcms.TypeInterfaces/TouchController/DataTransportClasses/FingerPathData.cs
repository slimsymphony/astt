using System;
using System.Collections.Generic;
using System.Linq;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController.DataTransportClasses
{
    /// <summary>
    /// Finger path data
    /// </summary>
    public class FingerPathData
    {
        private List<FingerState> data = new List<FingerState>();
        private Boolean lastCommandHold = false;

        /// <summary>
        /// Initializes a new instance of the <see cref="FingerPathData"/> class.
        /// </summary>
        public FingerPathData() { }

        /// <summary>
        /// Gets or sets the data.
        /// </summary>
        /// <value>
        /// The data.
        /// </value>
        public List<FingerState> Data
        {
            set { data = value; }
            get { return data; }
        }

        /// <summary>
        /// Gets the last message.
        /// </summary>
        public FingerState LastMessage
        {
            get { return data.Last(); }
        }

        /// <summary>
        /// Gets the length.
        /// </summary>
        public Int32 Length
        {
            get { return data.Count(); }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is last command hold.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is last command hold; otherwise, <c>false</c>.
        /// </value>
        public Boolean IsLastCommandHold
        {
            set { lastCommandHold = value; }
            get { return lastCommandHold; }
        }
    }
}
