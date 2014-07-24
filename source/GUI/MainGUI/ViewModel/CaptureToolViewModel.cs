// -----------------------------------------------------------------------
// <copyright file="CaptureToolViewModel.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

using System.Diagnostics;
using System.IO;
using System.Windows.Input;
using MarbleLibrary.Commands;

namespace Marble.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Linq;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using System.Windows.Shapes;
    using System.Xml.Linq;

    using Marble.Communication;
    using Marble.Model;
    using Marble.Utilities;
    using Marble.Views;

    using MarbleLibrary.Utilities;

    public enum ElementSelectionMethod
    {
        BestPossible = 0,
        Description = 1,
        ResourceId = 2,
        Text = 3,
        IndexTree = 4,
        Coordinates = 5
    }

    public enum SelectionCommandType
    {
        Select = 0,
        SelectLong = 1,
        Drag = 2,
    }

    public class ElementSelectionParams
    {
        public int Index { get; set; }

        public bool IsLongSelect { get; set; }

        public ElementSelectionMethod SelectionMethod { get; set; }

        public string Parameter { get; set; }
    }

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public class CaptureToolViewModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CaptureToolViewModel"/> class.
        /// </summary>
        public CaptureToolViewModel()
        {
            this.DisplayElements = new ObservableCollectionAdv<DisplayElement>();
            this.GridWidth = 50;
            this.DefaultSelectionMethod = ElementSelectionMethod.BestPossible;
        }

        /// <summary>
        /// Selects element.
        /// </summary>
        /// <param name="elementSelectionParams">Element selection parameters.</param>
        public void ElementSelect(ElementSelectionParams elementSelectionParams)
        {
            switch (elementSelectionParams.SelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    break;
                case ElementSelectionMethod.Description:
                    this.SelectByDescription(elementSelectionParams);
                    break;
                case ElementSelectionMethod.ResourceId:
                    this.SelectByResourceId(elementSelectionParams);
                    break;
                case ElementSelectionMethod.Text:
                    this.SelectByText(elementSelectionParams);
                    break;
                case ElementSelectionMethod.IndexTree:
                    this.SelectByIndexTree(elementSelectionParams);
                    break;
                case ElementSelectionMethod.Coordinates:
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        /// <summary>
        /// Gets element count using element selection parameters.
        /// </summary>
        /// <param name="elementSelectionParams">Element selection parameters.</param>
        /// <returns>Element count.</returns>
        public int GetElementCount(ElementSelectionParams elementSelectionParams)
        {
            if (string.IsNullOrEmpty(elementSelectionParams.Parameter)) return 0;

            switch (elementSelectionParams.SelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return -1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(displayElement => displayElement.Description == elementSelectionParams.Parameter);
                case ElementSelectionMethod.ResourceId:
                    return this.DisplayElements.Count(displayElement => displayElement.ResourceId == elementSelectionParams.Parameter);
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(displayElement => displayElement.Text == elementSelectionParams.Parameter);
                case ElementSelectionMethod.IndexTree:
                    return this.DisplayElements.Count(displayElement => displayElement.IndexTree == elementSelectionParams.Parameter);
                case ElementSelectionMethod.Coordinates:
                    return this.DisplayElements.Count(displayElement => displayElement.Rectangle.ToString() == elementSelectionParams.Parameter);
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        /// <summary>
        /// Gets the index of the current display element.
        /// </summary>
        /// <param name="elementSelectionParams">Element selection parameters.</param>
        /// <returns>Index of the current display element.</returns>
        public int GetCurrentDisplayElementIndex(ElementSelectionParams elementSelectionParams)
        {
            int i = 1;

            switch (elementSelectionParams.SelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return -1;
                case ElementSelectionMethod.Description:
                    foreach (DisplayElement displayElement in this.DisplayElements.Where(element => element.Description == this.CurrentDisplayElement.Description))
                    {
                        if (displayElement == this.CurrentDisplayElement)
                            return i;
                        i++;
                    }
                    break;
                case ElementSelectionMethod.ResourceId:
                    foreach (DisplayElement displayElement in this.DisplayElements.Where(element => element.ResourceId == this.CurrentDisplayElement.ResourceId))
                    {
                        if (displayElement == this.CurrentDisplayElement)
                            return i;
                        i++;
                    }
                    break;
                case ElementSelectionMethod.Text:
                    foreach (DisplayElement displayElement in this.DisplayElements.Where(element => element.Text == this.CurrentDisplayElement.Text))
                    {
                        if (displayElement == this.CurrentDisplayElement)
                            return i;
                        i++;
                    }
                    break;
                case ElementSelectionMethod.IndexTree:
                    foreach (DisplayElement displayElement in this.DisplayElements.Where(element => element.IndexTree == this.CurrentDisplayElement.IndexTree))
                    {
                        if (displayElement == this.CurrentDisplayElement)
                            return i;
                        i++;
                    }
                    break;
                case ElementSelectionMethod.Coordinates:
                    foreach (DisplayElement displayElement in this.DisplayElements.Where(element => element.Rectangle == this.CurrentDisplayElement.Rectangle))
                    {
                        if (displayElement == this.CurrentDisplayElement)
                            return i;
                        i++;
                    }
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }

            return -1;
        }

        #region [ Commands ]

        #region [ Commands - BackButton ]

        private DelegateCommand backButtonCommand;

        /// <summary>
        /// Command for back stepping phone to previous UI state.
        /// Executes self.back()
        /// </summary>
        public ICommand BackButtonCommand
        {
            get
            {
                if (this.backButtonCommand == null)
                    this.backButtonCommand = new DelegateCommand(this.BackButtonCommandExecuted, this.BackButtonCommandCanExecute);

                return this.backButtonCommand;
            }
        }

        /// <summary>
        /// Back stepping is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool BackButtonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.back()" and updates the display capture.
        /// </summary>
        private void BackButtonCommandExecuted()
        {
            this.SendScriptCommand("self.back()");
        }

        #endregion [ Commands - BackButton ]

        #region [ Commands - ExitToIdle ]

        private DelegateCommand exitToIdleCommand;

        /// <summary>
        /// Command for returning the phone UI to idle state.
        /// Executes self.exit()
        /// </summary>
        public ICommand ExitToIdleCommand
        {
            get
            {
                if (this.exitToIdleCommand == null)
                    this.exitToIdleCommand = new DelegateCommand(this.ExitToIdleCommandExecuted, this.ExitToIdleCommandCanExecute);

                return this.exitToIdleCommand;
            }
        }

        /// <summary>
        /// Exit to idle is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool ExitToIdleCommandCanExecute()
        {
            return this.IsPhoneControlEnabled && !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.exit()" and updates the display capture.
        /// </summary>
        private void ExitToIdleCommandExecuted()
        {
            this.SendScriptCommand("self.exit()");
        }

        #endregion [ Commands - ExitToIdle ]

        #region [ Commands - VolumeDownButton ]

        private DelegateCommand volumeDownButtonCommand;

        /// <summary>
        /// Command for volume down button.
        /// Executes self.select('KEYCODE_VOLUME_DOWN')
        /// </summary>
        public ICommand VolumeDownButtonCommand
        {
            get
            {
                if (this.volumeDownButtonCommand == null)
                    this.volumeDownButtonCommand = new DelegateCommand(this.VolumeDownButtonCommandExecuted, this.VolumeDownButtonCommandCanExecute);

                return this.volumeDownButtonCommand;
            }
        }

        /// <summary>
        /// Volume down button is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool VolumeDownButtonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.select('KEYCODE_VOLUME_DOWN')" and updates the display capture.
        /// </summary>
        private void VolumeDownButtonCommandExecuted()
        {
            this.SendScriptCommand("self.select('KEYCODE_VOLUME_DOWN')");
        }

        #endregion [ Commands - VolumeDownButton ]

        #region [ Commands - VolumeUpButton ]

        private DelegateCommand volumeUpButtonCommand;

        /// <summary>
        /// Command for volume up button.
        /// Executes self.select('KEYCODE_VOLUME_UP')
        /// </summary>
        public ICommand VolumeUpButtonCommand
        {
            get
            {
                if (this.volumeUpButtonCommand == null)
                    this.volumeUpButtonCommand = new DelegateCommand(this.VolumeUpButtonCommandExecuted, this.VolumeUpButtonCommandCanExecute);

                return this.volumeUpButtonCommand;
            }
        }

        /// <summary>
        /// Volume up button is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool VolumeUpButtonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.select('KEYCODE_VOLUME_UP')" and updates the display capture.
        /// </summary>
        private void VolumeUpButtonCommandExecuted()
        {
            this.SendScriptCommand("self.select('KEYCODE_VOLUME_UP')");
        }

        #endregion [ Commands - VolumeUpButton ]

        #region [ Commands - PowerButton ]

        private DelegateCommand powerButtonCommand;

        /// <summary>
        /// Command for power button.
        /// Executes self.select('KEYCODE_POWER')
        /// </summary>
        public ICommand PowerButtonCommand
        {
            get
            {
                if (this.powerButtonCommand == null)
                    this.powerButtonCommand = new DelegateCommand(this.PowerButtonCommandExecuted, this.PowerButtonCommandCanExecute);

                return this.powerButtonCommand;
            }
        }

        /// <summary>
        /// Power button is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool PowerButtonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.select('KEYCODE_POWER')" and updates the display capture.
        /// </summary>
        private void PowerButtonCommandExecuted()
        {
            this.SendScriptCommand("self.select('KEYCODE_POWER')");
        }

        #endregion [ Commands - PowerButton ]

        #region [ Commands - Disable Lock Screen ]

        private DelegateCommand disableLockScreenCommand;

        /// <summary>
        /// Command for power button.
        /// Executes disable_lock_screen
        /// </summary>
        public ICommand DisableLockScreenCommand
        {
            get
            {
                if (this.disableLockScreenCommand == null)
                    this.disableLockScreenCommand = new DelegateCommand(this.DisableLockScreenCommandExecuted, this.DisableLockScreenCommandCanExecute);

                return this.disableLockScreenCommand;
            }
        }

        /// <summary>
        /// Disable lock screen is enabled if captured image exists.
        /// </summary>
        /// <returns></returns>
        private bool DisableLockScreenCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "disable_lock_screen" and updates the display capture.
        /// </summary>
        private void DisableLockScreenCommandExecuted()
        {
            this.SendScriptCommand("disable_lock_screen");
        }

        #endregion [ Commands - PowerButton ]

        #region [ Commands - Select by ResourceID ]

        private DelegateCommand<string> selectByResourceIdCommand;

        private DelegateCommand<string> selectLongByResourceIdCommand;

        /// <summary>
        /// Command for selecting element by Resource ID.
        /// </summary>
        public ICommand SelectByResourceIdCommand
        {
            get
            {
                if (this.selectByResourceIdCommand == null)
                    this.selectByResourceIdCommand = new DelegateCommand<string>(this.SelectByResourceIdCommandExecuted, this.SelectByResourceIdCommandCanExecute);

                return this.selectByResourceIdCommand;
            }
        }

        /// <summary>
        /// Command for selecting element by Resource ID.
        /// </summary>
        public ICommand SelectLongByResourceIdCommand
        {
            get
            {
                if (this.selectLongByResourceIdCommand == null)
                    this.selectLongByResourceIdCommand = new DelegateCommand<string>(this.SelectLongByResourceIdCommandExecuted, this.SelectByResourceIdCommandCanExecute);

                return this.selectLongByResourceIdCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Resource ID.
        /// </summary>
        /// <returns></returns>
        private bool SelectByResourceIdCommandCanExecute(string resourceId = "")
        {
            if (string.IsNullOrEmpty(this.ImagePath) || string.IsNullOrEmpty(resourceId)) return false;

            return this.DisplayElements.Count(displayElement => displayElement.ResourceId == resourceId) >= 1;
        }

        /// <summary>
        /// Sends script command "self.select.resourceId(" + resourceId + ")" and updates the display capture.
        /// </summary>
        private void SelectByResourceIdCommandExecuted(string resourceId)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = false, Parameter = resourceId, SelectionMethod = ElementSelectionMethod.ResourceId };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByResourceId(elementSelectionParams);
        }

        /// <summary>
        /// Sends script command "self.select.resourceId(" + resourceId + ")" and updates the display capture.
        /// </summary>
        private void SelectLongByResourceIdCommandExecuted(string resourceId)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = true, Parameter = resourceId, SelectionMethod = ElementSelectionMethod.ResourceId };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByResourceId(elementSelectionParams);
        }

        private void SelectByResourceId(ElementSelectionParams elementSelectionParams)
        {
            if (string.IsNullOrEmpty(elementSelectionParams.Parameter)) return;

            if (elementSelectionParams.Index < 1)
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.resourceId('" + elementSelectionParams.Parameter + "')");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'resourceId')");
            }
            else
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.resourceId('" + elementSelectionParams.Parameter + "', index = " + elementSelectionParams.Index + ")");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'resourceId', index = " + elementSelectionParams.Index + ")");
            }
        }

        #endregion [ Commands - Select by ResourceID ]

        #region [ Commands - Select by Description ]

        private DelegateCommand<string> selectByDescriptionCommand;

        private DelegateCommand<string> selectLongByDescriptionCommand;

        /// <summary>
        /// Command for selecting element by Description.
        /// </summary>
        public ICommand SelectByDescriptionCommand
        {
            get
            {
                if (this.selectByDescriptionCommand == null)
                    this.selectByDescriptionCommand = new DelegateCommand<string>(this.SelectByDescriptionCommandExecuted, this.SelectByDescriptionCommandCanExecute);

                return this.selectByDescriptionCommand;
            }
        }

        /// <summary>
        /// Command for long selecting element by Description.
        /// </summary>
        public ICommand SelectLongByDescriptionCommand
        {
            get
            {
                if (this.selectLongByDescriptionCommand == null)
                    this.selectLongByDescriptionCommand = new DelegateCommand<string>(this.SelectLongByDescriptionCommandExecuted, this.SelectByDescriptionCommandCanExecute);

                return this.selectLongByDescriptionCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Description.
        /// </summary>
        /// <returns></returns>
        private bool SelectByDescriptionCommandCanExecute(string description = "")
        {
            if (string.IsNullOrEmpty(this.ImagePath) || string.IsNullOrEmpty(description)) return false;

            return this.DisplayElements.Count(displayElement => displayElement.Description == description) >= 1;
        }

        /// <summary>
        /// Sends script command "self.select.description(" + description + ")" and updates the display capture.
        /// </summary>
        private void SelectByDescriptionCommandExecuted(string description)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = false, Parameter = description, SelectionMethod = ElementSelectionMethod.Description };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByDescription(elementSelectionParams);
        }

        private void SelectLongByDescriptionCommandExecuted(string description)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = true, Parameter = description, SelectionMethod = ElementSelectionMethod.Description };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByDescription(elementSelectionParams);
        }

        private void SelectByDescription(ElementSelectionParams elementSelectionParams)
        {
            if (string.IsNullOrEmpty(elementSelectionParams.Parameter)) return;

            if (elementSelectionParams.Index < 1)
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.description('" + elementSelectionParams.Parameter + "')");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'description')");
            }
            else
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.description('" + elementSelectionParams.Parameter + "', index = " + elementSelectionParams.Index + ")");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'description', index = " + elementSelectionParams.Index + ")");
            }
        }

        #endregion [ Commands - Select by Description ]

        #region [ Commands - Select by Index Tree ]

        private DelegateCommand<string> selectByIndexTreeCommand;

        private DelegateCommand<string> selectLongByIndexTreeCommand;

        /// <summary>
        /// Command for selecting element by Index Tree.
        /// </summary>
        public ICommand SelectByIndexTreeCommand
        {
            get
            {
                if (this.selectByIndexTreeCommand == null)
                    this.selectByIndexTreeCommand = new DelegateCommand<string>(this.SelectByIndexTreeCommandExecuted, this.SelectByIndexTreeCommandCanExecute);

                return this.selectByIndexTreeCommand;
            }
        }

        /// <summary>
        /// Command for long selecting element by Index Tree.
        /// </summary>
        public ICommand SelectLongByIndexTreeCommand
        {
            get
            {
                if (this.selectLongByIndexTreeCommand == null)
                    this.selectLongByIndexTreeCommand = new DelegateCommand<string>(this.SelectLongByIndexTreeCommandExecuted, this.SelectByIndexTreeCommandCanExecute);

                return this.selectLongByIndexTreeCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Index Tree.
        /// </summary>
        /// <returns></returns>
        private bool SelectByIndexTreeCommandCanExecute(string indexTree = "")
        {
            if (string.IsNullOrEmpty(this.ImagePath) || string.IsNullOrEmpty(indexTree)) return false;

            return this.DisplayElements.Count(displayElement => displayElement.IndexTree == indexTree) >= 1;
        }

        /// <summary>
        /// Sends script command "self.select.indexTree(" + indexTree + ")" and updates the display capture.
        /// </summary>
        private void SelectByIndexTreeCommandExecuted(string indexTree)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = false, Parameter = indexTree, SelectionMethod = ElementSelectionMethod.IndexTree };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByIndexTree(elementSelectionParams);
        }

        /// <summary>
        /// Sends script command "self.select.indexTree(" + indexTree + ")" and updates the display capture.
        /// </summary>
        private void SelectLongByIndexTreeCommandExecuted(string indexTree)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = true, Parameter = indexTree, SelectionMethod = ElementSelectionMethod.IndexTree };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByIndexTree(elementSelectionParams);
        }

        private void SelectByIndexTree(ElementSelectionParams elementSelectionParams)
        {
            if (string.IsNullOrEmpty(elementSelectionParams.Parameter)) return;

            if (elementSelectionParams.Index < 1)
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.indexTree('" + elementSelectionParams.Parameter + "')");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'indexTree')");
            }
            else
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.indexTree('" + elementSelectionParams.Parameter + "', index = " + elementSelectionParams.Index + ")");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'indexTree', index = " + elementSelectionParams.Index + ")");
            }
        }

        #endregion [ Commands - Select by Index Tree ]

        #region [ Commands - Select by Text ]

        private DelegateCommand<string> selectByTextCommand;

        private DelegateCommand<string> selectLongByTextCommand;

        /// <summary>
        /// Command for selecting element by Text.
        /// </summary>
        public ICommand SelectByTextCommand
        {
            get
            {
                if (this.selectByTextCommand == null)
                    this.selectByTextCommand = new DelegateCommand<string>(this.SelectByTextCommandExecuted, this.SelectByTextCommandCanExecute);

                return this.selectByTextCommand;
            }
        }

        /// <summary>
        /// Command for long selecting element by Text.
        /// </summary>
        public ICommand SelectLongByTextCommand
        {
            get
            {
                if (this.selectLongByTextCommand == null)
                    this.selectLongByTextCommand = new DelegateCommand<string>(this.SelectLongByTextCommandExecuted, this.SelectByTextCommandCanExecute);

                return this.selectLongByTextCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Text.
        /// </summary>
        /// <returns></returns>
        private bool SelectByTextCommandCanExecute(string text = "")
        {
            if (string.IsNullOrEmpty(this.ImagePath) || string.IsNullOrEmpty(text)) return false;

            return this.DisplayElements.Count(displayElement => displayElement.Text == text) >= 1;
        }

        /// <summary>
        /// Sends script command "self.select.text(" + text + ")" and updates the display capture.
        /// </summary>
        private void SelectByTextCommandExecuted(string text)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = false, Parameter = text, SelectionMethod = ElementSelectionMethod.Text };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByText(elementSelectionParams);
        }

        /// <summary>
        /// Sends script command "self.select.text(" + text + ")" and updates the display capture.
        /// </summary>
        private void SelectLongByTextCommandExecuted(string text)
        {
            ElementSelectionParams elementSelectionParams = new ElementSelectionParams() { IsLongSelect = true, Parameter = text, SelectionMethod = ElementSelectionMethod.Text };
            elementSelectionParams.Index = this.GetElementCount(elementSelectionParams) > 1 ? this.GetCurrentDisplayElementIndex(elementSelectionParams) : 0;
            this.SelectByText(elementSelectionParams);
        }

        private void SelectByText(ElementSelectionParams elementSelectionParams)
        {
            if (string.IsNullOrEmpty(elementSelectionParams.Parameter)) return;

            if (elementSelectionParams.Index < 1)
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.text('" + elementSelectionParams.Parameter + "')");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'text')");
            }
            else
            {
                if (!elementSelectionParams.IsLongSelect)
                    this.SendScriptCommand("self.select.text('" + elementSelectionParams.Parameter + "', index = " + elementSelectionParams.Index + ")");
                else
                    this.SendScriptCommand("self.select.long('" + elementSelectionParams.Parameter + "', withAttribute = 'text', index = " + elementSelectionParams.Index + ")");
            }
        }

        #endregion [ Commands - Select by Text ]

        #region [ Commands - Select by Coordinates ]

        private DelegateCommand<Point> selectByCoordinatesCommand;

        private DelegateCommand<Point> selectLongByCoordinatesCommand;

        /// <summary>
        /// Command for selecting element by Coordinates.
        /// </summary>
        public ICommand SelectByCoordinatesCommand
        {
            get
            {
                if (this.selectByCoordinatesCommand == null)
                    this.selectByCoordinatesCommand = new DelegateCommand<Point>(this.SelectByCoordinatesCommandExecuted, this.SelectByCoordinatesCommandCanExecute);

                return this.selectByCoordinatesCommand;
            }
        }

        /// <summary>
        /// Command for selecting element by Coordinates.
        /// </summary>
        public ICommand SelectLongByCoordinatesCommand
        {
            get
            {
                if (this.selectLongByCoordinatesCommand == null)
                    this.selectLongByCoordinatesCommand = new DelegateCommand<Point>(this.SelectLongByCoordinatesCommandExecuted, this.SelectByCoordinatesCommandCanExecute);

                return this.selectLongByCoordinatesCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Text.
        /// </summary>
        /// <returns></returns>
        private bool SelectByCoordinatesCommandCanExecute(Point point)
        {
            return !string.IsNullOrEmpty(this.ImagePath);
        }

        /// <summary>
        /// Sends script command "self.select(" point.X + ", " + point.Y + ")" and updates the display capture.
        /// </summary>
        private void SelectByCoordinatesCommandExecuted(Point point)
        {
            this.SendScriptCommand("self.select((" + point.X + ", " + point.Y + "))");
        }

        /// <summary>
        /// Sends script command "self.select.long(" point.X + ", " + point.Y + ")" and updates the display capture.
        /// </summary>
        private void SelectLongByCoordinatesCommandExecuted(Point point)
        {
            this.SendScriptCommand("self.select.long((" + point.X + ", " + point.Y + "))");
        }

        #endregion [ Commands - Select by Coordinates ]

        #region [ Commands - Select by Relative Coordinates ]

        private DelegateCommand<Point> selectByRelativeCoordinatesCommand;

        private DelegateCommand<Point> selectLongByRelativeCoordinatesCommand;

        /// <summary>
        /// Command for selecting element by Relative Coordinates.
        /// </summary>
        public ICommand SelectByRelativeCoordinatesCommand
        {
            get
            {
                // Uses same "can execute method" as selection by absolute coordinates.
                if (this.selectByRelativeCoordinatesCommand == null)
                    this.selectByRelativeCoordinatesCommand = new DelegateCommand<Point>(this.SelectByRelativeCoordinatesCommandExecuted, this.SelectByCoordinatesCommandCanExecute);

                return this.selectByRelativeCoordinatesCommand;
            }
        }

        /// <summary>
        /// Command for selecting element by Relative Coordinates.
        /// </summary>
        public ICommand SelectLongByRelativeCoordinatesCommand
        {
            get
            {
                // Uses same "can execute method" as selection by absolute coordinates.
                if (this.selectLongByRelativeCoordinatesCommand == null)
                    this.selectLongByRelativeCoordinatesCommand = new DelegateCommand<Point>(this.SelectLongByRelativeCoordinatesCommandExecuted, this.SelectByCoordinatesCommandCanExecute);

                return this.selectLongByRelativeCoordinatesCommand;
            }
        }

        /// <summary>
        /// Sends script command "self.select(" + text + ")" and updates the display capture.
        /// </summary>
        private void SelectByRelativeCoordinatesCommandExecuted(Point point)
        {
            this.SendScriptCommand("self.select((" +
                    string.Format("{0:0.0000}", Math.Round(point.X / this.canvasRealCapture.Width, 4)) + ", " +
                    string.Format("{0:0.0000}", Math.Round(point.Y / this.canvasRealCapture.Height, 4)) + "))");
        }

        /// <summary>
        /// Sends script command "self.select(" + text + ")" and updates the display capture.
        /// </summary>
        private void SelectLongByRelativeCoordinatesCommandExecuted(Point point)
        {
            this.SendScriptCommand("self.select.long((" +
                    string.Format("{0:0.0000}", Math.Round(point.X / this.canvasRealCapture.Width, 4)) + ", " +
                    string.Format("{0:0.0000}", Math.Round(point.Y / this.canvasRealCapture.Height, 4)) + "))");
        }

        #endregion [ Commands - Select by Relative Coordinates ]

        #region [ Commands - Select by Default Selection Method ]

        private DelegateCommand<bool> selectByDefaultSelectionMethodCommand;

        /// <summary>
        /// Command for selecting element by default selection method.
        /// </summary>
        public ICommand SelectByDefaultSelectionMethodCommand
        {
            get
            {
                if (this.selectByDefaultSelectionMethodCommand == null)
                    this.selectByDefaultSelectionMethodCommand = new DelegateCommand<bool>(this.SelectByDefaultSelectionMethodCommandExecuted, this.SelectByDefaultSelectionMethodCommandCanExecute);

                return this.selectByDefaultSelectionMethodCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by default selection method.
        /// </summary>
        /// <returns></returns>
        private bool SelectByDefaultSelectionMethodCommandCanExecute(bool isLongSelect = false)
        {
            if (isLongSelect) return true;

            if (this.CurrentDisplayElement == null) return false;

            switch (this.DefaultSelectionMethod)
            {
                case ElementSelectionMethod.Description:
                    return this.SelectByDescriptionCommandCanExecute(this.CurrentDisplayElement.Description);
                case ElementSelectionMethod.ResourceId:
                    return this.SelectByResourceIdCommandCanExecute(this.CurrentDisplayElement.ResourceId);                
                case ElementSelectionMethod.Text:
                    return this.SelectByTextCommandCanExecute(this.CurrentDisplayElement.Text);
                case ElementSelectionMethod.IndexTree:
                    return this.SelectByIndexTreeCommandCanExecute(this.CurrentDisplayElement.IndexTree);
                case ElementSelectionMethod.Coordinates:
                    return this.SelectByCoordinatesCommandCanExecute(this.CurrentEndCoordinates);
                case ElementSelectionMethod.BestPossible:
                    return (this.SelectByDescriptionCommandCanExecute(this.CurrentDisplayElement.Description)
                            || this.SelectByResourceIdCommandCanExecute(this.CurrentDisplayElement.ResourceId)
                            || this.SelectByTextCommandCanExecute(this.CurrentDisplayElement.Text)
                            || this.SelectByIndexTreeCommandCanExecute(this.CurrentDisplayElement.IndexTree)
                            || this.SelectByCoordinatesCommandCanExecute(this.CurrentStartCoordinates));
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        /// <summary>
        /// Sends script command for selecting element by default selection method.
        /// </summary>
        private void SelectByDefaultSelectionMethodCommandExecuted(bool isLongSelect = false)
        {
            this.selectElementCommand(this.DefaultSelectionMethod, isLongSelect);
        }

        private void selectElementCommand(ElementSelectionMethod selectionMethod, bool isLongSelect)
        {
            if (this.CurrentDisplayElement == null)
            {
                if (this.SelectByCoordinatesCommandCanExecute(this.CurrentStartCoordinates))
                {
                    if (!isLongSelect)
                        this.SelectByRelativeCoordinatesCommandExecuted(this.CurrentStartCoordinates);
                    else
                        this.SelectLongByRelativeCoordinatesCommandExecuted(this.CurrentStartCoordinates);
                }

                return;
            }

            switch (selectionMethod)
            {
                case ElementSelectionMethod.Description:
                    if (!isLongSelect)
                        this.SelectByDescriptionCommandExecuted(this.CurrentDisplayElement.Description);
                    else
                        this.SelectLongByDescriptionCommandExecuted(this.CurrentDisplayElement.Description);
                    break;
                case ElementSelectionMethod.ResourceId:
                    if (!isLongSelect)
                        this.SelectByResourceIdCommandExecuted(this.CurrentDisplayElement.ResourceId);
                    else
                        this.SelectLongByResourceIdCommandExecuted(this.CurrentDisplayElement.ResourceId);
                    break;
                case ElementSelectionMethod.Text:
                    if (!isLongSelect)
                        this.SelectByTextCommandExecuted(this.CurrentDisplayElement.Text);
                    else
                        this.SelectLongByTextCommandExecuted(this.CurrentDisplayElement.Text);
                    break;
                case ElementSelectionMethod.IndexTree:
                    if (!isLongSelect)
                        this.SelectByIndexTreeCommandExecuted(this.CurrentDisplayElement.IndexTree);
                    else
                        this.SelectLongByIndexTreeCommandExecuted(this.CurrentDisplayElement.IndexTree);
                    break;
                case ElementSelectionMethod.Coordinates:
                    if (!isLongSelect)
                        this.SelectByCoordinatesCommandExecuted(this.CurrentStartCoordinates);
                    else
                        this.SelectLongByCoordinatesCommandExecuted(this.CurrentStartCoordinates);
                    break;
                case ElementSelectionMethod.BestPossible:
                    this.selectElementCommand(this.getBestPossibleElementSelectionMethod(), isLongSelect);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private ElementSelectionMethod getBestPossibleElementSelectionMethod()
        {
            int descriptionCount = this.GetElementCount(new ElementSelectionParams() { IsLongSelect = false, Parameter = this.CurrentDisplayElement.Description, SelectionMethod = ElementSelectionMethod.Description });
            if (descriptionCount == 1 && this.SelectByDescriptionCommandCanExecute(this.CurrentDisplayElement.Description))
                return ElementSelectionMethod.Description;

            int textCount = this.GetElementCount(new ElementSelectionParams() { IsLongSelect = false, Parameter = this.CurrentDisplayElement.Text, SelectionMethod = ElementSelectionMethod.Text });
            if (textCount == 1 && this.SelectByTextCommandCanExecute(this.CurrentDisplayElement.Text))
                return ElementSelectionMethod.Text;

            int resourceIdCount = this.GetElementCount(new ElementSelectionParams() { IsLongSelect = false, Parameter = this.CurrentDisplayElement.ResourceId, SelectionMethod = ElementSelectionMethod.ResourceId });
            if (resourceIdCount == 1 && this.SelectByResourceIdCommandCanExecute(this.CurrentDisplayElement.ResourceId))
                return ElementSelectionMethod.ResourceId;

            if (this.SelectByIndexTreeCommandCanExecute(this.CurrentDisplayElement.IndexTree))
                return ElementSelectionMethod.IndexTree;

            return ElementSelectionMethod.Coordinates;
        }

        public string GetDisplayElementIdentifier(DisplayElement element)
        {
            if (element == null) return string.Empty;

            switch (this.DefaultSelectionMethod)
            {
                case ElementSelectionMethod.Description:
                    return element.Description;
                case ElementSelectionMethod.ResourceId:
                    return element.ResourceId;
                case ElementSelectionMethod.Text:
                    return element.Text;
                case ElementSelectionMethod.IndexTree:
                    return element.IndexTree;
                case ElementSelectionMethod.Coordinates:
                    return string.Format("({0},{1})", Math.Round(element.Center.X / this.CanvasRealCapture.Width, 4),
                                         Math.Round(element.Center.Y / this.CanvasRealCapture.Height, 4));
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(element.Description))
                        return element.Description;
                    if (!string.IsNullOrEmpty(element.ResourceId))
                        return element.ResourceId;
                    if (!string.IsNullOrEmpty(element.Text))
                        return element.Text;
                    if (!string.IsNullOrEmpty(element.IndexTree))
                        return element.IndexTree;
                    return string.Format("({0},{1})", Math.Round(element.Center.X / this.CanvasRealCapture.Width, 4),
                     Math.Round(element.Center.Y / this.CanvasRealCapture.Height, 4));

                default:
                    return string.Empty;
            }
        }

        #endregion [ Commands - Select by Default Selection Method ]

        #region [ Commands - Toggle ]

        private DelegateCommand<object> toggleCommand;

        /// <summary>
        /// Command for selecting element by Description.
        /// </summary>
        public ICommand ToggleCommand
        {
            get
            {
                if (this.toggleCommand == null)
                    this.toggleCommand = new DelegateCommand<object>(this.ToggleCommandExecuted, this.ToggleCommandCanExecute);

                return this.toggleCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Description.
        /// </summary>
        /// <returns></returns>
        private bool ToggleCommandCanExecute(object toggleCommandParametersTuple)
        {
            if (string.IsNullOrEmpty(this.ImagePath) || toggleCommandParametersTuple == null) return false;

            var param = (Tuple<DisplayElement, ElementSelectionMethod, bool?>)toggleCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;
            bool? newValue = param.Item3;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return this.DisplayElements.Count(dispElem => dispElem.RelatedDescription == displayElement.RelatedDescription) == 1
                            || this.DisplayElements.Count(dispElem => dispElem.RelatedText == displayElement.RelatedText) == 1
                            || this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(dispElem => dispElem.RelatedDescription == displayElement.RelatedDescription) == 1;
                case ElementSelectionMethod.ResourceId:
                    return this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1;
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(dispElem => dispElem.RelatedText == displayElement.RelatedText) == 1;
                case ElementSelectionMethod.IndexTree:
                    return this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1; 
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    break;
            }

            return false;
        }

        /// <summary>
        /// Sends script command "self.select.description(" + description + ")" and updates the display capture.
        /// </summary>
        private void ToggleCommandExecuted(object toggleCommandParametersTuple)
        {
            if (toggleCommandParametersTuple == null) return;

            var param = (Tuple<DisplayElement, ElementSelectionMethod, bool?>)toggleCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;
            bool? newValue = param.Item3;
            
            this.toggleScriptCommand(elementSelectionMethod, displayElement, newValue);
        }

        #endregion [ Commands - Toggle ]

        #region [ Commands - Drag ]

        private DelegateCommand<object> dragCommand;

        /// <summary>
        /// Command for selecting element by Description.
        /// </summary>
        public ICommand DragCommand
        {
            get
            {
                if (this.dragCommand == null)
                    this.dragCommand = new DelegateCommand<object>(this.DragCommandExecuted, this.DragCommandCanExecute);

                return this.dragCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be selected by Description.
        /// </summary>
        /// <param name="dragCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        /// <returns></returns>
        private bool DragCommandCanExecute(object dragCommandParametersTuple)
        {
            if (string.IsNullOrEmpty(this.ImagePath) || dragCommandParametersTuple == null) return false;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)dragCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1;
                case ElementSelectionMethod.ResourceId:
                    return this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1;
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1;
                case ElementSelectionMethod.IndexTree:
                    return this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    break;
            }

            return false;
        }

        /// <summary>
        /// Sends script command "self.select.description(" + description + ")" and updates the display capture.
        /// </summary>
        /// <param name="dragCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        private void DragCommandExecuted(object dragCommandParametersTuple)
        {
            if (dragCommandParametersTuple == null) return;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)dragCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            this.dragScriptCommand(elementSelectionMethod, displayElement);
        }

        #endregion [ Commands - Drag ]

        #region [ Commands - Expect ]

        private DelegateCommand<object> expectCommand;

        /// <summary>
        /// Command for Expecting element.
        /// </summary>
        public ICommand ExpectCommand
        {
            get
            {
                if (this.expectCommand == null)
                    this.expectCommand = new DelegateCommand<object>(this.ExpectCommandExecuted, this.ExpectCommandCanExecute);

                return this.expectCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be Expected.
        /// </summary>
        /// <param name="expectCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        /// <returns></returns>
        private bool ExpectCommandCanExecute(object expectCommandParametersTuple)
        {
            if (string.IsNullOrEmpty(this.ImagePath) || expectCommandParametersTuple == null) return false;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)expectCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1;
                case ElementSelectionMethod.ResourceId:
                    return this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1;
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1;
                case ElementSelectionMethod.IndexTree:
                    return this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    break;
            }

            return false;
        }

        /// <summary>
        /// Sends script command "self.expect(" + ITEM + ")" and updates the display capture.
        /// </summary>
        /// <param name="expectCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        private void ExpectCommandExecuted(object expectCommandParametersTuple)
        {
            if (expectCommandParametersTuple == null) return;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)expectCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            this.expectScriptCommand(elementSelectionMethod, displayElement);
        }

        #endregion [ Commands - Expect ]

        #region [ Commands - Not Expect ]

        private DelegateCommand<object> notExpectCommand;

        /// <summary>
        /// Command for Not Expecting element.
        /// </summary>
        public ICommand NotExpectCommand
        {
            get
            {
                if (this.notExpectCommand == null)
                    this.notExpectCommand = new DelegateCommand<object>(this.NotExpectCommandExecuted, this.NotExpectCommandCanExecute);

                return this.notExpectCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can Not be Expected.
        /// </summary>
        /// <param name="notExpectCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        /// <returns></returns>
        private bool NotExpectCommandCanExecute(object notExpectCommandParametersTuple)
        {
            if (string.IsNullOrEmpty(this.ImagePath) || notExpectCommandParametersTuple == null) return false;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)notExpectCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1;
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1;
                // Not supported.
                case ElementSelectionMethod.ResourceId:
                case ElementSelectionMethod.IndexTree:
                case ElementSelectionMethod.Coordinates:
                default:
                    break;
            }

            return false;
        }

        /// <summary>
        /// Sends script command "self.notExpect(" + ITEM + ")" and updates the display capture.
        /// </summary>
        /// <param name="notExpectCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        private void NotExpectCommandExecuted(object notExpectCommandParametersTuple)
        {
            if (notExpectCommandParametersTuple == null) return;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)notExpectCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            this.notExpectScriptCommand(elementSelectionMethod, displayElement);
        }

        #endregion [ Commands - Not Expect ]

        #region [ Commands - Check ]

        private DelegateCommand<object> checkCommand;

        /// <summary>
        /// Command for Checking element.
        /// </summary>
        public ICommand CheckCommand
        {
            get
            {
                if (this.checkCommand == null)
                    this.checkCommand = new DelegateCommand<object>(this.CheckCommandExecuted, this.CheckCommandCanExecute);

                return this.checkCommand;
            }
        }

        /// <summary>
        /// Returns whether the element can be Checked.
        /// </summary>
        /// <param name="checkCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        /// <returns></returns>
        private bool CheckCommandCanExecute(object checkCommandParametersTuple)
        {
            if (string.IsNullOrEmpty(this.ImagePath) || checkCommandParametersTuple == null) return false;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)checkCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1
                           || this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                case ElementSelectionMethod.Description:
                    return this.DisplayElements.Count(dispElem => dispElem.Description == displayElement.Description) == 1;
                case ElementSelectionMethod.ResourceId:
                    return this.DisplayElements.Count(dispElem => dispElem.ResourceId == displayElement.ResourceId) == 1;
                case ElementSelectionMethod.Text:
                    return this.DisplayElements.Count(dispElem => dispElem.Text == displayElement.Text) == 1;
                case ElementSelectionMethod.IndexTree:
                    return this.DisplayElements.Count(dispElem => dispElem.IndexTree == displayElement.IndexTree) == 1;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    break;
            }

            return false;
        }

        /// <summary>
        /// Sends script command "self.check(" + ITEM + ")" and updates the display capture.
        /// </summary>
        /// <param name="checkCommandParametersTuple">DisplayElementAndSelectionMethodCommandParameters converter created tuple.</param>
        private void CheckCommandExecuted(object checkCommandParametersTuple)
        {
            if (checkCommandParametersTuple == null) return;

            var param = (Tuple<DisplayElement, ElementSelectionMethod>)checkCommandParametersTuple;
            DisplayElement displayElement = param.Item1;
            ElementSelectionMethod elementSelectionMethod = param.Item2;

            this.checkScriptCommand(elementSelectionMethod, displayElement);
        }

        #endregion [ Commands - Check ]

        #region [ Commands - Python Execute Commands ]

        #region [ Commands - Python Execute All Command ]

        private DelegateCommand executeAllPythonCommand;

        /// <summary>
        /// Command for executing all python commands in command history.
        /// </summary>
        public ICommand ExecuteAllPythonCommand
        {
            get
            {
                if (this.executeAllPythonCommand == null)
                    this.executeAllPythonCommand = new DelegateCommand(this.ExecuteAllPythonCommandExecuted, this.ExecuteAllPythonCommandCanExecute);

                return this.executeAllPythonCommand;
            }
        }

        private bool ExecuteAllPythonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.CommandHistory);
        }

        private void ExecuteAllPythonCommandExecuted()
        {
            this.addScriptCommandsToQueue(this.CommandHistory);
        }

        #endregion [ Commands - Python Execute All Command ]

        #region [ Commands - Python Execute Last Command ]

        private DelegateCommand executeLastPythonCommand;

        /// <summary>
        /// Command for executing all python commands in command history.
        /// </summary>
        public ICommand ExecuteLastPythonCommand
        {
            get
            {
                if (this.executeLastPythonCommand == null)
                    this.executeLastPythonCommand = new DelegateCommand(this.ExecuteLastPythonCommandExecuted, this.ExecuteLastPythonCommandCanExecute);

                return this.executeLastPythonCommand;
            }
        }

        private bool ExecuteLastPythonCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.CommandHistory);
        }

        private void ExecuteLastPythonCommandExecuted()
        {
            this.addScriptCommandToQueue(TextUtilities.GetLastLine(this.CommandHistory));
        }

        #endregion [ Commands - Python Execute Last Command ]

        #region [ Commands - Python Execute Selected Command ]

        private DelegateCommand<string> executeSelectedPythonCommand;

        /// <summary>
        /// Command for executing all python commands in command history.
        /// </summary>
        public ICommand ExecuteSelectedPythonCommand
        {
            get
            {
                if (this.executeSelectedPythonCommand == null)
                    this.executeSelectedPythonCommand = new DelegateCommand<string>(this.ExecuteSelectedPythonCommandExecuted, this.ExecuteSelectedPythonCommandCanExecute);

                return this.executeSelectedPythonCommand;
            }
        }

        private bool ExecuteSelectedPythonCommandCanExecute(string commandText)
        {
            if (string.IsNullOrEmpty(commandText)) return false;

            return commandText.Trim().StartsWith(PythonScriptCommands.PythonScriptCommonPrefix)
                    && commandText.Trim().EndsWith(PythonScriptCommands.PythonScriptCommonPostfix);
        }

        private void ExecuteSelectedPythonCommandExecuted(string commandText)
        {
            this.addScriptCommandsToQueue(commandText);
        }

        #endregion [ Commands - Python Execute Last Command ]

        #endregion [ Commands - Python Execute Commands ]

        #region [ Commands - Clear Command History Command ]

        private DelegateCommand clearCommandHistoryCommand;

        /// <summary>
        /// Command for clearing command history.
        /// </summary>
        public ICommand ClearCommandHistoryCommand
        {
            get
            {
                if (this.clearCommandHistoryCommand == null)
                    this.clearCommandHistoryCommand = new DelegateCommand(this.ClearCommandHistoryCommandExecuted, this.ClearCommandHistoryCommandCanExecute);

                return this.clearCommandHistoryCommand;
            }
        }

        private bool ClearCommandHistoryCommandCanExecute()
        {
            return !string.IsNullOrEmpty(this.CommandHistory);
        }

        private void ClearCommandHistoryCommandExecuted()
        {
            this.CommandHistory = string.Empty;
        }

        #endregion [ Commands - Clear Command History Command ]

        #endregion [ Commands ]

        #region [ Script Commands ]

        private void toggleScriptCommand(ElementSelectionMethod elementSelectionMethod, DisplayElement displayElement, bool? newValue = null)
        {
            string item = null;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(displayElement.RelatedDescription))
                        this.toggleScriptCommand(ElementSelectionMethod.Description, displayElement, newValue);
                    else if (!string.IsNullOrEmpty(displayElement.RelatedText))
                        this.toggleScriptCommand(ElementSelectionMethod.Text, displayElement, newValue);
                    else if (!string.IsNullOrEmpty(displayElement.IndexTree))
                        this.toggleScriptCommand(ElementSelectionMethod.IndexTree, displayElement, newValue);
                    break;
                case ElementSelectionMethod.Description:
                    if (string.IsNullOrEmpty(displayElement.RelatedDescription)) return;
                    
                    item = displayElement.RelatedDescription;
                    break;
                case ElementSelectionMethod.Text:
                    if (string.IsNullOrEmpty(displayElement.RelatedText)) return;

                    item = displayElement.RelatedText;
                    break;
                case ElementSelectionMethod.IndexTree:
                    item = displayElement.IndexTree;
                    break;
                // Not supported.
                case ElementSelectionMethod.ResourceId:
                case ElementSelectionMethod.Coordinates:
                default:
                    return;
            }

            if (item == null) return;

            this.SendScriptCommand(PythonScriptCommands.GetToggleCommand(item, newValue));
        }

        private void dragScriptCommand(ElementSelectionMethod elementSelectionMethod, DisplayElement displayElement)
        {
            string item = null;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(displayElement.Description))
                        this.dragScriptCommand(ElementSelectionMethod.Description, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.ResourceId))
                        this.dragScriptCommand(ElementSelectionMethod.ResourceId, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.Text))
                        this.dragScriptCommand(ElementSelectionMethod.Text, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.IndexTree))
                        this.dragScriptCommand(ElementSelectionMethod.IndexTree, displayElement);
                    return;
                case ElementSelectionMethod.Description:
                    item = displayElement.Description;
                    break;
                case ElementSelectionMethod.ResourceId:
                    item = displayElement.ResourceId;
                    break;
                case ElementSelectionMethod.Text:
                    item = displayElement.Text;
                    break;
                case ElementSelectionMethod.IndexTree:
                    item = displayElement.IndexTree;
                    break;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    return;
            }

            if (item == null) return;

            this.SendScriptCommand(PythonScriptCommands.GetDragCommand(item, this.CurrentEndCoordinates, new Point(this.canvasRealCapture.Width, this.canvasRealCapture.Height)));
        }

        private void expectScriptCommand(ElementSelectionMethod elementSelectionMethod, DisplayElement displayElement)
        {
            string item = null;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(displayElement.Description))
                        this.expectScriptCommand(ElementSelectionMethod.Description, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.ResourceId))
                        this.expectScriptCommand(ElementSelectionMethod.ResourceId, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.Text))
                        this.expectScriptCommand(ElementSelectionMethod.Text, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.IndexTree))
                        this.expectScriptCommand(ElementSelectionMethod.IndexTree, displayElement);
                    return;
                case ElementSelectionMethod.Description:
                    item = displayElement.Description;
                    break;
                case ElementSelectionMethod.ResourceId:
                    item = displayElement.ResourceId;
                    break;
                case ElementSelectionMethod.Text:
                    item = displayElement.Text;
                    break;
                case ElementSelectionMethod.IndexTree:
                    item = displayElement.IndexTree;
                    break;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    return;
            }

            if (item == null) return;

            this.SendScriptCommand(PythonScriptCommands.GetExpectCommand(item, elementSelectionMethod));
        }

        private void notExpectScriptCommand(ElementSelectionMethod elementSelectionMethod, DisplayElement displayElement)
        {
            string item = null;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(displayElement.Description))
                        this.notExpectScriptCommand(ElementSelectionMethod.Description, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.Text))
                        this.notExpectScriptCommand(ElementSelectionMethod.Text, displayElement);
                    return;
                case ElementSelectionMethod.Description:
                    item = displayElement.Description;
                    break;
                case ElementSelectionMethod.Text:
                    item = displayElement.Text;
                    break;
                // Not supported.
                case ElementSelectionMethod.IndexTree:
                case ElementSelectionMethod.ResourceId:
                case ElementSelectionMethod.Coordinates:
                default:
                    return;
            }

            if (item == null) return;

            this.SendScriptCommand(PythonScriptCommands.GetNotExpectCommand(item));
        }

        private void checkScriptCommand(ElementSelectionMethod elementSelectionMethod, DisplayElement displayElement)
        {
            string item = null;

            switch (elementSelectionMethod)
            {
                case ElementSelectionMethod.BestPossible:
                    if (!string.IsNullOrEmpty(displayElement.Description))
                        this.checkScriptCommand(ElementSelectionMethod.Description, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.ResourceId))
                        this.checkScriptCommand(ElementSelectionMethod.ResourceId, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.Text))
                        this.checkScriptCommand(ElementSelectionMethod.Text, displayElement);
                    else if (!string.IsNullOrEmpty(displayElement.IndexTree))
                        this.checkScriptCommand(ElementSelectionMethod.IndexTree, displayElement);
                    return;
                case ElementSelectionMethod.Description:
                    item = displayElement.Description;
                    break;
                case ElementSelectionMethod.ResourceId:
                    item = displayElement.ResourceId;
                    break;
                case ElementSelectionMethod.Text:
                    item = displayElement.Text;
                    break;
                case ElementSelectionMethod.IndexTree:
                    item = displayElement.IndexTree;
                    break;
                // Not supported.
                case ElementSelectionMethod.Coordinates:
                default:
                    return;
            }

            if (item == null) return;

            this.SendScriptCommand(PythonScriptCommands.GetCheckCommand(item, elementSelectionMethod));
        }

        #endregion [ Script Commands ]

        private ObservableCollectionAdv<DisplayElement> displayElements;

        /// <summary>
        /// Collection for the captured display elements.
        /// </summary>
        public ObservableCollectionAdv<Marble.Model.DisplayElement> DisplayElements
        {
            get
            {
                return this.displayElements;
            }
            set
            {
                this.displayElements = value;
                this.OnPropertyChanged("DisplayElements");
            }
        }

        private DisplayElement currentDisplayElement;

        /// <summary>
        /// Gets or sets currently selected display element.
        /// </summary>
        public DisplayElement CurrentDisplayElement
        {
            get
            {
                return this.currentDisplayElement;
            }
            set
            {
                this.currentDisplayElement = value;
                this.OnPropertyChanged("CurrentDisplayElement");
            }
        }

        private Point currentStartCoordinates;

        /// <summary>
        /// Gets or sets the current start coordinates.
        /// </summary>
        public Point CurrentStartCoordinates
        {
            get
            {
                return this.currentStartCoordinates;
            }
            set
            {
                this.currentStartCoordinates = value;
                this.OnPropertyChanged("CurrentStartCoordinates");
            }
        }

        private Point currentEndCoordinates;

        /// <summary>
        /// Gets or sets the current end coordinates.
        /// </summary>
        public Point CurrentEndCoordinates
        {
            get
            {
                return this.currentEndCoordinates;
            }
            set
            {
                this.currentEndCoordinates = value;
                this.OnPropertyChanged("CurrentEndCoordinates");
            }
        }

        private string commandHistory;

        /// <summary>
        /// Gets or sets the command history.
        /// </summary>
        public string CommandHistory
        {
            get
            {
                return this.commandHistory;
            }
            set
            {
                this.commandHistory = value;
                this.OnPropertyChanged("CommandHistory");
                this.OnCommandHistoryChanged(EventArgs.Empty);
            }
        }

        protected void OnCommandHistoryChanged(EventArgs e)
        {
            EventHandler handler = CommandHistoryChanged;

            if (handler != null) handler(this, e);
        }

        /// <summary>
        /// Event handler for command histroy changes.
        /// </summary>
        public event EventHandler CommandHistoryChanged;

        /// <summary>
        /// Gets or sets the default selection method.
        /// </summary>
        public ElementSelectionMethod DefaultSelectionMethod
        {
            get
            {
                return this.defaultSelectionMethod;
            }
            set
            {
                this.defaultSelectionMethod = value;
                this.OnPropertyChanged("DefaultSelectionMethod");
            }
        }

        /// <summary>
        /// Indicates whether there is an image loaded and can be saved.
        /// </summary>
        public bool CanSave { get { return !string.IsNullOrEmpty(this.ImagePath); } }

        /// <summary>
        /// Image translations lookup table.
        /// key: png file name
        /// value: possible translations (logical paths)
        /// </summary>
        private Dictionary<string, List<string>> translationsTable = new Dictionary<string, List<string>>();

        private bool isDrawGridActive;

        /// <summary>
        /// Gets or sets a value indicating whether is draw grid active.
        /// </summary>
        public bool IsDrawGridActive
        {
            get
            {
                return this.isDrawGridActive;
            }
            set
            {
                this.isDrawGridActive = value;
                

                if (value)
                    this.DrawGrid(this.CanvasRealCapture);
                else
                    this.CanvasRealCapture.Children.Clear();

                this.OnPropertyChanged("IsDrawGridActive");
            }
        }

        private bool isPhoneControlEnabled = true;

        /// <summary>
        /// Whether to send created script command to phone and re-capture the phone screen.
        /// </summary>
        public bool IsPhoneControlEnabled
        {
            get { return this.isPhoneControlEnabled; }
            set
            {
                if (this.isPhoneControlEnabled == value) return;

                this.isPhoneControlEnabled = value;
                this.OnPropertyChanged("IsPhoneControlEnabled");
            }
        }

        private Canvas canvasRealCapture;

        /// <summary>
        /// Gets or sets the canvas used for capturing.
        /// </summary>
        public Canvas CanvasRealCapture
        {
            get
            {
                return this.canvasRealCapture;
            }
            set
            {
                this.canvasRealCapture = value;
                this.OnPropertyChanged("CanvasRealCapture");
            }
        }

        /// <summary>
        /// Gets or sets the dragged display element.
        /// </summary>
        public DisplayElement DraggedDisplayElement
        {
            get
            {
                return this.draggedDisplayElement;
            }
            set
            {
                this.draggedDisplayElement = value;
                this.OnPropertyChanged("DraggedDisplayElement");
            }
        }

        /// <summary>
        /// Default name for captures from the phone.
        /// </summary>
        public const string TempCaptureName = "LastCapture";

        /// <summary>
        /// File name for the image translation table.
        /// </summary>
        public const string ImagesLookupFile = "ImageTranslationTable.xml";

        /// <summary>
        /// File name for the xaml command file.
        /// </summary>
        public const string TempXamlFile = "LastScriptCommand.xaml";

        private string imagePath;

        /// <summary>
        /// File system path of the captured display image.
        /// </summary>
        public string ImagePath
        {
            get
            {
                return this.imagePath;
            }
            private set
            {
                this.imagePath = value;
                this.OnPropertyChanged("ImagePath");
                this.OnPropertyChanged("CanSave");
            }
        }

        private int gridWidth;

        /// <summary>
        /// Gets or sets the grid width.
        /// </summary>
        public int GridWidth
        {
            get
            {
                return this.gridWidth;
            }
            set
            {
                this.gridWidth = value;
                this.OnPropertyChanged("GridWidth");

                if (!this.IsDrawGridActive) return;

                this.canvasRealCapture.Children.Clear();
                this.DrawGrid(this.canvasRealCapture);
            }
        }

        /// <summary>
        /// File system path of the result xml returned by framework.
        /// Xml contains display elements and path to the real image.
        /// </summary>
        private string xmlPath { get; set; }

        /// <summary>
        /// Name of the application that is open on phone when taking a capture.
        /// </summary>
        public string OnScreenApplicationName { get; set; }

        /// <summary>
        /// Indicates whether a landscape capture was taken and image needs to be rotated.
        /// </summary>
        private bool rotateNeeded = false;

        private DisplayElement draggedDisplayElement;

        private ElementSelectionMethod defaultSelectionMethod;

        private bool pinchStarted = false;

        /// <summary>
        /// Indicates whether we are at the second step of the pinch creation process - the center point of the pinch is already selected.
        /// </summary>
        public bool PinchStarted
        {
            get { return this.pinchStarted; }
            set
            {
                if (this.pinchStarted == value) return;

                this.pinchStarted = value;
                this.canvasRealCapture.Cursor = value ? Cursors.Arrow : Cursors.None;
                this.OnPropertyChanged("PinchStarted");
                this.OnPropertyChanged("PinchInfo");
            }
        }

        /// <summary>
        /// Instructive text to display at the UI for pinch creation.
        /// </summary>
        public string PinchInfo
        {
            get
            {
                return !this.pinchStarted
                           ? "1. Select the center point of the pinch"
                           : "2. Click and hold to create pinch";
            }
        }

        private bool isPinchToolInUse;

        /// <summary>
        /// Indicates whether the pinch creation tool is currently active.
        /// </summary>
        public bool IsPinchToolInUse
        {
            get { return this.isPinchToolInUse; }
            set
            {
                if (this.isPinchToolInUse == value) return;

                this.canvasRealCapture.Cursor = value ? Cursors.None : Cursors.Arrow;
                this.isPinchToolInUse = value;

                this.PinchStarted = false;
                this.OnPropertyChanged("IsPinchToolInUse");
            }
        }

        /// <summary>
        /// Clears display elements and draws grid if it is active.
        /// </summary>
        public void ClearDisplayElements()
        {
            this.DisplayElements.Clear();

            if (this.IsDrawGridActive)
                this.DrawGrid(this.CanvasRealCapture, this.GridWidth);
        }

        /// <summary>
        /// Displays open file dialog and opens the image along with it's meta data.
        /// </summary>
        /// <returns></returns>
        public bool OpenSavedImage()
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Portable network graphics|*.png";

            // Show open file dialog and check if OK was pressed and filename was selected
            if ((bool)openFileDialog.ShowDialog() && !string.IsNullOrEmpty(openFileDialog.FileName))
            {
                if (!System.IO.File.Exists(openFileDialog.FileName)) return false;

                // Set image path and clear other variables
                this.ImagePath = openFileDialog.FileName;
                this.xmlPath = string.Empty;
                this.displayElements.Clear();
                this.OnScreenApplicationName = string.Empty;
                this.rotateNeeded = false;

                // Parse display elements from the image meta data
                this.getDisplayElementsFromImage();

                // Draw captured image
                this.DrawImage();
            }

            return false;
        }

        /// <summary>
        /// Reads stored display elements from image meta data.
        /// PropertyTagImageDescription fields is used to store display elements in an xml format.
        /// </summary>
        private void getDisplayElementsFromImage()
        {
            System.Drawing.Bitmap bitmap = (System.Drawing.Bitmap)System.Drawing.Bitmap.FromFile(this.ImagePath);

            // Check if image description property tag can be found (PropertyTagImageDescription = 0x010E).
            if (!bitmap.PropertyIdList.Any(propId => propId == 0x010E)) return;

            // Get xml data from property item
            System.Drawing.Imaging.PropertyItem property = bitmap.GetPropertyItem(0x010E);
            string captureXml = Encoding.UTF8.GetString(property.Value, 0, property.Len - 1);
            XElement captureElement = XElement.Parse(captureXml);
            
            if (captureElement.IsEmpty) return;

            // Get stored application name from xml
            XAttribute attrib;
            if ((attrib = captureElement.Attribute("application")) != null)
                this.OnScreenApplicationName = attrib.Value;

            // Get display elements from xml
            foreach (XElement displayElement in captureElement.Descendants().Where(elem => elem.Parent == captureElement))
                this.DisplayElements.Add(new DisplayElement(displayElement));
        }

        /// <summary>
        /// Sets current captured image to background of canvas.
        /// Draws grid lines on top of the image if needed.
        /// Captured image is rotated if it is landscape type.
        /// </summary>
        private void DrawImage()
        {
            // Create new bitmap image object with current image path
            BitmapImage capturedImage = new BitmapImage();
            capturedImage.BeginInit();
            capturedImage.CacheOption = BitmapCacheOption.OnLoad;
            capturedImage.CreateOptions = BitmapCreateOptions.IgnoreImageCache;
            capturedImage.UriSource = new Uri(this.ImagePath, UriKind.Relative);

            // Rotate image 90 degrees counter clockwise if needed
            if (this.rotateNeeded)
                capturedImage.Rotation = Rotation.Rotate270;

            capturedImage.EndInit();

            // Resize canvas according to image
            this.canvasRealCapture.Width = capturedImage.Width;
            this.canvasRealCapture.Height = capturedImage.Height;

            // Draw image on canvas
            this.canvasRealCapture.Background = new ImageBrush(capturedImage);

            // Draw grid over the image
            if (this.IsDrawGridActive)
                this.DrawGrid(this.CanvasRealCapture, this.GridWidth);
        }

        /// <summary>
        /// Callback method for images command.
        /// Parses image translations table from the result file.
        /// </summary>
        /// <param name="command">Command that was executed.</param>
        private void OnImagesCommandDone(BaseCommand command)
        {
            if (command.GetType() != typeof (Communication.ImagesCommand)) return;
            
            this.ParseImageTranslationTable();
        }

        /// <summary>
        /// Callback method for a script execution command.
        /// Sends a capture command.
        /// </summary>
        /// <param name="command"></param>
        private void OnScriptCommandDone(BaseCommand command)
        {
            if (command.GetType() != typeof(ExecuteTestStep)) return;

            this.SendCaptureCommand();
        }

        /// <summary>
        /// Callback method for capture commands.
        /// This method is called when connector is finished executing the capture command.
        /// Parses display elements from the display dump.
        /// Real image along with the display elements are updated to view.
        /// Also grid lines are drawn if needed.
        /// </summary>
        private void OnCaptureCommandDone(BaseCommand command)
        {
            if (this.CanvasRealCapture == null) return;

            // Handle only capture commands
            if (command.GetType() != typeof(Communication.CaptureCommand)) return;

            // TODO: Show error note
            //if (!e.IsSuccess) return;

            // Parse result file for the captured image path and display elements
            this.ParseDisplayElements();

            // Show output window on capturing failed
            if (!System.IO.File.Exists(this.ImagePath)) return;

            // Draw captured image
            this.DrawImage();
        }

        /// <summary>
        /// Gets data for the image translation table.
        /// Dictionary is filled with png names as keys and possible translations list as a value.
        /// Source file must have been previously obtained from the framework with images command.
        /// </summary>
        private void ParseImageTranslationTable()
        {
            // Get images root element from the source file
            XElement images;
            string filePath = System.IO.Path.Combine(MarblePaths.CaptureToolTemp, ImagesLookupFile);
            if (!CaptureToolViewModel.TryParseXml(filePath, out images))
                return;

            // Fill translation dictionary
            this.translationsTable.Clear();
            foreach (var image in images.Descendants())
            {
                string id = image.Attribute("id").Value;
                // Take just the file name part of the (png) path
                string path = System.IO.Path.GetFileName(image.Attribute("path").Value);

                // Add new key
                if (!this.translationsTable.ContainsKey(path))
                    this.translationsTable[path] = new List<string>();

                // Add new value for existing key
                if (!this.translationsTable[path].Contains(id))
                    this.translationsTable[path].Add(id);
            }
        }

        /// <summary>
        /// Gets the translations list for the given image.
        /// First item of the list is the suggested translation.
        /// First item is the original name of the image if no translation can be found.
        /// </summary>
        /// <param name="name">Image file name for which to look for translations (key of the dictionary).</param>
        /// <returns>List of possible translations (suggested one being first).</returns>
        public List<string> GetImageTranslations(string name)
        {
            // No entry for this name or entry contains no translations: put original name as the suggested translation
            if (string.IsNullOrEmpty(name) || !this.translationsTable.ContainsKey(name) || this.translationsTable[name].Count == 0)
            {
                List<string> noTranslation = new List<string>(1);
                noTranslation.Add(name);
                return noTranslation;
            }

            // Just one translation or application name not defined
            if (this.translationsTable[name].Count == 1 || string.IsNullOrEmpty(this.OnScreenApplicationName))
                return this.translationsTable[name];

            // Search for a translation that begins with current application name
            string suggestedTranslation = this.translationsTable[name].FirstOrDefault(path => path.StartsWith(this.OnScreenApplicationName));

            // Move suggested translation as the first item of the list
            if (suggestedTranslation != null && this.translationsTable[name].IndexOf(suggestedTranslation) > 0)
            {
                this.translationsTable[name].Remove(suggestedTranslation);
                this.translationsTable[name].Insert(0, suggestedTranslation);
            }

            return this.translationsTable[name];
        }

        /// <summary>
        /// Updates settings and sends capture command to framework.
        /// Image translations dictionary is updated on first capture.
        /// Output window is displayed on first capture.
        /// </summary>
        public void SendCaptureCommand()
        {
            App.ViewModel.UpdateSettings();

            // Send capture command
            App.ViewModel.MarbleConnector.AddToQueue(
                new CaptureCommand(System.IO.Path.Combine(MarblePaths.CaptureToolTemp, TempCaptureName))
                    {
                        CallBackMethod = this.OnCaptureCommandDone
                    });
        }

        /// <summary>
        /// Parses the given xml file and returns a value that indicates whether the parsing succeeded.
        /// </summary>
        /// <param name="xmlPath">Path to the xml file.</param>
        /// <param name="element">XElement as an out parameter. Contains the parsed xml file contents, or null if parsing failed.</param>
        /// <returns>Returns true if xml parsing succeeded.</returns>
        private static bool TryParseXml(string xmlPath, out XElement element)
        {
            try
            {
                element = XElement.Load(xmlPath);
            }
            catch
            {
                element = null;
                return false;
            }

            return true;
        }

        /// <summary>
        /// Fetches display elements from the display dump file.
        /// </summary>
        public void ParseDisplayElements()
        {
            this.parseDisplayElements(System.IO.Path.Combine(MarblePaths.CaptureToolTemp, "xml", TempCaptureName) + ".xml");
        }

        /// <summary>
        /// Fetches display elements from the display dump file.
        /// Populates imagePath and DisplayElements collection.
        /// </summary>
        /// <param name="xmlPath">File system path of the display dump file</param>
        private void parseDisplayElements(string xmlPath)
        {
            // Clear previous results
            this.ClearDisplayElements();

            this.ImagePath = string.Empty;

            // Open display dump xml and find the capture element
            XElement root = null;

            if (!TryParseXml(xmlPath, out root)) return;

            XElement captureElement = System.Xml.XPath.Extensions.XPathSelectElement(root, "//summary/capture[@id]");
            
            if (captureElement == null) return;

            // Image is displayed vertically by default (480, 800)
            this.rotateNeeded = false;

            // Check if image is horizontal (landscape) (800, 480)
            XElement bitmapElement = System.Xml.XPath.Extensions.XPathSelectElement(root, "//bitmap");
            if (bitmapElement != null)
            {
                var widthAttrib = bitmapElement.Attribute("width");
                var heightAttrib = bitmapElement.Attribute("height");
                int width;
                int height;

                if (widthAttrib != null && heightAttrib != null && int.TryParse(widthAttrib.Value, out width) &&
                    int.TryParse(heightAttrib.Value, out height) && width > height)
                    this.rotateNeeded = true;
            }

            this.xmlPath = xmlPath;

            // Get the on screen application name
            XElement appElem = System.Xml.XPath.Extensions.XPathSelectElement(root, "//application[@name]");

            this.OnScreenApplicationName = appElem != null && appElem.Attribute("name") != null
                                               ? appElem.Attribute("name").Value
                                               : string.Empty;

            // Go through all the descendants in capture element
            foreach (var displayElement in captureElement.Descendants())
            {
                // Elements with coords attribute
                var xAttribute = displayElement.Attribute("coords");

                if (xAttribute != null)
                {
                    string[] coordinateValues = xAttribute.Value.Split(',');

                    // Skip elements with 0 width or 0 height
                    if (coordinateValues[2] == "0" || coordinateValues[3] == "0") continue;
                }

                // Real image
                if (displayElement.Name == "bitmap" && displayElement.Attribute("name") != null)
                {
                    // Try image file from the same directory as the xml file
                    this.ImagePath = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(this.xmlPath), displayElement.Attribute("name").Value);

                    // Try image file from the captured bitmaps directory
                    if (!System.IO.File.Exists(this.ImagePath))
                        this.ImagePath = System.IO.Path.Combine(
                            System.IO.Path.GetDirectoryName(this.xmlPath), @"..\captured bitmaps", displayElement.Attribute("name").Value);
                }

                // Skip invalid elements
                if (displayElement.Name != "animation" && displayElement.Name != "text" && displayElement.Name != "node") continue;

                // Get translations for the element
                DisplayElement newElement = new DisplayElement(displayElement);
                newElement.Translations = this.GetImageTranslations(newElement.Content);

                this.DisplayElements.Add(newElement);
            }

        }

        /// <summary>
        /// Draws symmetric grid on top of the captured image.
        /// Cell width is determined by the value of textBoxGridWidth.
        /// </summary>
        public void DrawGrid(Canvas targetCanvas, int width = 0)
        {
            if (width == 0) width = this.GridWidth;

            // Grid not drawn if width isn't longer than 1
            if (width < 1) return;

            // Increase index in intervals of width until image bounds (vertical and horizontal) are exceeded.
            for (int ii = width; ii < targetCanvas.Width || ii < targetCanvas.Height; ii += width)
            {
                // Draw a vertical line
                if (ii < targetCanvas.Width)
                {
                    Line line = new Line
                    {
                        X1 = ii,
                        Y1 = 0,
                        X2 = ii,
                        Y2 = targetCanvas.Height - 1,
                        Stroke = new SolidColorBrush() { Color = Colors.White, Opacity = 0.4 },
                        StrokeThickness = 1,
                        IsHitTestVisible = false,
                        SnapsToDevicePixels = true
                    };

                    targetCanvas.Children.Add(line);
                }

                // Draw a horizontal line
                if (ii < targetCanvas.Height)
                {
                    Line line = new Line
                    {
                        X1 = 0,
                        Y1 = ii,
                        X2 = targetCanvas.Width - 1,
                        Y2 = ii,
                        Stroke = new SolidColorBrush() { Color = Colors.White, Opacity = 0.4 },
                        StrokeThickness = 1,
                        IsHitTestVisible = false,
                        SnapsToDevicePixels = true
                    };

                    targetCanvas.Children.Add(line);
                }
            }
        }

        /// <summary>
        /// Helper method for calculating the distance between the two points.
        /// </summary>
        /// <param name="start">First point</param>
        /// <param name="end">Second point</param>
        /// <returns>Distance between the points</returns>
        public static int GetDistance(Point start, Point end)
        {
            // Calculate the distance using the Pythagorean theorem
            return (int)Math.Sqrt(Math.Pow(start.X - end.X, 2) + Math.Pow(start.Y - end.Y, 2));
        }

        /// <summary>
        /// Creates a line shape.
        /// </summary>
        /// <param name="start">Start position</param>
        /// <param name="end">End position</param>
        /// <param name="thickness">Stroke thickness (default = 1)</param>
        /// <param name="colour">Stroke brush</param>
        /// <param name="dashLength">Length of the dash (relative to the width of the line, see StrokeDashArray)</param>
        /// <returns>Line object</returns>
        private static Line createLine(Point start, Point end, double thickness = 1, Brush colour = null, double dashLength=0)
        {
            if (colour == null)
                colour = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 };

            Line line = new Line
            {
                X1 = start.X,
                Y1 = start.Y,
                X2 = end.X,
                Y2 = end.Y,
                Stroke = colour,
                StrokeThickness = thickness,
                StrokeStartLineCap = PenLineCap.Round,
                StrokeEndLineCap = PenLineCap.Round,
                IsHitTestVisible = false,
                SnapsToDevicePixels = true
            };

            // Create dashed line
            if (dashLength > 0)
                line.StrokeDashArray = new DoubleCollection(new[] {dashLength, dashLength});

            return line;
        }

        /// <summary>
        /// Creates a (sharp) triangle shape that can be used as a head for arrows.
        /// Width of the base is half of the length.
        /// </summary>
        /// <param name="tip">Top point of the triangle</param>
        /// <param name="diameter">Defines the direction and length of the triangle</param>
        /// <returns>Triangle shape</returns>
        private Polygon createArrowHead(Point tip, Vector diameter)
        {
            PointCollection points = new PointCollection
                {
                    tip,

                    // Calculate other two points
                    tip - diameter + CaptureToolViewModel.RotateVector(diameter, 90) * 0.25,
                    tip - diameter - CaptureToolViewModel.RotateVector(diameter, 90) * 0.25
                };

            Polygon arrowHead = new Polygon
            {
                Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                Fill = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                Points = points,
                SnapsToDevicePixels = true,
                IsHitTestVisible = false
            };

            return arrowHead;
        }

        /// <summary>
        /// Draws an arrow shape over the real capture.
        /// Adds two childs (line and arrow head) to targetCanvas.
        /// </summary>
        /// <param name="start">Start position of the arrow</param>
        /// <param name="end">End position of the arrow</param>
        /// <param name="targetCanvas">Canvas on which the arrow is drawn (added as a child)</param>
        /// <param name="dashLength">Length of the dash (relative to the width of the line, see StrokeDashArray)</param>
        public void DrawArrow(Point start, Point end, Canvas targetCanvas, double dashLength=0)
        {
            // Draw an arrow head to the target point
            // Length of the arrow head is fourth of the total length
            Vector arrowDiameter = (end - start) * 0.25;
            targetCanvas.Children.Add(this.createArrowHead(end, arrowDiameter));

            // Draw a red line from start position to the beginning of the arrow head
            // Line thickness depends of the line length
            Line line = createLine(start, end - arrowDiameter, Math.Ceiling((end - start).Length / 50), dashLength:dashLength);
            targetCanvas.Children.Add(line);
        }

        /// <summary>
        /// Draws a sniper scope to the given point over the given canvas.
        /// </summary>
        /// <param name="target">Center point of the scope.</param>
        /// <param name="targetCanvas">Canvas on which the scope is drawn (added as a child).</param>
        public void DrawScope(Point target, Canvas targetCanvas)
        {
            int radius = 20;

            // Draw an ellipse
            var ellipse = new Ellipse()
                {
                    Stroke = new SolidColorBrush() {Color = Colors.Red, Opacity = 0.6},
                    StrokeThickness = 2,
                    SnapsToDevicePixels = true,
                    IsHitTestVisible = false,
                    Width = radius * 2,
                    Height = radius * 2
                };

            Canvas.SetLeft(ellipse, target.X - radius);
            Canvas.SetTop(ellipse, target.Y - radius);
            targetCanvas.Children.Add(ellipse);

            // Draw horisontal line
            var start = new Point(target.X - radius - 5, target.Y);
            var end = new Point(target.X + radius + 5, target.Y);

            targetCanvas.Children.Add(createLine(start, end));

            // Draw vertical line
            start = new Point(target.X, target.Y - radius - 5);
            end = new Point(target.X, target.Y + radius + 5);

            targetCanvas.Children.Add(createLine(start, end));
        }

        /// <summary>
        /// Draws an ellipse over the real capture.
        /// </summary>
        /// <param name="center">Center point of the ellipse.</param>
        /// <param name="radius">Radius of the ellipse.</param>
        /// <param name="dashLength">Length of the dash (relative to the width of the line, see StrokeDashArray)</param>
        public void DrawEllipse(Point center, double radius, double dashLength = 0)
        {
            var ellipse = new Ellipse()
            {
                Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                StrokeThickness = 2,
                SnapsToDevicePixels = true,
                IsHitTestVisible = false,
                Width = radius * 2,
                Height = radius * 2
            };

            if (dashLength > 0)
                ellipse.StrokeDashArray = new DoubleCollection(new[] {dashLength, dashLength});

            Canvas.SetLeft(ellipse, center.X - radius);
            Canvas.SetTop(ellipse, center.Y - radius);
            this.canvasRealCapture.Children.Add(ellipse);
        }

        /// <summary>
        /// Rotates a vector
        /// </summary>
        /// <param name="origVector">Initial vector to rotate</param>
        /// <param name="angle">Angle in degrees to rotate</param>
        /// <returns>Rotated vector</returns>
        public static Vector RotateVector(Vector origVector, int angle)
        {
            // Angle in radians
            double radians = angle * Math.PI / 180;
            double cos = 0;
            double sin = 0;

            // Calculate cos and sin components if needed
            if (!(Math.Abs(radians) % Math.PI == Math.PI / 2))
                cos = Math.Cos(radians);
            if (!(Math.Abs(radians) % Math.PI == 0))
                sin = Math.Sin(radians);

            // Rotate vector
            return new Vector { X = origVector.X * cos - origVector.Y * sin, Y = origVector.X * sin + origVector.Y * cos };
        }

        /// <summary>
        /// Calculates the pinch direction, length and angle.
        /// </summary>
        /// <param name="mousePosition">Current mouse position</param>
        /// <returns>Pinch command suitable for Marble scripts. e.g. self.gesture.pinch.in(50, angle=45)</returns>
        public string CreatePinchString(Point centerPoint, Point mousePosition, Point startPosition, Point canvasSize)
        {

            double canvasDiagonalLength = Math.Sqrt(Math.Pow(canvasSize.X, 2) + Math.Pow(canvasSize.Y, 2));

            // Calculate the distance of the pinch start position to the center of the pinch
            double startDistance = (startPosition - centerPoint).Length;

            // Create vector from center of the pinch to the current mouse position
            Vector centerToMousePos = mousePosition - centerPoint;

            // Pinch length
            double pinchLength = Math.Round(startDistance - centerToMousePos.Length);

            // Pinch direction
            string pinchDirection = pinchLength > 0 ? "In" : "Out";

            // Pinch angle (vertical axis to north being zero)
            // values: north to south clokwise = 0 to -180, counter clokwise = 0 to 180
            double pinchAngle = Vector.AngleBetween(centerToMousePos, new Point(centerPoint.X, centerPoint.Y - 1) - centerPoint);

            // Transform angle to fit scripting specs: north to south clockwise = 0 to 179
            pinchAngle = Math.Round(360 - pinchAngle) % 180;

            return string.Format("self.pinch{0}(({1},{2}), angle={3}, length={4})",
                                 pinchDirection,
                                 Math.Round(centerPoint.X/canvasSize.X, 4),
                                 Math.Round(centerPoint.Y/canvasSize.Y, 4),
                                 pinchAngle,
                                 Math.Round(Math.Abs(pinchLength)/(canvasDiagonalLength/2), 2));
        }

        /// <summary>
        /// Returns the display element of currently selected display elements that have the smallest area.
        /// </summary>
        /// <returns></returns>
        public DisplayElement SelectSmallestDisplayElement(Point pos)
        {
            DisplayElement selectedDisplayElement = null;

            // Select the DisplayElement with smallest area
            foreach (DisplayElement displayElement in this.DisplayElements.Where(dElem => dElem.Rectangle.Contains((int)pos.X, (int)pos.Y)))
            {
                if (selectedDisplayElement == null ||
                    selectedDisplayElement.Rectangle.Width * selectedDisplayElement.Rectangle.Height >
                    displayElement.Rectangle.Width * displayElement.Rectangle.Height)
                    selectedDisplayElement = displayElement;
            }

            return selectedDisplayElement;
        }

        /// <summary>
        /// Returns the display element of currently selected display elements that have the smallest area and is specific type.
        /// </summary>
        /// <returns></returns>
        public DisplayElement SelectSmallestDisplayElement(Point pos, DisplayElementType displayElementType)
        {
            DisplayElement selectedDisplayElement = null;

            // Select the DisplayElement with smallest area
            foreach (DisplayElement displayElement in this.DisplayElements.Where(dElem => dElem.Rectangle.Contains((int)pos.X, (int)pos.Y)))
            {
                if (displayElement.Type != displayElementType) continue;

                if (selectedDisplayElement == null ||
                    selectedDisplayElement.Rectangle.Width * selectedDisplayElement.Rectangle.Height >
                    displayElement.Rectangle.Width * displayElement.Rectangle.Height)
                    selectedDisplayElement = displayElement;
            }

            return selectedDisplayElement;
        }

        /// <summary>
        /// Displays the save file dialog and saves the image with the elements as meta data.
        /// </summary>
        public void SaveCaptureImage()
        {
            if (string.IsNullOrEmpty(this.ImagePath)) return;

            // Initialize save file dialog
            Microsoft.Win32.SaveFileDialog saveFileDialog = new Microsoft.Win32.SaveFileDialog
            {
                OverwritePrompt = true,
                FileName = @"Marble_capture(" + this.OnScreenApplicationName + @").png",
                Filter = "Portable network graphics|*.png"
            };

            // Display save file dialog and check that OK was pressed and filename was entered
            if (!((bool)saveFileDialog.ShowDialog()) || string.IsNullOrEmpty(saveFileDialog.FileName)) return;

            System.Drawing.Bitmap image = (System.Drawing.Bitmap)System.Drawing.Bitmap.FromFile(this.imagePath);

            // Rotate saved image if needed
            if (this.rotateNeeded)
                image.RotateFlip(System.Drawing.RotateFlipType.Rotate270FlipNone);

            // Store display elements to image description property tag
            byte[] bytes = Encoding.UTF8.GetBytes(this.createCaptureXml());
            System.Drawing.Imaging.PropertyItem commentMeta = createPropertyItem();
            
            // PropertyTagImageDescription = 0x010E
            commentMeta.Id = 0x010E;
            commentMeta.Type = 2;
            commentMeta.Value = new byte[bytes.Length + 1];
            bytes.CopyTo(commentMeta.Value, 0);
            commentMeta.Value[bytes.Length] = 0;
            commentMeta.Len = bytes.Length + 1;
            image.SetPropertyItem(commentMeta);

            // Save image file to given location
            image.Save(saveFileDialog.FileName);
        }

        /// <summary>
        /// Creates an empty property item.
        /// Property item doesn't have a constructor.
        /// </summary>
        /// <returns>Empty property item</returns>
        static private System.Drawing.Imaging.PropertyItem createPropertyItem()
        {
            System.Reflection.ConstructorInfo constructorInfo = typeof(System.Drawing.Imaging.PropertyItem).GetConstructor(
                System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Public,
                null,
                new Type[] { },
                null);
            return (System.Drawing.Imaging.PropertyItem)constructorInfo.Invoke(null);
        }

        /// <summary>
        /// Creates the xml that is stored into image meta data.
        /// Structure: capture element as a root with application name as an attribute.
        /// Display elements as child elements of the root.
        /// </summary>
        /// <returns>Capture element as an xml.</returns>
        private string createCaptureXml()
        {
            XElement element = new XElement("capture");
            element.SetAttributeValue("application", this.OnScreenApplicationName);

            foreach (DisplayElement displayElement in this.DisplayElements)
            {
                element.Add(displayElement.ToXmlElement());
            }

            return element.ToString();
        }
        
        /// <summary>
        /// Draws the rectangle of the display element over the real capture.
        /// Also center point is drawn as a cross.
        /// </summary>
        /// <param name="displayElement">Display element to draw</param>
        public void DrawDisplayElement(DisplayElement displayElement, Canvas targetCanvas)
        {
            if (displayElement == null) return;

            // Draw a rectangle
            Rectangle rect = new Rectangle
                {
                    Width = displayElement.Rectangle.Width,
                    Height = displayElement.Rectangle.Height,
                    Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                    IsHitTestVisible = false
                };

            Canvas.SetLeft(rect, displayElement.Rectangle.X);
            Canvas.SetTop(rect, displayElement.Rectangle.Y);
            targetCanvas.Children.Add(rect);

            // Draw a center cross
            // Horizontal line 3 pixels long
            Line line1 = new Line
                {
                    X1 = displayElement.Center.X - 1,
                    X2 = displayElement.Center.X + 2, // For some reason the result isn't cross if this is 1
                    Y1 = displayElement.Center.Y,
                    Y2 = displayElement.Center.Y,
                    Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                    SnapsToDevicePixels = true,
                    IsHitTestVisible = false
                };

            targetCanvas.Children.Add(line1);

            // Vertical line 3 pixels long
            Line line2 = new Line
                {
                    Y1 = displayElement.Center.Y - 2,
                    Y2 = displayElement.Center.Y + 1, // For some reason the result isn't cross if this is 1
                    X1 = displayElement.Center.X,
                    X2 = displayElement.Center.X,
                    Stroke = new SolidColorBrush() { Color = Colors.Red, Opacity = 0.6 },
                    SnapsToDevicePixels = true,
                    IsHitTestVisible = false
                };

            targetCanvas.Children.Add(line2);
        }

        /// <summary>
        /// Sends given command to phone. Phone screen is re-captured after command is executed.
        /// Command is packed into SimpleXamlCommand which is written to a file.
        /// This is then executed by framework.
        /// </summary>
        /// <param name="command">Valid Marble script command.</param>
        /// <param name="executeScriptCommand">Whether script should be executed. When 'null' this depends on whether phone control property is enabled. </param>
        public void SendScriptCommand(string command, bool? executeScriptCommand = null)
        {
            this.CommandHistory += command + "\n";
            Clipboard.SetDataObject(command);

            if ((executeScriptCommand == null && this.IsPhoneControlEnabled) || executeScriptCommand == true)
            {
                this.addScriptCommandToQueue(command);
            }
        }

        private void addScriptCommandToQueue(string command)
        {
            if (string.IsNullOrEmpty(command)) return;
                
            App.ViewModel.MarbleConnector.AddToQueue(
                new ExecuteTestStep(command)
                {
                    CallBackMethod = this.OnScriptCommandDone
                });
        }

        private void addScriptCommandsToQueue(string commandText)
        {
            foreach (string command in commandText.Trim().Split(new string[] { "\n" }, StringSplitOptions.RemoveEmptyEntries))
            {
                // Comments are not added to queue.
                if (command.StartsWith("#")) continue;

                this.addScriptCommandToQueue(command);
            }
        }

        #region [ INotifyPropertyChanged Members ]

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        public void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion [ INotifyPropertyChanged Members ]
    }
}
