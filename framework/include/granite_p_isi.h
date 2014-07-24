/*
NOKIA                                                             CONFIDENTIAL
MP
SETS Oulu




                  Granite Server Private ISI Interface
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        -

project path:    -

name:            granite_p_isi.h

version:         001.008

type:            incl

instance:        -


ISI header file for GRANITE private interface (private interface

Current   ISI Version : 001.008
Supported ISI Versions: 001.000, 001.001, 001.002, 001.003, 001.004, 001.005, 
                        001.006, 001.007, 001.008

Generated with autogen version 11w13 on 27-Aug-2013 12:54:07
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 001.008                2013-08-27     Risto Pakanen
Reason      : ISI interface update
Reference   : -
Description : Added Message GRN_DISPLAY_UPDATE_NTF
              Updated GRN_DISPLAY_UPDATE_NTF message and added ntf_sending
              attribute

Version     : 001.007                2013-04-26     Vaino Holopainen
Reason      : ISI interface update
Reference   : -
Description : Removed ISM setting support

Version     : 001.006                2013-01-23     Vaino Holopainen
Reason      : ISI interface update
Reference   : -
Description : Removed ISM ucs2_string setting support

Version     : 001.005                2012-10-23     Joni Vanhamaki
Reason      : ISI interface update
Reference   : -
Description : Added Message GRN_PROVISIONING_DELETE_REQ
              Added Message GRN_PROVISIONING_DELETE_RESP
              Added Message GRN_PROVISIONING_READ_REQ
              Added Message GRN_PROVISIONING_READ_RESP
              Added Message GRN_PROVISIONING_SELECT_REQ
              Added Message GRN_PROVISIONING_SELECT_RESP
              Added Message GRN_PROVISIONING_WRITE_REQ
              Added Message GRN_PROVISIONING_WRITE_RESP
              Updated provisioning settings messages

Version     : 001.004                2012-09-4      Teemu Kokko
Reason      : ISI interface update
Reference   : -
Description : Added new tag and renamed attribute

Version     : 001.003                2012-06-6      Risto Pakanen
Reason      : ISI interface update
Reference   : -
Description : Added Message GRN_CTC_START_REQ
              Added Message GRN_CTC_START_RESP
              Added Message GRN_CTC_STOP_REQ
              Added Message GRN_CTC_STOP_RESP
              ISI messages added for CTC usage and Provisioning write & read

Version     : 001.002                2012-05-16     Teemu Kokko
Reason      : ISI interface update
Reference   : -
Description : Common-request and display-notify data structures added

Version     : 001.001                2012-04-17     Risto Pakanen
Reason      : ISI interface update
Reference   : -
Description : Data structures updated

Version     : 001.000                2012-02-13     Risto Pakanen
Reason      : Creation of Granite server
Reference   : -
Description : Granite server private interface is based on ART2 server's
              private interface

------------------------------------------------------------------------------
*/

#ifndef _GRANITE_P_ISI_H
#define _GRANITE_P_ISI_H

#define PN_PRIVATE_GRANITE               0xFF0D
#define GRANITE                          ((PN_PRIVATE_GRANITE << 8) | PN_PRIVATE)

#include "isi_conf.h"

#ifndef GRANITE_ISI_VERSION
#define GRANITE_ISI_VERSION
#define GRANITE_ISI_VERSION_Z   1
#define GRANITE_ISI_VERSION_Y   8
#endif

#define GRANITE_ISI_MIN_VERSION(z,y) \
 ((GRANITE_ISI_VERSION_Z == (z) && GRANITE_ISI_VERSION_Y >= (y)) || \
  (GRANITE_ISI_VERSION_Z > (z)))

#if !GRANITE_ISI_MIN_VERSION(1,0)
#error The specified interface version is not supported by this header file
#elif GRANITE_ISI_MIN_VERSION(1,9)
#error The specified interface version is not supported by this header file
#endif


/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */

/* constant for variable-length definitions */
#define GRANITE_ANY_SIZE                         1
#define MAX_PROVISIONG_DATA                      0x7FFB

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_SERVER_STATE                                        */
/* ----------------------------------------------------------------------- */
typedef uint8 tGRN_server_state;

#define GRN_SERVER_STATE_STARTING                0x00
#define GRN_SERVER_STATE_IDLE                    0x01
#define GRN_SERVER_STATE_PARSING                 0x02
#define GRN_SERVER_STATE_RUNNING                 0x03
#define GRN_SERVER_STATE_ABORTING                0x04
#define GRN_SERVER_STATE_SUSPENDED               0x05
#define GRN_SERVER_STATE_INACTIVE                0x07
#define GRN_SERVER_STATE_REPORTING               0x08
#define GRN_SERVER_STATE_CLEARING                0x09
#define GRN_SERVER_STATE_TERMINATING             0x0A
#define GRN_SERVER_STATE_CLEARING_TESTCASE       0x0B

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_OPTIONS                                             */
/* ----------------------------------------------------------------------- */
typedef uint8 tGRN_option;

#define GRN_OPTION_NONE                          0x00
#define GRN_OPTION_POLLED                        0x01
#define GRN_OPTION_FILE                          0x02
#define GRN_OPTION_END                           0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_NOTIFICATIONS                                       */
/* ----------------------------------------------------------------------- */
/* Future versions may add other notifications. Unidentified notifications
   may be ignored.
*/
typedef uint8 tGRN_notification;

/* Server is expecting continuation to a test request */
#define GRN_NTF_PARSE_CONTINUE                   0x02
#define GRN_NTF_PARSE_DONE                       0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_CAUSES                                              */
/* ----------------------------------------------------------------------- */
typedef uint8 tGRN_cause;

