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
    public sealed class IowCardUnknown : IowCard
    {
        /// <summary>
        /// Empty constructor just calls constructor of IowCard class.
        /// </summary>
        public IowCardUnknown()
            : base()
        {
        }

        public IowCardUnknown(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
        }

        public override void Shutdown()
        {
            // Do all required to get card in safe state.
        }

        public override void Reset()
        {
            // Do all required to reset the card.
        }

        public override ICollection<String> KnownCommands
        {
            get { return new String[0]; }
        }

        /// <summary>
        /// Check, whether a command can be executed.
        /// </summary>
        /// <param name="command">Command string.</param>
        /// <returns>Always false: an unknown card cannot execute any command.</returns>
        public override IowCardCommand CheckCommand(String command)
        {
            IowCardCommand result = new IowCardCommand(command);
            return result;
        }

        /// <summary>
        /// Execute a given command.
        /// </summary>
        /// <param name="command">Command string.</param>
        /// <returns>Always false: an unknown card cannot execute any command.</returns>
        public override IowCardCommand ExecuteCommand(String command)
        {
            IowCardCommand result = new IowCardCommand(command);
            return result;
        }
    }
}
