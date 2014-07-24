using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Class for holding constant values for this assembly
    /// </summary>
    public class Constants
    {
        public const string UI_AUTOMATOR_PROCESS_NAME =         "TAServer";

        public const string TEST_SERVER_ARCHIVE_NAME =          "TAServer.jar";
        public const string TEST_SERVER_PACKAGE_NAME =          "Server";
        public const string TEST_SERVER_CLASS_NAME =            "TAServer";
        public const string TEST_SERVER_ENTRY_METHOD_NAME =     "start";
        public const string TEST_SERVER_EVENT_SUBSCRIPTION =    "subscribeForEvents";
        public const string TEST_SERVER_REMOTE_PATH =           "/data/local/tmp/";
        public const int TEST_SERVER_START_TIMEOUT = 15000;

        public const string SCRIPTING_SERVICE_APK_NAME =        "sl4a_r6.apk";
        public const string SCRIPTING_SERVICE_PACKAGE_NAME =    "com.googlecode.android_scripting";
        public const string SCRIPTING_SERVICE_ACTION_NAME =     "com.googlecode.android_scripting.action.LAUNCH_SERVER";
        public const string SCRIPTING_SERVICE_KILL_ACTION_NAME= "com.googlecode.android_scripting.action.KILL_ALL";
        public const string SCRIPTING_SERVICE_COMPONENT_NAME =  "com.googlecode.android_scripting/.activity.ScriptingLayerServiceLauncher";
        public const string SCRIPTING_SERVICE_PORT_EXTRA_KEY =  "com.googlecode.android_scripting.extra.USE_SERVICE_PORT";

        public const int DEFAULT_SERVER_PORT_RANGE_START = 30300;
        public const int DEFAULT_SERVER_PORT_RANGE_END = 30500;
        public const int DEFAULT_SCRIPTING_PORT_RANGE_START = 30501;
        public const int DEFAULT_SCRIPTING_PORT_RANGE_END = 30800;

        public const int RPC_MESSAGE_HEADER_LENGTH = 18;
        public const int RPC_MAX_PACKET_SIZE = 1024 * 4; //This is the maximum payload size with ADB itself

        public const string DEVICE_START_TIME_TAG = "ro.runtime.firstboot";
    }
}
