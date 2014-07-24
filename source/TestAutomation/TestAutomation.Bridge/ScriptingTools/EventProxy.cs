using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace TestAutomation.Bridge.ScriptingTools
{
    /// <summary>
    /// Class for adding and removing events for the proxied object
    /// </summary>
    public class EventProxy : DynamicObject
    {
        private EventInfo m_event;
        private object m_instance;

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="event">Event for which to add or remove</param>
        /// <param name="instance">The proxied object</param>
        private EventProxy(EventInfo @event, object instance)
        {
            m_event = @event;
            m_instance = instance;
        }

        /// <summary>
        /// Called when event handler is being added or removed for/from the event
        /// </summary>
        /// <param name="binder"></param>
        /// <param name="arg"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
        {
            result = this; //Due to setter in parent proxy class can see that value is coming from here

            if (binder.Operation == System.Linq.Expressions.ExpressionType.AddAssign)
            {
                m_event.AddEventHandler(m_instance, (Delegate)arg);
                return true;
            }
            else if (binder.Operation == System.Linq.Expressions.ExpressionType.SubtractAssign)
            {
                m_event.RemoveEventHandler(m_instance, (Delegate)arg);
                return true;
            }

            return false;
        }

        /// <summary>
        /// Creates a new EventProxy
        /// </summary>
        /// <param name="event">Event for which to create the proxy</param>
        /// <param name="instance">Owner instanc of the event</param>
        /// <returns>New EventProxy instance</returns>
        public static EventProxy Create(EventInfo @event, object instance)
        {
            return new EventProxy(@event, instance);
        }
    }
}
