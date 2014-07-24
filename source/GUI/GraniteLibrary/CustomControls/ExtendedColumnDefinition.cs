using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MarbleLibrary.CustomControls
{
    using System.Windows;
    using System.Windows.Controls;

    /// <summary>
    /// Extends ColumnDefinition by adding and allowing binding to visibility property.
    /// </summary>
    public class ColumnDefinitionExtended : ColumnDefinition
    {
        public static DependencyProperty VisibleProperty;

        /// <summary>
        /// Gets or sets the visible property.
        /// </summary>
        public Boolean Visible
        {
            get { return (Boolean)GetValue(VisibleProperty); }
            set { SetValue(VisibleProperty, value); }
        }

        static ColumnDefinitionExtended()
        {
            VisibleProperty = DependencyProperty.Register("Visible",
                typeof(Boolean),
                typeof(ColumnDefinitionExtended),
                new PropertyMetadata(true, new PropertyChangedCallback(OnVisibleChanged)));

            ColumnDefinition.WidthProperty.OverrideMetadata(typeof(ColumnDefinitionExtended),
                new FrameworkPropertyMetadata(new GridLength(1, GridUnitType.Star), null,
                    new CoerceValueCallback(CoerceWidth)));
        }

        public static void SetVisible(DependencyObject obj, Boolean nVisible)
        {
            obj.SetValue(VisibleProperty, nVisible);
        }

        public static Boolean GetVisible(DependencyObject obj)
        {
            return (Boolean)obj.GetValue(VisibleProperty);
        }

        static void OnVisibleChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            obj.CoerceValue(ColumnDefinition.WidthProperty);
        }

        static Object CoerceWidth(DependencyObject obj, Object nValue)
        {
            return (((ColumnDefinitionExtended)obj).Visible) ? nValue : new GridLength(0);
        }
    }
}
