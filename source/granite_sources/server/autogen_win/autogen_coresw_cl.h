/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_coresw_cl.h
                -------------------
                SW Include






Project:          autogen

%name:            autogen_coresw_cl.h %
%version:         co1tss#26 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Nov 24 12:17:22 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes all released CoreSW/CL message definition files
*/

#if (ICF_CL == ON)
 #include "cm_isi_m.h"
 #include "pn_name_isi_m.h"
 #include "pn_pipe_isi_m.h"
 #include "pn_media_isi_m.h"

 #include "autogen_alive.h"
 #include "autogen_registration.h"
 #include "autogen_router.h"

#endif /* ICF_CL == ON */


#if (ICF_PN_MEDIA_FBUS == ON)
 #include "mm_fbus_m.h"
#else
 printf("* ICF_PN_MEDIA_FBUS is OFF. Excluding 'mm_fbus_m.h'\n");
#endif /* ICF_PN_MEDIA_FBUS == ON */


#if (ICF_PN_MEDIA_STI == ON)
 #include "mm_sti_m.h"
#else
 printf("* ICF_PN_MEDIA_STI is OFF. Excluding 'mm_sti_m.h'\n");
#endif /* ICF_PN_MEDIA_STI == ON */


#if (ICF_PN_MEDIA_XTI == ON)
/*
As long as XTI used media PN_MEDIA_STI, this should not be included!
#include "mm_xti_m.h"
*/
#endif /* ICF_PN_MEDIA_XTI == ON */


#if (ICF_PN_MEDIA_MDI == ON)
 #include "mm_mdi_m.h"
#else
 printf("* ICF_PN_MEDIA_MDI is OFF. Excluding 'mm_mdi_m.h'\n");
#endif /* ICF_PN_MEDIA_MDI == ON */


#if (ICF_PN_MEDIA_USB == ON)
 #include "mm_usb_m.h"
#else
 printf("* ICF_PN_MEDIA_USB is OFF. Excluding 'mm_usb_m.h'\n");
#endif /* ICF_PN_MEDIA_USB == ON */


#if (ICF_PN_MEDIA_I2C == ON)
 #include "mm_i2c_m.h"
#else
 printf("* ICF_PN_MEDIA_I2C is OFF. Excluding 'mm_i2c_m.h'\n");
#endif /* ICF_PN_MEDIA_I2C == ON */


#if (ICF_PN_MEDIA_BT == ON)
 #include "mm_bt_m.h"
#else
 printf("* ICF_PN_MEDIA_BT is OFF. Excluding 'mm_bt_m.h'\n");
#endif /* ICF_PN_MEDIA_BT == ON */


#if (ICF_PN_MEDIA_IRDA == ON)
 #include "irda_isi_m.h" 
#else
 printf("* ICF_PN_MEDIA_IR is OFF. Excluding 'mm_irda_m.h'\n");
#endif /* ICF_PN_MEDIA_IR == ON */


#if (ICF_PN_MEDIA_SOS_USB == ON)
 #include "sos_usb_isi_m.h" 
#else
 printf("* ICF_PN_MEDIA_SOS_USB is OFF. Excluding 'sos_usb_isi_m.h'\n");
#endif /* ICF_PN_MEDIA_SOS_USB == ON */


#if (PN_DEFAULT_MM_IN_USE == ON)
 #include "mm_default_m.h"
#else
 printf("* PN_DEFAULT_MM_IN_USE is OFF. Excluding 'mm_default_m.h'\n");
#endif /* PN_DEFAULT_MM_IN_USE == ON */


/* end of file autogen_coresw_cl.h */
