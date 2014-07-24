using System;
using System.Windows;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController
{
    /// <summary>
    /// Move parameter
    /// </summary>
    public class MoveParameter 
    {
        private Vector p1;
        private Vector p2;
        private Int32 lineSpeed;
        private Int32 fingerNumber;

        /// <summary>
        /// Initializes a new instance of the <see cref="MoveParameter"/> class.
        /// </summary>
        /// <param name="p1">The p1.</param>
        /// <param name="p2">The p2.</param>
        /// <param name="lineSpeed">The line speed.</param>
        /// <param name="fingerNumber">The finger number.</param>
        public MoveParameter(Vector p1, Vector p2, Int32 lineSpeed, Int32 fingerNumber)
        {
            this.p1 = p1;
            this.p2 = p2;
            this.lineSpeed = lineSpeed;
            this.fingerNumber = fingerNumber;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MoveParameter"/> class.
        /// </summary>
        /// <param name="x1">The x1.</param>
        /// <param name="y1">The y1.</param>
        /// <param name="x2">The x2.</param>
        /// <param name="y2">The y2.</param>
        /// <param name="lineSpeed">The line speed.</param>
        /// <param name="fingerNumber">The finger number.</param>
        public MoveParameter(Double x1, Double y1, Double x2, Double y2, Int32 lineSpeed, Int32 fingerNumber)
        {
            this.p1 = new Vector(x1, y1);
            this.p2 = new Vector(x2, y2);
            this.lineSpeed = lineSpeed;
            this.fingerNumber = fingerNumber;
        }

        /// <summary>
        /// Gets the p1.
        /// </summary>
        public Vector P1
        {
            get { return p1; }
        }

        /// <summary>
        /// Gets the p2.
        /// </summary>
        public Vector P2
        {
            get { return p2; }
        }

        /// <summary>
        /// Gets the line speed.
        /// </summary>
        public Int32 LineSpeed
        {
            get { return lineSpeed; }
        }

        /// <summary>
        /// Gets the finger number.
        /// </summary>
        public Int32 FingerNumber
        {
            get { return fingerNumber; }
        }
    }
}
