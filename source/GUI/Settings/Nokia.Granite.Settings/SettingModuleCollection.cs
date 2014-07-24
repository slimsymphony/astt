using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace TestAutomation.Gui.Marble.Settings
{
    /// <summary>
    /// Represents a thread-safe collection setting modules that can be accessed
    /// by multiple threads concurrently.
    /// </summary>
    [Serializable()]
    public class SettingModuleCollection : IEnumerable<SettingModule>, IEnumerable
    {
        /// <summary>
        /// A thread-safe collection of setting modules where we use the setting module name as
        /// the key to ensure we never allow setting modules to be added with the same name.
        /// </summary>
        private ConcurrentDictionary<string, SettingModule> _collection = null;

        /// <summary>
        /// Creates a new empty collection of setting modules.
        /// </summary>
        internal SettingModuleCollection()
        {
            // Create the concurrent dictionary
            _collection = new ConcurrentDictionary<string, SettingModule>();
        }

        /// <summary>
        /// Adds a setting module to the collection.
        /// </summary>
        /// <param name="module">Setting module.</param>
        /// <returns>Value of <c>true</c> if the setting module was added, otherwise <c>false</c> is returned.</returns>
        /// <remarks>The setting module will not be added if there is already a setting module in the collection that has the
        /// same setting module name.</remarks>
        internal bool Add(SettingModule module)
        {
            return _collection.TryAdd(module.Name, module);
        }

        /// <summary>
        /// Adds a range of setting modules to the collection.
        /// </summary>
        /// <param name="module">Setting module.</param>
        internal void AddRange(IEnumerable<SettingModule> modules)
        {
            foreach (var module in modules)
            {
                Add(module);
            }
        }

        /// <summary>
        /// Removes the setting module if it is in this collection.
        /// </summary>
        /// <param name="module">Setting module.</param>
        internal void Remove(SettingModule module)
        {
            SettingModule temp;
            _collection.TryRemove(module.Name, out temp);
        }

        /// <summary>
        /// Removes all setting modules that match a particular criteria.
        /// </summary>
        /// <param name="match">The criteria to match for the setting module to be removed.</param>
        internal void RemoveAll(Predicate<SettingModule> match)
        {
            foreach (SettingModule item in this)
            {
                if (match(item))
                {
                    Remove(item);
                }
            }
        }
        
        /// <summary>
        /// Removes all setting modules in the collection.
        /// </summary>
        internal void Clear()
        {
            _collection.Clear();
        }

        /// <summary>
        /// Determines whether any setting modules are in the collection that match a particular criteria.
        /// </summary>
        /// <param name="match">The criteria to match.</param>
        /// <returns>Value of <c>true</c> if there is at least one setting module in this collection that 
        /// matches the criteria, otherwise <c>false</c> is returned.</returns>
        public bool Exists(Predicate<SettingModule> match)
        {
            return Find(match) != null;
        }

        /// <summary>
        /// Finds a setting module that matches some criteria.
        /// </summary>
        /// <param name="match">Method that determines whether the setting module matches some criteria or not.</param>
        /// <returns>Setting module that matches the criteria or <c>null</c> if there is no setting that matches the criteria.</returns>
        public SettingModule Find(Predicate<SettingModule> match)
        {
            foreach (SettingModule item in this)
            {
                if (match(item))
                {
                    return item;
                }
            }

            return null;
        }

        /// <summary>
        /// Find all setting modules that match some criteria.
        /// </summary>
        /// <param name="match">Method that determines whether the setting modules match some criteria or not.</param>
        /// <returns>Read-only collection of setting modules that match the criteria.</returns>
        public ReadOnlyCollection<SettingModule> FindAll(Predicate<SettingModule> match)
        {
            var items = new List<SettingModule>();

            foreach (SettingModule item in this)
            {
                if (match(item))
                {
                    items.Add(item);
                }
            }

            return new ReadOnlyCollection<SettingModule>(items);
        }

        /// <summary>
        /// Returns an enumerator that iterates through the setting modules.
        /// </summary>
        /// <returns>Enumerator interface.</returns>
        public IEnumerator GetEnumerator()
        {
            return _collection.Values.ToList().GetEnumerator();
        }

        /// <summary>
        /// Gets the number of setting modules in the collection.
        /// </summary>
        public int Count
        {
            get
            {
                return _collection.Count;
            }
        }

        /// <summary>
        /// Determines whether the collection contains a specific setting module.
        /// </summary>
        /// <param name="module">Setting module.</param>
        /// <returns>Value of <c>true</c> if the setting module is found in the collection, otherwise
        /// <c>false</c> is returned.</returns>
        public bool Contains(SettingModule module)
        {
            return _collection.Values.Contains(module);
        }

        /// <summary>
        /// Retrieves the index of the setting module.
        /// </summary>
        /// <param name="module">Setting module.</param>
        /// <returns>Index of the setting if it was found, otherwise -1 is returned.</returns>
        public int IndexOf(SettingModule module)
        {
            int i = 0;

            foreach (var item in this)
            {
                if (module.Equals(item))
                {
                    return i;
                }
                i++;
            }

            return -1;
        }

        /// <summary>
        /// Gets the setting module at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the setting module to get.</param>
        /// <returns>Setting module at the specified index.</returns>
        public SettingModule this[int index]
        {
            get
            {
                return _collection.Values.ToArray()[index];
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        IEnumerator<SettingModule> IEnumerable<SettingModule>.GetEnumerator()
        {
            return (IEnumerator<SettingModule>)GetEnumerator();
        }
    }
}
