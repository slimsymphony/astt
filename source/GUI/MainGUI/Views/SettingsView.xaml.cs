using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using System.Windows.Input;
using System.Windows.Threading;
using Marble.ViewModel;
using MarbleLibrary.CustomControls;
using TestAutomation.Gui.Marble.Settings;

namespace Marble.Views
{
    /// <summary>
    /// Interaction logic for SettingsView.xaml
    /// </summary>
    public partial class SettingsView : UcBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsView"/> class.
        /// </summary>
        /// <param name="viewModel">The view model to be used by this view.</param>
        public SettingsView(SettingsViewModel viewModel)
        {
            InitializeComponent();

            // Store the view model
            this.DataContext = viewModel;

            // Create property grid for each of the setting modules
            CreatePropertyGrids();

            // Hook up to events for any changes
            var model = viewModel.Model;
            model.SettingModuleAdded += OnSettingModuleAdded;
            model.SettingModuleRemoved += OnSettingModuleRemoved;
            model.SettingModuleRenamed += OnSettingModuleRenamed;
            model.SettingAdded += OnSettingAdded;
            model.SettingRemoved += OnSettingRemoved;
            model.SettingValueChanged += OnSettingChanged;

            viewModel.SetCancelValuesToAll();
        }

        /// <summary>
        /// Create the property grids for the setting modules.
        /// </summary>
        private void CreatePropertyGrids()
        {
            SettingsViewModel viewModel = this.DataContext as SettingsViewModel;

            if (viewModel != null)
            {
                foreach (SettingModule settingModule in viewModel.Model.SettingModules.OrderBy(s => s.Name))
                {
                    AddTabItem(settingModule);
                }
            }
        }

        /// <summary>
        /// Creates a new property grid for the setting module.
        /// </summary>
        /// <param name="settingModule">Setting module.</param>
        private void AddTabItem(SettingModule settingModule)      
        {
            // Create a tab item and add it to the tab control
            tabSettings.Items.Add(CreateTabItem(settingModule));
        }

        /// <summary>
        /// Creates a new tab item for the setting module.
        /// </summary>
        /// <param name="settingModule">Setting module.</param>
        /// <returns>New tab item containing the grid for the setting module.</returns>
        private static TabItem CreateTabItem(SettingModule settingModule)
        {
            // Add a new tab for the settings grid
            TabItem tabItem = new TabItem();
            tabItem.Header = settingModule.Name;
            tabItem.ToolTip = settingModule.SettingFilePath;
            tabItem.Content = CreateGrid(settingModule);

            return tabItem;
        }

        /// <summary>
        /// Creates a new grid for the setting module.
        /// </summary>
        /// <param name="settingModule">Setting module</param>
        /// <returns>New grid containing the property grid for the setting module.</returns>
        private static Grid CreateGrid(SettingModule settingModule)
        {
            // Create a property grid for the configuration section
            ExtendedPropertyGrid propertyGrid = new ExtendedPropertyGrid();
            propertyGrid.Dock = DockStyle.Fill;
            propertyGrid.SelectedObject = settingModule;

            // Create a host for the Windows form control
            WindowsFormsHost host = new WindowsFormsHost();
            host.Child = propertyGrid;

            // Add the host to a settings grid
            Grid settingsGrid = new Grid();
            settingsGrid.Children.Add(host);

            return settingsGrid;
        }

