using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAutomation.Bridge
{
    /// <summary>
    /// Handler delegate for an occured crashdump
    /// </summary>
    /// <param name="crashdump">The crashdump</param>
    public delegate void CrashDumpHandler(CrashdumpInfo crashdump);

    /// <summary>
    /// Source from which the crashdump was found
    /// </summary>
    public enum CrashdumpSource
    {
        /// <summary>
        /// Found under anr directory
        /// </summary>
        Anr,
        
        /// <summary>
        /// Found under  dropbox directory
        /// </summary>
        Dropbox,
        
        /// <summary>
        /// Found under tombstone directory
        /// </summary>
        Tombstone,
        
        /// <summary>
        /// Other crashsump source
        /// </summary>
        Other
    }

    /// <summary>
    /// Crashdump info container
    /// </summary>
    public sealed class CrashdumpInfo
    {
        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="name">Name of the crashdump</param>
        /// <param name="creationTime">Remote creation time of the crashdump</param>
        /// <param name="source">Source of the crashdump</param>
        public CrashdumpInfo(string name, DateTime creationTime, CrashdumpSource source)
        {
            Name = name;
            CreationTime = creationTime;
            Source = source;
        }

        /// <summary>
        /// Gets the remote creation time of the crashdump file
        /// </summary>
        public DateTime CreationTime { get; private set; }
        
        /// <summary>
        /// Gets the source of the crashdump file
        /// </summary>
        public CrashdumpSource Source { get; private set; }
               
        /// <summary>
        /// Gets the name of the crashdump file
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// Gets the name of the test case during which the crashsump was generated
        /// </summary>
        public string FoundInTestCase { get; set; }

        /// <summary>
        /// Gets the absolute location of the crashdump file in local file system
        /// </summary>
        public string Location { get; set; }
    }

    /// <summary>
    /// Observable crashdump info collection
    /// </summary>
    public sealed class CrashdumpInfoCollection : ObservableCollection<CrashdumpInfo>
    { }
}
