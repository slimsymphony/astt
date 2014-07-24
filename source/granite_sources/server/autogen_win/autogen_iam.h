/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_iam.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_iam.h %
%version:         co1tss#51 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Mar 09 09:30:25 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes IAM message definition files
*/

#ifdef PN_OBJ_APPL_RM_SERVER
 #include "appl_rm_isi_m.h"
#else
 printf("* PN_OBJ_APPL_RM_SERVER not in product. Excluding 'appl_rm_isi_m.h'\n");
#endif /* PN_OBJ_APPL_RM_SERVER */

#ifdef PN_OBJ_AT_APPL_SRV
 #include "at_appl_isi_m.h"
#else
 printf("* PN_OBJ_AT_APPL_SRV not in product. Excluding 'at_appl_isi_m.h'\n");
#endif /* PN_OBJ_AT_APPL_SRV */


#ifdef PN_OBJ_ART_SERV
 #include "srvart_isi_m.h"
#else
 printf("* PN_OBJ_ART_SERV not in product. Excluding 'srvart_isi_m.h'\n");
#endif /* PN_OBJ_ART_SERV */

#ifdef PN_OBJ_BACKUP_SERV
 #include "backup_isi_m.h"
#else
 printf("* PN_OBJ_BACKUP_SERV not in product. Excluding 'backup_isi_m.h'\n");
#endif /* PN_OBJ_BACKUP_SERV */


#ifdef PN_OBJ_BLUETOOTH_SERV
 #include "bt_isi_m.h"
#else
 printf("* PN_OBJ_BLUETOOTH_SERV not in product. Excluding 'bt_isi_m.h'\n");
#endif /* PN_OBJ_BLUETOOTH_SERV */


#ifdef PN_OBJ_CLDR_SERV
 #include "cldr_isi_m.h"
#else
 printf("* PN_OBJ_CLDR_SERV not in product. Excluding 'cldr_isi_m.h'\n");
#endif /* PN_OBJ_CLDR_SERV */


#ifdef PN_OBJ_CMT_SERV
 #include "cmt_isi_m.h"
#else
 printf("* PN_OBJ_CMT_SERV not in product. Excluding 'cmt_isi_m.h'\n");
#endif /* PN_OBJ_CMT_SERV */


#ifdef PN_OBJ_CONTENT_DISPATCH_SERV
 #include "ContDisp_Isi_m.h"
#else
 printf("* PN_OBJ_CONTENT_DISPATCH_SERV not in product. Excluding 'ContDisp_Isi_m.h'\n");
#endif /* PN_OBJ_CONTENT_DISPATCH_SERV */


#ifdef PN_OBJ_CUSTOM_IDLE_SERV
 #include "custom_idle_m.h"
#else
 printf("* PN_OBJ_CUSTOM_IDLE_SERV not in product. Excluding 'custom_idle_m.h'\n");
#endif /* PN_OBJ_CUSTOM_IDLE_SERV */


#ifdef PRODUCT_INCLUDES_DRCORE_SERVER 
 #include "drcore_isi_m.h"
#else
 printf("* PRODUCT_INCLUDES_DRCORE_SERVER not in product. Excluding 'drcore_isi_m.h'\n");
#endif


#ifdef PRODUCT_INCLUDES_FLASHLITE
 #include "flashlite_private_isi_m.h"
#else
 printf("* PRODUCT_INCLUDES_FLASHLITE not in product. Excluding 'flashlite_private_isi_m.h'\n");
#endif /* PRODUCT_INCLUDES_FLASHLITE */


#ifdef PN_OBJ_GARBAGE_SERV
 #include "autogen_garbage.h"
#else
 printf("* PN_OBJ_GARBAGE_SERV not in product. Excluding 'autogen_garbage.h'\n");
#endif /* PN_OBJ_GARBAGE_SERV */


#ifdef PN_OBJ_HELP_APPL
 #include "autogen_help.h"
#else
 printf("* PN_OBJ_HELP_APPL not in product. Excluding 'autogen_help.h'\n");
#endif /* PN_OBJ_HELP_APPL */


#ifdef PN_OBJ_HTTPSRV_SERV
 #include "httpsrv_isi_m.h"
#else
 printf("* PN_OBJ_HTTPSRV_SERV is not in product. Excluding 'httpsrv_isi_m.h'\n");
#endif /* PN_OBJ_HTTPSRV_SERV */


#ifdef PN_OBJ_HTTP_SERV
 #include "http_isi_m.h"
#else
 printf("* PN_OBJ_HTTP_SERV is not in product. Excluding 'http_isi_m.h'\n");
#endif /* IPN_OBJ_HTTP_SERV */


#ifdef PN_OBJ_IMS_SERV
 #include "ims_isi_m.h"
#else
 printf("* PN_OBJ_IMS_SERV is not defined. Excluding 'ims_isi_m.h'\n");
#endif /* PN_OBJ_IMS_SERV */

#ifdef PN_OBJ_IPC_SERV
 #include "ipc_isi_m.h"
 #include "ipc_internal_msg_m.h"
#else
 printf("* PN_OBJ_IPC_SERV is not defined. Excluding 'ipc_isi_m.h'\n");
 printf("* PN_OBJ_IPC_SERV is not defined. Excluding 'ipc_internal_msg_m.h'\n");
#endif /* PN_OBJ_IPC_SERV */


#ifdef PN_OBJ_ISA_SETTINGS_SERV
 #include "isa_settings_isi_m.h"
#else
 printf("* PN_OBJ_ISA_SETTINGS_SERV not in product. Excluding 'isa_settings_isi_m.h'\n");
#endif /* PN_OBJ_ISA_SETTINGS_SERV */





/*  End of file autogen_iam.h */
