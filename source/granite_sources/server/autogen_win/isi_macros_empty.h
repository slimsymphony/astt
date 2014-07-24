/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                isi_macros_empty.h
                ------------------
                SW Include






Project:          autogen

%name:            isi_macros_empty.h %
%version:         co1tss#49 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Tue May 19 13:28:38 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */
/*  Header file for autogen

    This file defines all the ISI message macros empty.
*/


/* macros related to resource definitions */

#ifndef RES_BEGIN
#define RES_BEGIN(_type, _id, _shortname, _sername, _version, _suppcomm)
#endif

#ifndef RES_END
#define RES_END
#endif

#ifndef RES_COMMENT
#define RES_COMMENT(_type, _comment)
#endif

#ifndef RES_COMMENT_LINK
#define RES_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef RES_VERSION_STRING
#define RES_VERSION_STRING(_Z, _Y)
#endif

#ifndef RES_INCLUDE_SHARED_FILE
#define RES_INCLUDE_SHARED_FILE(_id, _verfrom, _verto)
#endif

#ifndef INCLUDE_SHARED_FILE
#define INCLUDE_SHARED_FILE(_id, _verfrom, _verto)
#endif

#ifndef INCLUDE_SHARED_FILE_COMMENT
#define INCLUDE_SHARED_FILE_COMMENT(_type, _comment)
#endif



#ifndef DEFINE_SERVER_BEGIN
#define DEFINE_SERVER_BEGIN(_id, _sername, _version, _comment)
#endif

#ifndef DEFINE_SERVER_END
#define DEFINE_SERVER_END
#endif

#ifndef DEFINE_COMMON_SERVER_BEGIN
#define DEFINE_COMMON_SERVER_BEGIN(_comment)
#endif

#ifndef SERVER_SET_COMMON_MESSAGE_SUPPORT
#define SERVER_SET_COMMON_MESSAGE_SUPPORT(_supports_comm)
#endif

#ifndef SERVER_SET_SHORT_NAME
#define SERVER_SET_SHORT_NAME(_name)
#endif

#ifndef SERVER_SET_TYPE
#define SERVER_SET_TYPE(_type)
#endif


/* macros related to constant definitions */

#ifndef CONSTANT
#define CONSTANT(_name, _id)
#endif

#ifndef CONSTANT_VER   
#define CONSTANT_VER(_name, _id, _verfrom, _verto)
#endif

#ifndef CONSTANT_COMMENT
#define CONSTANT_COMMENT(_type, _comment)
#endif

#ifndef CONSTANT_COMMENT_LINK
#define CONSTANT_COMMENT_LINK(_type, _name, _subname, _ver)
#endif



/* macros related to constant table definitions */

#ifndef CONST_TBL_BEGIN
#define CONST_TBL_BEGIN(_name, _length, _order, _verfrom, _verto)
#endif

#ifndef CONST_TBL_END
#define CONST_TBL_END
#endif

#ifndef CONST_TBL_COMMENT
#define CONST_TBL_COMMENT(_type, _comment)
#endif

#ifndef CONST_TBL_COMMENT_LINK
#define CONST_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef CONST_TBL_ENTRY
#define CONST_TBL_ENTRY(_name, _id, _comment)
#endif

#ifndef CONST_TBL_ENTRY_VER
#define CONST_TBL_ENTRY_VER(_name, _id, _verfrom, _verto)
#endif

#ifndef CONST_TBL_ENTRY_COMMENT
#define CONST_TBL_ENTRY_COMMENT(_type, _comment)
#endif

#ifndef CONST_TBL_ENTRY_COMMENT_LINK
#define CONST_TBL_ENTRY_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef DER_CONST_TBL_BEGIN
#define DER_CONST_TBL_BEGIN(_name, _consttblname, _verfrom, _verto)
#endif

#ifndef DER_CONST_TBL_END
#define DER_CONST_TBL_END
#endif

#ifndef DER_CONST_TBL_ENTRY
#define DER_CONST_TBL_ENTRY(_constname)
#endif

#ifndef DER_CONST_TBL_ENTRY_VER
#define DER_CONST_TBL_ENTRY_VER(_constname, _verfrom, _verto)
#endif

#ifndef DEFINE_CONST_TBL_BEGIN
#define DEFINE_CONST_TBL_BEGIN(_name, _length, _order, _comment)
#endif

#ifndef DEFINE_CONST_TBL_END
#define DEFINE_CONST_TBL_END
#endif
   

