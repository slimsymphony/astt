using Managed.Adb;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Serialization;

namespace TestAutomation.Bridge
{
    public static class Extensions
    {
        public static void Close(this Socket sck, bool wait)
        {
            if (!wait)
            {
                sck.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(true, 0));
            }
            sck.Close();
        }

        public static void SendLine(this Socket sck, string line)
        {
            sck.Send(Encoding.Default.GetBytes(line + "\n"));
        }

        public static SortedSet<T> TailSet<T>(this SortedSet<T> set, T start)
        {
            return set.GetViewBetween(start, set.Max);
        }

        public static SortedSet<T> HeadSet<T>(this SortedSet<T> set, T end)
        {
            return set.GetViewBetween(set.Min, end);
        }

        public static string substring(this string str, int startIndex)
        {
            return str.Substring(startIndex);
        }

        public static string substring(this string str, int startIndex, int endIndex)
        {
            return str.Substring(startIndex, endIndex - startIndex);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public class BooleanResultReader : MultiLineReceiver
    {
        private Regex m_pattern = new Regex(".*?\\([0-9]{8} ([0-9]{8}).*", RegexOptions.Compiled);
        private bool[] m_result;

        public BooleanResultReader(bool[] result)
        {
            m_result = result;
        }

        protected override void ProcessNewLines(string[] lines)
        {
            if (lines.Length > 0)
            {
                Match matcher = m_pattern.Match(lines[0]);
                if (matcher.Success)
                {
                    if (int.Parse(matcher.Groups[1].Value) == 1)
                    {
                        m_result[0] = true;
                    }
                }
            }
        }

        public override bool IsCancelled { get { return false; } }

    }

    /// <summary>
    /// 
    /// </summary>
    [XmlType("window")]
    public class Window
    {
        private ViewServerClient m_client;

        public Window()
        { }

        internal Window(ViewServerClient client)
        {
            m_client = client;
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("id")]
        public int Id { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("name")]
        public string Name { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public string Encode()
        {
            return Id.ToString("X4");
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlIgnore]
        public bool IsFocused
        {
            get
            {
                return m_client.GetFocusedWindow() == Id;
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public enum ProfileRating
    {
        /// <summary>
        /// 
        /// </summary>
        Red, 
        
        /// <summary>
        /// 
        /// </summary>
        Yellow, 
        
        /// <summary>
        /// 
        /// </summary>
        Green, 
        
        /// <summary>
        /// 
        /// </summary>
        None
    }

    /// <summary>
    /// 
    /// </summary>
    [XmlType("viewNode")]
    public class ViewNode
    {
        private const double RED_THRESHOLD = 0.8;

        private const double YELLOW_THRESHOLD = 0.5;

        public const string MISCELLANIOUS = "miscellaneous";

        public ViewNode()
        { }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="window"></param>
        /// <param name="parent"></param>
        /// <param name="data"></param>
        public ViewNode(Window window, ViewNode parent, string data)
        {
            Window = window;
            Parent = parent;

            Properties = new List<Property>();
            NamedProperties = new Dictionary<string, Property>();
            Children = new List<ViewNode>();
            Categories = new SortedSet<string>();

            MeasureRating = ProfileRating.None;
            LayoutRating = ProfileRating.None;
            DrawRating = ProfileRating.None;

            ImageReferences = 1;

            Index = Parent == null ? 0 : Parent.Children.Count;
            if (Parent != null)
            {
                Parent.Children.Add(this);
            }
            int delimIndex = data.IndexOf('@');
            if (delimIndex < 0)
            {
                throw new ArgumentException("Invalid format for ViewNode, missing @: " + data);
            }
            Name = data.substring(0, delimIndex);
            data = data.substring(delimIndex + 1);
            delimIndex = data.IndexOf(' ');
            HashCode = data.substring(0, delimIndex);

            if (data.Length > delimIndex + 1)
            {
                LoadProperties(data.substring(delimIndex + 1).Trim());
            }
            else
            {
                // defaults in case properties are not available
                Id = "unknown";
                Width = Height = 10;
            }

            MeasureTime = -1;
            LayoutTime = -1;
            DrawTime = -1;
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("id")]
        public string Id { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("name")]
        public string Name { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("hashCode")]
        public string HashCode { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlArray("properties")]
        public List<Property> Properties { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlIgnore]
        public Dictionary<string, Property> NamedProperties { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlIgnore]
        public ViewNode Parent { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlArray("children")]
        public List<ViewNode> Children { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("left")]
        public int Left { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("top")]
        public int Top { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public int Width { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public int Height { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("scrollX")]
        public int ScrollX { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("scrollY")]
        public int ScrollY { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("paddingLeft")]
        public int PaddingLeft { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("paddingRight")]
        public int PaddingRight { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("paddingTop")]
        public int PaddingTop { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("paddingBottom")]
        public int PaddingBottom { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("marginLeft")]
        public int MarginLeft { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("marginRight")]
        public int MarginRight { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("marginTop")]
        public int MarginTop { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("marginBottom")]
        public int MarginBottom { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("baseline")]
        public int Baseline { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("willNotDraw")]
        public bool WillNotDraw { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("hasMargins")]
        public bool HasMargins { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("hasFocus")]
        public bool HasFocus { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("index")]
        public int Index { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("measureTime")]
        public double MeasureTime { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("layoutTime")]
        public double LayoutTime { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("drawTime")]
        public double DrawTime { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("measureRating")]
        public ProfileRating MeasureRating { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("layoutRating")]
        public ProfileRating LayoutRating { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("drawRating")]
        public ProfileRating DrawRating { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlIgnore]
        public SortedSet<string> Categories { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlElement("window")]
        public Window Window { get; set; }

        //public Image image;

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("imageRefereces")]
        public int ImageReferences { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("viewCount")]
        public int ViewCount { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("filtered")]
        public bool Filtered { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlIgnore]
        public int ProtocolVersion { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filename"></param>
        public void Dump(string filename)
        {
            XmlSerializer x = new XmlSerializer(GetType());
            TextWriter writer = new StreamWriter(filename);
            x.Serialize(writer, this);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public XmlDocument Dump()
        {
            var doc = new XmlDocument();
            XmlSerializer x = new XmlSerializer(GetType());
            using (var ms = new MemoryStream())
            {
                x.Serialize(ms, this);
                ms.Position = 0;
                doc.Load(ms);
            }
            return doc;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="data"></param>
        private void LoadProperties(string data)
        {
            int start = 0;
            bool stop;
            do
            {
                int index = data.IndexOf('=', start);
                Property property = new Property();
                property.Name = data.substring(start, index);

                int index2 = data.IndexOf(',', index + 1);
                int length = int.Parse(data.substring(index + 1, index2));
                start = index2 + 1 + length;
                property.Value = data.substring(index2 + 1, index2 + 1 + length);

                Properties.Add(property);
                NamedProperties[property.Name] = property;

                stop = start >= data.Length;
                if (!stop)
                {
                    start += 1;
                }
            } while (!stop);

            Properties.Sort(delegate(Property source, Property destination)
            {
                return source.Name.CompareTo(destination.Name);
            });

            Id = NamedProperties["mID"].Value;

            Left = NamedProperties.ContainsKey("mLeft") ? GetInt("mLeft", 0) : GetInt("layout:mLeft", 0);
            Top = NamedProperties.ContainsKey("mTop") ? GetInt("mTop", 0) : GetInt("layout:mTop", 0);
            Width = NamedProperties.ContainsKey("getWidth()") ? GetInt("getWidth()", 0) : GetInt("layout:getWidth()", 0);
            Height = NamedProperties.ContainsKey("getHeight()") ? GetInt("getHeight()", 0) : GetInt("layout:getHeight()", 0);
            ScrollX = NamedProperties.ContainsKey("mScrollX") ? GetInt("mScrollX", 0) : GetInt("scrolling:mScrollX", 0);
            ScrollY = NamedProperties.ContainsKey("mScrollY") ? GetInt("mScrollY", 0) : GetInt("scrolling:mScrollY", 0);
            PaddingLeft = NamedProperties.ContainsKey("mPaddingLeft") ? GetInt("mPaddingLeft", 0) : GetInt("padding:mPaddingLeft", 0);
            PaddingRight = NamedProperties.ContainsKey("mPaddingRight") ? GetInt("mPaddingRight", 0) : GetInt("padding:mPaddingRight", 0);
            PaddingTop = NamedProperties.ContainsKey("mPaddingTop") ? GetInt("mPaddingTop", 0) : GetInt("padding:mPaddingTop", 0);
            PaddingBottom = NamedProperties.ContainsKey("mPaddingBottom") ? GetInt("mPaddingBottom", 0) : GetInt("padding:mPaddingBottom", 0);
            MarginLeft = NamedProperties.ContainsKey("layout_leftMargin") ? GetInt("layout_leftMargin", int.MinValue) : GetInt("layout:layout_leftMargin", int.MinValue);
            MarginRight = NamedProperties.ContainsKey("layout_rightMargin") ? GetInt("layout_rightMargin", int.MinValue) : GetInt("layout:layout_rightMargin", int.MinValue);
            MarginTop = NamedProperties.ContainsKey("layout_topMargin") ? GetInt("layout_topMargin", int.MinValue) : GetInt("layout:layout_topMargin", int.MinValue);
            MarginBottom = NamedProperties.ContainsKey("layout_bottomMargin") ? GetInt("layout_bottomMargin", int.MinValue) : GetInt("layout:layout_bottomMargin", int.MinValue);
            Baseline = NamedProperties.ContainsKey("getBaseline()") ? GetInt("getBaseline()", 0) : GetInt("layout:getBaseline()", 0);
            WillNotDraw = NamedProperties.ContainsKey("willNotDraw()") ? GetBoolean("willNotDraw()", false) : GetBoolean("drawing:willNotDraw()", false);
            HasFocus = NamedProperties.ContainsKey("hasFocus()") ? GetBoolean("hasFocus()", false) : GetBoolean("focus:hasFocus()", false);
            HasMargins = MarginLeft != int.MinValue && MarginRight != int.MinValue && MarginTop != int.MinValue && MarginBottom != int.MinValue;

            foreach (var name in NamedProperties.Keys)
            {
                int index = name.IndexOf(':');
                if (index != -1)
                {
                    Categories.Add(name.substring(0, index));
                }
            }
            if (Categories.Count != 0)
            {
                Categories.Add(MISCELLANIOUS);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        private int GetInt(string name, int defaultValue)
        {
            if (NamedProperties.ContainsKey(name))
            {
                Property p = NamedProperties[name];
                int value;
                if (int.TryParse(p.Value, out value))
                {
                    return value;
                }
            }
            return defaultValue;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        private bool GetBoolean(string name, bool defaultValue)
        {
            if (NamedProperties.ContainsKey(name))
            {
                Property p = NamedProperties[name];
                bool value;
                if (bool.TryParse(p.Value, out value))
                {
                    return value;
                }
            }
            return defaultValue;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    [XmlType("property")]
    public class Property 
    {
        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("name")]
        public string Name { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("value")]       
        public string Value { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Name + '=' + Value;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public sealed class ViewServerInfo 
    {
        /// <summary>
        /// 
        /// </summary>
        public int ProtocolVersion { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public int ServerVersion { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="serverVersion"></param>
        /// <param name="protocolVersion"></param>
        internal ViewServerInfo(int serverVersion, int protocolVersion) 
        {
            ProtocolVersion = protocolVersion;
            ServerVersion = serverVersion;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public sealed class ViewServerClient
    {
        private const int DEFAULT_SERVER_PORT = 4939;

        // These codes must match the auto-generated codes in IWindowManager.java
        // See IWindowManager.aidl as well
        private const int SERVICE_CODE_START_SERVER = 1;

        private const int SERVICE_CODE_STOP_SERVER = 2;

        private const int SERVICE_CODE_IS_SERVER_RUNNING = 3;
        
        private TABConnection m_tab;

        /// <summary>
        /// 
        /// </summary>
        internal ViewServerClient(TABConnection tab)
        {
            m_tab = tab;
        }

        /// <summary>
        /// 
        /// </summary>
        public int ServerVersion { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public int ProtocolVersion { get; private set; }

        /// <summary>
        /// 
        /// </summary>
        public bool IsConnected
        {
            get
            {
                if (IsServerRunning())
                {
                    Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    try
                    {
                        s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                        return true;
                    }
                    catch
                    {
                        return false;
                    }
                    finally
                    {
                        s.Close(false);
                        s.Dispose();
                    }
                }
                return false;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool Connect()
        {
            bool isConnected = IsConnected;
            if (!isConnected)
            {
                isConnected = CreatePortForward() && StartServer();
            }
            if (isConnected)
            {
                ServerVersion = GetServerVersion();
                ProtocolVersion = GetServerProtocolVersion();
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Disconnect()
        {
            if (IsConnected)
            {
                StopServer(); //&& RemovePortForward();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool StartServer()
        {
            return StartServer(DEFAULT_SERVER_PORT);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="port"></param>
        /// <returns></returns>
        private bool StartServer(int port)
        {
            bool[] result = new bool[1];

            if (m_tab.State == DeviceState.Online)
            {
                m_tab.ExecuteShellCommand(BuildStartServerShellCommand(port),
                        new BooleanResultReader(result));
            }

            return result[0];
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool StopServer()
        {
            bool[] result = new bool[1];

            if (m_tab.State == DeviceState.Online)
            {
                m_tab.ExecuteShellCommand(BuildStopServerShellCommand(),
                        new BooleanResultReader(result));
            }

            return result[0];
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool IsServerRunning()
        {
            bool[] result = new bool[1];

            if (m_tab.State == DeviceState.Online)
            {
                m_tab.ExecuteShellCommand(BuildIsServerRunningShellCommand(),
                        new BooleanResultReader(result));

                //if (!result[0])
                //{
                //    //FIX
                //    if (ProtocolVersion > 2)
                //    {
                //        result[0] = true;
                //    }
                //}
            }

            return result[0];
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="port"></param>
        /// <returns></returns>
        private string BuildStartServerShellCommand(int port)
        {
            return string.Format("service call window {0} i32 {1}", SERVICE_CODE_START_SERVER, port);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private string BuildStopServerShellCommand()
        {
            return string.Format("service call window {0}", SERVICE_CODE_STOP_SERVER);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private string BuildIsServerRunningShellCommand()
        {
            return string.Format("service call window {0}", SERVICE_CODE_IS_SERVER_RUNNING);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private bool CreatePortForward()
        {
            return m_tab.CreateForward(DEFAULT_SERVER_PORT, DEFAULT_SERVER_PORT);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public ViewNode GetFocusedView()
        {
            int winId = GetFocusedWindow();
            foreach (var win in GetWindows())
            {
                if (win.Id == winId)
                {
                    return LoadWindowData(win);
                }
            }
            return null;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public int GetFocusedWindow()
        {
            using (Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                try
                {
                    s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                    s.Blocking = true;
                    s.SendLine("GET_FOCUS");
                    var buffer = new byte[100];
                    int len = s.Receive(buffer);
                    s.Close(false);
                    var line = Encoding.Default.GetString(buffer, 0, len);
                    if (string.IsNullOrEmpty(line))
                    {
                        return -1;
                    }
                    return Convert.ToInt32(line.substring(0, line.IndexOf(' ')), 16);
                }
                catch
                {
                    return -1;
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="window"></param>
        /// <returns></returns>
        public ViewNode LoadWindowData(Window window)
        {
            using (Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                s.Blocking = true;
                s.SendLine("DUMP " + window.Encode());

                using (var data = new MemoryStream())
                {
                    while (true)
                    {
                        var buffer = new byte[4096];
                        int len = s.Receive(buffer);
                        if (len <= 0)
                        {
                            break;
                        }
                        else
                        {
                            data.Write(buffer, 0, len);
                        }
                    }
                    s.Close(false);
                    data.Position = 0;
                    ViewNode currentNode = ParseViewHierarchy(data, window);
                    currentNode.ProtocolVersion = ProtocolVersion;
                    return currentNode;
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="window"></param>
        /// <returns></returns>
        private ViewNode ParseViewHierarchy(Stream input, Window window)
        {
            using (StreamReader sr = new StreamReader(input))
            {
                ViewNode currentNode = null;
                int currentDepth = -1;
                string line;

                while ((line = sr.ReadLine()) != null)
                {
                    if (string.Compare(line, "DONE.", true) == 0)
                    {
                        break;
                    }
                    int depth = 0;
                    while (line[depth] == ' ')
                    {
                        depth++;
                    }
                    while (depth <= currentDepth)
                    {
                        if (currentNode != null)
                        {
                            currentNode = currentNode.Parent;
                        }
                        currentDepth--;
                    }
                    currentNode = new ViewNode(window, currentNode, line.substring(depth));
                    currentDepth = depth;
                }
                if (currentNode == null)
                {
                    return null;
                }
                while (currentNode.Parent != null)
                {
                    currentNode = currentNode.Parent;
                }
                return currentNode;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public Window[] GetWindows()
        {
            using (Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                s.Blocking = true;
                s.SendLine("LIST");

                var buffer = new byte[4096];

                int len = s.Receive(buffer);

                s.Close(false);

                var data = Encoding.Default.GetString(buffer, 0, len).Trim();

                var items = new List<string>(data.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries));
                items.RemoveAll(i => string.Compare(i, "DONE.", true) == 0);

                var windows = new List<Window>();

                foreach (var item in items)
                {
                    var index = item.IndexOf(' ');
                    if (index != -1)
                    {
                        var windowId = item.substring(0, index);
                        int id = Convert.ToInt32(windowId, 16);
                        string name = item.substring(index + 1);
                        windows.Add(new Window(this) { Id = id, Name = name }); 
                    }
                }

                windows.Reverse();
                return windows.ToArray();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private int GetServerVersion()
        {
            using (Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                s.Blocking = true;

                s.SendLine("PROTOCOL");

                var buffer = new byte[4];

                int len = s.Receive(buffer);

                s.Close(false);

                var line = Encoding.Default.GetString(buffer, 0, len);

                return int.Parse(line);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private int GetServerProtocolVersion()
        {
            using (Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                s.Connect(IPAddress.Loopback, DEFAULT_SERVER_PORT);
                s.Blocking = true;

                s.SendLine("SERVER");

                var buffer = new byte[4];

                int len = s.Receive(buffer);

                s.Close(false);

                var line = Encoding.Default.GetString(buffer, 0, len).Trim();

                return int.Parse(line);
            }
        }
    }
}
