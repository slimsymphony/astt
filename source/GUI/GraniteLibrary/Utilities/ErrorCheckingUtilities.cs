// -----------------------------------------------------------------------
// <copyright file="ErrorCheckingUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.Globalization;
    using System.Linq;
    using System.Threading;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class ErrorCheckingUtilities
    {
        /// <summary>
        /// Verifies if string is a number.
        /// </summary>
        /// <param name="value">Value to verify.</param>
        /// <param name="allowLeadingSign">if set to <c>true</c> [allow leading sign].</param>
        /// <param name="allowDecimalSeparator">if set to <c>true</c> [allow decimal separator].</param>
        /// <returns>
        /// Bool which states if string is a number.
        /// </returns>
        public static bool VerifyStringAsNumber(string value, bool allowLeadingSign, bool allowDecimalSeparator)
        {
            if (value == null) return false;

            if (string.IsNullOrEmpty(value) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.CurrencyGroupSeparator) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.CurrencySymbol) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.NegativeInfinitySymbol) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.NumberGroupSeparator) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PercentGroupSeparator) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PercentSymbol) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PerMilleSymbol) |
                value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PositiveInfinitySymbol))
                return false;

            if (!allowLeadingSign)
                if (value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.NegativeSign) |
                    value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PositiveSign))
                    return false;

            if (!allowDecimalSeparator)
                if (value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.CurrencyDecimalSeparator) |
                    value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator) |
                    value.Contains(System.Globalization.NumberFormatInfo.CurrentInfo.PercentDecimalSeparator))
                    return false;

            return value.All(character => char.IsDigit(character) ||
                character == Convert.ToChar(System.Globalization.NumberFormatInfo.CurrentInfo.NegativeSign) ||
                character == Convert.ToChar(System.Globalization.NumberFormatInfo.CurrentInfo.PositiveSign) ||
                character == Convert.ToChar(System.Globalization.NumberFormatInfo.CurrentInfo.CurrencyDecimalSeparator) ||
                character == Convert.ToChar(System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator) ||
                character == Convert.ToChar(System.Globalization.NumberFormatInfo.CurrentInfo.PercentDecimalSeparator));

            //return !value.Any(character => !char.IsDigit(character));
        }

        /// <summary>
        /// Verifies if string is an int.
        /// </summary>
        /// <param name="value">Value to verify.</param>
        /// <param name="allowLeadingSign">True if minus and plus sign is allowed.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>
        /// Bool which states if string is an int.
        /// </returns>
        public static bool VerifyStringAsInt(string value, bool allowLeadingSign, CultureInfo culture = null)
        {
            int result;
            CultureInfo usedCulture = culture;

            if (culture == null)
                culture = Thread.CurrentThread.CurrentUICulture;

            if (allowLeadingSign)
            {
                if (!int.TryParse(value, NumberStyles.AllowLeadingSign, culture, out result))
                    return false;
            }
            else
            {
                if (!int.TryParse(value, out result))
                    return false;
            }

            return VerifyStringAsNumber(value, allowLeadingSign, false);
        }

        /// <summary>
        /// Verifies if string is a double.
        /// </summary>
        /// <param name="value">Value to verify.</param>
        /// <param name="allowLeadingSign">True if minus and plus sign is allowed.</param>
        /// <returns>Bool which states if string is a double.</returns>
        public static bool VerifyStringAsDouble(string value, bool allowLeadingSign)
        {
            double result;

            //if (allowLeadingSign)
            //{
            //    if ()
            //    //if (!double.TryParse(value, NumberStyles.AllowLeadingSign, App.MainTeaBox.ToolBox.Culture, out result))
            //    //    return false;
            //}
            if (!allowLeadingSign)
            {
                if (!double.TryParse(value, out result))
                    return false;
            }

            if (!VerifyStringAsNumber(value, allowLeadingSign, true)) return false;

            return double.TryParse(value, out result);
        }

        /// <summary>
        /// Verifies if string is a float.
        /// </summary>
        /// <param name="value">Value to verify.</param>
        /// <param name="allowLeadingSign">True if minus and plus sign is allowed.</param>
        /// <param name="culture">The culture.</param>
        /// <returns>
        /// Bool which states if string is a float.
        /// </returns>
        public static bool VerifyStringAsFloat(string value, bool allowLeadingSign, CultureInfo culture = null)
        {
            float result;
            CultureInfo usedCulture = culture;

            if (culture == null)
                culture = Thread.CurrentThread.CurrentUICulture;

            if (allowLeadingSign)
            {
                if (!float.TryParse(value, NumberStyles.AllowLeadingSign, culture, out result))
                    return false;
            }
            else
            {
                if (!float.TryParse(value, out result))
                    return false;
            }

            if (!VerifyStringAsNumber(value, allowLeadingSign, true)) return false;

            return float.TryParse(value, out result);
        }
    }
}