/* macros related to bit table definitions */

#ifndef BIT_TBL_BEGIN
#define BIT_TBL_BEGIN(_name, _length, _order, _verfrom, _verto)
#endif

#ifndef BIT_TBL_END
#define BIT_TBL_END
#endif

#ifndef BIT_TBL_COMMENT
#define BIT_TBL_COMMENT(_type, _comment)
#endif

#ifndef BIT_TBL_COMMENT_LINK
#define BIT_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef BIT_TBL_ENTRY
#define BIT_TBL_ENTRY(_bits, _bitname, _comment)
#endif

#ifndef BIT_TBL_ENTRY_VER
#define BIT_TBL_ENTRY_VER(_bits, _bitname, _verfrom, _verto)
#endif

#ifndef BIT_TBL_ENTRY_COMMENT
#define BIT_TBL_ENTRY_COMMENT(_type, _comment)
#endif

#ifndef DER_BIT_TBL_BEGIN
#define DER_BIT_TBL_BEGIN(_name, _bittblname, _verfrom, _verto)
#endif

#ifndef DER_BIT_TBL_END
#define DER_BIT_TBL_END
#endif

#ifndef DER_BIT_TBL_ENTRY
#define DER_BIT_TBL_ENTRY(_constname)
#endif

#ifndef DER_BIT_TBL_ENTRY_VER
#define DER_BIT_TBL_ENTRY_VER(_constname, _verfrom, _verto)
#endif

#ifndef DEFINE_BIT_TBL_BEGIN
#define DEFINE_BIT_TBL_BEGIN(_name, _length, _order, _comment)
#endif
   
#ifndef DEFINE_BIT_TBL_END
#define DEFINE_BIT_TBL_END
#endif


/* macros related to FTD table definitions */

#ifndef FTD_TBL_BEGIN
#define FTD_TBL_BEGIN(_verfrom, _verto)
#endif

#ifndef FTD_TBL_END
#define FTD_TBL_END
#endif

#ifndef FTD_TBL_COMMENT
#define FTD_TBL_COMMENT(_type, _comment)
#endif

#ifndef FTD_TBL_COMMENT_LINK
#define FTD_TBL_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef FTD_TBL_ENTRY_CONST
#define FTD_TBL_ENTRY_CONST(_name, _id, _tblname, _comment)
#endif

#ifndef FTD_TBL_ENTRY_CONST_VER
#define FTD_TBL_ENTRY_CONST_VER(_name, _id, _tblname, _verfrom, _verto)
#endif

#ifndef FTD_TBL_ENTRY_STRING
#define FTD_TBL_ENTRY_STRING(_name, _id, _unit, _comment)
#endif

#ifndef FTD_TBL_ENTRY_STRING_VER
#define FTD_TBL_ENTRY_STRING_VER(_name, _id, _unit, _verfrom, _verto)
#endif

#ifndef FTD_STRING
#define FTD_STRING(_name, _id, _parname, _verfrom, _verto)
#endif

#ifndef FTD_TBL_ENTRY_TABLE
#define FTD_TBL_ENTRY_TABLE(_name, _id, _length, _pres, _unit, _comment)
#endif

#ifndef FTD_TABLE_BEGIN
#define FTD_TABLE_BEGIN(_name, _id, _verfrom, _verto)
#endif

#ifndef FTD_TABLE_END
#define FTD_TABLE_END
#endif

#ifndef FTD_TBL_ENTRY_TABLE_VER
#define FTD_TBL_ENTRY_TABLE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto)
#endif

#ifndef FTD_TBL_ENTRY_TABLE_CONST
#define FTD_TBL_ENTRY_TABLE_CONST(_name, _id, _tblname)
#endif

#ifndef FTD_TBL_ENTRY_TEST
#define FTD_TBL_ENTRY_TEST(_name, _id)
#endif

#ifndef FTD_TBL_ENTRY_TEST_VER
#define FTD_TBL_ENTRY_TEST_VER(_name, _id, _verfrom, _verto)
#endif

#ifndef FTD_TBL_ENTRY_VALUE
#define FTD_TBL_ENTRY_VALUE(_name, _id, _length, _pres, _unit, _comment)
#endif

#ifndef FTD_VALUE_BEGIN
#define FTD_VALUE_BEGIN(_name, _id, _verfrom, _verto)
#endif

