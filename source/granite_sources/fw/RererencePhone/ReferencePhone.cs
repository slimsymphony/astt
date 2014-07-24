using System;
using System.Globalization;
using System.Threading;
using Nokia.RD.Communication;
using Nokia.RD.CoreTestTool;
using Nokia.Trident.Phone;
using Nokia.Trident.Phone.Call.Messages;
using Nokia.Trident.Phone.Commgr.Messages;
using Nokia.RD;
using System.IO;
using System.Reflection;


namespace Nokia.Granite.Connection.ReferencePhone
{
    public class ReferencePhone
    {
        #region Private Members

        private CommunicationAdapter phoneConnection;
        private ConnectionManager connectionManager;
        private string conIdentifier;

        #endregion

        #region Constructor(s)

        /// <summary>
        /// Constructs the class
        /// </summary>
        /// <param name="connectionManager"></param>
        /// <param name="conIdentifier">Connection name. E.g. USB1 or Guid E.g. GConnId_3739686824a14000</param>
        public ReferencePhone(ConnectionManager connectionManager, string conIdentifier)
        {
            // Ensure that proper culture specific settings are always used!
            // We do not want to see any incorrect .ToString() and Double.Parse() behaviour related to
            // DateTime or NumberDecimalSeparator.

            Thread.CurrentThread.CurrentCulture = GetCulture();
            Thread.CurrentThread.CurrentUICulture = GetCulture();

#if TRACE_LOG || TRACE_LOG_CRITICAL // 17.09.2012 added compiler flag to enable text file logging.
            if (logWriter != null)
            {
                logWriter.WriteLine("Closing File");
                logWriter.Flush();
                logWriter.Close();
            }

            string graniteDir = Directory.GetCurrentDirectory() + @"\Framework_logs\";
            if (!Directory.Exists(graniteDir))
            {
                graniteDir = Directory.GetCurrentDirectory();
            }

            graniteDir += @"\ReferencePhone_Log_" + DateTime.Now.ToString("yyyy-MM-dd_HH.mm.ss") + ".txt";
            logStream = new FileStream(graniteDir, FileMode.Create, FileAccess.Write, FileShare.Read);
            logWriter = new StreamWriter(logStream, Encoding.UTF8, 128);
#endif
#if TRACE_LOG_CRITICAL
            logWriter.AutoFlush = true;
#endif
            phoneConnection = null;
            this.connectionManager = connectionManager;
            this.conIdentifier = conIdentifier;
            connectPhone();
            checkPhoneConnectionAndReconnectIfNotConnected();
        }

        #endregion

        #region Public Mehtods


        public void SendSMS(string phoneNumber)
        {
            //Phonet & ISI message headers for SMS_MESSAGE_SEND_REQ
            Byte[] msgHeader = { 0x00, 0x00, 0x10, 0x02, 0x00, 0x0a, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 };

            // rest of the sub block data
            //Byte[] msgSubBlocks = { 0x00, 0x33, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x10, 0x02, 0x08, 0x07, 0x91, 0x53, 0x58, 0x80, 0x77, 0x01, 0x01, 0x00, 0x00 };
            //Byte[] msgSubBlocks = { 0x00, 0x33, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x10, 0x02, 0x08, 0x07, 0x91, 0x53, 0x58, 0x80, 0x77, 0x01, 0x01, 0x00, 0x00 };
            //Byte[] msgSubBlocks = { 0x00, 0x33, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x10, 0x02, 0x08, 0x07, 0x91, 0x53, 0x48, 0x45, 0x04, 0x00, 0x15, 0x00, 0x00 };
            Byte[] msgSubBlocks = { 0x00, 0x33, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x10, 0x02, 0x08, 0x07, 0x91, 0x53, 0x58, 0x80, 0x77, 0x01, 0x01, 0x00, 0x00 };


            byte[] phoneNumber_sb = SMS_SB_TPDU(phoneNumber);

            byte[] ret = new byte[msgHeader.Length + phoneNumber_sb.Length + msgSubBlocks.Length];
            Array.Copy(msgHeader, 0, ret, 0, msgHeader.Length);
            Array.Copy(phoneNumber_sb, 0, ret, msgHeader.Length, phoneNumber_sb.Length);
            Array.Copy(msgSubBlocks, 0, ret, msgHeader.Length + phoneNumber_sb.Length, msgSubBlocks.Length);

            ret[4] = (byte)ret.Length;

            PhonetMessage msg = new PhonetMessage(ret);

            phoneConnection.MessageApiSender.BeginSend(msg);

        }

