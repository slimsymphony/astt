using MediatorLib;

namespace Marble.Model
{
    /// <summary>
    /// Base class for Mediator implementation.
    /// Mediator, or Messenger, is a part of MVVM Foundation.
    /// http://mvvmfoundation.codeplex.com/
    /// </summary>
    public class MediatorModel
    {
        static readonly Mediator mediator = new Mediator();

        public Mediator Mediator
        {
            get { return mediator; }
        }
    }
}
