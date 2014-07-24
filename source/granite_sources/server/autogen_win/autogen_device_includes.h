/*
NOKIA
R&D Copenhagen
ASW/DSS/DS/Corleone









                autogen_device_includes.h
                --------------------------
                SW Include






Project:          autogen

%name:            autogen_device_includes.h %
%version:         1 %
%instance:        co1tss_1 %
%derived_by:      eliasen %
%date_modified:   Thu May  8 12:33:48 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes DEVICE specific message definition files
*/

/* processor1_files.h includes all message macro files to be included in PMD file for processor 1 */
#if (AUTOGEN_PROCESSOR_1 == ON)
 printf("  AUTOGEN_PROCESSOR_1 is ON.  Including 'processor1_files.h'\n");
 #include "processor1_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_1 is OFF. Excluding 'processor1_files.h'\n");
#endif

/* processor2_files.h includes all message macro files to be included in PMD file for processor 2 */
#if (AUTOGEN_PROCESSOR_2 == ON)
 printf("  AUTOGEN_PROCESSOR_2 is ON.  Including 'processor2_files.h'\n");
 #include "processor2_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_2 is OFF. Excluding 'processor2_files.h'\n");
#endif

/* processor3_files.h includes all message macro files to be included in PMD file for processor 3 */
#if (AUTOGEN_PROCESSOR_3 == ON)
 printf("  AUTOGEN_PROCESSOR_3 is ON.  Including 'processor3_files.h'\n");
 #include "processor3_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_3 is OFF. Excluding 'processor3_files.h'\n");
#endif

/* processor4_files.h includes all message macro files to be included in PMD file for processor 4 */
#if (AUTOGEN_PROCESSOR_4 == ON)
 printf("  AUTOGEN_PROCESSOR_4 is ON.  Including 'processor4_files.h'\n");
 #include "processor4_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_4 is OFF. Excluding 'processor4_files.h'\n");
#endif

/* processor5_files.h includes all message macro files to be included in PMD file for processor 5 */
#if (AUTOGEN_PROCESSOR_5 == ON)
 printf("  AUTOGEN_PROCESSOR_5 is ON.  Including 'processor5_files.h'\n");
 #include "processor5_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_5 is OFF. Excluding 'processor5_files.h'\n");
#endif

/* processor6_files.h includes all message macro files to be included in PMD file for processor 6 */
#if (AUTOGEN_PROCESSOR_6 == ON)
 printf("  AUTOGEN_PROCESSOR_6 is ON.  Including 'processor6_files.h'\n");
 #include "processor6_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_6 is OFF. Excluding 'processor6_files.h'\n");
#endif

/* processor7_files.h includes all message macro files to be included in PMD file for processor 7 */
#if (AUTOGEN_PROCESSOR_7 == ON)
 printf("  AUTOGEN_PROCESSOR_7 is ON.  Including 'processor7_files.h'\n");
 #include "processor7_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_7 is OFF. Excluding 'processor7_files.h'\n");
#endif

/* processor8_files.h includes all message macro files to be included in PMD file for processor 8 */
#if (AUTOGEN_PROCESSOR_8 == ON)
 printf("  AUTOGEN_PROCESSOR_8 is ON.  Including 'processor8_files.h'\n");
 #include "processor8_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_8 is OFF. Excluding 'processor8_files.h'\n");
#endif

/* processor9_files.h includes all message macro files to be included in PMD file for processor 9 */
#if (AUTOGEN_PROCESSOR_9 == ON)
 printf("  AUTOGEN_PROCESSOR_9 is ON.  Including 'processor9_files.h'\n");
 #include "processor9_files.h"
#else
 printf("* AUTOGEN_PROCESSOR_9 is OFF. Excluding 'processor9_files.h'\n");
#endif

/*  End of file autogen_device_includes.h */