#define GRN_CAUSE_NONE                           0x00
#define GRN_CAUSE_INVALID_WBXML_DATA             0x01
#define GRN_CAUSE_MEMORY_FULL                    0x02
#define GRN_CAUSE_ERROR_TERMINATION              0x03
#define GRN_CAUSE_NOTEXPECTED_RESULT             0x04
#define GRN_CAUSE_STATE_UNKNOWN                  0x09
#define GRN_CAUSE_STATE_STARTING                 0x0B
#define GRN_CAUSE_STATE_IDLE                     0x11
#define GRN_CAUSE_STATE_PARSING                  0x06
#define GRN_CAUSE_STATE_RUNNING                  0x07
#define GRN_CAUSE_STATE_ABORTING                 0x08
#define GRN_CAUSE_STATE_SUSPENDED                0x15
#define GRN_CAUSE_STATE_INACTIVE                 0x17
#define GRN_CAUSE_STATE_REPORTING                0x18
#define GRN_CAUSE_STATE_CLEARING                 0x19
#define GRN_CAUSE_STATE_TERMINATING              0x1A
#define GRN_CAUSE_STATE_CLEARING_TESTCASE        0x1B

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_TEST_PARSE_ERRORS                                   */
/* ----------------------------------------------------------------------- */
typedef uint8 tGRN_error;

