/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_protocols3.h
                -------------------
                SW Include






Project:          autogen

%name:            autogen_protocols3.h %
%version:         5 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Thu Apr 16 16:28:39 2009 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes protocol message definition files
*/


#if (IPF_UMA == ON)
 #include "sos_uma_isi_m.h"
#else
 printf("* IPF_UMA is OFF. Excluding 'sos_uma_isi_m.h'\n");
#endif /* IPF_UMA == ON */
 

/*  End of file autogen_protocols3.h */
