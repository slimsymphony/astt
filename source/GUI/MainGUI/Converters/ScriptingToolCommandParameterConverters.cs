using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Marble.Converters
{
    using System.Globalization;
    using System.Windows.Data;
    using System.Windows.Markup;

    using Marble.Model;
    using Marble.ViewModel;

    /// <summary>
    /// Converts multiple values to one tuple containing toggle python command parameteres.
    /// </summary>
    public class ToggleCommandParameters : MarkupExtension, IMultiValueConverter
    {
        private static ToggleCommandParameters converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new ToggleCommandParameters());
        }

        #region IValueConverter Members

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(values[0] is DisplayElement)) return null;

            return new Tuple<DisplayElement, ElementSelectionMethod, bool?>(
                (DisplayElement)values[0], 
                (ElementSelectionMethod)values[1],
                (bool?)values[2]);
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion

    }

    /// <summary>
    /// Converts DisplayElement and ElementSelectionMethod values to one tuple containing python command parameters.
    /// </summary>
    public class DisplayElementAndSelectionMethodCommandParameters : MarkupExtension, IMultiValueConverter
    {
        private static DisplayElementAndSelectionMethodCommandParameters converter = null;

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return converter ?? (converter = new DisplayElementAndSelectionMethodCommandParameters());
        }

        #region IValueConverter Members

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(values[0] is DisplayElement)) return null;

            return new Tuple<DisplayElement, ElementSelectionMethod>(
                (DisplayElement)values[0],
                (ElementSelectionMethod)values[1]);
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        #endregion

    }
}
