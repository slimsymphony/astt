using System.Runtime.Serialization;
using System.ServiceModel;
using System.Xml.Serialization;
using TestAutomation.Gui.Marble.IPC.ServiceClientCommon;

namespace TestAutomation.Gui.Marble.IPC.Interfaces
{
    [ServiceContract (SessionMode = SessionMode.Required)]
    public interface IBltUeService
    {
        [OperationContract]
        void InitGpib();

        [OperationContract]
        void InitPsu();

        [OperationContract]
        void Disconnect();
    }

    /// <summary>
    /// Parameterclass that stores the settings needed for BlackBox Client to communicate with BlackBox Service.
    /// Inherits BaseSettings so that logging services are automatically taken into use (if configured).
    /// </summary>
    [DataContract]
    public class BltUeClientSettings : ClientSettings
    {
        public BltUeClientSettings()
        {
            base.ServiceUri.HostAddress = "localhost";
            base.ServiceUri.ServicePort = 8052;
        }
    }

    [DataContract]
    public class BltUeServiceSettings : BaseSettings
    {
        [XmlElement]
        public int ServicePort { get; set; }

        public BltUeServiceSettings()
        {
            this.ServicePort = 8052;
        }
    }
}
