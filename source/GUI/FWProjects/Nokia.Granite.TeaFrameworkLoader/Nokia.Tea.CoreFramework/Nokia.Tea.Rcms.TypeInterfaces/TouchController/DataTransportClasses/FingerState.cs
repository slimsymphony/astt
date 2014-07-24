using System;
using System.Windows;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController.DataTransportClasses
{
    /// <summary>
    /// Finger state
    /// </summary>
    public class FingerState
    {
        private Vector coordinates;
        private Boolean fingerPressed = false;

        /// <summary>
        /// Initializes a new instance of the <see cref="FingerState"/> class.
        /// </summary>
        public FingerState() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="FingerState"/> class.
        /// </summary>
        /// <param name="coordinates">The coordinates.</param>
        /// <param name="fingerPressed">if set to <c>true</c> [finger pressed].</param>
        public FingerState(Vector coordinates, Boolean fingerPressed)
        {
            this.coordinates = coordinates;
            this.fingerPressed = fingerPressed;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="FingerState"/> class.
        /// </summary>
        /// <param name="fingerstate">The fingerstate.</param>
        public FingerState(FingerState fingerstate)
        {
            this.coordinates = fingerstate.Coordinates;
            this.fingerPressed = fingerstate.FingerPressed;
        }

        /// <summary>
        /// Gets or sets the coordinates.
        /// </summary>
        /// <value>
        /// The coordinates.
        /// </value>
        public Vector Coordinates
        {
            set { this.coordinates = value; }
            get { return coordinates; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether [finger pressed].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [finger pressed]; otherwise, <c>false</c>.
        /// </value>
        public Boolean FingerPressed
        {
            set { this.fingerPressed = value; }
            get { return fingerPressed; }
        }
    }
}