#define GRN_TEST_PARSE_NOERROR                   0x00
#define GRN_TEST_PARSE_MEMORY_ERROR              0x01
#define GRN_TEST_ILLEGAL_PUBLIC_ID               0x03
#define GRN_TEST_ILLEGAL_CHARSET                 0x04
#define GRN_TEST_STR_T_NOT_EMPTY                 0x05
#define GRN_TEST_ILLEGAL_MB_U_INT32              0x06
#define GRN_TEST_ILLEGAL_UTF8_STRING             0x07
#define GRN_TEST_UNEXPECTED_TAG                  0x08
#define GRN_TEST_UNEXPECTED_DATA_END             0x0D
#define GRN_TEST_UNEXPECTED_ELEMENT              0x0E

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_VERSIONS                                      */
/* ----------------------------------------------------------------------- */
/* The first byte of any WBXML data identifies WBXML version in use. */
#define GRN_WBXML_VERSION                        0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_PUBLIC_IDS                                    */
/* ----------------------------------------------------------------------- */
/* The second byte of any WBXML data is a publick ID that identifies encoding
   of tags. In case of GRANITE server's private interface this has little
   significance, for all parties know encoding conventions, and the WBXML
   data is not used elsewhere.
*/
#define GRN_WBXML_PUBLIC_ID                      0x20

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_CHARSETS                                      */
/* ----------------------------------------------------------------------- */
/* The third byte of any WBXML data identifies character encoding used in all
   texts.
*/
#define GRN_WBXML_CHARSET_UTF8                   0x6A

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_GLOBALS                                       */
/* ----------------------------------------------------------------------- */
/* Encoding of WBXML Global tokens as specified in the WBXML standard /7/.
   Tokens marked "Not used" are not used in messages to or from GRANITE
   server.
*/
#define GRN_WBXML_SWITCH_PAGE                    0x00  /* Not used */
#define GRN_WBXML_END                            0x01
#define GRN_WBXML_ENTITY                         0x02  /* Not used */
/* used for string values and text content */
#define GRN_WBXML_STR_I                          0x03
#define GRN_WBXML_LITERAL                        0x04  /* Not used */
#define GRN_WBXML_EXT_I_0                        0x40  /* Not used */
#define GRN_WBXML_EXT_I_1                        0x41  /* Not used */
#define GRN_WBXML_EXT_I_2                        0x42  /* Not used */
#define GRN_WBXML_PI                             0x43  /* Not used */
#define GRN_WBXML_LITERAL_C                      0x44  /* Not used */
/* used for integer values */
#define GRN_WBXML_EXT_T_0                        0x80
#define GRN_WBXML_EXT_T_1                        0x81  /* Not used */
#define GRN_WBXML_EXT_T_2                        0x82  /* Not used */
#define GRN_WBXML_STR_T                          0x83  /* Not used */
#define GRN_WBXML_LITERAL_A                      0x84  /* Not used */
#define GRN_WBXML_EXT_0                          0xC0  /* Not used */
#define GRN_WBXML_EXT_1                          0xC1  /* Not used */
#define GRN_WBXML_EXT_2                          0xC2  /* Not used */
/* used for bitmap images */
#define GRN_WBXML_OPAQUE                         0xC3
#define GRN_WBXML_LITERAL_AC                     0xC4  /* Not used */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: GRN_WBXML_TAG_BITS                                       */
/* ----------------------------------------------------------------------- */
/* Two bits in a tag byte are reserved for attribute and content indicators.
*/
/* Tag has attributes */
#define GRN_WBXML_A                              0x80  /* 1------- */
/* Tag has contents */
#define GRN_WBXML_C                              0x40  /* -1------ */
/* Mask for tag */
#define GRN_WBXML_TAG_MASK                       0x3F  /* --111111 */

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_TAGS                                          */
/* ----------------------------------------------------------------------- */
/* These encodings are used for XML tags in messages to and from GRANITE
   server. Literal tags are not used.
*/
#define GRN_WBXML_TAG_teststep                   0x05
#define GRN_WBXML_TAG_sx                         0x06
#define GRN_WBXML_TAG_delay                      0x07
#define GRN_WBXML_TAG_key_in                     0x08
#define GRN_WBXML_TAG_keypress                   0x09
#define GRN_WBXML_TAG_expect                     0x0B
#define GRN_WBXML_TAG_display                    0x0C
#define GRN_WBXML_TAG_bitmap                     0x0D
#define GRN_WBXML_TAG_text                       0x0E
#define GRN_WBXML_TAG_data                       0x0F
#define GRN_WBXML_TAG_capture                    0x10
#define GRN_WBXML_TAG_animation                  0x11
#define GRN_WBXML_TAG_config                     0x12
#define GRN_WBXML_TAG_block                      0x13
#define GRN_WBXML_TAG_touch                      0x14
#define GRN_WBXML_TAG_press                      0x15
#define GRN_WBXML_TAG_move                       0x16
#define GRN_WBXML_TAG_release                    0x17
#define GRN_WBXML_TAG_xml                        0x18
#define GRN_WBXML_TAG_java                       0x19

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_ATTR_LABELS                                   */
/* ----------------------------------------------------------------------- */
/* These encodings are used for XML attribute names in messages to and from
   GRANITE server. None of the codes encodes any part of the attribute value.
   Literal names are not used. The value that follows must be of the type
   indicated in Comment.
   The Comment indicates how attribute values are encoded. Comment "string"
   means that the attribute value is encoded as a string. Values of other
   attributes shall not be encoded as a string. Comment with alternatives
   means that the values is one of alternatives encoded with a single byte as
   shown in table GRN_WBXML_ATTR_VALUES. The value "yes" may be omitted. If
   the list of alternatives is surrounded  by braces, more than one
   alternative may be specified. Comment "integer" means that value is a
   number encoded with the GRN_WBXML_EXT_T_0 byte (defined in table
   GRN_WBXML_GLOBALS) followed by the value in mb_uint32 encoding. However,
   small values may (but need not) be encoded with single bytes as shown in
   table GRN_WBXML_ATTR_VALUES. The value zero can be omitted completely.
*/
#define GRN_WBXML_ATTR_wait                      0x05  /* integer */
#define GRN_WBXML_ATTR_key                       0x06  /* integer */
#define GRN_WBXML_ATTR_length                    0x07  /* integer */
#define GRN_WBXML_ATTR_repeat                    0x08  /* integer */
#define GRN_WBXML_ATTR_timeout                   0x09  /* integer */
#define GRN_WBXML_ATTR_font                      0x0A  /* integer */
#define GRN_WBXML_ATTR_color                     0x0B  /* integer */
#define GRN_WBXML_ATTR_x                         0x0C  /* integer */
#define GRN_WBXML_ATTR_y                         0x0D  /* integer */
#define GRN_WBXML_ATTR_width                     0x0E  /* integer */
#define GRN_WBXML_ATTR_height                    0x0F  /* integer */
#define GRN_WBXML_ATTR_mask                      0x10  /* integer */
#define GRN_WBXML_ATTR_highlighted               0x11  /* yes/no */
#define GRN_WBXML_ATTR_name                      0x12  /* string */
#define GRN_WBXML_ATTR_valid                     0x13  /* yes/no */
#define GRN_WBXML_ATTR_id                        0x14  /* integer */
/* integer with GRN_STATUS_BITS */
#define GRN_WBXML_ATTR_result                    0x15
#define GRN_WBXML_ATTR_format                    0x16  /* integer */
#define GRN_WBXML_ATTR_checksum                  0x17  /* integer */
#define GRN_WBXML_ATTR_animation_id              0x18  /* integer */
#define GRN_WBXML_ATTR_truncated                 0x19  /* yes/no */
/* {text/animation/bitmap/items/all} */
#define GRN_WBXML_ATTR_items                     0x1A
#define GRN_WBXML_ATTR_bitmap_capture            0x1B  /* yes/no */
#define GRN_WBXML_ATTR_max_isi_data_length       0x1C  /* integer */
#define GRN_WBXML_ATTR_keypress_length           0x1D  /* integer */
#define GRN_WBXML_ATTR_keypress_wait             0x1E  /* integer */
#define GRN_WBXML_ATTR_screen                    0x1F  /* integer */
#define GRN_WBXML_ATTR_dimmed                    0x20  /* yes/no */
#define GRN_WBXML_ATTR_wait_for_key_release      0x21  /* yes/no */
#define GRN_WBXML_ATTR_wildcard                  0x22  /* yes/no */
#define GRN_WBXML_ATTR_offset                    0x24  /* integer */
#define GRN_WBXML_ATTR_gap                       0x25  /* integer */
#define GRN_WBXML_ATTR_little_endian_cpu         0x30  /* yes/no */
#define GRN_WBXML_ATTR_training                  0x31  /* yes/no */
#define GRN_WBXML_ATTR_action                    0x32  /* hold/release */
/* integer (default: 800) */
#define GRN_WBXML_ATTR_long_press_length         0x33
/* integer (default: 500) */
#define GRN_WBXML_ATTR_repeat_length             0x34
/* integer (8+8+8 bit RGB) */
#define GRN_WBXML_ATTR_fore_color                0x35
/* integer (8+8+8 bit RGB) */
#define GRN_WBXML_ATTR_bg                        0x36
/* yes/no/all (default: no) */
#define GRN_WBXML_ATTR_background                0x37
/* yes/no (default: no) */
#define GRN_WBXML_ATTR_landscape                 0x38
/* integer (default may vary) */
#define GRN_WBXML_ATTR_font_type                 0x39
/* integer (default: 0) */
#define GRN_WBXML_ATTR_short_press_length        0x3A
/* integer (default: 0) */
#define GRN_WBXML_ATTR_keys_idle_length          0x3B
/* integer (default: 0) */
#define GRN_WBXML_ATTR_is_checksum               0x52
/* integer (default: 0) */
#define GRN_WBXML_ATTR_checksum_id               0x53
/* yes/no (default: no) */
#define GRN_WBXML_ATTR_ntf_sending               0x54
/* integer (default: 0) */
#define GRN_WBXML_ATTR_touch_id                  0x55

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_WBXML_ATTR_VALUES                                   */
/* ----------------------------------------------------------------------- */
/* These encodings are used for XML for attribute values. Encoding as a
   string is used only for attributes marked with "string" in the table
   GRN_WBXML_ATTR_LABELS. Integer values greater than 15 must (and all
   integer values may) be encoded with with the GRN_WBXML_EXT_T_0 byte
   (defined in table GRN_WBXML_GLOBALS) followed by the value in mb_uint32
   encoding.
   If attribute value is encoded using bytes of this table, it is encoded
   with single byte only, except that the value of items attribute in capture
   tag can be a sequence of bytes.
   If the value of attribute is "yes" or zero it can be omitted.
*/
#define GRN_WBXML_ATTR_VALUE_yes                 0x85
#define GRN_WBXML_ATTR_VALUE_no                  0x86
/* for items in capture tag */
#define GRN_WBXML_ATTR_VALUE_text                0x87
/* for items in capture tag */
#define GRN_WBXML_ATTR_VALUE_animation           0x88
/* for items in capture tag */
#define GRN_WBXML_ATTR_VALUE_bitmap              0x89
/* for items in capture tag */
#define GRN_WBXML_ATTR_VALUE_items               0x90
/* for items in capture tag */
#define GRN_WBXML_ATTR_VALUE_all                 0x91
/* for action in keypress */
#define GRN_WBXML_ATTR_VALUE_hold                0x92
/* for action in keypress */
#define GRN_WBXML_ATTR_VALUE_release             0x93
/* numeric value zero */
#define GRN_WBXML_ATTR_VALUE_0                   0xB0
/* numeric value one */
#define GRN_WBXML_ATTR_VALUE_1                   0xB1
/* numeric value two */
#define GRN_WBXML_ATTR_VALUE_2                   0xB2
/* numeric value three */
#define GRN_WBXML_ATTR_VALUE_3                   0xB3
/* numeric value four */
#define GRN_WBXML_ATTR_VALUE_4                   0xB4
/* numeric value five */
#define GRN_WBXML_ATTR_VALUE_5                   0xB5
/* numeric value six */
#define GRN_WBXML_ATTR_VALUE_6                   0xB6
/* numeric value seven */
#define GRN_WBXML_ATTR_VALUE_7                   0xB7
/* numeric value eight */
#define GRN_WBXML_ATTR_VALUE_8                   0xB8
/* numeric value nine */
#define GRN_WBXML_ATTR_VALUE_9                   0xB9
/* numeric value ten */
#define GRN_WBXML_ATTR_VALUE_10                  0xBA
/* numeric value eleven */
#define GRN_WBXML_ATTR_VALUE_11                  0xBB
/* numeric value twelve */
#define GRN_WBXML_ATTR_VALUE_12                  0xBC
/* numeric value thirteen */
#define GRN_WBXML_ATTR_VALUE_13                  0xBD
/* numeric value fourteen */
#define GRN_WBXML_ATTR_VALUE_14                  0xBE
/* numeric value fifteen */
#define GRN_WBXML_ATTR_VALUE_15                  0xBF

