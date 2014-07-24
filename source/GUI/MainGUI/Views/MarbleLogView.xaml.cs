using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Marble.Views
{
    using System.Collections;
    using System.Collections.Specialized;
    using System.ComponentModel;
    using System.IO;
    using System.Timers;
    using System.Windows.Media.Animation;
    using System.Windows.Threading;

    using Marble.Model;
    using Marble.Utilities;

    using MarbleLibrary.Commands;
    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for VideoPlayerView.xaml
    /// </summary>
    public partial class MarbleLogView : UcBase, INotifyPropertyChanged
    {
        /// <summary>
        /// Gets or sets whether the auto scrolling is currently enabled.
        /// </summary>
        public bool IsAutoScrollEnabled { get; set; }

        private bool isResizing { get; set; }

        /// <summary>
        /// Dispatcher timer which is used to slow down size changed events.
        /// </summary>
        private DispatcherTimer resizeTimer; 

        /// <summary>
        /// Initializes a new instance of the <see cref="MarbleLogView"/> class.
        /// </summary>
        public MarbleLogView()
        {
            InitializeComponent();

            this.ListViewMarbleLog.ItemsSource = App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries;
            this.IsAutoScrollEnabled = true;

            // Same as 
            // App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries.CollectionChanged += MarbleLogEntriesOnCollectionChanged;
            // however this approach prevents memory leaks.
            if (App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries != null)
            {
                WeakEventManager<FastObservableCollection<MarbleLogEntry>, NotifyCollectionChangedEventArgs>.RemoveHandler(
                    App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "CollectionChanged", MarbleLogEntriesOnCollectionChanged);
            }

            WeakEventManager<FastObservableCollection<MarbleLogEntry>, NotifyCollectionChangedEventArgs>.AddHandler(
                App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "CollectionChanged", MarbleLogEntriesOnCollectionChanged);

            ////// Same as 
            ////// App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries.CollectionChanged += MarbleLogEntriesOnCollectionChanged;
            ////// however this approach prevents memory leaks.
            ////if (App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries != null)
            ////{
            ////    WeakEventManager<BindingList<MarbleLogEntry>, ListChangedEventArgs>.RemoveHandler(
            ////        App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "ListChanged", MarbleLogEntries_ListChanged);
            ////}

            ////WeakEventManager<BindingList<MarbleLogEntry>, ListChangedEventArgs>.AddHandler(
            ////    App.ViewModel.MarbleConnector.MarbleLogModel.MarbleLogEntries, "ListChanged", MarbleLogEntries_ListChanged);

            this.Loaded += this.MarbleLogView_Loaded;
            this.Unloaded += this.MarbleLogView_Unloaded;

        }

        private void MarbleLogEntries_ListChanged(object sender, ListChangedEventArgs e)
        {
            ////this.performAutocroll();

            this.Dispatcher.BeginInvoke(new Action(this.performAutocroll));
        }

        private void MarbleLogEntriesOnCollectionChanged(object sender, NotifyCollectionChangedEventArgs notifyCollectionChangedEventArgs)
        {
            this.performAutocroll();
            //ListViewItem lvi = new ListViewItem();
            
        }

        /// <summary>
        /// Performs autoscroll if autoscroll is enabled.
        /// </summary>
        private void performAutocroll()
        {
            if (this.IsAutoScrollEnabled && this.scrollViewerListViewMarbleLog != null)
            {
                //if (this.scrollViewerListViewMarbleLog.VerticalOffset + 2 <= this.scrollViewerListViewMarbleLog.ScrollableHeight)
                    this.scrollViewerListViewMarbleLog.ScrollToVerticalOffset(this.scrollViewerListViewMarbleLog.ExtentHeight);
            }
        }

        void MarbleLogView_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.resizeTimer.IsEnabled = true;
            this.resizeTimer.Stop();
            this.resizeTimer.Start();
            this.isResizing = true;
        }

        void MarbleLogView_Loaded(object sender, RoutedEventArgs e)
        {
            this.resizeTimer = new DispatcherTimer { Interval = new TimeSpan(0, 0, 0, 0, 500), IsEnabled = false };
            
            this.scrollViewerListViewMarbleLog = GuiUtilities.FindVisualChild<ScrollViewer>(this.ListViewMarbleLog);
            
            this.scrollViewerListViewMarbleLog.ScrollChanged += scrollViewerListViewMarbleLog_ScrollChanged;
            this.SizeChanged += MarbleLogView_SizeChanged;
            this.resizeTimer.Tick += resizeTimer_Tick;
        }

        private void MarbleLogView_Unloaded(object sender, RoutedEventArgs e)
        {
            this.resizeTimer.Stop();
            this.resizeTimer.Tick -= this.resizeTimer_Tick;
        }

        void resizeTimer_Tick(object sender, EventArgs e)
        {
            this.resizeTimer.IsEnabled = false;
            this.isResizing = false;

            this.performAutocroll();
        }

        void scrollViewerListViewMarbleLog_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            if (this.scrollViewerListViewMarbleLog == null) return;

            if (e.ExtentHeightChange == 0 && !this.isResizing)
            {
                if (this.scrollViewerListViewMarbleLog.VerticalOffset + 2 >= this.scrollViewerListViewMarbleLog.ScrollableHeight)
                {
                    this.IsAutoScrollEnabled = true;
                }
                else
                {
                    this.IsAutoScrollEnabled = false;
                }
            }

            if (this.IsAutoScrollEnabled && e.ExtentHeightChange != 0)
            {
                this.scrollViewerListViewMarbleLog.ScrollToVerticalOffset(this.scrollViewerListViewMarbleLog.ExtentHeight);
            }
        }

        /// <summary>
        /// Gets the command for copying selected log entries to clipboard.
        /// </summary>
        public ICommand CmdCopySelected
        {
            get
            {
                if (this.cmdCopySelected == null)
                {
                    this.cmdCopySelected = new DelegateCommand(new Action(this.copySelectedLogEntriesToClipboard));
                }

                return this.cmdCopySelected;
            }
        }

        private ScrollViewer scrollViewerListViewMarbleLog;

        private ICommand cmdCopySelected;

        #region INotifyPropertyChanged Members

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion

        private void UcMarbleLogView_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (!this.IsLoaded) return;

            const int scrollBarWidth = 30;
            double messageColumnWidth = this.ListViewMarbleLog.ActualWidth - this.columnType.ActualWidth
                                        - this.columnTimeStamp.ActualWidth - scrollBarWidth;

            this.columnMessage.Width = messageColumnWidth > this.columnMessage.MinWidth ? messageColumnWidth : this.columnMessage.MinWidth;
            this.columnMessage.MaxWidth = messageColumnWidth > this.columnMessage.MinWidth ? messageColumnWidth : this.columnMessage.MinWidth;

            this.ListViewMarbleLog.Height = this.ActualHeight - this.StackPanelFilterControls.ActualHeight - this.columnsDataGrid.ActualHeight;
            this.ListViewMarbleLog.Width = this.ActualWidth;

            this.updateLogViewColumnSizing();
        }

        private void updateLogViewColumnSizing()
        {
            //this.GridViewColumnType.Width = this.columnType.ActualWidth;
            this.GridViewColumnTimeStamp.Width = this.columnTimeStamp.ActualWidth;
            this.GridViewColumnMessage.Width = this.columnMessage.ActualWidth;
        }

        private void ButtonCopySelected_Click(object sender, RoutedEventArgs e)
        {
            this.copySelectedLogEntriesToClipboard();
        }

        private void ButtonCopyAll_Click(object sender, RoutedEventArgs e)
        {
            this.copyAllLogEntriesToClipboard();
        }

        /// <summary>
        /// Unselects filtered items which have been filtered out.
        /// </summary>
        private void unselectHiddenItems()
        {
            List<object> selectedItems = this.ListViewMarbleLog.SelectedItems.Cast<object>().ToList();

            foreach (var selectedItem in selectedItems)
            {
                ListViewItem lvi = (ListViewItem)this.ListViewMarbleLog.ItemContainerGenerator.ContainerFromItem(selectedItem);

                if (lvi == null) continue;

                if (lvi.Template == null) lvi.IsSelected = false;
            }
        }

        private void copySelectedLogEntriesToClipboard()
        {
            this.unselectHiddenItems();

            Clipboard.SetDataObject(App.ViewModel.MarbleConnector.MarbleLogModel.GetCopyDataFromLogEntries(this.ListViewMarbleLog.SelectedItems));
        }

        private void copyAllLogEntriesToClipboard()
        {
            this.ListViewMarbleLog.SelectAll();
            this.unselectHiddenItems();

            Clipboard.SetDataObject(App.ViewModel.MarbleConnector.MarbleLogModel.GetCopyDataFromLogEntries(this.ListViewMarbleLog.SelectedItems));
        }

        private void columnsDataGrid_GotFocus(object sender, RoutedEventArgs e)
        {
            this.UcMarbleLogView_SizeChanged(sender, null);
        }
    }
}
