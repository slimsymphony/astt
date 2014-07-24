/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols2.h
                -------------------
                SW Include






Project:          autogen

%name:            autogen_protocols2.h %
%version:         7 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Thu Apr 16 16:28:14 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes protocol message definition files
*/


#ifdef PN_OBJ_SSOM_SERV
 #include "ssom_isi_m.h"
#else
 printf("* PN_OBJ_SSOM_SERV is not defined. Excluding 'ssom_isi_m.h'\n");
#endif /* PN_OBJ_SSOM_SERV */


/*  End of file autogen_protocols2.h */
