// -----------------------------------------------------------------------
// <copyright file="BoolToTextWrappingConverter.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Converters
{
    using System;
    using System.Globalization;
    using System.Windows;
    using System.Windows.Data;

    /// <summary>
    /// Converts boolean to TextWrapping.
    /// True -&gt; Text wrapping is set to wrap.
    /// False -&gt; Text wrapping is set to no wrap.
    /// </summary>
    public class BoolToTextWrappingConverter : IValueConverter
    {
        #region IValueConverter Members

        /// <summary>
        /// Converts a value.
        /// </summary>
        /// <param name="value">The value produced by the binding source.</param>
        /// <param name="targetType">The type of the binding target property.</param>
        /// <param name="parameter">The converter parameter to use.</param>
        /// <param name="culture">The culture to use in the converter.</param>
        /// <returns>
        /// A converted value. If the method returns null, the valid null value is used.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is bool)) return TextWrapping.NoWrap;

            var v = (bool)value;

            return v ? TextWrapping.Wrap : TextWrapping.NoWrap;
        }

        /// <summary>
        /// Converts a value back.
        /// </summary>
        /// <param name="value">The value that is produced by the binding target.</param>
        /// <param name="targetType">The type to convert to.</param>
        /// <param name="parameter">The converter parameter to use.</param>
        /// <param name="culture">The culture to use in the converter.</param>
        /// <returns>
        /// A converted value. If the method returns null, the valid null value is used.
        /// </returns>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
