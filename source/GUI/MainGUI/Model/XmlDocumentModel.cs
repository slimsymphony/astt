using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml;

namespace Marble.Model
{
    class XmlDocumentModel : INotifyPropertyChanged
    {
        //XmlDocument
        private XmlDocument _testsetDocument;
        public XmlDocument TestsetDocument
        {
            get { return _testsetDocument; }
            set
            {
                if (_testsetDocument != value)
                {
                    _testsetDocument = value;
                    OnPropertyChanged("TestsetDocument");
                }
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
