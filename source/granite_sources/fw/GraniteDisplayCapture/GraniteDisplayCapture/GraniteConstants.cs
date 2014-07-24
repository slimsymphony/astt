using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Nokia.Granite.Display.Capture
{

    //-----------------------------------------------------------------------
    //Constant Table: GRN_SERVER_STATE                                       
    //-----------------------------------------------------------------------
    public enum GraniteServerState : byte
    {
        GRN_SERVER_STATE_STARTING =                 0x00,
        GRN_SERVER_STATE_IDLE =                     0x01,
        GRN_SERVER_STATE_PARSING =                  0x02,
        GRN_SERVER_STATE_RUNNING =                  0x03,
        GRN_SERVER_STATE_ABORTING =                 0x04,
        GRN_SERVER_STATE_SUSPENDED =                0x05,
        GRN_SERVER_STATE_WAITING =                  0x06,
        GRN_SERVER_STATE_INACTIVE =                 0x07,
        GRN_SERVER_STATE_REPORTING =                0x08,
        GRN_SERVER_STATE_CLEARING =                 0x09,
        GRN_SERVER_STATE_TERMINATING =              0x0A,
        GRN_SERVER_STATE_CLEARING_TESTCASE =        0x0B
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_OPTIONS                                            
    //-----------------------------------------------------------------------
    public enum GraniteOptions : byte
    {
        GRN_OPTION_NONE =                           0x00,
        GRN_OPTION_POLLED =                         0x01,
        GRN_OPTION_FILE =                           0x02,
        GRN_OPTION_END =                            0x03
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_NOTIFICATIONS                                      
    //-----------------------------------------------------------------------
    //Future versions may add other notifications. Unidentified notifications
    //may be ignored.
    public enum GraniteNotifications : byte
    {
        GRN_NTF_NONE =                              0x00,
        GRN_NTF_PARSE_START =                       0x01,
        //Server is expecting continuation to a test request
        GRN_NTF_PARSE_CONTINUE =                    0x02,
        GRN_NTF_PARSE_DONE =                        0x03,
        GRN_NTF_RUN_START =                         0x04,
        GRN_NTF_RUN_DONE =                          0x05
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_CAUSES                                             
    //-----------------------------------------------------------------------
    public enum GraniteCauses : byte
    {
        GRN_CAUSE_NONE =                            0x00,
        GRN_CAUSE_INVALID_WBXML_DATA =              0x01,
        GRN_CAUSE_MEMORY_FULL =                     0x02,
        GRN_CAUSE_ERROR_TERMINATION =               0x03,
        GRN_CAUSE_NOTEXPECTED_RESULT =              0x04,
        GRN_CAUSE_STATE_UNKNOWN =                   0x09,
        GRN_CAUSE_STATE_STARTING =                  0x0B,
        GRN_CAUSE_STATE_IDLE =                      0x11,
        GRN_CAUSE_STATE_PARSING =                   0x06,
        GRN_CAUSE_STATE_RUNNING =                   0x07,
        GRN_CAUSE_STATE_ABORTING =                  0x08,
        GRN_CAUSE_STATE_SUSPENDED =                 0x15,
        GRN_CAUSE_STATE_INACTIVE =                  0x17,
        GRN_CAUSE_STATE_REPORTING =                 0x18,
        GRN_CAUSE_STATE_CLEARING =                  0x19,
        GRN_CAUSE_STATE_TERMINATING =               0x1A,
        GRN_CAUSE_STATE_CLEARING_TESTCASE =         0x1B
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_TEST_PARSE_ERRORS                                  
    //-----------------------------------------------------------------------
    public enum GraniteTestParseErrors : byte
    {
        GRN_TEST_PARSE_NOERROR =                    0x00,
        GRN_TEST_PARSE_MEMORY_ERROR =               0x01,
        GRN_TEST_WBXML_TOOSHORT =                   0x02,
        GRN_TEST_ILLEGAL_PUBLIC_ID =                0x03,
        GRN_TEST_ILLEGAL_CHARSET =                  0x04,
        GRN_TEST_STR_T_NOT_EMPTY =                  0x05,
        GRN_TEST_ILLEGAL_MB_U_INT32 =               0x06,
        GRN_TEST_ILLEGAL_UTF8_STRING =              0x07,
        GRN_TEST_UNEXPECTED_TAG =                   0x08,
        GRN_TEST_TAG_WITH_CONTENT =                 0x09,
        GRN_TEST_TAG_WITHOUT_CONTENT =              0x0A,
        GRN_TEST_TAG_WITH_ATTRIBUTE =               0x0B,
        GRN_TEST_TAG_WITHOUT_ATTRIBUTE =            0x0C,
        GRN_TEST_UNEXPECTED_DATA_END =              0x0D,
        GRN_TEST_UNEXPECTED_ELEMENT =               0x0E
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_VERSIONS                                     
    //-----------------------------------------------------------------------
    //The first byte of any WBXML data identifies WBXML version in use.
    public enum GraniteWbxmlVersions : byte
    {
        GRN_WBXML_VERSION =                         0x03
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_PUBLIC_IDS                                   
    //-----------------------------------------------------------------------
    //The second byte of any WBXML data is a publick ID that identifies encoding
    //of tags. In case of ART2 server's private interface this has little
    //significance, for all parties know encoding conventions, and the WBXML
    //data is not used elsewhere.
    public enum GraniteWbxmlPublicId : byte
    {
        GRN_WBXML_PUBLIC_ID =                       0x20
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_CHARSETS                                     
    //-----------------------------------------------------------------------
    //The third byte of any WBXML data identifies character encoding used in all
    //texts.
    public enum GraniteWbxmlCharsets : byte
    {
        GRN_WBXML_CHARSET_UTF8 =                    0x6A
    }

    //-----------------------------------------------------------------------
    //Message ID's                                                           
    //-----------------------------------------------------------------------
    public enum GraniteMessageIds : byte
    {
        GRN_STATUS_REQ =                            0x00,
        GRN_STATUS_RESP =                           0x01,
        GRN_TEST_REQ =                              0x02,
        GRN_TEST_RESP =                             0x03,
        GRN_TEST_NTF =                              0x04,
        GRN_ABORT_REQ =                             0x05,
        GRN_ABORT_RESP =                            0x06,
        GRN_RESULT_REQ =                            0x0F,
        GRN_RESULT_RESP =                           0x10,
        GRN_TERM_REQ =                              0x11,
        GRN_TERM_RESP =                             0x12,
        GRN_CLEAR_REQ =                             0x14,
        GRN_CLEAR_RESP =                            0x16,
        GRN_CLEAR_TESTCASE_REQ =                    0x17,
        GRN_CLEAR_TESTCASE_RESP =                   0x19,
        GRN_ISM_API_WRITE_REQ =                     0x1A,
        GRN_ISM_API_WRITE_RESP =                    0x1B,
        GRN_ISM_API_READ_REQ =                      0x1C,
        GRN_ISM_API_READ_RESP =                     0x1D,
        GRN_RESET_PHONE_REQ	=                       0x1E
    }

    //-----------------------------------------------------------------------
    //Subblock ID's                                                          
    //-----------------------------------------------------------------------
    public enum GraniteSubblockIds : byte
    {
         GRN_NO_INFO =                              0x00,
         GRN_PARSE_ERROR_INFO =                     0x01,
         GRN_WBXML_REQ_INFO =                       0x02,
         GRN_WBXML_RESP_INFO =                      0x04,
         GRN_INDEX_INFO =                           0x06,
         GRN_SERVER_VERSION_INFO =                  0x07,
         GRN_SERVER_STATE_INFO =                    0x08,
         GRN_ISM_API_BOOL_SETTING =                 0x09,
         GRN_ISM_API_UCS2_STRING_SETTING =          0x0A,
         GRN_ISM_API_FILEPATH_SETTING =             0x0B,
         GRN_ISM_API_ENUM_SETTING =                 0x0C,
         GRN_ISM_API_INT32_SETTING =                0x0D,
         GRN_ISM_API_FIM_ID_SETTING =               0x0E
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_GLOBALS                                      
    //-----------------------------------------------------------------------
    //Encoding of WBXML Global tokens as specified in the WBXML standard /7/.
    //Tokens marked "Not used" are not used in messages to or from ART2 server.
    public enum GraniteWbxmlGlobals : byte
    {
        GRN_WBXML_SWITCH_PAGE =                     0x00, //Not used 
        GRN_WBXML_END =                             0x01,
        GRN_WBXML_ENTITY =                          0x02, //Not used 
        //used for string values and text content 
        GRN_WBXML_STR_I =                           0x03,
        GRN_WBXML_LITERAL =                         0x04, //Not used 
        GRN_WBXML_EXT_I_0 =                         0x40, //Not used 
        GRN_WBXML_EXT_I_1 =                         0x41, //Not used 
        GRN_WBXML_EXT_I_2 =                         0x42, //Not used 
        GRN_WBXML_PI =                              0x43, //Not used 
        GRN_WBXML_LITERAL_C =                       0x44,
        //used for integer values 
        GRN_WBXML_EXT_T_0 =                         0x80,
        GRN_WBXML_EXT_T_1 =                         0x81, //Not used 
        GRN_WBXML_EXT_T_2 =                         0x82, //Not used 
        GRN_WBXML_STR_T =                           0x83, //Not used 
        GRN_WBXML_LITERAL_A =                       0x84, //Not used 
        GRN_WBXML_EXT_0 =                           0xC0, //Not used 
        GRN_WBXML_EXT_1 =                           0xC1, //Not used 
        GRN_WBXML_EXT_2 =                           0xC2, //Not used 
        //used for bitmap images 
        GRN_WBXML_OPAQUE =                          0xC3,
        GRN_WBXML_LITERAL_AC =                      0xC4 //Not used 
    }

    //-----------------------------------------------------------------------
    //Bitmask Table: GRN_WBXML_TAG_BITS                                      
    //-----------------------------------------------------------------------
    //Two bits in a tag byte are reserved for attribute and content indicators.
    public enum GraniteWbxmlTagBits : byte
    {
        //Tag has attributes
        GRN_WBXML_A =                             0x80,  // 1-------
        //Tag has contents
        GRN_WBXML_C =                             0x40,  // -1------
        //Mask for tag
        GRN_WBXML_TAG_MASK =                      0x3F  // --111111
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_TAGS                                         
    //-----------------------------------------------------------------------
    //These encodings are used for XML tags in messages to and from ART2 server.
    //Literal tags are not used.
    public enum GraniteWbxmlTags : byte
    {
         GRN_WBXML_TAG_teststep =                  0x05,
         GRN_WBXML_TAG_sx =                        0x06,
         GRN_WBXML_TAG_delay =                     0x07,
         GRN_WBXML_TAG_key_in =                    0x08,
         GRN_WBXML_TAG_keypress =                  0x09,
         GRN_WBXML_TAG_expect =                    0x0B,
         GRN_WBXML_TAG_display =                   0x0C,
         GRN_WBXML_TAG_bitmap =                    0x0D,
         GRN_WBXML_TAG_label =                     0x0E,
         GRN_WBXML_TAG_data =                      0x0F,
         GRN_WBXML_TAG_capture =                   0x10,
         GRN_WBXML_TAG_image_widget =              0x11,
         GRN_WBXML_TAG_config =                    0x12,
         GRN_WBXML_TAG_block =                     0x13,
         GRN_WBXML_TAG_touch =                     0x14,
         GRN_WBXML_TAG_press =                     0x15,
         GRN_WBXML_TAG_move =                      0x16,
         GRN_WBXML_TAG_release =                   0x17,
         GRN_WBXML_TAG_xml =                       0x18,
         GRN_WBXML_TAG_java =                      0x19
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_ATTR_LABELS                                  
    //-----------------------------------------------------------------------
    //These encodings are used for XML attribute names in messages to and from
    //ART2 server. None of the codes encodes any part of the attribute value.
    //Literal names are not used. The value that follows must be of the type
    //indicated in Comment.
    //The Comment indicates how attribute values are encoded. Comment "string"
    //means that the attribute value is encoded as a string. Values of other
    //attributes shall not be encoded as a string. Comment with alternatives
    //means that the values is one of alternatives encoded with a single byte as
    //shown in table GRN_WBXML_ATTR_VALUES. The value "yes" may be omitted. If
    //the list of alternatives is surrounded  by braces, more than one
    //alternative may be specified. Comment "integer" means that value is a
    //number encoded with the GRN_WBXML_EXT_T_0 byte (defined in table
    //GRN_WBXML_GLOBALS) followed by the value in mb_uint32 encoding. However,
    //small values may (but need not) be encoded with single bytes as shown in
    //table GRN_WBXML_ATTR_VALUES. The value zero can be omitted completely.
    public enum GraniteWbxmlAttrLabels : byte
    {
         GRN_WBXML_ATTR_wait =                     0x05,  //integer 
         GRN_WBXML_ATTR_key =                      0x06,  //integer 
         GRN_WBXML_ATTR_length =                   0x07,  //integer 
         GRN_WBXML_ATTR_repeat =                   0x08,  //integer 
         GRN_WBXML_ATTR_timeout =                  0x09,  //integer 
         GRN_WBXML_ATTR_font =                     0x0A,  //integer 
         GRN_WBXML_ATTR_color =                    0x0B,  //integer 
         GRN_WBXML_ATTR_x =                        0x0C,  //integer 
         GRN_WBXML_ATTR_y =                        0x0D,  //integer 
         GRN_WBXML_ATTR_width =                    0x0E,  //integer 
         GRN_WBXML_ATTR_height =                   0x0F,  //integer 
         GRN_WBXML_ATTR_mask =                     0x10,  //integer 
         GRN_WBXML_ATTR_highlighted =              0x11,  //yes/no 
         GRN_WBXML_ATTR_name =                     0x12,  //string 
         GRN_WBXML_ATTR_valid =                    0x13,  //yes/no 
         GRN_WBXML_ATTR_id =                       0x14,  //integer 
         //integer with GRN_STATUS_BITS 
         GRN_WBXML_ATTR_result =                   0x15,
         GRN_WBXML_ATTR_format =                   0x16,  //integer 
         GRN_WBXML_ATTR_checksum =                 0x17,  //integer 
         GRN_WBXML_ATTR_animation_id =             0x18,  //integer 
         GRN_WBXML_ATTR_truncated =                0x19,  //yes/no 
         //{text/animation/bitmap/items/all} 
         GRN_WBXML_ATTR_items =                    0x1A,
         GRN_WBXML_ATTR_bitmap_capture =           0x1B,  //yes/no 
         GRN_WBXML_ATTR_max_isi_data_length =      0x1C,  //integer 
         GRN_WBXML_ATTR_keypress_length =          0x1D,  //integer 
         GRN_WBXML_ATTR_keypress_wait =            0x1E,  //integer 
         GRN_WBXML_ATTR_screen =                   0x1F,  //integer 
         GRN_WBXML_ATTR_dimmed =                   0x20,  //yes/no 
         GRN_WBXML_ATTR_wait_for_key_release =     0x21,  //yes/no 
         GRN_WBXML_ATTR_wildcard =                 0x22,  //yes/no 
         GRN_WBXML_ATTR_offset =                   0x24,  //integer 
         GRN_WBXML_ATTR_gap =                      0x25,  //integer 
         GRN_WBXML_ATTR_little_endian_cpu =        0x30,  //yes/no 
         GRN_WBXML_ATTR_training =                 0x31,  //yes/no 
         GRN_WBXML_ATTR_action =                   0x32,  //hold/release 

         //integer (default: 800) 
         GRN_WBXML_ATTR_long_press_length =        0x33,
         //integer (default: 500) 
         GRN_WBXML_ATTR_repeat_length =            0x34,
         //integer (8+8+8 bit RGB) 
         GRN_WBXML_ATTR_fg =                       0x35,
         //integer (8+8+8 bit RGB) 
         GRN_WBXML_ATTR_bg =                       0x36,
         //yes/no/all (default: no) 
         GRN_WBXML_ATTR_background =               0x37,
         //yes/no (default: no) 
         GRN_WBXML_ATTR_landscape =                0x38,
         //integer (default may vary) 
         GRN_WBXML_ATTR_font_type =                0x39,
         //integer (default: 0) 
         GRN_WBXML_ATTR_short_press_length =       0x3A,
         //integer (default: 0) 
         GRN_WBXML_ATTR_keys_idle_length =         0x3B,
         //integer (default: 0) 
         GRN_WBXML_ATTR_touch_id =                 0x55
    }

    //-----------------------------------------------------------------------
    //Constant Table: GRN_WBXML_ATTR_VALUES                                  
    //-----------------------------------------------------------------------
    //These encodings are used for XML for attribute values. Encoding as a
    //string is used only for attributes marked with "string" in the table
    //GRN_WBXML_ATTR_LABELS. Integer values greater than 15 must (and all
    //integer values may) be encoded with with the GRN_WBXML_EXT_T_0 byte
    //(defined in table GRN_WBXML_GLOBALS) followed by the value in mb_uint32
    //encoding.
    //If attribute value is encoded using bytes of this table, it is encoded
    //with single byte only, except that the value of items attribute in capture
    //tag can be a sequence of bytes.
    //If the value of attribute is "yes" or zero it can be omitted.
    public enum GraniteWbxmlAttrValues : byte
    {
        GRN_WBXML_ATTR_VALUE_yes =                0x85,
        GRN_WBXML_ATTR_VALUE_no =                 0x86,
        //for items in capture tag
        GRN_WBXML_ATTR_VALUE_text =               0x87,
        //for items in capture tag
        GRN_WBXML_ATTR_VALUE_animation =          0x88,
        //for items in capture tag
        GRN_WBXML_ATTR_VALUE_bitmap =             0x89,
        //for items in capture tag
        GRN_WBXML_ATTR_VALUE_items =              0x90,
        //for items in capture tag; also for "don't care" in optional attributes of
        //items in expect tag
        GRN_WBXML_ATTR_VALUE_all =                0x91,
        //GRN_WBXML_ATTR_VALUE_all              0x91 (already defined)
        //for action in keypress
        GRN_WBXML_ATTR_VALUE_hold =               0x92,
        //for action in keypress
        GRN_WBXML_ATTR_VALUE_release =            0x93,
        //numeric value zero 
        GRN_WBXML_ATTR_VALUE_0 =                  0xB0,
        //numeric value one 
        GRN_WBXML_ATTR_VALUE_1 =                  0xB1,
        //numeric value two 
        GRN_WBXML_ATTR_VALUE_2 =                  0xB2,
        //numeric value three 
        GRN_WBXML_ATTR_VALUE_3 =                  0xB3,
        //numeric value four 
        GRN_WBXML_ATTR_VALUE_4 =                  0xB4,
        //numeric value five 
        GRN_WBXML_ATTR_VALUE_5 =                  0xB5,
        //numeric value six 
        GRN_WBXML_ATTR_VALUE_6 =                  0xB6,
        //numeric value seven 
        GRN_WBXML_ATTR_VALUE_7 =                  0xB7,
        //numeric value eight 
        GRN_WBXML_ATTR_VALUE_8 =                  0xB8,
        //numeric value nine 
        GRN_WBXML_ATTR_VALUE_9 =                  0xB9,
        //numeric value ten 
        GRN_WBXML_ATTR_VALUE_10 =                 0xBA,
        //numeric value eleven 
        GRN_WBXML_ATTR_VALUE_11 =                 0xBB,
        //numeric value twelve 
        GRN_WBXML_ATTR_VALUE_12 =                 0xBC,
        //numeric value thirteen 
        GRN_WBXML_ATTR_VALUE_13 =                 0xBD,
        //numeric value fourteen 
        GRN_WBXML_ATTR_VALUE_14 =                 0xBE,
        //numeric value fifteen 
        GRN_WBXML_ATTR_VALUE_15 =                 0xBF
    }

    //-----------------------------------------------------------------------
    //Bitmask Table: GRN_STATUS_BITS                                         
    //-----------------------------------------------------------------------
    //Value of result attribute is an integer where each bit has independent
    //meaning (what was wrong in the display). This table identifies the bit
    //used for each meaning.
    public enum GraniteStatusBits : ushort
    {
         GRN_STATUS_NONE =                         0x0000,  //0000000000000000 
         GRN_STATUS_data =                         0x0001,  //---------------1 
         GRN_STATUS_text =                         GRN_STATUS_data,
         GRN_STATUS_animation_id =                 GRN_STATUS_data,
         GRN_STATUS_x =                            0x0002,  //--------------1- 
         GRN_STATUS_y =                            0x0004,  //-------------1-- 
         GRN_STATUS_width =                        0x0008,  //------------1--- 
         GRN_STATUS_height =                       0x0010,  //-----------1---- 
         GRN_STATUS_highlighted =                  0x0020,  //----------1----- 
         GRN_STATUS_font =                         0x0040,  //---------1------ 
         GRN_STATUS_color =                        0x0080,  //--------1------- 
         GRN_STATUS_truncated =                    0x0100,  //-------1-------- 
         GRN_STATUS_screen =                       0x0200,  //------1--------- 
         GRN_STATUS_dimmed =                       0x0400,  //-----1---------- 
         GRN_STATUS_background =                   0x0800   //----1----------- 
    }

    //-----------------------------------------------------------------------
    //Constant Table: Font names (defined in font_def_priv.h)                                       
    //-----------------------------------------------------------------------
    public enum FontNames : byte
    {
         FONT_NAME_PRIV_PIXEL_06 =      0x0006,
         FONT_NAME_PRIV_PIXEL_07 =      0x0007,
         FONT_NAME_PRIV_PIXEL_08 =      0x0008,
         FONT_NAME_PRIV_PIXEL_09 =      0x0009,
         FONT_NAME_PRIV_PIXEL_10 =      0x000A,
         FONT_NAME_PRIV_PIXEL_11 =      0x000B,
         FONT_NAME_PRIV_PIXEL_12 =      0x000C,
         FONT_NAME_PRIV_PIXEL_13 =      0x000D,
         FONT_NAME_PRIV_PIXEL_14 =      0x000E,
         FONT_NAME_PRIV_PIXEL_15 =      0x000F,
         FONT_NAME_PRIV_PIXEL_16 =      0x0010,
         FONT_NAME_PRIV_PIXEL_17 =      0x0011,
         FONT_NAME_PRIV_PIXEL_18 =      0x0012,
         FONT_NAME_PRIV_PIXEL_19 =      0x0013,
         FONT_NAME_PRIV_PIXEL_20 =      0x0014,
         FONT_NAME_PRIV_PIXEL_21 =      0x0015,
         FONT_NAME_PRIV_PIXEL_22 =      0x0016,
         FONT_NAME_PRIV_PIXEL_23 =      0x0017,
         FONT_NAME_PRIV_PIXEL_24 =      0x0018,
         FONT_NAME_PRIV_PIXEL_25 =      0x0019,
         FONT_NAME_PRIV_PIXEL_26 =      0x001A,
         FONT_NAME_PRIV_PIXEL_27 =      0x001B,
         FONT_NAME_PRIV_PIXEL_28 =      0x001C,
         FONT_NAME_PRIV_PIXEL_29 =      0x001D,
         FONT_NAME_PRIV_PIXEL_30 =      0x001E,
         FONT_NAME_PRIV_PIXEL_31 =      0x001F,
         FONT_NAME_PRIV_PIXEL_32 =      0x0020,
         FONT_NAME_PRIV_PIXEL_33 =      0x0021,
         FONT_NAME_PRIV_PIXEL_34 =      0x0022,
         FONT_NAME_PRIV_PIXEL_35 =      0x0023,
         FONT_NAME_PRIV_PIXEL_36 =      0x0024,
         FONT_NAME_PRIV_PIXEL_37 =      0x0025,
         FONT_NAME_PRIV_PIXEL_38 =      0x0026,
         FONT_NAME_PRIV_PIXEL_39 =      0x0027,
         FONT_NAME_PRIV_PIXEL_40 =      0x0028,
         FONT_NAME_PRIV_PIXEL_41 =      0x0029,
         FONT_NAME_PRIV_PIXEL_42 =      0x002A,
         FONT_NAME_PRIV_PIXEL_43 =      0x002B,
         FONT_NAME_PRIV_PIXEL_44 =      0x002C,
         FONT_NAME_PRIV_PIXEL_45 =      0x002D,
         FONT_NAME_PRIV_PIXEL_46 =      0x002E,
         FONT_NAME_PRIV_PIXEL_47 =      0x002F,
         FONT_NAME_PRIV_PIXEL_48 =      0x0030,
         FONT_NAME_PRIV_PIXEL_49 =      0x0031,
         FONT_NAME_PRIV_PIXEL_50 =      0x0032,
         FONT_NAME_PRIV_PIXEL_51 =      0x0033,
         FONT_NAME_PRIV_PIXEL_52 =      0x0034,
         FONT_NAME_PRIV_PIXEL_53 =      0x0035,
         FONT_NAME_PRIV_PIXEL_54 =      0x0036,
         FONT_NAME_PRIV_PIXEL_55 =      0x0037,
         FONT_NAME_PRIV_PIXEL_56 =      0x0038,
         FONT_NAME_PRIV_PIXEL_57 =      0x0039,
         FONT_NAME_PRIV_PIXEL_58 =      0x003A,
         FONT_NAME_PRIV_PIXEL_59 =      0x003B,
         FONT_NAME_PRIV_PIXEL_60 =      0x003C,
         FONT_NAME_PRIV_PIXEL_61 =      0x003D,
         FONT_NAME_PRIV_PIXEL_62 =      0x003E,
         FONT_NAME_PRIV_PIXEL_63 =      0x003F,
         FONT_NAME_PRIV_PIXEL_64 =      0x0040,
         FONT_NAME_PRIV_PIXEL_65 =      0x0041,
         FONT_NAME_PRIV_PIXEL_66 =      0x0042,
         FONT_NAME_PRIV_PIXEL_67 =      0x0043,
         FONT_NAME_PRIV_PIXEL_68 =      0x0044,
         FONT_NAME_PRIV_PIXEL_69 =      0x0045,
         FONT_NAME_PRIV_PIXEL_70 =      0x0046,
         FONT_NAME_PRIV_PIXEL_71 =      0x0047,
         FONT_NAME_PRIV_PIXEL_72 =      0x0048,
         FONT_NAME_PRIV_PIXEL_73 =      0x0049,
         FONT_NAME_PRIV_PIXEL_74 =      0x004A,
         FONT_NAME_PRIV_PIXEL_75 =      0x004B,
         FONT_NAME_PRIV_PIXEL_76 =      0x004C,
         FONT_NAME_PRIV_PIXEL_77 =      0x004D,
         FONT_NAME_PRIV_PIXEL_78 =      0x004E,
         FONT_NAME_PRIV_PIXEL_79 =      0x004F,
         FONT_NAME_PRIV_PIXEL_80 =      0x0050,
         FONT_NAME_PRIV_PIXEL_81 =      0x0051,
         FONT_NAME_PRIV_PIXEL_82 =      0x0052,
         FONT_NAME_PRIV_PIXEL_83 =      0x0053,
         FONT_NAME_PRIV_PIXEL_84 =      0x0054,
         FONT_NAME_PRIV_PIXEL_85 =      0x0055,
         FONT_NAME_PRIV_PIXEL_86 =      0x0056,
         FONT_NAME_PRIV_PIXEL_87 =      0x0057,
         FONT_NAME_PRIV_PIXEL_88 =      0x0058,
         FONT_NAME_PRIV_PIXEL_89 =      0x0059,
         FONT_NAME_PRIV_PIXEL_90 =      0x005A,
         FONT_NAME_PRIV_PIXEL_91 =      0x005B,
         FONT_NAME_PRIV_PIXEL_92 =      0x005C,
         FONT_NAME_PRIV_PIXEL_93 =      0x005D,
         FONT_NAME_PRIV_PIXEL_94 =      0x005E,
         FONT_NAME_PRIV_PIXEL_95 =      0x005F,
         FONT_NAME_PRIV_PIXEL_96 =      0x0060,
         FONT_NAME_PRIV_PIXEL_97 =      0x0061,
         FONT_NAME_PRIV_PIXEL_98 =      0x0062,
         FONT_NAME_PRIV_PIXEL_99 =      0x0063,
         FONT_NAME_PRIV_PIXEL_100 =     0x0064,
         FONT_NAME_PRIV_PIXEL_101 =     0x0065,
         FONT_NAME_PRIV_PIXEL_102 =     0x0066,
         FONT_NAME_PRIV_PIXEL_103 =     0x0067,
         FONT_NAME_PRIV_PIXEL_104 =     0x0068,
         FONT_NAME_PRIV_PIXEL_105 =     0x0069,
         FONT_NAME_PRIV_PIXEL_106 =     0x006A,
         FONT_NAME_PRIV_PIXEL_107 =     0x006B,
         FONT_NAME_PRIV_PIXEL_108 =     0x006C,
         FONT_NAME_PRIV_PIXEL_109 =     0x006D,
         FONT_NAME_PRIV_PIXEL_110 =     0x006E,
         FONT_NAME_PRIV_PIXEL_111 =     0x006F,
         FONT_NAME_PRIV_PIXEL_112 =     0x0070,
         FONT_NAME_PRIV_PIXEL_113 =     0x0071,
         FONT_NAME_PRIV_PIXEL_114 =     0x0072,
         FONT_NAME_PRIV_PIXEL_115 =     0x0073,
         FONT_NAME_PRIV_PIXEL_116 =     0x0074,
         FONT_NAME_PRIV_PIXEL_117 =     0x0075,
         FONT_NAME_PRIV_PIXEL_118 =     0x0076,
         FONT_NAME_PRIV_PIXEL_119 =     0x0077,
         FONT_NAME_PRIV_PIXEL_120 =     0x0078,
         FONT_NAME_PRIV_PIXEL_121 =     0x0079,
         FONT_NAME_PRIV_PIXEL_122 =     0x007A,
         FONT_NAME_PRIV_PIXEL_123 =     0x007B,
         FONT_NAME_PRIV_PIXEL_124 =     0x007C,
         FONT_NAME_PRIV_PIXEL_125 =     0x007D,
         FONT_NAME_PRIV_PIXEL_126 =     0x007E,
         FONT_NAME_PRIV_PIXEL_127 =     0x007F,
         FONT_NAME_PRIV_PIXEL_128 =     0x0080,
    }
    
    //-----------------------------------------------------------------------
    //Constant Table: Font types (defined in font_def_priv.h)                                       
    //-----------------------------------------------------------------------
    public enum FontTypes : byte
    {
        FONT_TYPE_PRIV_REGULAR =            0x0000,
        FONT_TYPE_PRIV_CN_REGULAR =         0x0008,
        FONT_TYPE_PRIV_SEMIBOLD =           0x0010,
        FONT_TYPE_PRIV_WIDE_BOLD =          0x0012,
        FONT_TYPE_PRIV_SEMIBOLD_ITALIC =    0x0014,
        FONT_TYPE_PRIV_WIDE_BOLD_ITALIC =   0x0016,
        FONT_TYPE_PRIV_DIGI =               0x0018,
        FONT_TYPE_PRIV_CHINESE =            0x0020,
        FONT_TYPE_PRIV_DUMMY =              0x0028,
        FONT_TYPE_PRIV_SEMIBOLD_NL =        0x0030,
        FONT_TYPE_PRIV_LIGHT =              0x0038,
        FONT_TYPE_PRIV_ARABIC =             0x0040,
        FONT_TYPE_PRIV_HEBREW =             0x0048,
        FONT_TYPE_PRIV_THAI =               0x0050,
        FONT_TYPE_PRIV_SYMB =               0x0058,
        FONT_TYPE_PRIV_GEORGIAN =           0x0060,
        FONT_TYPE_PRIV_ARMENIAN =           0x0068,
        FONT_TYPE_PRIV_ETHIOPIC =           0x0070,
        FONT_TYPE_PRIV_BENGALI =            0x0078,
        FONT_TYPE_PRIV_GUJARATI =           0x0080,
        FONT_TYPE_PRIV_TELUGU =             0x0088,
        FONT_TYPE_PRIV_GURMUKHI =           0x0090,
        FONT_TYPE_PRIV_KANNADA =            0x0098,
        FONT_TYPE_PRIV_MALAYALAM =          0x00A0,
        FONT_TYPE_PRIV_SINHALA =            0x00A8,
        FONT_TYPE_PRIV_TAMIL =              0x00B0,
        FONT_TYPE_PRIV_ORIYA =              0x00B8,
        FONT_TYPE_PRIV_KHMER =              0x00C0,
        FONT_TYPE_PRIV_DEVANAGARI =         0x00C8,
        // Bitmap font types
        FONT_TYPE_PRIV_PLAIN =              0x00D0,
        FONT_TYPE_PRIV_PLAIN_ITALIC =       0x00D8,
        FONT_TYPE_PRIV_C_L =                0x00E0,
        FONT_TYPE_PRIV_MUSIC =              0x00E8,
        FONT_TYPE_PRIV_NORM =               0x00F0,
        FONT_TYPE_PRIV_STRIKE_THROUGH =     0x00F8,
        // Special cases
        FONT_TYPE_PRIV_BOLD =               0x0002,
        FONT_TYPE_PRIV_ITALIC =             0x0004,
        FONT_TYPE_PRIV_BOLD_ITALIC =        0x0006,
    }

    //-----------------------------------------------------------------------
    //Constant Table: Font bit masks (defined in font_priv.h)                                       
    //-----------------------------------------------------------------------
    public enum FontBitMasks : byte
    {
        FONT_IS_ANTIALIASED_FONT = (1 << 0),
        FONT_IS_BOLD_FONT = (1 << 1),
        FONT_IS_ITALIC_FONT = (1 << 2),
    }


    public class GlobalTokens
    {
        private Dictionary<byte, GraniteWbxmlGlobals> tokenDictionary = new Dictionary<byte, GraniteWbxmlGlobals>();

        public GlobalTokens()
        {
            foreach (GraniteWbxmlGlobals token in Enum.GetValues(typeof(GraniteWbxmlGlobals)))
            {
                tokenDictionary.Add((byte)token, token);
            }
        }

        public bool Contains(byte keyValue)
        {
            return tokenDictionary.ContainsKey(keyValue);
        }

        public GraniteWbxmlGlobals GetToken(byte byteValue)
        {
            return tokenDictionary[byteValue];
        }
    }

    public class GraniteTokens
    {
        private Dictionary<byte, GraniteWbxmlTags> tokenDictionary = new Dictionary<byte, GraniteWbxmlTags>();

        public GraniteTokens()
        {
            foreach (GraniteWbxmlTags token in Enum.GetValues(typeof(GraniteWbxmlTags)))
            {
                tokenDictionary.Add((byte)token, token);
            }
        }

        public bool Contains(byte keyValue)
        {
            return tokenDictionary.ContainsKey(keyValue);
        }

        public bool Contains(string name)
        {
            GraniteWbxmlTags temp;
            return Enum.TryParse<GraniteWbxmlTags>("GRN_WBXML_TAG_" + name, out temp);
        }

        public GraniteWbxmlTags GetToken(byte byteValue)
        {
            return tokenDictionary[byteValue];
        }

        public string GetTokenString(byte byteValue)
        {
            return tokenDictionary[byteValue].ToString().Replace("GRN_WBXML_TAG_", "");
        }

        public byte GetByte(string name)
        {
            GraniteWbxmlTags temp;
            if (Enum.TryParse<GraniteWbxmlTags>("GRN_WBXML_TAG_" + name, out temp))
            {
                return (byte)temp;
            }

            throw new Exception("No match for " + name);
        }        
    }

    public class GraniteAttributeLabels
    {
        private Dictionary<byte, GraniteWbxmlAttrLabels> tokenDictionary = new Dictionary<byte, GraniteWbxmlAttrLabels>();

        public GraniteAttributeLabels()
        {
            foreach (GraniteWbxmlAttrLabels token in Enum.GetValues(typeof(GraniteWbxmlAttrLabels)))
            {
                tokenDictionary.Add((byte)token, token);
            }
        }

        public bool Contains(byte keyValue)
        {
            return tokenDictionary.ContainsKey(keyValue);
        }

        public bool Contains(string name)
        {
            GraniteWbxmlAttrLabels temp;
            return Enum.TryParse<GraniteWbxmlAttrLabels>("GRN_WBXML_ATTR_" + name, out temp);
        }

        public GraniteWbxmlAttrLabels GetToken(byte byteValue)
        {
            return tokenDictionary[byteValue];
        }

        public string GetTokenString(byte byteValue)
        {
            return tokenDictionary[byteValue].ToString().Replace("GRN_WBXML_ATTR_", "");
        }

        public byte GetByte(string name)
        {
            GraniteWbxmlAttrLabels temp;
            if (Enum.TryParse<GraniteWbxmlAttrLabels>("GRN_WBXML_ATTR_" + name, out temp))
            {
                return (byte)temp;
            }

            throw new Exception("No match for " + name);
        }
    }

    public class GraniteAttributeValues
    {
        private Dictionary<byte, GraniteWbxmlAttrValues> tokenDictionary = new Dictionary<byte, GraniteWbxmlAttrValues>();

        public GraniteAttributeValues()
        {
            foreach (GraniteWbxmlAttrValues token in Enum.GetValues(typeof(GraniteWbxmlAttrValues)))
            {
                tokenDictionary.Add((byte)token, token);
            }
        }

        public bool Contains(byte keyValue)
        {
            return tokenDictionary.ContainsKey(keyValue);
        }

        public bool Contains(string name)
        {
            GraniteWbxmlAttrValues temp;
            return Enum.TryParse<GraniteWbxmlAttrValues>("GRN_WBXML_ATTR_VALUE_" + name, out temp);
        }

        public GraniteWbxmlAttrValues GetToken(byte byteValue)
        {
            return tokenDictionary[byteValue];
        }

        public string GetTokenString(byte byteValue)
        {
            return tokenDictionary[byteValue].ToString().Replace("GRN_WBXML_ATTR_VALUE_", "");
        }

        public byte GetByte(string name)
        {
            GraniteWbxmlAttrValues temp;
            if (Enum.TryParse<GraniteWbxmlAttrValues>("GRN_WBXML_ATTR_VALUE_" + name, out temp))
            {
                return (byte)temp;
            }

            throw new Exception("No match for " + name);
        }
    }

    public class FontTokens
    {
        private Dictionary<byte, FontNames> nameDictionary = new Dictionary<byte, FontNames>();
        private Dictionary<byte, FontTypes> typeDictionary = new Dictionary<byte, FontTypes>();
                       
        public FontTokens()
        {
            foreach (FontNames token in Enum.GetValues(typeof(FontNames)))
            {
                nameDictionary.Add((byte)token, token);
            }

            foreach (FontTypes token in Enum.GetValues(typeof(FontTypes)))
            {
                typeDictionary.Add((byte)token, token);
            }
        }
     /*  Java Font constants
     * 
     *  public static final int STYLE_PLAIN = 0;
     *  public static final int STYLE_BOLD = 1;
     *  public static final int STYLE_ITALIC = 2;
     *  public static final int STYLE_UNDERLINED = 4;
     *
     *  public static final int SIZE_SMALL = 8;
     *  public static final int SIZE_MEDIUM = 0;
     *  public static final int SIZE_LARGE = 16;
     * 
     *  public static final int FACE_SYSTEM = 0;
     *  public static final int FACE_MONOSPACE = 32;
     *  public static final int FACE_PROPORTIONAL = 64;
     * 
     *  public static final int FONT_STATIC_TEXT = 0;
     *  public static final int FONT_INPUT_TEXT = 1;
     * 
     */

        public string GetFontName(byte byteValue)
        {
            return "Support";//nameDictionary[byteValue].ToString().Replace("FONT_NAME_PRIV_", "");
        }

        public string GetFontType(byte byteValue)
        {
            return " not implemented yet";// typeDictionary[byteValue].ToString().Replace("FONT_TYPE_PRIV_", "");
        }

        public string GetFontValue(byte byteValue)
        {
            // face<<16 | style<<8 | size

            byte top = (byte)(byteValue >> 16);
            byte low = (byte)(byteValue & 0x0000ffff);

            string fontName = GetFontName(low);
            string fontType = GetFontType((byte)(top & ~((byte)FontBitMasks.FONT_IS_ANTIALIASED_FONT | (byte)FontBitMasks.FONT_IS_BOLD_FONT | (byte)FontBitMasks.FONT_IS_ITALIC_FONT)));

            return fontName + "-" + fontType;
        }
    }
}
