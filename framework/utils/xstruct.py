# ============================================================================
#
#
#                           Extended Struct Module
#                           -----------------------
#                           Granite SW module - Python
#
#
# Copyright (c) Nokia. All rights reserved.
#
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
#       This module implements extended versions of struct-module's calcsize
#       pack and unpack functions. Functions' format string interfaces have some
#       additions to make them more compatible with None-values, list items and
#       unknown length lists and strings.
#
#   1.3 Notes
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
#       3.1 xcalcsize
#       3.2 xpack
#       3.3 xunpack
#       3.n Self test
# ----------------------------------------------------------------------------

# ============================================================================
#   3   MODULE CODE
# ----------------------------------------------------------------------------

# Python library module imports
from struct import pack, unpack, calcsize
import re, threading

# thread safe lock object for xpack and xunpack functions
xstructLock = threading.Lock()

# Local data structures

# FIXME: This doesn't support 'x' character!
format_findall = re.compile(
    '^[><=!@]|[cbBhHiIlLfd]|\*[[sp]|[0-9]+[[sp]|:\s*\w+').findall

# Self test setup
if __name__ == '__main__':
    import unittest


# ============================================================================
#   3.2     xcalcsize
# ----------------------------------------------------------------------------
def xcalcsize(format_string):
    """Get size of the format string in bytes.

    FIXME: Doesn't support named fields!
    """

    assert type(format_string) == type(''), \
        'Expected format string, got: %s' % type(format_string)

    format_string = format_string.replace('[', 's')

    if '*' not in format_string:
        return calcsize(format_string)

    assert 0, "Unknown repeat counter '*' found from the format string: %s" % \
              format_string

# ============================================================================
#   3.3     xpack
# ----------------------------------------------------------------------------
def xpack(format_string, *args):
    """Return a list containing the values packed according to the format.

       The supported format string is the same as struct's format except:

       a) Support for list format character '[':
            xpack('>7[', [10, 'A', 'Hep']) --> [10, 65, 72, 101, 112, 0, 0]
            (notice the zero fills to match len:7)

            xpack('>3[', [10, 'A', 'Hep']) --> [10, 65, 72]
            (notice the truncated output!)

       b) Support for unknown repeat count character '*':
            sub_block = [10, 20, 30]
            xpack('>H*[', len(sub_block), sub_block) --> [0, 3, 10, 20, 30]

            Works also with strings:
            xpack('*s', 'Hello!') --> [72, 101, 108, 108, 111, 33]

       c) Support for named fields with ':':

            ...

       Also, any value in arguments (also inside lists) is allowed to be None:
       xpack('>H5[B', None, [10, 20, None], 15)
        --> [None, None,         # H  (two bytes for word)
             10, 20, None, 0, 0, # 5[ (two zero fills to match len:5)
             15                  # B
            ]

        FIXME: Should '[' support Unicode strings? What about ucs2/utf-8 chars?
        FIXME: Should we have new format character for Unicode strings?
        FIXME: Should we have new format character for GSM strings?
        FIXME: Should we have new format character for bit fields?
    """
    with xstructLock:
        assert type(format_string) == type(''), \
            'Expected format string, got: %s' % type(format_string)

        formats = format_findall(format_string)
        assert formats, 'Invalid format string: %s' % format_string

        # Parse endianess
        if len(formats[0]) == 1 and formats[0] in '><=!@':
            endianess = formats[0]
            del formats[0]
        else:
            endianess = '='

        # Resolve field names: build list of tuples (format, field name)
        # Check that the are no more fields after unknown repeat counter.
        fields = []
        length = len(formats)
        i = 0
        while i < length:
            # Is there a name for i'th format?
            if (i+1 < length) and formats[i+1][0] == ':':
                fields.append((formats[i], formats[i+1][1:]))
                i += 1
            else:
                fields.append((formats[i], None))
            i += 1

            if fields[-1][0][0] == '*':
                assert i >= length, 'Format string continues after %s: %s' \
                                    % (fields[-1][0], format_string)

        assert len(fields) == len(args), \
            'Arguments: %s do not match with the format string: %s' % \
            (args, tuple([f[0] for f in fields]))

        # Pack each field separately. Handle special list format and unknown
        # repeat counter characters separately.
        data = []
        index = 0
        for format, field_name in fields:
            arg = args[index]
            if arg is not None:
                if format[-1] == '[':
                    assert type(arg) in (type([]), type(())), \
                           'Expected list, got: %s' % type(arg)

                    # Convert characters and strings into bytes.
                    list_data = []
                    for item in arg:
                        if type(item) == type(''):
                            list_data.extend(map(ord, item))
                        else:
                            list_data.append(item)

                    data_length = len(list_data)
                    if format[0] == '*':
                        format = '%s[' % data_length

                    format_length = int(format[:-1])

                    # Assure the actual data length matches with the format length
                    if data_length > format_length:
                        # Strip overflowing bytes
                        list_data = list_data[:format_length]
                    elif data_length < format_length:
                        # Append missing bytes
                        list_data.extend((format_length-data_length) * [0])

                    data.extend(list_data)
                else:
                    if format[0] == '*':
                        format = '%s%s' % (len(arg), format[1:])
                    data.extend(map(ord, pack('%s%s' % (endianess, format), arg)))
            else:
                data.extend(xcalcsize(format) * [None])
            index += 1

        return data

