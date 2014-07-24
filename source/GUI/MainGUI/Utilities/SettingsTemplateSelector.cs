using System;
using System.Resources;
using System.Windows.Controls;
using System.Windows;

using Marble.Model;

namespace Marble.Utilities
{
    /// <summary>
    /// DataTemplateSelector for Settings view.
    /// </summary>
    public class SettingsTemplateSelector : DataTemplateSelector
    {
        /// <summary>
        /// DataTemplate for boolean and other multiple valued SettingsItems.
        /// </summary>
        public DataTemplate ComboBoxTemplate { get; set; }
        
        /// <summary>
        /// DataTemplate for string SettingsItems.
        /// </summary>
        public DataTemplate StringTemplate { get; set; }

        /// <summary>
        /// DataTemplate for empty string SettingsItems.
        /// </summary>
        public DataTemplate EmptyStringTemplate { get; set; }

        /// <summary>
        /// Selects right data template for showing different types of settings.
        /// </summary>
        /// <param name="item">Settings item.</param>
        /// <param name="container"></param>
        /// <returns>Returns appropriate data template. Returns StringTemplate if SettingsItem is null.</returns>
        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            SettingsItem settingsItem = (SettingsItem)item;

            if (settingsItem != null)
            {
                if (settingsItem.Type == "URL")
                    return EmptyStringTemplate;
                else if (settingsItem.Type == "Bool")
                    return ComboBoxTemplate;
                else if (!string.IsNullOrEmpty(settingsItem.ValidValues))
                    return ComboBoxTemplate;
            }

            return StringTemplate;
        }
    }
}
