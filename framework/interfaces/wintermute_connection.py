""" Wintermute connection testing module. To be executed via CPython 

""" 
import socket, time, cPickle, codecs, struct

TCP_IP = '127.0.0.1'
TCP_PORT = 46521
BUFFER_SIZE = 1024

MULTILINE_SX = """\"\"\"
(begin
                (define (get-granite-text-metadata)
                    (define text-dict "")
                    (define out-xml (create-builtin-xml-builder))

                    (send out-xml open-element "texts")

                    (dictionary-for-each meta-dict
                        (lambda (key value)
                            (dictionary-for-each value
                                (lambda (key2 value2)
                                    (when (equal? key2 'texts)
                                        (set! text-dict value2)
                                    )
                                )
                            )
                            (when (not (equal? text-dict ""))
                                (dictionary-for-each text-dict
                                    (lambda (text-key text-value)
                                        (define text-id (send text-value ->string))
                                        (define text-translation (send (xlate text-value) ->string))
                                        (when (not (equal? text-id text-translation))
                                            (send out-xml open-element "text")
                                            (send out-xml add-attribute "app" (send key ->string))
                                            (send out-xml add-attribute "id" text-id)
                                            (send out-xml add-attribute "translation" text-translation)
                                            (send out-xml close-element)
                                        )
                                    )
                                )
                                (set! text-dict "")
                            )
                        )
                    )

                    (dictionary-for-each xlate-db
                        (lambda (key value)
                            (send out-xml open-element "text")
                            (send out-xml add-attribute "app" "common")
                            (send out-xml add-attribute "id" (send key ->string))
                            (send out-xml add-attribute "translation" (send value ->string))
                            (send out-xml close-element)
                        )
                    )

                    (send out-xml close-element)

                    out-xml
                )

                (send (get-granite-text-metadata) get-data)
            )\"\"\""""

class WintermuteConnection(object):
    """ class to communicate with Granite framework """ 

    def __init__(self):
        self.TCP_IP = '127.0.0.1'
        self.TCP_PORT = 46521
        self.BUFFER_SIZE = 204800 # warning: no message length specified in granite side
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def disconnect(self):
        """ disconnect from Granite framework """ 
        self.s.shutdown(1)
        self.s.close()

    def connect(self):
        """ try connecting to Granite framework """
        try:
            self.s.connect((self.TCP_IP, self.TCP_PORT))
            print('Wintermute connection established')
            return True
        except Exception as e:
            print('Exception with Wintermute connection: %s' % e.message)

        return False

    def receive(self):
        """ receive a message via socket 
        Returns (tuple)
            (success, data) : Indication whether operation was ok and
                              Message data from operation (depends on the command executed)
        
        """
        MAX_MESSAGE_LENGTH = 1638400

        try:
            data = self.s.recv(MAX_MESSAGE_LENGTH)
            
        except Exception as e:
            print('Exception with data receive: %s' % e.message)
            
        try:
            data = cPickle.loads(data)
                
        except Exception as e:
            data ='exception with unpickle: %s' % e.message 
            data  = [False, data]
            return data
        else:
            return data

    def send(self, operation, input, message=None):
        """ send a message to Granite framework 
        Parameters:
        operation(str)  :  'OPERATION', 'WAIT', 'TC_END'
        input(str)      :  Operation to exececute or TC result (Passed, Failed)
        message(str)    :  Message to be added to case result

        """ 

        assert operation in ['OPERATION', 'WAIT', 'TC_END'], "Invalid operation. Valid ones: 'OPERATION', 'WAIT', 'TC_END'"
        assert type(input) == str, 'Input is not a string'

        if message and type(message) == str:
            data = (op, input, msg)
        else:
            data = (op, input)

        print('sending %s' % repr(data))
        try:
            self.s.send( cPickle.dumps(data) )
            return True
        except Exception as e:
            print('Could not send data: %s' % e.message)
            try:
                print('Closing connection..')
                self.s.shutdown()
                self.s.close()
            except:
                pass

        return False



# Testing via command line: 

g = WintermuteConnection()
connection = False

input = raw_input('1: Execute Granite as client \n2: Granite GUI executing cases\n> ')

# If Granite GUI executes wintermute, it needs to listen the testData/tcClass after connection
# If Granite is working as client, tc listening is not needed
if input == '1':
    tcdata = True
else:
    tcdata = False

while True:

    if not connection:
        if g.connect():
            connection = True
        else:
            print('no connection..')
            connection = False

    
    if connection and not tcdata:
        # receive the TC info on first message (when Granite GUI is executing cases)
        success, data = g.receive()
        if not success:
            print('initial receive was not successful: %s' % repr(data))
            exit(1)
        else:
            print('Test case details %s' % (repr(data)))
            tcdata = True

    if connection:
        input = raw_input('1: OP 2: WAIT 3: TC_END 4: multiline test > ')
        if input == '1':
            op = 'OPERATION'
        elif input == '2':
            op = 'WAIT'
        elif input == '3':
            op = 'TC_END'
        elif input == '4':
            op = 'OPERATION'
        else:
            continue
        if input != '4':
            input = raw_input('params? > ')
            if op == 'TC_END':
                msg = raw_input('message? > ')
            else:
                msg = None
        else:
            input = 'self.sx(%s)' % MULTILINE_SX
            msg = None

        if not g.send(op, input, msg):
            print ('Error with connection')

        else: # receive a response from of the command
            if msg == None: # this was not TC end
                success, data = g.receive()

                if not success:
                    print('Error: %s' % data)

                else:
                    if data:
                        data = data.encode("utf-8")

                    if data and len(repr(data)) < 50:
                        print('response from granite:\n%s' % repr(data))
                    elif data:
                        print('response got from granite:\n%s ...(snip)... %s' % (str(data)[:30], str(data)[-30:]))

            else:
                print('tc ended')
                g.disconnect()
                break


