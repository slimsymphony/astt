using System.Runtime.Serialization;
using System.ServiceModel;
using System.Collections;
using System.Xml;
using System.Collections.Generic;
using System;
using System.Dynamic;
using System.Xml.Linq;

namespace Nokia.Granite.IPC.Interfaces
{
    public interface IGraniteFollowerCallback
    {
        [OperationContract]
        string GetClientId();

        [OperationContract]
        void PressKey(string key, int delay);

        [OperationContract]
        void TouchEvent(List<TouchTask> graniteTouchTasks);

        [OperationContract]
        void StopTest();

        [OperationContract]
        void AbortCurrentTestCase();

        [OperationContract]
        bool InitializeTestCase(string[] attributes);

        [OperationContract]
        void ExecuteString(StringTask strTask);

        [OperationContract]
        void SaveCurrentState(XElement dump);

        [OperationContract]
        void InputString(InputTask inputTask);

        [OperationContract]
        void RemotePhoneExecute(RemotePhoneTask remoteTask);

        [OperationContract]
        void VirtualPhoneExecute(VirtualPhoneTask virtualPhoneTask);

        [OperationContract]
        void SaveImageDictionary(Dictionary<string, string> imageDict);

        [OperationContract]
        void SaveLayoutMaps(LayoutMapSaveTask st);

        [OperationContract]
        bool Ping();

        [OperationContract]
        int GetStatus();

        [OperationContract]
        Dictionary<string, string> GetResults();
    }

    [ServiceContract(SessionMode = SessionMode.Required, CallbackContract = typeof(IGraniteFollowerCallback))]
    public interface IGraniteLeadService
    {
        [OperationContract]
        bool ClientSubscribe(string clientId);

        [OperationContract]
        bool ClientUnsubscribe(string clientId);

        [OperationContract]
        void ConfigurationRequest(ConfigurationRequestTask ct);

        [OperationContract]
        bool KeepAlive(string clientId);

        [OperationContract]
        void ClientFiasco(string clientId, string reason, string step);

        [OperationContract]
        void ClientFail(string clientId, string reason, string step);

        [OperationContract]
        void AddVariable(string variable);
        
    }

    [DataContract]
    public class TouchDataPlain
    {
        public TouchDataPlain(string eventType, int x, int y, int wait)
        {
            EventType = eventType;
            X = x;
            Y = y;
            Wait = wait;
        }

        [DataMember]
        public string EventType;

        [DataMember]
        public int X;

        [DataMember]
        public int Y;

        [DataMember]
        public int Wait;
    }

    //[DataContract]
    //public class TouchData
    //{
    //    // carries xml format of data
    //    public TouchData(XmlElement node)
    //    {
    //        Xml = node;
    //    }
    //    [DataMember]
    //    public XmlElement Xml;

    //}

    //[DataContract]
    //public class GraniteUIState
    //{
    //    public GraniteUIState(XElement dump)
    //    {
    //        XmlDump = dump;
    //    }
    //    [DataMember]
    //    public XElement XmlDump;

    //}

    #region Service DataContracts
    [DataContract]
    public class ServiceTask // base class for service tasks
    {
        // client Id who made the request
        [DataMember]
        public string ClientId { get; set; }

        public ServiceTask(string clientId)
        {
            ClientId = clientId;
        }

    }

    [DataContract]
    public class FiascoTask : ServiceTask
    {
        [DataMember]
        public string Reason;

        [DataMember]
        public string Step;

        public FiascoTask(string clientId, string reason, string step)
            : base(clientId)
        {
            Reason = reason;
            Step = step;
        }
    }

    [DataContract]
    public class FailureTask : ServiceTask
    {
        [DataMember]
        public string Reason;

        [DataMember]
        public string Step;

        public FailureTask(string clientId, string reason, string step)
            : base(clientId)
        {
            Reason = reason;
            Step = step;
        }
    }
    

    [DataContract]
    public class ConfigurationRequestTask : ServiceTask
    {
        //[DataMember]
        //public string newProperty { get; set; }

        public ConfigurationRequestTask(string clientId) : base(clientId)
        {
            // no other properties to be set
        }
    }

    #endregion

    #region Client DataContracts

    [DataContract]
    public class QueueTask // base class for client task
    {
        // test case defines currently ongoing test case
        [DataMember]
        public string TestCase { get; set; }

