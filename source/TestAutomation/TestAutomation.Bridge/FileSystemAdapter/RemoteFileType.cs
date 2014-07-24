using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// 
    /// </summary>
    public enum RemoteFileType
    {
        /// <summary>
        /// 
        /// </summary>
        File = 0,
        /// <summary>
        /// 
        /// </summary>
        Directory = 1,
        /// <summary>
        /// 
        /// </summary>
        DirectoryLink = 2,
        /// <summary>
        /// 
        /// </summary>
        Block = 3,
        /// <summary>
        /// 
        /// </summary>
        Character = 4,
        /// <summary>
        /// 
        /// </summary>
        Link = 5,
        /// <summary>
        /// 
        /// </summary>
        Socket = 6,
        /// <summary>
        /// 
        /// </summary>
        FIFO = 7,
        /// <summary>
        /// 
        /// </summary>
        Other = 8
    }
}
