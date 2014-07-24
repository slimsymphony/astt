﻿// -----------------------------------------------------------------------
// <copyright file="NumericTextBox.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.CustomControls
{
    using System;
    using System.Diagnostics;
    using System.Globalization;
    using System.Linq;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Data;
    using System.Windows.Input;
    using System.Windows.Media;

    using MarbleLibrary.Utilities;

    /// <summary>
    /// Number mode.
    /// </summary>
    public enum NumberMode
    {
        /// <summary>
        /// Number mode integer
        /// </summary>
        Int = 0,

        /// <summary>
        /// Number mode double
        /// </summary>
        Double = 1,

        /// <summary>
        /// Number mode float
        /// </summary>
        Float = 2
    }

    /// <summary>
    /// Numeric text box class.
    /// </summary>
    public class NumericTextBox : ClickSelectTextBox
    {
        /// <summary>
        /// Gets previous text value of the numeric text box.
        /// </summary>
        public string PreviousText { get; private set; }

        private Stopwatch stopwatch = new Stopwatch();

        private bool stopwatchFlag = true;

        private readonly LinearGradientBrush normalBackground = new LinearGradientBrush();

        private readonly LinearGradientBrush errorBackground = new LinearGradientBrush();

        private MinMaxValidationRule minMaxValidationRule = new MinMaxValidationRule();

        private NumberModeValidationRule numberModeValidationRule = new NumberModeValidationRule();

        private object originalToolTip;

        /// <summary>
        /// Initializes a new instance of the NumericTextBox class.
        /// </summary>
        public NumericTextBox()
        {
            this.normalBackground.GradientStops.Add(new GradientStop(Colors.White, 0.0));

            this.errorBackground.GradientStops.Add(new GradientStop(Color.FromRgb(255, 0, 0), 0.0));
            this.errorBackground.GradientStops.Add(new GradientStop(Colors.White, 1.0));
            this.errorBackground.StartPoint = new Point(0, 0);
            this.errorBackground.EndPoint = new Point(0, 1);

            this.updateValidationRule();

            Binding validationRuleBinding = new Binding();
            validationRuleBinding.ValidationRules.Add(this.numberModeValidationRule);
            validationRuleBinding.ValidationRules.Add(this.minMaxValidationRule);

            this.PreviewTextInput += new TextCompositionEventHandler(this.numericTextBox_PreviewTextInput);

            if (this.UseAutomaticValueCorrection)
            {
                //this.PreviewTextInput += new TextCompositionEventHandler(this.numericTextBox_PreviewTextInput);
                this.TextChanged += new TextChangedEventHandler(this.numericTextBox_TextChanged);
            }
            else
            {
                this.TextChanged += new TextChangedEventHandler(this.NumericTextBox_TextChanged);
            }

            this.MouseWheel += new MouseWheelEventHandler(this.numericTextBox_MouseWheel);
            this.LostFocus += new RoutedEventHandler(NumericTextBox_LostFocus);
        }

        void NumericTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (!this.isValid(this)) this.Text = this.PreviousText;
        }

        private bool isValid(DependencyObject obj)
        {
            // The dependency object is valid if it has no errors, and all of its children (that are dependency objects) are error-free.
            return !Validation.GetHasError(obj) &&
                LogicalTreeHelper.GetChildren(obj)
                .OfType<DependencyObject>()
                .All(child => isValid(child));
        }


        protected override void OnPreviewKeyDown(KeyEventArgs e)
        {
            if (e.Key == Key.Space)
            {
                e.Handled = true;
            }

            base.OnPreviewKeyDown(e);
        } 

        private void updateValidationRule()
        {
            this.minMaxValidationRule.Minimum = this.MinValue;
            this.minMaxValidationRule.Maximum = this.MaxValue;
            this.minMaxValidationRule.NumberMode = this.NumberMode;
            this.numberModeValidationRule.NumberMode = this.NumberMode;
        }

        private void NumericTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(this.Text))
                this.Text = this.MinValue.ToString();
            else if (this.Text.Length > this.MaxValue.ToString().Length)
                this.Text = this.MaxValue.ToString();

            if (this.originalToolTip == null && this.ToolTip != null)
                this.originalToolTip = this.ToolTip;

            string originalToolTipText = string.Empty;

            if (this.originalToolTip != null)
                originalToolTipText = this.originalToolTip.ToString();


            try
            {
                // Value is verified to be number matching the number mode.
                ValidationError validationErrorNumberMode = new ValidationError(this.numberModeValidationRule, this.GetBindingExpression(TextBox.TextProperty));
                ValidationResult validationResultNumberMode = this.numberModeValidationRule.Validate(this.Text, System.Threading.Thread.CurrentThread.CurrentCulture);

                if (!validationResultNumberMode.IsValid)
                {
                    validationErrorNumberMode.ErrorContent = validationResultNumberMode.ErrorContent;
                    Validation.MarkInvalid(this.GetBindingExpression(TextBox.TextProperty), validationErrorNumberMode);
                    //this.ToolTip = StringUtilities.CustomToolTipErrorText(validationErrorNumberMode.ErrorContent.ToString(), originalToolTipText);
                    return;
                }

                // If value matches the number mode, value is verified with the minimum and maximum validation rule.
                ValidationError validationError = new ValidationError(this.minMaxValidationRule, this.GetBindingExpression(TextBox.TextProperty));
                ValidationResult validationResult;

                switch (this.NumberMode)
                {
                    case NumberMode.Double:
                    case NumberMode.Float:
                    default:
                        validationResult = this.minMaxValidationRule.Validate(Convert.ToDouble(this.Text), System.Threading.Thread.CurrentThread.CurrentCulture);
                        break;

                    case NumberMode.Int:
                        validationResult = this.minMaxValidationRule.Validate(Convert.ToInt32(this.Text), System.Threading.Thread.CurrentThread.CurrentCulture);
                        break;
                }

                // If value is invalid, text box displays error graphics and error tool tip. Otherwise original tool tip is used.
                if (!validationResult.IsValid)
                {
                    validationError.ErrorContent = validationResult.ErrorContent;
                    Validation.MarkInvalid(this.GetBindingExpression(TextBox.TextProperty), validationError);
                    //this.ToolTip = StringUtilities.CustomToolTipErrorText(validationError.ErrorContent.ToString(), originalToolTipText);
                }
                else
                {
                    Validation.ClearInvalid(this.GetBindingExpression(TextBox.TextProperty));
                    this.ToolTip = this.originalToolTip;
                }
            }
            catch (Exception)
            {
                return;
            }
            finally
            {
                if (this.isValid(this))
                    this.PreviousText = this.Text;
            }
        }

        private void numericTextBox_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            if (!this.IsFocused) return;

            if (string.IsNullOrEmpty(this.Text)) this.Text = "0";

            switch (this.NumberMode)
            {
                case NumberMode.Int:
                    this.mouseWheelEventForNumberModeInt(Convert.ToInt32(this.Text), e);
                    break;
                case NumberMode.Double:
                case NumberMode.Float:
                    this.mouseWheelEventForNumberModeInt(Convert.ToDouble(this.Text), e);
                    break;
            }
        }

        private void mouseWheelEventForNumberModeInt(int value, MouseWheelEventArgs e)
        {
            //int value = Convert.ToInt32(this.Text);

            int newValue = Convert.ToInt32(this.applySpeedFactorToValueOnMouseWheelEvent(value, e));

            if (newValue > this.MaxValue)
                newValue = this.MaxValue;
            else if (newValue < this.MinValue)
                newValue = this.MinValue;

            this.Text = newValue.ToString();
        }

        private void mouseWheelEventForNumberModeInt(double value, MouseWheelEventArgs e)
        {
            //double value = Convert.ToInt32(this.Text);

            double newValue = Convert.ToDouble(this.applySpeedFactorToValueOnMouseWheelEvent(value, e));

            if (newValue > this.MaxValue)
                newValue = this.MaxValue;
            else if (newValue < this.MinValue)
                newValue = this.MinValue;

            this.Text = newValue.ToString();
        }

        private double applySpeedFactorToValueOnMouseWheelEvent(double value, MouseWheelEventArgs e)
        {
            int speedFactor = 400;
            double newValue = 0;

            if (this.NumberMode == NumberMode.Int) this.MouseWheelIncrement = (int)this.MouseWheelIncrement;

            if (Keyboard.IsKeyDown(Key.LeftCtrl) || Keyboard.IsKeyDown(Key.RightCtrl))
                speedFactor = speedFactor * 10;

            if (Keyboard.IsKeyDown(Key.LeftAlt) || Keyboard.IsKeyDown(Key.RightAlt))
                speedFactor = speedFactor * 10;

            if (this.stopwatchFlag)
            {
                this.stopwatch.Start();
                this.stopwatchFlag = false;
            }
            else
            {
                this.stopwatch.Stop();

                if (this.stopwatch.ElapsedMilliseconds > 0)
                    newValue = speedFactor / this.stopwatch.ElapsedMilliseconds;
                else 
                    newValue = speedFactor;

                if (e.Delta > 0)
                    value += (int)newValue * this.MouseWheelIncrement;
                else if (e.Delta < 0)
                    value -= (int)newValue * this.MouseWheelIncrement;

                this.stopwatch.Reset();
                this.stopwatch.Start();
                this.stopwatchFlag = true;
            }

            if (this.NumberMode == NumberMode.Double && (newValue < 1 && newValue > -1) && this.stopwatchFlag)
            {
                if (e.Delta > 0)
                    value += this.MouseWheelIncrement;
                else if (e.Delta < 0)
                    value -= this.MouseWheelIncrement;
            }
            else if (this.NumberMode == NumberMode.Int)
            {
                if (e.Delta > 0)
                    value += (int)this.MouseWheelIncrement;
                else if (e.Delta < 0)
                    value -= (int)this.MouseWheelIncrement;
            }

            return value;
        }


        /// <summary>
        /// Gets or sets number mode for the numeric text box.
        /// </summary>
        public NumberMode NumberMode
        {
            get { return (NumberMode)this.GetValue(NumberModeProperty); }
            set
            {
                this.SetValue(NumberModeProperty, value);
                this.minMaxValidationRule.NumberMode = value;
                this.numberModeValidationRule.NumberMode = value;
            }
        }

        /// <summary>
        /// Number mode dependency property.
        /// </summary>
        public static readonly DependencyProperty NumberModeProperty = DependencyProperty.Register(
            "NumberMode",
            typeof(NumberMode),
            typeof(NumericTextBox),
            new PropertyMetadata(NumberMode.Double, new PropertyChangedCallback(OnNumberModePropertyChanged)));

        /// <summary>
        /// Method which is called when NumberMode property is changed.
        /// </summary>
        /// <param name="d">Depency object.</param>
        /// <param name="e">Depency property changed event arguments.</param>
        private static void OnNumberModePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NumericTextBox numericTextBox = d as NumericTextBox;

            NumberMode numberMode = (NumberMode)e.NewValue;
            numericTextBox.updateValidationRule();
        }

        /// <summary>
        /// Gets or sets a value indicating whether [use automatic value correction].
        /// </summary>
        /// <value>
        /// <c>true</c> if [use automatic value correction]; otherwise, <c>false</c>.
        /// </value>
        public bool UseAutomaticValueCorrection { get; set; }

        /// <summary>
        /// Use automatic value correction dependency property.
        /// </summary>
        public static readonly DependencyProperty UseAutomaticValueCorrectionProperty = DependencyProperty.Register(
            "UseAutomaticValueCorrection",
            typeof(bool),
            typeof(NumericTextBox),
            new PropertyMetadata(false, new PropertyChangedCallback(OnUseAutomaticValueCorrectionPropertyChanged)));

        /// <summary>
        /// Method which is called when UseAutomaticValueCorrection property is changed.
        /// </summary>
        /// <param name="d">Depency object.</param>
        /// <param name="e">Depency property changed event arguments.</param>
        private static void OnUseAutomaticValueCorrectionPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NumericTextBox numericTextBox = d as NumericTextBox;

            numericTextBox.updateValidationRule();
        }

        /// <summary>
        /// Gets or sets max value for the numeric text box.
        /// </summary>
        public int MaxValue
        {
            get { return (int)this.GetValue(MaxValueProperty); }
            set
            {
                this.SetValue(MaxValueProperty, value);
                this.minMaxValidationRule.Maximum = value;
            }
        }

        /// <summary>
        /// Max value dependency property.
        /// </summary>
        public static readonly DependencyProperty MaxValueProperty = DependencyProperty.Register(
            "MaxValue",
            typeof(int),
            typeof(NumericTextBox),
            new PropertyMetadata(int.MaxValue, new PropertyChangedCallback(OnMaxValuePropertyChanged)));

        /// <summary>
        /// Method which is called when MaxValue property is changed.
        /// </summary>
        /// <param name="d">Depency object.</param>
        /// <param name="e">Depency property changed event arguments.</param>
        private static void OnMaxValuePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NumericTextBox numericTextBox = d as NumericTextBox;

            int maximumValue = (int)e.NewValue;
            numericTextBox.updateValidationRule();
        }

        /// <summary>
        /// Gets or sets min value for the numeric text box.
        /// </summary>
        public int MinValue
        {
            get { return (int)this.GetValue(MinValueProperty); }
            set
            {
                this.SetValue(MinValueProperty, value);
                this.minMaxValidationRule.Minimum = value;
            }
        }

        /// <summary>
        /// Min value dependency property.
        /// </summary>
        public static readonly DependencyProperty MinValueProperty = DependencyProperty.Register(
            "MinValue",
            typeof(int),
            typeof(NumericTextBox),
            new PropertyMetadata(int.MinValue, new PropertyChangedCallback(OnMinValuePropertyChanged)));

        /// <summary>
        /// Method which is called when MinValue property is changed.
        /// </summary>
        /// <param name="d">Depency object.</param>
        /// <param name="e">Depency property changed event arguments.</param>
        private static void OnMinValuePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NumericTextBox numericTextBox = d as NumericTextBox;

            int maximumValue = (int)e.NewValue;
            numericTextBox.updateValidationRule();
        }

        /// <summary>
        /// Gets or sets mouse wheel increment for NumericTextBox. Mouse wheel increment defines how much current value is increased/decreased on a single mouse wheel move.
        /// </summary>
        public double MouseWheelIncrement
        {
            get { return (double)this.GetValue(MouseWheelIncrementProperty); }
            set { this.SetValue(MouseWheelIncrementProperty, value); }
        }

        /// <summary>
        /// Mouse wheel increment dependency property.
        /// </summary>
        public static readonly DependencyProperty MouseWheelIncrementProperty = DependencyProperty.Register(
            "MouseWheelIncrement",
            typeof(double),
            typeof(NumericTextBox),
            new PropertyMetadata(1d, new PropertyChangedCallback(OnMouseWheelIncrementPropertyChanged)));

        /// <summary>
        /// Method which is called when MouseWheelIncrement property is changed.
        /// </summary>
        /// <param name="d">Depency object.</param>
        /// <param name="e">Depency property changed event arguments.</param>
        private static void OnMouseWheelIncrementPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e) { }

        /// <summary>
        /// Increases numeric text box value.
        /// </summary>
        /// <param name="value">Int value to add to current value.</param>
        public void IncreaseValue(int value)
        {
            int increasedValue = this.GetValueAsInt() + value;

            if (increasedValue > this.MaxValue || increasedValue < this.MinValue) return;

            this.Text = (increasedValue).ToString();
        }

        /// <summary>
        /// Increases numeric text box value.
        /// </summary>
        /// <param name="value">Double value to add to current value.</param>
        public void IncreaseValue(double value)
        {
            double increasedValue = this.GetValueAsDouble() + value;

            if (increasedValue > this.MaxValue || increasedValue < this.MinValue) return;

            this.Text = (increasedValue).ToString();
        }

        /// <summary>
        /// Increases numeric text box value.
        /// </summary>
        /// <param name="value">Float value to add to current value.</param>
        public void IncreaseValue(float value)
        {
            float increasedValue = this.GetValueAsFloat() + value;

            if (increasedValue > this.MaxValue || increasedValue < this.MinValue) return;

            this.Text = (increasedValue).ToString();
        }

        /// <summary>
        /// Decreases numeric text box value.
        /// </summary>
        /// <param name="value">Int value to decrease from current value.</param>
        public void DecreaseValue(int value)
        {
            int decreasedValue = this.GetValueAsInt() - value;

            if (decreasedValue > this.MaxValue || decreasedValue < this.MinValue) return;

            this.Text = (decreasedValue).ToString();
        }

        /// <summary>
        /// Decreases numeric text box value.
        /// </summary>
        /// <param name="value">Double value to decrease from current value.</param>
        public void DecreaseValue(double value)
        {
            double decreasedValue = this.GetValueAsDouble() - value;

            if (decreasedValue > this.MaxValue || decreasedValue < this.MinValue) return;

            this.Text = (decreasedValue).ToString();
        }

        /// <summary>
        /// Decreases numeric text box value.
        /// </summary>
        /// <param name="value">Float value to decrease from current value.</param>
        public void DecreaseValue(float value)
        {
            float decreasedValue = this.GetValueAsFloat() - value;

            if (decreasedValue > this.MaxValue || decreasedValue < this.MinValue) return;

            this.Text = (decreasedValue).ToString();
        }

        /// <summary>
        /// Gets numeric text box value as int.
        /// </summary>
        /// <returns>Numeric text box value as int.</returns>
        public int GetValueAsInt()
        {
            int returnValue;
            if (int.TryParse(this.Text, out returnValue))
                return returnValue;
            throw new NullReferenceException();
        }

        /// <summary>
        /// Gets numeric text box value as double.
        /// </summary>
        /// <returns>Numeric text box value as double.</returns>
        public double GetValueAsDouble()
        {
            double returnValue;
            if (double.TryParse(this.Text, out returnValue))
                return returnValue;
            throw new NullReferenceException();
        }

        /// <summary>
        /// Gets numeric text box value as float.
        /// </summary>
        /// <returns>Numeric text box value as float.</returns>
        public float GetValueAsFloat()
        {
            float returnValue;
            if (float.TryParse(this.Text, out returnValue))
                return returnValue;
            throw new NullReferenceException();
        }

        /// <summary>
        /// Previews text input for the numeric text box.
        /// </summary>
        /// <param name="sender">Sender object.</param>
        /// <param name="e">Text composition event arguments.</param>
        private void numericTextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            if (e == null || e.Text == null || e.Text.Length <= 0) return;

            // Negative and Positive signs can only be the first character.
            if (this.CaretIndex > 0 &&
                (e.Text[0].ToString(CultureInfo.InvariantCulture) == System.Globalization.NumberFormatInfo.CurrentInfo.NegativeSign ||
                 e.Text[0].ToString(CultureInfo.InvariantCulture) == System.Globalization.NumberFormatInfo.CurrentInfo.PositiveSign))
            {
                e.Handled = true;
                return;
            }

            // Decimal Separator cannot be the first character.
            if (this.CaretIndex == 0 &&
                e.Text[0].ToString(CultureInfo.InvariantCulture) == System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator)
            {
                e.Handled = true;
                return;
            }

            foreach (char c in e.Text)
            {
                if ((!char.IsDigit(c) && 
                    c.ToString(CultureInfo.InvariantCulture) != System.Globalization.NumberFormatInfo.CurrentInfo.NegativeSign &&
                    c.ToString(CultureInfo.InvariantCulture) != System.Globalization.NumberFormatInfo.CurrentInfo.PositiveSign) ||
                    (c.ToString(CultureInfo.InvariantCulture) == System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator && this.NumberMode == NumberMode.Int))
                {
                    e.Handled = true;
                    return;
                }
            }

            ////int caretIndex = this.CaretIndex;
            ////string newText = this.Text;
            ////int selectionStart = this.SelectionStart;

            ////newText = newText.Insert(caretIndex, e.Text);

            ////switch (this.NumberMode)
            ////{
            ////    case NumberMode.Int:
            ////        if (!ErrorCheckingUtilities.VerifyStringAsInt(newText, true)) e.Handled = true;
            ////        break;

            ////    case NumberMode.Double:
            ////        if (!ErrorCheckingUtilities.VerifyStringAsDouble(newText, true)) e.Handled = true;
            ////        break;

            ////    case NumberMode.Float:
            ////        if (!ErrorCheckingUtilities.VerifyStringAsFloat(newText, true)) e.Handled = true;
            ////        break;
            ////}

            ////if (e.Handled && !this.UseAutomaticValueCorrection)
            ////{
            ////    this.Background = this.errorBackground;
            ////    e.Handled = false;

            ////}

            //if (this.UseAutomaticValueCorrection)
            //{
            //    if (this.PreviousText == null) this.PreviousText = this.Text;
            //    if (newText == this.PreviousText) return;

            //    if (newText.StartsWith("0") && this.Text.Length > 1 && this.UseAutomaticValueCorrection)
            //    {
            //        if (this.NumberMode == UserControls.NumberMode.Int)
            //            newText = this.Text.Remove(0, 1);
            //        else if (
            //            !newText.StartsWith("0" +
            //                                System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator))
            //            newText = this.Text.Remove(0, 1);
            //    }

            //    if (newText.Contains(" "))
            //        newText = this.Text.Replace(" ", "");

            //    newText = this.verifyNumberMode(newText);

            //    if (string.IsNullOrEmpty(newText) && this.UseAutomaticValueCorrection)
            //        newText = this.PreviousText;

            //    // Text value of the text box is set to the Tag-property. This way previous value is found in the Tag.
            //    this.PreviousText = newText;
            //    //this.Text = newText;

            //    if (this.UseAutomaticValueCorrection)
            //    {
            //        this.CaretIndex = 1;
            //        this.SelectionStart = selectionStart;
            //    }
            //}
            //else
            //{
            //    newText = this.verifyNumberMode(newText);
            //}

            //this.Text = newText;

            base.OnPreviewTextInput(e);
        }

        /// <summary>
        /// Verifys changes for the numeric text box.
        /// </summary>
        /// <param name="sender">Sender object.</param>
        /// <param name="e">Text changed event arguments.</param>
        private void numericTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (this.PreviousText == null) this.PreviousText = this.Text;
            if (this.Text == this.PreviousText) return;

            int caretIndex = this.CaretIndex;
            string newText = this.Text;
            int selectionStart = this.SelectionStart;

            if (newText.StartsWith("0") && this.Text.Length > 1 && this.UseAutomaticValueCorrection)
            {
                if (this.NumberMode == NumberMode.Int)
                    newText = this.Text.Remove(0, 1);
                else if (!newText.StartsWith("0" + System.Globalization.NumberFormatInfo.CurrentInfo.NumberDecimalSeparator))
                    newText = this.Text.Remove(0, 1);
            }

            if (newText.Contains(" "))
                newText = this.Text.Replace(" ", "");

            newText = this.verifyNumberMode(newText);

            if (string.IsNullOrEmpty(newText) && this.UseAutomaticValueCorrection)
                newText = this.PreviousText;

            // Text value of the text box is set to the Tag-property. This way previous value is found in the Tag.
            
            if (this.isValid(this))
                this.PreviousText = newText;

            this.Text = newText;

            if (this.UseAutomaticValueCorrection)
            {
                this.CaretIndex = 1;
                this.SelectionStart = selectionStart;
            }

            base.OnTextChanged(e);
        }

        /// <summary>
        /// Verifies number mode of the new text.
        /// </summary>
        /// <param name="newText">New text string.</param>
        /// <returns>Possibly modified new text.</returns>
        private string verifyNumberMode(string newText)
        {
            bool containsErrors = false;

            switch (this.NumberMode)
            {
                case NumberMode.Int:
                    int textAsInt;
                    if (!int.TryParse(newText, out textAsInt))
                        containsErrors = true;
                    if (textAsInt > this.MaxValue || textAsInt < this.MinValue)
                        containsErrors = true;
                    break;

                case NumberMode.Double:
                    double textAsDouble;
                    if (!double.TryParse(newText, out textAsDouble))
                        containsErrors = true;
                    if (textAsDouble > this.MaxValue || textAsDouble < this.MinValue)
                        containsErrors = true;
                    break;

                case NumberMode.Float:
                    float textAsFloat;
                    if (!float.TryParse(newText, out textAsFloat))
                        containsErrors = true;
                    if (textAsFloat > this.MaxValue || textAsFloat < this.MinValue)
                        containsErrors = true;
                    break;

                default:
                    break;
            }

            if (containsErrors && this.UseAutomaticValueCorrection)
                newText = this.PreviousText;

            this.Background = containsErrors ? this.errorBackground : this.normalBackground;

            return newText;
        }
    }

    public class MinMaxValidationRule : ValidationRule
    {
        /// <summary>
        /// Gets or sets the minimum.
        /// </summary>
        /// <value>
        /// The minimum.
        /// </value>
        public int Minimum { get; set; }

        /// <summary>
        /// Gets or sets the maximum.
        /// </summary>
        /// <value>
        /// The maximum.
        /// </value>
        public int Maximum { get; set; }

        /// <summary>
        /// Gets or sets the number mode.
        /// </summary>
        /// <value>
        /// The number mode.
        /// </value>
        public NumberMode NumberMode { get; set; }

        /// <summary>
        /// When overridden in a derived class, performs validation checks on a value.
        /// </summary>
        /// <param name="value">The value from the binding target to check.</param>
        /// <param name="cultureInfo">The culture to use in this rule.</param>
        /// <returns>
        /// A <see cref="T:System.Windows.Controls.ValidationResult"/> object.
        /// </returns>
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            if (this.Minimum > this.Maximum || this.Maximum < this.Minimum)
                throw new Exception("Minimum cannot be bigger than maximum and maximum cannot be smaller than minimum!");

            switch (this.NumberMode)
            {
                case NumberMode.Double:
                    if (!(value is double)) return new ValidationResult(false, "Value is not a double!");
                    if ((double)value < this.Minimum || (double)value > this.Maximum)
                        return new ValidationResult(false, "Value is not in the limits of minimum and maximum!");
                    break;

                case NumberMode.Int:
                    if (!(value is int)) return new ValidationResult(false, "Value is not an integer!");
                    if ((int)value < this.Minimum || (int)value > this.Maximum)
                        return new ValidationResult(false, "Value is not in the limits of minimum and maximum!");
                    break;

                case NumberMode.Float:
                    if (!(value is float)) return new ValidationResult(false, "Value is not a float!");
                    if ((float)value < this.Minimum || (float)value > this.Maximum)
                        return new ValidationResult(false, "Value is not in the limits of minimum and maximum!");
                    break;
            }

            return new ValidationResult(true, null);
        }
    }

    public class NumberModeValidationRule : ValidationRule
    {
        /// <summary>
        /// Gets or sets the number mode.
        /// </summary>
        /// <value>
        /// The number mode.
        /// </value>
        public NumberMode NumberMode { get; set; }

        /// <summary>
        /// When overridden in a derived class, performs validation checks on a value.
        /// </summary>
        /// <param name="value">The value from the binding target to check.</param>
        /// <param name="cultureInfo">The culture to use in this rule.</param>
        /// <returns>
        /// A <see cref="T:System.Windows.Controls.ValidationResult"/> object.
        /// </returns>
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            switch (this.NumberMode)
            {
                case NumberMode.Double:
                    if (!ErrorCheckingUtilities.VerifyStringAsDouble(value.ToString(), true))
                        return new ValidationResult(false, "Value is not a double!");
                    break;

                case NumberMode.Int:
                    if (!ErrorCheckingUtilities.VerifyStringAsInt(value.ToString(), true))
                        return new ValidationResult(false, "Value is not an integer!");
                    break;

                case NumberMode.Float:
                    if (!ErrorCheckingUtilities.VerifyStringAsFloat(value.ToString(), true))
                        return new ValidationResult(false, "Value is not a float!");
                    break;
            }

            return new ValidationResult(true, null);
        }
    }
}
