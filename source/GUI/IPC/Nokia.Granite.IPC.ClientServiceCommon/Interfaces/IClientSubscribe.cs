using System.ServiceModel;

namespace TestAutomation.Gui.Marble.IPC.Interfaces
{
    [ServiceContract]
    public interface IClientKeepalive
    {
        [OperationContract]
        bool ClientKeepalive();
    }

    [ServiceContract]
    public interface IClientSubscribe
    {
        [OperationContract(IsOneWay = true)]
        void ClientSubscribe();

        [OperationContract(IsOneWay = true)]
        void ClientUnSubscribe();
    }
}
