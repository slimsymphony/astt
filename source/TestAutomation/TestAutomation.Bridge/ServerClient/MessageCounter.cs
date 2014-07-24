using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Class for keeping track of the transsction IDs of the messages being sent
    /// </summary>
    public class MessageCounter
    {
        private static ushort m_currentId = 1;

        /// <summary>
        /// Gets the next Transaction ID
        /// </summary>
        /// <returns></returns>
        internal static ushort GetNextTransactionId()
        {
            ushort id = m_currentId;
            m_currentId++;

            //0 is reserved for event messages
            if (m_currentId == 0)
            {
                m_currentId++;
            }
            return id;
        }
    }
}
