"""Connection module for Marble Framework.

    Implements socket level connection and application level connection
    between FW server and client (can be GUI or CLI).

"""
from interfaces.socket_connection import SocketClient, SocketServer, \
                                              SocketTimeoutException,\
                                              SocketErrorException,\
                                              SocketNonBlockingException

fw2guiInfoDict = {
    'Musti logs':'Info message: Musti logs:',
    'Recorder events':'Info message: Recorder events',
    'Difference warning':'Info message: Difference warning:', #art-pack sw != phone sw
    'HWID warning':'Info message: HWID warning:', # Target's HWID != HWID variable in *_env.txt file
    'Flash not completed':'Info message: Flash not completed:',
    'Flash failure warning':'Info message: Flash failure warning:'
}
        

# client - FW server protocol message definitions
class ProtocolMessages:
    """Defines the messages used in GUI<->FW protocol traffic."""
    # FIXME protocol version number or SVN revesion number must be checked
    # GUI and FW must have same version
    CMD_RUN = 'run'                                           # request FW to run test case
    CMD_QUIT = 'quit'                                         # request FW to quit
    CMD_STOP = 'stop'                                         # request FW to stop
    CMD_SETTINGS = 'settings'                                 # send settings file name to FW
    CMD_CAPTURE = 'capture'                                   # request FW to take display capture
    CMD_INIT_SERVER  = 'init_server'                          # request FW to initialize the socket server
    CMD_TESTRUN_END = 'test_run_end'                          # indicate end of test run to FW
    CMD_DISABLE_LOCK_SCREEN = 'disable_lock_screen'           # request FW to disable lock screen
    CMD_EXECUTE = 'execute'                                   # request FW to execute test step

    RESP_WAIT = 'marble_wait'                  # command received response
                                                # FW starts executing command

    RESP_READY = 'marble_resp'                 # command executed response
                                                # FW ready to receive new command

    RESP_ERROR = 'marble_error'                # error occurred in execution
                                                # FW ready to receive new command

    RESP_BLACKBOX_READY = 'blackbox_ready_resp' # command executed response
                                                # BlackBox ready for test execution
    
    #SOCK_TIMEOUT = 'sock_timeout'      # not in use

    # If there are parameters in command, this separator is used to
    # separate command and parameters
    COMMAND_SEPARATOR = '|'

    # client - FW server error messages
    # If FW cannot execute command one of these arror messages
    # are sent to GUI instead of RESP_WAIT message

    ERR_ARGUMENTS = 'ERR: Invalid number of arguments for command %s. ' \
                    'Required %s got %s.'
    ERR_COMMAND = 'ERR: Invalid command %s.'

msg = ProtocolMessages

class FwEventDefinitions(object):
    """Defines the Framework events."""
    FW_DEAD = 'fw%s_dead'
    FW_CONNECTED = 'fw%s_connected'
    FW_TIMEOUT = 'fw%s_timeout'
    FW_WAIT = 'fw%s_wait'
    FW_READY = 'fw%s_ready'
    FW_ERROR = 'fw%s_error'
    FW_DATA = 'fw%s_data'
    FW_NO_MESSAGE = 'fw%s_no_message'
    FW_RECORDER_READY = 'fw%s_recorder_ready'
    FW_RECORDER_STOP = 'fw%s_recorder_stop'

    def __init__(self, fwIndex):
        """Defines Framework event definitions."""
        # NOTE: Remove this when more processes can exist!
        assert fwIndex in [1, 2], 'Wrong fwIndex given!'

        # make list attributes which are fw messages.
        # store also attribute values
        events = [(i, getattr(self, i)) \
                 for i in dir(self) if i.startswith('FW_')]

        # list of event_values
        self.fwEvents = []

        # loop trough events and set index number to event value        
        for event_name, event_value in events:
            self.fwEvents.append(event_value)
            setattr(self, event_name, event_value % fwIndex)

class FWServer(SocketServer):
    """ Implementation for control protocol server """
    # message: (number of parameters, execution timeout)
    commands = {msg.CMD_RUN: (2, 120),      # can also have more than 2 parameters
                msg.CMD_QUIT: (0, 20),
                msg.CMD_STOP:(0,20),
                msg.CMD_SETTINGS: (1, 10),
                msg.CMD_CAPTURE: (1, 10),
                msg.CMD_INIT_SERVER:(0,20),
                msg.CMD_TESTRUN_END:(0, 10),
                msg.CMD_DISABLE_LOCK_SCREEN:(0,60),
                msg.CMD_EXECUTE:(0,60),}
                #msg.CMD_RECORDER_START:(0, 10),
                #msg.CMD_RECORDER_STOP:(0, 10),
                #msg.CMD_RECORDER_VERIFY:(2, 10),
                #msg.CMD_RECORDER_CLEAR:(0, 10),
                #msg.CMD_RECORDER_BROWSE:(1,10)}

    def receiveMessage(self):
        """Receives control protocol message and interpretes it.

            Sends ok response if valid command and parameters,
            otherwise sends error response to client.

            Returns
                message ID
                parameters in list
                or None,None when invalid command
        """
        message = SocketServer.receiveMessage(self)
        #words = message.split(msg.COMMAND_SEPARATOR)
        words = message.strip().split(msg.COMMAND_SEPARATOR)

        if words:
            command = words[0]
            args = words[1:]
            
            if self.commands.has_key(command):
                numberOfArgs, timeout = self.commands[command]
                if len(args) >= numberOfArgs:
                    # command OK
                    self.sendWaitMessage(timeout, 'command OK')
                    return command, args
                else:
                    # invalid argument amount
                    self.sendErrorMessage(msg.ERR_ARGUMENTS % \
                                (command,
                                 numberOfArgs,
                                 len(args)))
            elif command == '':
                # skip empty command
                # sometimes these can appear in socket traffic interrupts
                return None, None
            else:
                # invalid command
                self.sendErrorMessage(msg.ERR_COMMAND % command)

        return None, None

    def sendReadyMessage(self, command):
        """Sends ready to receive command to client.
        
            Parameters
            
            command         command which has been executed
        """
        try:
            self.sendMessage(msg.RESP_READY + msg.COMMAND_SEPARATOR + command)
        except SocketErrorException:
            # This should occur only when fw is trying to send and GUI is
            # no longer listening
            debug('Error: socket disconnected in GUI when trying to send')

    def sendErrorMessage(self, error):
        """Sends error message to client.

            Parameters

                error       error traceback in string
        """
        # take possible COMMAND_SEPARATORs away from error
        error = error.replace(msg.COMMAND_SEPARATOR, '_')
        self.sendMessage(msg.RESP_ERROR + msg.COMMAND_SEPARATOR + error)

    def sendWaitMessage(self, timeout, comment):
        """Sends wait message to client.

            Parameters

                timeout     timeout in seconds
                comment     comment in string
        """
        # take possible COMMAND_SEPARATORs away from comment
        comment = comment.replace(msg.COMMAND_SEPARATOR, '_')

        self.sendMessage(msg.RESP_WAIT +
                         msg.COMMAND_SEPARATOR +
                         str(timeout) + 
                         msg.COMMAND_SEPARATOR +
                         comment)

    def sendBlackBoxReadyMessage(self):
        """Sends BlackBox ready message to client."""
        try:
            self.sendMessage(msg.RESP_BLACKBOX_READY)
        except SocketErrorException:
            # This should occur only when fw is trying to send and GUI is
            # no longer listening
            debug('Error: socket disconnected in GUI when trying to send')
