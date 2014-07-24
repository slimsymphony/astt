/*
NOKIA MOBILE PHONES
R&D Copenhagen
TSS









                autogen_error_info.h
                --------------------

                SW Include






Status:           DRAFT

Continuus DB:     co_pctls

Project:          autogen

%name:            autogen_error_info.h %

%version:         2 %

%instance:        co_pctls_1 %

%derived_by:      cjhansen %

%date_modified:   Wed Nov 26 16:41:27 2003 %

Copyright (c) 2003. Nokia Corporation. All rights reserved


Change history:

VERSION     : 2          DRAFT        26-Nov-2003  Christian J. Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added more contents to file

VERSION     : 1          DRAFT        26-Nov-2003  Christian J. Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : First version of the file
*/

/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains definitions for the PN_ERROR_INFO resource.
    To be used until file is officially made and released
*/

RES_BEGIN(RESOURCE_PHONET_EXT, PN_ERROR_INFO, ERROR_INFO, "Error info", "", FALSE)

    SEQ_BEGIN(ERROR_INFO_DATA, DONT_CREATE_STRUCT, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, data, "Data", HEX)
    SEQ_END

    /* --------------------------------------------------------------------- */
    /* Messages */
    /* --------------------------------------------------------------------- */

#ifdef PNS_FAIL_REGISTRATION
    MSG_BEGIN(PNS_FAIL_REGISTRATION, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, device_type, "Device type", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE(8, BE, reg_type, "Registration type", HEX)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media", PN_MEDIA)
    MSG_END
#endif /* PNS_FAIL_REGISTRATION */

#ifdef PNS_FAIL_SYSTEM_REQ
    MSG_BEGIN(PNS_FAIL_SYSTEM_REQ, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
    MSG_END
#endif /* PNS_FAIL_SYSTEM_REQ */

#ifdef PNS_FAIL_FUNCTION_ROUTING
    MSG_BEGIN(PNS_FAIL_FUNCTION_ROUTING, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
    MSG_END
#endif /* PNS_FAIL_FUNCTION_ROUTING */

#ifdef PNS_FAIL_OBJECT_ROUTING
    MSG_BEGIN(PNS_FAIL_OBJECT_ROUTING, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
    MSG_END
#endif /* PNS_FAIL_OBJECT_ROUTING */

#ifdef PNS_FAIL_MSG_SENDING
    MSG_BEGIN(PNS_FAIL_MSG_SENDING, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
        SEQ_OF_REF(data, "Data", ERROR_INFO_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END
#endif /* PNS_FAIL_MSG_SENDING */

#ifdef PNS_FAIL_DEV_INACTIVE
    MSG_BEGIN(PNS_FAIL_DEV_INACTIVE, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
        SEQ_OF_REF(data, "Data", ERROR_INFO_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END
#endif /* PNS_FAIL_DEV_INACTIVE */

#ifdef PNS_FAIL_OS_MBX_FULL
    MSG_BEGIN(PNS_FAIL_OS_MBX_FULL, MESSAGE_IND, "", "")
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(resource, "Requested resource", PN_RESOURCE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(device, "Requesting device", PN_DEVICE)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(object, "Requesting object", PN_OBJECT)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        VALUE_CONST(media, "Media used", PN_MEDIA)
        SEQ_OF_REF(data, "Data", ERROR_INFO_DATA, REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
    MSG_END
#endif /* PNS_FAIL_OS_MBX_FULL */

RES_END

/* End of file autogen_error_info.h */
