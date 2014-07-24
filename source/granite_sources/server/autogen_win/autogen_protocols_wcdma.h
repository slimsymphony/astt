/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols_wcdma.h
                -------------------------
                SW Include






Project:          autogen

%name:            autogen_protocols_wcdma.h %
%version:         co1tss#3 %
%instance:        co_pctls_1 %
%derived_by:      cjhansen %
%date_modified:   Thu Jan  4 09:51:48 2007 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes WCDMA specific protocol message definition files
*/

#ifdef PN_OBJ_WRAN
 #include "wran_isi_m.h"
 #include "wran_isi_local_m.h"
#else
 printf("* PN_OBJ_WRAN not in product. Excluding 'wran_isi_m.h'\n");
 printf("* PN_OBJ_WRAN not in product. Excluding 'wran_isi_local_m.h'\n");
#endif /* PN_OBJ_WRAN */


/*  End of file autogen_protocols_wcdma.h */
