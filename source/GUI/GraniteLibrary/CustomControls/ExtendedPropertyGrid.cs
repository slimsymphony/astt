using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Reflection;
using System.Windows.Forms;

namespace MarbleLibrary.CustomControls
{
    /// <summary>
    /// Extends the Windows Form property grid so that it has a similar style to that used in Marble.
    /// </summary>
    public class ExtendedPropertyGrid : PropertyGrid
    {
        /// <summary>
        /// Class containing the names of the members to invoke on the base class.
        /// </summary>
        private class MemberNames
        {
            internal const string DOC_COMMENT = "doccomment";
            internal const string DOC_COMMENT_TITLE = "m_labelTitle";
            internal const string DOC_COMMENT_DESCRIPTION = "m_labelDesc";
            internal const string TOOL_STRIP = "toolStrip";
            internal const string SORTING_CATEGORIZED = "categorized";
            internal const string SORTING_ALPHABETICAL = "alphabetical";
        }

        private ToolStrip _toolStrip;
        private ToolTip _toolTip;
        private Control _docComment;
        private Label _docCommentTitle;
        private Label _docCommentDescription;
        private Container _components;
        private Color _docCommentBackgroundStartColor;
        private Color _docCommentBackgroundEndColor;
        private Color _toolStripBackgroundStartColor;
        private Color _toolStripBackGroundEndColor;
        private Font _docCommentDescriptionFont;
        private Font _docCommentTitleFont;

        public ExtendedPropertyGrid()
        {
            InitializeComponent();
            ModifyComponents();
        }

        [DisplayName("DocCommentBackgroundStartColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment background gradient start color")]
        public Color DocCommentBackgroundStartColor
        {
            get
            {
                return _docCommentBackgroundStartColor;
            }
            set
            {
                if (value != null)
                {
                    _docCommentBackgroundStartColor = value;
                    _docComment.BackgroundImage = CreateGradientImage(value, _docCommentBackgroundEndColor);
                }
            }
        }
        
        [DisplayName("DocCommentBackgroundEndColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment background gradient end color")]
        public Color DocCommentBackgroundEndColor
        {
            get
            {
                return _docCommentBackgroundEndColor;
            }
            set
            {
                if (value != null)
                {
                    _docCommentBackgroundEndColor = value;
                    _docComment.BackgroundImage = CreateGradientImage(_docCommentBackgroundStartColor, value);
                }
            }
        }

        [DisplayName("DocCommentDescriptionFontColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment description field font color")]
        public Color DocCommentDescriptionFontColor
        {
            get
            {
                return _docCommentDescription.ForeColor;
            }
            set
            {
                _docCommentDescription.ForeColor = value;
            }
        }

