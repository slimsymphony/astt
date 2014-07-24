/*
NOKIA
R&D Copenhagen
DSS/Corleone









                Module definition
                -----------------

                SW Include






Status:           DRAFT

Continuus DB:     co_pctls

Project:          -

%name:            example_autogen_ti_conf.h %

%version:         co1tss#46 %

%instance:        co_pctls_1 %

%derived_by:      eliasen %

%date_modified:   Wed Sep 30 13:24:03 2009 %

Copyright (c) Nokia. All rights reserved

Change history:

VERSION     : 45         DRAFT        23-Apr-2009  Stig Holmsten Eliasen
REASON      : SCO
REFERENCE   : 417-45805
DESCRIPTION : Remove srvcall_mon.ti from example_autogen_ti_conf.h.

VERSION     : 44         DRAFT        15-Apr-2009  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : REQ 417-35032
DESCRIPTION : Remove PRODUCT_INCLUDES_ISA_WV_IM and included .ti file.

VERSION     : 43         DRAFT        11-Mar-2009  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Removed trace files which have been upgraded to new MCU trace concept:
              - lcif_mon.ti (still has some deprecated macros!)
              - usb_hal_mon.ti (still has some deprecated macros!)
              - ati_mon.ti
              - csdc_cct_trace.ti
              - gpds_mon.ti
              - vip_server.ti (still has some deprecated macros!)
              - wim_mon.ti (still has some deprecated macros!)
              Renamed or obsolete files
              - syncml_mon.ti
              - csd_fax_trace.ti
              - csd_tb_trace.ti
              - wtls_srv.ti
              - wtp_srv.ti
              - http_serv.ti
              - http_nif_isa.ti
              - npa_mon.ti
              - nsp_mon.ti
              - res_mgr_mon.ti
              - transport_mon.ti
              - korex_mon.ti
              - user_agent_mon.ti
              - srvtone_mon.ti

VERSION     : 41         DRAFT        09-May-2007  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Re-introduced vip_server.ti
              Removed files, correctly included in mcu_trace_xxx.h files:
              - srvsckt_mon.ti

VERSION     : 40         DRAFT        19-Apr-2007  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : -
DESCRIPTION : Removed warr_mon.ti

VERSION     : 38         DRAFT        26-Mar-2007  Stig Holmsten Eliasen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed files, correctly included in mcu_trace_xxx.h files:
              - srvatk_mon.ti
              - location_mon.ti
              - mtc_mon.ti
              - servsec_mon.ti
              - apdu_mon.ti
              - simson_mon.ti
              - trackplayer_mon.ti
              - demux_mon.ti
              - synccontrol_mon.ti
              - goltm_mon.ti
              - bcs_serv.ti
              - csd_at_trace-ti
              - csd_common_trace-ti
              - csd_ntb_trace.ti
              - csdc_trace.ti
              - csdc_bc_trace.ti
              - csd_mac_trace.ti
              - csd_wtb_trace.ti
              - sip_mon.ti
              - vip_server.ti
              - httpsrv_serv.ti
              - wdp_srv.ti
              - wsp_srv.ti

VERSION     : 37         DRAFT        08-Dec-2006  Stig Holmsten Eliasen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed file cs_mon.ti

VERSION     : 36         DRAFT        04-Sep-2006  Stig Holmsten Eliasen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed files, correctly included in mcu_trace_xxx.h files:
              - phonet_pipe_mon.ti
              - common_pep_mon.ti
              - cm_info_mon.ti
              - em_mon.ti
              - srvkbd_mon.ti
              - light_mon.ti
              - ta_mon.ti
              - sensor_mon.ti
              - time_mon.ti

VERSION     : 35         DRAFT        04-Sep-2006  Stig Holmsten Eliasen
REASON      : CR
REFERENCE   : 
DESCRIPTION : Change flag for inclusion of lcif_mon.ti

VERSION     : 34         DRAFT        28-Mar-2006  Stig Holmsten Eliasen
REASON      : Error?
REFERENCE   : NH06032453217
DESCRIPTION : Removed inclusion of srvsim_mon.ti

VERSION     : 33         DRAFT        21-Mar-2006  Christian Jacob Hansen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed files, correctly included in mcu_trace_xxx.h files:
              - srvmon_mon.ti
              - cm_mon.ti
              - obx_mon.ti
              - ssl_srv.ti

VERSION     : 32         DRAFT        16-Mar-2006  Stig Holmsten Eliasen
REASON      : Bug
REFERENCE   : JS06031035217
DESCRIPTION : Added missing quotes. 
              wsp_srv.ti and wdp_srv.ti included under PRODUCT_INCLUDES_GSM

VERSION     : 31         DRAFT        24-Jan-2006  Christian Jacob Hansen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Put some files behind ICF_ISA_PROTOCOLS flag
              Removed files, correctly included in mcu_trace_xxx.h files:
              - mon_err.ti
              - fts_appl.ti

VERSION     : 30         DRAFT        14-Nov-2005  Christian Jacob Hansen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed files, correctly included in mcu_trace_xxx.h files:
              - btcs_serv.ti
              - bt_mon.ti
              - fbus_mm_mon.ti
              - file_serv.ti
              - i2c_core_mon.ti
              - i2c_mm_mon.ti
              - mdi_mon.ti
              - nw_browser_trace.ti
              - odin_mon.ti
              - perm_mon.ti
              - rs232_mon.ti
              - rtp_mon.ti
              - test_mon.ti
              - usb_mon.ti
              - wap_trace.ti

VERSION     : 29         DRAFT        03-Nov-2005  Stig Holmsten Eliasen
REASON      : Change Request
REFERENCE   : -
DESCRIPTION : Removed syncml_mon.ti 

VERSION     : 28         DRAFT        21-Sep-2005  Christian Jacob Hansen
REASON      : Update due to new MCU trace concept
REFERENCE   : -
DESCRIPTION : Removed files, correctly configured in mcu_trace_xxx.h files:
              - mes.ti
			  - rtsp_mon.ti
			  - poc_mon.ti
			  - acc_mon.ti
			  - audio_mon.ti
			  - tuneplayer_mon.ti
			  - irda_mon.ti

VERSION     : 27         DRAFT        27-Jun-2005  Christian Jacob Hansen
REASON      : Change Request
REFERENCE   : -
DESCRIPTION : Remove ddi_mon.ti.

VERSION     : 26         DRAFT        15-Jun-2005  Stig Holmsten Eliasen
REASON      : Change Request
REFERENCE   : -
DESCRIPTION : Added vip_server.ti under flag IPF_VIP. 

VERSION     : 25         DRAFT        23-Mar-2005  Stig Holmsten Eliasen
REASON      : Change Request
REFERENCE   : -
DESCRIPTION : Added phonet_pipe_mon.ti under flag ICF_CL. 

VERSION     : 24         DRAFT        09-Feb-2005  Stig Holmsten Eliasen
REASON      : Error
REFERENCE   : -
DESCRIPTION : Corrected C/P error: OBEX->ODIN 

VERSION     : 23         DRAFT        22-Dec-2004  Stig Holmsten Eliasen
REASON      : Change request
REFERENCE   : -
DESCRIPTION : Added mes.ti under flag IPF_MES 

VERSION     : 22         DRAFT        27-Oct-2004  Stig Holmsten Eliasen
REASON      : Change request
REFERENCE   : -
DESCRIPTION : Added cm_info_mon.ti under flag ICF_CL and 
              java_mon.ti under PRODUCT_INCLUDES_MIDP2

VERSION     : 21         DRAFT        27-Oct-2004  Stig Holmsten Eliasen
REASON      : Change request
REFERENCE   : -
DESCRIPTION : Added common_pep_mon.ti under flag ICF_CL

VERSION     : 20         DRAFT        07-Jul-2004  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added fbus_mm_mon.ti

VERSION     : 19         DRAFT        07-Apr-2004  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Corrected flagging around lcif_mon.ti

VERSION     : 18         DRAFT        05-Apr-2004  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added simlock_mon.ti

VERSION     : 17         DRAFT        02-Apr-2004  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added video .ti files
              Moved several ISA protocol .ti files under flags (IPF_XXX)
              Removed duplicate ta_mon.ti

VERSION     : 16         DRAFT        16-Feb-2004  Christian Jacob Hansen
REASON      : -
REFERENCE   : -
DESCRIPTION : Added goltm_mon.ti file

VERSION     : 15         DRAFT        04-Feb-2004  Christian Jacob Hansen
REASON      : Changed core flags to ICF_XXX
REFERENCE   : -
DESCRIPTION : Merged version 14 and 13.7

VERSION     : 14         DRAFT        01-Oct-2003  Christian Jacob Hansen
REASON      : Configuration improvements
REFERENCE   : Task co_pctls#23066
DESCRIPTION : Changed core flags to ICF_XXX
              Removed inclusion of product.h (is already included)
              Added inclusion of i2c_mm_mon.ti

VERSION     : 13.7       DRAFT        21-Jan-2004  Tom Thuneby
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added file tuneplayer_mon.ti

VERSION     : 13.6       DRAFT        29-Dec-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Added files odin_mon.ti and lcif_mon.ti

VERSION     : 13.5       DRAFT        26-Nov-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : -
DESCRIPTION : Included phonet_mon.ti and srvsec_mon.ti

VERSION     : 13.2       DRAFT        29-Oct-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#23306
DESCRIPTION : Included sensor_mon.ti

VERSION     : 13.2       DRAFT        11-Oct-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#23329
DESCRIPTION : Included i2c_mm_mon.ti

VERSION     : 13.1       DRAFT        07-Oct-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#23170
DESCRIPTION : Removed product.h

VERSION     : 13         DRAFT        16-Sep-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#22923
DESCRIPTION : Added rtp_mon.ti to STREAMING section as well
              Removed inclusion of product.h (is already included)

VERSION     : 12          DRAFT       02-Sep-2003  Christian Jacob Hansen
REASON      : Updates
REFERENCE   : Task co_pctls#22764
DESCRIPTION : Removed rtp_mon.ti from STREAMING section
              Added imps_mon.ti to ISA_WV_IM section

VERSION     : 11          DRAFT       02-Jul-2003  Christian Jacob Hansen
REASON      : Improvements
REFERENCE   : Task co_pctls#21971
DESCRIPTION : Added POC section
              Added flags ESIM_IN_USE, PRODUCT_INCLUDES_CS_ISA3
              Added ta_mon.ti to protocols section
 
VERSION     : 10          DRAFT       11-May-2003  Christian Jacob Hansen
REASON      : Change
REFERENCE   : -
DESCRIPTION : Changed flags to PRODUCT_INCLUDES_ flags
              Added many new .ti files

VERSION     : 9          DRAFT        12-Dec-2002  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Changed PN_MEDIA_IR_SUPPORT to PN_MEDIA_IRDA_SUPPORT

VERSION     : 8          DRAFT        30-Oct-2002  Christian Jacob Hansen
REASON      : Add support of coresw server config flags
              Add new ti files
REFERENCE   : -
DESCRIPTION : -

VERSION     : 7          DRAFT        08-Sep-2002  Christian Jacob Hansen
REASON      : Add FTS_appl.ti file
REFERENCE   : Task co_pctls#17102
DESCRIPTION : -

VERSION     : 6          DRAFT        22-Dec-2001  Christian Jacob Hansen
REASON      : Change
REFERENCE   : -
DESCRIPTION : Added ati_mon.ti file
              Task co_pctls#12443

VERSION     : 5          DRAFT        26-Nov-2001  Christian Jacob Hansen
REASON      : Bug fix
REFERENCE   : -
DESCRIPTION : Changed #Include to #include
              Task co_pctls#11966
              Added continuus file header

VERSION     : 4          DRAFT        04-Oct-2001  Christian Jacob Hansen
REASON      : Change
REFERENCE   : -
DESCRIPTION : Added trace files commented out

VERSION     : 3          DRAFT        29-Aug-2001  Christian Jacob Hansen
REASON      : Change
REFERENCE   : -
DESCRIPTION : Added location server traces

VERSION     : 2          DRAFT        29-Aug-2001  Christian Jacob Hansen
REASON      : Change
REFERENCE   : -
DESCRIPTION : Changed bt traces. Added test server traces

VERSION     : 1          DRAFT        22-Aug-2001  Christian Jacob Hansen
REASON      : Original
REFERENCE   : -
DESCRIPTION : Original version

*/