/* ----------------------------------------------------------------------- */
/* Bitmask Table: GRN_STATUS_BITS                                          */
/* ----------------------------------------------------------------------- */
/* Value of result attribute is an integer where each bit has independent
   meaning (what was wrong in the display). This table identifies the bit
   used for each meaning.
*/
typedef uint16 tGRN_status_bits;

#define GRN_STATUS_NONE                          0x0000  /* 0000000000000000 */
#define GRN_STATUS_data                          0x0001  /* ---------------1 */
#define GRN_STATUS_text                          GRN_STATUS_data
#define GRN_STATUS_animation_id                  GRN_STATUS_data
#define GRN_STATUS_x                             0x0002  /* --------------1- */
#define GRN_STATUS_y                             0x0004  /* -------------1-- */
#define GRN_STATUS_width                         0x0008  /* ------------1--- */
#define GRN_STATUS_height                        0x0010  /* -----------1---- */
#define GRN_STATUS_highlighted                   0x0020  /* ----------1----- */
#define GRN_STATUS_font                          0x0040  /* ---------1------ */
#define GRN_STATUS_color                         0x0080  /* --------1------- */
#define GRN_STATUS_truncated                     0x0100  /* -------1-------- */
#define GRN_STATUS_screen                        0x0200  /* ------1--------- */
#define GRN_STATUS_dimmed                        0x0400  /* -----1---------- */
#define GRN_STATUS_background                    0x0800  /* ----1----------- */
#define GRN_STATUS_is_checksum                   0x1000  /* ---1------------ */
#define GRN_STATUS_checksum_id                   0x2000  /* --1------------- */

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_PROVISIONING_DATA_TYPES                             */
/* ----------------------------------------------------------------------- */
/* Provisioning data type one of these: JSON,XML,WBXML */
#define GRN_PROVISIONING_JSON                    0x00  /* JSON [Default] */
#define GRN_PROVISIONING_XML                     0x01  /* XML */
#define GRN_PROVISIONING_WBXML                   0x02  /* WBXML */

/* ----------------------------------------------------------------------- */
/* Constant Table: GRN_PROVISIONING_RESPONSE                               */
/* ----------------------------------------------------------------------- */
/* Provisioning responses */
#define GRN_PROVISIONING_OK                      0x00  /* Success */
#define GRN_PROVISIONING_FAIL                    0x01  /* Failure */
#define GRN_PROVISIONING_NOT_SUPPORTED           0x02  /* Not supported */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define GRN_STATUS_REQ                           0x00
#define GRN_STATUS_RESP                          0x01
#define GRN_TEST_REQ                             0x02
#define GRN_TEST_RESP                            0x03
#define GRN_TEST_NTF                             0x04
#define GRN_ABORT_REQ                            0x05
#define GRN_ABORT_RESP                           0x06
#define GRN_DISPLAY_UPDATE_NTF                   0x09
#define GRN_CTC_START_REQ                        0x0A
#define GRN_CTC_START_RESP                       0x0B
#define GRN_CTC_STOP_REQ                         0x0C
#define GRN_CTC_STOP_RESP                        0x0D
#define GRN_RESULT_REQ                           0x0F
#define GRN_RESULT_RESP                          0x10
#define GRN_TERM_REQ                             0x11
#define GRN_TERM_RESP                            0x12
#define GRN_CLEAR_REQ                            0x14
#define GRN_CLEAR_RESP                           0x16
#define GRN_CLEAR_TESTCASE_REQ                   0x17
#define GRN_CLEAR_TESTCASE_RESP                  0x19
#define GRN_RESET_PHONE_REQ                      0x1E
#define GRN_PROVISIONING_WRITE_REQ               0x1F
#define GRN_PROVISIONING_WRITE_RESP              0x20
#define GRN_PROVISIONING_READ_REQ                0x21
#define GRN_PROVISIONING_READ_RESP               0x22
#define GRN_PROVISIONING_SELECT_REQ              0x23
#define GRN_PROVISIONING_SELECT_RESP             0x24
#define GRN_PROVISIONING_DELETE_REQ              0x25
#define GRN_PROVISIONING_DELETE_RESP             0x26

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define GRN_NO_INFO                              0x00
#define GRN_PARSE_ERROR_INFO                     0x01
#define GRN_WBXML_REQ_INFO                       0x02
#define GRN_WBXML_RESP_INFO                      0x04
#define GRN_INDEX_INFO                           0x06
#define GRN_SERVER_VERSION_INFO                  0x07
#define GRN_SERVER_STATE_INFO                    0x08
#define GRN_PROVISIONG_DATA                      0x0D