        [DisplayName("DocCommentDescriptionFont"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment description field font")]
        public Font DocCommentDescriptionFont
        {
            get
            {
                return _docCommentDescriptionFont;
            }
            set
            {
                if (value != null)
                {
                    _docCommentDescriptionFont = value;
                    UpdateFonts();
                }
            }
        }

        [DisplayName("DocCommentTitleFontColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment title field font color")]
        public Color DocCommentTitleFontColor
        {
            get
            {
                return _docCommentTitle.ForeColor;
            }
            set
            {
                _docCommentTitle.ForeColor = value;
            }
        }

        [DisplayName("DocCommentTitleFont"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("DocComment title field font")]
        public Font DocCommentTitleFont
        {
            get
            {
                return _docCommentTitleFont;
            }
            set
            {
                if (value != null)
                {
                    _docCommentTitleFont = value;
                    UpdateFonts();
                }
            }
        }

        [DisplayName("GridFont"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("Grid font")]
        public Font GridFont
        {
            get
            {
                return base.Font;
            }
            set
            {
                base.Font = value;
            }
        }

        [DisplayName("GridFontColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("Grid font color")]
        public Color GridFontColor
        {
            get
            {
                return base.ViewForeColor;
            }
            set
            {
                base.ViewForeColor = value;
            }
        }

        [DisplayName("GridCellColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("Grid cell background color")]
        public Color GridCellColor
        {
            get
            {
                return base.ViewBackColor;
            }
            set
            {
                base.ViewBackColor = value;
            }
        }

        [DisplayName("GridCategoryColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("Grid category background color")]
        public Color GridCategoryColor
        {
            get
            {
                return base.LineColor;
            }
            set
            {
                base.LineColor = value;
            }
        }

        [DisplayName("ToolStripBackgroundStartColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("ToolStrip background gradient start color")]
        public Color ToolStripBackgroundStartColor
        {
            get
            {
                return _toolStripBackgroundStartColor;
            }
            set
            {
                if (value != null)
                {
                    _toolStripBackgroundStartColor = base.BackColor = value;
                    _toolStrip.BackgroundImage = CreateGradientImage(value, _toolStripBackGroundEndColor);
                }
            }
        }
        
        [DisplayName("ToolStripBackgroundEndColor"), Browsable(true), Category("Appearance"), DesignerSerializationVisibility(DesignerSerializationVisibility.Content), Description("ToolStrip background gradient end color")]
        public Color ToolStripBackGroundEndColor
        {
            get
            {
                return _toolStripBackGroundEndColor;
            }
            set
            {
                if (value != null)
                {
                    _toolStripBackGroundEndColor = value;
                    _toolStrip.BackgroundImage = CreateGradientImage(_toolStripBackgroundStartColor, value);
                }
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new bool LargeButtons
        {
            get
            {
                return true;
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Font Font
        {
            get
            {
                return base.Font;
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Color ViewBackColor
        {
            get
            {
                return base.ViewBackColor;
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Color ViewForeColor
        {
            get
            {
                return base.ViewForeColor;
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Color LineColor
        {
            get
            {
                return base.LineColor;
            }
        }

        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Color BackColor
        {
            get
            {
                return base.BackColor;
            }
        }

        private Image GetEmbeddedImage(string name)
        {
            var resourceName = "MarbleLibrary.Images." + name;

            string[] names = GetType().Assembly.GetManifestResourceNames();

            using (var stream = GetType().Assembly.GetManifestResourceStream(resourceName))
            {
                return Image.FromStream(stream);
            }
        }

        private Image CreateGradientImage(Color startColor, Color endColor)
        {
            Bitmap bitmap = new Bitmap(Width, Height / 2);
            Graphics g = Graphics.FromImage(bitmap);
            Point p1 = new Point(0, 0);
            Point p2 = new Point(0, Height / 2);
            LinearGradientBrush backBrush = new LinearGradientBrush(p1, p2, startColor, endColor);
            Rectangle rect = new Rectangle(p1, new Size(Width, Height / 2));
            g.FillRectangle(backBrush, rect);
            g.Dispose();
            backBrush.Dispose();
            return bitmap;
        }

        private void UpdateFonts()
        {
            _docCommentTitle.Font = _docCommentTitleFont;
            _docCommentDescription.Location = new Point(_docCommentTitle.Location.X + 2, 5 + _docCommentTitle.Font.Height);
            _docCommentDescription.Font = _docCommentDescriptionFont;
            Refresh();
        }
        protected override void OnVisibleChanged(EventArgs e)
        {
            base.OnVisibleChanged(e);
            UpdateFonts();
        }

        [DebuggerNonUserCode]
        protected override void Dispose(bool disposing)
        {
            if (disposing && _components != null)
            {
                _components.Dispose();
            }
            base.Dispose(disposing);
        }
        
        [DebuggerStepThrough]
        private void InitializeComponent()
        {
            _components = new Container();
        }

        private void ModifyComponents()
        {
            base.AutoScaleMode = AutoScaleMode.Font;
            base.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            base.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            base.LargeButtons = true;

            GridCellColor = Color.White;
            GridCategoryColor = Color.FromArgb(240, 248, 255);
            GridFontColor = Color.FromArgb(60, 60, 60);
            GridFont = new Font("Segoe UI", 9.0f);
            Dock = DockStyle.Fill;

            _toolStrip = (ToolStrip)base.GetType().BaseType.InvokeMember(MemberNames.TOOL_STRIP, 
                BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.GetField, null, this, null);

            _toolStripBackgroundStartColor = base.BackColor = Color.FromArgb(81, 71, 100);
            _toolStripBackGroundEndColor = Color.FromArgb(16, 0, 45);
            _toolStrip.BackgroundImage = CreateGradientImage(_toolStripBackgroundStartColor, _toolStripBackGroundEndColor);
            _toolStrip.BackgroundImageLayout = ImageLayout.Stretch;

            var remove = new List<ToolStripItem>();

            _toolStrip.RenderMode = ToolStripRenderMode.Professional;
            _toolStrip.Renderer = new CustomRenderer();

            _toolTip = new CustomToolTip();
            _toolTip.InitialDelay = 1000;
            _toolTip.ReshowDelay = 1000;
            _toolTip.UseFading = true;
            _toolTip.UseAnimation = true;
            _toolTip.Active = false;
            _toolTip.SetToolTip(_toolStrip, " ");

            foreach (ToolStripItem item in _toolStrip.Items)
            {
                var text = item.Text.ToLower();

                if (text == MemberNames.SORTING_CATEGORIZED)
                {
                    item.Image = GetEmbeddedImage("sort.category.128x128.png");
                }
                else if (text == MemberNames.SORTING_ALPHABETICAL)
                {
                    item.Image = GetEmbeddedImage("sort.ascend.32x32.png");
                }
                else
                {
                    remove.Add(item);
                    continue;
                }

                if (item is ToolStripButton)
                {
                    var button = item as ToolStripButton;
                    item.AutoToolTip = false;
                    button.MouseEnter += new EventHandler(ToolStripButtonMouseEnter);
                    button.MouseLeave += new EventHandler(ToolStripButtonMouseLeave);
                }
            }
            remove.ForEach(i => _toolStrip.Items.Remove(i));

            _docComment = (Control)base.GetType().BaseType.InvokeMember(MemberNames.DOC_COMMENT, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.GetField, null, this, null);
            if (_docComment != null)
            {
                _docCommentTitle = (Label)_docComment.GetType().InvokeMember(MemberNames.DOC_COMMENT_TITLE, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.GetField, null, _docComment, null);
                _docCommentTitle.Font = _docCommentTitleFont = new Font("Segoe UI", 16, FontStyle.Bold);

                _docCommentDescription = (Label)_docComment.GetType().InvokeMember(MemberNames.DOC_COMMENT_DESCRIPTION, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.GetField, null, _docComment, null);
                _docCommentDescription.Location = new Point(3, (5 + _docCommentDescription.Font.Height));

                _docComment.BackgroundImageLayout = ImageLayout.Stretch;
                _docCommentBackgroundStartColor = Color.FromArgb(81, 71, 100);
                _docCommentBackgroundEndColor = Color.FromArgb(16, 0, 45);
                _docComment.BackgroundImage = CreateGradientImage(_docCommentBackgroundStartColor, _docCommentBackgroundEndColor);

                _docCommentDescription.BackColor = Color.Transparent;
                _docCommentDescription.ForeColor = Color.White;
                _docCommentDescription.AutoEllipsis = true;
                _docCommentDescription.Font = _docCommentDescriptionFont = new Font("Segoe UI", 10);
                _docCommentTitle.AutoSize = true;
                _docCommentTitle.BackColor = Color.Transparent;
                _docCommentTitle.UseMnemonic = false;
                _docCommentDescription.UseMnemonic = false;
                _docCommentTitle.ForeColor = Color.White;
            }

            Refresh();
        }

        private void ToolStripButtonMouseLeave(object sender, EventArgs e)
        {
            _toolTip.Active = false;
        }

        private void ToolStripButtonMouseEnter(object sender, EventArgs e)
        {
            var button = sender as ToolStripButton;
            _toolTip.ToolTipTitle = button.Text;
            _toolTip.Active = true;
        }
    }

    internal class CustomRenderer : ToolStripProfessionalRenderer
    {
        protected override void OnRenderButtonBackground(ToolStripItemRenderEventArgs e)
        {
            if (e.Item.Selected)
            {
                e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

                Color light = Color.FromArgb(64, 156, 208);
                Color dark = Color.FromArgb(10, 55, 130);

                Rectangle top = new Rectangle(0, 0, e.Item.Size.Width + 1, e.Item.Size.Height / 2 + 1);
                Rectangle bottom = new Rectangle(0, e.Item.Size.Width / 2 - 1, e.Item.Size.Width, e.Item.Size.Height / 2 + 1);
                LinearGradientBrush backBrush = new LinearGradientBrush(top, light , dark, 90);
                e.Graphics.FillRectangle(backBrush, top);
                backBrush.Dispose();
                backBrush = new LinearGradientBrush(bottom, dark, light, 90);
                e.Graphics.FillRectangle(backBrush, bottom);
                backBrush.Dispose();
            }
        }

        protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e)
        { }
    }

    internal class CustomToolTip : ToolTip
    {
        public CustomToolTip()
        {
            Font = new Font("Segoe UI", 9f, FontStyle.Bold);
            this.OwnerDraw = true;
            this.Popup += new PopupEventHandler(this.OnPopup);
            this.Draw += new DrawToolTipEventHandler(this.OnDraw);
        }

        public Font Font
        {
            get;
            set;
        }

        private void OnPopup(object sender, PopupEventArgs e)
        {
            var size = TextRenderer.MeasureText(this.ToolTipTitle, Font);
            e.ToolTipSize = new Size(size.Width + 10, size.Height * 2);
        }

        private void OnDraw(object sender, DrawToolTipEventArgs e)
        {
            Graphics g = e.Graphics;

            g.SmoothingMode = SmoothingMode.AntiAlias;

            LinearGradientBrush b = new LinearGradientBrush(e.Bounds,
                Color.FromArgb(48, 48, 48), Color.FromArgb(100, 100, 100), 90f);

            g.FillRectangle(b, e.Bounds);

            var stringSize = g.MeasureString(ToolTipTitle, Font);

            g.DrawString(this.ToolTipTitle, Font, Brushes.White,
                new PointF(e.Bounds.Width / 2 - stringSize.Width / 2, e.Bounds.Height / 2 - stringSize.Height / 2));

            b.Dispose();
        }
    }
}