# ============================================================================
#   3.4     xunpack
# ----------------------------------------------------------------------------
def xunpack(format_string, data):
    """Return tuple of items of unpacked data according to the given format.

       The data is allowed to be a string, a tuple or a list. The supported
       format string is the same as struct's format except:

       a) Support for list format character '[':

            xunpack('5[', [66, 67, 68, 69, 70])
                --> ([66, 67, 68, 69, 70],)

            xunpack('5s', [66, 67, 68, 69, 70])
                --> ('BCDEF',)

       b) Support for unknown repeat counter '*':
            xunpack('>BH*[', [10, 20, 20, 30, 30, 30])
                --> (10, 5140, [30, 30, 30])

            xunpack('>*s', 10*[77])
                --> ('MMMMMMMMMM',)

          Unknown repeat counter must be the last format character.

       c) Support for named fields with ':':

            ...

       Also, if part of item's data is None, the whole item is set to None:
            xunpack('H', [10, 20])     --> (5130,)
            xunpack('H', [10, None])   --> (None,)
            xunpack('H', [None, None]) --> (None,)

        FIXME: Should the data parameter support characters and strings?
            (caveat: list format doesn't check for chars..)

        FIXME: Add support for '(' format character (returns tuple)
    """
    with xstructLock:
        assert type(format_string) == type(''), \
            'Expected format string, got: %s' % type(format_string)

        if type(data) == type(''):
            return apply(unpack, (format_string, data))

        if type(data) == type(()):
            data = list(data)

        formats = format_findall(format_string)
        assert formats, 'Invalid format string: %s' % format_string

        # Parse endianess
        if len(formats[0]) == 1 and formats[0] in '><=!@':
            endianess = formats[0]
            del formats[0]
        else:
            endianess = '='

        # Resolve field names: build list of tuples (format, field name)
        # Check that the are no more fields after unknown repeat counter.
        fields = []
        length = len(formats)
        i = 0
        while i < length:
            # Is there a name for i'th format?
            if (i+1 < length) and formats[i+1][0] == ':':
                fields.append((formats[i], formats[i+1][1:]))
                i += 1
            else:
                fields.append((formats[i], None))
            i += 1

            if fields[-1][0][0] == '*':
                assert i >= length, 'Format string continues after %s: %s' \
                                    % (fields[-1][0], format_string)

        # Check for totally empty data (None or empty list)
        if not data:
            return tuple(len(fields) * [None])

        # Unpack each field separately. Handle special list format and unknown
        # repeat counter characters separately.
        items = []
        index = 0
        for format, field_name in fields:

            if format[-1] == '[':
                if format[0] == '*':
                    format_length = len(data)-index # length == Rest of data
                else:
                    format_length = int(format[0:-1])

                if index >= len(data):
                    # Starting index was out of data range.
                    item = None
                else:
                    item = data[index:index+format_length]

                    # Append Nones if out of data
                    if (index+format_length) > len(data):
                        item.extend((index+format_length-len(data)) * [None])

                items.append(item)
            else:
                if format[0] == '*':
                    format = '%s%s' % (len(data)-index, format[-1])
                    format_length = int(format[0:-1])
                else:
                    format_length = calcsize(format)
                item_data = data[index:index+format_length]
                if not None in item_data:
                    try:
                        items.extend(unpack('%s%s' % (endianess, format),
                                       ''.join(map(chr, item_data))))
                    except:
                        items.append(None)
                else:
                    items.append(None)

            index += format_length

        return tuple(items)

