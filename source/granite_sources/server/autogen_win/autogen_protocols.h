/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols.h
                -------------------
                SW Include






Project:          autogen

%name:            autogen_protocols.h %
%version:         co1tss#41 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Wed Apr 15 14:50:37 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes protocol message definition files
*/

#ifdef PN_OBJ_SOCKET_SERVER
 #include "srvsckt_isi_m.h"
#else
 printf("* PN_OBJ_SOCKET_SERVER is not in product. Excluding 'srvsckt_isi_m.h'\n");
#endif /* PN_OBJ_SOCKET_SERVER */


/*  End of file autogen_protocols.h */