#ifndef FTD_VALUE_END
#define FTD_VALUE_END
#endif

#ifndef FTD_TBL_ENTRY_VALUE_VER
#define FTD_TBL_ENTRY_VALUE_VER(_name, _id, _length, _pres, _unit, _verfrom, _verto)
#endif

#ifndef FTD_TBL_ENTRY_COMMENT
#define FTD_TBL_ENTRY_COMMENT(_type, _comment)
#endif

#ifndef FTD_TBL_ENTRY_END
#define FTD_TBL_ENTRY_END
#endif

/* macros related to PPC table definitions */

#ifndef PPC_TBL_BEGIN
#define PPC_TBL_BEGIN(_verfrom, _verto)
#endif
   
#ifndef PPC_TBL_END
#define PPC_TBL_END
#endif

#ifndef PPC_TBL_ENTRY
#define PPC_TBL_ENTRY(_name, _id, _seqname)
#endif

#ifndef PPC_TBL_ENTRY_VER
#define PPC_TBL_ENTRY_VER(_name, _id, _seqname, _verfrom, _verto)
#endif

#ifndef PPC_TBL_BEGIN
#define PPC_TBL_BEGIN(_verfrom, _verto)
#endif
   
#ifndef PPC_TBL_END
#define PPC_TBL_END
#endif

#ifndef PPC_TBL_ENTRY
#define PPC_TBL_ENTRY(_name, _id, _seqname)
#endif

#ifndef PPC_TBL_ENTRY_VER
#define PPC_TBL_ENTRY_VER(_name, _id, _seqname, _verfrom, _verto)
#endif


/* macros related to place holder sections */

#ifndef MSG_ID_SECTION
#define MSG_ID_SECTION
#endif

#ifndef SB_ID_SECTION
#define SB_ID_SECTION
#endif


/* macros related to ISI version history definitions */

#ifndef ISI_VERSION_HISTORY
#define ISI_VERSION_HISTORY(_version)
#endif

#ifndef ISI_VERSION_COMMENT
#define ISI_VERSION_COMMENT(_type, _comment)
#endif

/* macros related to note definitions */

#ifndef NOTE
#define NOTE(_name)
#endif

#ifndef NOTE_COMMENT
#define NOTE_COMMENT(_type, _comment)
#endif


/* macros related to message definitions */

#ifndef MSG_BEGIN
#define MSG_BEGIN(_id, _type, _verfrom, _verto)
#endif

#ifndef MSG_END
#define MSG_END
#endif

#ifndef MSG_PAIR
#define MSG_PAIR(_reqmsgname, _respmsgname)
#endif

#ifndef MSG_PAIR_EXT
#define MSG_PAIR_EXT(_reqmsgname, _respmsgname, _resname)
#endif

#ifndef MSG_PAIR_VER
#define MSG_PAIR_VER(_reqmsgname, _respmsgname, _verfrom, _verto)
#endif

#ifndef MSG_PAIR_EXT_VER
#define MSG_PAIR_EXT_VER(_reqmsgname, _respmsgname, _resname, _verfrom, _verto)
#endif

#ifndef MSG_COMMENT
#define MSG_COMMENT(_type, _comment)
#endif

#ifndef MSG_COMMENT_LINK
#define MSG_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef MSG_ID_COMMENT
#define MSG_ID_COMMENT(_type, _comment)
#endif

#ifndef SUB_MSG_BEGIN
#define SUB_MSG_BEGIN(_subid, _id, _type, _verfrom, _verto)
#endif

#ifndef SUB_MSG_END
#define SUB_MSG_END
#endif

#ifndef SUB_MSG_PAIR
#define SUB_MSG_PAIR(_reqsubmsgname, _reqmsgname, _respsubmsgname, _respmsgname)
#endif

#ifndef SUB_MSG_PAIR_VER
#define SUB_MSG_PAIR_VER(_reqsubmsgname, _reqmsgname, _respsubmsgname, _respmsgname, _verfrom, _verto)
#endif

#ifndef SUB_MSG_COMMENT
#define SUB_MSG_COMMENT(_type, _comment)
#endif

#ifndef SUB_MSG_COMMENT_LINK
#define SUB_MSG_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef DEFINE_MSG_BEGIN
#define DEFINE_MSG_BEGIN(_id, _verfrom, _verto, _comment)
#endif

#ifndef DEFINE_MSG_END
#define DEFINE_MSG_END
#endif

