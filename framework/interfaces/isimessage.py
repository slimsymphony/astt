# ============================================================================
#                              ISIMessage module
#                           -----------------------
# ----------------------------------------------------------------------------

# ============================================================================
#   1   ABSTRACT
#
#   1.1 Module type
#
#       Test utility
#
#   1.2 Description
#
#       This module implements a common ISI message helper class. The class
#       and its subclasses (implemented elsewhere) take care of packing and
#       unpacking of ISI messages' fields. Errors in (un)packing raise an
#       ISIMessageException.
#
#   1.3 Notes
#
#       Current plan:
#           - Implement subclass of ISIMessage for each non MM'ed ISI IF
#           - Implement PMDMessage class for Message Macros (PMD wrapper)
#
#       The latest documentation for the struct module is here:
#           http://www.python.org/doc/current/lib/module-struct.html
#
#       Code indentation rule: 4 spaces for one indentation level, no tabs!
#       Recommended maximum line length is 79 characters.
#       (see more from: http://www.python.org/doc/essays/styleguide.html)
# ----------------------------------------------------------------------------

# ============================================================================
#   2   CONTENT
#
#       1   ABSTRACT
#       1.1 Module type
#       1.2 Description
#       1.3 Notes
#
#       2   CONTENT
#
#       3   MODULE CODE
#       3.1 ISIMessageException class
#       3.2 ISIMessage class
#       3.n Self test
# ----------------------------------------------------------------------------

""" ART2 internal

"""

# ============================================================================
#   3   MODULE CODE
# ----------------------------------------------------------------------------

# Python library module imports
import time, copy

# Self test setup
if __name__ == '__main__':
    import unittest, sys
    sys.path.insert(1, '..')

from utils.xstruct import xcalcsize, xpack, xunpack
from core.testcase_exceptions import TestException

# Local data structures
class Undefined: pass # Helper class for specifying undefined items (this is
                      # used where None can't be used)

class ISITestResultElement:
    def __init__(self):
        self.timestamp = time.time()

    def toxmlelement(self, element):
        """Get an XML element version of the object.
        """
        try:
            oElement = NodeUtils(str(element), True)
        except:
            oElement = NodeUtils(repr(element), True)

        return oElement                      
                      
# ============================================================================
#   3.1     ISIMessageException class
# ----------------------------------------------------------------------------
class ISIMessageException(TestException):
    """An exception class for errors found while (un)packing or verifying a
       single ISI message.

    Parameters
        isi_message_obj : Instance of the failed message
        errors          : List of tuples describing what went wrong:
                          (field name, expected value, error message)

                          Optionally just a string explaining an error.

                          Notice: ISIMessage's match-function returns similar
                          tuple list as this one.
    """

    def __init__(self, isi_message_obj, errors):
        TestException.__init__(self, 'ISIMessageException')

        assert isinstance(isi_message_obj, ISIMessage), \
            'Expected instance of ISIMessage, got: %s' % \
            (type(isi_message_obj)==type(self) and isi_message_obj.__class__ \
             or type(isi_message_obj))

        # Convert plain string into simple tuple
        if type(errors) == type(''):
            errors = [(None, None, errors)]

        self.isi_message = isi_message_obj
        self.errors = errors

    def __str__(self):
        return '\n'.join([\
            field is not None and expected is not None and \
            '%s in the %s field. Expected:%s' % (msg, field, expected) or \
            field is not None and \
            '%s: %s' % (msg, field) or
            '%s' % (msg) \
            for field, expected, msg in self.errors if msg != None])

    def toxml(self):
        """Return an xml version of the exception.

        Example:
        <error>
            <message_error field='msg_id' expected='10'>
                Error message for the msg_id field.
            </message_error>
            <message_error field='resource'>
                Error message for the resource field. This message_error
                didn't have an expected-value.
            </message_error>
            <message_error>
                Common message_error message.
            </message_error>
        </error>

        FIXME: Include <message>..</message> in the result!
        """
        message_errors = []

        for field, expected, msg in self.errors:
            if msg != None:

                if field != None:
                    field = " field='%s'" % field
                else:
                    field = ''

                if expected != None:
                    expected = " expected='%s'" % expected
                else:
                    expected = ''

                message_errors.append((field, expected, msg))

        message_errors = ''.join(['<message_error%s%s>%s</message_error>' % \
            (field, expected, msg) for field, expected, msg in message_errors])

        return '<error>%s</error>' % message_errors


    def __len__(self):
        return len(self.errors)