/* ----------------------------------------------------------------------- */
/* Subblock: GRN_NO_INFO                                                   */
/* ----------------------------------------------------------------------- */
/* Zero bytes can be used between subblocks as fillers for proper alignment
   of the next subblock. They are not included in the number of subblocks
   shown in the Blocks field.
*/

typedef struct
    {
    uint8   ID;
    } tGRN_no_info;

#define SIZE_tGRN_no_info   sizeof(tGRN_no_info)


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_PARSE_ERROR_INFO                                          */
/* ----------------------------------------------------------------------- */
/* This subblock contains details of WBXML syntax error (in test step). */

typedef struct
    {
    uint8   ID;
    uint8   fill1;
    uint16  Length;
    /* The number of WBXML bytes before the erroneous ones, counted from the
       first WBXML byte (even in case the WBXML was split to several
       messages).
    */
    uint32  Index;
    /* Values from the constant table GRN_TEST_PARSE_ERRORS */
    tGRN_error Code;
    uint8   BadByte;
    uint8   fill2[2];
    } tGRN_parse_error_info;

#define SIZE_tGRN_parse_error_info   sizeof(tGRN_parse_error_info)


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_WBXML_REQ_INFO                                            */
/* ----------------------------------------------------------------------- */
/* The length of this subblock can be anything (whithin limits). Therefore
   this subblock should be the last, in order to avoid bad alignment in next
   subblocks.
   Test step is encoded in WBXML. If a test step is too long for a message,
   the WBXML encoded test step may be split at any point and parts be sent in
   separate messages.
   There are various constrains on the WBXML encoding. The global tokens have
   their normal encodings that is shown in the table GRN_WBXML_GLOBALS, but
   most of them (marked "Not used") shall not be used. The WBXML header bytes
   must have values from tables GRN_WBXML_VERSIONS, GRN_WBXML_PUBLIC_IDS, and
   GRN_WBXML_CHARSETS. The string table shall not be used (so the length of
   the string table is zero, and shall be encoded as a single zero byte. All
   XML tags shall be encoded by codes shown in the table GRN_WBXML_TAGS. Tags
   not shown in the table shall not be used. First byte of an attribute
   identifies the label of the attribute and shall be encoded with a single
   byte as shown in table GRN_WBXML_ATTR_LABELS. The first byte shall be
   followed by the encoded attribute value (of the appropriate type). The
   value shall not be encoded as a string unless it really is a string value.
   String values start with the GRN_WBXML_STR_I byte, followed by the string
   in UTF-8 encoding, and end with a zero byte. Integer values shall be
   encoded with GRN_WBXML_EXT_T_0 byte followed by mb_uint32 encoding of the
   value. However, for small values can be encoded with a single byte. Single
   byte encodings are shown in the table GRN_WBXML_ATTR_VALUES. These
   encodings shall be used for attributes with a limited set of valid values.
   More than one byte from the table shall not be used except for items in
   capture tag. Attribute value may be omitted if it is "yes" or zero. Tag
   content can be inner tags or text but not both. Text is encoded as a
   single string in the same way as a string attribute value.
*/

typedef struct
    {
    uint8   ID;
    /* A subset of values from the constant table GRN_OPTIONS */
    uint8   Option;
    uint16  Length;
    uint8   WbxmlData[GRANITE_ANY_SIZE];
    } tGRN_wbxml_req_info;

#define SIZE_tGRN_wbxml_req_info   (2*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_WBXML_RESP_INFO                                           */
/* ----------------------------------------------------------------------- */
/* The length of this subblock can be anything (whithin limits). Therefore
   this subblock should be the last, in order to avoid bad alignment in next
   subblocks.
   If there is no WBXML result or the index in request points beyond the end
   of the WBXML result, this subblock may be absent or the WBXML Data may
   have zero length.
   Test result encoded in WBXML or part of one. If the beginning of the WBXML
   encoded result is absent, this subblock is preceded by an GRN_INDEX_INFO
   subblock that indicates how much is missing from the beginning. Option
   indicates whether there are more WBXML bytes after the ones in this block:
   GRN_OPTION_END means that there are not.
   Only a subset of possible WBXML encodings areused. The global tokens have
   their normal encodings that is shown in the table GRN_WBXML_GLOBALS, but
   most of them (marked "Not used") shall not be used. The WBXML header has
   values from tables GRN_WBXML_VERSIONS, GRN_WBXML_PUBLIC_IDS, and
   GRN_WBXML_CHARSETS. The string table is not used (so the length of the
   string table is zero, and is encoded as a single zero byte. All XML tags
   are encoded by codes shown in the table GRN_WBXML_TAGS. Tags not shown in
   the table are not used. First byte of an attribute identifies the label of
   the attribute as shown in table GRN_WBXML_ATTR_LABELS. The first byte is
   followed by the encoded attribute value (of the appropriate type). The
   value is not encoded as a string unless it really is a string value.
   String values start with the GRN_WBXML_STR_I byte, followed by the string
   in UTF-8 encoding, and end with a zero byte. Integer values are encoded
   with GRN_WBXML_EXT_T_0 byte followed by mb_uint32 encoding of the value.
   However, for small values can be encoded with a single byte. Single byte
   encodings are shown in the table GRN_WBXML_ATTR_VALUES. These encodings
   are used for attributes with a limited set of valid values. More than one
   byte from the table is not used except. Attribute value may be omitted if
   it is "yes" or zero. Tag content can be inner tags only or text only or
   image data only. If the content is text it is encoded as a single string
   in the same way as a string attribute value. Image data (screen image or a
   part of one) is encoded as opaque data. The format of the image (including
   the order of the bytes) is as it is obtained in screen capture.
*/

