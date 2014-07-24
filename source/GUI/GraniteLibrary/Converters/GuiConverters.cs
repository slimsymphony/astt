// -----------------------------------------------------------------------
// <copyright file="GuiConverters.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

using System.Drawing;
using System.Windows.Media.Imaging;

namespace MarbleLibrary.Converters
{
    using System;
    using System.Drawing.Imaging;
    using System.Globalization;
    using System.IO;
    using System.Linq;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Markup;
    using MarbleLibrary.CustomControls;

    /// <summary>
    /// Adds double type parameter value to double type value.
    /// </summary>
    public class DoubleValueAndParameterValueAdded : MarkupExtension, IValueConverter
    {
        private static DoubleValueAndParameterValueAdded converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new DoubleValueAndParameterValueAdded());
        }

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
            if (!(value is double)) return null;
            if (!(parameter is string)) return null;

            double parameterValue;

            if (!double.TryParse(parameter.ToString(), out parameterValue)) return null;

            double returnValue = (double)value + parameterValue;

            return returnValue < 0 ? 0 : returnValue;
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

    /// <summary>
    /// Adds int type parameter value to int type value.
    /// </summary>
    public class IntValueAndParameterValueAdded : MarkupExtension, IValueConverter
    {
        private static IntValueAndParameterValueAdded converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new IntValueAndParameterValueAdded());
        }

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
            if (!(value is int)) return null;
            if (!(parameter is string)) return null;

            int parameterValue;

            if (!int.TryParse(parameter.ToString(), out parameterValue)) return null;

            int returnValue = (int)value + parameterValue;

            return returnValue < 0 ? 0 : returnValue;
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

    /// <summary>
    /// Adds multiple values and returns sum.
    /// </summary>
    public class DoubleValuesAdded : MarkupExtension, IMultiValueConverter
    {
        private static DoubleValuesAdded converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new DoubleValuesAdded());
        }

        #region IValueConverter Members

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            double sum = 0;

            sum += values.Where(value => value is int || value is double).Aggregate<object, double>(0, (current, value) => current + (double)value);

            return sum;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion

    }

    /// <summary>
    /// Removes double type parameter value from double type value.
    /// </summary>
    public class DoubleValueAndParameterValueReduced : MarkupExtension, IValueConverter
    {
        private static DoubleValueAndParameterValueReduced converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new DoubleValueAndParameterValueReduced());
        }

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
            if (!(value is double)) return null;
            if (!(parameter is string)) return null;

            double parameterValue;

            if (!double.TryParse(parameter.ToString(), out parameterValue)) return null;

            double returnValue = (double)value - parameterValue;

            return returnValue < 0 ? 0 : returnValue;
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

    /// <summary>
    /// Reduces values from the first one and returns outcome.
    /// </summary>
    public class ReduceFromFirstValue : MarkupExtension, IMultiValueConverter
    {
        private static ReduceFromFirstValue converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new ReduceFromFirstValue());
        }

        #region IValueConverter Members

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            double outcome = 0;
            int i = 0;

            foreach (var value in values)
            {

                if (i == 0 && (value is int || value is double))
                {
                    outcome = (double)value;
                }
                else if (value is int || value is double)
                {
                    outcome -= (double)value;
                }

                i++;
            }

            return outcome;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion

    }

    /// <summary>
    /// Adds double type parameter value to double type value.
    /// </summary>
    public class NumericValueIsBiggerThanParameterValue : MarkupExtension, IValueConverter
    {
        private static NumericValueIsBiggerThanParameterValue converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new NumericValueIsBiggerThanParameterValue());
        }

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
            double valueAsDouble;
            double parameterValue;

            if (!double.TryParse(value.ToString(), out valueAsDouble)) return null;
            if (!double.TryParse(parameter.ToString(), out parameterValue)) return null;

            return valueAsDouble > parameterValue;
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

    /// <summary>
    /// Adds double type parameter value to double type value.
    /// </summary>
    public class NumericValueIsSmallerThanParameterValue : MarkupExtension, IValueConverter
    {
        private static NumericValueIsSmallerThanParameterValue converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new NumericValueIsSmallerThanParameterValue());
        }

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
            double valueAsDouble;
            double parameterValue;

            if (!double.TryParse(value.ToString(), out valueAsDouble)) return null;
            if (!double.TryParse(parameter.ToString(), out parameterValue)) return null;

            return valueAsDouble < parameterValue;
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

    /// <summary>
    /// Adds double type parameter value to double type value.
    /// </summary>
    public class InvertBoolValueConverter : MarkupExtension, IValueConverter
    {
        private static InvertBoolValueConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new InvertBoolValueConverter());
        }

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
            return !(value is bool) ? (object)null : !((bool)value);
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
            return !(value is bool) ? (object)null : !((bool)value);
        }

        #endregion
    }

    [ValueConversion(typeof(bool?), typeof(bool))]
    public class SuccessConverter : MarkupExtension, IValueConverter
    {
        private static SuccessConverter converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new SuccessConverter());
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool param = bool.Parse(parameter.ToString());

            return value != null && !((bool)value ^ param);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool param = bool.Parse(parameter.ToString());

            return !((bool)value ^ param);
        }

        #endregion
    }

    /// <summary>
    /// Converts CollapseMode to visibility.
    /// Collapse mode is Previous, visibility visible is returned.
    /// Other wise visibility collapsed is returned.
    /// </summary>
    public class CollapseModeIsPreviousToVisibility : IValueConverter
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
            if (!(value is CollapseMode)) return null;

            var collapseMode = (CollapseMode)value;

            return collapseMode == CollapseMode.Previous ? Visibility.Visible : Visibility.Collapsed;
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

    /// <summary>
    /// Converts CollapseMode to visibility.
    /// Collapse mode is Next, visibility visible is returned.
    /// Other wise visibility collapsed is returned.
    /// </summary>
    public class CollapseModeIsNextToVisibility : MarkupExtension, IValueConverter
    {
        private static CollapseModeIsNextToVisibility converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new CollapseModeIsNextToVisibility());
        }

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
            if (!(value is CollapseMode)) return null;

            var collapseMode = (CollapseMode)value;

            return collapseMode == CollapseMode.Next ? Visibility.Visible : Visibility.Collapsed;
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

    /// <summary>
    /// Converts CollapseMode to Style.
    /// </summary>
    public class CollapseModeToStyle : MarkupExtension, IValueConverter
    {
        private static CollapseModeToStyle converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new CollapseModeToStyle());
        }

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
            if (!(value is CollapseMode)) return null;

            var collapseMode = (CollapseMode)value;

            return collapseMode == CollapseMode.Next ? (object)string.Empty : Visibility.Collapsed;
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

    /// <summary>
    /// Converts file path to file name.
    /// </summary>
    public class FilePathToFileName : MarkupExtension, IValueConverter
    {
        private static FilePathToFileName converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new FilePathToFileName());
        }

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
            if (value == null) return null;

            if (string.IsNullOrEmpty(value.ToString())) 
                return string.Empty;

            if (!Path.IsPathRooted(value.ToString()) && value.ToString().Contains("\\") && !value.ToString().EndsWith("\\")) 
                return value.ToString().Substring(value.ToString().LastIndexOf("\\", System.StringComparison.Ordinal) + 1);

            if (Path.IsPathRooted(value.ToString())) 
                return Path.GetFileName(value.ToString());

            return value.ToString();
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

    /// <summary>
    /// Converts file path to file name.
    /// </summary>
    public class IsEnabledToOpacity : MarkupExtension, IValueConverter
    {
        private static IsEnabledToOpacity converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new IsEnabledToOpacity());
        }

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
            if (value == null) return null;

            // When true opacity value is 1.0 and when false opacity value is 0.4.
            if (value is bool)
                return (bool)value ? 1.0 : 0.4;

            return null;
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

    public class ImageToSourceConverter : MarkupExtension, IValueConverter
    {
        private static ImageToSourceConverter _converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new ImageToSourceConverter();
            }
            return _converter;
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            Image image = value as Image;
            if (image != null)
            {
                MemoryStream ms = new MemoryStream();
                image.Save(ms, ImageFormat.Jpeg);
                ms.Seek(0, SeekOrigin.Begin);
                BitmapImage bi = new BitmapImage();
                bi.BeginInit();
                bi.StreamSource = ms;
                bi.EndInit();
                return bi;
            }
            return null;
        }

        public object ConvertBack(object value, Type targetType,
            object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }

        #endregion
    }

    public class IsNullConverter : MarkupExtension, IValueConverter
    {
        private static IsNullConverter _converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new IsNullConverter();
            }
            return _converter;
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return (value == null);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new InvalidOperationException("IsNullConverter is used only for OneWay binding.");
        }

        #endregion
    }

    public class IsNullOrEmptyConverter : MarkupExtension, IValueConverter
    {
        private static IsNullOrEmptyConverter _converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            if (_converter == null)
            {
                _converter = new IsNullOrEmptyConverter();
            }
            return _converter;
        }

        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return string.IsNullOrEmpty(value.ToString());
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new InvalidOperationException("IsNullOrStringEmptyConverter is used only for OneWay binding.");
        }

        #endregion
    }

    /// <summary>
    /// Converts to double values to percentage. Divides 1st double with 2nd value and multiplies it with 100.
    /// </summary>
    public class DoubleValuesToPercentage : MarkupExtension, IMultiValueConverter
    {
        private static DoubleValuesToPercentage converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new DoubleValuesToPercentage());
        }

        #region IValueConverter Members

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(values[0] is double)) return null;
            if (!(values[1] is double)) return null;

            double returnValue = Math.Round((double)values[0] / (double)values[1] * 100, 2);

            return string.Format("({0:0.00}", returnValue);
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion

    }
}
