// -----------------------------------------------------------------------
// <copyright file="IGuiPlugin.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace Marble.Model
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public interface IGuiPlugin
    {
        /// <summary>
        /// Gets or sets pointer to possible plugin instance.
        /// </summary>
        object PluginInstance { get; set; }

        /// <summary>
        /// Gets a value indicating whether the plugin instance is found.
        /// </summary>
        bool HasPluginInstance { get; }

        /// <summary>
        /// Gets or sets a value indicating whether the progress bar is indeterminate (no specific progress is displayed).
        /// </summary>
        bool IsProgressBarIndeterminate { get; set; }

        /// <summary>
        /// Gets or sets a value indicating percentage value for the progress bar.
        /// </summary>
        double ProgressValue { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the plugin information should be displayed in the GUI.
        /// </summary>
        bool IsRunning { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the plugin has completed tasks.
        /// </summary>
        bool IsReady { get; set; }

        /// <summary>
        /// Gets or sets short description for the current status of the plugin to be displayed.
        /// </summary>
        string StatusText { get; set; }

        /// <summary>
        /// Gets or sets text for the tooltip, longer description.
        /// </summary>
        string ToolTipText { get; set; }

        /// <summary>
        /// Gets or sets file name for the icon which is displayed next to the progress bar.
        /// </summary>
        string IconFileName { get; set; }
        
        /// <summary>
        /// Opens the plugin process.
        /// </summary>
        void OpenProcess();
    }
}
