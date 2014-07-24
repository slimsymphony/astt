using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MarbleLibrary.CustomControls
{
    using System.Collections;
    using System.Collections.ObjectModel;
    using System.Collections.Specialized;
    using System.Windows;
    using System.Windows.Controls;

    public class ListViewExtensions : DependencyObject
    {
        public static readonly DependencyProperty AutoScrollToEndProperty = DependencyProperty.RegisterAttached("AutoScrollToEnd", typeof(bool), typeof(ListViewExtensions), new UIPropertyMetadata(default(bool), OnAutoScrollToEndChanged));

        /// <summary>
        /// Returns the value of the AutoScrollToEndProperty
        /// </summary>
        /// <param name="obj">The dependency-object whichs value should be returned</param>
        /// <returns>The value of the given property</returns>
        public static bool GetAutoScrollToEnd(DependencyObject obj)
        {
            return (bool)obj.GetValue(AutoScrollToEndProperty);
        }

        /// <summary>
        /// Sets the value of the AutoScrollToEndProperty
        /// </summary>
        /// <param name="obj">The dependency-object whichs value should be set</param>
        /// <param name="value">The value which should be assigned to the AutoScrollToEndProperty</param>
        public static void SetAutoScrollToEnd(DependencyObject obj, bool value)
        {
            obj.SetValue(AutoScrollToEndProperty, value);
        }

        /// <summary>
        /// This method will be called when the AutoScrollToEnd
        /// property was changed
        /// </summary>
        /// <param name="s">The sender (the ListView)</param>
        /// <param name="e">Some additional information</param>
        public static void OnAutoScrollToEndChanged(DependencyObject s, DependencyPropertyChangedEventArgs e)
        {
            ListView listView = s as ListView;

            if (listView == null || listView.Items == null) return;

            var listViewItems = listView.Items;
            INotifyCollectionChanged data = listViewItems.SourceCollection as INotifyCollectionChanged;

            var scrollToEndHandler = new System.Collections.Specialized.NotifyCollectionChangedEventHandler(
                (s1, e1) =>
                {
                    if (listView.Items.Count > 0)
                    {
                        object lastItem = listView.Items[listView.Items.Count - 1];
                        listViewItems.MoveCurrentTo(lastItem);
                        listView.ScrollIntoView(lastItem);
                    }
                });

            if ((bool)e.NewValue)
            {
                data.CollectionChanged += scrollToEndHandler;
            }
            else
            {
                data.CollectionChanged -= scrollToEndHandler;
            }

            ////// Same as 
            ////// App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries.CollectionChanged += MarbleLogEntriesOnCollectionChanged;
            ////// however this approach prevents memory leaks.
            ////if (App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries != null)
            ////{
            ////    WeakEventManager<ObservableCollectionAdv<MarbleLogEntry>, NotifyCollectionChangedEventArgs>.RemoveHandler(
            ////        App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "CollectionChanged", MarbleLogEntriesOnCollectionChanged);
            ////}

            ////WeakEventManager<ObservableCollectionAdv<MarbleLogEntry>, NotifyCollectionChangedEventArgs>.AddHandler(
            ////    App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "CollectionChanged", MarbleLogEntriesOnCollectionChanged);


            ////WeakEventManager<ItemCollection, NotifyCollectionChangedEventArgs>.RemoveHandler(data, "CollectionChanged", scrollToEndHandler);
        }
    }
}
