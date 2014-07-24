// -----------------------------------------------------------------------
// <copyright file="GraphModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Xml.Linq;

    using Visiblox.Charts;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class GraphModel
    {
        public class PerfTestStepItemReportModel
        {
            public PerfTestStepItemReportModel()
            {
                this.FpsDataSeries = new DataSeries<double, double>();
                this.UiMovementDataSeries = new DataSeries<double, double>();
            }

            public string Name { get; set; }

            public double AverageFps { get; set; }

            public double CommonAverageFps { get; set; }

            public double Duration { get; set; }

            public DataSeries<double, double> FpsDataSeries { get; set; }

            public DataSeries<double, double> UiMovementDataSeries { get; set; }

            public static PerfTestStepItemReportModel CreatePerfTestStepItemFromXml(XElement perfTestStepElement)
            {
                if (perfTestStepElement == null) return null;

                PerfTestStepItemReportModel perfTestStepItem = new PerfTestStepItemReportModel();

                perfTestStepItem.Name = perfTestStepElement.Attribute("name") != null ? perfTestStepElement.Attribute("name").Value : string.Empty;
                perfTestStepItem.AverageFps = perfTestStepElement.Attribute("average_fps") != null ? double.Parse(perfTestStepElement.Attribute("average_fps").Value) : -1;
                perfTestStepItem.CommonAverageFps = perfTestStepElement.Attribute("common_average_fps") != null ? double.Parse(perfTestStepElement.Attribute("common_average_fps").Value) : -1;
                perfTestStepItem.Duration = perfTestStepElement.Attribute("duration") != null ? double.Parse(perfTestStepElement.Attribute("duration").Value) : -1;

                perfTestStepItem.FpsDataSeries = PerfTestStepItemReportModel.CreateScreenUpdateDataSeriesFromXml(perfTestStepElement);

                DataSeries<double, double> uiMovementDataSeries = new DataSeries<double, double>();

                foreach (var uiMovementElement in perfTestStepElement.Elements("ui_movement"))
                {
                    UiMovementInfoModel uiMovementInfo = UiMovementInfoModel.CreateUiMovementInfoFromXElement(uiMovementElement);

                    if (!uiMovementElement.HasElements)
                    {
                        perfTestStepItem.UiMovementDataSeries.Add(new DataPoint<double, double>(uiMovementInfo.StartTimeStamp, 0) { Tag = uiMovementElement });
                        perfTestStepItem.UiMovementDataSeries.Add(new DataPoint<double, double>(uiMovementInfo.StopTimeStamp, 0) { Tag = uiMovementElement });

                        continue;
                    }

                    foreach (DataPoint<double, double> uiMovementDataPoint in PerfTestStepItemReportModel.CreateScreenUpdateDataSeriesFromXml(uiMovementElement))
                    {
                        perfTestStepItem.UiMovementDataSeries.Add(uiMovementDataPoint);
                    }
                }

                return perfTestStepItem;
            }

            public static DataSeries<double, double> CreateScreenUpdateDataSeriesFromXml(XElement xElement)
            {
                if (xElement == null) return null;

                DataSeries<double, double> dataSeries = new DataSeries<double, double>();

                foreach (var screenUpdateElement in xElement.Elements("screen_update"))
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

                    dataSeries.Add(new DataPoint<double, double>(timeStamp, fps) { Tag = ScreenUpdateInfoModel.CreateScreenUpdateInfoFromXElement(screenUpdateElement) });
                }

                return dataSeries;
            }

            public static void ChangeDataSeriesNullGaps(DataSeries<double, double> dataSeries, double gapInterval)
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
        }

        public class ScreenUpdateInfoModel
        {
            // <screen_update x="187" y="0" width="238" height="18" fps="2" time_stamp="344686" />

            public int X { get; set; }

            public int Y { get; set; }

            public int Width { get; set; }

            public int Height { get; set; }

            public double Fps { get; set; }

            public double TimeStamp { get; set; }

            public static ScreenUpdateInfoModel CreateScreenUpdateInfoFromXElement(XElement screenUpdateElement)
            {
                return new ScreenUpdateInfoModel
                {
                    X =
                        screenUpdateElement.Attribute("x") != null
                            ? int.Parse(screenUpdateElement.Attribute("x").Value)
                            : 0,
                    Y =
                        screenUpdateElement.Attribute("y") != null
                            ? int.Parse(screenUpdateElement.Attribute("y").Value)
                            : 0,
                    Width =
                        screenUpdateElement.Attribute("width") != null
                            ? int.Parse(screenUpdateElement.Attribute("width").Value)
                            : 0,
                    Height =
                        screenUpdateElement.Attribute("height") != null
                            ? int.Parse(screenUpdateElement.Attribute("height").Value)
                            : 0,
                    Fps =
                        screenUpdateElement.Attribute("fps") != null
                            ? int.Parse(screenUpdateElement.Attribute("fps").Value)
                            : 0,
                    TimeStamp =
                        screenUpdateElement.Attribute("time_stamp") != null
                            ? int.Parse(screenUpdateElement.Attribute("time_stamp").Value)
                            : 0
                };
            }
        }

        public class UiMovementInfoModel
        {
            // <ui_movement start="352886" duration="26" stop="352912" />

            public double StartTimeStamp { get; set; }

            public double StopTimeStamp { get; set; }

            public double Duration { get; set; }

            public static UiMovementInfoModel CreateUiMovementInfoFromXElement(XElement uiMovementElement)
            {
                return new UiMovementInfoModel()
                {
                    StartTimeStamp =
                    uiMovementElement.Attribute("start") != null
                        ? int.Parse(uiMovementElement.Attribute("start").Value)
                        : 0,
                    StopTimeStamp =
                    uiMovementElement.Attribute("stop") != null
                        ? int.Parse(uiMovementElement.Attribute("stop").Value)
                        : 0,
                    Duration =
                    uiMovementElement.Attribute("duration") != null
                        ? int.Parse(uiMovementElement.Attribute("duration").Value)
                        : 0
                };
            }
        }
    }
}
