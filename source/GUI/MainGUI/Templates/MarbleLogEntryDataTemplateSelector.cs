// -----------------------------------------------------------------------
// <copyright file="MarbleLogEntryDataTemplateSelector.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Templates
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;

    using Marble.Model;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class MarbleLogEntryDataTemplateSelector : DataTemplateSelector
    {
        public DataTemplate GenericMarbleLogEntryTemplate { get; set; }

        public DataTemplate GuiMessageMarbleLogEntryTemplate { get; set; }

        public DataTemplate EventMarbleLogEntryTemplate { get; set; }

        public DataTemplate InfoMarbleLogEntryTemplate { get; set; }

        public DataTemplate WarningMarbleLogEntryTemplate { get; set; }

        public DataTemplate ErrorMarbleLogEntryTemplate { get; set; }

        public DataTemplate FailureMarbleLogEntryTemplate { get; set; }

        public DataTemplate FatalMarbleLogEntryTemplate { get; set; }

        public DataTemplate StageStartMarbleLogEntryTemplate { get; set; }

        public DataTemplate FrameworkRequestMarbleLogEntryTemplate { get; set; }

        public DataTemplate FrameworkResponseMarbleLogEntryTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            if (item == null || !(item is MarbleLogEntry)) return null;

            MarbleLogEntry marbleLogEntry = item as MarbleLogEntry;

            //return this.GenericMarbleLogEntryTemplate;

            switch (marbleLogEntry.LogEntryType)
            {
                    //case MarbleLogEntryType.Generic:
                //    return this.GenericMarbleLogEntryTemplate;
                case MarbleLogEntryType.Generic:
                    return this.GenericMarbleLogEntryTemplate;
                case MarbleLogEntryType.GuiMessage:
                    return this.GuiMessageMarbleLogEntryTemplate;
                case MarbleLogEntryType.Event:
                    return this.EventMarbleLogEntryTemplate;
                case MarbleLogEntryType.Info:
                    return this.InfoMarbleLogEntryTemplate;
                case MarbleLogEntryType.Warning:
                    return this.WarningMarbleLogEntryTemplate;
                case MarbleLogEntryType.Error:
                    return this.ErrorMarbleLogEntryTemplate;
                case MarbleLogEntryType.Failure:
                    return this.FailureMarbleLogEntryTemplate;
                case MarbleLogEntryType.Fatal:
                    return this.FatalMarbleLogEntryTemplate;
                case MarbleLogEntryType.StageStart:
                    return this.StageStartMarbleLogEntryTemplate;
                case MarbleLogEntryType.FrameworkRequest:
                    return this.FrameworkRequestMarbleLogEntryTemplate;
                case MarbleLogEntryType.FrameworkResponse:
                    return this.FrameworkResponseMarbleLogEntryTemplate;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public DataTemplate SelectTemplate(string templateName)
        {
            //return this.GenericMarbleLogEntryTemplate;

            switch (templateName)
            {
                case "Generic":
                    return this.GenericMarbleLogEntryTemplate;
                case "GuiMessage":
                    return this.GuiMessageMarbleLogEntryTemplate;
                case "Event":
                    return this.EventMarbleLogEntryTemplate;
                case "Info":
                    return this.InfoMarbleLogEntryTemplate;
                case "Warning":
                    return this.WarningMarbleLogEntryTemplate;
                case "Error":
                    return this.ErrorMarbleLogEntryTemplate;
                case "Failure":
                    return this.FailureMarbleLogEntryTemplate;
                case "Fatal":
                    return this.FatalMarbleLogEntryTemplate;
                case "StageStart":
                    return this.StageStartMarbleLogEntryTemplate;
                case "FrameworkRequest":
                    return this.FrameworkRequestMarbleLogEntryTemplate;
                case "FrameworkResponse":
                    return this.FrameworkResponseMarbleLogEntryTemplate;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }
    }
}
