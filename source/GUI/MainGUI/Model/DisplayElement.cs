using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Xml.Linq;

namespace Marble.Model
{
    /// <summary>
    /// Specifies the type of the display element.
    /// </summary>
    public enum DisplayElementType {
        /// <summary>
        /// No type defined.
        /// </summary>
        None = 0,

        /// <summary>
        /// Visual graphic element, usually a .png file.
        /// </summary>
        Image = 1,

        /// <summary>
        /// Any kind of visible text block.
        /// </summary>
        Text = 2,
        
        /// <summary>
        /// Node type.
        /// </summary>
        Node = 3
    }

    /// <summary>
    /// Represents a visible display element captured from the phone screen via Marble server.
    /// Primary information is content (text or image name) and area of the element.
    /// </summary>
    public class DisplayElement
    {
        /// <summary>
        /// Type of the element (text or image).
        /// </summary>
        public DisplayElementType Type { get; set; }

        /// <summary>
        /// Area of the element.
        /// </summary>
        public System.Drawing.Rectangle Rectangle { get; set; }

        #region [ Element Details Properties ]

        /// <summary>
        /// Gets or sets the resource ID of the element.
        /// </summary>
        public string ResourceId { get; set; }

        /// <summary>
        /// Gets or sets the description of the element.
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the index tree of the element.
        /// </summary>
        public string IndexTree { get; set; }

        /// <summary>
        /// Gets or sets the class of the element.
        /// </summary>
        public string Class { get; set; }

        /////// <summary>
        /////// Gets the class/index of the element.
        /////// </summary>
        ////public string ClassIndex { get { return this.Class + ", " + this.Index; } }

        /// <summary>
        /// Gets or sets the text of the element.
        /// </summary>
        public string Text { get; set; }

        /// <summary>
        /// Gets or sets the bound coordinates of the element.
        /// </summary>
        public string Package { get; set; }

        /// <summary>
        /// Gets or sets the bound coordinates of the element.
        /// </summary>
        public string Bounds { get; set; }

        /// <summary>
        /// Description of an element related to this element (e.g. label for togglebutton). This is dynamic property and it is only available when it's found.
        /// </summary>
        public string RelatedDescription { get; set; }

        /// <summary>
        /// Text of an element related to this element (e.g. label for togglebutton). This is dynamic property and it is only available when it's found.
        /// </summary>
        public string RelatedText { get; set; }

        #endregion [ Element Details Properties ]

        #region [ Boolean Node Properties ]

