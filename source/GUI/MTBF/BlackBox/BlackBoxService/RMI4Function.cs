using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Nokia.Tea.Rcms.TypeInterfaces.TouchController
{
    /// <summary>
    /// RMI 4 Funcition
    /// </summary>
    class RMI4Function
    {
        private Byte function;
        private Byte queryRegister;
        private Byte commandRegister;
        private Byte controlRegister;
        private Byte dataRegister;
        private Byte numberOfInterruptSources;

        /// <summary>
        /// Initializes a new instance of the <see cref="RMI4Function"/> class.
        /// </summary>
        /// <param name="function">The function.</param>
        public RMI4Function(Byte function)
        {
            this.function = function;
        }

        /// <summary>
        /// Gets the function.
        /// </summary>
        public Byte Function
        {
            get { return function; }
        }

        /// <summary>
        /// Gets or sets the query register.
        /// </summary>
        /// <value>
        /// The query register.
        /// </value>
        public Byte QueryRegister
        {
            set { this.queryRegister = value; }
            get { return queryRegister; }
        }

        /// <summary>
        /// Gets or sets the command register.
        /// </summary>
        /// <value>
        /// The command register.
        /// </value>
        public Byte CommandRegister
        {
            set { this.commandRegister = value; }
            get { return commandRegister; }
        }

        /// <summary>
        /// Gets or sets the control register.
        /// </summary>
        /// <value>
        /// The control register.
        /// </value>
        public Byte ControlRegister
        {
            set { this.controlRegister = value; }
            get { return controlRegister; }
        }

        /// <summary>
        /// Gets or sets the data register.
        /// </summary>
        /// <value>
        /// The data register.
        /// </value>
        public Byte DataRegister
        {
            set { this.dataRegister = value; }
            get { return dataRegister; }
        }

        /// <summary>
        /// Gets or sets the number of interrupt sources.
        /// </summary>
        /// <value>
        /// The number of interrupt sources.
        /// </value>
        public Byte NumberOfInterruptSources
        {
            set { this.numberOfInterruptSources = value; }
            get { return numberOfInterruptSources; }
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("Function:\t\t" + function);
            sb.AppendLine("QueryRegister:\t" + queryRegister);
            sb.AppendLine("CommandRegister:\t" + commandRegister);
            sb.AppendLine("ControlRegister:\t" + controlRegister);
            sb.AppendLine("DataRegister:\t" + dataRegister);
            sb.AppendLine("NumberOfInterruptSources:\t" + numberOfInterruptSources);

            return sb.ToString();
        }
    }
}
