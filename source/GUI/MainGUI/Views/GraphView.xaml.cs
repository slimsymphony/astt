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
    using System.ComponentModel;
    using System.IO;
    using System.Timers;
    using System.Windows.Threading;
    using System.Xml.Linq;

    using Marble.Model;
    using Marble.Utilities;

    using Microsoft.Win32;

    using Visiblox.Charts;

    /// <summary>
    /// Interaction logic for VideoPlayerView.xaml
    /// </summary>
    public partial class GraphView : UcBase, INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="GraphView"/> class.
        /// </summary>
        public GraphView()
        {
            InitializeComponent();

            //this.CreateLineSeries();
            //this.CreateStaircaseSeries();
            //this.CreateColumnSeries();
            //this.CreateDiscontinuousLineSeries(XElement.Parse(ExampleGraphData));

            this.Unloaded += GraphView_Unloaded;
        }

        void GraphView_Unloaded(object sender, RoutedEventArgs e)
        {
            this.Unloaded -= this.GraphView_Unloaded;

            if (this.chartGraph == null) return;
            
            this.chartGraph.Behaviour = null;

            this.chartGraph.Series.Clear();
            this.chartGraph.Series = null;
            this.chartGraph.Dispose();
            this.chartGraph = null;

            //GC.Collect();
        }

        #region [ GraphXml DependencyProperty]

        /// <summary>
        /// The graph XML property.
        /// </summary>
        public static readonly DependencyProperty GraphXmlProperty = DependencyProperty.Register(
            "GraphXml", typeof(XElement), typeof(GraphView), new FrameworkPropertyMetadata(null, OnGraphXmlPropertyChanged));

        /// <summary>
        /// Gets or sets the video file path.
        /// </summary>
        public XElement GraphXml
        {
            get { return (XElement)this.GetValue(GraphXmlProperty); }
            set { this.SetValue(GraphXmlProperty, value); }
        }

        private static void OnGraphXmlPropertyChanged(DependencyObject source, DependencyPropertyChangedEventArgs e)
        {
            if (e.NewValue == null) return;

            GraphView control = source as GraphView;
            XElement graphElement = XElement.Parse(e.NewValue.ToString());

            if (control == null) return;

            control.OnPropertyChanged("GraphXml");

            if (control.chartGraph == null) return;

            control.chartGraph.Series.Clear();
            control.CreateDiscontinuousLineSeries(graphElement);
        }

        #endregion [ GraphXml DependencyProperty]

        private double gapInterval;

        public double GapInterval
        {
            get
            {
                return this.gapInterval;
            }
            set
            {
                this.gapInterval = value;
                this.OnPropertyChanged("GapInterval");
            }
        }

        public void CreateLineSeries()
        {
            LineSeries lineSeries = new LineSeries();
            lineSeries.DataSeries = GenerateExampleDataSeries();
            lineSeries.LineStrokeThickness = 1.5;
            chartGraph.Series.Add(lineSeries);
        }

        public void CreateStaircaseSeries()
        {
            StaircaseSeries staircaseSeries = new StaircaseSeries();
            staircaseSeries.DataSeries = this.GenerateExampleDataSeries();
            staircaseSeries.LineStrokeThickness = 1.5;
            staircaseSeries.ToolTipEnabled = true;
            staircaseSeries.ShowLine = true;
            
            

            chartGraph.Series.Add(staircaseSeries);
        }

        public void CreateColumnSeries()
        {
            ColumnSeries columnSeries = new ColumnSeries();
            columnSeries.DataSeries = this.GenerateExampleDataSeries();
            columnSeries.ToolTipEnabled = true;
            columnSeries.BevelDepth = 2;
            columnSeries.BarWidthFraction = 0.8;

            var toolTipTemplate = (ControlTemplate)FindResource("ChartToolTipTemplate");

            columnSeries.ToolTipTemplate = toolTipTemplate;
            
            chartGraph.Series.Add(columnSeries);
        }

        public void CreateDiscontinuousLineSeriesExample(double gapIntervalInMs = 500)
        {
            DiscontinuousLineSeries discontinuousLineSeries = new DiscontinuousLineSeries();
            discontinuousLineSeries.DataSeries =
                this.CreateDiscontinuousLineDataSeriesFromXml(XElement.Parse(ExampleGraphData), gapIntervalInMs);
            discontinuousLineSeries.ToolTipEnabled = true;
            discontinuousLineSeries.NullHandlingMode = NullHandlingMode.Gap;
            discontinuousLineSeries.ShowArea = true;

            var toolTipTemplate = (ControlTemplate)FindResource("ChartToolTipTemplate");

            discontinuousLineSeries.ToolTipTemplate = toolTipTemplate;

            chartGraph.Series.Add(discontinuousLineSeries);
        }

        public void CreateDiscontinuousLineSeries(XElement perfTestStepXml, double gapIntervalInMs = 500)
        {
            PerformanceReportItemReportModel performanceReport = new PerformanceReportItemReportModel();
            //performanceReport.CreatePerfTestStepsFromXml(XElement.Parse(ExampleGraphData));
            performanceReport.CreatePerfTestStepsFromXml(perfTestStepXml);

            //chartGraph.Title = performanceReport.PerfTestSteps[0].

            if (performanceReport.PerfTestSteps.Count > 0)
            {
                chartGraph.Title = performanceReport.PerfTestSteps[0].Name;
            }

            DiscontinuousLineSeries fpsDiscontinuousLineSeries = new DiscontinuousLineSeries();
            DiscontinuousLineSeries uiMovementDiscontinuousLineSeries = new DiscontinuousLineSeries();

            DataSeries<double, double> fpsDataSeriesEntries = new DataSeries<double, double>();
            DataSeries<double, double> uiMovementDataSeriesEntries = new DataSeries<double, double>();

            foreach (GraphModel.PerfTestStepItemReportModel perfTestSteps in performanceReport.PerfTestSteps)
            {
                if (perfTestSteps.FpsDataSeries != null && perfTestSteps.FpsDataSeries.Count > 0)
                {
                    ////DiscontinuousLineSeries discontinuousLineSeries = new DiscontinuousLineSeries();

                    this.AdjustDataSeriesGaps(perfTestSteps.FpsDataSeries, gapIntervalInMs);
                    ////discontinuousLineSeries.DataSeries = perfTestSteps.FpsDataSeries;
                    fpsDataSeriesEntries.AddRange(perfTestSteps.FpsDataSeries);

                    //discontinuousLineSeries.DataSeries =
                    //    this.CreateDiscontinuousLineDataSeriesFromXml(XElement.Parse(ExampleGraphData), gapIntervalInMs);
                    ////discontinuousLineSeries.ToolTipEnabled = true;
                    ////discontinuousLineSeries.NullHandlingMode = NullHandlingMode.Gap;
                    ////discontinuousLineSeries.ShowArea = true;
                    ////discontinuousLineSeries.ShowPoints = true;

                    ////var toolTipTemplate = (ControlTemplate)FindResource("ChartScreenUpdateToolTipTemplate");

                    ////discontinuousLineSeries.ToolTipTemplate = toolTipTemplate;

                    ////chartGraph.Series.Add(discontinuousLineSeries);
                }

                if (perfTestSteps.UiMovementDataSeries != null && perfTestSteps.UiMovementDataSeries.Count > 0)
                {
                    ////DiscontinuousLineSeries discontinuousLineSeries = new DiscontinuousLineSeries();

                    this.AdjustDataSeriesGaps(perfTestSteps.UiMovementDataSeries, gapIntervalInMs);
                    ////discontinuousLineSeries.DataSeries = perfTestSteps.UiMovementDataSeries;
                    uiMovementDataSeriesEntries.AddRange(perfTestSteps.UiMovementDataSeries);

                    //discontinuousLineSeries.DataSeries =
                    //    this.CreateDiscontinuousLineDataSeriesFromXml(XElement.Parse(ExampleGraphData), gapIntervalInMs);
                    ////discontinuousLineSeries.ToolTipEnabled = true;
                    ////discontinuousLineSeries.NullHandlingMode = NullHandlingMode.Gap;
                    ////discontinuousLineSeries.ShowArea = true;
                    ////discontinuousLineSeries.ShowPoints = true;

                    ////var toolTipTemplate = (ControlTemplate)FindResource("ChartUiMovementToolTipTemplate");

                    ////discontinuousLineSeries.ToolTipTemplate = toolTipTemplate;

                    ////chartGraph.Series.Add(discontinuousLineSeries);
                }

            }

            fpsDiscontinuousLineSeries.DataSeries = fpsDataSeriesEntries;
            fpsDiscontinuousLineSeries.ToolTipEnabled = true;
            fpsDiscontinuousLineSeries.NullHandlingMode = NullHandlingMode.Gap;
            fpsDiscontinuousLineSeries.ShowArea = true;
            fpsDiscontinuousLineSeries.ShowPoints = true;
            fpsDiscontinuousLineSeries.ToolTipTemplate = (ControlTemplate)FindResource("ChartScreenUpdateToolTipTemplate");

            chartGraph.Series.Add(fpsDiscontinuousLineSeries);

            uiMovementDiscontinuousLineSeries.DataSeries = uiMovementDataSeriesEntries;
            uiMovementDiscontinuousLineSeries.ToolTipEnabled = true;
            uiMovementDiscontinuousLineSeries.NullHandlingMode = NullHandlingMode.Gap;
            uiMovementDiscontinuousLineSeries.ShowArea = true;
            uiMovementDiscontinuousLineSeries.ShowPoints = true;
            uiMovementDiscontinuousLineSeries.ToolTipTemplate = (ControlTemplate)FindResource("ChartUiMovementToolTipTemplate");

            chartGraph.Series.Add(uiMovementDiscontinuousLineSeries);

            ////chartGraph.SizeChanged += chartGraph_SizeChanged;
            

        }

        void chartGraph_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.imageChartPreview.Source = GraphUtilities.CreateScreenshotFromChart(chartGraph);

            chartGraph.SizeChanged -= this.chartGraph_SizeChanged;
        }

        public IDataSeries GenerateExampleDataSeries()
        {
            //DataSeries<double, double> dataSeries = new DataSeries<double, double>();
            DataSeries<double, double> dataSeries = this.CreateDataSeriesFromXml(XElement.Parse(ExampleGraphData));

            return dataSeries;
        }

        public DataSeries<double, double> CreateDataSeriesFromXml(XElement performanceReportElement)
        {
            if (performanceReportElement == null) return null;

            DataSeries<double, double> dataSeries = new DataSeries<double, double>();

            foreach (var childElement in performanceReportElement.Elements("test_step_perf"))
            {
                foreach (var screenUpdateElement in childElement.Elements("screen_update"))
                {
                    double timeStamp = 0;
                    double fps = 0;

                    var fpsAttribute = screenUpdateElement.Attribute("fps");
                    if (fpsAttribute != null && !double.TryParse(fpsAttribute.Value, out fps))
                    {
                        fps = 0;
                    }

                    var timeStampAttribute = screenUpdateElement.Attribute("time_stamp");
                    if (timeStampAttribute != null && !double.TryParse(timeStampAttribute.Value, out timeStamp))
                    {
                        timeStamp = 0;
                    }

                    dataSeries.Add(new DataPoint<double, double>(timeStamp, fps));
                }
            }

            return dataSeries;
        }

        public DataSeries<double, double> CreateDiscontinuousLineDataSeriesFromXml(XElement performanceReportElement, double intervalInMs)
        {
            if (performanceReportElement == null) return null;

            DataSeries<double, double> dataSeries = new DataSeries<double, double>();

            double previousTimeStamp = 0;

            foreach (var childElement in performanceReportElement.Elements("test_step_perf"))
            {
                foreach (var screenUpdateElement in childElement.Elements("screen_update"))
                {
                    double timeStamp = 0;
                    double fps = 0;

                    var fpsAttribute = screenUpdateElement.Attribute("fps");
                    if (fpsAttribute != null && !double.TryParse(fpsAttribute.Value, out fps))
                    {
                        fps = 0;
                    }

                    var timeStampAttribute = screenUpdateElement.Attribute("time_stamp");
                    if (timeStampAttribute != null && !double.TryParse(timeStampAttribute.Value, out timeStamp))
                    {
                        timeStamp = 0;
                    }

                    if (timeStamp - previousTimeStamp > intervalInMs)
                    {
                        dataSeries.Add(null);
                    }

                    dataSeries.Add(new DataPoint<double, double>(timeStamp, fps));

                    previousTimeStamp = timeStamp;
                }
            }

            return dataSeries;
        }

        public void AdjustDataSeriesGaps(DataSeries<double, double> dataSeries, double gapInterval)
        {
            // Removes 'null' DataPoints from DataSeries.
            List<int> dataPointsToRemove = new List<int>();

            for (int i = 0; i < dataSeries.Count; i++)
            {
                if (dataSeries[i] != null) continue;

                dataPointsToRemove.Add(i);
            }

            dataPointsToRemove.Reverse();

            foreach (int i in dataPointsToRemove)
            {
                dataSeries.RemoveAt(i);
            }

            // 'null' DataPoints are added with the new gap interval.
            List<int> nullDataPointsToAdd = (from dataPoint in dataSeries.TakeWhile(dataPoint => dataPoint != dataSeries.Last()) 
                                             where dataSeries[dataSeries.IndexOf(dataPoint) + 1].X - dataPoint.X > gapInterval 
                                             select dataSeries.IndexOf(dataPoint) + 1).ToList();

            foreach (int i in nullDataPointsToAdd)
            {
                dataSeries.Insert(i, null);
            }
        }

        public const string ExampleGraphData = @"<performance_report>
  <test_step_perf name=""select(Notes (nZKrWiFJlSUK0boE-qrfPIg))"" average_fps=""15"" common_average_fps=""7"" duration=""15798"">
    <ui_movement start=""344683"" duration=""7611"" stop=""352294"">
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""344686"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""344811"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""344825"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""346112"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""346121"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""347115"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""347124"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""348117"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""348126"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""349119"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""349131"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""350125"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""350134"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""351127"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""351136"" />
      <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""352129"" />
      <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""352138"" />
    </ui_movement>
    <screen_update x=""4"" y=""0"" width=""236"" height=""320"" fps=""2"" time_stamp=""352319"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""2"" time_stamp=""352381"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""3"" time_stamp=""352411"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""3"" time_stamp=""352449"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""4"" time_stamp=""352478"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""4"" time_stamp=""352510"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""7"" time_stamp=""352538"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""6"" time_stamp=""352577"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""21"" time_stamp=""352605"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""20"" time_stamp=""352637"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""31"" time_stamp=""352665"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""34"" time_stamp=""352705"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""35"" time_stamp=""352733"" />
    <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""35"" time_stamp=""352761"" />
    <ui_movement start=""352886"" duration=""26"" stop=""352912"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""35"" time_stamp=""353134"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""16"" time_stamp=""353154"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""16"" time_stamp=""354881"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""4"" time_stamp=""354890"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""4"" time_stamp=""355882"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""3"" time_stamp=""355890"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""3"" time_stamp=""356883"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""356892"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""357884"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""357894"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""358168"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""1"" time_stamp=""359169"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""359178"" />
    <screen_update x=""187"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""360175"" />
    <screen_update x=""168"" y=""0"" width=""238"" height=""18"" fps=""2"" time_stamp=""360184"" />
    <screen_update x=""4"" y=""0"" width=""236"" height=""320"" fps=""2"" time_stamp=""360484"" />
    <application_changed time=""361245"" />
  </test_step_perf>
  <test_step_perf name=""exit()"" average_fps=""5"" common_average_fps=""5"" duration=""54"">
    <ui_movement start=""372737"" duration=""156"" stop=""372893"">
      <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""4"" time_stamp=""372789"" />
      <screen_update x=""0"" y=""0"" width=""240"" height=""320"" fps=""7"" time_stamp=""372843"" />
    </ui_movement>
    <application_changed time=""372965"" />
  </test_step_perf>