        /// <summary>
        /// Gets or sets value whether the node is checkable. Null is returned when this property is not available.
        /// </summary>
        public bool? IsCheckable { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is checked. Null is returned when this property is not available.
        /// </summary>
        public bool? IsChecked { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is clickable. Null is returned when this property is not available.
        /// </summary>
        public bool? IsClickable { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is enabled. Null is returned when this property is not available.
        /// </summary>
        public bool? IsEnabled { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is focusable. Null is returned when this property is not available.
        /// </summary>
        public bool? IsFocusable { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is focused. Null is returned when this property is not available.
        /// </summary>
        public bool? IsFocused { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is scrollable. Null is returned when this property is not available.
        /// </summary>
        public bool? IsScrollable { get; set; }

        /// <summary>
        /// Gets or sets value whether long click can be performed to the node. Null is returned when this property is not available.
        /// </summary>
        public bool? IsLongClickable { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is password. Null is returned when this property is not available.
        /// </summary>
        public bool? IsPassword { get; set; }

        /// <summary>
        /// Gets or sets value whether the node is selected. Null is returned when this property is not available.
        /// </summary>
        public bool? IsSelected { get; set; }
        
        #endregion [ Boolean Node Properties ]

        /// <summary>
        /// Center point of the element.
        /// </summary>
        public System.Windows.Point Center
        {
            get
            {
                return new System.Windows.Point(
                    Math.Round(this.Rectangle.X + this.Rectangle.Width / 2.0),
                    Math.Round(this.Rectangle.Y + this.Rectangle.Height / 2.0));
            }
        }

        /// <summary>
        /// Content of the element (text or image name).
        /// </summary>
        public string Content { get; set; }

        private List<string> translations;

        /// <summary>
        /// List of possible translations (path identifiers) for the content.
        /// </summary>
        public List<string> Translations
        {
            get { return this.translations; }
            set
            {
                this.SelectedTranslation = "";
                this.translations = value;
            }
        }

        /// <summary>
        /// Indicates whether the content has multiple possible translations.
        /// </summary>
        public bool HasMultipleTranslations { get { return Translations.Count > 1; } }

        // TODO: this should be cleared on Translations.Clear()
        private string selectedTranslation;

        /// <summary>
        /// Selected translation or first translation from the translations list or content.
        /// </summary>
        public string SelectedTranslation
        {
            get
            {
                // Selected translation
                if (!string.IsNullOrEmpty(this.selectedTranslation))
                    return selectedTranslation;

                // First (suggested) translation
                if (this.Translations.Count > 0)
                    return this.Translations.First();

                return this.Content;
            }
            set
            {
                this.selectedTranslation = value;
            }
        }

        /// <summary>
        /// Empty constructor.
        /// </summary>
        public DisplayElement()
        {
            this.Type = DisplayElementType.None;
            this.Rectangle = new System.Drawing.Rectangle();
            this.Content = string.Empty;
            this.Translations = new List<string>();
        }

        /// <summary>
        /// Constructor from an XML element.
        /// </summary>
        /// <param name="xElement">XML element from which to parse the information</param>
        public DisplayElement(XElement xElement)
        {
            this.Type = DisplayElementType.None;
            this.Rectangle = new System.Drawing.Rectangle();
            this.Content = string.Empty;
            this.Translations = new List<string>();

            // Not image or text (other types are not supported currently)
            if (xElement.Name != "animation" && xElement.Name != "image" && xElement.Name != "text" && xElement.Name != "node") return;

            if (xElement.Name == "animation" || xElement.Name == "image")
            {   // Image element
                this.Type = DisplayElementType.Image;

                // Get image name
                XAttribute name;
                if ((name = xElement.Attribute("name")) != null)
                    this.Content = name.Value;

                // Get translations
                foreach (var path in xElement.Descendants().Where(elem => elem.Name == "translation"))
                    this.Translations.Add(path.Value);
            }
            else if (xElement.Name == "text")
            {   // Text element
                this.Type = DisplayElementType.Text;
                // Get text content
                this.Content = HttpUtility.HtmlDecode(xElement.Value);
            }
            else if (xElement.Name == "node")
            {   // Node element
                this.Type = DisplayElementType.Node;

                ////int indexValue;
                ////if (xElement.Attribute("index") != null && int.TryParse(xElement.Attribute("index").Value, out indexValue)) 
                ////    this.Index = indexValue;
                ////else 
                ////    this.Index = null;

                this.IndexTree = xElement.Attribute("index") != null ? xElement.Attribute("index").Value : string.Empty;
                this.Text = xElement.Attribute("text") != null ? xElement.Attribute("text").Value : string.Empty;
                this.ResourceId = xElement.Attribute("resource-id") != null ? xElement.Attribute("resource-id").Value : string.Empty;
                this.Class = xElement.Attribute("class") != null ? xElement.Attribute("class").Value : string.Empty;
                this.Package = xElement.Attribute("package") != null ? xElement.Attribute("package").Value : string.Empty;
                this.Description = xElement.Attribute("content-desc") != null ? xElement.Attribute("content-desc").Value : string.Empty;
                this.Bounds = xElement.Attribute("bounds") != null ? xElement.Attribute("bounds").Value : string.Empty;

                // Dynamic properties which are only set when found.
                this.RelatedDescription = xElement.Attribute("related_description") != null ? xElement.Attribute("related_description").Value : string.Empty;
                this.RelatedText = xElement.Attribute("related_text") != null ? xElement.Attribute("related_text").Value : string.Empty;

                this.IsCheckable = this.getNullableBoolValueFromXElement(xElement, "checkable");
                this.IsChecked = this.getNullableBoolValueFromXElement(xElement, "checked");
                this.IsClickable = this.getNullableBoolValueFromXElement(xElement, "clickable");
                this.IsEnabled = this.getNullableBoolValueFromXElement(xElement, "enabled");
                this.IsFocusable = this.getNullableBoolValueFromXElement(xElement, "focusable");
                this.IsFocused = this.getNullableBoolValueFromXElement(xElement, "focused");
                this.IsScrollable = this.getNullableBoolValueFromXElement(xElement, "scrollable");
                this.IsLongClickable = this.getNullableBoolValueFromXElement(xElement, "long-clickable");
                this.IsPassword = this.getNullableBoolValueFromXElement(xElement, "password");
                this.IsSelected = this.getNullableBoolValueFromXElement(xElement, "selected");
            }

            // Get area rectangle
            XAttribute x, y, width, height;
            int xx, yy, width2, height2;
            // Try to parse values from the corresponding attribute fields
            if ((x = xElement.Attribute("x")) != null && int.TryParse(x.Value, out xx) &&
                (y = xElement.Attribute("y")) != null && int.TryParse(y.Value, out yy) &&
                (width = xElement.Attribute("width")) != null && int.TryParse(width.Value, out width2) &&
                (height = xElement.Attribute("height")) != null && int.TryParse(height.Value, out height2))
            {
                this.Rectangle = new System.Drawing.Rectangle(xx, yy, width2, height2);
            }
        }

        /// <summary>
        /// Creates an xml element from this display element.
        /// Structure: Element name is the type of the element (image or text).
        /// Attributes: name, x, y, width, height
        /// </summary>
        /// <returns>Xml representation of this display element.</returns>
        public XElement ToXmlElement()
        {
            XElement element = new XElement(this.Type == DisplayElementType.Image ? "image" : "text");

            switch (this.Type)
            {
                // Image name is stored to name attribute
                case DisplayElementType.Image:
                    element.SetAttributeValue("name", this.Content);
                    break;
                case DisplayElementType.Node:
                    ////if (this.Index != null)
                    ////    element.SetAttributeValue("index", this.Index);

                    element.SetAttributeValue("index", this.IndexTree);
                    element.SetAttributeValue("text", this.Text);
                    element.SetAttributeValue("resource-id", this.ResourceId);
                    element.SetAttributeValue("class", this.Class);
                    element.SetAttributeValue("package", this.Package);
                    element.SetAttributeValue("content-desc", this.Description);
                    element.SetAttributeValue("bounds", this.Bounds);

                    // Dynamic properties which are only set when found.
                    if (!string.IsNullOrEmpty(this.RelatedDescription))
                        element.SetAttributeValue("related_description", this.RelatedDescription);
                    if (!string.IsNullOrEmpty(this.RelatedText))
                        element.SetAttributeValue("related_text", this.RelatedText);

                    this.setNullableBoolValueToXElement(element, "checkable", this.IsCheckable);
                    this.setNullableBoolValueToXElement(element, "checked", this.IsChecked);
                    this.setNullableBoolValueToXElement(element, "clickable", this.IsClickable);
                    this.setNullableBoolValueToXElement(element, "enabled", this.IsEnabled);
                    this.setNullableBoolValueToXElement(element, "focusable", this.IsFocusable);
                    this.setNullableBoolValueToXElement(element, "focused", this.IsFocused);
                    this.setNullableBoolValueToXElement(element, "scrollable", this.IsScrollable);
                    this.setNullableBoolValueToXElement(element, "long-clickable", this.IsLongClickable);
                    this.setNullableBoolValueToXElement(element, "password", this.IsPassword);
                    this.setNullableBoolValueToXElement(element, "selected", this.IsSelected);
                    break;
                case DisplayElementType.None:
                case DisplayElementType.Text:
                default:
                    element.Value = this.Content;
                    break;
            }

            element.SetAttributeValue("x", this.Rectangle.X);
            element.SetAttributeValue("y", this.Rectangle.Y);
            element.SetAttributeValue("width", this.Rectangle.Width);
            element.SetAttributeValue("height", this.Rectangle.Height);

            // Create translations as sub elements
            if (this.Type == DisplayElementType.Image)
                foreach (var path in this.Translations)
                    element.Add(new XElement("translation", path));
            return element;
        }

        private bool? getNullableBoolValueFromXElement(XElement xElement, string attributeName)
        {
            if (xElement == null) return null;

            bool outputBoolResult;

            if (xElement.Attribute(attributeName) != null
                && bool.TryParse(xElement.Attribute(attributeName).Value, out outputBoolResult))
            {
                return outputBoolResult;
            }

            return null;
        }

        private void setNullableBoolValueToXElement(XElement xElement, string attributeName, bool? value)
        {
            if (xElement == null) return;

            if (value != null)
                xElement.SetAttributeValue(attributeName, value);
            else
                xElement.SetAttributeValue(attributeName, string.Empty);
        }
    }
}
