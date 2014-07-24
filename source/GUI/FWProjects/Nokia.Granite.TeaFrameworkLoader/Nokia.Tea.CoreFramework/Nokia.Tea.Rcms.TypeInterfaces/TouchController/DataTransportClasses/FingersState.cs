using System;
using System.Collections.Generic;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController.DataTransportClasses
{
    /// <summary>
    /// Finger state
    /// </summary>
    public class FingersState
    {
        /// <summary>
        /// State
        /// </summary>
        List<FingerState> state;

        /// <summary>
        /// Initializes a new instance of the <see cref="FingersState"/> class.
        /// </summary>
        /// <param name="numberOfFingers">The number of fingers.</param>
        public FingersState(Int32 numberOfFingers)
        {
            state = new List<FingerState>();

            for (Int32 i = 0; i < numberOfFingers; i++)
                state.Add(new FingerState());
        }

        /// <summary>
        /// Adds the finger.
        /// </summary>
        /// <param name="state">The state.</param>
        /// <param name="finger">The finger.</param>
        public void AddFinger(FingerState state, Int32 finger)
        {
            this.state[finger - 1] = state;
        }

        /// <summary>
        /// Gets the state of the finger.
        /// </summary>
        /// <param name="finger">The finger.</param>
        /// <returns></returns>
        public FingerState GetFingerState(Int32 finger)
        {
            return state[finger - 1];
        }

        /// <summary>
        /// Updates the state of the release.
        /// </summary>
        /// <param name="finger">The finger.</param>
        /// <param name="fingerPressed">if set to <c>true</c> [finger pressed].</param>
        public void UpdateReleaseState(Int32 finger, Boolean fingerPressed)
        {
            this.state[finger - 1].FingerPressed = fingerPressed;
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            String str = "";
            foreach (FingerState fs in state)
                str += String.Format("{0}/{1}\t", fs.Coordinates.X, fs.Coordinates.Y);
            
            return str;
        }
    }
}
