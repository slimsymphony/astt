using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using Marble.Model;
using Marble.ViewModel;
using MarbleLibrary.CustomControls;

namespace Marble.Views
{
    /// <summary>
    /// Interaction logic for CoreTestToolSettingsView.xaml
    /// </summary>
    public partial class CoreTestToolSettingsView : UcBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CoreTestToolSettingsView"/> class.
        /// </summary>
        /// <param name="viewModel">The view model to be used by this view.</param>
        public CoreTestToolSettingsView(CoreTestToolSettingsViewModel viewModel)
        {
            InitializeComponent();

            // Store the view model
            this.DataContext = viewModel;

            // Create property grid for each of the configuration sections
            CreatePropertyGrids();
        }

        /// <summary>
        /// Create the property grids for the configuration sections.
        /// </summary>
        private void CreatePropertyGrids()
        {
            CoreTestToolSettingsViewModel viewModel = this.DataContext as CoreTestToolSettingsViewModel;

            if (viewModel != null)
            {
                foreach (CoreTestToolSettingsSection section in viewModel.Model.SettingsSections)
                {
                    // If there is a configuration section
                    if (section.Section != null)
                    {
                        // Create a property grid for the configuration section
                        ExtendedPropertyGrid propertyGrid = new ExtendedPropertyGrid();
                        propertyGrid.Dock = DockStyle.Fill;
                        propertyGrid.SelectedObject = section.Section;

                        // Create a host for the Windows form control
                        WindowsFormsHost host = new WindowsFormsHost();
                        host.Child = propertyGrid;

                        // Add the host to a settings grid
                        Grid settingsGrid = new Grid();
                        settingsGrid.Children.Add(host);

                        // Add a new tab for the settings grid
                        TabItem tabItem = new TabItem();
                        tabItem.Header = section.SectionName;
                        tabItem.ToolTip = System.IO.Path.GetFileNameWithoutExtension(section.AssemblyFilePath);
                        tabItem.Content = settingsGrid;

                        // Add this tab item to the tab control
                        tabSettings.Items.Add(tabItem);
                    }
                }
            }
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

            // Close this window
            base.CloseCommandHandler(this, null);
        }
    }
}