        /// <summary>
        /// Sends a MMS to entered phone number
        /// </summary>
        /// <param name="phoneNumber"></param>
        public void SendMMS(string phoneNumber, string msgType)
        {

            Assembly assembly = Assembly.GetExecutingAssembly();
            Stream objStream;
            if (msgType == "contact")
            {
                objStream = assembly.GetManifestResourceStream("Nokia.Granite.Connection.ReferencePhone.contact.mms");
            }
            else if (msgType == "calendar")
            {
                objStream = assembly.GetManifestResourceStream("Nokia.Granite.Connection.ReferencePhone.calendar.mms");
            }
            else
            {
                objStream = assembly.GetManifestResourceStream("Nokia.Granite.Connection.ReferencePhone.granite.mms");
            }

            byte[] msgBin = new byte[objStream.Length];

            objStream.Read(msgBin, 0, msgBin.Length);

            msgBin[12] = (byte)(phoneNumber.Length + 12);

            byte[] newMsg = new byte[msgBin.Length + phoneNumber.Length];

            // Copy start of the message
            Array.Copy(msgBin, 0, newMsg, 0, 14);

            // Add custom phone number
            for (int i = 0; i < phoneNumber.Length; i++)
            {
                newMsg[i + 14] = (byte)phoneNumber[i];
            }

            // Copy rest of the MMS to buffer
            Array.Copy(msgBin, 14, newMsg, 14 + phoneNumber.Length, msgBin.Length - 14);

            FileServerAdapter fsa = new FileServerAdapter(phoneConnection.MessageApiSender, phoneConnection.PMDLoader, phoneConnection.BinaryLog);
            
            

            fsa.WriteFromBuffer(@"C:\predefmessages\exchange\" + FormatExchangeFilename(phoneNumber), ref newMsg);

            UpdateMessages();

        }

        public void Touch(int x, int y)
        {

            byte[] touch = TOUCHPAD_PEN_EVENT_NTF(x, y, 0);
            PhonetMessage msg = new PhonetMessage(touch);
            phoneConnection.MessageApiSender.BeginSend(msg);

            Thread.Sleep(33);
            byte[] touch1 = TOUCHPAD_PEN_EVENT_NTF(x, y, 1);
            PhonetMessage msg1 = new PhonetMessage(touch1);
            phoneConnection.MessageApiSender.BeginSend(msg1);

            Thread.Sleep(33);
            byte[] touch2 = TOUCHPAD_PEN_EVENT_NTF(x, y, 2);
            PhonetMessage msg2 = new PhonetMessage(touch2);
            phoneConnection.MessageApiSender.BeginSend(msg2);
        }


        /// <summary>
        /// Creates a MobileOriginated call to the given phone number. Number is given in international format. E.g. +3580501234567
        /// </summary>
        /// <param name="phoneNumber"></param>
        public int CreateCall(string phoneNumber)
        {
            RejectCall();

            CallType2 callType = CallType2.CALL_NBR_TYPE_INTERNATIONAL;
            if (phoneNumber.StartsWith("+"))
            {
                phoneNumber = phoneNumber.TrimStart('+');
            }
            else
            {
                if (phoneNumber.StartsWith("0"))
                {
                    callType = CallType2.CALL_NBR_TYPE_UNKNOWN;
                }
            }
            
            CallCreateReq createReq = new CallCreateReq();
            createReq.Add(new CallDestinationAddress(CallType2.CALL_NBR_PLAN_ISDN_TELEPHONY | callType, CallType3.CALL_PRESENTATION_ALLOWED, phoneNumber));
            createReq.Mode = new Mode(CallType.CALL_MODE_SPEECH, CallType1.CALL_MODE_ORIGINATOR);

            createReq.Validate();

            byte[] resp = trySendMessage((byte)PNType.PN_CALL, createReq.ToArray());

            if (resp != null && resp.Length > 10)
            {
                return resp[10];
            }
            throw new InvalidOperationException("ReferencePhone: CreateCall failed! Unable to parse CallID from phone response. Illegal response from the phone. Try to flash a newer FW version to the phone or use another phone.");
        }

        /// <summary>
        /// Releases a call. Either mobile originated or mobile terminated
        /// </summary>
        public void ReleaseCall(int callId)
        {
            // Terminate CallID (callId), Termination cause DEFAULT.
            terminateCall(callId, 3);
        }

        /// <summary>
        /// Answers to an incoming call
        /// </summary>
        /// <returns></returns>
        public int AnswerCall()
        {
            CallAnswerReq answerReq = new CallAnswerReq(1, CallIDType.CALL_ID_1);

            answerReq.Validate();

            byte[] resp = trySendMessage((byte)PNType.PN_CALL, answerReq.ToArray());

            if (resp != null && resp.Length > 10)
            {
                return resp[10];
            }
            throw new InvalidOperationException("ReferencePhone: AnswerCall failed! Unable to parse CallID from phone response. Illegal response from the phone. Try to flash a newer FW version to the phone or use another phone.");
        }

        /// <summary>
        /// Rejects an incoming call
        /// </summary>
        public void RejectCall()
        {
            // Terminate CallID 1, Termination cause BUSY_USER (reject).
            terminateCall(1, 4);
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Creates SMS_SB_TPDU sub block for SMS_MESSAGE_SEND_REQ message
        /// </summary>
        /// <param name="phonenumber">Phone number in string format</param>
        private byte[] SMS_SB_TPDU(string phonenumber)
        {
            bool landCodeInUse = false;
            if (phonenumber[0] == '+')
            {
                landCodeInUse = true;
                phonenumber = phonenumber.Remove(0, 1);
            }


            // MSG is "SMS from Granite."
            byte[] msgText = { 0x00, 0x00, 0xff, 0x11, 0xd3, 0xe6, 0x14, 0x64, 0x96, 0xbf, 0xdb, 0xa0, 0xa3, 0x3c, 0xec, 0x4e, 0xd3, 0xcb, 0x2e };

            int msgLength = (phonenumber.Length / 2 + (phonenumber.Length % 2)) + msgText.Length + 10;
            int fillerAmount = 4 - (msgLength % 4);
            if (fillerAmount == 4)
                fillerAmount = 0;

            byte[] ret = new byte[msgLength + fillerAmount];

            /**
             * This byte seems to indecate how phone number is entered 0x81 = normal, 0x91 with land code
             **/

            /*
             * Header of sub block
             */
            ret[0] = 0x00;
            ret[1] = 0x1C; // SB type
            ret[2] = 0x00;
            ret[3] = (byte)(msgLength + fillerAmount); //size
            ret[4] = (byte)((phonenumber.Length / 2) + (phonenumber.Length % 2) + msgText.Length + 4); //datasize
            ret[5] = 0x00;
            ret[6] = 0x11;
            ret[7] = 0x09;
            ret[8] = (byte)phonenumber.Length;
            if (landCodeInUse)
                ret[9] = 0x91;
            else
                ret[9] = 0x81;

            int msgPos = 10;

            for (int i = 0; i < phonenumber.Length / 2 + (phonenumber.Length % 2); i++)
            {
                byte b;
                if (i < phonenumber.Length / 2)
                {
                    b = (byte)(phonenumber[(i * 2) + 1] - 48);
                }
                else
                {
                    b = 0;
                }
                b = (byte)(b << 4);
                b += (byte)(phonenumber[i * 2] - 48);
                ret[i + 10] = b;
                msgPos++;
            }

            // the message text data
            //1c,00,24,1c,00,11,03,0a,81,50,40,38,16,06,00,00,ff,11,d3,e6,14,64,96,bf,db,a0,a3,3c,ec,4e,d3,cb,2e,00,00,
            //byte[] msgText = { 0x00, 0x00, 0xff, 0x0b, 0xcd, 0xb7, 0xfc, 0x4d, 0x07, 0xcd, 0xeb, 0x6c, 0x76, 0x19 };

            foreach (byte b in msgText)
            {
                ret[msgPos] = b;
                msgPos++;
            }
            for (int i = 0; i < fillerAmount; i++)
            {
                ret[msgPos] = 0;
                msgPos++;
            }
            return ret;


        }

        private byte[] TOUCHPAD_PEN_EVENT_NTF(int x, int y, byte state)
        {
            /*
Msg. seq.: 2
   0  (8) Media.......................: 0x00               => PN_MEDIA_ROUTING_REQ
   1  (6) Receiver Device.............: 0x00               => PN_DEV_HOST
   2  (6) Sender Device...............: 0x10               => PN_DEV_PC
   3  (8) Resource....................: 0x70               => PN_TOUCHPAD
   4 (16) Length......................: 0x0022             => 34
   6 (10) Receiver Object.............: 0x000              => PN_OBJ_ROUTING_REQ
   7 (10) Sender Object...............: 0x001              => 1
   8  (8) Transaction ID..............: 0x04               => 4
   9  (8) Message ID..................: 0x01               => TOUCHPAD_PEN_EVENT_NTF
  10  (8) Filler......................: 0x00               => 8 bit padding
  11  (8) Number Of Sub Blocks........: 0x02               => 2
  12 (32) Touch Time Stamp............: 0x00000000         => 00:00:00.000000
Sub block 1: TOUCHPAD_SB_PEN_STATE_INFO
  16  (8) Sub Block ID................: 0x00               => TOUCHPAD_SB_PEN_STATE_INFO
  17  (8) Sub Block Length............: 0x0C               => 12
  18  (8) Touch ID....................: 0x00               => 0
  19  (8) State.......................: 0x00               => TOUCHPAD_PEN_PRESSED
  20 (16) X...........................: 0x1C07             => 7175
  22 (16) Y...........................: 0x24D7             => 9431
  24  (8) Pressure....................: 0x3F               => 63
  25  (8) Type........................: 0x01               => TOUCHPAD_PEN_TYPE_FINGER
  26 (16) Filler......................: 0x0000             => 16 bit padding
Sub block 2: TOUCHPAD_SB_DISPLAY_COORDINATE_DATA
  28  (8) Sub Block ID................: 0x04               => TOUCHPAD_SB_DISPLAY_COORDINATE_DATA
  29  (8) Sub Block Length............: 0x0C               => 12
  30  (8) Touch ID....................: 0x00               => 0
  31  (8) State.......................: 0x00               => TOUCHPAD_PEN_PRESSED
  32 (16) X coordinate................: 0x0087             => 135
  34 (16) Y coordinate................: 0x00B4             => 180
  36  (8) Display touch status........: 0x01               => TOUCHPAD_TOUCH_ON_DISPLAY
  37  (8) Type........................: 0x01               => TOUCHPAD_PEN_TYPE_FINGER
  38 (16) Filler......................: 0x0000             => 16 bit padding

             * */

            /*
            
            int TOUCHPAD_DISPLAY_DIMENSION_PIXELS_X = 240;
            int TOUCHPAD_DISPLAY_DIMENSION_PIXELS_Y = 400;
            int TOUCHPAD_DISPLAY_TOUCH_MAX_X  =  TOUCHPAD_DISPLAY_DIMENSION_PIXELS_X*128;
            int TOUCHPAD_DISPLAY_TOUCH_MAX_Y = TOUCHPAD_DISPLAY_DIMENSION_PIXELS_Y * 128;
            int TOUCH_PER_PIXEL_X = TOUCHPAD_DISPLAY_TOUCH_MAX_X / TOUCHPAD_DISPLAY_DIMENSION_PIXELS_X;
            int TOUCH_PER_PIXEL_Y = TOUCHPAD_DISPLAY_TOUCH_MAX_Y / TOUCHPAD_DISPLAY_DIMENSION_PIXELS_Y;
            */

            Int16 sensorx = (Int16)(x * 53);
            Int16 sensory = (Int16)(y * 53);

            byte[] TOUCHPAD_PEN_EVENT_NTF = new byte[40];
            TOUCHPAD_PEN_EVENT_NTF[0] = 0x00; // media
            TOUCHPAD_PEN_EVENT_NTF[1] = 0x00; // Receiver Device
            TOUCHPAD_PEN_EVENT_NTF[2] = 0x10; // Sender Device
            TOUCHPAD_PEN_EVENT_NTF[3] = 0x70; // Resource
            TOUCHPAD_PEN_EVENT_NTF[4] = 0x00;
            TOUCHPAD_PEN_EVENT_NTF[5] = 0x22;
            TOUCHPAD_PEN_EVENT_NTF[6] = 0x8B;
            TOUCHPAD_PEN_EVENT_NTF[7] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[8] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[9] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[10] = 0x00;
            TOUCHPAD_PEN_EVENT_NTF[11] = 0x02;
            TOUCHPAD_PEN_EVENT_NTF[12] = 0x00; // Timestamp
            TOUCHPAD_PEN_EVENT_NTF[13] = 0x00; // Timestamp
            TOUCHPAD_PEN_EVENT_NTF[14] = 0x00; // Timestamp
            TOUCHPAD_PEN_EVENT_NTF[15] = 0x00; // Timestamp
            TOUCHPAD_PEN_EVENT_NTF[16] = 0x00; // SB ID
            TOUCHPAD_PEN_EVENT_NTF[17] = 0x0C; // SB Lenght
            TOUCHPAD_PEN_EVENT_NTF[18] = 0;
            TOUCHPAD_PEN_EVENT_NTF[19] = state;
            TOUCHPAD_PEN_EVENT_NTF[20] = (byte)(sensorx >> 8);
            TOUCHPAD_PEN_EVENT_NTF[21] = (byte)(sensorx % 0xFF);
            TOUCHPAD_PEN_EVENT_NTF[22] = (byte)(sensory >> 8);
            TOUCHPAD_PEN_EVENT_NTF[23] = (byte)(sensory % 0xFF);
            TOUCHPAD_PEN_EVENT_NTF[24] = 0x3F; // pressure
            TOUCHPAD_PEN_EVENT_NTF[25] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[26] = 0x00; // filler
            TOUCHPAD_PEN_EVENT_NTF[27] = 0x00; // filler
            TOUCHPAD_PEN_EVENT_NTF[28] = 0x04; // sb = TOUCHPAD_SB_DISPLAY_COORDINATE_DATA
            TOUCHPAD_PEN_EVENT_NTF[29] = 0x0c;
            TOUCHPAD_PEN_EVENT_NTF[30] = 0;
            TOUCHPAD_PEN_EVENT_NTF[31] = state;
            TOUCHPAD_PEN_EVENT_NTF[32] = (byte)(x >> 8);
            TOUCHPAD_PEN_EVENT_NTF[33] = (byte)(x % 0xFF);
            TOUCHPAD_PEN_EVENT_NTF[34] = (byte)(y >> 8);
            TOUCHPAD_PEN_EVENT_NTF[35] = (byte)(y % 0xFF);
            TOUCHPAD_PEN_EVENT_NTF[36] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[37] = 0x01;
            TOUCHPAD_PEN_EVENT_NTF[38] = 0x00; //filler
            TOUCHPAD_PEN_EVENT_NTF[39] = 0x00; //filler

            return TOUCHPAD_PEN_EVENT_NTF;
        }




        /// <summary>
        /// Creates time stamp for MMS
        /// </summary>
        /// <param name="phoneNumber"></param>
        private int GetTimeStamp()
        {
            TimeSpan t = DateTime.UtcNow - new DateTime(1980, 1, 1);
            return (int)t.TotalSeconds;
        }

        /// <summary>
        /// Creates data blocks with selected size
        /// </summary>
        /// <param name="phoneNumber"></param>
        private string FormatValue(string input, int size)
        {
            string returnvalue = "";

            if (input.Length > size)
                throw new Exception("Input sting does not fit into data block");

            for (int i = 0; i < size - input.Length; i++)
            {
                returnvalue += '0';
            }
            returnvalue += input;

            return returnvalue;
        }

        /// <summary>
        /// Format filename for message in exchange folder
        /// </summary>
        /// <param name="phoneNumber"></param>
        private string FormatExchangeFilename(string phonenumber)
        {
            string returnvalue = "";

            string uniqueid = "2";
            string timestamp = GetTimeStamp().ToString("X");
            string concat_ref = "0";
            string msgTypes = "12"; //"21";     // SMS
            string msgPriority = "2";   // MESSAGE_STORAGE_PRIORITY_NORMAL
            string message_flags = "0"; // MESSAGE_STORAGE_FLAG_NONE
            string msgStatus = "7";      // 6 = DRAFT, 7 = PENDING
            string retry_count = "0";
            string retry_time = "0";
            string concat_amount = "1";
            string concat_count = "0";
            string tZone = "0";
            string subject = "";

            returnvalue = FormatValue(uniqueid, 8) +
                            FormatValue(timestamp, 8) +
                            FormatValue(concat_ref, 4) +
                            FormatValue(msgTypes, 2) +
                            FormatValue(msgPriority, 1) +
                            FormatValue(message_flags, 2) +
                            FormatValue(msgStatus, 1) +
                            FormatValue(retry_count, 2) +
                            FormatValue(retry_time, 4) +
                            FormatValue(concat_amount, 2) +
                            FormatValue(concat_count, 2) +
                            FormatValue(tZone, 2) +
                            FormatValue(subject.Length.ToString("X"), 2) + // subject here
                            subject +
                            FormatValue(phonenumber.Length.ToString("X"), 2) +
                            phonenumber; //+ sim_id

            return returnvalue;
        }

        /// <summary>
        /// Message storeage update messages message
        /// </summary>
        /// <param name="phoneNumber"></param>
        private void UpdateMessages()
        {
            byte[] messageBinary = { 0x00, 0x00, 0x10, 0xaa, 0x00, 0x06, 0x00, 0x01, 0x07, 0x18, 0x02, 0x00 };

            PhonetMessage msg = new PhonetMessage(messageBinary);
            phoneConnection.MessageApiSender.BeginSend(msg);

            msg.Dispose();
        }

        /// <summary>
        /// Terminates a call. Either releases an ongoing call, or rejects an incoming call.
        /// </summary>
        /// <param name="callId">Id of call to be terminated</param>
        private void terminateCall(int callId, short cc)
        {
            CauseType causeType = new CauseType(CallCauseTypeType.CALL_CAUSE_TYPE_GSM, CallCauseTypeType1.CALL_CAUSE_TYPE_CLIENT);
            Cause cause = new Cause(new Default(cc));
            CallCause callCause = new CallCause(causeType, cause);
            CallReleaseReq releaseReq = new CallReleaseReq(1, (CallIDType)callId, callCause);

            releaseReq.Validate();

            trySendMessage((byte) PNType.PN_CALL, releaseReq.ToArray());
        }

        /// <summary>
        /// Tries to send the message. Retries upon failure.
        /// </summary>
        /// <param name="resource"></param>
        /// <param name="data"></param>
        private byte[] trySendMessage(byte resource, params byte[] data)
        {
            const int sendMessageTryCount = 10;

            // check phone connection before sending
            checkPhoneConnectionAndReconnectIfNotConnected();

            for (int i = 0; i < sendMessageTryCount; i++)
            {
                try
                {
                    return phoneConnection.SendMessage(resource, data);
                }
                catch (Exception ex)
                {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                    ReferencePhone.Log("trySendMessage Exception: " + ex.Message + ex.InnerException + ex.StackTrace);
#endif
                    // Try to disconnect
                    try
                    {
                        this.phoneConnection.Disconnect();
                    }
                    catch { /* Disconnect should not throw exception */ }
                    if (i == sendMessageTryCount)
                    {
                        throw;
                    }

                    // wait for a while and then check phone connection
                    Thread.Sleep(500);
                    checkPhoneConnectionAndReconnectIfNotConnected();
                }
            }
            // This mehthod either succeeds and returns a byte array or either fail and throw an exception.
            return null;
        }

        /// <summary>
        /// Connects the phone
        /// </summary>
        private void connectPhone()
        {
            try
            {
                // If CommunicationAdapter is Disposed phoneConnection.IsConnected will throw an exception.
                if (phoneConnection != null && phoneConnection.IsConnected)
                {
                    return;
                }
            }
            catch (Exception ex)
            {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                    ReferencePhone.Log("connectPhone failed. phoneConnection.IsConnected throwed an exception.  ConnectionManager probably Disposed: " + ex.Message + ex.StackTrace);
#endif
            }

            phoneConnection = getAdapterByConnectionIdentifier(connectionManager, conIdentifier);

            if (phoneConnection == null)
            {
                foreach (FuseConnectionParameter fuseConnectionParameter in connectionManager.GetFuseConnections())
                {
                    if (fuseConnectionParameter.Name == conIdentifier)
                    {
                        ConnectionParameterStrings fuseconnection = connectionManager.FindConnectionParameter(fuseConnectionParameter.Name);
                        connectionManager.Connections.Add(new CommunicationAdapter(new ConnectionParameters(fuseconnection)));
                        phoneConnection = getAdapterByConnectionIdentifier(connectionManager, fuseconnection.sGuid);
                        break;
                    }
                    if (fuseConnectionParameter.Guid == conIdentifier)
                    {
                        ConnectionParameterStrings fuseconnection = connectionManager.FindConnectionParameter(fuseConnectionParameter.Name);
                        connectionManager.Connections.Add(new CommunicationAdapter(new ConnectionParameters(fuseconnection)));
                        phoneConnection = getAdapterByConnectionIdentifier(connectionManager, fuseconnection.sGuid);
                        break;
                    }
                }
            }

            if (phoneConnection == null)
            {
                throw new InvalidOperationException("Error: Unable to connect ReferencePhone. No connection matching " + conIdentifier + " found!");
            }
            if (fuseCheckIsDevicePresent())
            {
                phoneConnection.PMDLoader.Load(@"..\phone_packages\local.pmd");               
                phoneConnection.Connect();
            }
        }

        /// <summary>
        /// From Fuse connections list check whether device is present due to phoneConnection.IsPhoneAvailable seems not always work properly.
        /// </summary>
        /// <returns>IsDevicePresent</returns>
        private bool fuseCheckIsDevicePresent()
        {
            foreach (FuseConnectionParameter fuseConnectionParameter in connectionManager.GetFuseConnections())
            {
                if (fuseConnectionParameter.Name == conIdentifier)
                {
                    return fuseConnectionParameter.IsDevicePresent;
                }
                if (fuseConnectionParameter.Guid == conIdentifier)
                {
                    return fuseConnectionParameter.IsDevicePresent;
                }
            }
            throw new InvalidOperationException("Error: Unable to connect ReferencePhone. No connection matching " + conIdentifier + " found!");
        }

        /// <summary>
        /// Checks the connection and tries to reconnect if not connected.
        /// </summary>
        private void checkPhoneConnectionAndReconnectIfNotConnected()
        {
            // If the device is not preset, wait a while for the device to became present.
            if (!fuseCheckIsDevicePresent())
            {
                phoneConnection.Disconnect();
                int checkCount = 30;
                for (int i = 0; i < checkCount; i++)
                {
                    if (fuseCheckIsDevicePresent())
                    {
                        break;
                    }
                    if (i == checkCount)
                    {
                        throw new InvalidOperationException("Error: Unable to connect ReferencePhone. Phone not present after a timeout of " + checkCount + " seconds!");
                    }
                    Thread.Sleep(1000);
                }
            }

            try
            {
                // If CommunicationAdapter is Disposed phoneConnection.IsConnected will throw an exception.
                if (phoneConnection.IsConnected)
                {
                    return;
                }
            }
            catch (Exception ex)
            {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                    ReferencePhone.Log("checkPhoneConnectionAndReconnectIfNotConnected failed on phoneConnection.IsConnected throwed an exception.  ConnectionManager probably Disposed: " + ex.Message + ex.StackTrace);
#endif
            }

            try
            {
                // If CommunicationAdapter is Disposed phoneConnection.TryReconnect() will throw an exception.
                if (phoneConnection.TryReconnect())
                {
                    return;
                }
            }
            catch (Exception ex)
            {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                    ReferencePhone.Log("checkPhoneConnectionAndReconnectIfNotConnected failed on phoneConnection.TryReconnect() throwed an exception.  ConnectionManager probably Disposed: " + ex.Message + ex.StackTrace);
#endif
            }

            connectPhone();
        }

        /// <summary>
        /// Helper method to get CommunicationAdapter by name or guid
        /// </summary>
        /// <param name="cm"></param>
        /// <param name="ci"></param>
        /// <returns></returns>
        private CommunicationAdapter getAdapterByConnectionIdentifier(ConnectionManager cm, string ci)
        {
            CommunicationAdapter con = null;
            try
            {
                con = cm.GetConnectionByName(ci);

                if (con == null)
                {
                    con = connectionManager.GetConnectionByGuid(ci);
                }
            }
            catch (Exception ex)
            {
#if TRACE_LOG || TRACE_LOG_CRITICAL
                    ReferencePhone.Log("getAdapterByConnectionIdentifier failed: " + ex.Message + ex.StackTrace);
#endif
            }

            return con;
        }

#if TRACE_LOG || TRACE_LOG_CRITICAL
        #region Logger methods.

        private static FileStream logStream;
        private static StreamWriter logWriter;
        internal static void Log(string logText)
        {
            logWriter.WriteLine(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss.fff") + " - " + logText);
        }

        #endregion
#endif

        #endregion

        /// <summary>
        /// Ensure that proper culture specific settings are always used!
        /// We do not want to see any incorrect .ToString() and Double.Parse() behaviour related to
        /// DateTime or NumberDecimalSeparator.
        /// </summary>
        /// <returns>CultureInfo of en-US</returns>
        internal static CultureInfo GetCulture()
        {
            CultureInfo cultureInfo;
            NumberFormatInfo provider = new NumberFormatInfo
            {
                NumberDecimalSeparator = "."
            };
            cultureInfo = new CultureInfo("en-US")
            {
                DateTimeFormat =
                {
                    ShortDatePattern = "dd.MM.yyyy",
                    LongDatePattern = "dd.MM.yyyy",
                    ShortTimePattern = "HH:mm:ss",
                    LongTimePattern = "HH:mm:ss"
                },
                NumberFormat =
                {
                    NumberDecimalSeparator = provider.NumberDecimalSeparator
                }
            };

            return cultureInfo;
        }

    }
}
