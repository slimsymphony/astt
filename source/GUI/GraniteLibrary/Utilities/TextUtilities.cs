// -----------------------------------------------------------------------
// <copyright file="TextUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.Linq;
    using System.Text;
    using System.Text.RegularExpressions;

    public enum LastUsedDateTimeComponent
    {
        Default = 0,
        Year = 1,
        Month = 2,
        Day = 3,
        Hour = 4,
        Minute = 5,
        Second = 6,
        MilliSecond = 7,
    }

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class TextUtilities
    {
        /// <summary>
        /// Special characters used in Regex. IMPORTANT "\\" must be first so that special characters are used properly.
        /// </summary>
        public static string[] RegexSpecialCharacters { get { return new string[] { "\\", "[", "^", "$", ".", "|", "?", "*", "+", "(", ")" }; } }

        public static string SimpleTextEditorName { get { return "Marble Script Editor"; } }

        public static string ConvertPhoneNumberToSimModelFormat(string phoneNumber)
        {
            if (!phoneNumber.StartsWith("+")) phoneNumber = "+" + phoneNumber;


            return phoneNumber;
        }

        public static string ConvertRegexSpecialCharactersToText(string text)
        {
            return TextUtilities.RegexSpecialCharacters.Aggregate(text, (current, regexCharacter) => current.Replace(regexCharacter, "\\" + regexCharacter));
        }

        public static string ConvertDateTimeToTextForFileNameUsage(
            DateTime dateTime, 
            bool useDotsAsDateSeparators = true, 
            bool isYearIncluded = true, 
            bool isMonthIncluded = true,
            bool isDayIncluded = true,
            bool isHourIncluded = true,
            bool isMinuteIncluded = true,
            bool isSecondIncluded = false,
            bool isMilliSecondIncluded = false)
        {
            StringBuilder stringBuilder = new StringBuilder();
            string separator = useDotsAsDateSeparators ? "." : string.Empty;

            if (isYearIncluded) 
                stringBuilder.Append(dateTime.Year + separator);
            if (isMonthIncluded)
                stringBuilder.Append(dateTime.Month < 10 ? "0" + dateTime.Month.ToString(CultureInfo.InvariantCulture) + separator : dateTime.Month.ToString(CultureInfo.InvariantCulture) + separator);
            if (isDayIncluded)
                stringBuilder.Append(dateTime.Day < 10 ? "0" + dateTime.Day.ToString(CultureInfo.InvariantCulture) + separator : dateTime.Day.ToString(CultureInfo.InvariantCulture) + separator);
            if (isHourIncluded)
                stringBuilder.Append(dateTime.Hour < 10 ? "0" + dateTime.Hour.ToString(CultureInfo.InvariantCulture) : dateTime.Hour.ToString(CultureInfo.InvariantCulture));
            if (isMinuteIncluded)
                stringBuilder.Append(dateTime.Minute < 10 ? "0" + dateTime.Minute.ToString(CultureInfo.InvariantCulture) : dateTime.Minute.ToString(CultureInfo.InvariantCulture));
            if (isSecondIncluded)
                stringBuilder.Append(dateTime.Second < 10 ? "0" + dateTime.Second.ToString(CultureInfo.InvariantCulture) : dateTime.Second.ToString(CultureInfo.InvariantCulture));
            if (isMilliSecondIncluded)
                if (dateTime.Millisecond < 100)
                    stringBuilder.Append(dateTime.Second < 10 ? "000" + dateTime.Millisecond.ToString(CultureInfo.InvariantCulture) : "00" + dateTime.Millisecond.ToString(CultureInfo.InvariantCulture));
                else
                    stringBuilder.Append(dateTime.Second < 1000 ? "0" + dateTime.Millisecond.ToString(CultureInfo.InvariantCulture) : dateTime.Millisecond.ToString(CultureInfo.InvariantCulture));

            return stringBuilder.ToString();
        }

        public static string ConvertDateTimeToTextForFileNameUsage(DateTime dateTime, LastUsedDateTimeComponent lastUsedDateTimeComponent)
        {
            switch (lastUsedDateTimeComponent)
            {
                case LastUsedDateTimeComponent.Default:
                    return ConvertDateTimeToTextForFileNameUsage(dateTime);
                case LastUsedDateTimeComponent.Year:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, false, false, false, false, false, false);
                case LastUsedDateTimeComponent.Month:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, false, false, false, false, false);
                case LastUsedDateTimeComponent.Day:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, true, false, false, false, false);
                case LastUsedDateTimeComponent.Hour:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, true, true, false, false, false);
                case LastUsedDateTimeComponent.Minute:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, true, true, true, false, false);
                case LastUsedDateTimeComponent.Second:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, true, true, true, true, false);
                case LastUsedDateTimeComponent.MilliSecond:
                    return ConvertDateTimeToTextForFileNameUsage(
                        dateTime, true, true, true, true, true, true, true, true);
                default:
                    throw new ArgumentOutOfRangeException("lastUsedDateTimeComponent");
            }
        }

        public static string AddDateTimeToFileName(string filePath, DateTime dateTime, string dateTimePrefix = "", string oldFileExtension = "", string newFileExtension = "")
        {
            return filePath.Remove(filePath.LastIndexOf(oldFileExtension, System.StringComparison.Ordinal)) + dateTimePrefix + ConvertDateTimeToTextForFileNameUsage(dateTime) + newFileExtension;
        }

        public static bool IsDigitsOnly(string textToCheck, bool nullOrEmptyValueReturnValue = true)
        {
            if (string.IsNullOrEmpty(textToCheck)) return nullOrEmptyValueReturnValue;

            foreach (char c in textToCheck)
            {
                if (c < '0' || c > '9') return false;
            }

            return true;
        }

        /// <summary>
        /// Gets last lines from text as list of strings.
        /// </summary>
        /// <param name="text"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        public static List<string> GetLastLines(string text, int count)
        {
            List<string> lines = new List<string>();
            Match match = Regex.Match(text, "^.*$", RegexOptions.Multiline | RegexOptions.RightToLeft);

            while (match.Success && lines.Count < count)
            {
                lines.Insert(0, match.Value);
                match = match.NextMatch();
            }

            return lines;
        }

        /// <summary>
        /// Gets the last line of text.
        /// </summary>
        /// <param name="text"></param>
        /// <param name="trimTrailingLineChanges"></param>
        /// <returns></returns>
        public static string GetLastLine(string text, bool trimTrailingLineChanges = true)
        {
            return trimTrailingLineChanges ? TextUtilities.GetLastLines(text.TrimEnd('\n'), 1).FirstOrDefault() : TextUtilities.GetLastLines(text, 1).FirstOrDefault();
        }

        public static string GenerateRandomString(int length, bool useWhiteSpaces = false)
        {
            Random random = new Random((int)DateTime.Now.Ticks);
            StringBuilder builder = new StringBuilder();
            char ch;

            for (int i = 0; i < length; i++)
            {
                ch = Convert.ToChar(Convert.ToInt32(Math.Floor(26 * random.NextDouble() + 65)));
                builder.Append(ch);
            }

            return builder.ToString();
        }

        public static string GenerateRandomStringWithWhiteSpaces(int words, int minWordLength, int maxWordLength)
        {
            Random random = new Random((int)DateTime.Now.Ticks);

            StringBuilder builder = new StringBuilder();
            string word;

            for (int i = 0; i < words; i++)
            {
                int wordLength = Convert.ToInt32(random.NextDouble() * (maxWordLength - minWordLength) + minWordLength);

                word = TextUtilities.GenerateRandomString(wordLength) + " ";
                builder.Append(word);
            }

            return builder.ToString().TrimEnd();
        }
    }
}