#ifndef DEFINE_SUB_MSG_BEGIN
#define DEFINE_SUB_MSG_BEGIN(_id, _subid, _verfrom, _verto, _comment)
#endif

#ifndef DEFINE_SUB_MSG_END
#define DEFINE_SUB_MSG_END
#endif

#ifndef DEFINE_MSG_PAIR
#define DEFINE_MSG_PAIR(_reqmsgname, _respmsgname)
#endif

#ifndef MSG_SET_TYPE
#define MSG_SET_TYPE(_type)
#endif


/* sub block related macros */

#ifndef SB_BEGIN
#define SB_BEGIN(_id, _verfrom, _verto)
#endif

#ifndef SB_END
#define SB_END
#endif

#ifndef DEFINE_SB_BEGIN
#define DEFINE_SB_BEGIN(_id, _verfrom, _verto, _comment)
#endif

#ifndef DEFINE_SB_END
#define DEFINE_SB_END
#endif

#ifndef SB_COMMENT
#define SB_COMMENT(_type, _comment)
#endif

#ifndef SB_COMMENT_LINK
#define SB_COMMENT_LINK(_type, _name, _subname, _ver)
#endif


/* macros related to sequence definitions */

#ifndef SEQ_BEGIN
#define SEQ_BEGIN(_name, _createstruct, _verfrom, _verto)
#endif
   
#ifndef SEQ_END
#define SEQ_END
#endif

#ifndef SEQ_COMMENT
#define SEQ_COMMENT(_type, _comment)
#endif

#ifndef SEQ_COMMENT_LINK
#define SEQ_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef DEFINE_SEQ_BEGIN
#define DEFINE_SEQ_BEGIN(_name, _createstruct, _comment)
#endif

#ifndef DEFINE_SEQ_END
#define DEFINE_SEQ_END
#endif


/* macros related to sequence elements */

#ifndef ITEM_PARAMETER
#define ITEM_PARAMETER
#endif

#ifndef PARAMETER
#define PARAMETER(_name, _desc)
#endif

#ifndef ITEM_LIMITS
#define ITEM_LIMITS(_minval, _maxval, _excval1, _excval2, _excval3)
#endif

#ifndef VALUE_LIMITS
#define VALUE_LIMITS(_type, _minval, _maxval, _excval)
#endif

#ifndef ITEM_COMMENT
#define ITEM_COMMENT(_type, _comment)
#endif

#ifndef ITEM_COMMENT_LINK
#define ITEM_COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef ITEM_DEFAULT_VALUE
#define ITEM_DEFAULT_VALUE(_val)
#endif

/* merge sequence elements */

#ifndef MERGE_BEGIN
#define MERGE_BEGIN(_length, _order, _varname, _parname)
#endif
   
#ifndef MERGE_END
#define MERGE_END
#endif

#ifndef DEFINE_MERGE_BEGIN
#define DEFINE_MERGE_BEGIN(_length, _order, _varname, _parname)
#endif
   
#ifndef DEFINE_MERGE_END
#define DEFINE_MERGE_END
#endif

/* constant sequence elements */

#ifndef VALUE_CONST
#define VALUE_CONST(_varname, _parname, _tblname)
#endif

#ifndef VALUE_CONST_IMP
#define VALUE_CONST_IMP(_varname, _parname, _tblname, _resname)
#endif

#ifndef BIT_REF
#define BIT_REF(_varname, _parname, _tblname)
#endif

#ifndef CONST_REF
#define CONST_REF(_varname, _parname, _tblname)
#endif

/* sub block list sequence elements */

#ifndef SB_LST_REF_BEGIN
#define SB_LST_REF_BEGIN(_type, _varname, _parname, _refname, _flag)
#endif

#ifndef SB_LST_REF_END
#define SB_LST_REF_END
#endif
   
#ifndef SB_LST_BEGIN
#define SB_LST_BEGIN(_type, _varname, _parname, _n, _flag)
#endif

#ifndef SB_LST_END
#define SB_LST_END
#endif
   
#ifndef SB_LST_ENTRY
#define SB_LST_ENTRY(_sbname)
#endif

#ifndef SB_LST_ENTRY_VER
#define SB_LST_ENTRY_VER(_sbname, _verfrom, _verto)
#endif

#ifndef SB_LST_ENTRY_NAME
#define SB_LST_ENTRY_NAME(_varname)
#endif

