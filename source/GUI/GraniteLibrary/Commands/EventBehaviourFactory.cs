namespace MarbleLibrary.Commands
{
    using System;
    using System.Reflection;
    using System.Windows;
    using System.Windows.Input;

    public class EventBehaviourArgs : EventArgs
    {
        public object OriginalSender;
        public EventArgs OriginalEventArgs;

        public ICommand Command;
        public object CommandParameter;
    }

    /// <summary>
    /// Provides a utility class making it easy to execute commands 
    /// when routed events are raised on WPF elements.
    /// Kudos to Samuel Jack
    /// http://archive.msdn.microsoft.com/eventbehaviourfactor
    /// </summary>
    public static class RoutedEventBehaviourFactory
    {
        public static DependencyProperty CreateCommandExecutionEventBehaviour(RoutedEvent routedEvent, string propertyName, Type ownerType)
        {
            var commandProperty = DependencyProperty.RegisterAttached(
                propertyName,
                typeof(ICommand),
                ownerType,
                new PropertyMetadata(null,
                    new ExecuteCommandOnRoutedEventBehaviour(routedEvent).CommandPropertyChangedHandler));

            return commandProperty;
        }

        public static DependencyProperty CreateCommandParameter(DependencyProperty command)
        {
            var target = command.DefaultMetadata.PropertyChangedCallback.Target as ExecuteCommandBehaviour;
            var paramProperty = DependencyProperty.RegisterAttached(
                command.Name + "Parameter",
                typeof(object),
                command.OwnerType,
                new PropertyMetadata(null,
                    target.ParamPropertyChangedHandler));

            return paramProperty;
        }

        /// <summary>
        /// An internal class to handle listening for an event and executing a command,
        /// when a Command is assigned to a particular DependencyProperty
        /// </summary>
        private class ExecuteCommandOnRoutedEventBehaviour : ExecuteCommandBehaviour
        {
            private readonly RoutedEvent _routedEvent;

            public ExecuteCommandOnRoutedEventBehaviour(RoutedEvent routedEvent)
            {
                this._routedEvent = routedEvent;
            }

            /// <summary>
            /// Handles attaching or Detaching Event handlers when a Command is assigned or unassigned
            /// </summary>
            /// <param name="sender"></param>
            /// <param name="oldValue"></param>
            /// <param name="newValue"></param>
            protected override void AdjustEventHandlers(DependencyObject sender, object oldValue, object newValue)
            {
                var element = sender as UIElement;
                if (element == null) { return; }

                if (oldValue != null)
                {
                    element.RemoveHandler(this._routedEvent, new RoutedEventHandler(this.EventHandler));
                }

                if (newValue != null)
                {
                    element.AddHandler(this._routedEvent, new RoutedEventHandler(this.EventHandler));
                }
            }

            protected void EventHandler(object sender, RoutedEventArgs e)
            {
                this.HandleEvent(sender, e);
            }
        }
    }

    /// <summary>
    /// Provides a utility class making it easy to execute commands 
    /// when regular .Net events are raised on WPF elements.
    /// Based on RoutedEventBehaviourFactory.
    /// </summary>
    /// <typeparam name="TO">type of object</typeparam>
    /// <typeparam name="TE">type of event args</typeparam>
    /// <typeparam name="TH">type of event handler</typeparam>
    public static class EventBehaviourFactory<TO, TE, TH>
        where TO : class
        where TE : EventArgs
        where TH : class
    {
        public static DependencyProperty CreateCommandExecutionEventBehaviour(
            string eventName,
            string propertyName,
            Type ownerType)
        {
            var commandProperty = DependencyProperty.RegisterAttached(
                propertyName,
                typeof(ICommand),
                ownerType,
                new PropertyMetadata(null,
                    new ExecuteCommandOnEventBehaviour(typeof(TO).GetEvent(eventName)).CommandPropertyChangedHandler));

            return commandProperty;
        }

        /// <summary>
        /// An internal class to handle listening for an event and executing a command,
        /// when a Command is assigned to a particular DependencyProperty
        /// </summary>
        private class ExecuteCommandOnEventBehaviour : ExecuteCommandBehaviour
        {
            private readonly object _delegate;
            private readonly EventInfo _event;

            public ExecuteCommandOnEventBehaviour(EventInfo ev)
            {
                this._delegate = Delegate.CreateDelegate(typeof(TH), this, "InternalHandleEvent");
                this._event = ev;
            }

            /// <summary>
            /// Handles attaching or Detaching Event handlers when a Command is assigned or unassigned
            /// </summary>
            /// <param name="sender"></param>
            /// <param name="oldValue"></param>
            /// <param name="newValue"></param>
            protected override void AdjustEventHandlers(DependencyObject sender, object oldValue, object newValue)
            {
                var obj = sender as TO;
                if (obj == null) { return; }

                if (oldValue != null)
                {
                    this._event.RemoveEventHandler(obj, (Delegate)this._delegate);
                }

                if (newValue != null)
                {
                    this._event.AddEventHandler(obj, (Delegate)this._delegate);
                }
            }

            private void InternalHandleEvent(object sender, TE e)
            {
                this.HandleEvent(sender, e);
            }
        }
    }

    internal abstract class ExecuteCommandBehaviour
    {
        protected DependencyProperty _commandProperty;
        protected DependencyProperty _paramProperty;

        protected abstract void AdjustEventHandlers(DependencyObject sender, object oldValue, object newValue);

        protected void HandleEvent(object sender, EventArgs e)
        {
            var dp = sender as DependencyObject;
            if (dp == null)
            {
                return;
            }

            var command = dp.GetValue(this._commandProperty) as ICommand;
            if (command == null)
            {
                return;
            }

            var args = new EventBehaviourArgs
            {
                OriginalSender = sender,
                OriginalEventArgs = e,
                Command = command,
                CommandParameter = this._paramProperty == null ? null : dp.GetValue(this._paramProperty)
            };

            if (command.CanExecute(args))
            {
                command.Execute(args);
            }
        }

        /// <summary>
        /// Listens for a change in the DependencyProperty that we are assigned to, and
        /// adjusts the EventHandlers accordingly
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void CommandPropertyChangedHandler(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            // the first time the property changes,
            // make a note of which property we are supposed
            // to be watching
            if (this._commandProperty == null)
            {
                this._commandProperty = e.Property;
            }

            var oldValue = e.OldValue;
            var newValue = e.NewValue;

            this.AdjustEventHandlers(sender, oldValue, newValue);
        }

        /// <summary>
        /// Listens for a change in the DependencyProperty that we are assigned to
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void ParamPropertyChangedHandler(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            // the first time the property changes,
            // make a note of which property we are supposed
            // to be watching
            if (this._paramProperty == null)
            {
                this._paramProperty = e.Property;
            }
        }
    }
}
