using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using TestAutomation.Bridge.ScriptingTools;

namespace TestAutomation.Bridge.Tracing
{
    /// <summary>
    /// Handler delegate for trace message subscriptions
    /// </summary>
    /// <param name="message">The trace message</param>
    public delegate void TraceMessageHandler(string message);

    /// <summary>
    /// Class for publishing trace messages over the appdomain
    /// </summary>
    public static class Trace
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="parent"></param>
        /// <returns></returns>
        private static string LookForIdentifier(object sender, object parent)
        {
            if (sender == null)
            {
                return null;
            }

            if (sender.GetType().Equals(typeof(WeakReference)))
            {
                sender = (sender as WeakReference).Target;
            }

            if (sender.GetType().Equals(typeof(DynamicProxy)))
            {
                sender = (sender as DynamicProxy).__target_instance__;
                if (sender == null)
                {
                    return null;
                }
            }

            var fields = sender.GetType().GetFields(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance)
                .ToList().FindAll(f => f.FieldType.Assembly == typeof(TABConnection).Assembly || f.FieldType == typeof(WeakReference));

            if (parent != null)
            {
                fields.RemoveAll(f => f.FieldType == parent.GetType());
            }

            var tabField = fields.Find(f => f.FieldType == typeof(TABConnection));

            if (tabField != null)
            {
                var tab = tabField.GetValue(sender) as TABConnection;
                return tab.SerialNumber;
            }
                       
            foreach (var f in fields)
            {
                var obj = f.GetValue(sender);
                if (obj != null)
                {
                    var identity = LookForIdentifier(obj, sender);
                    if (identity != null)
                    {
                        return identity;
                    }
                }
            }
            return null;
        }
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <returns></returns>
        private static string LookForIdentifier(object sender)
        {
            return LookForIdentifier(sender, null);
        }
        
        /// <summary>
        /// Publishes a trace message over the appdomain
        /// </summary>
        /// <param name="sender">Sender object</param>
        /// <param name="message">The message to publish</param>
        /// <param name="args">Arguments for formatting the message</param>
        public static void WriteMessage(object sender, string message, params object[] args)
        {
            if (!string.IsNullOrEmpty(message))
            {
                var msg = string.Format(message, args);
                
                var senderName = sender != null ? sender.ToString() : "";
                var index = senderName.LastIndexOf(".");
                if (index > 0)
                {
                    senderName = senderName.Substring(index + 1);
                }

                msg = senderName != "" ? string.Format("{0}.{1}", senderName, msg) : string.Format("{0}", msg);

                TraceListener.BroadcastMessage(msg, LookForIdentifier(sender));
            }
        }
    }

    /// <summary>
    /// Class via which to subscribe for trace message published by anyone in the appdomain
    /// </summary>
    public static class TraceListener
    {
        private static Lazy<List<Tuple<string, TraceMessageHandler>>> m_listeners;

        /// <summary>
        /// (Lazy) inits the listener collection
        /// </summary>
        private static void Init()
        {
            if (m_listeners == null)
            {
                m_listeners = new Lazy<List<Tuple<string, TraceMessageHandler>>>(() =>
                    {
                        return new List<Tuple<string, TraceMessageHandler>>();
                    });
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="listener"></param>
        public static void AddListener(TraceMessageHandler listener)
        {
            AddListener(null, listener);
        }

        /// <summary>
        /// Adds a trace message listener to the subscription list
        /// </summary>
        /// <param name="listener">The listener to add</param>
        public static void AddListener(string identifier, TraceMessageHandler listener)
        {
            Init();

            if (listener != null && !m_listeners.Value.Exists(l => l.Item2.Method.Equals(listener.Method)))
            {
                m_listeners.Value.Add(new Tuple<string, TraceMessageHandler>(identifier, listener));
            }
        }

        /// <summary>
        /// Removes a trace message listener from the subscription list
        /// </summary>
        /// <param name="listener">The listener to remove</param>
        public static void RemoveListeners(TraceMessageHandler listener)
        {
            Init();

            if (listener != null)
            {
                var lnr = m_listeners.Value.Find(l => l.Item2.Method.Equals(listener.Method));
                if (lnr != null)
                {
                    m_listeners.Value.Remove(lnr);
                }
            }
        }

        /// <summary>
        /// Broadcasts a message to all the listeners
        /// </summary>
        /// <param name="message">The message to broadcast</param>
        internal static void BroadcastMessage(string message, string identity)
        {
            if (m_listeners != null)
            {
                for (int i = 0; i < m_listeners.Value.Count; i++)
                {
                    if (m_listeners.Value[i].Item2 != null)
                    {
                        if ((identity != null && m_listeners.Value[i].Item1 != null && m_listeners.Value[i].Item1.Equals(identity)) 
                            || (identity == null) || (m_listeners.Value[i].Item1 == null))
                        {
                            m_listeners.Value[i].Item2(message);
                        }
                    }
                }
            }
        }
    }
}
