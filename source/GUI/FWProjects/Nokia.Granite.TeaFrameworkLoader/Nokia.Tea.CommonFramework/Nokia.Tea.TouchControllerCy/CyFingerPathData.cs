using System.Collections.Generic;
using System.Linq;

namespace Nokia.Tea.CommonFramework.Rcms.TouchControllerCY
{
    internal class CyFingerPathData
    {
        private List<FingerState> data = new List<FingerState>();
        private bool lastCommandHold;

        public List<FingerState> Data
        {
            get
            {
                return this.data;
            }
            set
            {
                this.data = value;
            }
        }

        public bool IsLastCommandHold
        {
            get
            {
                return this.lastCommandHold;
            }
            set
            {
                this.lastCommandHold = value;
            }
        }

        public FingerState LastMessage
        {
            get
            {
                return this.data.Last<FingerState>();
            }
        }

        public int Length
        {
            get
            {
                return this.data.Count<FingerState>();
            }
        }
    }
}

