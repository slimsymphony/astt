// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;

namespace Nokia.Iowarrior.Cards

{
    public sealed class IowCardMatrix_5x6 : MatrixBase
    {
        public IowCardMatrix_5x6() : base() { }

        public IowCardMatrix_5x6(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation, 6, 5) { }      
    }
}
