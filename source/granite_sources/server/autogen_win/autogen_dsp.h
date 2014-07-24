/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_dsp.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_dsp.h %
%version:         co1tss#16 %
%instance:        co_pctls_1 %
%derived_by:      nosterga %
%date_modified:   Thu Nov 20 13:14:55 2008 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for the autogen tool

    This file includes dsp message definition files
*/


#if (ICF_MUSIC_SERV == ON)
 #include "dsp_music_player_isi_m.h"
#else
 printf("* ICF_MUSIC_SERV is OFF. Excluding 'dsp_music_player_isi_m.h'\n");
#endif /* ICF_MUSIC_SERV == ON */


#if (ICF_VIDEO == ON)
 #include "dsp_video_isi_m.h"
#else
 printf("* ICF_VIDEO is OFF. Excluding 'dsp_video_isi_m.h'\n");
#endif /* ICF_VIDEO == ON */


#ifdef PN_OBJ_DSP_VOICE
 #include "dsp_voice_isi_m.h"
#else
 printf("* PN_OBJ_DSP_VOICE not in product. Excluding 'dsp_voice_isi_m.h'\n");
#endif /* PN_OBJ_DSP_VOICE */

PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_MAIN)
#include "dsp_core_isi_m.h"

#include "autogen_adsp_core.h"


/*  End of file autogen_dsp.h */