# ============================================================================
#   3.n     Self test
# ----------------------------------------------------------------------------
if __name__ == '__main__':

    # ============================== self test for xunpack and xpack functions
    class XPackTest(unittest.TestCase):

        def testPack(self):

            # Not any 'None' fields: ok
            assert [10, 20] == xpack('>BB', 10, 20)
            assert [0, 10, 20] == xpack('>HB', 10, 20)
            assert [0, 10, 20] == xpack('>HB', 10, 20)
            assert [10, 0, 20] == xpack('<HB', 10, 20)
            assert [0, 0, 0, 10, 20] == xpack('>LB', 10, 20)

            assert xpack('10s', 'Hello') == [72, 101, 108, 108, 111, 0, 0, 0, 0, 0]
            assert xpack('>10s', 'Hello') == [72, 101, 108, 108, 111, 0, 0, 0, 0, 0]
            assert xpack('>H10s', 10, 'Hello') == [0, 10, 72, 101, 108, 108, 111, 0, 0, 0, 0, 0]

            # Invalid format string:
            try:
                xpack('TT', 10, 20)
            except:
                pass
            else:
                raise Exception, 'Should have failed!'

        def testPackNone(self):

            # One None-field
            data = xpack('B', None)
            assert data == [None], 'Data: "%s"' % data

            # Mixed data and None fields
            data = xpack('BHBHLB', 10, 20, 30, 40, None, 60)
            assert data == [10, 20, 0, 30, 40, 0, None, None, None, None, 60], data

            # All fields are None
            data = xpack('BHH', None, None, None)
            assert data == [None, None, None, None, None], data

            # None strings
            data = xpack('>LLH10sHB', 0x12345678, 0x87654321L, 0x2020, None, 100, 6)
            assert data == [18, 52, 86, 120, 135, 101, 67, 33, 32, 32,
                            None, None, None, None, None, None, None,
                            None, None, None, 0, 100, 6], data

            data = xpack('10s', None)
            assert data == 10*[None], data

        def testPackList(self):

            data = xpack('>BB5[B', 100, 200, [10, 20, 30, 40, 65], 123)
            assert data == [100, 200, 10, 20, 30, 40, 65, 123], data

            data = xpack('>5[', [10, 20, 'A', 40, '\0'])
            assert data == [10, 20, 65, 40, 0], data

            # Data is too short: missing fields are filled with zeroes
            data = xpack('>5[', [10, 20, 30, 40])
            assert data == [10, 20, 30, 40, 0], data

            # Data is too long: extra data is stripped out
            data = xpack('>5[', [10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
            assert data == [10, 20, 30, 40, 50], data

            # Use the new '*' repeat counter:
            data = xpack('>*s', 'Hello there')
            assert data == [72, 101, 108, 108, 111, 32, 116, 104, 101, 114, 101], data

            sub_block = [20, 30, 40]
            data = xpack('>B*[', len(sub_block), sub_block)
            assert data == [3, 20, 30, 40], data

            # Test list having strings (unknown repeat):
            data = xpack('>H*[', 1234, ['a', 'b', 'c', 'eeeee'])
            assert data == [4, 210, # 1234
                            97,     # 'a'
                            98,     # 'b'
                            99,     # 'c'
                            101, 101, 101, 101, 101 # 'eeeee'
                            ], data

            # Test list having strings (repeat==5):
            data = xpack('>H5[', 1234, ['a', 'b', 'c', 'eeeee'])
            assert data == [4, 210, 97, 98, 99, 101, 101], data

            # Test list with None values #1
            data = xpack('>H*[', 1234, ['a', 'b', None, 'eeeee'])
            assert data == [4, 210, 97, 98, None, 101, 101, 101, 101, 101], data

            # Test list with None values #2
            data = xpack('>H3[', 1234, ['a', 'b', None, 'eeeee'])
            assert data == [4, 210, 97, 98, None], data

            # Test list with None values #3
            data = xpack('>H4[', 1234, ['a', 'b', None, 'e'])
            assert data == [4, 210, 97, 98, None, 101], data

            # Empty list
            data = xpack('>*[', [])
            assert data == [], data # FIXME: Is this ok?

            # > 255 values in list: failed
            data = xpack('>*[', [10, 20, 100, 3000, 200])
            # FIXME: doesn't assert for 3000 !!

        def testPackWithNamedFields(self):

            data = xpack('>B:length H:height', 10, 20)
            assert data == [10, 0, 20], data

            # Missing field
            try:
                data = xpack('>BH:height L:foo', 10, 20)
            except AssertionError, e:
                pass
            else:
                raise Exception('Should have failed: %s' % str(data))

        def testUnpack(self):

            # Data is given as a string: ok
            items = xunpack('>BB', '\x0a\x14')
            assert (0x0a, 0x14) == items, items

            # Data is given in a tuple or a list: ok
            foo, bar = xunpack('>BH', (10, 0, 20))
            foo2, bar2 = xunpack('>HB', [0, 10, 20])
            assert (foo, bar) == (10, 20), '%s %s' % (foo, bar)
            assert (foo2, bar2) == (10,20), '%s %s' % (foo2, bar2)

            # String of length 1
            foo, bar, life = xunpack('>LH1s', [0,0,0,10, 0, 20, 65])
            assert (foo, bar, life) == (10, 20, 'A'), '%s %s %s' % \
                                                      (foo, bar, life)

            # Invalid parameters
            try:
                text = xunpack('B', 'Hello')
            except:
                pass
            else:
                raise Exception, 'Should have failed!'

            # Invalid format string
            try:
                xunpack('T', [10, 20, 30])
            except:
                pass
            else:
                raise Exception, 'Should have failed!'

            # Tuple data: '[' should return a list
            data = (10, 20, 30, 40, 50, 60)
            items = xunpack('>BH*[', data)
            assert items == (10, 5150, [40, 50, 60]), items

        def testUnpackNone(self):

            # One None item: ok
            foo, bar = xunpack('>BB', [10, None])
            assert (foo, bar) == (10, None), '%s %s' % (foo, bar)

            # Half of the word item has None value: ok
            foo, bar = xunpack('>HB', (10, None, 10))
            assert (foo, bar) == (None, 10), '%s %s' % (foo, bar)

            # String data is None: ok
            foo, bar, life = xunpack('>LH2s', [0,0,0,10, 0, 20, None, None])
            assert (foo, bar, life) == (10, 20, None), '%s %s %s' % \
                                                      (foo, bar, life)

            # Part of the 1st string data is None, the other string is ok:
            foo, bar = xunpack('5s4s', [65, 66, None, 67, None, 65, 66, 67, 68])
            assert (foo, bar) == (None, 'ABCD'), '%s %s' % (foo, bar)

            # All fields are None: ok
            items = xunpack('>LLLLLLLLHL', calcsize('>LLLLLLLLHL') * [None])
            assert tuple(10 * [None]) == items, items

        def testUnpackList(self):
            alist, = xunpack('>5[', [10, 20, 30, 40, 50])
            assert alist == [10, 20, 30, 40, 50], alist

            # Some None fields
            abyte, alist = xunpack('>B5[', [10, 10, 20, 30, None, 50])
            assert abyte == 10, abyte
            assert alist == [10, 20, 30, None, 50], alist

            # Some None fields, one list value is a character
            abyte, alist = xunpack('>B5[', [10, 10, 'T', 30, None, 50])
            assert abyte == 10, abyte
            assert alist == [10, 'T', 30, None, 50], alist # FIXME: OK??

        def testUnpackRepeatCounter(self):
            abyte, aword, alist = xunpack('>BH*[', [10, 20, 20, 30, 30, 30])
            assert abyte == 10, abyte
            assert aword == 5140, aword
            assert alist == [30, 30, 30]

            # Test unpacking *s #1: ok
            items = xunpack('>*s', [65, 65, 66, 66, 67, 67])
            assert items == ('AABBCC',), items

            # Test unpacking *s #2: no data for string (becomes empty string)
            items = xunpack('>H*s', [None, None])
            assert items == (None, ''), items

            # Test unpacking *s #3: multiple items, partly None: ok
            items = xunpack('>H*s', [None, 10, None, 'A'])
            assert items == (None, None), items

        def testInvalidUnpackList(self):

            # Missing two bytes: missing bytes are replaced with Nones
            alist, = xunpack('>5[', [10, 20, 30])
            assert alist == [10, 20, 30, None, None], str(alist)

            astring, = xunpack('>5s', [65, 65, 65, 65])
            assert astring == None, astring

            items = xunpack('>BBBBB', [])
            assert items == (None, None, None, None, None), items

            items = xunpack('>BBBBB', None)
            assert items == (None, None, None, None, None), items

            items = xunpack('>BBBB', [0, 1, 3])
            assert items == (0, 1, 3, None), items

            # Out of data: all missing fields are None
            items = xunpack('>HBH5s1[', [0, 1])
            assert items == (1, None, None, None, None), str(items)

            # No data after list
            alist, abyte = xunpack('>5[B', [10, 20, 30, 40, 50])
            assert alist == [10, 20, 30, 40, 50], alist
            assert abyte == None, abyte

            # Test for format character after *[: fail
            try:
                items = xunpack('>H*[B', [None, None , 10, 20, 30, 40])
            except AssertionError, e:
                pass
            else:
                raise Exception, 'Should have failed: %s' % str(items)

            # Test unpacking *s #4: multiple items: one item is a character
            items = xunpack('>H*s', [10, None, 65, 66, 'C', 68])
            #FIXME assert items == (None, 'ABCD'), items
            assert items == (None, None), items

            items = xunpack('>*s', [10, 'Jee'])
            #FIXME
            assert items == (None,), items

        def testEmptyDataUnpack(self):

            resp = xunpack('>BBBB', None)
            assert resp == (None, None, None, None), resp

            resp = xunpack('>LBH5s', [])
            assert resp == (None, None, None, None), resp

            resp = xunpack('LBH5s', [])
            assert resp == (None, None, None, None), resp

            resp = xunpack('=BLH5[', [])
            assert resp == (None, None, None, None), resp

        def testNamedFields(self):

            items = xunpack('>B:foo L:bar', [10, 0, 0, 0, 10])
            assert items == (10, 10), items

            # Out of data:
            items = xunpack('>B:foo L:bar', [10, 0, 0, 0])
            assert items == (10, None), items

            # Out of data:
            items = xunpack('>B:foo L', [10, 0, 0, 0])
            assert items == (10, None), items

        def testCalcsize(self):

            size = xcalcsize('>BHL5s')
            assert size == 12, size

            size = xcalcsize('>B5[')
            assert size == 6, size

            # Unknown repeat counter won't work with xcalcsize:
            try:
                size = xcalcsize('>BL*[')
            except AssertionError, e:
                pass
            else:
                raise Exception('Should have failed!: %s' % size)

    print 'Executing self test suite..'
    unittest.main()
