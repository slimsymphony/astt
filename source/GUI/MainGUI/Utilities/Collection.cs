namespace Marble.Utilities
{
    using System.Collections.Generic;
    using System.Linq;
    using System.Collections.ObjectModel;
    using System.ComponentModel;
    using System.Collections.Specialized;
    using System.Windows.Threading;

    using Marble.Model;

    /// <summary>
    /// Represents a dynamic data collection that provides notifications when items get added,
    /// removed, or when the whole list is refreshed. Supports also RemoveRange, InsertRange and Sort functions.
    /// </summary>
    /// <typeparam name="T">The type of elements in the collection</typeparam>
    public class ObservableCollectionAdv<T> : ObservableCollection<T>
    {
        // CollectionChanged event is overridden so it can be accessed.
        public override event System.Collections.Specialized.NotifyCollectionChangedEventHandler CollectionChanged;

        // Suppresses notifications when true.
        private bool suppressNotification = false;

        // Allows data collection to be changed from other threads than the GUI thread.
        protected override void OnCollectionChanged(System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (suppressNotification) return;

            using (this.BlockReentrancy())
            {
                NotifyCollectionChangedEventHandler eventHandler = this.CollectionChanged;

                if (eventHandler == null) return;
                
                foreach (NotifyCollectionChangedEventHandler handler in eventHandler.GetInvocationList())
                {
                    DispatcherObject dispatcherObject = handler.Target as DispatcherObject;

                    // If the subscriber is a DispatcherObject and is using different thread.
                    if (dispatcherObject != null && dispatcherObject.CheckAccess() == false)
                    {
                        // Handler is invoked using dispatcher.
                        dispatcherObject.Dispatcher.Invoke(DispatcherPriority.DataBind, handler, this, e);
                    }
                    // Normal OnCollectionChanged behavior.
                    else 
                        handler(this, e);
                }
            }
        }

        public void SuppressNotifications()
        {
            this.suppressNotification = true;
        }

        public void ResumeNotifications()
        {
            this.suppressNotification = false;
            //this.OnReset();

            this.OnPropertyChanged("Count");
            this.OnPropertyChanged("Item[]");
            this.OnCollectionChanged(new NotifyCollectionChangedEventArgs(
                NotifyCollectionChangedAction.Add));
        }

        /// <summary>
        /// Initializes a new instance of the ObservableCollectionAdv<T> class.
        /// </summary>
        public ObservableCollectionAdv() { }

        /// <summary>
        /// Initializes a new instance of the ObservableCollectionAdv<T> class, 
        /// that contains elements copied from the specified collection.
        /// </summary>
        /// <param name="collection">The collection from which the elements are copied.</param>
        public ObservableCollectionAdv(IEnumerable<T> collection)
        {
            this.CheckReentrancy();
            var items = this.Items as List<T>;
            items.InsertRange(0, collection);
            this.OnReset();
        }

        /// <summary>
        /// Removes number of items from collection starting from specified index.
        /// </summary>
        /// <param name="index">starting index</param>
        /// <param name="count">item count</param>
        public void RemoveRange(int index, int count)
        {
            this.CheckReentrancy();
            var items = this.Items as List<T>;
            items.RemoveRange(index, count);
            this.OnReset();
        }

        /// <summary>
        /// Removes given items from the collection.
        /// </summary>
        /// <param name="collection">Items to remove</param>
        public void RemoveRange(IEnumerable<T> collection)
        {
            this.CheckReentrancy();
            var items = this.Items as List<T>;
            foreach (T removable in collection)
                items.Remove(removable);
            this.OnReset();   
        }

        /////// <summary>
        /////// Removes given items from the collection and nulls them.
        /////// </summary>
        /////// <param name="collection">Items to remove</param>
        ////public void RemoveRangeAndNullItems(IEnumerable<T> collection)
        ////{
        ////    this.CheckReentrancy();
        ////    var items = this.Items as List<T>;
            
        ////    foreach (T removable in collection)
        ////        items.Remove(removable);

        ////    for (int i = 0; i < collection.Count(); i++)
        ////    {
        ////        collection[i] = null;
        ////    }

        ////    this.OnReset();
        ////}

        /// <summary>
        /// Inserts items to collection starting from specified index.
        /// </summary>
        /// <param name="index">starting index</param>
        /// <param name="collection">list or collection to be inserted</param>
        public void InsertRange(int index, IEnumerable<T> collection)
        {
            this.CheckReentrancy();
            var items = this.Items as List<T>;
            items.InsertRange(index, collection);
            this.OnReset();
        }

        /// <summary>
        /// Indicates whether the collection is null or empty.
        /// </summary>
        /// <returns>Returns true if null or empty.</returns>
        public bool IsNullOrEmpty()
        {
            var items = this.Items as List<T>;
            if (items == null || items.Count == 0)
                return true;

            return false;
        }

        /// <summary>
        /// Sorts the TestCase collection based on specified field. (Only for TestCase collection)
        /// </summary>
        /// <param name="sortBy">field name to sort by</param>
        /// <param name="direction">sorting direction</param>
        public void SortTestset(string sortBy, ListSortDirection direction)
        {
            this.CheckReentrancy();
            var items = this.Items as List<TestCase>;
            List<TestCase> itemsTemp = new List<TestCase>();

            if (direction == ListSortDirection.Ascending)
            {
                switch (sortBy.ToLower())
                {
                    case "subarea":
                        // Place the ordered items in a temp list.
                        itemsTemp = items.OrderBy(item => item.Subarea).ThenBy(item => item.Feature).ThenBy(item => item.Name).ToList();
                        // Empty the list
                        items.RemoveRange(0, items.Count);
                        // Insert the sorted list.
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "feature":
                        itemsTemp = items.OrderBy(item => item.Feature).ThenBy(item => item.Name).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "test case":
                        itemsTemp = items.OrderBy(item => item.Name).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "result":
                        itemsTemp = items.OrderBy(item => item.Result.Result).ThenBy(item => item.Name).ThenBy(item => item.Feature).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "error reason":
                        itemsTemp = items.OrderBy(item => item.Result.ErrorReason).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "run time":
                        itemsTemp = items.OrderBy(item => item.Result.RunTime).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                }
            }
            else if (direction == ListSortDirection.Descending)
            {
                switch (sortBy.ToLower())
                {
                    case "subarea":
                        // Place the ordered items in a temp list.
                        itemsTemp = items.OrderByDescending(item => item.Subarea).ThenByDescending(item => item.Feature).ThenByDescending(item => item.Name).ToList();
                        // Empty the list
                        items.RemoveRange(0, items.Count);
                        // Insert the sorted list.
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "feature":
                        itemsTemp = items.OrderByDescending(item => item.Feature).ThenByDescending(item => item.Name).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "test case":
                        itemsTemp = items.OrderByDescending(item => item.Name).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "result":
                        itemsTemp = items.OrderByDescending(item => item.Result.Result).ThenByDescending(item => item.Name).ThenByDescending(item => item.Feature).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "error reason":
                        itemsTemp = items.OrderByDescending(item => item.Result.ErrorReason).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                    case "run time":
                        itemsTemp = items.OrderByDescending(item => item.Result.RunTime).ToList();
                        items.RemoveRange(0, items.Count);
                        items.InsertRange(0, itemsTemp);
                        break;
                }
            }
            this.OnReset();
        }

        private void OnReset()
        {
            this.OnPropertyChanged("Count");
            this.OnPropertyChanged("Item[]");
            this.OnCollectionChanged(new NotifyCollectionChangedEventArgs(
                NotifyCollectionChangedAction.Reset));
        }

        private void OnPropertyChanged(string propertyName)
        {
            this.OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }
	}
}
