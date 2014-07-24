// -----------------------------------------------------------------------
// <copyright file="GuiUtilities.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.Utilities
{
    using System;
    using System.IO;
    using System.Windows;
    using System.Windows.Automation.Peers;
    using System.Windows.Automation.Provider;
    using System.Windows.Controls;
    using System.Windows.Controls.Primitives;
    using System.Windows.Data;
    using System.Windows.Input;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;

    using Microsoft.Windows.Automation.Peers;
    using Microsoft.Windows.Controls.Ribbon;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class GuiUtilities
    {
        /// <summary>
        /// Gets version of the operating system like "Windows XP".
        /// </summary>
        /// <returns>Operating system version as a string.</returns>
        public static string GetOperatingSystemVersion()
        {
            OperatingSystem operatingSystem = Environment.OSVersion;
            string osName = string.Empty;

            if (operatingSystem.Platform == PlatformID.Win32Windows)
            {
                switch (operatingSystem.Version.Minor)
                {
                    case 0:
                        osName = "Windows 95";
                        break;
                    case 10:
                        osName = operatingSystem.Version.Revision.ToString() == "2222A" ? "Windows 98SE" : "Windows 98";
                        break;
                    case 90:
                        osName = "Windows ME";
                        break;
                }
            }
            else if (operatingSystem.Platform == PlatformID.Win32NT)
            {
                switch (operatingSystem.Version.Major)
                {
                    case 3:
                        osName = "Windows NT 3.51";
                        break;
                    case 4:
                        osName = "Windows NT 4.0";
                        break;
                    case 5:
                        osName = operatingSystem.Version.Minor == 0 ? "Windows 2000" : "Windows XP";
                        break;
                    case 6:
                        osName = operatingSystem.Version.Minor == 0 ? "Windows Vista" : "Windows 7";
                        break;
                }
            }

            return osName;
        }

        /// <summary>
        /// Gets whether operating system version supports large (256x256) icons.
        /// </summary>
        /// <returns>True if supported.</returns>
        public static bool HasOperatingSystemSupportForLargeIcons()
        {
            string osVersion = GetOperatingSystemVersion();
            return osVersion == "Windows 7" || osVersion == "Windows Vista";
        }

        /// <summary>
        /// Performs click to button. This is similar to PerformClick method in Windows Forms.
        /// </summary>
        /// <param name="button">Button to be clicked.</param>
        public static void PerformClick(Button button)
        {
            // Click can not be performed to control which is not enabled.
            if (!button.IsEnabled) return;

            ButtonAutomationPeer buttonAutomationPeer = new ButtonAutomationPeer(button);
            IInvokeProvider invokeProvider =
                buttonAutomationPeer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;

            if (invokeProvider != null) invokeProvider.Invoke();
        }

        /// <summary>
        /// Performs click to checkbox. This is similar to PerformClick method in Windows Forms.
        /// </summary>
        /// <param name="checkBox">CheckBox to be clicked.</param>
        public static void PerformClick(CheckBox checkBox)
        {
            CheckBoxAutomationPeer checkBoxAutomationPeer = new CheckBoxAutomationPeer(checkBox);
            IInvokeProvider invokeProvider =
                checkBoxAutomationPeer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;

            if (invokeProvider != null) invokeProvider.Invoke();
        }

        /// <summary>
        /// Performs click to menu item. This is similar to PerformClick method in Windows Forms.
        /// </summary>
        /// <param name="menuItem">MenuItem to be clicked.</param>
        public static void PerformClick(MenuItem menuItem)
        {
            MenuItemAutomationPeer menuItemAutomationPeer = new MenuItemAutomationPeer(menuItem);
            IInvokeProvider invokeProvider =
                menuItemAutomationPeer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;

            if (invokeProvider != null) invokeProvider.Invoke();
        }

        /// <summary>
        /// Performs click to toggle button. This is similar to PerformClick method in Windows Forms.
        /// </summary>
        /// <param name="menuItem">MenuItem to be clicked.</param>
        public static void PerformClick(ToggleButton toggleButton)
        {
            ToggleButtonAutomationPeer toggleButtonAutomationPeerAutomationPeer = new ToggleButtonAutomationPeer(toggleButton);
            IInvokeProvider invokeProvider =
                toggleButtonAutomationPeerAutomationPeer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;

            if (invokeProvider != null) invokeProvider.Invoke();
        }

        /// <summary>
        /// Performs click to ribbon tab. This is similar to PerformClick method in Windows Forms.
        /// </summary>
        /// <param name="menuItem">MenuItem to be clicked.</param>
        public static void PerformClick(RibbonTab ribbonTab)
        {
            RibbonTabAutomationPeer ribbonTabAutomationPeerAutomationPeer = new RibbonTabAutomationPeer(ribbonTab);
            IInvokeProvider invokeProvider =
                ribbonTabAutomationPeerAutomationPeer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;

            if (invokeProvider != null) invokeProvider.Invoke();
        }

        private delegate void NoArgDelegate();
        
        /// <summary>
        /// Forces DependencyObject to update itself.
        /// </summary>
        /// <param name="obj">Dependency object.</param>
        public static void Refresh(DependencyObject obj)
        {
            obj.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.ApplicationIdle, (NoArgDelegate)delegate { });
        }

        /// <summary>
        /// Get descendant by type.
        /// </summary>
        /// <param name="element">Element with Visual type.</param>
        /// <param name="type">Type of the element should be.</param>
        /// <param name="name">Name of the element.</param>
        /// <returns>Found element with Visual type.</returns>
        public static Visual GetDescendantByType(Visual element, Type type, string name)
        {
            if (element == null) return null;
            if (element.GetType() == type)
            {
                FrameworkElement fe = element as FrameworkElement;
                if (fe != null)
                {
                    if (fe.Name == name)
                    {
                        return fe;
                    }
                }
            }

            Visual foundElement = null;
            if (element is FrameworkElement)
                (element as FrameworkElement).ApplyTemplate();
            for (int i = 0;
                i < VisualTreeHelper.GetChildrenCount(element); i++)
            {
                Visual visual = VisualTreeHelper.GetChild(element, i) as Visual;
                foundElement = GetDescendantByType(visual, type, name);
                if (foundElement != null)
                    break;
            }

            return foundElement;
        }

        /// <summary>
        /// Finds the parent of the dependency object.
        /// </summary>
        /// <param name="child">Child DependencyObject which parent need to be found.</param>
        public static object FindParent(DependencyObject child, Type parentTypeToFind)
        {
            DependencyObject parent = VisualTreeHelper.GetParent(child);

            if (parent == null) return null;

            if (parent.GetType() != parentTypeToFind)
            {
                DependencyObject parentOfParent = FindParent(parent, parentTypeToFind) as DependencyObject;

                if (parentOfParent == null) return null;

                if (parentOfParent.GetType() == parentTypeToFind) return parentOfParent;
            }
            else
            {
                return parent;
            }

            return null;
        }

        /// <summary>
        /// Finds the visual child of the dependency object.
        /// </summary>
        /// <typeparam name="TChild">Type of the child dependency object to find.</typeparam>
        /// <param name="obj">Dependency object where the child is searched.</param>
        /// <returns>Child dependency object with searched type.</returns>
        public static TChild FindVisualChild<TChild>(DependencyObject obj) where TChild : DependencyObject
        {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(obj); i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(obj, i);

                if (child != null && child is TChild) return (TChild)child;

                TChild childOfChild = FindVisualChild<TChild>(child);

                if (childOfChild != null) return childOfChild;
            }

            return null;
        }

        /// <summary>
        /// Triggers an update of the source on the current control that has keyboard focus.
        /// </summary>
        /// <remarks><para>In situations where for instance you edit a TextBox and then click a Save button with the mouse, 
        /// the TextBox will not update its source since the TextBox does not lose keyboard focus. Calling this method 
        /// ensures that any control that has keyboard focus is triggered to update its source, thereby ensuring that 
        /// the source is updated prior to performing the save. There may be similar situations, other than a Save, 
        /// where this method should be called, if a similar type of scenario can arise.
        /// </para>
        /// <para>This method can be called even when there is no control that has keyboard focus, in which case calling this
        /// method will have no effect.</para>
        /// </remarks>
        public static void UpdateSourceOnControlWithKeyboardFocus()
        {
            // Determine whether the focused element is a textbox
            TextBox textBox = Keyboard.FocusedElement as TextBox;

            if (textBox != null)
            {
                // Get the binding on this control
                BindingExpression bindingExpression = textBox.GetBindingExpression(TextBox.TextProperty);

                if (bindingExpression != null)
                {
                    // Make the text box updates it source
                    bindingExpression.UpdateSource();
                }
            }

            // Trigger a keyboard focus change so that any type of property control having its value changed will update its source
            Keyboard.Focus(null);
        }

        /// <summary>
        /// Gets a JPG "screenshot" of the current UIElement
        /// </summary>
        /// <param name="source">UIElement to screenshot</param>
        /// <param name="scale">Scale to render the screenshot</param>
        /// <param name="quality">JPG Quality</param>
        /// <returns>Byte array of JPG data</returns>
        public static byte[] GetJpgImage(this UIElement source, double scale, int quality)
        {
            double actualHeight = source.RenderSize.Height;
            double actualWidth = source.RenderSize.Width;
            double renderHeight = actualHeight * scale;
            double renderWidth = actualWidth * scale;

            if (actualHeight.Equals(0) || actualWidth.Equals(0) || scale.Equals(0)) return null;

            RenderTargetBitmap renderTarget = new RenderTargetBitmap((int)renderWidth, (int)renderHeight, 96, 96, PixelFormats.Default);
            VisualBrush sourceBrush = new VisualBrush(source);
            DrawingVisual drawingVisual = new DrawingVisual();
            DrawingContext drawingContext = drawingVisual.RenderOpen();

            using (drawingContext)
            {
                drawingContext.PushTransform(new ScaleTransform((int)renderWidth / actualWidth, (int)renderHeight / actualHeight));
                drawingContext.DrawRectangle(sourceBrush, null, new Rect(new Point(0, 0), new Point(actualWidth, actualHeight)));
            }

            renderTarget.Render(drawingVisual);

            JpegBitmapEncoder jpgEncoder = new JpegBitmapEncoder { QualityLevel = quality };
            jpgEncoder.Frames.Add(BitmapFrame.Create(renderTarget));

            byte[] imageArray;

            using (MemoryStream outputStream = new MemoryStream())
            {
                jpgEncoder.Save(outputStream);
                imageArray = outputStream.ToArray();
            }

            return imageArray;
        }

        /// <summary>
        /// Gets a JPG "screenshot" of the current UIElement
        /// </summary>
        /// <param name="source">UIElement to screenshot</param>
        /// <param name="scale">Scale to render the screenshot</param>
        /// <param name="quality">JPG Quality</param>
        /// <returns>Byte array of JPG data</returns>
        public static byte[] GetPngImage(this UIElement source, double scale)
        {
            double actualHeight = source.RenderSize.Height;
            double actualWidth = source.RenderSize.Width;
            double renderHeight = actualHeight * scale;
            double renderWidth = actualWidth * scale;

            RenderTargetBitmap renderTarget = new RenderTargetBitmap((int)renderWidth, (int)renderHeight, 96, 96, PixelFormats.Default);
            VisualBrush sourceBrush = new VisualBrush(source);
            DrawingVisual drawingVisual = new DrawingVisual();
            DrawingContext drawingContext = drawingVisual.RenderOpen();
            
            using (drawingContext)
            {
                drawingContext.PushTransform(new ScaleTransform((int)renderWidth / actualWidth, (int)renderHeight / actualHeight));
                drawingContext.DrawRectangle(sourceBrush, null, new Rect(new Point(0, 0), new Point(actualWidth, actualHeight)));
            }

            renderTarget.Render(drawingVisual);

            PngBitmapEncoder pngEncoder = new PngBitmapEncoder();
            pngEncoder.Frames.Add(BitmapFrame.Create(renderTarget));

            byte[] imageArray;

            using (MemoryStream outputStream = new MemoryStream())
            {
                pngEncoder.Save(outputStream);
                imageArray = outputStream.ToArray();
            }

            return imageArray;
        }
    }
}