typedef struct
    {
    uint8   ID;
    /* A subset of values from the constant table GRN_OPTIONS */
    uint8   Option;
    uint16  Length;
    uint8   WbxmlData[GRANITE_ANY_SIZE];
    } tGRN_wbxml_resp_info;

#define SIZE_tGRN_wbxml_resp_info   (2*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_INDEX_INFO                                                */
/* ----------------------------------------------------------------------- */
/* In GRN_RESULT_REQ message indicates how many bytes shall be omitted from
   the beginning of the requested result.
   In GRN_RESULT_RESP message indicates how many bytes are omitted from the
   beginning of the WBXML Data of the next subblock. The value in the
   response should be the same as in the request; if it is not, the request
   can be repeated.
   The Index is always the number of WBXML bytes omitted from the beginning.
   If the Index is zero or this subblock is not present at all, that means
   the beginning of WBXML encoded result.
*/

typedef struct
    {
    uint8   ID;
    uint8   fill1;
    uint16  Length;
    uint32  Index;
    } tGRN_index_info;

#define SIZE_tGRN_index_info   sizeof(tGRN_index_info)


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_SERVER_VERSION_INFO                                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   ID;
    uint8   fill1;
    uint16  Length;
    uint8   VersionZZZ;   /* Version number see reference /4/ */
    uint8   VersionYYY;   /* Version number see reference /4/ */
    uint8   VersionXXX;   /* Version number see reference /4/ */
    uint8   fill2;
    } tGRN_version_info;

#define SIZE_tGRN_version_info   sizeof(tGRN_version_info)


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_SERVER_STATE_INFO                                         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   ID;
    uint8   fill1;
    uint16  Length;
    /* Values from the constant table GRN_SERVER_STATE */
    tGRN_server_state State;
    /* State before phone reset or last GRN_CLEAR_REQ message. In the latter
       case, state GRN_SERVER_STATE_INACTIVE means that the phone has
       rebooted.
       After the initial start the value is undefined and even illegal values
       are possible.
       Values from the constant table GRN_SERVER_STATE
    */
    tGRN_server_state OldState;
    /* Last tag in running.
       Before the first test case is started the value can be anything.
    */
    uint16  LatestKnownId;
    /* Transaction ID of the last received test or result request, or zero.
    */
    uint8   LastTID;
    /* Cause of error. Cleared to GRN_CAUSE_NONE on next GRN_CLEAR_REQ
       message.
       Values from the constant table GRN_CAUSES
    */
    tGRN_cause ErrCause;
    /* State of the server when error occurred.
       Values from the constant table GRN_SERVER_STATE
    */
    tGRN_server_state ErrState;
    /* Transaction ID of the last received test or result request when the
       error occurred, or zero.
    */
    uint8   ErrTID;
    } tGRN_server_state_info;

#define SIZE_tGRN_server_state_info   sizeof(tGRN_server_state_info)


/* ----------------------------------------------------------------------- */
/* Subblock: GRN_PROVISIONG_DATA                                           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   ID;
    uint8   fill1;
    uint16  Length;
    /* Length of data is limited to maximum size of this subblock */
    uint8   Data[GRANITE_ANY_SIZE];
    } tGRN_provisioning_data;

#define SIZE_tGRN_provisioning_data   (5)


/* ----------------------------------------------------------------------- */
/* Message: GRN_STATUS_REQ                                                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_status_req;

#define SIZE_tGRN_status_req   sizeof(tGRN_status_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_STATUS_RESP                                                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   IFversionZZZ; /* Interface version number */
    uint8   IFversionYYY; /* Interface version number */
    uint8   Blocks;
    /* Subblock list:
       GRN_SERVER_STATE_INFO
       GRN_SERVER_VERSION_INFO
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_status_resp;

#define SIZE_tGRN_status_resp   (5*sizeof(uint8) + sizeof(uint16) + \
        sizeof(bool8))


/* ----------------------------------------------------------------------- */
/* Message: GRN_TEST_REQ                                                   */
/* ----------------------------------------------------------------------- */
/* Test step is encoded in WBXML and put in a GRN_WBXML_REQ_INFO subblock. If
   the test step is too long for a single message, it can be split. Each
   message except the last one must have TRUE in the Continue field. A
   response (GRN_TEST_RESP) is sent only after the last request message
   except in case of error. The server may respond with a notification
   (GRN_TEST_NTF) to each message.
   This message also means that the results of the previous test step will
   not be queried anymore.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    /* TRUE if message is incomplete and continued in the next message. FALSE
       in the last messsage.
    */
    bool8   Continue;
    uint8   fill1[2];
    uint8   Blocks;
    /* Subblock list:
       GRN_WBXML_REQ_INFO
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_test_req;

#define SIZE_tGRN_test_req   (5*sizeof(uint8) + sizeof(uint16) + \
        sizeof(bool8))


/* ----------------------------------------------------------------------- */
/* Message: GRN_TEST_NTF                                                   */
/* ----------------------------------------------------------------------- */
/* These notifications may be sent as preliminary responses to GRN_TEST_REQ
   requests. Server need not send all notifications. Future versions of
   server may send other notifications. Unidentified notifications (content
   of Notify field not any of values in GRN_NOTIFICATIONS) can be ignored.
   Notifications as specified here have no subblocks. Future versions of
   GRANITE server may put subblocks to notifications. Unexpected subblocks
   can be ignored.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    /* TRUE if message is incomplete and continued in the next message. FALSE
       in the last messsage.
    */
    bool8   Continue;
    /* Values from the constant table GRN_NOTIFICATIONS */
    tGRN_notification Notify;
    uint8   fill1;
    uint8   Blocks;
    uint8   sub_blocks[GRANITE_ANY_SIZE]; /* Subblock list: */
    } tGRN_test_ntf;

