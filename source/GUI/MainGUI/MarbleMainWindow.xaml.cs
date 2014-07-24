using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using Marble.Communication;
using Microsoft.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Media;

using Marble.Model;
using Marble.Views;
using Marble.Utilities;

namespace Marble
{
    using System.Threading;
    using System.Windows.Input;

    using MarbleLibrary.Commands;
    using MarbleLibrary.CustomControls;
    using MarbleLibrary.Utilities;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MarbleMainWindow : Window
    {
        // To be able to show/hide external windows like VideoRecorder
        private const int SW_SHOWNORMAL = 1;
        private const int SW_SHOWMINIMIZED = 2;
        private const int SW_SHOWMAXIMIZED = 3;
        [DllImport("user32.dll")]
        private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        [DllImport("user32.dll")]
        private static extern bool SetForegroundWindow(IntPtr hWnd);

        private TestLabView _testLabView;

        private TestReportsTabView testReportsView;

        /// <summary>
        /// Gets test reports tab view user control.
        /// </summary>
        public TestReportsTabView TestReportsTabView { get { return this.testReportsView; } }

        /// <summary>
        /// Handles any unexpected exceptions and displays them to the user.
        /// </summary>
        private ExceptionHandler exceptionHandler;

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public MarbleMainWindow()
        {
            SplashScreenUtility.CloseSplashScreen();

            // Create the exception handler to handle any unexpected exceptions
            this.exceptionHandler = new ExceptionHandler(this, "Marble Error");

            this.testReportsView = new TestReportsTabView();

            InitializeComponent();

            this._testLabView = new TestLabView();
            this.DataContext = App.ViewModel;

            App.ViewModel.ActiveView = "TestLab";
            this.SwitchActiveView();

            App.ViewModel.PropertyChanged += (s, e) =>
            {
                if (e.PropertyName.Equals("ActiveView"))
                {
                    SwitchActiveView();
                }
            };

            // Fixes weird problem causing mouse cursor to stuck to normal arrow cursor.
            this.MouseMove += (s, e) => Mouse.OverrideCursor = null;


            this._testLabView.testCaseDataGrid.MouseDoubleClick += testCaseDataGrid_MouseDoubleClick;
        }

        void testCaseDataGrid_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (e.RightButton == MouseButtonState.Pressed || e.MiddleButton == MouseButtonState.Pressed ||
                Keyboard.GetKeyStates(Key.LeftShift) == KeyStates.Down || Keyboard.GetKeyStates(Key.RightShift) == KeyStates.Down ||
                Keyboard.GetKeyStates(Key.LeftCtrl) == KeyStates.Down || Keyboard.GetKeyStates(Key.RightCtrl) == KeyStates.Down ||
                Keyboard.GetKeyStates(Key.LeftAlt) == KeyStates.Down || Keyboard.GetKeyStates(Key.RightAlt) == KeyStates.Down) return;

            if (this._testLabView.testCaseDataGrid.SelectedItem == null) return;

            this.TestReportsTabView.SelectTestReportFromTestCaseSummary(this._testLabView.testCaseDataGrid.SelectedItem as TestCase);
            App.ViewModel.ActiveView = "TestReports";
        }

        /// <summary>
        /// Shows the right view when tab is clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnRibbonSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            RibbonTab tab = e.AddedItems[0] as RibbonTab;

            if (tab == null)
                return;

