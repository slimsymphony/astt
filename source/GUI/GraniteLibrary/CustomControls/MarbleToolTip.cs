using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MarbleLibrary.CustomControls
{
    using System.Windows;
    using System.Windows.Controls;

    public class MarbleToolTip : ToolTip
    {
        public string ToolTipTitle
        {
            get { return (string)GetValue(ToolTipTitleProperty); }
            set { SetValue(ToolTipTitleProperty, value); }
        }

        public static readonly DependencyProperty ToolTipTitleProperty = DependencyProperty.Register(
            "ToolTipTitle",
            typeof(string),
            typeof(MarbleToolTip),
            new PropertyMetadata(null));

        public string ToolTipDescription
        {
            get { return (string)GetValue(ToolTipDescriptionProperty); }
            set { SetValue(ToolTipDescriptionProperty, value); }
        }

        public static readonly DependencyProperty ToolTipDescriptionProperty = DependencyProperty.Register(
            "ToolTipDescription",
            typeof(string),
            typeof(MarbleToolTip),
            new PropertyMetadata(null));
    }
}