# ============================================================================
#   3.2     ISIMessage class
# ----------------------------------------------------------------------------
class ISIMessage(ISITestResultElement):
    """A common base class for ISI message (un)packing classes.

    This class is intended to be used as such for (un)packing and asserting
    common ISI messages or as a base class for other ISI request, response or
    indication classes. The main idea was to hide (un)pack calls from the
    class's users.

    Main features:

    - Message fields are read and written via object's attribute references.

      Example:

      >>> msg=ISIMessage()
      >>> msg.resource = 12
      >>> msg.resource
      12

      Special fields:

      msg.isi_message contains the whole message as a list of bytes.
      msg.msg_data contains the message data part of the message.

      If the length field's value is 'None', it's real value is generated based
      on the message's size - but only if the msg_data field IS defined.

    - Each time a field value is read or written, a special _get_<field_name>
      or _check_set_<field_name> function is called. Make sure that your sub
      classes override _get_msg_data and _check_set_msg_data correctly!

    - Field values can be compared to expected values with __eq__ and match
      functions. __eq__ compares messages by bytes, whereas match provides more
      complex interface for comparing any field for any value (even a range or
      a set).

    - Class is able to raise ISIMessageExceptions. There are some assertXXX-
      functions such as assertFields, failField, failFieldUnless etc. that are
      specially designed for expecting field values. Notice that return value
      of the match function equals with the ISIMessageException class's
      __init__.

    - String version of the object can be get from the __str__ -interface. Use
      msg.<field_name>_str or msg.getattrstr('field_name') to get the string
      view of a field. Notice that you can improve test reporting by
      implementing _get_<field_name>_str -functions for each msg data's field.
      XML-version of the whole message can be get from the toxml function.

    Parameters:
        isi_message_fields      dictionary of isi message field=value -pairs.

        If 'isi_message' is one of the fields, its allowed to be:
            - None or empty list
            - list or tuple of bytes (all or some of them None)
            - instance of another ISIMessage class (content is copied)

    See end of file for more usage examples.

    FIXME: Python 2.2 has a new property-model that could be used here
           to speed up lookups.
    """

    basic_fields = ['media', 'recv_dev', 'send_dev', 'resource', 'length',
                       'recv_obj', 'send_obj', 'utid', 'msg_id']

    all_fields = basic_fields + ['msg_data']

    def __init__(self, **isi_message_fields):

        ISITestResultElement.__init__(self)

        # Unpack isi_message-field if available. This must be done before
        # mapping other fields - they may want to override something.
        isi_message = isi_message_fields.get('isi_message', Undefined)
        if isi_message is not Undefined:
            self.isi_message = isi_message # calls _check_set_isi_message()
            del isi_message_fields['isi_message']

        # Unpack msg_data-field if available. This must be done before mapping
        # other fields.
        msg_data = isi_message_fields.get('msg_data', Undefined)
        if msg_data is not Undefined:
            self.msg_data = msg_data
            del isi_message_fields['msg_data']

        # Unpack other message fields.
        for field_name, value in isi_message_fields.items():
            setattr(self, field_name, value) # _check_set_<field_name>

        # And finally, make sure that all basic fields get defined
        for field_name in ISIMessage.basic_fields:
            if not hasattr(self, field_name):
                setattr(self, field_name, None)

        # FIXME: What if the msg_data is not defined?
        #   -> msg_data must return [] ?

    def initDefaults(self, **isi_message_fields):
        """Init fields' values if they are not defined or are None.

        This makes sure all given message fields exist and have a value.
        """
        isi_message = isi_message_fields.get('isi_message', None)
        if isi_message is not None:
            self.isi_message = isi_message
            del isi_message_fields['isi_message']

        for field_name, value in isi_message_fields.items():
            if getattr(self, field_name, None) is None:
                setattr(self, field_name, value)

    # ==================================================== assertion functions

    def assertFields(self, **isi_message_fields):
        """Assert message fields for expected values.

        Raises single ISIMessageException if errors were found.
        """
        errors = [error for error in self.match(**isi_message_fields) \
                  if error[2] is not None] # Filter passed tests
        if errors:
            raise ISIMessageException(self, errors)

    def assertDefined(self, names_of_isi_message_fields):
        """Assert given message fields are not None.

        Raises single ISIMessageException if errors were found.
        """

        if type(names_of_isi_message_fields) == type(''):
            names_of_isi_message_fields = [names_of_isi_message_fields]

        params = {}
        for field_name in names_of_isi_message_fields:
            params[field_name] = '%s is not None' % field_name

        self.assertFields(**params)

    def fail(self, error_msg):
        raise ISIMessageException(self, error_msg)

    def failUnless(self, expression, error_msg):
        if not expression:
            raise ISIMessageException(self, error_msg)

    def failField(self, field_name, error_msg):
        raise ISIMessageException(self, [(field_name, None, error_msg)])

    def failFieldUnless(self, field_name, expression, error_msg=None):
        if not expression:
            raise ISIMessageException(self, [(field_name, None, error_msg)])

    # ========================================== overridden internal functions

    def __getattr__(self, field_name):

        if field_name[0] == '_':
            raise AttributeError(field_name)

        self.failFieldUnless(field_name, field_name.islower(),
                             'Invalid name for an ISI message field')

        # Check for a special get function for this field
        get_function = getattr(self, '_get_%s' % field_name, None)
        if get_function:
            return get_function()

        # Get function was not found: check if a string version is needed
        if len(field_name) >= 4 and field_name[-4:] == '_str':
            return str(getattr(self, field_name[:-4]))

        # Plain value is needed. This raises an AttributeError if _<field_name>
        # is not defined in the instance.

        try:
            return getattr(self, '_'+field_name)
        except AttributeError, e:
            raise AttributeError(field_name)

    def __setattr__(self, field_name, value):

        self.failFieldUnless(field_name, field_name.islower(),
                             'Invalid name for an ISI message field')

        if field_name[0] == '_':
            self.__dict__[field_name] = value
            return

        check_set_function = getattr(self, '_check_set_%s' % field_name, None)

        if check_set_function:
            value = check_set_function(value)

        # Field values are stored in 'self._field_name' -attributes
        self.__dict__['_'+field_name] = value

    def __getitem__(self, index):
        return self.isi_message[index]

    def __setitem__(self, index, value):
        isi_message = self.isi_message
        isi_message[index] = value
        self.isi_message = isi_message

    def __str__(self):
        """Return a string version of the message."""
        return '<%s:\n  %s>' % (self.__class__, \
               '\n  '.join(['%-14s %s' % (str(field), str(getattr(self, \
               field+'_str'))) for field in ISIMessage.all_fields]))

    def toxml(self):
        """Return an xml version of the message.

        Generates a <message> tag. Basic fields are put into it's attributes,
        msg_data goes into the content part. Fields not having a value (None)
        are skipped.
        """
        attributes = ' '.join(['%s="%s"' % (f, getattr(self, f)) \
            for f in ISIMessage.basic_fields if getattr(self, f) is not None])

        content = self.msg_data is not None and self.msg_data_str or ''

        if content:
            return '<message class="%s" %s>%s</message>' % \
                   (self.__class__, attributes, content)
        else:
            return '<message class="%s" %s/>' % \
                   (self.__class__, attributes)


    def __eq__(self, isi_message_obj):
        """Compare object's non-None fields to destination object's fields."""

        if isinstance(isi_message_obj, self.__class__):
            source = self.isi_message
            destination = isi_message_obj.isi_message
            if len(source) != len(destination):
                return 0
            for i in xrange(0, len(source)):
                if source[i] is not None:
                    if source[i] != destination[i]:
                        return 0
            return 1
        return 0

    def __len__(self):
        """Get length of the whole message.

        Note: this is different value than getting self.length.
        """
        return len(self.isi_message)

    def getattrstr(self, field_name):
        """Return string version of field name's value."""
        return getattr(self, field_name+'_str')

    # ================================================================== match
    def match(self, **expected_fields):
        """Match message fields to given expected message fields.

        Parameters
            {field_name1:'expected_value1', field_name2:'expected_value2, .. }

            Expected value can be any value (simple match) or a complex
            function description such as 'resource in [10, 20, 30]'.
            In all cases, the match function constructs a lambda function
            which then evaluates the field for the expected value.

            Due to nature of Python's dictionary, the fields are matched in
            random order.

        Returns
            list of tuples for each expected field:
                (field name, expected value, None or error message)

            'None' means that the match was a success, thus no error msg.

        See end of file for usage examples.
        """

        match_results = []

        for field_name, expected_value in expected_fields.items():

            # Prepare expected_value to a lambda construction
            if type(expected_value) != type(''):
                expected_value = "%s==%s" % (field_name, expected_value)
            elif expected_value.find(field_name) == -1:
                expected_value = "%s==str('''%s''')" % (field_name, expected_value)

            # Repeat until all argument names are resolved and validated.
            # Usually requires only one loop.
            arguments = [field_name]
            while 1:
                try:
                    # Construct validator function
                    validator = eval('lambda %s:%s' % (','.join(arguments),\
                                                       expected_value))

                    argument_values = [getattr(self, name) for name in arguments]

                    result = validator(*argument_values)

                    if result == 0:
                        value = getattr(self, field_name)
                        value_str = self.getattrstr(field_name)
                        if value_str != str(value):
                            result = 'Unexpected value:%s (%s)' % \
                                     (value_str, value)
                        else:
                            result = 'Unexpected value:%s' % value
                    elif result == 1:
                        result = None # Match!
                    else:
                        result='Match function must return 0 or 1: "%s"' \
                            % str(result)
                    break

                except NameError, e:
                    missing_field_name = str(e).split("'")[1]
                    if missing_field_name not in arguments:
                        arguments.append(missing_field_name)
                    else:
                        result = 'Unknown error: "%s"' % str(e)
                        break

                except AttributeError, e:
                    result = 'Unknown field name: "%s"' % str(e)
                    break

                except SyntaxError, e:
                    result = 'Syntax error in match function: "%s"' % str(e)
                    break

                except Exception, e:
                    result = 'Error in match function: "%s"' % str(e)
                    break

            match_results.append((field_name, expected_value, result))

        return match_results

    # ==================================== special get and check_set functions

    def _check_set_isi_message(self, isi_message):
        """Unpack given message data to all message fields.

        Note that any field in the isi_message is allowed to be None.

        All exceptions are allowed to flow through.
        """

        self.failFieldUnless('isi_message', isi_message is not None,\
                             'Empty ISI message data')

        if type(isi_message) == type(''):
            isi_message = map(ord, isi_message)
        elif isinstance(isi_message, ISIMessage):
            isi_message = copy.copy(isi_message.isi_message)

        # Assert length if its defined
        length, = xunpack('>H', isi_message[4:6])
        if length is not None:
            self.failFieldUnless('length', length == (len(isi_message)-6),
                'Message data does not match with the length:%s' % str(length))

        # Unpack basic fields (calls __setattr__ for each field).
        # Fields are named though they are not used for anything yet.
        self.media, self.recv_dev, self.send_dev, \
        self.resource, self.length, \
        self.recv_obj, self.send_obj, \
        self.utid, self.msg_id, self.msg_data = \
            xunpack('''>
                        B:media B:recv_dev B:send_dev B:resource H:length
                        B:recv_obj B:send_obj B:utid B:msg_id *[:msg_data
                    ''',
                    isi_message)

    def _get_isi_message(self):
        """Get the whole message as a list of bytes.

        Missing fields are set to None.
        """
        # Media
        data = [self.media]

        # Receiver device
        if self.recv_dev is not None:
            if self.recv_obj is not None:
                data.append(self.recv_dev + ((self.recv_obj & 0x300) >> 8))
            else:
                data.append(self.recv_dev)
        else:
            data.append(None)

        # Sender device
        if self.send_dev is not None:
            if self.send_obj is not None:
                data.append(self.send_dev + ((self.send_obj & 0x300) >> 8))
            else:
                data.append(self.send_dev)
        else:
            data.append(None)

        # Resource
        data.append(self.resource)

        # Length
        if self.length is not None:
            data.append((self.length & 0xFF00) >> 8)
            data.append(self.length & 0x00FF)
        else:
            data.extend([None, None])

        # Receiver object
        if self.recv_obj is not None:
            data.append(self.recv_obj & 0xFF)
        else:
            data.append(None)

        # Sender object
        if self.send_obj is not None:
            data.append(self.send_obj & 0xFF)
        else:
            data.append(None)

        data.extend([self.utid, self.msg_id])

        msg_data = self.msg_data
        if msg_data is not None:
            data.extend(msg_data)

        return data

    def _get_resource_str(self):
        return self.resource is not None and '0x%02X' % (self.resource) or None

    def _get_length(self):
        """Get value for the length field.

            If length is None and msg_data is defined, returns calculated size.
        """
        if self._length is None:
            msg_data=self.msg_data
            if msg_data is not None:
                return len(msg_data)+4
        return self._length

    def _get_length_str(self):
        return self.length is not None and '0x%04X' % self.length or str(None)

    def _get_msg_id_str(self):
        return self.msg_id is not None and '0x%02X' % self.msg_id or str(None)

    def _check_set_msg_data(self, new_msg_data):
        """Set value of msg_data field. Must be overridden by a subclass!

        msg_data value is always stored as a list.
        """
        if type(new_msg_data) == type(''):
            new_msg_data = map(ord, new_msg_data)

        # Sub classes should check here that the message complies with it's ISI
        # specification!

        return new_msg_data

    def _get_msg_data(self):
        """Get value of msg_data field. Must be overridden by a subclass!"""
        return getattr(self, '_msg_data', None)

    def _get_msg_data_str(self):
        """Get msg_data as a string. Should be overridden by a subclass."""
        msg_data = self.msg_data
        return str(msg_data)

