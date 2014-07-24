using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace TestAutomation.Client
{
    /// <summary>
    /// Represents a record in an AccessibilityEvent and contains information about state change 
    /// of its source View. When a view fires an accessibility event it requests from its parent 
    /// to dispatch the constructed event. The parent may optionally append a record for itself 
    /// for providing more context to AccessibilityServices. Hence, accessibility services can 
    /// facilitate additional accessibility records to enhance feedback.
    /// </summary>
    [Serializable]
    public class AccessibilityRecord
    {
        /// <summary>
        /// 
        /// </summary>
        public string ClassName { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public List<string> Text { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public string ContentDescription { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int ItemCount { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int CurrentItemIndex { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsEnabled { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsPassword { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsChecked { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsFullScreen { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public bool IsScrollable { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public string BeforeText { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int FromIndex { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int ToIndex { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int ScrollX { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int ScrollY { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int AddedCount { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int RemovedCount { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public Rect BoundsInParent { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public Rect BoundsInScreen { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public long ViewId { get; set; }
    }

    /// <summary>
    /// This class represents accessibility events that are sent by the system when something notable 
    /// happens in the user interface. For example, when a Button is clicked, a View is focused, etc.
    /// 
    /// An accessibility event is fired by an individual view which populates the event with data for 
    /// its state and requests from its parent to send the event to interested parties. The parent can 
    /// optionally add an AccessibilityRecord for itself before dispatching a similar request to its 
    /// parent. A parent can also choose not to respect the request for sending an event. 
    /// The accessibility event is sent by the topmost view in the view tree. Therefore, 
    /// an AccessibilityService can explore all records in an accessibility event to obtain more 
    /// information about the context in which the event was fired
    /// </summary>
    [Serializable]
    public class AccessibilityEvent : AccessibilityRecord
    {
        /// <summary>
        /// 
        /// </summary>
        public int RecordCount { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public EventType EventType { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public long EventTime { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public string PackageName { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int MovementGranularity { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public int Action { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        public List<AccessibilityRecord> Records { get; set; }

        /// <summary>
        /// Event time stamp
        /// </summary>
        public DateTime? TimeStamp { get; internal set; }

        /// <summary>
        /// 
        /// </summary>
        public int PageFlipCount { get; set; }

        /// <summary>
        /// 
        /// </summary>
        public long PageFlipCountTimestamp { get; set; }
    }

    /// <summary>
    /// Rect holds four integer coordinates for a rectangle. 
    /// </summary>
    [Serializable]
    public class Rect
    {
        /// <summary>
        /// The top edge being unioned with this rectangle
        /// </summary>
        public int top { get; set; }

        /// <summary>
        /// The left edge being unioned with this rectangle
        /// </summary>
        public int left { get; set; }

        /// <summary>
        /// The right edge being unioned with this rectangle
        /// </summary>
        public int right { get; set; }

        /// <summary>
        /// The bottom edge being unioned with this rectangle
        /// </summary>
        public int bottom { get; set; }

        /// <summary>
        /// Returns a string containing a concise, human-readable description of this object.
        /// </summary>
        /// <returns>A string containing a concise, human-readable description of this object.</returns>
        public override string ToString()
        {
            return string.Format("[{0}, {1} - {2}, {3}]", left, top, right, bottom);
        }
    }

    /// <summary>
    /// Type of an AccessibilityEvent
    /// </summary>
    public enum EventType : int
    {
        /// <summary>
        /// Represents the event of clicking on a View like Button, CompoundButton, etc.
        /// </summary>
        TYPE_VIEW_CLICKED = 0x00000001,
        
        /// <summary>
        /// Represents the event of long clicking on a View like Button, CompoundButton, etc.
        /// </summary>
        TYPE_VIEW_LONG_CLICKED = 0x00000002,
        
        /// <summary>
        /// Represents the event of selecting an item usually in the context of an AdapterView.
        /// </summary>
        TYPE_VIEW_SELECTED = 0x00000004,
        
        /// <summary>
        /// Represents the event of setting input focus of a View.
        /// </summary>
        TYPE_VIEW_FOCUSED = 0x00000008,
        
        /// <summary>
        /// Represents the event of changing the text of an EditText.
        /// </summary>
        TYPE_VIEW_TEXT_CHANGED = 0x00000010,
        
        /// <summary>
        /// Represents the event of opening a PopupWindow, Menu, Dialog, etc.
        /// </summary>
        TYPE_WINDOW_STATE_CHANGED = 0x00000020,
        
        /// <summary>
        /// Represents the event showing a Notification.
        /// </summary>
        TYPE_NOTIFICATION_STATE_CHANGED = 0x00000040,
        
        /// <summary>
        /// Represents the event of a hover enter over a View.
        /// </summary>
        TYPE_VIEW_HOVER_ENTER = 0x00000080,
        
        /// <summary>
        /// Represents the event of a hover exit over a View.
        /// </summary>
        TYPE_VIEW_HOVER_EXIT = 0x00000100,
        
        /// <summary>
        /// Represents the event of starting a touch exploration gesture.
        /// </summary>
        TYPE_TOUCH_EXPLORATION_GESTURE_START = 0x00000200,
        
        /// <summary>
        /// Represents the event of ending a touch exploration gesture.
        /// </summary>
        TYPE_TOUCH_EXPLORATION_GESTURE_END = 0x00000400,
        
        /// <summary>
        /// Represents the event of changing the content of a window and more specifically 
        /// the sub-tree rooted at the event's source.
        /// </summary>
        TYPE_WINDOW_CONTENT_CHANGED = 0x00000800,
        
        /// <summary>
        /// Represents the event of scrolling a view.
        /// </summary>
        TYPE_VIEW_SCROLLED = 0x00001000,
        
        /// <summary>
        /// Represents the event of changing the selection in an EditText.
        /// </summary>
        TYPE_VIEW_TEXT_SELECTION_CHANGED = 0x00002000,
        
        /// <summary>
        /// Represents the event of an application making an announcement.
        /// </summary>
        TYPE_ANNOUNCEMENT = 0x00004000,
        
        /// <summary>
        /// Represents the event of gaining accessibility focus.
        /// </summary>
        TYPE_VIEW_ACCESSIBILITY_FOCUSED = 0x00008000,
        
        /// <summary>
        /// Represents the event of clearing accessibility focus.
        /// </summary>
        TYPE_VIEW_ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,
        
        /// <summary>
        /// Represents the event of traversing the text of a view at a given movement granularity.
        /// </summary>
        TYPE_VIEW_TEXT_TRAVERSED_AT_MOVEMENT_GRANULARITY = 0x00020000,
        
        /// <summary>
        /// Represents the event of beginning gesture detection.
        /// </summary>
        TYPE_GESTURE_DETECTION_START = 0x00040000,
        
        /// <summary>
        /// Represents the event of ending gesture detection.
        /// </summary>
        TYPE_GESTURE_DETECTION_END = 0x00080000,
        
        /// <summary>
        /// Represents the event of the user starting to touch the screen.
        /// </summary>
        TYPE_TOUCH_INTERACTION_START = 0x00100000,
        
        /// <summary>
        /// Represents the event of the user ending to touch the screen.
        /// </summary>
        TYPE_TOUCH_INTERACTION_END = 0x00200000,
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("popup-label")]
    public class PopUpLabel
    {
        [XmlAttribute("label")]
        public string Key { get; set; }
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("keyboard")]
    public class Keyboard
    {
        /// <summary>
        /// 
        /// </summary>
        public const string DESCRIPTION = "keyboard_json";

        /// <summary>
        /// 
        /// </summary>
        public Keyboard()
        {
            Keys = new List<Key>();
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("visible")]
        public bool KeyboardOn { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public int X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public int Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public int W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public int H { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("shiftMode")]
        public int ShiftMode { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("locale")]
        public string Locale { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("keys")]
        public List<Key> Keys { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public string GetXml()
        {
            var serializer = new XmlSerializer(GetType());
            using (var stream = new StringWriter())
            {
                using (var writer = new XmlTextWriter(stream))
                {
                    serializer.Serialize(writer, this);
                    return stream.ToString();
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return GetXml();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("key")]
    public class Key
    {
        /// <summary>
        /// 
        /// </summary>
        public Key()
        {
            PopUpKeys = new List<PopUpLabel>();
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("label")]
        public string Label { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public int X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public int Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public int W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public int H { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("popup-keys")]
        public List<PopUpLabel> PopUpKeys { get; set; }
    }




    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("albumset")]
    public class Albumset
    {
        /// <summary>
        /// 
        /// </summary>
        public const string DESCRIPTION = "json";

        /// <summary>
        /// 
        /// </summary>
        public Albumset()
        {
            Albums = new List<AlbumItem>();
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public string X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public string Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public string W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public string H { get; set; }

        /// <summary>
        /// /// </summary>
        [XmlArray(ElementName = "albums")]
        [XmlArrayItem(ElementName = "albums")]
        public List<AlbumItem> Albums { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public string GetXml()
        {
            var type = GetType();
            var serializer = new XmlSerializer(type);
            using (var stream = new StringWriter())
            {
                using (var writer = new XmlTextWriter(stream))
                {
                    serializer.Serialize(writer, this);
                    return stream.ToString();
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return GetXml();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("album-item")]
    public class AlbumItem
    {
        /// <summary>
        /// 
        /// </summary>
        public AlbumItem()
        {

        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("name")]
        public string Album { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("index")]
        public string Index { get; set; }


        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public string X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public string Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public string W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public string H { get; set; }

    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("album")]
    public class Album
    {
        /// <summary>
        /// 
        /// </summary>
        public const string DESCRIPTION = "json";

        /// <summary>
        /// 
        /// </summary>
        public Album()
        {
            Thumbnails = new List<ThumbnailItem>();
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public string X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public string Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public string W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public string H { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlArray(ElementName = "thumbnails")]
        [XmlArrayItem(ElementName = "thumbnails")]
        public List<ThumbnailItem> Thumbnails { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public string GetXml()
        {
            var serializer = new XmlSerializer(GetType());
            using (var stream = new StringWriter())
            {
                using (var writer = new XmlTextWriter(stream))
                {
                    serializer.Serialize(writer, this);
                    return stream.ToString();
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return GetXml();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    [XmlType("thumbnail_item")]
    public class ThumbnailItem
    {
        /// <summary>
        /// 
        /// </summary>
        public ThumbnailItem()
        {
        }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("file")]
        public string Thumbnail { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("index")]
        public string Index { get; set; }


        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("x")]
        public string X { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("y")]
        public string Y { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("width")]
        public string W { get; set; }

        /// <summary>
        /// 
        /// </summary>
        [XmlAttribute("height")]
        public string H { get; set; }

    }
}
