
import clr;

class PhoneReset(object) :
    DisplayName = 'phone reset'
    Category = 'Timeouts'
    Description = "Phone's reset timeout in seconds. Default = 30."
    DefaultValue = 30

class SendAndReceiveMessage(object) :
    DisplayName = 'send and receive message'
    Category = 'Timeouts'
    Description = "Send and receive message timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class ReceiveMessagesFrom(object) :
    DisplayName = 'receive messages from'
    Category = 'Timeouts'
    Description = "Receive messages from timeout in milliseconds. Default = 5000."
    DefaultValue = 5000

class ExpectTimeout(object) :
    DisplayName = 'expect timeout'
    Category = 'Timeouts'
    Description = "Expect timeout in milliseconds. Default = 5000"
    DefaultValue = 5000

class ExpectLength(object) :
    DisplayName = 'expect length'
    Category = 'Timeouts'
    Description = "Expect length in milliseconds. Default = 0"
    DefaultValue = 0

class ExpectWait(object) :
    DisplayName = 'expect wait'
    Category = 'Timeouts'
    Description = "Expect wait in milliseconds. Default = 0"
    DefaultValue = 0

class ResendMessageInUse(object) :
    DisplayName = 'resend message in use'
    Category = 'Message resending'
    Description = "Message resend feature enabled. Default = True"
    DefaultValue = True

class ResendCount(object) :
    DisplayName = 'resend count'
    Category = 'Message resending'
    Description = "Number of times a message is resent. Default = 3"
    DefaultValue = 3

class TimeoutBetweenTries(object) :
    DisplayName = 'timeout between tries'
    Category = 'Message resending'
    Description = "Timeout in seconds between tries. Default = 5"
    DefaultValue = 5

class GuiFrameworkProtocolPort(object) :
    DisplayName = 'gui - fw protocol port'
    Category = 'Port config'
    Description = "Protocol port for GUI - FW communication. Default is 31336. Integer 1-65535"
    DefaultValue = 31336

class PathForTempFiles(object) :
    DisplayName = 'path for temp files'
    Description = "Path where temporary files are stored. Default = '' (Files are stored under isa_test)"
    DefaultValue = ''
