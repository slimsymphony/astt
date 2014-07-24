using System.Collections.Generic;
using System.Windows;

namespace Nokia.Tea.CommonFramework.Rcms.TouchControllerCY
{
    internal class FingerState
    {
        private Vector coordinates;
        private bool fingerPressed;
        private bool toggle;

        public FingerState()
        {
            this.fingerPressed = false;
            this.toggle = false;
        }

        public FingerState(FingerState fingerstate)
        {
            this.fingerPressed = false;
            this.toggle = false;
            this.coordinates = fingerstate.Coordinates;
            this.fingerPressed = fingerstate.FingerPressed;
        }

        public FingerState(Vector coordinates, bool fingerPressed)
        {
            this.fingerPressed = false;
            this.toggle = false;
            this.coordinates = coordinates;
            this.fingerPressed = fingerPressed;
        }

        public Vector Coordinates
        {
            get
            {
                return this.coordinates;
            }
            set
            {
                this.coordinates = value;
            }
        }

        public bool FingerPressed
        {
            get
            {
                return this.fingerPressed;
            }
            set
            {
                this.fingerPressed = value;
            }
        }

        public bool Toggle
        {
            get
            {
                return this.toggle;
            }
            set
            {
                this.toggle = value;
            }
        }
    }

    internal class CyFingersState
    {
        private List<FingerState> state = new List<FingerState>();

        public CyFingersState(int numberOfFingers)
        {
            for (int i = 0; i < numberOfFingers; i++)
            {
                this.state.Add(new FingerState());
            }
        }

        public void AddFinger(FingerState state, int finger)
        {
            this.state[finger - 1] = state;
        }

        public FingerState GetFingerState(int finger)
        {
            return this.state[finger - 1];
        }
    }
}

