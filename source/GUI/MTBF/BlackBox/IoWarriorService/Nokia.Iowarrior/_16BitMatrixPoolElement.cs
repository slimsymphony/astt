using System;
using System.Collections.Generic;
using System.Text;

namespace Nokia.Iowarrior
{
    class _16BitMatrixPoolElement
    {
        private String key;
        private Boolean active = false;
        private _16BitMatrix matrix;

        public _16BitMatrixPoolElement() { }

        public _16BitMatrixPoolElement(_16BitMatrix matrix) 
        {
            this.matrix = matrix;
        }

        #region properties

        public String Key
        {
            get { return key; }
            set { key = value; }
        }

        public Boolean IsActive
        {
            get { return active; }
            set { active = value; }
        }

        public _16BitMatrix Matrix
        {
            get { return matrix; }
            set { matrix = value; }
        }

        #endregion
    }
}