#ifndef DEFINE_SB_LST_BEGIN
#define DEFINE_SB_LST_BEGIN
#endif

#ifndef DEFINE_SB_LST_END
#define DEFINE_SB_LST_END
#endif

/* string sequence elements */

#ifndef STRING
#define STRING(_type, _order, _varname, _parname, _n)
#endif

#ifndef STRING_REF
#define STRING_REF(_type, _order, _varname, _parname, _refname, _flag)
#endif

/* array sequence elements */

#ifndef SEQ_OF
#define SEQ_OF(_varname, _parname, _seqname, _n)
#endif

#ifndef SEQ_OF_REF
#define SEQ_OF_REF(_varname, _parname, _seqname, _refname, _flag)
#endif

#ifndef SB_REF
#define SB_REF(_varname, _parname, _sbname)
#endif

/* reference sequence elemenents */

#ifndef REFERENCE
#define REFERENCE(_length, _order, _varname, _parname, _refname)
#endif

#ifndef REFERENCE_TRANSFORM
#define REFERENCE_TRANSFORM(_oldrefname, _newrefname, _alg, _n)
#endif

#ifndef REFERENCE_CONST
#define REFERENCE_CONST(_varname, _parname, _refname, _tblname)
#endif

/* filler sequence elements */

#ifndef FILLER
#define FILLER(_type, _length)
#endif

#ifndef FILLER_EX
#define FILLER_EX(_varname, _length, _n)
#endif

/* block sequence elements */

#ifndef BLOCK
#define BLOCK(_order, _varname, _parname, _type, _data1, _data2, _data3, _n)
#endif

#ifndef BLOCK_REF
#define BLOCK_REF(_order, _varname, _parname, _type, _data1, _data2, _data3, _refname)
#endif

/* protocol sequence elements */

#ifndef PROTOCOL_REF
#define PROTOCOL_REF(_id, _varname, _parname, _refname, _flag)
#endif

/* printf sequence elements */

#ifndef PRINTF_BEGIN
#define PRINTF_BEGIN(_format)
#endif

#ifndef PRINTF_END
#define PRINTF_END
#endif

/* timestamp sequence elements */

#ifndef TIMESTAMP
#define TIMESTAMP(_length, _order, _varname, _parname, _type)
#endif

/* pointer sequence elements */
/*lint -esym(123,POINTER) POINTER is used as symbol name by other teams*/ 
#ifndef POINTER
#define POINTER(_order, _varname, _parname, _type)
#endif

/* value sequence elements */

#ifndef VALUE
#define VALUE(_length, _order, _varname, _parname, _pres)
#endif

#ifndef VALUE_EX
#define VALUE_EX(_length, _order, _varname, _parname, _pres, _scale, _offset, _unit)
#endif

#ifndef DEFINE_RANGE_FIELD_BEGIN
#define DEFINE_RANGE_FIELD_BEGIN(_length, _order, _varname, _parname)
#endif

/* choice sequence elements */

#ifndef CHOICE_BEGIN
#define CHOICE_BEGIN(_varname, _parname, _refname)
#endif

#ifndef CHOICE_VALUE_BEGIN
#define CHOICE_VALUE_BEGIN(_varname, _parname, _refname)
#endif

#ifndef CHOICE_END
#define CHOICE_END
#endif

#ifndef CHOICE_FORWARD_BEGIN
#define CHOICE_FORWARD_BEGIN(_varname, _parname, _tblname, _relpos)
#endif

#ifndef DEFINE_CHOICE_REF_BEGIN
#define DEFINE_CHOICE_REF_BEGIN(_varname, _parname, _refname)
#endif

#ifndef DEFINE_CHOICE_REF_END
#define DEFINE_CHOICE_REF_END
#endif

#ifndef CASE
#define CASE(_tagname, _seqname)
#endif

#ifndef CASE_BEGIN
#define CASE_BEGIN(_tagname, _verfrom, _verto)
#endif

#ifndef CASE_END
#define CASE_END
#endif

#ifndef CASE_VER
#define CASE_VER(_tagname, _seqname, _verfrom, _verto)
#endif

#ifndef CASE_DEFAULT
#define CASE_DEFAULT(_seqname)
#endif

#ifndef DEFAULT_BEGIN
#define DEFAULT_BEGIN(_verfrom, _verto)
#endif

#ifndef DEFAULT_END
#define DEFAULT_END
#endif


