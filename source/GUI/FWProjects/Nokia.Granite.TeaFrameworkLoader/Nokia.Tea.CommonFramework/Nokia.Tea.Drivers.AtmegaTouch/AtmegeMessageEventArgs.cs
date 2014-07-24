using System;

namespace Nokia.Tea.CommonFramework.Drivers
{
    class AtmegeMessageEventArgs : EventArgs
    {
        int message;

        public AtmegeMessageEventArgs(int message)
        {
            this.message = message;           
        }

        public int Message
        {
            get { return message; }
        }
    }
}