            // Change active view.
            switch (tab.Name)
            {
                case "tabTestLab":
                    App.ViewModel.ActiveView = "TestLab";
                    break;
                case "tabTestReports":
                    App.ViewModel.ActiveView = "TestReports";
                    break;
            }
        }

        /// <summary>
        /// Switches the active view based on the ActiveView property in the ViewModel.
        /// </summary>
        private void SwitchActiveView()
        {
            switch (App.ViewModel.ActiveView)
            {
                case "TestLab":
                    if (this.ViewGrid.Children.Count > 0)
                        this.ViewGrid.Children.RemoveAt(0);

                    this.ViewGrid.Children.Add(this._testLabView);
                    App.ViewModel.SetMarbleApplicationTitleText("TestLab");

                    // Show the status bar when in Test Lab.
                    this.MainViewStatusBar.Visibility = System.Windows.Visibility.Visible;
                    this.MainViewBottomBorder.Visibility = Visibility.Visible;
                    ////this.RibbonMain.SelectedItem = this.tabTestLab;

                    ////this.RibbonMain.IsCollapsed = false;
                    ////this.gridDummyRibbonTabHeaders.Visibility = Visibility.Collapsed;
                    DeferredAction.Create(this._testLabView.SelectAllCheckedTestCases).Defer(new TimeSpan(0, 0, 0, 0, 100));
                    break;
                case "TestReports":
                    if (this.ViewGrid.Children.Count > 0)
                        this.ViewGrid.Children.RemoveAt(0);

                    this.ViewGrid.Children.Add(this.testReportsView);
                    App.ViewModel.SetMarbleApplicationTitleText("TestReports");

                    // Show the status bar when in Test Reports.
                    this.MainViewStatusBar.Visibility = System.Windows.Visibility.Visible;
                    this.MainViewBottomBorder.Visibility = Visibility.Visible;
                    ////this.RibbonMain.SelectedItem = this.tabTestReports;

                    ////this.gridDummyRibbonTabHeaders.Visibility = this.RibbonMain.IsCollapsed ? Visibility.Visible : Visibility.Collapsed;
                    break;
            }
        }

        private void OnRibbonMainPreviewMouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            // This is to prevent user from minimizing Ribbon by double-clicking the RibbonTab header.
            e.Handled = true;
        }

        private void OnRibbonMainPreviewMouseRightButtonUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            // This is to prevent the rihght-click context menu from showing up in RibbonTab.
            e.Handled = true;
        }

        /// <summary>
        /// Handles only Ctrl+Break (Key.Cancel).
        /// Calls StopTestSet of the MarbleMainViewModel.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RibbonWindowKeyUp(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Oem6) && ((Keyboard.Modifiers & (ModifierKeys.Control | ModifierKeys.Alt)) == (ModifierKeys.Control | ModifierKeys.Alt)))
            {
                MessageBox.Show(!App.ViewModel.debugMode ? "Debug Mode Activated!" : "Debug Mode Deactivated!");
                App.ViewModel.debugMode = !App.ViewModel.debugMode;
            }
            if (e.Key == Key.Cancel)
                App.ViewModel.StopTestSet(true);
        }

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            ThreadPool.QueueUserWorkItem(state => App.createViewModels());
            App.ViewModel.StartLoadingSettings();
        }

        ////private void btnExport_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        ////{
        ////    App.ViewModel.UpdateMtbReportingRelatedControls();
        ////}

        ////private void RibbonTabHeader_MouseLeftButtonUp_1(object sender, MouseButtonEventArgs e)
        ////{
        ////    if (sender == dummyRibbonTabHeaderTestLab)
        ////    {
        ////        App.ViewModel.ActiveView = "TestLab";
        ////        this.SwitchActiveView();
        ////        this.gridDummyRibbonTabHeaders.Visibility = Visibility.Collapsed;
        ////    }
        ////    else if (sender == dummyRibbonTabHeaderTestReports)
        ////    {
        ////        ////this.RibbonMain.IsCollapsed = !this.RibbonMain.IsCollapsed;
        ////        ////this.gridDummyRibbonTabHeaders.Visibility = this.RibbonMain.IsCollapsed ? Visibility.Visible : Visibility.Collapsed;
        ////    }
        ////}

        private void btnTesting_Selected(object sender, RoutedEventArgs e)
        {

        }

        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            if (sender == this.buttonTestingView)
            {
                App.ViewModel.ActiveView = "TestLab";
            }
            else if (sender == this.buttonResultsView)
            {
                App.ViewModel.ActiveView = "TestReports";
            }
            else
            {
                return;
            }

            this.SwitchActiveView();
        }

        private void WindowMarbleMainWindow_StateChanged(object sender, EventArgs e)
        {
            string clientProcessDirectory = Environment.CurrentDirectory.Substring(0, Environment.CurrentDirectory.LastIndexOf(Path.DirectorySeparatorChar));
            bool processRunning = false;
            var processes = Process.GetProcessesByName("VideoRecorder");
            foreach (Process p in processes)
            {
                string processPath = Path.GetDirectoryName(p.MainModule.FileName);
                if (!string.IsNullOrEmpty(processPath) && processPath.StartsWith(clientProcessDirectory))
                {
                    processRunning = true;
                    if (p.MainWindowHandle != IntPtr.Zero)
                    {
                        if (this.WindowState == WindowState.Normal || this.WindowState == WindowState.Maximized)
                        {
                            ShowWindow(p.MainWindowHandle, SW_SHOWNORMAL);
                            SetForegroundWindow(p.MainWindowHandle);
                        }
                        else
                            ShowWindow(p.MainWindowHandle, SW_SHOWMINIMIZED);
                    }
                    p.Dispose();
                }
                p.Close();
                p.Dispose();
                if (processRunning)
                    break;
            }

            if (App.ViewModel.logWindow != null)
            {
                App.ViewModel.logWindow.WindowState = this.WindowState == WindowState.Minimized ? this.WindowState : WindowState.Normal;
            }
        }
    }
}