/* trace related macros */
#ifndef TRACE_GROUP_BEGIN
#define TRACE_GROUP_BEGIN(_grpname, _dectext, _state)
#endif

#ifndef TRACE_GROUP_END
#define TRACE_GROUP_END()
#endif

#ifndef TRACE_GROUP_DECODER
#define TRACE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags, _state)
#endif

#ifndef TRACE_BEGIN
#define TRACE_BEGIN(_trcname, _dectext)
#endif

#ifndef TRACE_END
#define TRACE_END()
#endif

#ifndef TRACE_ID
#define TRACE_ID(_trcname, _dectext)
#endif

#ifndef MCU_TRACE_GROUP_BEGIN
#define MCU_TRACE_GROUP_BEGIN(_grpname, _dectext, _state)
#endif

#ifndef MCU_TRACE_GROUP_END
#define MCU_TRACE_GROUP_END()
#endif

#ifndef MON_TRACE_GROUP_TBL_BEGIN
#define MON_TRACE_GROUP_TBL_BEGIN(_tblname)
#endif

#ifndef MON_TRACE_GROUP_TBL_END
#define MON_TRACE_GROUP_TBL_END()
#endif

#ifndef MON_TRACE_DEFINE_GROUP_ID
#define MON_TRACE_DEFINE_GROUP_ID(_grpname, _dectext)
#endif

#ifndef MON_TRACE_DEFINE_GROUP_ID_FIXED
#define MON_TRACE_DEFINE_GROUP_ID_FIXED(_grpname, _id, _dectext)
#endif

#ifndef MON_TRACE_GROUP_BEGIN
#define MON_TRACE_GROUP_BEGIN(_varname, _grpname, _dectext)
#endif

#ifndef MON_TRACE_GROUP_END
#define MON_TRACE_GROUP_END()
#endif

#ifndef MON_TRACE_ID_TBL_BEGIN
#define MON_TRACE_ID_TBL_BEGIN(_varname, _grpname)
#endif

#ifndef MON_TRACE_ID_TBL_END
#define MON_TRACE_ID_TBL_END()
#endif

#ifndef MON_TRACE_DEFINE_ID
#define MON_TRACE_DEFINE_ID(_trcname, _dectext, _func)
#endif

#ifndef MON_TRACE_DEFINE_ID_BEGIN
#define MON_TRACE_DEFINE_ID_BEGIN(_trcname, _dectext)
#endif

#ifndef MON_TRACE_DEFINE_ID_END
#define MON_TRACE_DEFINE_ID_END()
#endif

#ifndef MON_TRACE_DEFINE_ID_FIXED
#define MON_TRACE_DEFINE_ID_FIXED(_trcname, _dectext, _func, _grp, _id)
#endif

#ifndef MON_TRACE_DEFINE_ID_FIXED_BEGIN
#define MON_TRACE_DEFINE_ID_FIXED_BEGIN(_trcname, _dectext, _grp, _id)
#endif

#ifndef MON_TRACE_ID_COMMENT
#define MON_TRACE_ID_COMMENT(_type, _comment)
#endif

#ifndef MON_TRACE_LOGICAL_GROUP_BEGIN
#define MON_TRACE_LOGICAL_GROUP_BEGIN(_logname, _logdesc)
#endif

#ifndef MON_TRACE_LOGICAL_GROUP_END
#define MON_TRACE_LOGICAL_GROUP_END()
#endif

#ifndef MON_TRACE_DEFINE_GROUP_DECODER
#define MON_TRACE_DEFINE_GROUP_DECODER(_grpname, _dllname, _dllfunc, _flags)
#endif

#ifndef MON_TRACE_ID_TBL_COMMENT
#define MON_TRACE_ID_TBL_COMMENT(_type, _comment)
#endif


/* general macros */

#ifndef COMMENT
#define COMMENT(_comment, _type)
#endif

#ifndef COMMENT_PROPERTY
#define COMMENT_PROPERTY(_type)
#endif

#ifndef COMMENT_LINK
#define COMMENT_LINK(_type, _name, _subname, _ver)
#endif

#ifndef PROPERTY
#define PROPERTY(_type)
#endif

#ifndef PROPERTY_STRING
#define PROPERTY_STRING(_type, _value)
#endif

#ifndef PROPERTY_STRING_INDEX
#define PROPERTY_STRING_INDEX(_type, _index, _value)
#endif

#ifndef PROPERTY_VALUE
#define PROPERTY_VALUE(_type, _value)
#endif