#define SIZE_tGRN_test_ntf   (4*sizeof(uint8) + sizeof(uint16) + \
        sizeof(bool8) + sizeof(tGRN_notification))


/* ----------------------------------------------------------------------- */
/* Message: GRN_TEST_RESP                                                  */
/* ----------------------------------------------------------------------- */
/* This message is sent when the requested test step is executed or an error
   condition is detected. Error details are given in a subblock if there was
   a syntax error in the test request. Otherwise there is no subblock. The
   result of the test is not in the message but can be queried with
   GRN_RESULT_REQ messages.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    /* TRUE if message is incomplete and continued in the next message. FALSE
       in the last messsage.
    */
    bool8   Continue;
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   Blocks;
    /* Subblock list:
       GRN_PARSE_ERROR_INFO
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_test_resp;

#define SIZE_tGRN_test_resp   (3*sizeof(uint8) + sizeof(uint16) + \
        2*sizeof(bool8) + sizeof(tGRN_cause))


/* ----------------------------------------------------------------------- */
/* Message: GRN_RESULT_REQ                                                 */
/* ----------------------------------------------------------------------- */
/* After execution of test case the results can be queried with
   GRN_RESULT_REQ messages. Result must be queried before any of GRN_TEST_REQ
   or GRN_CLEAR_REQ or GRN_TERM_REQ message, for any one of these clears the
   result in the server. The result or a part of it is returned in a
   GRN_RESULT_RESP message. Several requests may be needed to get all of the
   result.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   fill1[2];
    uint8   Blocks;
    /* Subblock list:
       GRN_INDEX_INFO
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_result_req;

#define SIZE_tGRN_result_req   (5*sizeof(uint8) + sizeof(uint16) + \
        sizeof(bool8))


/* ----------------------------------------------------------------------- */
/* Message: GRN_RESULT_RESP                                                */
/* ----------------------------------------------------------------------- */
/* Result of last test or a part of it. The GRN_INDEX_INFO subblock (if
   present) identifies the part. The GRN_WBXML_RESP_INFO subblock (if
   present) contains the result in WBXML encoding. The latter or both
   subblocks may be absent if there is no result or the result is so short
   that the requested part does not exist.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   Blocks;
    /* Subblock list:
       GRN_INDEX_INFO
       GRN_WBXML_RESP_INFO
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_result_resp;

#define SIZE_tGRN_result_resp   (3*sizeof(uint8) + sizeof(uint16) + \
        2*sizeof(bool8) + sizeof(tGRN_cause))


/* ----------------------------------------------------------------------- */
/* Message: GRN_ABORT_REQ                                                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_abort_req;

#define SIZE_tGRN_abort_req   sizeof(tGRN_abort_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_ABORT_RESP                                                 */
/* ----------------------------------------------------------------------- */
/* GRANITE server sends this message when it has received an GRN_ABORT_REQ
   message and has aborted the currently executing test case.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   fill1;
    } tGRN_abort_resp;

#define SIZE_tGRN_abort_resp   sizeof(tGRN_abort_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_TERM_REQ                                                   */
/* ----------------------------------------------------------------------- */
/* Indication that test session is over and GRANITE server should release all
   resources it may have reserved for execution of tests. In particular,
   results of the last test case will not queried anymore.GRN_CLEAR_REQ
   message is required before the next test step is sent.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_term_req;

#define SIZE_tGRN_term_req   sizeof(tGRN_term_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_TERM_RESP                                                  */
/* ----------------------------------------------------------------------- */
/* GRANITE server sends this message when it has received an GRN_TERM_REQ
   message and has terminated.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   fill1;
    } tGRN_term_resp;

#define SIZE_tGRN_term_resp   sizeof(tGRN_term_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CLEAR_REQ                                                  */
/* ----------------------------------------------------------------------- */
/* This message is needed before the server can be given a test step. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_clear_req;

#define SIZE_tGRN_clear_req   sizeof(tGRN_clear_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CLEAR_RESP                                                 */
/* ----------------------------------------------------------------------- */
/* GRANITE server sends this message when it has received an GRN_CLEAR_REQ
   message and completed clearing. GRANITE server is ready for the next test
   step.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   fill1;
    } tGRN_clear_resp;

#define SIZE_tGRN_clear_resp   sizeof(tGRN_clear_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CLEAR_TESTCASE_REQ                                         */
/* ----------------------------------------------------------------------- */
/* This message is should be used between test cases. The message is similar
   in meaning to GRN_CLEAR_REQ message but in addition lets server to delete
   data structures that are no more needed in the next test case.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_clear_testcase_req;

#define SIZE_tGRN_clear_testcase_req   sizeof(tGRN_clear_testcase_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CLEAR_TESTCASE_RESP                                        */
/* ----------------------------------------------------------------------- */
/* GRANITE server sends this message when it has received an
   GRN_CLEAR_TESTCASE_REQ message and completed clearing. GRANITE server is
   ready for the next test step.
*/

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    tGRN_cause Cause;     /* Values from the constant table GRN_CAUSES */
    uint8   fill1;
    } tGRN_clear_testcase_resp;

#define SIZE_tGRN_clear_testcase_resp   sizeof(tGRN_clear_testcase_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_RESET_PHONE_REQ                                            */
/* ----------------------------------------------------------------------- */
/* This message is used for generating phone resets. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   reset_reason; /* Reset reason (valid values in hw_power.h) */
    } tGRN_reset_phone_req;

#define SIZE_tGRN_reset_phone_req   sizeof(tGRN_reset_phone_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_DISPLAY_UPDATE_NTF - Valid from version 001.008            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   fill1;
    uint16  X;
    uint16  Y;
    uint16  Width;
    uint16  Height;
    uint16  Fps;
    uint32  TimeStamp;
    char    Type[GRANITE_ANY_SIZE]; /* Display update notification type */
    } tGRN_display_update_ntf;

#define SIZE_tGRN_display_update_ntf   (3*sizeof(uint8) + 6*sizeof(uint16) + \
        sizeof(bool8) + sizeof(uint32))