        /// <summary>
        /// Refreshes the property grid for the setting module.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        private void RefreshPropertyGrid(string settingModuleName)
        {
            // Find the tab item for the setting module
            TabItem tabItem = FindTabItem(settingModuleName);

            if (tabItem != null)
            {
                // Get the grid from the tab item
                Grid grid = tabItem.Content as Grid;

                // If the tab item has a grid with children
                if (grid != null &&
                    grid.Children.Count > 0)
                {
                    // Get the windows form host
                    WindowsFormsHost host = grid.Children[0] as WindowsFormsHost;

                    if (host != null)
                    {
                        // Get the property grid
                        ExtendedPropertyGrid propertyGrid = host.Child as ExtendedPropertyGrid;

                        if (propertyGrid != null)
                        {
                            // Refresh the property grid
                            propertyGrid.Refresh();
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Finds the tab item for the setting module name.
        /// </summary>
        /// <param name="settingModuleName">Name of the setting module.</param>
        /// <returns>Tab item for the specified setting module, otherwise <c>null</c> is returned.</returns>
        private TabItem FindTabItem(string settingModuleName)
        {
            TabItem foundTabItem = null;

            foreach (var item in tabSettings.Items)
            {
                TabItem tabItem = item as TabItem;

                // If this tab has the same header as the setting module
                if (tabItem != null &&
                    tabItem.Header is string &&
                    (string)tabItem.Header == settingModuleName)
                {
                    foundTabItem = tabItem;
                    break;
                }
            }

            return foundTabItem;
        }

        /// <summary>
        /// Called when the OK button is pressed.
        /// </summary>
        /// <param name="sender">Sender of the event.</param>
        /// <param name="e">Arguments for the event.</param>
        private void buttonOK_Click(object sender, RoutedEventArgs e)
        {
            // We are handling this event
            e.Handled = true;

            // If SIM properties have changed for the Main product, these properties are updated to SIM Manager.
            if (App.ViewModel.UpdateChangedSimPropertiesFromSettings())
            {
                if (App.SimManagerViewModel != null)
                    App.SimManagerViewModel.SaveCommandExecuted();
            }

            // Close this window
            CloseCommandHandler(this, null);
        }

        /// <summary>
        /// Handler for Close command. Closes parent window.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The e.</param>
        protected override void CloseCommandHandler(object sender, ExecutedRoutedEventArgs e)
        {
            SettingsViewModel viewModel = this.DataContext as SettingsViewModel;

            if (viewModel != null)
            {
                // Unhook from the events for any changes
                var model = viewModel.Model;
                model.SettingModuleAdded -= OnSettingModuleAdded;
                model.SettingModuleRemoved -= OnSettingModuleRemoved;
                model.SettingModuleRenamed -= OnSettingModuleRenamed;
                model.SettingAdded -= OnSettingAdded;
                model.SettingRemoved -= OnSettingRemoved;
                model.SettingValueChanged -= OnSettingChanged;
            }

            base.CloseCommandHandler(sender, e);
        }

        /// <summary>
        /// Called when a setting module is added.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingModuleAdded(SettingModuleAddedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                SettingsViewModel viewModel = this.DataContext as SettingsViewModel;

                if (viewModel != null)
                {
                    SettingModule settingModule = viewModel.Model.SettingModules.FirstOrDefault(m => m.Name == args.SettingModuleName);

                    if (settingModule != null)
                    {
                        AddTabItem(settingModule);
                    }
                }
            }));
        }

        /// <summary>
        /// Called when a setting module is removed.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingModuleRemoved(SettingModuleRemovedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                TabItem tabItem = FindTabItem(args.SettingModuleName);

                if (tabItem != null)
                {
                    // Remove the tab
                    tabSettings.Items.Remove(tabItem);
                }
            }));
        }

        /// <summary>
        /// Called when a setting module is renamed.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingModuleRenamed(SettingModuleRenamedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                TabItem tabItem = FindTabItem(args.OldName);

                if (tabItem != null)
                {
                    // Update the header
                    tabItem.Header = args.NewName;

                    SettingsViewModel viewModel = this.DataContext as SettingsViewModel;

                    if (viewModel != null)
                    {
                        SettingModule settingModule = viewModel.Model.SettingModules.FirstOrDefault(m => m.Name == args.NewName);

                        if (settingModule != null)
                        {
                            // Update the settings
                            tabItem.ToolTip = settingModule.SettingFilePath;
                            tabItem.Content = CreateGrid(settingModule);
                        }
                    }
                }
            }));
        }

        /// <summary>
        /// Called when a setting module is changed.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingChanged(SettingPropertyChangedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                RefreshPropertyGrid(args.SettingModuleName);
            }));
        }

        /// <summary>
        /// Called when a setting is added.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingAdded(SettingAddedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                RefreshPropertyGrid(args.SettingModuleName);
            }));
        }

        /// <summary>
        /// Called when a setting is removed.
        /// </summary>
        /// <param name="args">Arguments for the event.</param>
        void OnSettingRemoved(SettingRemovedEventArgs args)
        {
            Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                RefreshPropertyGrid(args.SettingModuleName);
            }));
        }

        private void buttonCancel_Click(object sender, RoutedEventArgs e)
        {
            ((SettingsViewModel)this.DataContext).CancelAllCommandExecuted();

            // Close this window
            CloseCommandHandler(this, null);
        }
    }
}