#ifndef PROPERTY_VALUE_INDEX
#define PROPERTY_VALUE_INDEX(_type, _index, _value)
#endif

/* feature flag macros */

#ifndef FEATURE_FLAG_DEFINED 
#define FEATURE_FLAG_DEFINED(_flag, _value)
#endif

#ifndef FEATURE_FLAG_DEFINED_OR_DEFINED 
#define FEATURE_FLAG_DEFINED_OR_DEFINED(_flag1, _value1, _flag2, _value2)
#endif

#ifndef FEATURE_FLAG_DEFINED_AND_DEFINED 
#define FEATURE_FLAG_DEFINED_AND_DEFINED(_flag1, _value1, _flag2, _value2)
#endif

#ifndef FEATURE_FLAG_ELSE
#define FEATURE_FLAG_ELSE()
#endif

#ifndef FEATURE_FLAG_END
#define FEATURE_FLAG_END()
#endif

/* unsupported macros */

#ifndef DEFINE_BCD_TBL_BEGIN
#define DEFINE_BCD_TBL_BEGIN(_name, _comment)
#endif
   
#ifndef DEFINE_BCD_TBL_END
#define DEFINE_BCD_TBL_END
#endif

#ifndef BCD_TBL_ENTRY
#define BCD_TBL_ENTRY(_index, _value)
#endif

#ifndef BCD_REF_ENTRY
#define BCD_REF_ENTRY(_n, _varname, _parname)
#endif

#ifndef DEFINE_RANGE_FIELD_END
#define DEFINE_RANGE_FIELD_END
#endif

#ifndef RANGE_ENTRY_STRING
#define RANGE_ENTRY_STRING(_from, _to, _text)
#endif

#ifndef RANGE_ENTRY_VALUE
#define RANGE_ENTRY_VALUE(_from, _to, _pres)
#endif

#ifndef RANGE_ENTRY_VALUE_EX
#define RANGE_ENTRY_VALUE_EX(_from, _to, _scale, _offset, _unit, _pres)
#endif


/* short-cut macros */

#ifndef COMMON_MSG_HDR
#define COMMON_MSG_HDR
#endif

#ifndef COMMON_MSG_REQ
#define COMMON_MSG_REQ
#endif

#ifndef COMMON_MSG_RESP
#define COMMON_MSG_RESP
#endif

#ifndef COMMON_MSG_IND
#define COMMON_MSG_IND
#endif

#ifndef COMMON_MSG_NTF
#define COMMON_MSG_NTF
#endif

#ifndef COMMON_SB
#define COMMON_SB
#endif

#ifndef COMMON_SB_LONG
#define COMMON_SB_LONG
#endif

#ifndef COMMON_SB_16
#define COMMON_SB_16
#endif

#ifndef COMMON_SB_16_LONG
#define COMMON_SB_16_LONG
#endif

#ifndef COMMON_SUB_MSG_HDR
#define COMMON_SUB_MSG_HDR
#endif


/* L1NUTS macros*/

#ifndef COMMON_ISI_HDR_16
#define COMMON_ISI_HDR_16
#endif
  
#ifndef COMMON_ISI_HDR_16_REF
#define COMMON_ISI_HDR_16_REF
#endif

#ifndef COMMON_ISI_HDR
#define COMMON_ISI_HDR
#endif

#ifndef COMMON_ISI_HDR_REF
#define COMMON_ISI_HDR_REF
#endif
  
#ifndef COMMON_MSG_HDR_16
#define COMMON_MSG_HDR_16
#endif

#ifndef FILLER_16
#define FILLER_16
#endif

#ifndef FILLER_16_2
#define FILLER_16_2
#endif
        
#ifndef COMMON_MSG_REQ_16
#define COMMON_MSG_REQ_16
#endif
	
#ifndef COMMON_MSG_RESP_16
#define COMMON_MSG_RESP_16
#endif
	
#ifndef COMMON_MSG_IND_16
#define COMMON_MSG_IND_16
#endif
 
#ifndef COMMON_SB_WORD
#define COMMON_SB_WORD
#endif

#ifndef COMMON_SB_LONG_WORD
#define COMMON_SB_LONG_WORD
#endif

#ifndef COMMON_SB_ID16
#define COMMON_SB_ID16
#endif

#ifndef COMMON_SB_WORD_ID16
#define COMMON_SB_WORD_ID16
#endif

/* End of file isi_macros_empty.h */