</performance_report>";

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

        private void buttonOpenInWindow_Click(object sender, RoutedEventArgs e)
        {
            Window graphWindow = new Window();
            graphWindow.Title = "Marble - Chart - " + this.chartGraph.Title;
            graphWindow.Icon = new BitmapImage(new Uri("pack://application:,,,/MarbleLibrary;component/Images/Marble.M.Icon.ico", UriKind.RelativeOrAbsolute));
            graphWindow.Width = 640;
            graphWindow.Height = 480;

            GraphView graphView = new GraphView();
            graphView.ParentWindow = graphWindow;

            graphWindow.Content = graphView;
            graphView.GraphXml = this.GraphXml;
            //graphView.CreateDiscontinuousLineSeries(this.GraphXml);
            graphWindow.Show();

            graphWindow.Closing += delegate
                {
                    if (graphView.chartGraph != null)
                    {
                        graphView.chartGraph.Dispose();
                        graphView.chartGraph = null;
                        GC.Collect();
                    }
                };
        }

        private void radioButtonChartControls_CheckedUnchecked(object sender, RoutedEventArgs e)
        {
            if (sender == this.radioButtonPan)
            {
                this.panning.IsEnabled = this.radioButtonPan.IsChecked == true;
            }
            else if (sender == this.radioButtonZoom)
            {
                this.zooming.IsEnabled = this.radioButtonZoom.IsChecked == true;
            }
        }

        private void buttonSaveChartAsImage_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.FileName = "Exported Chart";
            dlg.Filter = "PNG File|*.png";

            if (dlg.ShowDialog() == true)
            {
                // Save the current layout transform before clearing it
                Transform transform = this.chartGraph.LayoutTransform;
                this.chartGraph.LayoutTransform = null;

                int width = (int)this.chartGraph.ActualWidth;
                int height = (int)this.chartGraph.ActualHeight;

                // Note: You only really need to do this bit if the chart isn't part of the UI (ie: a chart you create in memory)
                Size size = new Size(width, height);
                this.chartGraph.Measure(size);
                this.chartGraph.Arrange(new Rect(size));
                this.chartGraph.UpdateLayout();

                // Create a render bitmap and push the surface to it
                RenderTargetBitmap rtb = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
                rtb.Render(chartGraph);

                // Note: Change the encoder and frame for different image types
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(rtb));

                // Save the image
                Stream stream = dlg.OpenFile();
                encoder.Save(stream);
                stream.Flush();
                stream.Close();

                // Restore previously saved layout transform
                chartGraph.LayoutTransform = transform;
            }
        }

        private void buttonResetZoom_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void buttonZoomRangeToAxisX_Click(object sender, RoutedEventArgs e)
        {
            chartGraph.XAxis.AdoptZoomAsRange();
        }

        private void buttonZoomRangeToAxisY_Click(object sender, RoutedEventArgs e)
        {
            chartGraph.YAxis.AdoptZoomAsRange();
        }

        private void buttonApplyGapInterval_Click(object sender, RoutedEventArgs e)
        {
            this.chartGraph.Series.Clear();
            this.CreateDiscontinuousLineSeries(this.GraphXml, this.GapInterval);
        }
    }
}