/* ----------------------------------------------------------------------- */
/* Message: GRN_CTC_START_REQ - Valid from version 001.003                 */
/* ----------------------------------------------------------------------- */
/* This message is used to start CTC++ coverage measurement. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   fill1[2];
    char    filename[GRANITE_ANY_SIZE]; /* Filename for CTC data */
    } tGRN_ctc_start_req;

#define SIZE_tGRN_ctc_start_req   (4*sizeof(uint8) + sizeof(uint16) + \
        sizeof(bool8))


/* ----------------------------------------------------------------------- */
/* Message: GRN_CTC_START_RESP - Valid from version 001.003                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    } tGRN_ctc_start_resp;

#define SIZE_tGRN_ctc_start_resp   sizeof(tGRN_ctc_start_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CTC_STOP_REQ - Valid from version 001.003                  */
/* ----------------------------------------------------------------------- */
/* This message is used to stop CTC++ coverage measurement. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    } tGRN_ctc_stop_req;

#define SIZE_tGRN_ctc_stop_req   sizeof(tGRN_ctc_stop_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_CTC_STOP_RESP - Valid from version 001.003                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    bool8   Response;
    } tGRN_ctc_stop_resp;

#define SIZE_tGRN_ctc_stop_resp   sizeof(tGRN_ctc_stop_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_WRITE_REQ - Valid from version 001.005        */
/* ----------------------------------------------------------------------- */
/* This message is used to write Provisioning settings to phone */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Values from the constant table GRN_PROVISIONING_DATA_TYPES */
    uint8   DataType;
    uint8   SimID;
    uint8   Blocks;
    /* Subblock list:
       GRN_PROVISIONG_DATA
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_provisioning_write_req;

#define SIZE_tGRN_provisioning_write_req   (5*sizeof(uint8) + \
        sizeof(uint16) + sizeof(bool8))


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_WRITE_RESP - Valid from version 001.005       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Values from the constant table GRN_PROVISIONING_RESPONSE */
    uint8   Response;
    uint16  CC;
    } tGRN_provisioning_write_resp;

#define SIZE_tGRN_provisioning_write_resp   \
        sizeof(tGRN_provisioning_write_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_SELECT_REQ - Valid from version 001.005       */
/* ----------------------------------------------------------------------- */
/* This message is used to select Provisioning settings */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   SimID;
    uint16  CC;
    } tGRN_provisioning_select_req;

#define SIZE_tGRN_provisioning_select_req   \
        sizeof(tGRN_provisioning_select_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_SELECT_RESP - Valid from version 001.005      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Values from the constant table GRN_PROVISIONING_RESPONSE */
    uint8   Response;
    } tGRN_provisioning_select_resp;

#define SIZE_tGRN_provisioning_select_resp   \
        sizeof(tGRN_provisioning_select_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_DELETE_REQ - Valid from version 001.005       */
/* ----------------------------------------------------------------------- */
/* This message is used to delete one or all Provisioning settings */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Priority order: Delete all, SimID, CC
       
       E.g. to delete by CC
       DeleteAll -> FALSE, SimID -> 0, CC -> 'desired CC'
    */
    bool8   DeleteAll;
    uint16  CC;
    uint8   SimID;
    } tGRN_provisioning_delete_req;

#define SIZE_tGRN_provisioning_delete_req   \
        sizeof(tGRN_provisioning_delete_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_DELETE_RESP - Valid from version 001.005      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Values from the constant table GRN_PROVISIONING_RESPONSE */
    uint8   Response;
    } tGRN_provisioning_delete_resp;

#define SIZE_tGRN_provisioning_delete_resp   \
        sizeof(tGRN_provisioning_delete_resp)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_READ_REQ - Valid from version 001.005         */
/* ----------------------------------------------------------------------- */
/* This message is read Provisioning settings from phone. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    uint8   SimID;
    uint16  CC;
    /* Values from the constant table GRN_PROVISIONING_DATA_TYPES */
    uint8   DataType;
    } tGRN_provisioning_read_req;

#define SIZE_tGRN_provisioning_read_req   sizeof(tGRN_provisioning_read_req)


/* ----------------------------------------------------------------------- */
/* Message: GRN_PROVISIONING_READ_RESP - Valid from version 001.005        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  private_id;
    bool8   Continue;     /* This message cannot be continued */
    /* Values from the constant table GRN_PROVISIONING_RESPONSE */
    uint8   Response;
    uint8   fill1;
    uint8   Blocks;
    /* Subblock list:
       GRN_PROVISIONG_DATA
    */
    uint8   sub_blocks[GRANITE_ANY_SIZE];
    } tGRN_provisioning_read_resp;

#define SIZE_tGRN_provisioning_read_resp   (9)




/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /1/  Autogeneration Process
        Lotus Notes Database: Engine TEC DocMan
        Document Number:      DSJ00311
        Filename:             autogen_proc.doc

   /2/  ISI Server Specification Documentation Guidelines
        Part:      ISI:INSTRUCTIONS.BASE
        Item name: ISI:DOCUMENTATION_GUIDELINES.BASE-MISC
        Workset:   ISI:WS_ISI
        Filename:  i_docgui.doc

   /3/  ISI General Information
        Part:      ISI:INSTRUCTIONS.BASE
        Item name: ISI:GENERAL_INFORMATION.BASE-MISC
        Workset:   ISI:WS_ISI
        Filename:  i_geninf.doc

   /4/  ISI Common Message Descriptions
        Workset:   ISI:WS_ISI
        Part:      ISI:COMMON.BASE
        Item:      ISI:COMMON_MESSAGES.BASE-SPEC
        Filename:  i_comm_m.doc

   /6/  ISI Common Feature Descriptions
        Workset: ISI:WS_ISI
        Part: ISI:COMMON.BASE
        Item: ISI:COMMON_FEATURES.BASE-SPEC
        Filename: i_comm_f.doc

   /7/  Binary XML Content Format Specification
        Version 1.3, 25 July 2001
        Wireless Application Protocol
        WAP-192-WBXML-20010725-a
        Wireless Application Protocol Forum, Ltd.
*/


#endif /* _GRANITE_P_ISI_H */