        // test step defines currently ongoing test step
        [DataMember]
        public string TestStep { get; set; }

        public QueueTask(string tCase, string step)
        {
            TestCase = tCase;
            TestStep = step;
        }

    }

    [DataContract]
    public class InputTask : QueueTask
    {
        [DataMember]
        public string InputString { get; set; }
        [DataMember]
        public bool Evaluate { get; set; }
        [DataMember]
        public string Mode { get; set; }
        [DataMember]
        public string Orientation { get; set; }
        [DataMember]
        public int DelayBetweenPresses{ get; set; }
        [DataMember]
        public string ToBeEvaluatedSettings { get; set; }
    
        public InputTask(string tCase, string step, string inputString, bool evaluate, string mode, string orientation, int delayBetweenPresses, string toBeEvaluatedSettings)
            : base(tCase, step)
        {
            Evaluate = evaluate;
            InputString = inputString;
            Mode = mode;
            Orientation = orientation;
            DelayBetweenPresses = delayBetweenPresses;
            ToBeEvaluatedSettings = toBeEvaluatedSettings;
        }
    }

    [DataContract]
    public class LayoutMapSaveTask : QueueTask
    {
        [DataMember]
        public string LayoutRepresentation; // todo: layoutmap -> dictionary[int][str]:((int,int),int,int)

        [DataMember]
        public int LayoutReprLen;

        public LayoutMapSaveTask(string tCase, string step, string layoutRepr)
            : base(tCase, step)
        {
            LayoutRepresentation = layoutRepr;
            LayoutReprLen = layoutRepr.Length;
        }
    }

    [DataContract]
    public class ImageDictSaveTask : QueueTask
    {
        [DataMember]
        public Dictionary<string, string> ImageDict;

        public ImageDictSaveTask(string tCase, string step, Dictionary<string, string> imageDict)
            : base(tCase, step)
        {
            ImageDict = imageDict;
        }
    }

    [DataContract]
    public class StringTask : QueueTask
    {
        [DataMember]
        public string ExecString;

        public StringTask(string tCase, string step, string execString)
            : base(tCase, step)
        {
            ExecString = execString;
        }
    }

    [DataContract]
    public class TouchTask : QueueTask
    {
        [DataMember]
        public XElement TouchData;

        [DataMember]
        public double Interval;

        public TouchTask(string tCase, string step, XElement touchData, double interval )
            : base(tCase, step)
        {
            TouchData = touchData;
            Interval = interval;
        }
    }

    [DataContract]
    public class RemotePhoneTask : QueueTask
    {
        [DataMember]
        public string Method;

        [DataMember]
        public List<object> Args;
                
        [DataMember]
        public Dictionary<object, object> Kwargs;

        [DataMember]
        public List<int> ArgsEvalIndex;

        [DataMember]
        public List<int> KwargsEvalIndex;

        [DataMember]
        public string ToBeEvaluatedSettings;

        public RemotePhoneTask(string tCase, string step, string method, List<object> args, List<int> argsEvalIndex, Dictionary<object, object> kwargs, List<int> kwargsEvalIndex, string toBeEvaluatedSettings)
            : base(tCase, step)
        {
            Method = method;
            Args = args;
            Kwargs = kwargs;
            ArgsEvalIndex = argsEvalIndex;
            KwargsEvalIndex = kwargsEvalIndex;
            ToBeEvaluatedSettings = toBeEvaluatedSettings;
        }
    }

    [DataContract]
    public class VirtualPhoneTask : QueueTask
    {
        [DataMember]
        public string Method;

        [DataMember]
        public List<object> Args;

        [DataMember]
        public List<int> ArgsEvalIndex;

        [DataMember]
        public Dictionary<object, object> Kwargs;

        [DataMember]
        public List<int> KwargsEvalIndex;

        public VirtualPhoneTask(string tCase, string step, string method, List<object> args, List<int> argEvalIndex, Dictionary<object, object> kwargs, List<int> kwargEvalIndex)
            : base(tCase, step)
        {
            Method = method;
            Args = args;
            Kwargs = kwargs;
            ArgsEvalIndex = argEvalIndex;
            KwargsEvalIndex = kwargEvalIndex;
        }
    }

    #endregion
    
}
