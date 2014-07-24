﻿namespace MarbleLibrary.Commands
{
    using System;
    using System.Collections.Generic;
    using System.Windows.Input;

    /// <summary>
    ///     This class allows delegating the commanding logic to methods passed as parameters,
    ///     and enables a View to bind commands to objects that are not part of the element tree.
    /// </summary>
    public class DelegateCommand : ICommand
    {
        #region Constructors

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action executeMethod)
            : this(executeMethod, null, false)
        {
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action executeMethod, Func<bool> canExecuteMethod)
            : this(executeMethod, canExecuteMethod, false)
        {
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action executeMethod, Func<bool> canExecuteMethod, bool isAutomaticRequeryDisabled)
        {
            if (executeMethod == null)
            {
                throw new ArgumentNullException("executeMethod");
            }

            this._executeMethod = executeMethod;
            this._canExecuteMethod = canExecuteMethod;
            this._isAutomaticRequeryDisabled = isAutomaticRequeryDisabled;
        }

        #endregion

        #region Public Methods

        /// <summary>
        ///     Method to determine if the command can be executed
        /// </summary>
        public bool CanExecute()
        {
            if (this._canExecuteMethod != null)
            {
                return this._canExecuteMethod();
            }
            return true;
        }

        /// <summary>
        ///     Execution of the command
        /// </summary>
        public void Execute()
        {
            if (this._executeMethod != null)
            {
                this._executeMethod();
            }
        }

        /// <summary>
        ///     Property to enable or disable CommandManager's automatic requery on this command
        /// </summary>
        public bool IsAutomaticRequeryDisabled
        {
            get
            {
                return this._isAutomaticRequeryDisabled;
            }
            set
            {
                if (this._isAutomaticRequeryDisabled != value)
                {
                    if (value)
                    {
                        CommandManagerHelper.RemoveHandlersFromRequerySuggested(this._canExecuteChangedHandlers);
                    }
                    else
                    {
                        CommandManagerHelper.AddHandlersToRequerySuggested(this._canExecuteChangedHandlers);
                    }
                    this._isAutomaticRequeryDisabled = value;
                }
            }
        }

        /// <summary>
        ///     Raises the CanExecuteChaged event
        /// </summary>
        public void RaiseCanExecuteChanged()
        {
            this.OnCanExecuteChanged();
        }

        /// <summary>
        ///     Protected virtual method to raise CanExecuteChanged event
        /// </summary>
        protected virtual void OnCanExecuteChanged()
        {
            CommandManagerHelper.CallWeakReferenceHandlers(this._canExecuteChangedHandlers);
        }

        #endregion

        #region ICommand Members

        /// <summary>
        ///     ICommand.CanExecuteChanged implementation
        /// </summary>
        public event EventHandler CanExecuteChanged
        {
            add
            {
                if (!this._isAutomaticRequeryDisabled)
                {
                    CommandManager.RequerySuggested += value;
                }
                CommandManagerHelper.AddWeakReferenceHandler(ref this._canExecuteChangedHandlers, value, 2);
            }
            remove
            {
                if (!this._isAutomaticRequeryDisabled)
                {
                    CommandManager.RequerySuggested -= value;
                }
                CommandManagerHelper.RemoveWeakReferenceHandler(this._canExecuteChangedHandlers, value);
            }
        }

        bool ICommand.CanExecute(object parameter)
        {
            return this.CanExecute();
        }

        void ICommand.Execute(object parameter)
        {
            this.Execute();
        }

        #endregion

        #region Data

        private readonly Action _executeMethod = null;
        private readonly Func<bool> _canExecuteMethod = null;
        private bool _isAutomaticRequeryDisabled = false;
        private List<WeakReference> _canExecuteChangedHandlers;

        #endregion
    }

    /// <summary>
    ///     This class allows delegating the commanding logic to methods passed as parameters,
    ///     and enables a View to bind commands to objects that are not part of the element tree.
    /// </summary>
    /// <typeparam name="T">Type of the parameter passed to the delegates</typeparam>
    public class DelegateCommand<T> : ICommand
    {
        #region Constructors

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action<T> executeMethod)
            : this(executeMethod, null, false)
        {
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action<T> executeMethod, Func<T, bool> canExecuteMethod)
            : this(executeMethod, canExecuteMethod, false)
        {
        }

        /// <summary>
        ///     Constructor
        /// </summary>
        public DelegateCommand(Action<T> executeMethod, Func<T, bool> canExecuteMethod, bool isAutomaticRequeryDisabled)
        {
            if (executeMethod == null)
            {
                throw new ArgumentNullException("executeMethod");
            }

            this._executeMethod = executeMethod;
            this._canExecuteMethod = canExecuteMethod;
            this._isAutomaticRequeryDisabled = isAutomaticRequeryDisabled;
        }

        #endregion

        #region Public Methods

        /// <summary>
        ///     Method to determine if the command can be executed
        /// </summary>
        public bool CanExecute(T parameter)
        {
            if (this._canExecuteMethod != null)
            {
                return this._canExecuteMethod(parameter);
            }
            return true;
        }

        /// <summary>
        ///     Execution of the command
        /// </summary>
        public void Execute(T parameter)
        {
            if (this._executeMethod != null)
            {
                this._executeMethod(parameter);
            }
        }

        /// <summary>
        ///     Raises the CanExecuteChaged event
        /// </summary>
        public void RaiseCanExecuteChanged()
        {
            this.OnCanExecuteChanged();
        }

        /// <summary>
        ///     Protected virtual method to raise CanExecuteChanged event
        /// </summary>
        protected virtual void OnCanExecuteChanged()
        {
            CommandManagerHelper.CallWeakReferenceHandlers(this._canExecuteChangedHandlers);
        }

        /// <summary>
        ///     Property to enable or disable CommandManager's automatic requery on this command
        /// </summary>
        public bool IsAutomaticRequeryDisabled
        {
            get
            {
                return this._isAutomaticRequeryDisabled;
            }
            set
            {
                if (this._isAutomaticRequeryDisabled != value)
                {
                    if (value)
                    {
                        CommandManagerHelper.RemoveHandlersFromRequerySuggested(this._canExecuteChangedHandlers);
                    }
                    else
                    {
                        CommandManagerHelper.AddHandlersToRequerySuggested(this._canExecuteChangedHandlers);
                    }
                    this._isAutomaticRequeryDisabled = value;
                }
            }
        }

        #endregion

        #region ICommand Members

        /// <summary>
        ///     ICommand.CanExecuteChanged implementation
        /// </summary>
        public event EventHandler CanExecuteChanged
        {
            add
            {
                if (!this._isAutomaticRequeryDisabled)
                {
                    CommandManager.RequerySuggested += value;
                }
                CommandManagerHelper.AddWeakReferenceHandler(ref this._canExecuteChangedHandlers, value, 2);
            }
            remove
            {
                if (!this._isAutomaticRequeryDisabled)
                {
                    CommandManager.RequerySuggested -= value;
                }
                CommandManagerHelper.RemoveWeakReferenceHandler(this._canExecuteChangedHandlers, value);
            }
        }

        bool ICommand.CanExecute(object parameter)
        {
            // if T is of value type and the parameter is not
            // set yet, then return false if CanExecute delegate
            // exists, else return true
            if (parameter == null &&
                typeof(T).IsValueType)
            {
                return (this._canExecuteMethod == null);
            }
            return this.CanExecute((T)parameter);
        }

        void ICommand.Execute(object parameter)
        {
            this.Execute((T)parameter);
        }

        #endregion

        #region Data

        private readonly Action<T> _executeMethod = null;
        private readonly Func<T, bool> _canExecuteMethod = null;
        private bool _isAutomaticRequeryDisabled = false;
        private List<WeakReference> _canExecuteChangedHandlers;

        #endregion
    }

    /////// <summary>
    ///////     This class allows delegating the commanding logic to methods passed as parameters,
    ///////     and enables a View to bind commands to objects that are not part of the element tree.
    /////// </summary>
    /////// <typeparam name="T1">Type of the first parameter passed to the delegates</typeparam>
    /////// <typeparam name="T2">Type of the second parameter passed to the delegates</typeparam>
    ////public class DelegateCommand<T1, T2> : ICommand
    ////{
    ////    #region Constructors

    ////    /// <summary>
    ////    ///     Constructor
    ////    /// </summary>
    ////    public DelegateCommand(Action<T1, T2> executeMethod)
    ////        : this(executeMethod, null, false)
    ////    {
    ////    }

    ////    /// <summary>
    ////    ///     Constructor
    ////    /// </summary>
    ////    public DelegateCommand(Action<T1, T2> executeMethod, Func<T1, T2, bool> canExecuteMethod)
    ////        : this(executeMethod, canExecuteMethod, false)
    ////    {
    ////    }

    ////    /// <summary>
    ////    ///     Constructor
    ////    /// </summary>
    ////    public DelegateCommand(Action<T1, T2> executeMethod, Func<T1, T2, bool> canExecuteMethod, bool isAutomaticRequeryDisabled)
    ////    {
    ////        if (executeMethod == null)
    ////        {
    ////            throw new ArgumentNullException("executeMethod");
    ////        }

    ////        this._executeMethod = executeMethod;
    ////        this._canExecuteMethod = canExecuteMethod;
    ////        this._isAutomaticRequeryDisabled = isAutomaticRequeryDisabled;
    ////    }

    ////    #endregion

    ////    #region Public Methods

    ////    /// <summary>
    ////    ///     Method to determine if the command can be executed
    ////    /// </summary>
    ////    public bool CanExecute(T1 parameter1, T2 parameter2)
    ////    {
    ////        if (this._canExecuteMethod != null)
    ////        {
    ////            return this._canExecuteMethod(parameter1, parameter2);
    ////        }
    ////        return true;
    ////    }

    ////    /// <summary>
    ////    ///     Execution of the command
    ////    /// </summary>
    ////    public void Execute(T1 parameter1, T2 parameter2)
    ////    {
    ////        if (this._executeMethod != null)
    ////        {
    ////            this._executeMethod(parameter1, parameter2);
    ////        }
    ////    }

    ////    /// <summary>
    ////    ///     Raises the CanExecuteChaged event
    ////    /// </summary>
    ////    public void RaiseCanExecuteChanged()
    ////    {
    ////        this.OnCanExecuteChanged();
    ////    }

    ////    /// <summary>
    ////    ///     Protected virtual method to raise CanExecuteChanged event
    ////    /// </summary>
    ////    protected virtual void OnCanExecuteChanged()
    ////    {
    ////        CommandManagerHelper.CallWeakReferenceHandlers(this._canExecuteChangedHandlers);
    ////    }

    ////    /// <summary>
    ////    ///     Property to enable or disable CommandManager's automatic requery on this command
    ////    /// </summary>
    ////    public bool IsAutomaticRequeryDisabled
    ////    {
    ////        get
    ////        {
    ////            return this._isAutomaticRequeryDisabled;
    ////        }
    ////        set
    ////        {
    ////            if (this._isAutomaticRequeryDisabled != value)
    ////            {
    ////                if (value)
    ////                {
    ////                    CommandManagerHelper.RemoveHandlersFromRequerySuggested(this._canExecuteChangedHandlers);
    ////                }
    ////                else
    ////                {
    ////                    CommandManagerHelper.AddHandlersToRequerySuggested(this._canExecuteChangedHandlers);
    ////                }
    ////                this._isAutomaticRequeryDisabled = value;
    ////            }
    ////        }
    ////    }

    ////    #endregion

    ////    #region ICommand Members

    ////    /// <summary>
    ////    ///     ICommand.CanExecuteChanged implementation
    ////    /// </summary>
    ////    public event EventHandler CanExecuteChanged
    ////    {
    ////        add
    ////        {
    ////            if (!this._isAutomaticRequeryDisabled)
    ////            {
    ////                CommandManager.RequerySuggested += value;
    ////            }
    ////            CommandManagerHelper.AddWeakReferenceHandler(ref this._canExecuteChangedHandlers, value, 2);
    ////        }
    ////        remove
    ////        {
    ////            if (!this._isAutomaticRequeryDisabled)
    ////            {
    ////                CommandManager.RequerySuggested -= value;
    ////            }
    ////            CommandManagerHelper.RemoveWeakReferenceHandler(this._canExecuteChangedHandlers, value);
    ////        }
    ////    }

    ////    bool ICommand.CanExecute(object parameter1)
    ////    {
    ////        // if T is of value type and the parameter is not
    ////        // set yet, then return false if CanExecute delegate
    ////        // exists, else return true
    ////        if (parameter1 == null &&
    ////            typeof(T1).IsValueType)
    ////        {
    ////            return (this._canExecuteMethod == null);
    ////        }
    ////        return this.CanExecute((T1)parameter1);
    ////    }

    ////    void ICommand.Execute(object parameter)
    ////    {
    ////        this.Execute((T)parameter);
    ////    }

    ////    #endregion

    ////    #region Data

    ////    private readonly Action<T1, T2> _executeMethod = null;
    ////    private readonly Func<T1, T2, bool> _canExecuteMethod = null;

    ////    private bool _isAutomaticRequeryDisabled = false;
    ////    private List<WeakReference> _canExecuteChangedHandlers;

    ////    #endregion
    ////}

    /// <summary>
    ///     This class contains methods for the CommandManager that help avoid memory leaks by
    ///     using weak references.
    /// </summary>
    internal class CommandManagerHelper
    {
        internal static void CallWeakReferenceHandlers(List<WeakReference> handlers)
        {
            if (handlers != null)
            {
                // Take a snapshot of the handlers before we call out to them since the handlers
                // could cause the array to me modified while we are reading it.

                EventHandler[] callees = new EventHandler[handlers.Count];
                int count = 0;

                for (int i = handlers.Count - 1; i >= 0; i--)
                {
                    WeakReference reference = handlers[i];
                    EventHandler handler = reference.Target as EventHandler;
                    if (handler == null)
                    {
                        // Clean up old handlers that have been collected
                        handlers.RemoveAt(i);
                    }
                    else
                    {
                        callees[count] = handler;
                        count++;
                    }
                }

                // Call the handlers that we snapshotted
                for (int i = 0; i < count; i++)
                {
                    EventHandler handler = callees[i];
                    handler(null, EventArgs.Empty);
                }
            }
        }

        internal static void AddHandlersToRequerySuggested(List<WeakReference> handlers)
        {
            if (handlers != null)
            {
                foreach (WeakReference handlerRef in handlers)
                {
                    EventHandler handler = handlerRef.Target as EventHandler;
                    if (handler != null)
                    {
                        CommandManager.RequerySuggested += handler;
                    }
                }
            }
        }

        internal static void RemoveHandlersFromRequerySuggested(List<WeakReference> handlers)
        {
            if (handlers != null)
            {
                foreach (WeakReference handlerRef in handlers)
                {
                    EventHandler handler = handlerRef.Target as EventHandler;
                    if (handler != null)
                    {
                        CommandManager.RequerySuggested -= handler;
                    }
                }
            }
        }

        internal static void AddWeakReferenceHandler(ref List<WeakReference> handlers, EventHandler handler)
        {
            AddWeakReferenceHandler(ref handlers, handler, -1);
        }

        internal static void AddWeakReferenceHandler(ref List<WeakReference> handlers, EventHandler handler, int defaultListSize)
        {
            if (handlers == null)
            {
                handlers = (defaultListSize > 0 ? new List<WeakReference>(defaultListSize) : new List<WeakReference>());
            }

            handlers.Add(new WeakReference(handler));
        }

        internal static void RemoveWeakReferenceHandler(List<WeakReference> handlers, EventHandler handler)
        {
            if (handlers != null)
            {
                for (int i = handlers.Count - 1; i >= 0; i--)
                {
                    WeakReference reference = handlers[i];
                    EventHandler existingHandler = reference.Target as EventHandler;
                    if ((existingHandler == null) || (existingHandler == handler))
                    {
                        // Clean up old handlers that have been collected
                        // in addition to the handler that is to be removed.
                        handlers.RemoveAt(i);
                    }
                }
            }
        }
    }
}