/* ------------------------------------------------------------------------- */
/*                                                                           */
/*   ***  *     ****      ***** ****    *    ***  *****                      */
/*  *   * *     *   *       *   *   *  * *  *   * *                          */
/*  *   * *     *   *       *   *   * *   * *     *                          */
/*  *   * *     *   *       *   ****  ***** *     ****                       */
/*  *   * *     *   *       *   *  *  *   * *   * *                          */
/*   ***  ***** ****        *   *   * *   *  ***  *****                      */
/*                                                                           */
/*   ***   ***  *   *  ***  ***** ****  *****                                */
/*  *   * *   * **  * *   * *     *   *   *                                  */
/*  *     *   * * * * *     *     *   *   *                                  */
/*  *     *   * * * * *     ****  ****    *                                  */
/*  *     *   * *  ** *   * *     *       *                                  */
/*   ***   ***  *   *  ***  ***** *       *                                  */
/*                                                                           */
/*    ***  *   * *     *   *    **  **                                       */
/*   *   * **  * *      * *     **  **                                       */
/*   *   * * * * *       *      **  **                                       */
/*   *   * * * * *       *      **  **                                       */
/*   *   * *  ** *       *                                                   */
/*    ***  *   * *****   *      **  **                                       */
/* ------------------------------------------------------------------------- */
/* Trace interface files specified according to new MCU trace concept        */
/* MUST be included from one of the mcu_trace_xxx.h files specified in       */
/* http://autogen/products/autogen/documentation/topicpage.aspx?id=333       */
/* "Adding Traces To A Component"                                            */
/* (if the .ti file has a RES_BEGIN(RESOURCE_TRC..) in it it is NEW MCU Trc. */
/* ------------------------------------------------------------------------- */

/* include all OLD TRACE CONCEPT .ti files here (except group files, such as mon_grp.ti) */

/* Core */

#if (ICF_INFO_SERV == ON)
#include "info_mon.ti"
#endif /* ICF_INFO_SERV */

#if (ICF_TOUCHPAD_SERV == ON)
#include "srvtp_mon.ti"
#endif /* ICF_TOUCHPAD_SERV */

#if (ICF_VERSIT_SERV == ON)
#include "versit_mon.ti"
#endif /* ICF_VERSIT_SERV */


/*  End of file autogen_ti_conf.h  */