# ============================================================================
#   3.n     Self test
# ----------------------------------------------------------------------------
if __name__ == '__main__':

    # ========================================= self test for ISIMessage class
    class ISIMessageTest(unittest.TestCase):

        def testEmptyMessage(self):
            msg = ISIMessage()
            assert msg.media == None
            assert msg.recv_dev == None
            assert msg.send_dev == None
            assert msg.resource == None
            assert msg.length == None
            assert msg.recv_obj == None
            assert msg.send_obj == None
            assert msg.utid == None
            assert msg.msg_id == None
            assert msg.msg_data == None
            assert msg.isi_message == 10*[None] # msg_data is not counted here!

            msg.msg_data = [10, 20, None, 30, 40]
            assert msg.msg_data == [10, 20, None, 30, 40], msg.msg_data

        def testSettingFieldValues(self):
            msg = ISIMessage()

            # Test field initialization after init
            msg.msg_id = 0x12
            assert msg.msg_id == 0x12
            assert msg.isi_message[9] == 0x12

            msg.msg_id = 0xEE
            assert msg.msg_id == 0xEE
            assert msg.isi_message[9] == 0xEE
            msg.msg_id = 0x12

            # Test field initialization on init
            msg2 = ISIMessage(msg_id=0x12)
            assert msg.msg_id == msg2.msg_id
            assert msg2.isi_message[9] == 0x12

            # Test more than one field in init
            msg = ISIMessage(resource=0x10, msg_id=0x12)
            assert msg.resource == 0x10
            assert msg.msg_id == msg2.msg_id
            assert msg.isi_message[9] == 0x12
            assert msg.isi_message[3] == 0x10

        def testSettingFieldsViaISIMessage(self):

            # Test giving another instance of ISIMessage
            msg = ISIMessage(isi_message=[30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1, 0])
            msg2 = ISIMessage(isi_message=msg)

            assert msg == msg2, 'Messages do not match!\n%s\n\n%s' % (msg, msg2)

             # Test giving incomplete instance of ISIMessage - should NOT fail
            msg = ISIMessage(resource=10, msg_data = [10, 20, 30, 40])
            msg2 = ISIMessage(isi_message=msg)

            assert msg.msg_id == msg2.msg_id == None

        def testLengthCheck(self):

            msg = ISIMessage(isi_message=[30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1, 0])
            msg = ISIMessage(length=100) # no msg_data -> should be ok
            msg = ISIMessage(msg_data=[10]) # no length -> should be ok

            msg = ISIMessage(length=10, msg_data=[10, 20, 30, 40, 50, 60]) # ok

            try:
                # Length field does not match with the message - should fail
                msg = ISIMessage(isi_message=[30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1])
            except ISIMessageException, e:
                pass
            else:
                raise Exception('Should have failed')

            # tests _check_set_isi_message..
            msg = ISIMessage()
            try:
                # Length field does not match with the message - should fail
                msg.isi_message = [30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1]
            except ISIMessageException, e:
                pass
            else:
                raise Exception('Should have failed')

            msg = ISIMessage()
            msg.isi_message = [30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1, 0] # ok
            msg.isi_message = [30, 16, 0, 25, 0, 4, 1, 40, 1, 100] # ok

            # Too short message: no msg data
            msg = ISIMessage()
            try:
                msg.isi_message = [30, 16, 0, 25, 0, 6, 1, 40, None]
            except ISIMessageException, e:
                pass
            else:
                raise 'Should have failed!'

            # Too short message: Nones are used for missing fields
            msg.isi_message = [30, 16, 0, 25, 0, 6, 1, 40, None, None, None, None]
            assert msg.utid == None, msg.utid
            assert msg.msg_id == None, msg.msg_id
            assert msg.msg_data == [None, None], msg.msg_data
            assert msg.isi_message == [30, 16, 0, 25, 0, 6, 1, 40, None, None, None, None]

            # No msg_data
            msg = ISIMessage(isi_message=[30,16,0,63,0,4,1,78,1,43])
            msg.failUnless(len(msg.isi_message) == 10, str(msg.isi_message))

        def testFieldOverrides(self):
            pass

        def testSettingMsgData(self):

            msg = ISIMessage(msg_data = [10, 20, 30, 40])
            assert type(msg.msg_data) == type([]), type(msg.msg_data)
            assert msg.msg_data == [10, 20, 30, 40]
            assert msg.msg_data_str == '[10, 20, 30, 40]'

            # .. msg_data is given as a string
            msg = ISIMessage()
            msg.msg_data = ''.join(map(chr, [10, 20, 30, 40, 50]))
            assert msg.msg_data == [10, 20, 30, 40, 50]
            assert msg.msg_data_str == '[10, 20, 30, 40, 50]'

            # set to None
            msg.msg_data = None
            assert msg.msg_data == None
            assert msg.msg_data_str == 'None'

            # If set to None, the length field should be automatically udpated
            assert msg.length == None
            msg.msg_data = [10, 20, 30, 40]
            assert msg.length == 4 + 4

            msg = ISIMessage(length=10)
            assert msg.length == 10
            msg.msg_data = 123*[42, 13]
            assert len(msg.msg_data) == 246, len(msg.msg_data)

            try:
                assert msg.length == 4 + 246, msg.length
            except AssertionError, e:
                pass
            else:
                raise Exception('Length field was changed!')

        def testObjectIds(self):
            msg = ISIMessage()
            msg.recv_obj = 0x00
            assert msg.recv_obj == 0x00, msg.recv_obj
            assert msg.recv_dev == None, msg.recv_dev

            msg.recv_obj = 0x102 # -> will be splitted to 0x100 and 0x02
            assert msg.recv_obj == 0x102, msg.recv_obj
            assert msg.recv_dev == None, 'recv_dev should NOT be defined:%s' \
                                         % msg.recv_dev
            msg.recv_dev = 0x10
            assert msg.recv_dev == 0x10, msg.recv_dev

            isi_msg = msg.isi_message
            assert isi_msg[1] == 0x11, isi_msg # 0x10 + (0x100 >> 3)
            assert isi_msg[6] == 0x02, isi_msg # 0x02 of 0x102

            msg.send_obj = 0x102 # -> will be splitted to 0x100 and 0x02
            assert msg.send_obj == 0x102, msg.send_obj
            assert msg.send_dev == None, msg.send_dev
            msg.send_dev = 0x10
            assert msg.send_dev == 0x10, msg.send_dev
            isi_msg = msg.isi_message
            assert isi_msg[1] == 0x11, isi_msg # 0x10 + (0x100 >> 3)
            assert isi_msg[6] == 0x02, isi_msg # 0x02 of 0x102

        def testMatch(self):

            msg = ISIMessage(resource=10, msg_id=20, \
                             msg_data=[10, 20, 30, 40], send_dev='huh\n')

            # Simple match: ok
            result=msg.match(resource=10)
            assert result[0][2] is None, result

            # Simple match: ok
            result=msg.match(msg_data=[10, 20, 30, 40])
            assert result[0][2] is None, result

            # Simple match: failed
            result=msg.match(resource=20)
            assert str(result[0][2]).find('Unexpected value') == 0, result

            # Simple string match: ok
            result=msg.match(send_dev='huh\n')
            assert result[0][2] is None, result

            # Simple string match: failed
            result=msg.match(msg_id='10')
            assert str(result[0][2]).find('Unexpected value:') == 0, result

            # Simple match: unknown field
            result=msg.match(blabla=100)
            assert str(result[0][2]).find('Unknown field name:') == 0, result

            # Simple match: match to None field
            result=msg.match(recv_dev=100)
            assert str(result[0][2]).find('Unexpected value:None') == 0, result

            # Complex match: ok
            result=msg.match(resource='10 <= resource < 100')
            assert result[0][2] is None, result

            # Complex match: syntax error
            result=msg.match(resource="10 < resource < 20!!!")
            assert str(result[0][2]).find('Syntax error in match function:') == 0, result

            # Complex match: unknown field
            result=msg.match(blabla='blabla in [10, 20]')
            assert str(result[0][2]).find('Unknown field name:') == 0, result

            # Complex match: comparing to self: ok
            result=msg.match(msg_id='msg_id in [msg_id, 55]')
            assert result[0][2] is None, result

            # Complex match: unknown field name #1
            result=msg.match(resource='resourcee in [10,20]')
            assert str(result[0][2]).find('Unknown field name') == 0, result

            # Complex match: error in match function #2
            result=msg.match(resource='resource+1')
            assert str(result[0][2]).find('Match function must return 0 or 1') == 0, result

            # Complex match: multiple attributes: ok
            result=msg.match(resource='resource != msg_id')
            assert result[0][2] is None, result

            # Complex match: multiple attributes: type error
            # (recv_dev is None)
            result=msg.match(resource='resource != (msg_id + recv_dev)')
            assert result[0][2].find('Error in match function') == 0, result

            # Complex match: multiple attributes: ok
            # (recv_dev is now defined)
            msg.recv_dev = 0x10
            result=msg.match(resource='resource != (msg_id + recv_dev)')
            assert result[0][2] is None, result

            # Complex match: unknown fields
            msg.resource = 1
            msg.recv_dev = 2
            result=msg.match(resource='resource < recv_dev2')
            assert result[0][2].find('Unknown field name') == 0, result
            result=msg.match(resource='resource < recv_dev')
            assert result[0][2] is None, result

        def testSubClassing(self):

            class MyTestStatusReq(ISIMessage):
                """Message parser for MYTEST_STATUS_REQ

                Field name:     Description (default):

                msg_id          Message id (123)
                foo             Foo's value (100)
                bar             Bar's value (None)

                Usually most of the fields' default value is None.
                """
                def __init__(self, **isi_message_fields):
                    ISIMessage.__init__(self, **isi_message_fields)
                    self.initDefaults(msg_id=123, foo=100)
                    self.assertFields(msg_id=123, foo='foo in [10, 100, 200]')

                def _get_msg_data(self):
                    return xpack('>BH', self.foo, self.bar)

                def _get_msg_data_str(self):
                    return 'foo:%s bar:%s' % (self.foo, self.bar)

                def _check_set_msg_data(self, new_msg_data):
                    self.foo, self.bar = xunpack('>BH', new_msg_data)
                    return new_msg_data

            class MyTestStatusResp(ISIMessage):
                """Message parser for MYTEST_STATUS_RESP

                Field name:     Description (value range, default):

                msg_id          Message id (124)
                result          Result of the status query (0-100, None)
                """
                def __init__(self, **isi_message_fields):
                    ISIMessage.__init__(self, **isi_message_fields)
                    self.initDefaults(msg_id=124)
                    self.assertFields(msg_id=124)

                    # If this instance has a value for result, it must ALWAYS
                    # be between 0..100.
                    if self.result is not None:
                        self.assertFields(result='0 < result < 100')

                def _get_msg_data(self):
                    return xpack('>B', self.result)

                def _get_msg_data_str(self):
                    return 'result:%s' % (self.result)

                def _check_set_msg_data(self, new_msg_data):
                    self.result, = xunpack('>B', new_msg_data)

                    # FIXME: Check that data complies with the specification..

                    return new_msg_data

            req = MyTestStatusReq(bar=16)

            # Test that MyTestStatusReq class works correctly:
            assert req.foo == 100, req.foo # <- default value
            assert req.bar == 16, req.bar # <- given value
            assert req.msg_id == 123, req.msg_id # <- default value
            assert req.msg_data == [100, 0, 16], req.msg_data
            assert req.msg_data_str == 'foo:100 bar:16', req.msg_data_str

            # Simulated response from a phone:
            # (msg_id=124, result=10)
            response_data = [None, None, None, None, 0, 5, None, None, None, 124, 10]

            # Give response to the class, notice how it automatically checks msg_id
            # and result fields
            resp = MyTestStatusResp(isi_message=response_data)

            # You can also assert any other field(s) by yourself:
            #resp.assertFields(msg_id=100, result='result in [15, 20]')

        def testToXml(self):

            # Empty message
            msg = ISIMessage()
            assert msg.toxml() == '<message class="__main__.ISIMessage" />', msg.toxml()

            # msg_data only (generates length field too)
            msg = ISIMessage(msg_data=[10, 20, 30])
            assert msg.toxml() == '<message class="__main__.ISIMessage" length="7">[10, 20, 30]</message>', msg.toxml()

            # msg_id field - no msg_data
            msg = ISIMessage(msg_id=10)
            assert msg.toxml() == '<message class="__main__.ISIMessage" msg_id="10"/>', msg.toxml()

            # msg_id field with msg_data
            msg = ISIMessage(msg_id=10, msg_data='Hello')
            assert msg.toxml() == '<message class="__main__.ISIMessage" length="9" msg_id="10">[72, 101, 108, 108, 111]</message>', msg.toxml()

            # full msg
            msg = ISIMessage(isi_message=[30, 16, 0, 25, 0, 6, 1, 40, 1, 2, 1, 0])
            assert msg.toxml() == '<message class="__main__.ISIMessage" media="30" recv_dev="16" send_dev="0" resource="25" length="6" recv_obj="1" send_obj="40" utid="1" msg_id="2">[1, 0]</message>', msg.toxml()

    # ================================ self test for ISIMessageException class
    class ISIMessageExceptionTest(unittest.TestCase):

        class Foobar:
            pass

        def testBasic(self):

            # Invalid isi message instance
            try:
                e = ISIMessageException(ISIMessageExceptionTest.Foobar(), \
                                        'Something went wrong')
            except AssertionError, e:
                pass
            else:
                raise Exception, 'Should have failed!'

            msg = ISIMessage(resource=1, msg_id=20, msg_data=[10, 20, 30])

            # Test __len__
            e = ISIMessageException(msg, msg.match(msg_id=10, resource=None))
            assert len(e) == 2, len(e)

            # Test printing (all fields are defined)
            assert str(e) == \
                'Unexpected value:0x14 (20) in the msg_id field. Expected:msg_id==10\n' + \
                'Unexpected value:0x01 (1) in the resource field. Expected:resource==None', e

            # Test printing (only field and error msg are defined)
            try:
                msg.failField('Test', 'Some error')
            except ISIMessageException, e:
                assert str(e) == 'Some error: Test', str(e)
            else:
                raise 'Should have failed!'

            # Test printing (only error msg is defined)
            e = ISIMessageException(msg, 'Hello')
            f = ISIMessageException(msg, [(None, None, 'Hello')])
            assert str(e) == str(f), '%s != %s' % (str(e), str(f))
            assert str(e) == 'Hello', str(e)

            # assertFields test: ok
            msg.assertFields(resource='resource in [10, 20, 30, 1]')

            # assertFields test: one fail, one ok
            try:
                msg.assertFields(resource=10, msg_id=20)
            except ISIMessageException, e:
                assert len(e) == 1, len(e)
                assert e.isi_message == msg
            else:
                raise 'Should have failed!'

            # assertFields test: fail (multiple fails)
            try:
                msg.assertFields(resource=100, msg_id='msg_id in [42, 13]')
            except ISIMessageException, e:
                assert len(e) == 2, len(e)
                assert e.isi_message == msg
            else:
                raise 'Should have failed!'

            # failFieldUnless test: ok
            msg.failFieldUnless('recv_obj', 1==1, 'Should pass')

            # failFieldUnless test: fail
            try:
                msg.failFieldUnless('recv_obj', 1==2, 'Should fail')
            except ISIMessageException, e:
                assert len(e) == 1, len(e)
                assert str(e) == 'Should fail: recv_obj', str(e)
                assert e.isi_message == msg
            else:
                raise 'Should have failed!'

            # assertDefined test: ok
            msg = ISIMessage()
            msg.msg_id = 10
            msg.assertDefined(['msg_id'])

            # assertDefined test: fail
            try:
                msg.assertDefined(['resource', 'msg_id', 'length'])
            except ISIMessageException, e:
                assert len(e) == 2, e
                fields = [field_name for field_name, expected, err_msg in e.errors]
                fields.sort()
                assert fields == ['length', 'resource'], fields
            else:
                raise 'Should have failed!'

            msg.msg_id = 50
            msg.utid = 100
            msg.assertFields(msg_id='msg_id != utid')
            try:
                msg.assertFields(msg_id='msg_id*2 != utid', utid='utid==utid+1-1')
            except ISIMessageException, e:
                assert len(e) == 1, e
                assert e.errors[0][0] == 'msg_id', e
            else:
                raise 'Should have failed!'

        def testToXml(self):

            msg = ISIMessage(isi_message=[30, 16, 0, 25, 0, 6, 1, 40, 1, 100, 20, 30])
            msg.assertFields(resource=0x19, msg_id=0x64)

            # Exception without a field and expected-values:
            e = ISIMessageException(msg, 'Hello there')
            assert e.toxml() == \
                '<error><message_error>Hello there</message_error></error>', e

            # One error found (field, expected, msg)
            try:
                msg.assertFields(resource=123)
            except ISIMessageException, e:
                assert len(e) == 1, e

            # Two errors found (field, expected, msg)
            try:
                msg.assertFields(resource=200, msg_id='msg_id in [1, 2, 7]')
            except ISIMessageException, e:
                assert len(e) == 2, e
                assert e.toxml().replace(' ','') == \
                """
                <error>
                    <message_error field='msg_id' expected='msg_id in [1, 2, 7]'>
                        Unexpected value:0x64 (100)
                    </message_error>
                    <message_error field='resource' expected='resource==200'>
                        Unexpected value:0x19 (25)
                    </message_error>
                </error>
                """.replace(' ', '').replace('\n',''), e

            # One error found (field)
            e = ISIMessageException(msg, [('foo', None, 'Not correct')])
            assert e.toxml() == \
                "<error><message_error field='foo'>Not correct</message_error></error>", e


    print 'Executing self test suite with Python', sys.version
    unittest.main()
