﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Managed.Adb.IO
{
    /// <summary>
    /// 
    /// </summary>
    public class ByteOrder
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        private ByteOrder(string name)
        {
            Name = name;
        }

        public readonly static ByteOrder BIG_ENDIAN = new ByteOrder("BIG_ENDIAN");
        public readonly static ByteOrder LITTLE_ENDIAN = new ByteOrder("LITTLE_ENDIAN");

        public string Name { get; private set; }
        public override string ToString()
        {
            return Name;
        }
    }

}
