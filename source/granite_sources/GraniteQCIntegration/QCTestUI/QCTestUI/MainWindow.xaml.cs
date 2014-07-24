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
using Nokia.Granite.QC;
using System.Xml.Linq;
using System.IO;
using System.Xml;


namespace QCTestUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private GraniteQCInterface graniteQCInterface = new GraniteQCInterface();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            //string status = graniteQCInterface.Authenticate(textBoxUserName.Text, passwordBox.Password, "https://qc11qa.nokia.com/qcbin/");
            string status = graniteQCInterface.Authenticate(textBoxUserName.Text, passwordBox.Password, "https://qc11.nokia.com/qcbin/");
            if (status != "OK")
            {
                textBox1.Text = status;
            }
            else
            {
                textBox1.Text = graniteQCInterface.GetDomainsAndProjects().ToString();
            }
        }

        private void Grid_Initialized(object sender, EventArgs e)
        {
            passwordBox.Focus();
        }

        private void buttonLoadTestLab_Click(object sender, RoutedEventArgs e)
        {
            XElement root;

            string testFolderId = "0";

            if (comboBoxTestFolders.SelectedItem!=null)
            {
                testFolderId = comboBoxTestFolders.SelectedItem.ToString();
            }

            root = graniteQCInterface.GetTestLabViewNode(textBoxDomain.Text, textBoxProject.Text, testFolderId);//.InnerXml;
            //XDocument XDoc = new XDocument();
            /*
            foreach (XElement node in root.Elements("//Entity[@Type='test-set-folder']/Fields/Field[@Name='id']/Value"))
            {
                comboBoxTestFolders.Items.Add(node.ToString());
            }

            foreach (XElement node in root.Elements("//Entity[@Type='test-set']/Fields/Field[@Name='id']/Value"))
            {
                comboBoxTestSets.Items.Add(node.ToString());
            }
            */
            textBox1.Text = root.ToString();

        }

        private void buttonLoadTestSet_Click(object sender, RoutedEventArgs e)
        {
            XElement root;
            root = graniteQCInterface.GetTestSet(textBoxDomain.Text, textBoxProject.Text, textBoxTestSet.Text, @"E:\Workareas\s40ng\granite\test_sets\test_file*.xml");//.InnerXml;
            //XDocument XDoc = new XDocument();
            if (root != null)
            {
                //using (response = request.GetResponse() as HttpWebResponse)
                //using (StringReader stringReader = new StringReader(root.OuterXml) as StringReader)
                //{
                    textBox1.Text = root.ToString();
                //}
            }
        }

        private void buttonSendResults_Click(object sender, RoutedEventArgs e)
        {
            textBox1.Text = graniteQCInterface.SendResults(textBoxTestSetPath.Text, textBoxUserName.Text,passwordBox.Password).ToString();
        }

        private void buttonTestAPI_Click(object sender, RoutedEventArgs e)
        {
            string value = graniteQCInterface.TestAPI(textBoxTestAPI.Text);
            if (value != "")
            {
                textBox1.Text = value;
            }
        }
    }
}
