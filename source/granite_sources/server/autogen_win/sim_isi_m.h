/*
NOKIA MOBILE PHONES
R&D Copenhagen














            SIM server interface description
            --------------------------------

            SW module - Autogen input file






Object Name:        %full_name: co_sim#1/incl/sim_isi_m.h/co1core2#020.001 %
 
Filename:           sim_isi_m.h

Document Code:      -

Copyright(c) Nokia Mobile Phones. All rights reserved.

  

Change History:

VERSION    : 020.001    6-Nov-2009    Thomas Kure Thorngreen    Approved
REASON     : Correct minor errors in SIM ISI macro file, causing PMD decode problems.
REFERENCE  : ActionDB for SWAM: TT09110554994
DESCRIPTION: -

VERSION    : 020.000    12-Aug-2009    Nikolaj Skov    Approved
REASON     : Remove parts of SIM ISI IF not supported by S40 Adaptation SIM Server.
REFERENCE  : ActionDB for SWAM: NS09061946380
DESCRIPTION: -

VERSION    : 018.002    11-Feb-2009    Nikolaj Skov    Approved
REASON     : Change to SUB_MSG_REQUEST_HDR macro.
REFERENCE  : ActionDB for SWAM: NS09021134415
DESCRIPTION: Added padding byte to SUB_MSG_REQUEST_HDR.

VERSION    : 018.000    07-Jan-2008    Thomas Stormark   Approved
REASON     : Updating ISI interface CR to I_CPR_7.2 on Smartcard profile: Parental Control Pincode and OMA BCAST AUTHENTICATE response
REFERENCE  : CM Synergy task: co1core#86560
             WP RM-RIM Tool: 006-15505, 006-16563
             ActionDB for SWAM: TS07110689414
DESCRIPTION: Added ext bcast support to Authenticate req/resp and new PIN_PC to pin isi related msg.
             SIM_SB_AM_HANDLE subblock has been moved to the new sim_shared_isi.h file.
             018.000 follows 017.006 in R&D and 018.001 follows 017.004 in 7.2 branch.

VERSION    : 017.006    06-Dec-2007    John Soerensen Approved
REASON     : RM-RIM:408-2329
REFERENCE  : Synergy/CM task: co1core#87508
             ActionDB for SWAM: JS07111351317
DESCRIPTION: New SB SIM_SB_AT&T_RAT_ID  is defined. Added to
             SIM_CS_READ_REQ/RESP.
             New refresh ID SIM_REFRESH_AT&T_RAT  is defined. Added to
             SIM_REFRESH_NTF and SIM_REFRESH_REQ.
             Version 017.005 is used for 7.1 branch only.

VERSION    : 017.004      20-Aug-2007    John Sorensen   Approved
REASON     : RM-RIM:006-14131
REFERENCE  : ActionDB for SWAM: JS07062732576
DESCRIPTION: DSS related stuff removed:
             SIM_MISC_SERVICE_TYPE_TABLE updated. All DSS related definitions removed.
             Messages supported by DSS server only, are removed:
             SIM_PN_READ_REQ/RESP, SIM_INIT_REQ,
	     SIM_UPDATE_REQ/RESP, SIM_STANDBY_STATUS_REQ/RESP,
	     SIM_READ_NVT_MEM_REQ/RESP, SIM_RUN_GSM_ALGORITM_REQ/RESP,
	     SIM_PN_LIST_ENABLE_REQ/RESP,
	     SIM_INFONUM_REQ/RESP, SIM_ATK_SEND_USSD_CONS, 
	     SIM_ATK_SEND_USSD_INF, SIM_MSISDN_INFO_REQ/RESP,
	     SIM_PREFERRED_PROTOCOL_IND, SIM_GET_SEARCH_TABLE_REQ/RESP,
	     SIM_NETWORK_INFO_REQ/RESP(READ_PLMN_LIST),
	     SIM_ACM_REQ/RESP(SIM_ST_WARNING_LEVEL_READ),
	     SIM_CSP_REQ/RESP(READ_TO_SCM, WRITE_TO_SCM),
	     SIM_PB_REQ(SIM_PB_ROOM_CHECK).
	     
	     DSS message not removed(Not visible in HTML file):
	     SIM_PN_LIST_STATUS_REQ/RESP, used by ATK
	     SIM_PN_WRITE_REQ/RESP, used by ProtocolSW and SIMSON.
	     SIM_PN_READ_RESP, used by SIMSON.
     	     SIM_TARIFF_REQ/RESP(READ_PACKAGE) used by UI.
             SIM_JACOB_REQ/RESP(READ_REAL_JACOB_IDS) used by UI.
	     SIM_SAT_REQ/RESP(CB_DOWNLOAD) used by ProtocolSW from dct4_srvsim_msg.h.

	     SBs, related to DSS, not removed:
	     SIM_PB_ROOM_INFO_REQ, used by SIMSON.
	     SIM_PB_ROOM_INFO_ERROR, used by SIMSON.
	     
	     Removed SBs:
	     SIM_PB_LND, SIM_PB_PSC.
	     SIM_PB_ROOM_INFO_REQUEST,SIM_PB_ROOM_INFO_ERROR.
	     
	     Removed sequences:
	     SIM_ACM_WARNING
	     
	     Alignments:
	     All "VALUE(8, BE, StorageStatus, "StorageStatus", DEC)"
	     changed to
             "VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE"
	     
	     Removed tables(not used):
	     SIM_SB_FILE_STATUS,
	     SIM_PIN_ENABLE_SERVICE_TYPE,
             SIM_ST_SMS_WRITE_RAW_STATUS.	     

	     General:
	     Comments added to messages and parameters. Visible in HTML file.
	     
	     Definitions removed:
	     Doubble definition of "#define ADN" and "#define FDN" removed.
	     
VERSION    : 017.003    03-Aug-2007    Thomas Stormark   Approved
REASON     : Updating ISI interface for 408-1076: SIM Server support for lumiere gba_u and MGV_U
REFERENCE  : CM Synergy task: co1core#76808
             WP RM-RIM Tool: 408-1076
             ActionDB for SWAM: TS07061989406
DESCRIPTION: Added GBA, MBMS, ApplicationManagement API for 7.2 branch.

VERSION    : 017.002.1    23-Mar-2007    Nikolaj Skov    Approved
REASON     : Error correction
REFERENCE  : Synergy/CM task: co1core#70603
             ActionDB for SWAM: NS07032335341
DESCRIPTION: Three padding bytes added after MailboxNumbInfo in SIM_CPHS_RESP to
             match the real world.

VERSION    : 017.002    19-Dec-2006    Nikolaj Skov    Approved
REASON     : Addition of SIM_ST_REFRESH_STARTING service type to
             SIM_REFRESH_NTF.
REFERENCE  : Synergy/CM task: co1core#64901
             ActionDB for SWAM: NS06112745514
DESCRIPTION: SIM_ST_REFRESH_STARTING service type added to SIM_REFRESH_NTF.

VERSION    : 017.001    15-Dec-2006    Thomas Stormark   Approved
REASON     : Updating ISI interface for 006-12840: Enhanced FETCH handling
REFERENCE  : CM Synergy task: co1core#56686
             WP RM-RIM Tool: 006-12840
             ActionDB for SWAM: TS06103133373
DESCRIPTION: Added service types to req SIM_ATK_REQ:
                - SIM_ST_CAT_SUPPORT_ENABLE
                - SIM_ST_CAT_SUPPORT_DISABLE

Version     : 017.000    Approved    23-Oct-2006    Soren Engquist
Reason      : Removal of CDMA in the core software asset.
Reference   : CM Synergy task: co1core#62431
              WP RM-RIM Tool: 006-14124
              ActionDB for SWAM: SE06102354231
Description : All RUIM and GAIT references have been removed.

Version     : 016.000    Approved    10-Aug-2006    Paetur Petersen
Reason      : Remove dependency to Tracfone Server
Reference   : CM Synergy task: co1core#11885
              WP RM-RIM Tool: 006-13174
              ActionDB for SWAM: PP06072156397
Description : Added Message SIM_TRACFONE_REQ
              Added Message SIM_TRACFONE_REQ.SIM_ST_TRACFONE_COMPLETED_FAIL
              Added Message SIM_TRACFONE_REQ.SIM_ST_TRACFONE_COMPLETED_SUCCESS
              Added Message SIM_TRACFONE_REQ.SIM_ST_TRACFONE_STATUS
              Added Message SIM_TRACFONE_RESP
              Added Message SIM_TRACFONE_RESP.SIM_ST_TRACFONE_COMPLETED_FAIL
              Added Message SIM_TRACFONE_RESP.SIM_ST_TRACFONE_COMPLETED_SUCCESS
              Added Message SIM_TRACFONE_RESP.SIM_ST_TRACFONE_STATUS
              Discontinued Message SIM_TRACFONE_SIMLOCK_STATUS_REQ
              Discontinued Message SIM_TRACFONE_SIMLOCK_STATUS_REQ.NO_SERVICE_TYPE
              Discontinued Message SIM_TRACFONE_SIMLOCK_STATUS_RESP
              Discontinued Message SIM_TRACFONE_SIMLOCK_STATUS_RESP.NO_SERVICE_TYPE

VERSION    : 015.011    19-May-2006    Annette Thy    Approved
REASON     : Macrofile should be created for SIM server
REFERENCE  : CM Synergy task: co1core#50080
             WP RM-RIM Tool: 006-8365: Macro file should be created for SIM server 
             ActionDB for SWAM: AT06051933264
DESCRIPTION: sim_isi_m.h file has been changed so that it now can be used to 
             generate sim_isi.h file. Other interface files should NOT be automatically
             generated yet.

VERSION    : 015.010    02-May-2006    Thomas Stormark   Approved
REASON     : Updating ISI interface for 010-182: Support for EF-ACL UI part
REFERENCE  : CM Synergy task: co1core#50821
             WP RM-RIM Tool: 010-182
             ActionDB for SWAM: TS06050249393
DESCRIPTION: Added service types, structures and constants for ACL Read and Write

VERSION    : 015.009    3-Apr-2006    Soren Engquist     Approved
REASON     : Changing constant for 006-10452: Remove SIM_SERV_LOC_NOT_VALID
REFERENCE  : CM Synergy task: co1core#49940
             WP RM-RIM Tool: 006-10452
             ActionDB for SWAM: SE06040351729
DESCRIPTION: Version macro updated and added SIM_ST_GPRS_CALL_CONTROL_AVAIL
             to the SIM_READ_TABLE_SERVICE_TYPE table.

VERSION    : 015.008    4-Apr-2006    Soren Engquist     Approved
REASON     : PCP Error: EO06032951336 GSM/WCDMA - OTC - SIm phonebook : entering a 70 caracters long email address
REFERENCE  : CM Synergy task: co1core#49973
             ActionDB for SWAM: SE06040442314
DESCRIPTION: Version macro updated and Correcting 
                SIM_TEXT_LEN = PR_NAME_LENGTH+1 -> 
                SIM_TEXT_LEN = PR_TEXT_LENGTH+1.

VERSION    : 015.007    13-Mar-2006    Michael Noerlev     Approved
REASON     : Adding ISI interface for 006-5954: APN - Support for EFACL
REFERENCE  : CM Synergy task: co1core#48518
             WP RM-RIM Tool: 006-5954
             ActionDB for SWAM: MN05122035049
DESCRIPTION: Version macro updated and SIM_STA_ACL_CHECK_DISABLED removed.

VERSION    : 015.006    21-Feb-2006    Michael Noerlev     Approved
REASON     : Adding ISI interface for 006-5954: APN - Support for EFACL
REFERENCE  : CM Synergy task: co1core#42462
             WP RM-RIM Tool: 006-5954
             ActionDB for SWAM: MN05122035049
DESCRIPTION: Added service types, structures and constants for ACL

VERSION    : 015.005.1    12-Jan-2005    Nikolaj Skov Hansen    Approved
REASON     : Error correction
REFERENCE  : CM Synergy task: co1core#44463
DESCRIPTION: In table SIM_PIN_ATTEMPTS_LEFT_STATUS these changes have been made:
                 SIM_SERV_NOTREADY -> SIM_STA_NOTREADY
                 SIM_SERV_ERROR -> SIM_STA_ERROR
                 SIM_SERV_NOSERVICE -> SIM_STA_NOSERVICE

VERSION    : 015.005    09-Jan-2005    Nikolaj Skov Hansen    Approved
REASON     : New ISI message to retrieve number of remaining verification
             attempts for PIN and PUK.
REFERENCE  : CM Synergy task: co1core#43453
             ActionDB for SWAM: NH05120235814
DESCRIPTION: Added new Message IDs:
                 SIM_PIN_ATTEMPTS_LEFT_REQ
                 SIM_PIN_ATTEMPTS_LEFT_RESP
             Added new Service Types:
                 SIM_ST_PUK
                 SIM_ST_PUK2
             Added new message structures:
                 tSIM_PIN_ATTEMPTS_LEFT_REQ
                 tSIM_PIN_ATTEMPTS_LEFT_RESP

VERSION    : 015.004    02-Jan-2006    Paetur Petersen    Approved
REASON     : Adding ISI interface for TracFone integration to GSM ISA
REFERENCE  : CM Synergy task: co1core#42394
             WP RM-RIM Tool: 006-8308
             ActionDB for SWAM: PE05121357262
DESCRIPTION: Added a new service type and related stuff for envelope sending
             Added a new req/resp for SIM_TRACFONE_SIMLOCK_STATUS_REQ/RESP

VERSION    : 015.003    14-Dec-2005    Soren Engquist    Approved
REASON     : Adding service types for SIM_READ_TABLE_REQ
REFERENCE  : CM Synergy task: co1core#30746
             WP RM-RIM Tool: 006-10401
             ActionDB for SWAM: SE05121450785 
DESCRIPTION: Adding service types for SIM_READ_TABLE_REQ/RESP:  
                SIM_ST_GPRS_CALL_CONTROL_AVAIL, 

VERSION    : 015.001    17-Nov-2005    Soren Engquist    Approved
REASON     : Adding service types for SIM_DATA_SIZES_REQ
REFERENCE  : CM Synergy task: co1core#40951
             ActionDB for SWAM: SE05110833235
DESCRIPTION: Adding service types for SIM_DATA_SIZES_REQ/RESP:  
                SIM_ST_READ_VMBX_CNT, 
                SIM_ST_READ_VMBX_ALPHA_LEN, 
                SIM_ST_READ_VMBX_NBR_LEN, 
                SIM_ST_READ_MBDN_CNT, 
                SIM_ST_READ_MBDN_PROFILE_SIZE, 
                SIM_ST_READ_MBDN_PROFILE_CNT. 
                SIM_ST_READ_MBDN_ALPHA_LEN, 
                SIM_ST_READ_MBDN_NBR_LEN

VERSION    : 015.000    31-Oct-2005    Nikolaj Skov Hansen    Approved
REASON     : Change of status values for R-UIM Operational Mode
REFERENCE  : CM Synergy task: co1core#39074
             ActionDB for SWAM: NH05100554048
DESCRIPTION: SIM_STA_NO_RUIM is replaced by SIM_STA_RUIM_OFF; SIM_STA_FULL_RUIM 
             is replaced by SIM_STA_RUIM_ON; SIM_STA_LIMITED_RUIM is removed.

VERSION    : 014.019    06-Oct-2005    Michael Noerlev    Approved
REASON     : Support EF-EHPLMN field on USIM
REFERENCE  : CM Synergy task: co1core#38855
             WP RM-RIM Tool: 006-8926
             ActionDB for SWAM: PP05090846932
DESCRIPTION: Added SIM_SB_EQUIVALENT_HPLMNS_ID and SIM_REFRESH_EQUIVALENT_HPLMNS

VERSION    : 014.018    06-Sep-2005    Nikolaj Skov Hansen    Approved
REASON     : Interface for ESN
REFERENCE  : CM Synergy task: co1core#38516
             WP RM-RIM Tool: 006-9582
             ActionDB for SWAM: NH05083056389
DESCRIPTION: Added SIM_ESN_MEID_EQUAL_IND and SIM_ESN_MEID_EQUAL_REQ/RESP.
                
VERSION    : 014.017    06-Jul-2005    Soren Engquist            Approved
REASON     : long configuration subblocks for phonebook.
REFERENCE  : CM Synergy task: co1core#37125
             WP RM-RIM Tool: 006-9284
             ActionDB for SWAM: SE05070537600 (Change Request)
             ActionDB for SWAM: SE05070654225 (Inspection Minutes)
DESCRIPTION: New subblock ids
             SIM_PB_CONF_ANR_LONG_SB  
             SIM_PB_CONF_EMAIL_LONG_SB
             SIM_PB_CONF_SNE_LONG_SB  
             SIM_PB_CONF_GRP_LONG_SB  

VERSION    : 014.016.1    07-Jun-2005    Nikolaj Skov Hansen    Approved
REASON     : Error correction
REFERENCE  : CM Synergy task: co1core#35237
             WP RM-RIM Tool: 006-8372 & 006-8373
             ActionDB for SWAM: AT05051844532 (Change Request)
             ActionDB for SWAM: AT05052733033 (Inspection Minutes)
DESCRIPTION: SIM_STA_DATA_NOT_AVAIL removed from table SIM_STA.
             New table SIM_HZ_STATUS created.

VERSION    : 014.016    06-Jun-2005    Annette Thy            Approved
REASON     : New ServiceTypes for O2 HomeZone
REFERENCE  : CM Synergy task: co1core#34393
             WP RM-RIM Tool: 006-8372 & 006-8373
             ActionDB for SWAM: AT05051844532 (Change Request)
             ActionDB for SWAM: AT05052733033 (Inspection Minutes)
DESCRIPTION: New service types
             SIM_ST_READ_SUBSCRIBED_LAC_CI
             SIM_ST_READ_HZ_TAGS
             SIM_ST_READ_UHZIUE_SETTINGS
             SIM_ST_WRITE_UHZIUE_SETTINGS
             added for SIM_VIAG_HOME_ZONE_REQ message.
             SIM_STA_DATA_NOT_AVAIL added to SIM_STA table.

VERSION    : 014.015    17-Mar-2005    Nikolaj Skov Hansen    Approved
REASON     : New ServiceType for CALL CONTROL
REFERENCE  : CM Synergy task: co1core#29306
             WP RM-RIM Tool: 006-7198
             ActionDB for SWAM: NH05022459122 (Change Request)
             ActionDB for SWAM: NH05031732544 (Inspection Minutes)
DESCRIPTION: New service type SIM_ST_CDMA_CALL_CONTROL added for 
             SIM_READ_RUIM_TABLE_REQ message.
                
VERSION    : 014.014.3    16-Mar-2005    Nikolaj Skov Hansen     Approved
REASON     : PMD loading error in sim
REFERENCE  : CM Synergy task: co1core#29233
DESCRIPTION: tSIM_SMS_READ_RAW_RESP had two fields called 'Status'; one is now 
             renamed 'StorageStatus'.

VERSION    : 014.014 ver 2    14-Mar-2005    Erik Laursen     Approved
REASON     : duplicate definition in sim_isi_m.h?
REFERENCE  : CM Synergy task: co1core#29092;
             PCP Error TS05031452109
DESCRIPTION: Correct SIM_IMS_REQ.SIM_ST_IMS_STATUS to Resp

VERSION    : 014.014    11-Mar-2005    Nikolaj Skov Hansen    Approved
REASON     : SIM: New SMS interface for SCO 006-5531 - Support for new 
             messaging platform.
REFERENCE  : CM Synergy task: co1core#28220
             WP RM-RIM Tool: 006-5531
             ActionDB for SWAM: NH04102546452 (Change Request)
             ActionDB for SWAM: NH05030245613 (Inspection Minutes)
DESCRIPTION: Added message structures:
                - tSIM_SMS_READ_RAW_REQ
                - tSIM_SMS_READ_RAW_RESP
                - tSIM_SMS_WRITE_RAW_REQ
                - tSIM_SMS_WRITE_RAW_RESP
             Added service types to SIM_SMS_REQ message:
                - SIM_ST_SMS_READ_RAW
                - SIM_ST_SMS_WRITE_RAW
                
VERSION    : 014.013    03-Mar-2005    Nikolaj Skov Hansen    Approved
REASON     : Additions to SIM_RUIM_IND and SIM_STATUS_REQ.
REFERENCE  : CM Synergy task: co1core#27327;
             ActionDB for SWAM: NH05013146615 (Change Request);
             ActionDB for SWAM: NH05021845815 (Inspection Agenda)
DESCRIPTION: Added service type SIM_ST_RUIM_OPERATIONAL_MODE.
             Added status values SIM_STA_NO_RUIM, SIM_STA_LIMITED_RUIM and 
             SIM_STA_FULL_RUIM.

VERSION    : 014.012    23-Feb-2005    Erik Laursen            Approved
REASON     : SIM: Icon buffering in ISA and splitting to SOS
REFERENCE  : CM Synergy task co1core#27565;
             WP RM-RIM Tool: 009-16822: Icon buffering in ISA and splitting to SOS;
             ActionDB for SWAM: EL05021030307 (Change Request);
             ActionDB for SWAM: EL05022353233 (Inspection Minutes)
DESCRIPTION: Added service types to reg SIM_ATK_REQ:
                - SIM_ST_READ_ICON_CLUT
                - SIM_ST_READ_ICON_BODY_DATA
             And sub blocks:
                - SIM_SB_ICON_DATA_CLUT_ID
                - SIM_SB_ICON_BODY_DATA_ID  

VERSION    : 014.011    31-Jan-2005    Erik Laursen            Approved
REASON     : SIM: Support of ISIM for IMS access
REFERENCE  : CM Synergy task co1core#24439;
             WP RM-RIM Tool: 006-3097;
             ActionDB for SWAM: EL04122339567 (Change Request);
             ActionDB for SWAM: EL05013146658 (Inspection Minutes)
DESCRIPTION: Added message IDs: SIM_IMS_REQ/RESP and SIM_IMS_IND
                With service types:
                    SIM_ST_IMS_START_SESSION
                    SIM_ST_IMS_END_SESSION
                    SIM_ST_IMS_STATUS
                    SIM_ST_IMS_READ_DATA   
                And Sub blocks:
                    SIM_SB_IMS_PRIVATE_USER_ID
                    SIM_SB_IMS_PUBLIC_USER_ID        
                    SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID
                And refresh message IDs:
                    SIM_REFRESH_IMS_PRIVATE_USER_ID
                    SIM_REFRESH_IMS_PUBLIC_USER_ID
                    SIM_REFRESH_IMS_HOME_NW_DOMAIN_NAME
              Add Service type and Sub block to Message ID SIM_APP_SELECTION_REQ:
                    SIM_ST_GET_ISIM_LABEL
                    SIM_ST_GET_LABEL_BY_NO
                    SIM_SB_APP_SELECTION_UNICODE
              Add Service type to Message ID SIM_AUTHENTICATION_REQ:
                    SIM_ST_IMS_CONTEXT 
              In all PIN requests padding byte is substituted with:
                    ApplicationNumber            

VERSION    : 014.010    11-Jan-2005    Annette Thy           Approved
REASON     : SIM: EAP-AKA authentication support in SIMSON
REFERENCE  : CM Synergy task co1core#15124;
             WP RM-RIM Tool: 006-3761;
             ActionDB for SWAM: AT04092342665 (Change Request);
             ActionDB for SWAM: AT04112555298 (Inspection Minutes)
DESCRIPTION: Added service type SIM_ST_EAP_AKA_CONTEXT to be used with
             SIM_AUTHENTICATION_REQ
             Added the following subblocks:
             SIM_SB_EAP_INTEGRITY_KEY
             SIM_SB_EAP_CIPHERING_KEY
             Added constants:
             SIM_EAP_CIPH_KEY_LEN
             SIM_EAP_INTE_KEY_LEN

VERSION    : 014.009    06-Jan-2005    Dan Egebo             Approved
REASON     : New service type added.
REFERENCE  : ActionDB for SWAM:  DE04110854756(Change Request);
             ActionDB for SWAM:  DE04112334116(Inspection Minutes)
             RM-RIM 006-5886, Connecting SIM from PDA mode in DSS.
             CM Synergy task co1core#21462.
DESCRIPTION: Added new service type SIM_ST_SIM_CONNECTION_FORCED_PIN to
             SIM_CONNECTION_REQ/RESP.
             
VERSION    : 014.008    26-nov-2004    Jorgen Moller Ilsoe          Approved
REASON     : Addition of new subblock to phonebook start-up phase 2
REFERENCE  : CM Synergy task co1core#20930;
             WP RM-RIM Tool: 006-6382; 
             ActionDB for SWAM: JI04102053490 (Change Request);
             ActionDB for SWAM: JI04111546442 (Inspection Minutes)
DESCRIPTION: Addition of new subblock for phonebook start-up phase 2


VERSION    : 014.007    04-nov-2004    Erik Laursen          Approved
REASON     : SIM: Addition of missing file IDs for Refresh Release 99 implementation
REFERENCE  : CM Synergy task co1core#20852;
             WP RM-RIM Tool: 006-2213;
             ActionDB for SWAM: EL04102542507 (Change Request);
             ActionDB for SWAM: EL04110542986 (Inspection Minutes)
DESCRIPTION: Add missing file ID definitions for Refresh R99
             Add missing macroes for ALS (Dynamic flags)

VERSION    : 014.006    08-Sep-2004    Nikolaj Skov Hansen    Approved
REASON     : SIM: New interface for R-UIM
REFERENCE  : CM Synergy task co1core#14144;
             WP RM-RIM Tool: 006-4630;
             ActionDB for SWAM: NH04063042099 (Change Request);
             ActionDB for SWAM: NH04072053264 (Inspection Minutes)
DESCRIPTION: Added support for R-UIM messages.

VERSION    : 014.005    01-Jul-2004    Nikolaj Skov Hansen    Approved
REASON     : SIM: SIMLOCK state enquiry with req/resp message
REFERENCE  : Continuus task co1core#12352;
             WP RM-RIM Tool: 006-4864;
             ActionDB for SWAM: NH04061753527 (Change Request);
             ActionDB for SWAM: NH04062444852 (Inspection Minutes)
DESCRIPTION: Added support for SIM_STATUS_REQ(SIM_ST_SIMLOCK_STATUS)

VERSION     : 014.004   10-Jun-2004 Erik Laursen              Approved
REASON      : SIM: Support for disabling and enabling of PIN2 on USIM Cards 
REFERENCE   : Continuus task co_sim#37182;
              SWAM CR: EL04052746922, WP RM-RIM Tool: 006-4125: Disable/Enable PIN2 on USIM 
DESCRIPTION : Add SIM_ST_PIN2 to enable/disable PIN ISI Request

VERSION    : 014.003.2    10-Jun-2004    Nikolaj Skov Hansen    Approved
REASON     : Fixed error in table SIM_STATUS_MMS
REFERENCE  : Continuus task co_sim#37178
DESCRIPTION: A comma was missing after SIM_STA_DATA_NOT_AVAILABLE and
             SIM_STA_FILE_NOT_AVAILABLE.

VERSION    : 014.003    03-Jun-2004    Nikolaj Skov Hansen    Approved
REASON     : New ISI interface for provisioning of MMS settings on the (U)SIM
REFERENCE  : Continuus task co_sim#36409;
             WP RM-RIM Tool: 006-3566;
             ActionDB for SWAM: NH04042755103 (Change Request);
             ActionDB for SWAM: NH04051949372 (Inspection Minutes)
DESCRIPTION: Added support for SIM_MMS_REQ

VERSION    : 014.002    13-May-2004    Nikolaj Skov Hansen    Approved
REASON     : Implementation of full refresh according to 3GPP TS 11.14
REFERENCE  : Continuus task co_sim#35574;
             WP RM-RIM Tool: 006-2213;
             ActionDB for SWAM: JM04032334025 (Change Request)
DESCRIPTION: Added support for SIM_REFRESH_REQ and SIM_REFRESH_NTF

VERSION    : 014.000    19-Mar-2004    Jorgen Ilsoe    Approved
REASON     : PCP MM04021959464
REFERENCE  : PCP MM04021959464, SWAM JI04022354652 and SWAM JI04031944552
DESCRIPTION: Added version history. No further changes.

VERSION    : 013.004    02-Apr-2004        Erik Laursen          Approved
REASON     : O2 HomeZone
REFERENCE  : Continuus task co_sim#18047
DESCRIPTION: Support for SIM_VIAG_HOME_ZONE_REQ

VERSION    : 013.003    18-Mar-2004        Erik Laursen          Approved
REASON     : The input data did not match the length expected by SIM_CS_READ_RESP
REFERENCE  : PCP Error: JK03112888758, Task: co_sim#32524, LN ADB for TEC EL04031948697
DESCRIPTION: Many updates of the SIM Message Macroes

VERSION    : 8    14-jan-2004        Erik Laursen          Approved
REASON     : Support for Icons on (U)SIM card    
REFERENCE  : ActionDB for SWAM Ref.:EL03121546046(Change Request),
             ActionDB for SWAM Ref.: EL04011439377 (Inspection Agenda)
DESCRIPTION: Add new Service Type: SIM_ST_READ_ICON to SIM_ATK_REQ/RESP and sub block: SIM_SB_ICON_DATA_ID

VERSION    : 7    2-Dec-2003    Erik Laursen    Approved
REASON     : Support for futher messages.
REFERENCE  : Task co_sim#30957
DESCRIPTION: Added support for SIM_PB_REQ, SIM_READ_CI_REQ,
             ACM releated isi requests and SIM indications. 

VERSION    : 6    19-Nov-2003    Nikolaj Skov Hansen    Approved
REASON     : Support for futher messages.
REFERENCE  : Task co_sim#27420
DESCRIPTION: Added support for SIM_CPHS_REQ, SIM_READ_TABLE_REQ and
             SIM_OPERATOR_NAME_REQ.

VERSION    : 5    03-Nov-2003    Nikolaj Skov Hansen    Approved
REASON     : Support for futher messages.
REFERENCE  : Task co_sim#27204
DESCRIPTION: Added support for SIM_GSM_DIR_REQ, SIM_NETWORK_INFO_REQ and
             SIM_READ_EMERG_CODES_REQ.

VERSION    : 4_for_pmd_only      20-Oct-2003    Erik Laursen    Draft
REASON     : Connection request added
REFERENCE  : Task co_sim#28700
DESCRIPTION: Connection request added

VERSION    : 3_for_pmd_only      20-Oct-2003    Erik Laursen    Draft
REASON     : Add misc 
REFERENCE  : Task co_sim#28700
DESCRIPTION: Add: Application sel,
                  Release 4 CPHS
                  Release 4 SPN
                  FDN check  

VERSION    : 1.1      22-Sep-2003    Erik Laursen    Draft
REASON     : EAP and SPN rel 4 support
REFERENCE  : Task co_sim#28700
DESCRIPTION: EAP and SPN rel 4 support

VERSION    : 2    15-Sep-2003    Nikolaj Skov Hansen    Draft
REASON     : New interface for Release 4 features
REFERENCE  : Task co_sim#28384,
             RM-RIM SCO: 006-1534, 006-1535, 006-1856 and 006-1795,
             ActionDB for SWAM NH03080142373 (Change Request),
             ActionDB for SWAM EL03072431349 (Change Request),
             ActionDB for SWAM NH03090353110 (Inspection Agenda)
DESCRIPTION: Status SIM_SERV_ILLEGAL_NUMBER changed value to 0x2e.

VERSION    : 1      1-may-2003    Erik Laursen    Draft
REASON     : First version of sim_isi_m.h
REFERENCE  : Task co_sim#24259
DESCRIPTION: This version of sim_isi_m.h is only intented for PMD support
             Not for generation of ISI header file.
             This initial version only contains support for a limited number
             of ISI Requests.
*/

#ifndef SIM_ISI_VERSION
#define SIM_ISI_VERSION
#define SIM_ISI_VERSION_Z   20
#define SIM_ISI_VERSION_Y   1  /* minor */
#endif


#ifndef _SIM_ISI_M_H_
#define _SIM_ISI_M_H_

/* This flag is to be defined if the sim_isi.h interface file is to be used WITHOUT inclusion of sim_isi_common_str.h 
   (e.g. by SYMBIAN products). Later on sim_isi_common_str.h will be removed and the structures moved permanently to 
   sim_isi.h */
/*
#define S60_INTERFACE
*/

#ifndef S60_INTERFACE
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"sim_fea_conf.h\"         /*SIM_AVOID_GCC_PADDING - SIM_HYBRID*/")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"sim_isi_common_str.h\"")
COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#include \"comm_isi.h\"")
#endif

/*  3    CONSTANTS */

/* CONSTANTS for compilation purpose in local environment */

#define PR_NUMBER_LENGTH            48
#define PR_NAME_LENGTH              50
#define PR_TEXT_LENGTH              60
#define COMM_MAX_FTD_STRING_LENGTH 124

#define SIM_MAX_NBR_OF_CBMIDS        5

/*----------------------------------------------*/

/* --------------------------------------------------------------------- */
/* Message ID's                                                          */
/* --------------------------------------------------------------------- */
#define SIM_TABLE_END                           0

#define SIM_PIN_VERIFY_REQ                      1
#define SIM_PIN_VERIFY_RESP                     2

#define SIM_PIN_CHANGE_REQ                      3
#define SIM_PIN_CHANGE_RESP                     4

#define SIM_PIN_ENABLE_REQ                      5
#define SIM_PIN_ENABLE_RESP                     6

#define SIM_PIN_UNBLOCK_REQ                     7
#define SIM_PIN_UNBLOCK_RESP                    8

#define SIM_PIN_STATE_GET_REQ                   9
#define SIM_PIN_STATE_GET_RESP                  10

#define SIM_PN_READ_REQ                         15
#define SIM_PN_READ_RESP                        16

#define SIM_PN_WRITE_REQ                        17
#define SIM_PN_WRITE_RESP                       18

#define SIM_READ_TABLE_REQ                      19
#define SIM_READ_TABLE_RESP                     20

#define SIM_ACM_REQ                             21
#define SIM_ACM_RESP                            22

#define SIM_PUCT_REQ                            23
#define SIM_PUCT_RESP                           24

#define SIM_NETWORK_INFO_REQ                    25
#define SIM_NETWORK_INFO_RESP                   26

#define SIM_IMSI_REQ                            29
#define SIM_IMSI_RESP                           30

#define SIM_PREF_LANGUAGE_REQ                   31
#define SIM_PREF_LANGUAGE_RESP                  32

#define SIM_SERV_PROV_NAME_REQ                  33
#define SIM_SERV_PROV_NAME_RESP                 34

#define SIM_DATA_SIZES_REQ                      35
#define SIM_DATA_SIZES_RESP                     36

#define SIM_HOME_ZONE_REQ                       37
#define SIM_HOME_ZONE_RESP                      38

#define SIM_JACOB_REQ                           39
#define SIM_JACOB_RESP                          40

#define SIM_DYNAMIC_FLAGS_REQ                   41
#define SIM_DYNAMIC_FLAGS_RESP                  42

#define SIM_VOICE_MSG_REQ                       43
#define SIM_VOICE_MSG_RESP                      44

#define SIM_CALL_FWD_REQ                        45
#define SIM_CALL_FWD_RESP                       46

#define SIM_CPHS_REQ                            47
#define SIM_CPHS_RESP                           48

#define SIM_CSP_REQ                             49
#define SIM_CSP_RESP                            50

#define SIM_OPERATOR_REQ                        51
#define SIM_OPERATOR_RESP                       52

#define SIM_TARIFF_REQ                          53
#define SIM_TARIFF_RESP                         54

#define SIM_READ_ACM_ACCESS_REQ                 57
#define SIM_READ_ACM_ACCESS_RESP                58

#define SIM_IMSI_EQUAL_REQ                      59
#define SIM_IMSI_EQUAL_RESP                     60

#define SIM_READ_EMERG_CODES_REQ                61
#define SIM_READ_EMERG_CODES_RESP               62

#define SIM_GSM_DIR_REQ                         63
#define SIM_GSM_DIR_RESP                        64

#define SIM_READ_CI_REQ                         96
#define SIM_READ_CI_RESP                        97

#define SIM_VIAG_HOME_ZONE_REQ                  98
#define SIM_VIAG_HOME_ZONE_RESP                 99

/* READ_FIELD                                   100 */
/* ACC                                          101 */
/* ICC                                          102 */
/* AD                                           103 */

#define SIM_FDN_CHECK_REQ                       104
#define SIM_FDN_CHECK_RESP                      105

#define SIM_MMS_REQ                             106
#define SIM_MMS_RESP                            107

#define SIM_IMS_REQ                             108
#define SIM_IMS_RESP                            109

#define SIM_ESN_MEID_EQUAL_IND                  110
#define SIM_ESN_MEID_EQUAL_REQ                  111
#define SIM_ESN_MEID_EQUAL_RESP                 112

#define SIM_TRACFONE_SIMLOCK_STATUS_REQ         113
#define SIM_TRACFONE_SIMLOCK_STATUS_RESP        114

#define SIM_PIN_ATTEMPTS_LEFT_REQ               115
#define SIM_PIN_ATTEMPTS_LEFT_RESP              116

#define SIM_TRACFONE_REQ                        117
#define SIM_TRACFONE_RESP                       118

#define SIM_TRACFONE_NTF                        119

#define SIM_AM_REQ                              130
#define SIM_AM_RESP                             131

#define SIM_AM_IND                              140

#define SIM_READ_FIELD_REQ                      186
#define SIM_READ_FIELD_RESP                     187

#define SIM_SMS_REQ                             188
#define SIM_SMS_RESP                            189

/*define APDU_REQ                                190
#define APDU_RESP                               191*/

#define SIM_STATUS_REQ                          192
#define SIM_STATUS_RESP                         193

#define SIM_GPRS_REQ                            200
#define SIM_GPRS_RESP                           201

#define SIM_SAT_REQ                             208
#define SIM_SAT_RESP                            209

#define SIM_GAIT_REQ                            210 
#define SIM_GAIT_RESP                           211 

#define SIM_CS_READ_REQ                         212
#define SIM_CS_READ_RESP                        213

#define SIM_CS_WRITE_REQ                        214
#define SIM_CS_WRITE_RESP                       215

#define SIM_AUTHENTICATION_REQ                  216
#define SIM_AUTHENTICATION_RESP                 217

#define SIM_APP_SELECTION_REQ                   218
#define SIM_APP_SELECTION_RESP                  219

#define SIM_PB_REQ                              220
#define SIM_PB_RESP                             221

#define SIM_ICC_TYPE_REQ                        222
#define SIM_ICC_TYPE_RESP                       223

#define SIM_CONNECTION_REQ                      224
#define SIM_CONNECTION_RESP                     225

#define SIM_ATK_REQ                             226
#define SIM_ATK_RESP                            227

#define SIM_REFRESH_REQ                         228
#define SIM_REFRESH_RESP                        229
#define SIM_REFRESH_NTF                         230

#define SIM_ACL_IND                             231
#define SIM_IMS_IND                             232
#define SIM_PB_IND                              234
#define SIM_ICC_TYPE_IND                        235
#define SIM_SERVER_READY_IND                    237
#define SIM_CS_IND                              238 
#define SIM_IND                                 239

/* --------------------------------------------------------------------- */
/* Sub block ID's                                                        */
/* --------------------------------------------------------------------- */

#define SIM_SB_MOBILE_IDENTIFICATION_NUMBER                      0x01
#define SIM_SB_ACCESS_OVERLOAD_CLASS                             0x02
#define SIM_SB_SYSTEM_ID                                         0x03
#define SIM_SB_HOME_SYSTEM_OPERATOR_CODE_AND_MOBILE_COUNTRY_CODE 0x04
#define SIM_SB_INITIAL_PAGING_CHANNEL                            0x05
#define SIM_SB_GROUP_ID                                          0x06
#define SIM_SB_SIM_ELECTRONIC_SERIAL_NUMBER                      0x07
#define SIM_SB_AMPS_USAGE_INDICATORS                             0x08
#define SIM_SB_ANSI_136_USAGE_INDICATORS                         0x09
#define SIM_SB_ALPHA_TAGS                                        0x0A
#define SIM_SB_COOPERATIVE_SOC_LIST                              0x0B
#define SIM_SB_IRDB_VERSION_TABLE                                0x0C
#define SIM_SB_PARTNER_SID_LIST                                  0x0D
#define SIM_SB_POSITIVE_FAVORED_SID_LIST                         0x0E
#define SIM_SB_NEGATIVE_FORBIDDEN_SID_LIST                       0x0F
#define SIM_SB_PARTNER_SOC_LIST                                  0x10
#define SIM_SB_FAVORED_SOC_LIST                                  0x11
#define SIM_SB_FORBIDDEN_SOC_LIST                                0x12
#define SIM_SB_IRDB_PARAMETER                                    0x13
#define SIM_SB_BAND_AND_SUB_BAND_PRIORITY_ORDER                  0x14
#define SIM_SB_NAM_PSIDS_AND_RSIDS                               0x15
#define SIM_SB_TEST_REGISTRATION_PSIDS_AND_RSIDS                 0x16
#define SIM_SB_REG_ACCEPT_PSIDS_AND_RSIDS                        0x17
#define SIM_SB_SS_FEATURE_CODE_TABLE                             0x18
#define SIM_SB_TRIGGERED_SCAN_TIMERS                             0x19
#define SIM_SB_REGISTRATION_THRESHOLD                            0x1A
#define SIM_SB_GSM_ANSI_136_SIM_PHASE_ID                         0x1B
#define SIM_SB_TELESERVICE_SERVER_ADDRESS_INFO                   0x1C
#define SIM_SB_BAND_HISTORY_TABLE                                0x1D
#define SIM_SB_DCCH_HISTORY_TABLE                                0x1E
#define SIM_SB_ADDITIONAL_USER_REGISTRATION_PARAMETERS           0x1F
#define SIM_SB_USER_GROUP_ID_INFO                                0x20  
#define SIM_SB_SOC_DEPERSONALIZATION_CONTROL_KEY                 0x21 

#define SIM_SB_CS_START                         100 
#define SIM_SB_ACC_ID                           (SIM_SB_CS_START + 0)
#define SIM_SB_BCCH_ID                          (SIM_SB_CS_START + 1)
#define SIM_SB_CARD_TYPE_ID                     (SIM_SB_CS_START + 2)
#define SIM_SB_CIPHERING_KEY_ID                 (SIM_SB_CS_START + 3)
#define SIM_SB_CIPHERING_KEY_SNR_ID             (SIM_SB_CS_START + 4)
#define SIM_SB_FORBIDDEN_PLMNS_ID               (SIM_SB_CS_START + 5)
#define SIM_SB_GPRS_CIPHERING_KEY_ID            (SIM_SB_CS_START + 6)
#define SIM_SB_GPRS_CIPHERING_KEY_SNR_ID        (SIM_SB_CS_START + 7)
#define SIM_SB_GPRS_RAI_ID                      (SIM_SB_CS_START + 8)
#define SIM_SB_GPRS_RAUS_ID                     (SIM_SB_CS_START + 9)
#define SIM_SB_GPRS_TMSI_ID                     (SIM_SB_CS_START + 10)
#define SIM_SB_GPRS_TMSI_SIGN_VALUE_ID          (SIM_SB_CS_START + 11)
#define SIM_SB_HPLMN_ID                         (SIM_SB_CS_START + 12)
#define SIM_SB_HPLMN_SEARCH_ID                  (SIM_SB_CS_START + 13)
#define SIM_SB_IMSI_ID                          (SIM_SB_CS_START + 14)
#define SIM_SB_LAI_ID                           (SIM_SB_CS_START + 15)
#define SIM_SB_TMSI_ID                          (SIM_SB_CS_START + 16)
#define SIM_SB_UMTS_CS_KSI_ID                   (SIM_SB_CS_START + 17)
#define SIM_SB_UMTS_CS_CIPHERING_KEY_ID         (SIM_SB_CS_START + 18)
#define SIM_SB_UMTS_CS_INTEGRITY_KEY_ID         (SIM_SB_CS_START + 19)
#define SIM_SB_UMTS_PS_KSI_ID                   (SIM_SB_CS_START + 20)
#define SIM_SB_UMTS_PS_CIPHERING_KEY_ID         (SIM_SB_CS_START + 21)
#define SIM_SB_UMTS_PS_INTEGRITY_KEY_ID         (SIM_SB_CS_START + 22)
#define SIM_SB_UMTS_START_PS_ID                 (SIM_SB_CS_START + 23)
#define SIM_SB_UMTS_START_MAX_ID                (SIM_SB_CS_START + 24)
#define SIM_SB_UMTS_START_CS_ID                 (SIM_SB_CS_START + 25)
#define SIM_SB_LOC_UPD_STATUS_ID                (SIM_SB_CS_START + 26)
#define SIM_SB_OPERATOR_PLMN_ID                 (SIM_SB_CS_START + 27)
#define SIM_SB_USER_PLMN_ID                     (SIM_SB_CS_START + 28)
#define SIM_SB_HOME_PLMN_ID                     (SIM_SB_CS_START + 29)
#define SIM_SB_RPLMN_ID                         (SIM_SB_CS_START + 30)
#define SIM_SB_ECC_ID                           (SIM_SB_CS_START + 31)
#define SIM_SB_PLMN_SELECTOR_ID                 (SIM_SB_CS_START + 32)  
#define SIM_SB_FULL_NETWORK_NAME                (SIM_SB_CS_START + 33)  
#define SIM_SB_SHORT_NETWORK_NAME               (SIM_SB_CS_START + 34)  
#define SIM_SB_GSM_NETPAR_ID                    (SIM_SB_CS_START + 35)
#define SIM_SB_FDD_NETPAR_ID                    (SIM_SB_CS_START + 36)
#define SIM_SB_TDD_NETPAR_ID                    (SIM_SB_CS_START + 37)
#define SIM_SB_EQUIVALENT_HPLMNS_ID             (SIM_SB_CS_START + 38)
#define SIM_SB_ATT_RAT_ID                       (SIM_SB_CS_START + 39)

#define SIM_SB_APP_SELECTION                    150
#define SIM_SB_SPN_DISPLAY_INFO_PLMNS_ID        151
#define SIM_SB_APP_SELECTION_UNICODE            152

#define SIM_SB_SOLSA_START                      1
#define SIM_SB_LSA_INFO_ID                      (SIM_SB_SOLSA_START + 0)
#define SIM_SB_SOLSA_END                        (SIM_SB_SOLSA_START + 1)

#define SIM_SB_AUT_START                        300
#define SIM_SB_UMTS_AUTN_PARAMS_ID              (SIM_SB_AUT_START + 0)
#define SIM_SB_RES_PARAMS_ID                    (SIM_SB_AUT_START + 1)
#define SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID         (SIM_SB_AUT_START + 2)
#define SIM_SB_RAND_PARAMS_ID                   (SIM_SB_AUT_START + 3)
#define SIM_SB_AUT_END                          (SIM_SB_AUT_START + 4)


#define SIM_PB_SB_START                         200 
#define SIM_PB_ADN                              (SIM_PB_SB_START + 0)
#define SIM_PB_ADN_NUMBER_LENGTH                (SIM_PB_SB_START + 1)
#define SIM_PB_ANR                              (SIM_PB_SB_START + 2)
#define SIM_PB_BDN                              (SIM_PB_SB_START + 3)
#define SIM_PB_CC                               (SIM_PB_SB_START + 4)
#define SIM_PB_CCP                              (SIM_PB_SB_START + 5)
#define SIM_PB_CCP1                             (SIM_PB_SB_START + 6)
#define SIM_PB_CCP2                             (SIM_PB_SB_START + 7)
#define SIM_PB_CONF_ADN_SB                      (SIM_PB_SB_START + 8)
#define SIM_PB_CONF_ANR_SB                      (SIM_PB_SB_START + 9)
#define SIM_PB_CONF_EMAIL_SB                    (SIM_PB_SB_START + 10)
#define SIM_PB_CONF_FDN_SB                      (SIM_PB_SB_START + 11)
#define SIM_PB_CONF_GAS_SB                      (SIM_PB_SB_START + 12)
#define SIM_PB_CONF_GRP_SB                      (SIM_PB_SB_START + 13)
#define SIM_PB_CONF_MISC_SB                     (SIM_PB_SB_START + 14)
#define SIM_PB_CONF_PH_1                        (SIM_PB_SB_START + 15)
#define SIM_PB_CONF_PH_3                        (SIM_PB_SB_START + 16)
#define SIM_PB_CONF_SNE_SB                      (SIM_PB_SB_START + 17)
#define SIM_PB_CONF_AAS_SB                      (SIM_PB_SB_START + 18)
#define SIM_PB_DELETE_ALL                       (SIM_PB_SB_START + 19)
#define SIM_PB_DELETE_LOCATION                  (SIM_PB_SB_START + 20)
#define SIM_PB_EMAIL                            (SIM_PB_SB_START + 21)
#define SIM_PB_FDN                              (SIM_PB_SB_START + 22)
#define SIM_PB_FDN_LIST_STATUS                  (SIM_PB_SB_START + 23)
#define SIM_PB_FDN_NUMBER_LENGTH                (SIM_PB_SB_START + 24)
#define SIM_PB_GAS                              (SIM_PB_SB_START + 25)
#define SIM_PB_GRP                              (SIM_PB_SB_START + 26)
#define SIM_PB_HIDDEN                           (SIM_PB_SB_START + 27)
#define SIM_PB_INFO_REQUEST                     (SIM_PB_SB_START + 28)
#define SIM_PB_LDN                              (SIM_PB_SB_START + 29)
#define SIM_PB_LOC                              (SIM_PB_SB_START + 30)
#define SIM_PB_LOC_ANR                          (SIM_PB_SB_START + 31)
#define SIM_PB_LOC_EMAIL                        (SIM_PB_SB_START + 32)
#define SIM_PB_LOC_FIRST                        (SIM_PB_SB_START + 33)
#define SIM_PB_LOC_GAS                          (SIM_PB_SB_START + 34)
#define SIM_PB_LOC_GRP                          (SIM_PB_SB_START + 35)
#define SIM_PB_LOC_NEXT                         (SIM_PB_SB_START + 36)
#define SIM_PB_LOC_SNE                          (SIM_PB_SB_START + 37)
#define SIM_PB_LOC_AAS                          (SIM_PB_SB_START + 38)
#define SIM_PB_MSISDN_NUMBER_LENGTH             (SIM_PB_SB_START + 39)
#define SIM_PB_PBC                              (SIM_PB_SB_START + 40)
#define SIM_PB_PSC                              (SIM_PB_SB_START + 41)
#define SIM_PB_PUID                             (SIM_PB_SB_START + 42)
#define SIM_PB_ROOM_INFO_ERROR                  (SIM_PB_SB_START + 43)
#define SIM_PB_ROOM_INFO_REQUEST                (SIM_PB_SB_START + 44)
#define SIM_PB_SDN                              (SIM_PB_SB_START + 45)
#define SIM_PB_SELECT_PB_SB                     (SIM_PB_SB_START + 46)
#define SIM_PB_SNE                              (SIM_PB_SB_START + 47)
#define SIM_PB_STARTUP_PHASE_1                  (SIM_PB_SB_START + 48)
#define SIM_PB_STARTUP_PHASE_2                  (SIM_PB_SB_START + 49)
#define SIM_PB_STARTUP_PHASE_3                  (SIM_PB_SB_START + 50)
#define SIM_PB_STATUS                           (SIM_PB_SB_START + 51)
#define SIM_PB_UID                              (SIM_PB_SB_START + 52)
#define SIM_PB_AAS                              (SIM_PB_SB_START + 53)
#define SIM_PB_LOCATION                         (SIM_PB_SB_START + 54)
#define SIM_PB_LOCATION_SEARCH                  (SIM_PB_SB_START + 55)
#define SIM_PB_MSISDN                           (SIM_PB_SB_START + 56)
#define SIM_PB_VMBX                             (SIM_PB_SB_START + 57)
#define SIM_PB_LOC_VMBX                         (SIM_PB_SB_START + 58)
#define SIM_PB_VMBX_NUMBER_LENGTH               (SIM_PB_SB_START + 59)
#define SIM_PB_LOC_BDN                          (SIM_PB_SB_START + 60)
#define SIM_PB_BDN_NUMBER_LENGTH                (SIM_PB_SB_START + 61)
#define SIM_PB_MBDN                             (SIM_PB_SB_START + 62)
#define SIM_PB_CONF_ADN_LONG_SB                 (SIM_PB_SB_START + 63)
#define SIM_PB_CONF_ANR_LONG_SB                 (SIM_PB_SB_START + 64)
#define SIM_PB_CONF_EMAIL_LONG_SB               (SIM_PB_SB_START + 65)
#define SIM_PB_CONF_SNE_LONG_SB                 (SIM_PB_SB_START + 66)
#define SIM_PB_CONF_GRP_LONG_SB                 (SIM_PB_SB_START + 67)
#define SIM_PB_SB_END                           (SIM_PB_SB_START + 68)



#define SIM_SB_PLMN_RECORD_LEN                  4

#define SIM_FDN_CHECK_SB_START                  180
#define SIM_SB_PHONE_NUMBER_FIELD_ID            (SIM_FDN_CHECK_SB_START + 0)
#define SIM_SB_SMS_DEST_ADR_ID                  (SIM_FDN_CHECK_SB_START + 1)
#define SIM_SB_SMSC_ADR_ID                      (SIM_FDN_CHECK_SB_START + 2)

#define SIM_SB_ICC_START                        0x0190 /* 400 */
#define SIM_SB_ICC_TYPE_ID                      ( SIM_SB_ICC_START + 0 )
#define SIM_SB_AID_ID                           ( SIM_SB_ICC_START + 1 )
#define SIM_SB_ICCID_ID                         ( SIM_SB_ICC_START + 2 )
#define SIM_SB_REFRESH_FILE_ID                  ( SIM_SB_ICC_START + 3 )
#define SIM_SB_ICON_DATA_ID                     ( SIM_SB_ICC_START + 4 )
#define SIM_SB_ICON_DATA_CLUT_ID                ( SIM_SB_ICC_START + 5 )
#define SIM_SB_ICON_BODY_DATA_ID                ( SIM_SB_ICC_START + 6 )

/* Start of SMS subblocks */
#define SIM_SB_SMS_START                        0x015E /* 350 */
#define SIM_SB_SMS_DELIVER_ID                   SIM_SB_SMS_START + 0 
#define SIM_SB_SMS_STATUS_REPORT_ID             SIM_SB_SMS_START + 1 
#define SIM_SB_SMS_SUBMIT_ID                    SIM_SB_SMS_START + 2 
#define SIM_SB_SMS_COMMAND_ID                   SIM_SB_SMS_START + 3 
#define SIM_SB_SMS_MO_UNDEFINED_ID              SIM_SB_SMS_START + 4 
#define SIM_SB_SMS_MT_UNDEFINED_ID              SIM_SB_SMS_START + 5 
#define SIM_SB_SMS_ADDRESS_ID                   SIM_SB_SMS_START + 6 
#define SIM_SB_SMS_COMMON_DATA_ID               SIM_SB_SMS_START + 7 
#define SIM_SB_SMS_VALIDITY_PERIOD_ID           SIM_SB_SMS_START + 8 

/* Start of CPHS subblocks */
#define SIM_SB_CPHS_START                       0x01A4 /* 420 */
#define SIM_SB_CPHS_MSG_FLAGS_ID                SIM_SB_CPHS_START + 0
#define SIM_SB_REL4_MSG_FLAGS_ID                SIM_SB_CPHS_START + 1
#define SIM_SB_CPHS_CALL_FWD_FLAGS_ID           SIM_SB_CPHS_START + 2
#define SIM_SB_REL4_CALL_FWD_FLAGS_ID           SIM_SB_CPHS_START + 3

/* Start of MMS subblocks */
#define SIM_SB_MMS_START                        0x01AE /* 430 */
#define SIM_SB_MMS_CONNECTIVITY_PARAMETERS_ID   SIM_SB_MMS_START + 0
#define SIM_SB_MMS_USER_PREFERENCES_ID          SIM_SB_MMS_START + 1

/* Start of IMS subblocks */
#define SIM_SB_IMS_START                        0x01B8 /* 440 */
#define SIM_SB_IMS_PRIVATE_USER_ID              SIM_SB_IMS_START + 0
#define SIM_SB_IMS_PUBLIC_USER_ID               SIM_SB_IMS_START + 1
#define SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID       SIM_SB_IMS_START + 2

/* Start of SIM_CONNECTION_REQ subblocks */
#define  SIM_SB_CONNECTION_ID                   450

/* Start of EAP subblocks */
#define  SIM_SB_EAP_START                       0x01CC /* 460 */
#define  SIM_SB_EAP_INTEGRITY_KEY_ID            SIM_SB_EAP_START + 0
#define  SIM_SB_EAP_CIPHERING_KEY_ID            SIM_SB_EAP_START + 1

/* Start of AM subblocks */
#define  SIM_SB_AM_START                       0x0200 /* 512 */
/* #define  SIM_SB_AM_HANDLE_ID                SIM_SB_AM_START + 0  this sb has been moved to sim_shared_isi_m.h from 018.000. */
#define  SIM_SB_AM_APP_LABEL_ID                SIM_SB_AM_START + 1
#define  SIM_SB_AM_APP_INFO_RECORD_ID          SIM_SB_AM_START + 2
#define  SIM_SB_AM_FILE_DATA_ID_ID             SIM_SB_AM_START + 3
#define  SIM_SB_AM_SERVICE_ID_ID               SIM_SB_AM_START + 4
#define  SIM_SB_AM_GBA_B_TID_ID                SIM_SB_AM_START + 5
#define  SIM_SB_AM_GBA_KEY_LIFETIME_ID         SIM_SB_AM_START + 6
#define  SIM_SB_AM_GBA_NAF_ID_ID               SIM_SB_AM_START + 7
#define  SIM_SB_AM_GBA_GBANL_RECORD_ID         SIM_SB_AM_START + 8
#define  SIM_SB_AM_GBA_KS_EXT_NAF_ID           SIM_SB_AM_START + 9
#define  SIM_SB_AM_MBMS_MSK_RECORD_ID          SIM_SB_AM_START + 10
#define  SIM_SB_AM_MBMS_MUK_RECORD_ID          SIM_SB_AM_START + 11
#define  SIM_SB_AM_MBMS_MIKEY_ID               SIM_SB_AM_START + 12
#define  SIM_SB_AM_MBMS_MTK_SALT_ID            SIM_SB_AM_START + 13
#define  SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID       SIM_SB_AM_START + 14
#define  SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID   SIM_SB_AM_START + 15
#define  SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID              SIM_SB_AM_START + 16
#define  SIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH_ID  SIM_SB_AM_START + 17
#define  SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID       SIM_SB_AM_START + 18
#define  SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID                 SIM_SB_AM_START + 19
#define  SIM_SB_AM_BCAST_SPE_USER_PURSE_ID                  SIM_SB_AM_START + 20
#define  SIM_SB_AM_BCAST_SPE_LIVE_PPT_PURSE_ID              SIM_SB_AM_START + 21
#define  SIM_SB_AM_BCAST_SPE_PLAYBACK_PPT_PURSE_ID          SIM_SB_AM_START + 22
#define  SIM_SB_AM_BCAST_SPE_KEPT_TEK_COUNTER_ID            SIM_SB_AM_START + 23
#define  SIM_SB_AM_BCAST_KEY_GROUP_DESCRIPTION_ID           SIM_SB_AM_START + 24
#define  SIM_SB_AM_BCAST_SPE_KEY_PROPERTIES_ID              SIM_SB_AM_START + 25
#define  SIM_SB_AM_BCAST_SPE_COST_VALUE_ID                  SIM_SB_AM_START + 26
#define  SIM_SB_AM_BCAST_SPE_PLAYBACK_COUNTER_ID            SIM_SB_AM_START + 27
#define  SIM_SB_AM_BCAST_SPE_TEK_COUNTER_ID                 SIM_SB_AM_START + 28
#define  SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID                 SIM_SB_AM_START + 29
#define  SIM_SB_AM_BCAST_SPE_PARENTAL_RATING_ID             SIM_SB_AM_START + 30
#define  SIM_SB_AM_BCAST_SPE_PARENTAL_CONTROL_OPERATION_ID  SIM_SB_AM_START + 31
#define  SIM_SB_AM_BCAST_TEK_DATA_ID                        SIM_SB_AM_START + 32
#define  SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID             SIM_SB_AM_START + 33
#define  SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID              SIM_SB_AM_START + 34
#define  SIM_SB_AM_BCAST_REC_TS_INTERVAL_ID                 SIM_SB_AM_START + 35
#define  SIM_SB_AM_BCAST_SPE_AVAILABLE_NR_OF_REC_ID         SIM_SB_AM_START + 36
#define  SIM_SB_AM_BCAST_REC_CONTENT_DESCRIPTION_ID         SIM_SB_AM_START + 37

/* Next range of subblocks to be allocated in range: SIM_SB_AM_START + 256 = 0x0300 */
/* #define  SIM_SB_XXX_START                   0x0300 */ /* 768 */

/* MISC subblocks */

#define SIM_SB_TO_BE_DELETED_ONE                1
#define SIM_SB_TO_BE_DELETED_TWO                2


/* Other constants */

#define MAX_CODE_LEN                            9
#define SIM_LANG_PREF_LEN                       4   
#define SIM_SMS_TIME_STAMP_LEN                  0x07
#define SMS_ALPHA_TAG_MAX_LENGTH                16  
/*#define SMS_ALPHA_TAG_MAX_LENGTH_PLUS_ONE  SMS_ALPHA_TAG_MAX_LENGTH + 1*/
#define SIM_SERV_PROV_NAME_LEN                  16
#define SIM_PLMN_SELECTOR_LIST_LEN              84 

#define SIM_MAX_NBR_OF_JACOB_IDS                32

/* RUIM */
#define SIM_STA_RUIM_OFF                         0x66
#define SIM_ST_RUIM_OPERATIONAL_MODE             0x02


#define MAX_NAME_LEN                            PR_NAME_LENGTH
#define MAX_NUM_LEN                             PR_NUMBER_LENGTH

#define SIM_NAME_LEN                            (PR_NAME_LENGTH + 1) /* incl. zero termination */
#define SIM_TEXT_LEN                            (PR_TEXT_LENGTH + 1) /* incl. zero termination */
#define SIM_MAX_NUMBER_OF_TAGS                  10
#define SIM_NUMBER_LEN                          (PR_NUMBER_LENGTH + 1) /* incl. zero termination */
#define SIM_BLOCK_TYPE_ISI                      0
#define SIM_BLOCK_TYPE_MSG                      1
#define SIM_IMSI_DFIELD_LEN                     9
#define SIM_IMSI_LEN                            8
#define SIM_TMSI_LEN                            4
#define SIM_CIPH_KEY_LEN                        8
#define SIM_HPLMN_LEN                           3
#define SIM_ONE_PLMN_LEN                        3
#define SIM_BCCH_INFO_LEN                       16
#define SIM_ACC_CTRL_LEN                        2
#define SIM_PLMN_LEN                            3
#define SIM_LAI_LEN                             5
#define SIM_ICC_ID_LEN                          10
#define SIM_GPRS_CIPH_KEY_LEN                   8
#define SIM_GPRS_TMSI_LEN                       4
#define SIM_GPRS_TMSI_SIGN_VAL_LEN              3
#define SIM_PTMSI_LEN                           4
#define SIM_PTMSI_SIG_VAL_LEN                   3
#define SIM_RAI_LEN                             6
#define SIM_LSA_DESC_FILE_ID_LEN                2
#define SIM_UMTS_CS_CIPH_KEY_LEN                16
#define SIM_UMTS_CS_INTE_KEY_LEN                16
#define SIM_UMTS_PS_CIPH_KEY_LEN                16
#define SIM_UMTS_PS_INTE_KEY_LEN                16
#define SIM_UMTS_CS_HFN_LEN                     3
#define SIM_UMTS_PS_HFN_LEN                     3
#define SIM_UMTS_START_MAX_LEN                  3
#define SIM_RND_PARAMS_LEN                      16
#define SIM_UMTS_AUTN_PARAMS_LEN                16
#define SIM_UMTS_AUTS_PARAMS_LEN                14
#define SIM_RES_MAX_LEN                         16
#define SIM_EAP_CIPH_KEY_LEN                    16
#define SIM_EAP_INTE_KEY_LEN                    16

#define SIM_AID_MAX_LENGTH                      16
#define ICCID_LENGTH                            10
#define RPLMN_LAST_USED_AT_LEN                  2

#define SIM_PLMN_ACCESS_TECHNOLOGY_LEN          2
#define SIM_PUCT_CURRENCY_CODE_LEN              (3+1)
#define SIM_FILE_PATH_LEN                       8
#define READ_FIELD_OFFSET_LEN                   2

#define SMS_ADDRESS_MAX_LENGTH                  12

#define SIM_ONE_EMRG_CALL_CODE_LEN              3

#define SIM_MAX_NBR_OF_EMRG_CALL_CODES          5   /*To be defined when sim_isi_common_str.h is removed*/
#define SIM_OPERATOR_NAME_LEN                  24   /*To be defined when sim_isi_common_str.h is removed*/

#define SIM_NBR_OF_CELL_BC_MSG_IDS              15  /*To be defined when sim_isi_common_str.h is removed*/

/*#define SIM_MAX_APDU_LEN                        261
#define SIM_MAX_APDU_DATA_LENGTH                258*/

/* --------------------------------------------------------------------- */
/* Service Types                                                         */
/* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* Service Type definitions for Message ID: SIM_ATK_REQ                  */
    /* --------------------------------------------------------------------- */

#define SIM_ST_REFRESH_INIT_FROM_PIN            0
#define SIM_ST_REFRESH_FCN                      1
#define SIM_ST_REFRESH_INIT_FROM_PIN_FCN        2
#define SIM_ST_REFRESH_INIT_FROM_PIN_FFCN       3
#define SIM_ST_REFRESH_RESET                    4
#define SIM_ST_REFRESH_APPLICATION_RESET        5
#define SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET 6

#define SIM_ST_SET_POLLING                      16
#define SIM_ST_READ_ICON                        17
#define SIM_ST_READ_ICON_CLUT                   18
#define SIM_ST_READ_ICON_BODY_DATA              19
#define SIM_ST_SEND_ENVELOPE                    20
#define SIM_ST_CAT_SUPPORT_ENABLE               21
#define SIM_ST_CAT_SUPPORT_DISABLE              22

/* --------------------------------------------------------------------- */
/* Service Type definitions for Message ID: SIM_PIN_XXX_REQ              */
/* --------------------------------------------------------------------- */

#define PIN                                     1  
#define SIM_ST_PIN                              PIN
#define PIN2                                    2
#define SIM_ST_PIN2                             PIN2 

#define SIM_ST_PIN_UNIVERSAL                    151  

#define SIM_ST_SUBSTITUTE_PIN                   153
#define SIM_ST_SUBSTITUTE_PIN_UNIVERSAL         154 
#define SIM_ST_GET_ACTIVE_PIN                   155

#define PIN_PARENTAL_CONTROL                    167
#define SIM_ST_PIN_PARENTAL_CONTROL             PIN_PARENTAL_CONTROL

/* --------------------------------------------------------------------- */
/* Service Type definitions for Message ID: SIM_PREF_LANGUAGE_REQ        */
/* --------------------------------------------------------------------- */

#define SIM_ST_CARD_STATUS                      0  
#define CARD_STATUS                             SIM_ST_CARD_STATUS      /*Deprecated*/

#define SIM_ST_SIMLOCK_STATUS                   1

/*#define SIM_ST_RUIM_OPERATIONAL_MODE            2*/

#define SIM_ST_READ_PL_LANGUAGE                 1
#define READ_PL_LANGUAGE                        SIM_ST_READ_PL_LANGUAGE /* Deprecated */

#define SIM_ST_READ_LI_LANGUAGE                 2
#define READ_LI_LANGUAGE                        SIM_ST_READ_LI_LANGUAGE /* Deprecated */

#define SIM_ST_WRITE_PL_LANGUAGE                3
#define WRITE_PL_LANGUAGE                       SIM_ST_WRITE_PL_LANGUAGE /* Deprecated */

#define SIM_ST_WRITE_LI_LANGUAGE                4
#define WRITE_LI_LANGUAGE                       SIM_ST_WRITE_LI_LANGUAGE /* Deprecated */

/* --------------------------------------------------------------------- */
/* Service Type definitions for Message ID: SIM_ACM_REQ        */
/* --------------------------------------------------------------------- */


#define SIM_ST_INCREMENT                        18
#define SIM_ACM_INCREMENT_SRV                   SIM_ST_INCREMENT    /*Deprecated*/
    
#define SIM_ST_SET                              19
#define SIM_ACM_SET_SRV                         SIM_ST_SET          /*Deprecated*/    

#define SIM_ST_READ_AOC                         20
#define SIM_ACM_READ_SRV                        SIM_ST_READ_AOC     /*Deprecated*/

#define SIM_ST_MAX_VALUE_SET                    21
#define SIM_ACM_MAX_VALUE_SET_SRV               SIM_ST_MAX_VALUE_SET /*Deprecated*/     

#define SIM_ST_MAX_VALUE_READ                   22
#define SIM_ACM_MAX_VALUE_READ_SRV              SIM_ST_MAX_VALUE_READ /*Deprecated*/    

/* --------------------------------------------------------------------- */
/* Service Type definitions for Message ID: SIM_IMSI_XXX_REQ             */
/* --------------------------------------------------------------------- */

#define READ_IMSI                               45

/* --------------------------------------------------------------------- */
/* Service Types for SIM_SERV_PROV_NAME_REQ                              */
/* --------------------------------------------------------------------- */

#define SIM_ST_SPN_DISPLAY_INFO                 1 
#define SIM_ST_READ_SERV_PROV_NAME              44 
#define READ_SERV_PROV_NAME                     SIM_ST_READ_SERV_PROV_NAME /* Deprecated */

/* --------------------------------------------------------------------- */
/* Service Types for SIM_VOICE_MSG_REQ and SIM_CALL_FWD_REQ              */
/* --------------------------------------------------------------------- */

#define SIM_ST_WRITE_MSG_FLAGS                  1
#define SIM_ST_READ_MSG_FLAGS                   2
#define SIM_ST_WRITE_CALL_FWD_FLAGS             3
#define SIM_ST_READ_CALL_FWD_FLAGS              4
#define SIM_ST_WRITE_FLAGS                      57
#define WRITE_FLAGS                             SIM_ST_WRITE_FLAGS /* Deprecated */
#define SIM_ST_READ_FLAGS                       58
#define READ_FLAGS                              SIM_ST_READ_FLAGS /* Deprecated */

/* --------------------------------------------------------------------- */
/* Service types for message ID SIM_APP_SELECTION_REQ                    */
/* --------------------------------------------------------------------- */

#define SIM_ST_GET_NUMBER_OF_APP                1
#define SIM_ST_GET_ALL_APP_LABELS               2
#define SIM_ST_GET_ACTIVE_APP_LABEL             3
#define SIM_ST_SET_DEFAULT_APP                  4
#define SIM_ST_ACTIVATE_APP                     5
#define SIM_ST_SET_APP_SELECTION_AUTOMATIC      6
#define SIM_ST_SET_APP_SELECTION_MANUAL         7
#define SIM_ST_GET_APP_SELECTION_STATUS         8
#define SIM_ST_GET_ISIM_LABEL                   9
#define SIM_ST_GET_LABEL_BY_NO                  10 


/* --------------------------------------------------------------------- */
/* Service types for SIM_CONNECTION_REQ                                  */
/* --------------------------------------------------------------------- */

#define SIM_ST_SIM_DISCONNECT                   1
#define SIM_ST_SIM_CONNECT                      2
#define SIM_ST_SIM_RECONNECT                    3
#define SIM_ST_SIM_CONNECT_FORCED_PIN           4

/* --------------------------------------------------------------------- */
/* Service types for SIM_OPERATOR_REQ                                    */
/* --------------------------------------------------------------------- */

#define SIM_ST_READ_OPL                         19
#define SIM_ST_READ_PNN                         20
#define READ_NAME                               62

/* --------------------------------------------------------------------- */
/* Service types for SIM_PB_REQ                                          */
/* --------------------------------------------------------------------- */

#define SIM_PB_READ                             15
#define SIM_PB_WRITE                            16
#define SIM_PB_GET_CONF                         17
#define SIM_PB_SELECT_PB                        19

/* --------------------------------------------------------------------- */
/* Service types for SIM_PN_READ_REQ and SIM_PN_WRITE_REQ                */
/* NOT TO BE USED IN FUTURE DEVELOPMENT.                                 */
/* --------------------------------------------------------------------- */

#define SIM_ST_ADN                               7   
#define SIM_ST_FDN                               9   
#define SIM_ST_VMBX                             11   
#define SDN                                     73

/* --------------------------------------------------------------------- */
/* Service Types for SIM_REFRESH_REQ and SIM_REFRESH_NTF                 */
/* --------------------------------------------------------------------- */

#define SIM_ST_REFRESH_REGISTER                 1
#define SIM_ST_REFRESH_UNREGISTER               2
#define SIM_ST_REFRESH_OK                       3
#define SIM_ST_REFRESH_NOT_OK                   4
#define SIM_ST_REFRESH_DONE                     5
#define SIM_ST_REFRESH_ERROR                    6
#define SIM_ST_REFRESH_REQUESTED                7
#define SIM_ST_REFRESH_NOW                      8
#define SIM_ST_REFRESH_CANCELLED                9
#define SIM_ST_REFRESH_STARTING                10


/* --------------------------------------------------------------------- */
/* Service Types for SIM_MMS_REQ                                         */
/* --------------------------------------------------------------------- */

#define SIM_ST_MMS_ICP_READ                     1
#define SIM_ST_MMS_UP_READ                      2

/* --------------------------------------------------------------------- */
/* Service Types for SIM_IMS_REQ                                         */
/* --------------------------------------------------------------------- */
 
#define SIM_ST_IMS_START_SESSION                1
#define SIM_ST_IMS_END_SESSION                  2
#define SIM_ST_IMS_STATUS                       3
#define SIM_ST_IMS_READ_DATA                    4
  
/* --------------------------------------------------------------------- */
/* Service Types for SIM_TRACFONE_REQ and SIM_TRACFONE_NTF               */
/*                                                                       */
/* --------------------------------------------------------------------- */

#define SIM_ST_TRACFONE_STATUS                      1
#define SIM_ST_TRACFONE_COMPLETED_SUCCESS           2
#define SIM_ST_TRACFONE_COMPLETED_FAIL              3
#define SIM_ST_TRACFONE_REQUESTED                   4

/* --------------------------------------------------------------------- */
/* General Service Type definitions                                      */
/* --------------------------------------------------------------------- */

#define SIM_ST_ALL_SERVICES                   5
#define ALL_SERVICES                          SIM_ST_ALL_SERVICES /*Deprecated*/

#define SIM_ST_ADN                            7   
#define ADN                                   SIM_ST_ADN          /*Deprecated*/

#define SIM_ST_FDN                            9   
#define FDN                                   SIM_ST_FDN          /*Deprecated*/

#define SIM_ST_INFONUM                        12   
#define INFONUM                               SIM_ST_INFONUM      /*Deprecated*/
            
#define SIM_ST_INFO                           13
#define INFO                                  SIM_ST_INFO         /*Deprecated*/

#define SIM_ST_JACOB                          14   
#define JACOB                                 SIM_ST_JACOB        /*Deprecated*/

#define READ_PREF_LANGUAGE                    46

#define SIM_ST_APP_SELECTION                  150 

#define NO_SERVICE_TYPE                       250  

/* SIM_CS_READ_REQ */
#define SIM_ST_CS_DATA_READ_REQ                   1
#define SIM_ST_CS_DATA_READ_ALL_REQ               2
#define SIM_ST_CS_STATUS_REQ                      4
#define SIM_ST_CS_DATA_READ_ALL_GSS_REQ           5
#define SIM_ST_CS_DATA_WRITE_REQ                  3

/* SIM_READ_FIELD_REQ */
#define READ_FIELD                              100
#define ACC                                     101
#define ICC                                     102
#define AD                                      103

/* SIM_IMSI_EQUAL_REQ */
#define ICC_EQUAL                               104

/* SIM_SMS_REQ */
#define READ_PARAMETER                           82
#define UPDATE_PARAMETER                         83
#define READ_STATUS                              84
#define WRITE_STATUS                             85
#define SIM_ST_SMS_GET_NUM_OF_LOC              0x01
#define SIM_ST_SMS_READ                        0x02
#define SIM_ST_SMS_WRITE                       0x03
#define SIM_ST_SMS_ERASE                       0x04
#define SIM_ST_SMS_UPDATE_STATUS               0x05
#define SIM_ST_SMS_READ_RAW                    0x06
#define SIM_ST_SMS_WRITE_RAW                   0x07

/* SIM_DYNAMIC_FLAGS_REQ */
#define READ_DYN_FLAGS                           53
#define WRITE_DYN_FLAGS                          54
#define READ_DYN2_FLAGS                          55
#define WRITE_DYN2_FLAGS                         56

/* SIM_GSM_DIR_REQ */
#define UPDATE_CB_MSGIDS                        105
#define READ_CB_MSG_IDS                          72

/* SIM_NETWORK_INFO_REQ */
#define READ_HPLMN                               47
#define WRITE_FIRST_PLMN                         49

/* SIM_CPHS_REQ */
#define READ_DATA                                63

/* SIM_CSP_REQ */
#define READ_LINE_DATA                           59

/* SIM_SAT_REQ */
#define READ_CBMIDS                             108

/* SIM_VIAG_HOME_ZONE_REQ */
#define READ_PARAM                               76
#define READ_CACHE                               77
#define WRITE_CACHE                              78
#define SIM_ST_READ_SUBSCRIBED_LAC_CI            79
#define SIM_ST_READ_HZ_TAGS                      80
#define SIM_ST_READ_UHZIUE_SETTINGS              81
#define SIM_ST_WRITE_UHZIUE_SETTINGS             82

/* SIM_HOME_ZONE_REQ */
#define CHECK_CELL_ID                            51
#define READ_COORDINATES                         65

/* SIM_IND */
#define PREF_LANGUAGE                            70
#define EMERGENCY_CODES                          71

/* SIM_JACOB_REQ */
#define READ_ID                                  52
#define READ_REAL_JACOB_IDS                     106

/* SIM_TARIFF_REQ: Don't use in future development. */
#define READ_PACKAGE                             64

/* SIM_GPRS_REQ */
#define SIM_ST_ACL_STATUS                       118
#define SIM_ST_ACL_ENABLE                       119
#define SIM_ST_ACL_DISABLE                      120
#define SIM_ST_ACL_READ                         121
#define SIM_ST_ACL_WRITE                        122
#define SIM_ST_CHECK_APN                        123

/*  4    MACROS */

#define SIM_MSG_HDR_AUTH \
    VALUE(8, BE, TransactionID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)

/*#define SIM_SERVICE_HEADER \
    SIM_MSG_HEADER \
    REFERENCE(8, BE, ServiceType, "ServiceType", SUB_MSG_ID)*/

#define SIM_SB_16_LONG \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID) \
    REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)

#define SIM_SB_16_LONG_SEQ \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE(16, BE, SubBlockID, "Sub Block ID", DEC) \
    VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
    
/*#define SIM_SB_16_LONG \
    REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID) \
    REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH) \
    VALUE_CONST(Status, "Status", SIM_SB_STATUS)  */

#define SUB_MSG_REQ \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)

#define SUB_MSG_RESP(statustbl) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_REQ_HDR \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req Req;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)

#define SUB_MSG_REQUEST_HDR \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request     Req;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    FILLER_EX(paddingbyte, 8, 1)

#define SUB_MSG_RESP_HDR(statustbl) \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response        Resp;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_INFO_HDR(statustbl) \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_InfoResponse Resp;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE_CONST(Status, "Status", statustbl)

#define SUB_MSG_IND_HDR(statustbl) \
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Ind        Head;") \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
    PROPERTY(PROPERTY_PMD_PARAMETER) \
    VALUE_CONST(Status, "Status", statustbl)

#define SIM_COMMON_REQ_MSG_HDR \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    

#define SIM_COMMON_RESP_MSG_HDR \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    

#define SIM_REQUEST_HEADER \
    SIM_COMMON_REQ_MSG_HDR

#define SIM_RESPONSE_HEADER \
    SIM_COMMON_RESP_MSG_HDR

/* Helper macros to avoid repeating comments and definitions */
#define SIM_MSG_HEADER(idcomment) \
    COMMENT(COMMENT_TEXT, "Trans Action ID. Set by Service Requester") \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    COMMENT(COMMENT_TEXT, idcomment) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)

#define SIM_SERVICE_HEADER(idcomment) \
    SIM_MSG_HEADER(idcomment) \
    COMMENT(COMMENT_TEXT, "Service Type Requested") \
    REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)

#define     SIM_MSG_HDR \
    VALUE(8, BE, TransID, "Transaction ID", DEC) \
    REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)

/* ------------------------------------------------------------------------- */
/* INCLUDE of shared macro files ------------------------------------------- */
/* ------------------------------------------------------------------------- */
#include "sim_shared_isi_m.h"

/* Project / Document properties */
PROPERTY_STRING(PROPERTY_PROJECT_SITE_NAME,                "R&D Copenhagen")
PROPERTY_STRING(PROPERTY_PROJECT_NAME,                     "Smartcards")
PROPERTY_STRING(PROPERTY_PROJECT_OWNER_NAME,               "smartcards.support@nokia.com")
PROPERTY_STRING(PROPERTY_PROJECT_CONFIDENTIALITY,          "CONFIDENTIAL")

/* ISI header properties */
PROPERTY_STRING(PROPERTY_ISIHDR_TITLE,                     "SIM Server ISI Message Specification")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME,                  "sim_isi.h")
PROPERTY_STRING(PROPERTY_ISIHDR_FILENAME_16,               "sim_isi_16.h")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,      "ou1gif")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,    "global_interface/coresw_interface/coresw_public")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16, "global_interface/coresw_interface/coresw_public")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,   "co_sim#1")
PROPERTY_STRING(PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16,"co1core#1")

/* HTML properties */
PROPERTY_STRING(PROPERTY_HTML_TITLE,                       "SIM Server ISI Message Description")
PROPERTY_STRING(PROPERTY_HTML_FILENAME,                    "i_sim_m.html")
PROPERTY_STRING(PROPERTY_HTML_DOCUMENT_NUMBER,             "")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_DB,        "ou1gif")
PROPERTY_STRING(PROPERTY_HTML_CONTINUUS_PROJECT_NAME,      "GIF_SPECS-ou1gif#browse")
PROPERTY_STRING(PROPERTY_HTML_DIRECTORY_PATH,              "GIF_SPECS/CoreSW/coresw_public_spec")
PROPERTY(PROPERTY_HTML_INCLUDE_INTRODUCTION)

PROPERTY(PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS)

RES_BEGIN(RESOURCE_ISI, PN_SIM, SIM, "SIM Server",
    RES_VERSION_STRING(SIM_ISI_VERSION_Z, SIM_ISI_VERSION_Y), TRUE)

/* Include our shared SIM SHARED ISI */
INCLUDE_SHARED_FILE(PN_SIM, "018.000", "")

    /* --------------------------------------------------------------------- */
    /* ISI version history                                                   */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Correct minor errors in SIM ISI macro file, causing PMD decode problems.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: TT09110554994")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "6-Nov-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Kure Thorngreen")
    COMMENT(COMMENT_PARAGRAPH,                 "-")
    ISI_VERSION_HISTORY(                       "020.001")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Remove parts of SIM ISI IF not supported by S40 Adaptation SIM Server.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS09061946380")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-Aug-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "-")
    ISI_VERSION_HISTORY(                       "020.000")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change to SUB_MSG_REQUEST_HDR macro.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS09021134415")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Feb-2009")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "Version updated.")
    ISI_VERSION_HISTORY(                       "018.002")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Updating ISI interface CR to I_CPR_7.2 on Smartcard profile: Parental Control Pincode and OMA BCAST AUTHENTICATE response")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "RM-RIM: 006-15505, 006-16563")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#86560")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM:TS07110689414")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "07-Jan-2008")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Stormark")
    COMMENT(COMMENT_PARAGRAPH,                 "Added ext bcast support to Authenticate req/resp and new PIN_PC to pin isi related msg.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_SB_AM_HANDLE subblock has been moved to the new sim_shared_isi.h file.")
    COMMENT(COMMENT_PARAGRAPH,                 "018.000 follows 017.006 in R&D and 018.001 follows 017.004 in 7.2 branch.")
    ISI_VERSION_HISTORY(                       "018.000")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "RM-RIM:408-2329")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#87508")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JS07111351317")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "05-Dec-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "John Soerensen")
    COMMENT(COMMENT_PARAGRAPH,                 "New SB SIM_SB_ATT_RAT_ID  is defined. Added to SIM_CS_READ_REQ/RESP.")
    COMMENT(COMMENT_PARAGRAPH,                 "New refresh ID SIM_REFRESH_ATT_RAT  is defined. Added to SIM_REFRESH_NTF and SIM_REFRESH_REQ.")
    COMMENT(COMMENT_PARAGRAPH,                 "Version 017.005 is used for 7.1 branch only.")
    ISI_VERSION_HISTORY(                       "017.006")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "RM-RIM:006-14131")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#74622")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JS07062732576")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "20-Aug-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "John Soerensen")
    COMMENT(COMMENT_PARAGRAPH,                 "DSS related stuff removed.")
    COMMENT(COMMENT_PARAGRAPH,                 "Otherwise are kept because these are still avilable used by Clients.")
    COMMENT(COMMENT_PARAGRAPH,                 "Messages supported by DSS server only, are removed:")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_INIT_REQ,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_READ_NVT_MEM_REQ/RESP, SIM_RUN_GSM_ALGORITM_REQ/RESP,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_UPDATE_REQ/RESP, SIM_STANDBY_STATUS_REQ/RESP,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PN_LIST_ENABLE_REQ/RESP,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_INFONUM_REQ/RESP, SIM_ATK_SEND_USSD_CONS,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_ATK_SEND_USSD_INF, SIM_MSISDN_INFO_REQ/RESP,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PREFERRED_PROTOCOL_IND, SIM_GET_SEARCH_TABLE_REQ/RESP,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_NETWORK_INFO_REQ/RESP(READ_PLMN_LIST),")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_ACM_REQ/RESP(SIM_ST_WARNING_LEVEL_READ),")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_CSP_REQ/RESP(READ_TO_SCM, WRITE_TO_SCM),")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PB_REQ(SIM_PB_ROOM_CHECK)")
    COMMENT(COMMENT_PARAGRAPH,                 "                             ")
    COMMENT(COMMENT_PARAGRAPH,                 "DSS message not removed(Not visible in HTML file):")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PN_LIST_STATUS_REQ/RESP, used by ATK")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PN_WRITE_REQ/RESP, used by ProtocolSW and SIMSON.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PN_READ_RESP, used by SIMSON.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_TARIFF_REQ/RESP(READ_PACKAGE) used by UI.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_JACOB_REQ/RESP(READ_REAL_JACOB_IDS) used by UI.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_SAT_REQ/RESP(CB_DOWNLOAD) used by ProtocolSW from dct4_srvsim_msg.h.")
    COMMENT(COMMENT_PARAGRAPH,                 "        ")
    COMMENT(COMMENT_PARAGRAPH,                 "SBs, related to DSS, not removed:")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PB_LND, SIM_PB_PSC.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PB_ROOM_INFO_REQUEST,SIM_PB_ROOM_INFO_ERROR.")
    COMMENT(COMMENT_PARAGRAPH,                 "        ")
    COMMENT(COMMENT_PARAGRAPH,                 "Removed SBs:")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PB_LND, SIM_PB_PSC.")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PB_ROOM_INFO_REQUEST,SIM_PB_ROOM_INFO_ERROR.")
    COMMENT(COMMENT_PARAGRAPH,                 "      ")
    COMMENT(COMMENT_PARAGRAPH,                 "Removed sequences:")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_ACM_WARNING")
    COMMENT(COMMENT_PARAGRAPH,                 "  ")
    COMMENT(COMMENT_PARAGRAPH,                 "Alignments:")
    COMMENT(COMMENT_PARAGRAPH,                 "All 'VALUE(8, BE, StorageStatus, StorageStatus, DEC)'")
    COMMENT(COMMENT_PARAGRAPH,                 "to")
    COMMENT(COMMENT_PARAGRAPH,                 "'VALUE_CONST(StorageStatus, StorageStatus, SIM_SMS_MSG_STATUS_TABLE'")
    COMMENT(COMMENT_PARAGRAPH,                 " ")
    COMMENT(COMMENT_PARAGRAPH,                 "Removed tables(not used):")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_SB_FILE_STATUS,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_PIN_ENABLE_SERVICE_TYPE,")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_ST_SMS_WRITE_RAW_STATUS")
    COMMENT(COMMENT_PARAGRAPH,                 "       ")
    COMMENT(COMMENT_PARAGRAPH,                 "General:")
    COMMENT(COMMENT_PARAGRAPH,                 "Comments added to messages and parameters. Visible in HTML file.")
    COMMENT(COMMENT_PARAGRAPH,                 "          ")
    COMMENT(COMMENT_PARAGRAPH,                 "Definitions removed:")
    COMMENT(COMMENT_PARAGRAPH,                 "Doubble definition of #define ADN and #define FDN removed.")
    ISI_VERSION_HISTORY(                       "017.004")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Updating ISI interface for 408-1076: SIM Server support for lumiere gba_u and MGV_U")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#76808")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: TS07061989406")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Aug-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Stormark")
    COMMENT(COMMENT_PARAGRAPH,                 "Added GBA, MBMS, ApplicationManagement API for 7.2 branch.")
    ISI_VERSION_HISTORY(                       "017.003")
    
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Error correction")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#70603")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS07032335341")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Mar-2007")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "Three padding bytes added after MailboxNumbInfo in SIM_CPHS_RESP to")
    COMMENT(COMMENT_PARAGRAPH,                 "match the real world.")
    ISI_VERSION_HISTORY(                       "017.002")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Addition of SIM_ST_REFRESH_STARTING service type to SIM_REFRESH_NTF.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Synergy/CM task: co1core#64901")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NS06112745514")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Dec-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov")
    COMMENT(COMMENT_PARAGRAPH,                 "SIM_ST_REFRESH_STARTING service type added to SIM_REFRESH_NTF.")
    ISI_VERSION_HISTORY(                       "017.002")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Updating ISI interface for 006-12840: Enhanced FETCH handling")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#56686")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-12840")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: TS06103133373")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "15-Dec-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Stormark")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new service types and related stuff for CAT ")
    COMMENT(COMMENT_PARAGRAPH,                 "enable and disable support under SIM_ATK_REQ/RESP.")
    ISI_VERSION_HISTORY(                       "017.001")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Remove RUIM and GAIT")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#62431")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-14124")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE06102354231")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Oct-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "The CDMA definitions have been removed from the macro and .h ")
    COMMENT(COMMENT_PARAGRAPH,                 "file as would have caused file to be even more cluttered ")
    COMMENT(COMMENT_PARAGRAPH,                 "than it already is. Further more the CDMA is removed from ")
    COMMENT(COMMENT_PARAGRAPH,                 "the code asset not phased out. So a clean cut seems as the ")
    COMMENT(COMMENT_PARAGRAPH,                 "best solution.")
    COMMENT(COMMENT_PARAGRAPH,                 "If futher CDMA definitions are found at a later stage they ")
    COMMENT(COMMENT_PARAGRAPH,                 "should be removed.")
    COMMENT(COMMENT_PARAGRAPH,                 "PMD property is removed as it is no longer a valid keyword ")
    COMMENT(COMMENT_PARAGRAPH,                 "for Autogen.")
    ISI_VERSION_HISTORY(                       "017.000")

    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Remove dependency to Tracfone Server")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#11885")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-13174")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: PP06072156397")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-Aug-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Paetur Petersen")
    ISI_VERSION_HISTORY(                       "016.000")

    /* --------------------------------------------------------------------- */
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Macrofile should be created for SIM server")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#50080")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-8365")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: AT06051933264")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-May-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Annette Thy")
    COMMENT(COMMENT_PARAGRAPH,                 "sim_isi_m.h file has been changed so that it now can be used to ")
	COMMENT(COMMENT_PARAGRAPH,                 "generate sim_isi.h file. Other interface files should NOT be ")
	COMMENT(COMMENT_PARAGRAPH,                 "automatically generated yet.")
    ISI_VERSION_HISTORY(                       "015.011")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Updating ISI interface for 010-182: Support for EF-ACL UI part")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#50821")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 010-182")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: TS06050249393")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "02-May-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Thomas Stormark")
    COMMENT(COMMENT_PARAGRAPH,                 "Added service types, structures and constants for ACL Read and Write")
    ISI_VERSION_HISTORY(                       "015.010")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Changing constant for 006-10452: Remove SIM_SERV_LOC_NOT_VALID")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#49940")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-10452")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE06040351729")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Apr-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "Version macro updated and SIM_SERV_LOC_NOT_VALID moved from ")
    COMMENT(COMMENT_PARAGRAPH,                 "numeric value 16 to 44 to remove number clash with SIM_STA_UPDATE_IMPOSSIBLE.")
    ISI_VERSION_HISTORY(                       "015.009")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "PCP Error: EO06032951336 GSM/WCDMA - OTC - SIm phonebook : "
                                                "entering a 70 caracters long email address")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#49973")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "PCP Error: EO06032951336")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE06040442314")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "04-Apr-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "Version macro updated and Correcting")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_TEXT_LEN = PR_NAME_LENGTH+1 ->")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_TEXT_LEN = PR_TEXT_LENGTH+1.")
    ISI_VERSION_HISTORY(                       "015.008")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Adding ISI interface for 006-5954: APN - Support for EFACL")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#48518")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-5954")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: MN05122035049")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-Mar-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Michael Noerlev")
    COMMENT(COMMENT_PARAGRAPH,                 "Version macro updated and SIM_STA_ACL_CHECK_DISABLED removed.")
    ISI_VERSION_HISTORY(                       "015.007")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Adding ISI interface for 006-5954: APN - Support for EFACL")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#42462")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-5954")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: MN05122035049")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "21-Feb-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Michael Noerlev")
    COMMENT(COMMENT_PARAGRAPH,                 "Added service types, structures and constants for ACL")
    ISI_VERSION_HISTORY(                       "015.006")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New ISI message to retrieve number of remaining verification "
                                               "attempts for PIN and PUK.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#43453")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05120235814")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "09-Jan-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Message IDs:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PIN_ATTEMPTS_LEFT_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PIN_ATTEMPTS_LEFT_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Service Types:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_PUK")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_PUK2")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new message structures:")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_PIN_ATTEMPTS_LEFT_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_PIN_ATTEMPTS_LEFT_RESP")
    ISI_VERSION_HISTORY(                       "015.005")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Adding ISI interface for TracFone integration to GSM ISA")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#42394")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-8308")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: PE05121357262")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "02-Jan-2006")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Paetur Petersen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added a new service type and related stuff for envelope sending")
    COMMENT(COMMENT_PARAGRAPH,                 "Added a new req/resp for SIM_TRACFONE_SIMLOCK_STATUS_REQ/RESP")
    ISI_VERSION_HISTORY(                       "015.004")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Adding service types for SIM_READ_TABLE_REQ")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#30746")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-10401")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE05121450785")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "14-Dec-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "Adding service types for SIM_READ_TABLE_REQ/RESP:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_GPRS_CALL_CONTROL_AVAIL")
    ISI_VERSION_HISTORY(                       "015.003")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Adding service types for SIM_DATA_SIZES_REQ")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#40951")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE05110833235")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Nov-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "Adding service types for SIM_DATA_SIZES_REQ/RESP:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_VMBX_CNT, ")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_VMBX_ALPHA_LEN,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_VMBX_NBR_LEN,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_MBDN_CNT,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_MBDN_PROFILE_SIZE,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_MBDN_PROFILE_CNT,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_MBDN_ALPHA_LEN,")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_MBDN_NBR_LEN")
    ISI_VERSION_HISTORY(                       "015.001")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Change of status values for R-UIM Operational Mode")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#39074")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05100554048")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Oct-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_TEXT,                      "SIM_STA_NO_RUIM is replaced by SIM_STA_RUIM_OFF; SIM_STA_FULL_RUIM "
                                               "is replaced by SIM_STA_RUIM_ON; SIM_STA_LIMITED_RUIM is removed. "
                                               "tSIM_RUIM_STATUS_REQ and tSIM_RUIM_STATUS_RESP has been added.")
    ISI_VERSION_HISTORY(                       "015.000")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Support EF-EHPLMN field on USIM")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#38855")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-8926")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: PP05090846932")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Oct-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Michael Noerlev")
    COMMENT(COMMENT_TEXT,                      "Added SIM_REFRESH_EQUIVALENT_HPLMNS, tSIM_SB_EQUIVALENT_HPLMNS and"
                                               "SIM_SB_EQUIVALENT_HPLMNS_ID")
    ISI_VERSION_HISTORY(                       "014.019")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Interface for ESN")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#38516")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-9582")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05083056389")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Sep-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_TEXT,                      "Added SIM_ESN_MEID_EQUAL_IND and SIM_ESN_MEID_EQUAL_REQ/RESP.")
    ISI_VERSION_HISTORY(                       "014.018")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Long configuration subblocks for phonebook.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#37125")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-9284")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE05070537600 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: SE05070654225 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Jul-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Soren Engquist")
    COMMENT(COMMENT_PARAGRAPH,                 "New subblock ids:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PB_CONF_ANR_LONG_SB")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PB_CONF_EMAIL_LONG_SB")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PB_CONF_SNE_LONG_SB")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_PB_CONF_GRP_LONG_SB")
    ISI_VERSION_HISTORY(                       "014.017")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New ServiceTypes for O2 HomeZone")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#34393")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-8372 & 006-8373")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: AT05051844532 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: AT05052733033 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Jun-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Annette Thy")
    COMMENT(COMMENT_PARAGRAPH,                 "New service types:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_SUBSCRIBED_LAC_CI")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_HZ_TAGS")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_READ_UHZIUE_SETTINGS")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_WRITE_UHZIUE_SETTINGS")
    COMMENT(COMMENT_PARAGRAPH,                 "added for SIM_VIAG_HOME_ZONE_REQ message.")
    COMMENT(COMMENT_PARAGRAPH,                 "New status SIM_STA_DATA_NOT_AVAIL added.")
    ISI_VERSION_HISTORY(                       "014.016")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New ServiceType for CALL CONTROL")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#29306")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-7198")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05022459122 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05031732544 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "17-Mar-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_TEXT,                      "New service type SIM_ST_CDMA_CALL_CONTROL added for "
                                               "SIM_READ_RUIM_TABLE_REQ message.")
    ISI_VERSION_HISTORY(                       "014.015")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: New SMS interface for SCO 006-5531 - Support for new "
                                               "messaging platform.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#28220")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-5531")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04102546452 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05030245613 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Mar-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added message structures:")
    COMMENT(COMMENT_PARAGRAPH,                 "    - tSIM_SMS_READ_RAW_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    - tSIM_SMS_READ_RAW_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    - tSIM_SMS_WRITE_RAW_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    - tSIM_SMS_WRITE_RAW_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "Added service types to SIM_SMS_REQ message:")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_ST_SMS_READ_RAW")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_ST_SMS_WRITE_RAW")
    ISI_VERSION_HISTORY(                       "014.014")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Additions to SIM_RUIM_IND and SIM_STATUS_REQ.")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task: co1core#27327")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05013146615 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH05021845815 (Inspection Agenda)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Mar-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added service type SIM_ST_RUIM_OPERATIONAL_MODE.")
    COMMENT(COMMENT_TEXT,                      "Added status values SIM_STA_NO_RUIM, SIM_STA_LIMITED_RUIM and "
                                               "SIM_STA_FULL_RUIM.")
    ISI_VERSION_HISTORY(                       "014.013")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: Icon buffering in ISA and splitting to SOS")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#27565")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 009-16822: Icon buffering in ISA and splitting to SOS")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL05021030307 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL05022353233 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "23-Feb-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Erik Laursen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added service types to reg SIM_ATK_REQ:")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_ST_READ_ICON_CLUT")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_ST_READ_ICON_BODY_DATA")
    COMMENT(COMMENT_PARAGRAPH,                 "And sub blocks:")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_SB_ICON_DATA_CLUT_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "    - SIM_SB_ICON_BODY_DATA_ID")
    ISI_VERSION_HISTORY(                       "014.012")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: Support of ISIM for IMS access")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#24439")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-3097")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL04122339567 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL05013146658 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "PCP Error: VS05020960999")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "31-Jan-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Erik Laursen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added message IDs: SIM_IMS_REQ/RESP and SIM_IMS_IND")
    COMMENT(COMMENT_PARAGRAPH,                 "    With service types:")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_ST_IMS_START_SESSION")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_ST_IMS_END_SESSION")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_ST_IMS_STATUS")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_ST_IMS_READ_DATA")
    COMMENT(COMMENT_PARAGRAPH,                 "    And Sub blocks:")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_SB_IMS_PRIVATE_USER_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_SB_IMS_PUBLIC_USER_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "    And refresh message IDs:")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_REFRESH_IMS_PRIVATE_USER_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_REFRESH_IMS_PUBLIC_USER_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "        SIM_REFRESH_IMS_HOME_NW_DOMAIN_NAME")
    COMMENT(COMMENT_PARAGRAPH,                 "Add Service type and Sub block to Message ID SIM_APP_SELECTION_REQ:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_GET_ISIM_LABEL")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_GET_LABEL_BY_NO")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_SB_APP_SELECTION_UNICODE")
    COMMENT(COMMENT_PARAGRAPH,                 "Add Service type to Message ID SIM_AUTHENTICATION_REQ:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_IMS_CONTEXT")
    COMMENT(COMMENT_PARAGRAPH,                 "In all PIN requests padding byte is substituted with:")
    COMMENT(COMMENT_PARAGRAPH,                 "    ApplicationNumber")
    COMMENT(COMMENT_PARAGRAPH,                 "Change SIM_OTA_SSPR_CONFIG_RESP_PARAM_DATA from 4 to 3")
    ISI_VERSION_HISTORY(                       "014.011")

    /* --------------------------------------------------------------------- */
    
    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: EAP-AKA authentication support in SIMSON")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#15124")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-3761")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: AT04092342665 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: AT04112555298 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "11-Jan-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Annette Thy")
    COMMENT(COMMENT_TEXT,                      "Added service type SIM_ST_EAP_AKA_CONTEXT to be used with "
                                               "SIM_AUTHENTICATION_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "Added the following subblocks:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_SB_EAP_INTEGRITY_KEY_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_SB_EAP_CIPHERING_KEY_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "Added constants:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_EAP_CIPH_KEY_LEN")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_EAP_INTE_KEY_LEN")
    ISI_VERSION_HISTORY(                       "014.010")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New service type added")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#21462")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-5886: Connecting SIM from PDA mode in DSS")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM:  DE04110854756(Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM:  DE04112334116(Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "06-Jan-2005")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Dan Egebo")
    COMMENT(COMMENT_TEXT,                      "Added new service type SIM_ST_SIM_CONNECTION_FORCED_PIN to "
                                               "SIM_CONNECTION_REQ/RESP.")
    ISI_VERSION_HISTORY(                       "014.009")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Addition of new subblock to phonebook start-up phase 2")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#20930")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-6382")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JI04102053490 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JI04111546442 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "26-Nov-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jorgen Moller Ilsoe")
    COMMENT(COMMENT_TEXT,                      "Addition of new subblock for phonebook start-up phase 2")
    ISI_VERSION_HISTORY(                       "014.008")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: Addition of missing file IDs for Refresh Release 99 implementation")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#20852")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-2213")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL04102542507 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL04110542986 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "04-Nov-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Erik Laursen")
    COMMENT(COMMENT_TEXT,                      "Add missing file ID definitions for Refresh R99")
    ISI_VERSION_HISTORY(                       "014.007")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: New interface for R-UIM")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co1core#14144")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-4630")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04063042099 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04072053264 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "08-Sep-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_TEXT,                      "Added support for R-UIM messages. Old temporary interface "
                                               "structures are flagged with SIM_TEMP_RUIM_OLD_IF.")
    ISI_VERSION_HISTORY(                       "014.006")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: SIMLOCK state enquiry with req/resp message")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Continuus task co1core#12352")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-4864")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04061753527 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04062444852 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "01-Jul-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new message structures tSIM_SIMLOCK_STATUS_REQ/RESP.")
    COMMENT(COMMENT_TEXT,                      "Added new Service Type SIM_ST_SIMLOCK_STATUS for SIM_STATUS_REQ "
                                               "message. Added new status values SIM_STA_SIMLOCK_OK and"
                                               "SIM_STA_SIMLOCK_STATUS_NOT_INITIALIZED.")
    ISI_VERSION_HISTORY(                       "014.005")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "SIM: Support for disabling and enabling of PIN2 on USIM Cards")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Continuus task co_sim#37182")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-4125: Disable/Enable PIN2 on USIM	")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: EL04052746922 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "10-Jun-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Erik Laursen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new message structures tSIM_SIMLOCK_STATUS_REQ/RESP.")
    COMMENT(COMMENT_PARAGRAPH,                 "Update ISI version")
    COMMENT(COMMENT_PARAGRAPH,                 "Following has been made in version 014.003.2 (it is added here as "
                                               "autogen can not handle version numbers other than xxx.yyy):")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new message structures tSIM_SIMLOCK_STATUS_REQ/RESP.")
    COMMENT(COMMENT_PARAGRAPH,                 "SubBSlockLength field renamed to correct name SubBlockLength")
    ISI_VERSION_HISTORY(                       "014.004")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "New ISI interface for provisioning of MMS settings on the (U)SIM")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Continuus task co_sim#36409")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-3566")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04042755103 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04051949372 (Inspection Minutes)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "03-Jun-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Message IDs:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_MMS_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_MMS_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Service Types:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_MMS_ICP_READ")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_MMS_UP_READ")
    COMMENT(COMMENT_PARAGRAPH,                 "Added ISI Message structures:")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_ST_MMS_ICP_READ_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_ST_MMS_ICP_READ_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_ST_MMS_UP_READ_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_ST_MMS_UP_READ_RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Subblock IDs:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_SB_MMS_CONNECTIVITY_PARAMETERS_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_SB_MMS_USER_PREFERENCES_ID")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Subblock structures:")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_SB_MMS_CONNECTIVITY_PARAMETERS")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_SB_MMS_USER_PREFERENCES")
    COMMENT(COMMENT_PARAGRAPH,                 "Changed tSIM_SB_NUMBER subblock; Filler exchanged with AASNumber.")
    ISI_VERSION_HISTORY(                       "014.003")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "Implementation of full refresh according to 3GPP TS 11.14")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "Continuus task co_sim#35574")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "WP RM-RIM Tool: 006-2213")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JM04032334025 (Change Request)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: NH04042643144 (Inspection)")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "13-May-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Nikolaj Skov Hansen")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Message IDs: ")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_REFRESH_REQ/RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_REFRESH_NTF")
    COMMENT(COMMENT_PARAGRAPH,                 "Added new Service Types:")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_REGISTER")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_UNREGISTER")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_OK")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_NOT_OK")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_DONE")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_ERROR")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_REQUESTED")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_NOW")
    COMMENT(COMMENT_PARAGRAPH,                 "    SIM_ST_REFRESH_CANCELLED")
    COMMENT(COMMENT_PARAGRAPH,                 "Added File ID constants for use with SIM_REFRESH_REQ")
    COMMENT(COMMENT_PARAGRAPH,                 "Added structures:")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_REGISTER_REQ/RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_UNREGISTER_REQ/RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_PERMISSION_REQ/RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_RESULT_REQ/RESP")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_REQUESTED_NTF")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_NOW_NTF,")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_CANCELLED_NTF")
    COMMENT(COMMENT_PARAGRAPH,                 "    tSIM_REFRESH_FILE_LIST_STR")
    ISI_VERSION_HISTORY(                       "014.002")

    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_CHANGE_REASON,    "PCP MM04021959464")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co_sim#33486 (simson) ")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "CM Synergy task co_sim#35601 (DSS)")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "PCP MM04021959464")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JI04022354652")
    PROPERTY_STRING(PROPERTY_CHANGE_REFERENCE, "ActionDB for SWAM: JI04031944552")
    PROPERTY_STRING(PROPERTY_CHANGE_STATUS,    "Approved")
    PROPERTY_STRING(PROPERTY_CHANGE_DATE,      "19-Mar-2004")
    PROPERTY_STRING(PROPERTY_CHANGE_PERSON,    "Jorgen Ilsoe")
    COMMENT(COMMENT_TEXT,                      "Added version history. No further changes.")
    ISI_VERSION_HISTORY(                       "014.000")


    /* --------------------------------------------------------------------- */
    /* Notes references                                                      */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* Symbol tables                                                         */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* Constants                                                             */
    /* --------------------------------------------------------------------- */

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(COMM_MAX_FTD_STRING_LENGTH, 124)

#ifndef S60_INTERFACE
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
#endif
    CONSTANT(SIM_MAX_NBR_OF_CBMIDS, 5)

#ifndef S60_INTERFACE
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
#endif
    CONSTANT(SIM_MAX_NBR_OF_EMRG_CALL_CODES, 5)

#ifndef S60_INTERFACE
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
#endif
    CONSTANT(SIM_NBR_OF_CELL_BC_MSG_IDS, 15)

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SIM_NAME_LEN, 51)
	
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SIM_NUMBER_LEN, 49)

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SIM_TEXT_LEN, 61)

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SIM_PUCT_CURRENCY_CODE_LEN, 4)

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SIM_FILE_PATH_LEN, 8)

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONSTANT(SMS_ADDRESS_MAX_LENGTH, 12)

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_ATK_REQ                                         */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_ATK_REQ")
    CONST_TBL_BEGIN(SIM_ATK_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_INIT_FROM_PIN,       0,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_FCN,                 1,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_INIT_FROM_PIN_FCN,   2,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_INIT_FROM_PIN_FFCN,  3,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_RESET,               4,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_APPLICATION_RESET,   5,     "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET,   6,     "")
        CONST_TBL_ENTRY(SIM_ST_SET_POLLING,                16,     "")
        CONST_TBL_ENTRY(SIM_ST_READ_ICON,                  17,     "")
        CONST_TBL_ENTRY(SIM_ST_READ_ICON_CLUT,             18,     "")
        CONST_TBL_ENTRY(SIM_ST_READ_ICON_BODY_DATA,        19,     "")
        CONST_TBL_ENTRY(SIM_ST_SEND_ENVELOPE,              20,     "")
        CONST_TBL_ENTRY_VER(SIM_ST_CAT_SUPPORT_ENABLE,     21,     "017.001", "")
        CONST_TBL_ENTRY_VER(SIM_ST_CAT_SUPPORT_DISABLE,    22,     "017.001", "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_PIN_STATE_GET_REQ                               */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_PIN_STATE_GET_REQ")
    CONST_TBL_BEGIN(SIM_PIN_STATE_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_GET_ACTIVE_PIN,              155,     "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_STATUS_REQ                                      */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_STATUS_REQ")
    CONST_TBL_BEGIN(SIM_STATUS_SERVICE_TYPE_TABLE, 8, BE, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "CARD_STATUS")
        CONST_TBL_ENTRY(SIM_ST_CARD_STATUS,                 0,       "")
        CONST_TBL_ENTRY(SIM_ST_SIMLOCK_STATUS,              1,       "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_PREF_LANGUAGE_REQ                               */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_PREF_LANGUAGE_REQ")
    CONST_TBL_BEGIN(SIM_PREF_LANGUAGE_SERVICE_TYPE_TABLE, 8, BE, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "READ_PL_LANGUAGE")
        CONST_TBL_ENTRY(SIM_ST_READ_PL_LANGUAGE,            1,       "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "READ_LI_LANGUAGE")
        CONST_TBL_ENTRY(SIM_ST_READ_LI_LANGUAGE,            2,       "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "WRITE_PL_LANGUAGE")
        CONST_TBL_ENTRY(SIM_ST_WRITE_PL_LANGUAGE,           3,       "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "WRITE_LI_LANGUAGE")
        CONST_TBL_ENTRY(SIM_ST_WRITE_LI_LANGUAGE,           4,       "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_ACM_REQ                                         */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_ACM_REQ")
    CONST_TBL_BEGIN(SIM_ACM_SERVICE_TYPE_TABLE, 8, BE, "", "020.000")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "SIM_ACM_INCREMENT_SRV")
        CONST_TBL_ENTRY(SIM_ST_INCREMENT,                   18,      "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "SIM_ACM_SET_SRV")
        CONST_TBL_ENTRY(SIM_ST_SET,                         19,      "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "SIM_ACM_READ_SRV")
        CONST_TBL_ENTRY(SIM_ST_READ_AOC,                    20,      "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "SIM_ACM_MAX_VALUE_SET_SRV")
        CONST_TBL_ENTRY(SIM_ST_MAX_VALUE_SET,               21,      "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "SIM_ACM_MAX_VALUE_READ_SRV")
        CONST_TBL_ENTRY(SIM_ST_MAX_VALUE_READ,              22,      "")
    CONST_TBL_END
    
    /* --------------------------------------------------------------------- */
    /* Service types for SIM_IMSI_XXX_REQ                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_IMSI_XXX_REQ")
    CONST_TBL_BEGIN(SIM_IMSI_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(READ_IMSI,                          45,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_SERV_PROV_NAME_REQ                              */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_SERV_PROV_NAME_REQ")
    CONST_TBL_BEGIN(SIM_SERV_PROV_NAME_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_SPN_DISPLAY_INFO,            1,       "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "READ_SERV_PROV_NAME")
        CONST_TBL_ENTRY(SIM_ST_READ_SERV_PROV_NAME,         44,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_VOICE_MSG_REQ and SIM_CALL_FWD_REQ              */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_VOICE_MSG_REQ and SIM_CALL_FWD_REQ.")
    CONST_TBL_BEGIN(SIM_VOICE_MSG_CALL_FWD_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_WRITE_MSG_FLAGS,             1,       "")
        CONST_TBL_ENTRY(SIM_ST_READ_MSG_FLAGS,              2,       "")
        CONST_TBL_ENTRY(SIM_ST_WRITE_CALL_FWD_FLAGS,        3,       "")
        CONST_TBL_ENTRY(SIM_ST_READ_CALL_FWD_FLAGS,         4,       "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "WRITE_FLAGS")
        CONST_TBL_ENTRY(SIM_ST_WRITE_FLAGS,                 57,      "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "READ_FLAGS")
        CONST_TBL_ENTRY(SIM_ST_READ_FLAGS,                  58,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_APP_SELECTION_REQ                               */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_APP_SELECTION_REQ")
    CONST_TBL_BEGIN(SIM_APP_SELECTION_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY_VER(SIM_ST_GET_NUMBER_OF_APP,           1,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_GET_ALL_APP_LABELS,          2,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_GET_ACTIVE_APP_LABEL,        3,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_SET_DEFAULT_APP,             4,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_ACTIVATE_APP,                5,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_SET_APP_SELECTION_AUTOMATIC, 6,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_SET_APP_SELECTION_MANUAL,    7,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_GET_APP_SELECTION_STATUS,    8,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_GET_ISIM_LABEL,              9,      "", "020.000")
        CONST_TBL_ENTRY(SIM_ST_GET_LABEL_BY_NO,            10,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_CONNECTION_REQ                                  */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_CONNECTION_SERVICE_TYPE_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        CONST_TBL_ENTRY(SIM_ST_SIM_DISCONNECT,              1,      "This state brings the SIM server in disconnected state. Going into this state causes all un-updated files to be updated, de-activates the APDU server and send indications SIM_CS_IND (STATE_SIM_REMOVED) and SIM_IND(STATE_SIM_REMOVED). The result of this is that another device can take over the physical ICC.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        CONST_TBL_ENTRY(SIM_ST_SIM_CONNECT,                 2,      "This state will activate the APDU server. Activation of the APDU server will bring the SIM server into the same state as it is at the starting point of start-up. After this a normal start-up can be expected. It is only legal to send this message, when the SIM server is in disconnected state.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        CONST_TBL_ENTRY(SIM_ST_SIM_RECONNECT,               3,      "This state first performs the same actions as service type SIM_ST_SIM_DISCONNECT. Then it changes the APDU server address to the address specified in the subblock. When the APDU server address has been changed, the new APDU server is activated, as described for service type SIM_ST_SIM_CONNECT. SIM_ST_SIM_RECONNECT can also be performed after the SIM server has been disconnected.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        CONST_TBL_ENTRY(SIM_ST_SIM_CONNECT_FORCED_PIN,      4,      " Only DSS SERVER ?????????????????????????")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_OPERATOR_REQ                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_OPERATOR_REQ.")
    CONST_TBL_BEGIN(SIM_OPERATOR_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_READ_OPL,                   19,      "")
        CONST_TBL_ENTRY(SIM_ST_READ_PNN,                   20,      "")
        CONST_TBL_ENTRY(READ_NAME,                         62,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_PB_REQ                                          */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_PB_REQ")
    CONST_TBL_BEGIN(SIM_PB_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_PB_READ,                       15,      "")
        CONST_TBL_ENTRY(SIM_PB_WRITE,                      16,      "")
        CONST_TBL_ENTRY(SIM_PB_GET_CONF,                   17,      "")
        CONST_TBL_ENTRY(SIM_PB_SELECT_PB,                  19,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_PN_READ_REQ and SIM_PN_WRITE_REQ                */
    /* NOT TO BE USED IN FUTURE DEVELOPMENT                                  */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT(COMMENT_TEXT, "NOT TO BE USED IN FUTURE DEVELOPMENT")
    CONST_TBL_BEGIN(SIM_PN_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_ADN,                         7,      "")
        CONST_TBL_ENTRY(SIM_ST_FDN,                         9,      "")
        CONST_TBL_ENTRY(SIM_ST_VMBX,                       11,      "")
        CONST_TBL_ENTRY(SDN,                               73,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_REFRESH_REQ and SIM_REFRESH_NTF                 */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_REFRESH_REQ and SIM_REFRESH_NTF")
    CONST_TBL_BEGIN(SIM_REFRESH_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_REGISTER,            1,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_UNREGISTER,          2,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_OK,                  3,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_NOT_OK,              4,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_DONE,                5,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_ERROR,               6,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_REQUESTED,           7,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_NOW,                 8,      "")
        CONST_TBL_ENTRY(SIM_ST_REFRESH_CANCELLED,           9,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_MMS_REQ                                         */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_MMS_REQ")
    CONST_TBL_BEGIN(SIM_MMS_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_MMS_ICP_READ,                1,      "")
        CONST_TBL_ENTRY(SIM_ST_MMS_UP_READ,                 2,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_IMS_REQ                                         */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_IMS_REQ")
    CONST_TBL_BEGIN(SIM_IMS_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_IMS_START_SESSION,           1,      "")
        CONST_TBL_ENTRY(SIM_ST_IMS_END_SESSION,             2,      "")
        CONST_TBL_ENTRY(SIM_ST_IMS_STATUS,                  3,      "")
        CONST_TBL_ENTRY(SIM_ST_IMS_READ_DATA,               4,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_CS_READ_REQ and SIM_CS_WRITE_REQ                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_CS_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_CS_DATA_READ_REQ,            1,      "")
        CONST_TBL_ENTRY_VER(SIM_ST_CS_DATA_READ_ALL_REQ,    2,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_CS_DATA_WRITE_REQ,       3,      "", "020.000")
        CONST_TBL_ENTRY_VER(SIM_ST_CS_STATUS_REQ,           4,      "", "020.000")
        CONST_TBL_ENTRY(SIM_ST_CS_DATA_READ_ALL_GSS_REQ,    5,      "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_AUTHENTICATION_REQ / SIM_AUTHENTICATION_RESP    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AUTH_SERVICE_TYPE_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "A GSM authentication will be preformed either on a 3G card if GSM Security Context is enabled(service 38 in the USIM Service Table) or on a 2G card.")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_TEXT, "Subblocks in response (OK, 3G(USIM) case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_TEXT, "Note1:Kc and CKSN are stored on the card if the authentication succeded")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Note2:The CK and IK values are derived from Kc by the SIM server and stored on USIM card together with an invalid KSI")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response (OK, 2G(SIM) case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_TEXT, "Note1:Kc and CKSN are stored on the card if the authentication succeded")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Note2:The CK and IK values are derived from Kc by the SIM server and stored on SIM card together with an invalid KSI")
        COMMENT(COMMENT_PARAGRAPH, "    ")
    CONST_TBL_ENTRY_VER(SIM_ST_CS_GSM_CONTEXT,        5, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "A UMTS authentication will be performed on a 3G (USIM) card.")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_KSI_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response. (OK case):")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_KSI_ID")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Note:IK and KSI are stored on the sim card.")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "If GSM Access is enabled(Service No. 27 in the USIM Service Table) on the USIM card, Kc subblock  is  also included.")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Kc is stored on the card together with an invalid CKSN ??????.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response. (Error case):")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(2G(SIM) card inserted in ME.):")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "If an UMTS authentication is issued on a 2G card.")
	COMMENT(COMMENT_TEXT, "This should only happen due to an error in the network. The SIM server try to respond as")
	COMMENT(COMMENT_TEXT, "if the service type was SIM_ST_CS_GSM_CONTEXT.")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Note1:Kc and CKSN are stored on the card if the authentication succeded")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Note2:The CK and IK values are derived from Kc by the SIM server and stored on SIM card together with an invalid KSI")
    CONST_TBL_ENTRY_VER(SIM_ST_CS_UMTS_CONTEXT,             6, "", "020.000")
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "A GSM authentication will be performed either on a 3G card with GSM Security Context enabled(service 38 in the USIM Service Table), or on a 2G card with GPRS enabled(service 38 in the SIM Service Table).")
	COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_GPRS_CIPHERING_KEY_SNR_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, 3G card):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_GPRS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_GPRS_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_PS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_PS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Note:Kc_gprs and CKSN_gprs are stored on the card if the authentication was successful.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note:The PS_CK and PS_IK values are derived from Kc_gprs by the SIM server and kept together with an invalid PS_KSI.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, 2G card):")	
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_GPRS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_GPRS_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_PS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_PS_INTEGRITY_KEY_ID")	
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note:Kc_gprs and CKSN_gprs are stored on the card if the authentication was successful.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note:The PS_CK and PS_IK values are derived from Kc_gprs by the SIM server and kept together with an invalid PS_KSI.")
    CONST_TBL_ENTRY_VER(SIM_ST_PS_GSM_CONTEXT,              7, "", "020.000")
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "A UMTS authentication will be performed on a 3G card.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_KSI_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_KSI_ID")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note:IK and KSI are stored on the sim card.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If GSM Access is enabled(Service No. 27 in the USIM Service Table) on the USIM card, Kc subblock  is  also included.")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Kc is stored on the card together with an invalid CKSN.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response. (Error case):")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(2G(SIM) card inserted in ME.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "If an UMTS authentication is issued on a 2G card.")
	COMMENT(COMMENT_TEXT, "This should only happen due to an error in the network. The SIM server try to respond as")
	COMMENT(COMMENT_TEXT, "if the service type was SIM_ST_CS_GSM_CONTEXT.")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_SNR_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Note1:Kc and CKSN are stored on the card if the authentication succeded")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Note2:The CK and IK values are derived from Kc by the SIM server and stored on SIM card together with an invalid KSI")
    CONST_TBL_ENTRY_VER(SIM_ST_PS_UMTS_CONTEXT,             8, "", "020.000")
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "A GSM authentication will be performed if the SIM Card is a 2G SIM Card.")
	COMMENT(COMMENT_TEXT, " After a succesful authentication the SIM Card will not be updated, i.e. Kc and Keys fields will not be updated.")
        COMMENT(COMMENT_NEWLINE, "")        
	COMMENT(COMMENT_TEXT, "This request will always fails in USIM case.")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_EAP_INTEGRITY_KEY")
	COMMENT(COMMENT_BULLET, "SIM_SB_EAP_CIPHERING_KEY")
        COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_TEXT, "Note:Nothing is stored on the SIM Card")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(Error case):")
        COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_TEXT, "No sub blocks are included in error response")
    CONST_TBL_ENTRY(SIM_ST_EAP_SIM_CONTEXT,             9, "")
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "A GSM authentication will be performed if the SIM Card is a 2G SIM Card an UMTS Authentication")
	COMMENT(COMMENT_TEXT, "will be performed if the SIM card is a 3G USIM card. After a successful authentication no files on the (U)SIM card will be updated.")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_EAP_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_EAP_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_CIPHERING_KEY is always included in case of 2G SIM card and in case of USIM if GSM Access is enabled(Service No. 27 in the USIM Service Table) on the USIM card.")  
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response. (Error case):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID")
    CONST_TBL_ENTRY(SIM_ST_EAP_AKA_CONTEXT,             10, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "A IMS/ISIM authentication will be performed on a ISIM or a USIM application on a UICC.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response. (Error case):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(2G card(SIM) case):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_CIPHERING_KEY_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_CS_INTEGRITY_KEY_ID")
	COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_TEXT, "If an IMS/ISIM authentication is issued on a 2G card, CK and IK are calculated from the ")
	COMMENT(COMMENT_TEXT, "Kc on the SIM Card.")
    CONST_TBL_ENTRY(SIM_ST_IMS_CONTEXT,                 11, "")
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "A GBA Bootstrapping mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Notice: The RAND parameter within the EFGBABP file, is only updated by the UICC")
	COMMENT(COMMENT_TEXT,"and will hold valid RAND value data after a successful GBA_BOOTSTRAP execution.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_RAND_PARAMS_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_PARAMS_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFGBABP file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response. (Sync/MAC error):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
    CONST_TBL_ENTRY_VER(SIM_ST_GBA_BOOTSTRAP,           12, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "An update (write) of the file EFGBABP will (only) be performed with (all)")
	COMMENT(COMMENT_TEXT, "the parameters presented: B-TID, KeyLifetime.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"A prior GBA Bootstrap completed successful, but no validation check is performed on this.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Notice: The RAND parameter within the EFGBABP file, is only updated by the UICC and")
	COMMENT(COMMENT_TEXT,"will hold valid RAND value data after a successful GBA_BOOTSTRAP execution. After a")
	COMMENT(COMMENT_TEXT, "successful GBA_BOOTSTRAP_UPDATE, the RAND value read from the EFGBABP file is returned in the response.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "      ")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_GBA_B_TID_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_GBA_KEY_LIFETIME_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_BULLET, "SIM_SB_RES_PARAMS_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Updates to EFgbabp is unser PIN1 protection.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
         COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_STA_ILLEGAL_LENGTH	The length of data (B-TID, Key Lifetime) has exceeded the max data space available.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SERV_DATA_NOT_AVAIL	Temporary Failure.")
	COMMENT(COMMENT_TEXT, "Information is not available, e.g. could be loss of contact to the card.")
    CONST_TBL_ENTRY_VER(SIM_ST_GBA_BOOTSTRAP_UPDATE,    13, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "A GBA NAF Derivation mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"A prior GBA Bootstrap and GBA Bootstrap Update completed successful.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_GBA_NAF_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_IMS_PRIVATE_USER_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_GBA_KS_EXT_NAF_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFgbanl file.")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure: Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_COND_USE_NOT_SATISFIED:	Conditions of use not satisfied.")
    CONST_TBL_ENTRY_VER(SIM_ST_GBA_NAF_DERIVATION,      14, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "An MBMS MSK Update mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 69 (MBMS) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"A prior GBA Bootstrap and GBA Bootstrap Update completed successful.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_MIKEY_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Notice: This is the MIKEY MSK Update Message, coding defined in TS 33.246, with")
	COMMENT(COMMENT_TEXT,"further oma EXT BCAST format support defined in BCAST10-ServContProt (/27/).")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_MIKEY_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: This is the MIKEY Verification Message, coding defined in TS 33.246, with")
	COMMENT(COMMENT_TEXT, "further oma EXT BCAST format support defined in BCAST10-ServContProt (/27/).")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "In case there are no MIKEY verification message returned from UICC  the data")
	COMMENT(COMMENT_TEXT, " size returned in sim_sb_am_mbms_mikey subblock will be zero.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFMSK and EFMUK files.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_SPE_PARENTAL_RATING_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure: Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_OUT_OF_MEM_MSK:	No available memory space in EFMSK.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_OUT_OF_MEM_MUK:	No available memory space in EFMUK")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_COND_USE_NOT_SATISFIED:	Conditions of use not satisfied.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_AUTH_ERR_MAC:	Authentication error, incorrect MAC.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_OK:	Verification is successful, no MIKEY verification message available.")
    CONST_TBL_ENTRY_VER(SIM_ST_MSK_UPDATE,              15, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "An MBMS MTK Generation mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 69 (MBMS) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"A prior GBA Bootstrap and GBA Bootstrap Update completed successful.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"A prior MSK Update completed successful.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_MIKEY_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"  Notice: This is the MIKEY MSK Update Message, coding defined in TS 33.246, with")
	COMMENT(COMMENT_TEXT,"further oma EXT BCAST format support defined in BCAST10-ServContProt (/27/).")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_SPE_PARENTAL_CONTROL_OPERATION_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_TEK_DATA_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_MTK_SALT_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: UICC computes the MGV-F function and returns the MTK (and SALT if available), as described in TS 33.246.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFMSK file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure: Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND	Referenced data not found.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_COND_USE_NOT_SATISFIED:	Conditions of use not satisfied.")
  	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_KEY_FRESH	Key freshness failure.")
    CONST_TBL_ENTRY_VER(SIM_ST_MTK_GENERATION,          16, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "An MBMS MSK Deletion mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 69 (MBMS) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_DOMAIN_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "No sub blocks are included.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFMSK file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure: Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_MSK_DELETION,            17, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "An MBMS MUK Deletion mode authentication will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 69 (MBMS) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_MUK_RECORD_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: A MUK ID TLV is constructed from the given data (in the SIM_SB_AM_MBMS_MUK_RECORD):") 
	COMMENT(COMMENT_TEXT, "MUK IDr Data, MUK IDi Data and passed to UICC for deletion. The rest (E.g. Time Stamp Counter Data) is ignored.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "No sub blocks are included.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: UICC have updated EFMUK file. UICC may have further updated EFGBABP, EFGBANL.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure: Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_MUK_DELETION,            18, "017.003", "")

     /************************  SIM_ST_BCAST_SPE_AUDIT_KEYS  **********************************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST audit keys function is performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request: None.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_KEY_GROUP_DESCRIPTION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: One ore more key group description subblocks may be returned.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_SPE_AUDIT_KEYS,            19, "018.000", "")

     /************************  SIM_ST_BCAST_SPE_AUDIT_SECURITY_POLICY  ***********************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST audit security policy function is performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_DOMAIN_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: One ore more spe description subblocks may be returned.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_SPE_AUDIT_SECURITY_POLICY,            20, "018.000", "")

     /************************  SIM_ST_BCAST_SPE_DELETION  ************************************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST Security Policy Extension Deletion will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_DOMAIN_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If one of the above three optional subblocks are present, all three subblocks shall be present.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_SPE_DELETION,            21, "018.000", "")

     /************************  SIM_ST_BCAST_REC_DELETION  ************************************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST recording deletion will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: Only one sim_sb_am_bcast_management_data subblock is returned in the response. One or more sim_sb_am_bcast_spe_description subblocks may be returned, each corresponding to an OMA BCAST flagged SPE.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_REC_DELETION,            22, "018.000", "")

     /************************  SIM_ST_BCAST_REC_SIGNALLING  **********************************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST record signalling will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_DOMAIN_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_BCAST_REC_TS_INTERVAL_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_SPE_AVAILABLE_NR_OF_REC_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: Only one sim_sb_am_bcast_spe_available_nr_of_rec subblock is returned in the response. One or more sim_sb_am_bcast_spe_description subblocks may be returned, each corresponding to an OMA BCAST flagged SPE.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_OUT_OF_MEM_MSK:	Authentication error, no memory space available.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_REC_SIGNALLING,          23, "018.000", "")

     /************************  SIM_ST_BCAST_REC_AUDIT_CONTENT  *******************************/
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "An OMA BCAST recording audit will be performed. This will retrieve all the content identifiers of recorded content and their associated flagged SPE's.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Presumption: Service No 68 (GBA) and service No 75 (BCAST) must be available in the Service Table file.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")  
	COMMENT(COMMENT_TEXT, "Required subblocks in request: None")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_SB_AM_BCAST_REC_CONTENT_DESCRIPTION_ID subblock.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK \226 SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: Not Supported  handled as Not OK below")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK: Permanent Failure. Generic Error. No further info.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_DATA_NOT_FOUND:	Referenced data not found.")
    CONST_TBL_ENTRY_VER(SIM_ST_BCAST_REC_AUDIT_CONTENT,       24, "018.000", "")

    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_AM_REQ / SIM_AM_RESP    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AM_SERVICE_TYPE_TABLE, 8, BE, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Provides NAA application specific information  including status info.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA")
	COMMENT(COMMENT_TEXT, "application is used (USIM or SIM).")      
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Generic Error Code is not available. No further info.")
   CONST_TBL_ENTRY_VER(SIM_ST_APP_INFO,              1, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Provides all available NAA application (string) labels from the (u)icc.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: The returned application information holds an application handle")
	COMMENT(COMMENT_TEXT, " (6.12.1 SIM_SB_AM_HANDLE subblock) which may be used in subsequent requests")
	COMMENT(COMMENT_TEXT, " for targeting a specific NAA Application residing on the (u)icc.")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Required subblocks in request:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "No sub blocks are included in the request.")   
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_APP_INFO_RECORD")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: One or more USIM and/or ISIM NAA applications may reside on an UICC.")
	COMMENT(COMMENT_TEXT, " Typically only one (telecom) USIM (and possibly one or more ISIM) NAA applications resides on the UICC.")
 	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_APP_INFO_RECORD")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: That only one (telecom) NAA application always resides on an ICC.")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Generic Error Code is not available. No further info.")
   CONST_TBL_ENTRY_VER(SIM_ST_APP_GET_ALL_LABELS,    2, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Activate NAA application. Allocates resources for the NAA application and activates it on the (u)icc.")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Required subblocks in request:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
 	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Notice: That only one (telecom) NAA application always resides on an ICC.")
	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Generic Error Code is not available. No further info.")
   CONST_TBL_ENTRY_VER(SIM_ST_APP_ACTIVATE,          3, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Releases the resources used for the NAA application on the (u)icc.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Required subblocks in request:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Notice: A successful application release execution, will invalidate all\
	                     further references for this particular NAA application handle (i.e. usage\
			     of the concrete SIM_SB_AM_HANDLE ).")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"No sub blocks are included in the success response.")
 	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"No sub blocks are included in the success response.")
 	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Generic Error Code is not available. No further info.")
   CONST_TBL_ENTRY_VER(SIM_ST_APP_RELEASE,           4, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "This function is used for detecting wether a specific service is available from\
	                       a specific NAA application residing on the (u)icc smart card. The function may be\
			       used e.g. to ensure that some NAA application specific file data exist on the (u)icc,\
			       before accessing the data.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Required subblocks in request:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_SERVICE_ID")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,"Notice: A successful application release execution, will invalidate all\
	                     further references for this particular NAA application handle (i.e. usage\
			     of the concrete SIM_SB_AM_HANDLE ).")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA\
	                       application is used (USIM or SIM).")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT, "Subblocks in response(OK case, USIM/ISIM NAA app.):")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_SERVICE_ID")
  	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK, SIM NAA App.):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"No sub blocks are included in the success response.")
 	COMMENT(COMMENT_PARAGRAPH, "    ")    
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_SERVICE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Generic Error Code is not available. No further info.")	
   CONST_TBL_ENTRY_VER(SIM_ST_APP_SERVICE_AVAIL,     5, "017.003", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, " file data read operation will be performed.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT,"Notice: Some files requires the related service number to be available in the NAA\
	                      application service table.")
        COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT,"Required subblocks in request:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_FILE_DATA_ID")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_TEXT,"Optional subblocks in request:")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: If the optional SIM_SB_AM_HANDLE is not present, the default telecom NAA\
	                       application is used (USIM or SIM).")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Subblocks in response(SIM_AM_RESP):")
        COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_BULLET, "File ID: SIM_FDI_IMPI:")
  	COMMENT(COMMENT_PARAGRAPH, "This FDI holds the IMS private user identity (IMPI) of the user.")    
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET,"SIM_SB_IMS_PRIVATE_USER_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: The IMPI value resides in the EFIMPI file, which is only defined\
	                       for an ISIM NAA Application. If the (optional) subblock in the request: SIM_SB_AM_HANDLE\
			       subblock, is not targeting an ISIM NAA Application  a derived value from the IMSI (EFIMSI)\
			       (SIM NAA Application or USIM NAA Application) will be returned.")
	COMMENT(COMMENT_PARAGRAPH, "    ")	 
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK	Permanent Failure. Generic Error. No further info.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Temporary Failure.\
                               Information is not available, e.g. could be loss of contact to the card.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "File ID: SIM_FDI_GBABP:")
	COMMENT(COMMENT_NEWLINE, "")
  	COMMENT(COMMENT_TEXT, "This FDI holds the AKA Random challenge (RAND) and Bootstrapping Transaction\
	                            Identifier (B-TID) associated with a GBA bootstrapping procedure.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: The RAND value is updated by UICC upon a successful gba bootstrap authentication execution.")    
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET,"SIM_SB_RAND_PARAMS_ID")
        COMMENT(COMMENT_BULLET,"SIM_SB_AM_GBA_B_TID_ID")
        COMMENT(COMMENT_BULLET,"SIM_SB_AM_GBA_KEY_LIFETIME_ID")
	COMMENT(COMMENT_PARAGRAPH, "    ")	 
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK	Permanent Failure. Generic Error. No further info.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Temporary Failure.\
                               Information is not available, e.g. could be loss of contact to the card.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "File ID: SIM_FDI_GBANL:")
	COMMENT(COMMENT_NEWLINE, "")
  	COMMENT(COMMENT_TEXT, "This FDI holds the list of GBANL records each consisting of a NAF_ID and associated B-TID.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: The NAF_ID and B-TID values (an GBANL record) are updated by the UICC upon a successful \
	                       GBA NAF derivation authentication execution.")    
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET,"SIM_SB_AM_GBA_GBANL_RECORD_ID")
 	COMMENT(COMMENT_PARAGRAPH, "    ")	 
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK	Permanent Failure. Generic Error. No further info.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Temporary Failure.\
                               Information is not available, e.g. could be loss of contact to the card.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_BULLET, "File ID: SIM_FDI_MSK:")
	COMMENT(COMMENT_NEWLINE, "")
  	COMMENT(COMMENT_TEXT, "This FDI holds the list of MSK records each consisting of MBMS Service keys \
	                            (MSK IDs) and associated parameters.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: The MSK record values are updated by the UICC upon a successful mbms MSK \
	                       update authentication execution.")    
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET,"SIM_SB_AM_MBMS_MSK_RECORD_ID")
 	COMMENT(COMMENT_PARAGRAPH, "    ")	 
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE_ID")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK	Permanent Failure. Generic Error. No further info.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Temporary Failure.\
                               Information is not available, e.g. could be loss of contact to the card.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_NEWLINE, "")		   
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "File ID: SIM_FDI_MUK:")
	COMMENT(COMMENT_NEWLINE, "")
  	COMMENT(COMMENT_TEXT, "This FDI holds the list of MUK records each consisting of the MBMS \
	                            User Key parameters that is used to protect the transfer of MBMS Service Keys (MSK).")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: The MUK record values are updated by the UICC upon a successful mbms MSK update authentication execution.")    
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Subblocks in response(OK):")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET,"SIM_SB_AM_MBMS_MUK_RECORD_ID")
 	COMMENT(COMMENT_PARAGRAPH, "    ")	 
        COMMENT(COMMENT_TEXT, "Subblocks in response(Not OK):")
	COMMENT(COMMENT_BULLET, "SIM_SB_AM_HANDLE")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Notice: To be used for detailed status and/or generic error code information.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "The following generic error codes may be returned:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_OK	Permanent Failure. Generic Error. No further info.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "SIM_GEC_ID_NOT_AVAILABLE:Temporary Failure.\
                               Information is not available, e.g. could be loss of contact to the card.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_NEWLINE, "")	
   CONST_TBL_ENTRY_VER(SIM_ST_FILE_DATA_READ,        6, "017.003", "020.000")
   CONST_TBL_END


    /* --------------------------------------------------------------------- */
    /* Service types for SMS                                                 */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SMS")
    CONST_TBL_BEGIN(SIM_SMS_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_SMS_GET_NUM_OF_LOC,          1, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_READ,                    2, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_WRITE,                   3, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_ERASE,                   4, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_UPDATE_STATUS,           5, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_READ_RAW,                6, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_WRITE_RAW,               7, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for HomeZone                                            */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for HomeZone")
    CONST_TBL_BEGIN(SIM_HOMEZONE_SERVICE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_READ_SUBSCRIBED_LAC_CI,       79, "")
        CONST_TBL_ENTRY(SIM_ST_READ_HZ_TAGS,                 80, "")
        CONST_TBL_ENTRY(SIM_ST_READ_UHZIUE_SETTINGS,         81, "")
        CONST_TBL_ENTRY(SIM_ST_WRITE_UHZIUE_SETTINGS,        82, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /*  Service types for SIM_READ_ACM_ACCESS_REQ                            */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_READ_ACM_ACCESS_REQ")
    CONST_TBL_BEGIN(SIM_ACM_ACCESS_SERVICE_TYPE_TABLE, 8, BE, "", "020.000")
        CONST_TBL_ENTRY(ACM_SET,                            67, "")
        CONST_TBL_ENTRY(ACM_MAX_SET,                        68, "")
        CONST_TBL_ENTRY(PUCT_SET,                           69, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /*  Service types for SIM_ICC_TYPE_REQ                                   */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_ICC_TYPE_SERVICE_TYPE_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        CONST_TBL_ENTRY(SIM_ST_READ_SB,                     1, "Read the requested sub-blocks.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Read all possible sub-blocks")
        CONST_TBL_ENTRY_VER(SIM_ST_READ_ALL_SB,             2, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Read the current AID of for the active application on ICC.")
        CONST_TBL_ENTRY_VER(SIM_ST_READ_ACTIVE_AID_SB,      3, "", "020.000")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* States                                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_STATE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(STATE_SIM_INIT_WAIT,           1, "")
        CONST_TBL_ENTRY(STATE_SIM_LOCK_OPERATIVE,      2, "")
        CONST_TBL_ENTRY(STATE_SIM_PIN_VERIFY_REQUIRED, 3, "") 
        CONST_TBL_ENTRY(STATE_SIM_PERMANENTLY_BLOCKED, 4, "")
        CONST_TBL_ENTRY(STATE_SIM_REMOVED,             5, "")
        CONST_TBL_ENTRY(STATE_SIM_REJECTED,            6, "")
        CONST_TBL_ENTRY(STATE_SIM_BLOCKED,             7, "")
        CONST_TBL_ENTRY(STATE_SIM_OK,                  8, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* PLMN operations                                                       */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_PLMN_OPERATIONS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(PLMN_ADD,                      42, "")
        CONST_TBL_ENTRY(PLMN_REMOVE,                   87, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Misc service types                                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_MISC_SERVICE_TYPE_TABLE, 8, BE, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "PIN")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_PIN,                           1, "Service Type for PIN1")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "PIN2")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_PIN2,                          2, "Service type for PIN2")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "ALL_SERVICES")
        CONST_TBL_ENTRY(SIM_ST_ALL_SERVICES,                  5, "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "ADN")
	COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_ADN,                           7, "Abbreviated Dialling Number")
	PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "FDN")
	COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_FDN,                           9, "Fixed Dialling Number")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(VMBX,                                11, "Voice MailBoX Number")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "INFONUM")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_INFONUM,                      12, "Mercury Information Number")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "INFO")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_INFO,                         13, "SIM RAM Information Storage")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "JACOB")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_JACOB,                        14, "JACOB services")
        CONST_TBL_ENTRY(SMS,                                 15, "")
        CONST_TBL_ENTRY(ACM,                                 16, "")
        CONST_TBL_ENTRY(SERVICE_TABLE,                       17, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of ADN records on the card.")
        CONST_TBL_ENTRY_VER(READ_ADN_CNT,                    24, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_ADN_ALPHA_LEN,                  25, "The length of ADN name field on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of PLMN Selector records on the card.")
        CONST_TBL_ENTRY_VER(READ_PLMN_SELECTOR_CNT,          26, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_FDN_CNT,                        27, "The number of FDN records on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_FDN_ALPHA_LEN,                  28, "The length of FDN name field on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_MSISDN_CNT,                     29, "The number of MSISDN records on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of MSISDN name field on the card.")
        CONST_TBL_ENTRY_VER(READ_MSISDN_ALPHA_LEN,           30, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_SMS_PARAM_CNT,                  31, "The number of SMS parameter records on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of SMS parameter Aplha ID field on the card.")
        CONST_TBL_ENTRY_VER(READ_SMS_PARAM_ALPHA_LEN,        32, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of language preference records on the card.")
        CONST_TBL_ENTRY_VER(READ_PREF_LANGUAGE_CNT,          33, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of Operator name field on the card.")
        CONST_TBL_ENTRY_VER(READ_OPERATOR_NAME_LEN,          34, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of MBX records on the card.")
        CONST_TBL_ENTRY_VER(READ_MBX_CNT,                    35, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of MBX Alpha tag on the card.")
        CONST_TBL_ENTRY_VER(READ_MBX_ALPHA_LEN,              36, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_CB_MSG_ID_CNT,                  37, "The number of CB message IDs on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of the CSP1 file on the card.")
        CONST_TBL_ENTRY_VER(READ_CSP1_LEN,                   38, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of info. numbers on the card.")
        CONST_TBL_ENTRY_VER(READ_INF_NBR_CNT,                39, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_JACOB_ID_CNT,                   40, "The number of Jacob IDs on the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of the VMWI file on the card")
        CONST_TBL_ENTRY_VER(READ_VMWI_LEN,                   41, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of the CPHS file.")
        CONST_TBL_ENTRY_VER(READ_CPHS_LEN,                   42, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The number of Emergency Call Codes.")
        CONST_TBL_ENTRY_VER(READ_ECC_CNT,                    43, "", "020.000")
        CONST_TBL_ENTRY(READ_PREF_LANGUAGE,                  46, "")
        CONST_TBL_ENTRY(READ_HPLMN,                          47, "")
        CONST_TBL_ENTRY_VER(WRITE_FIRST_PLMN,                49, "", "020.000")
        CONST_TBL_ENTRY(MSISDN_STORE,                        50, "")
        CONST_TBL_ENTRY_VER(CHECK_CELL_ID,                   51, "", "020.000")
        CONST_TBL_ENTRY(READ_ID,                             52, "")
        CONST_TBL_ENTRY(READ_DYN_FLAGS,                      53, "")
        CONST_TBL_ENTRY(WRITE_DYN_FLAGS,                     54, "")
        CONST_TBL_ENTRY(READ_DYN2_FLAGS,                     55, "")
        CONST_TBL_ENTRY(WRITE_DYN2_FLAGS,                    56, "")
        CONST_TBL_ENTRY(READ_LINE_DATA,                      59, "")
        CONST_TBL_ENTRY(READ_TO_SCM,                         60, "")
        CONST_TBL_ENTRY(WRITE_FROM_SCM,                      61, "")
        CONST_TBL_ENTRY(READ_DATA,                           63, "")
        CONST_TBL_ENTRY(READ_PACKAGE,                        64, "")
        CONST_TBL_ENTRY(READ_COORDINATES,                    65, "")
        CONST_TBL_ENTRY(MSISDN_READ,                         66, "")
        CONST_TBL_ENTRY(ACM_SET,                             67, "")
        CONST_TBL_ENTRY(ACM_MAX_SET,                         68, "")
        CONST_TBL_ENTRY(PUCT_SET,                            69, "")
        CONST_TBL_ENTRY(PREF_LANGUAGE,                       70, "")
        CONST_TBL_ENTRY(EMERGENCY_CODES,                     71, "")
        CONST_TBL_ENTRY(READ_CB_MSG_IDS,                     72, "")
        CONST_TBL_ENTRY(SDN,                                 73, "")
        CONST_TBL_ENTRY(INFO_USER_WHEN_MSG_SEND,             74, "")
        CONST_TBL_ENTRY(FACTORY_SETTING,                     75, "")
        CONST_TBL_ENTRY(READ_PARAM,                          76, "")
        CONST_TBL_ENTRY(READ_CACHE,                          77, "")
        CONST_TBL_ENTRY(WRITE_CACHE,                         78, "")
/*#define SEND_APDU                  79
#define GET_ATR                    80 
#define GET_LIST                   81*/
        CONST_TBL_ENTRY(READ_PARAMETER,                      82, "")
        CONST_TBL_ENTRY(UPDATE_PARAMETER,                    83, "")
        CONST_TBL_ENTRY_VER(READ_STATUS,                     84, "", "020.000")
        CONST_TBL_ENTRY_VER(WRITE_STATUS,                    85, "", "020.000")
        CONST_TBL_ENTRY(GPRS_AUTH,                           97, "")
        CONST_TBL_ENTRY(GSM_AUTH,                            98, "")
        CONST_TBL_ENTRY(CS,                                  99, "")
        CONST_TBL_ENTRY(READ_FIELD,                         100, "")
        CONST_TBL_ENTRY_VER(ACC,                            101, "", "020.000")
        CONST_TBL_ENTRY(ICC,                                102, "")
        CONST_TBL_ENTRY_VER(AD,                             103, "", "020.000")
        CONST_TBL_ENTRY(ICC_EQUAL,                          104, "")
        CONST_TBL_ENTRY(UPDATE_CB_MSGIDS,                   105, "")
        CONST_TBL_ENTRY(READ_REAL_JACOB_IDS,                106, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "DSS contant.Don't use in future development")
        CONST_TBL_ENTRY_VER(CB_DOWNLOAD,                    107, "", "020.000")
        CONST_TBL_ENTRY_VER(READ_CBMIDS,                    108, "", "020.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_ADN_NBR_LEN,                   110, "The ADN number length.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(READ_FDN_NBR_LEN,                   111, "The FDN number length.")
        CONST_TBL_ENTRY_VER(READ_MSISDN_NBR_LEN,            112, "", "020.000")
        CONST_TBL_ENTRY(SIM_ST_APP_SELECTION,               150, "")
        CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL,               151, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_SUBSTITUTE_PIN,              153, "PIN1 substitutes universal PIN as active PIN")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_ST_SUBSTITUTE_PIN_UNIVERSAL,    154, "Univsersal PIN substitutes PIN1 as active PIN.")
        CONST_TBL_ENTRY(SIM_ST_READ_VMBX_CNT,               156, "")
        CONST_TBL_ENTRY(SIM_ST_READ_VMBX_ALPHA_LEN,         157, "")
        CONST_TBL_ENTRY(SIM_ST_READ_VMBX_NBR_LEN,           158, "")
        CONST_TBL_ENTRY(SIM_ST_READ_MBDN_CNT,               159, "")
        CONST_TBL_ENTRY(SIM_ST_READ_MBDN_PROFILE_SIZE,      160, "")
        CONST_TBL_ENTRY(SIM_ST_READ_MBDN_PROFILE_CNT,       161, "")
        CONST_TBL_ENTRY(SIM_ST_READ_MBDN_ALPHA_LEN,         162, "")
        CONST_TBL_ENTRY(SIM_ST_READ_MBDN_NBR_LEN,           163, "")
        CONST_TBL_ENTRY(SIM_ST_PUK,                         164, "")
        CONST_TBL_ENTRY(SIM_ST_PUK2,                        165, "")
        CONST_TBL_ENTRY(SIM_ST_PUK_UNIVERSAL,               166, "")
        PROPERTY_STRING(PROPERTY_ISIHDR_ALIAS_NAME, "PIN_PARENTAL_CONTROL")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY_VER(SIM_ST_PIN_PARENTAL_CONTROL,    167, "018.000", "")  /* Service type for PIN Parental Control */
        CONST_TBL_ENTRY_VER(SIM_ST_PUK_PARENTAL_CONTROL,    168, "018.000", "")  /* Service type for PUK Parental Control */
        CONST_TBL_ENTRY(NO_SERVICE_TYPE,                    250, "")  
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service types for SIM_READ_TABLE_REQ                                  */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_ST_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_PIN1_DISABLE_FUNCTION,           1, "")
        CONST_TBL_ENTRY(SIM_ST_ADN_AVAIL,                       2, "")
        CONST_TBL_ENTRY(SIM_ST_FDN_AVAIL,                       114, "")
        CONST_TBL_ENTRY(SIM_ST_SMS_AVAIL,                       4, "")
        CONST_TBL_ENTRY(SIM_ST_AOC_AVAIL,                       113, "")
        CONST_TBL_ENTRY(SIM_ST_CCP_AVAIL,                       6, "")
        CONST_TBL_ENTRY(SIM_ST_PLMN_SELECTOR_AVAIL,             7, "")
        CONST_TBL_ENTRY(SIM_ST_MSISDN_AVAIL,                    8, "")
        CONST_TBL_ENTRY(SIM_ST_EXT1_AVAIL,                      9, "")
        CONST_TBL_ENTRY(SIM_ST_EXT2_AVAIL,                      10, "")
        CONST_TBL_ENTRY(SIM_ST_EXT3_AVAIL,                      11, "")
        CONST_TBL_ENTRY(SIM_ST_EXT4_AVAIL,                      12, "")
        CONST_TBL_ENTRY(SIM_ST_EXT5_AVAIL,                      13, "")
        CONST_TBL_ENTRY(SIM_ST_SMSP_AVAIL,                      14, "")
        CONST_TBL_ENTRY(SIM_ST_LDN_AVAIL,                       15, "")
        CONST_TBL_ENTRY(SIM_ST_CBMI_AVAIL,                      16, "")
        CONST_TBL_ENTRY(SIM_ST_GID_L1_AVAIL,                    3, "")
        CONST_TBL_ENTRY(SIM_ST_GID_L2_AVAIL,                    18, "")
        CONST_TBL_ENTRY(SIM_ST_SPN_AVAIL,                       19, "")
        CONST_TBL_ENTRY(SIM_ST_SDN_AVAIL,                       20, "")
        CONST_TBL_ENTRY(SIM_ST_VGCS_GID_LIST_AVAIL,             21, "")
        CONST_TBL_ENTRY(SIM_ST_VBS_GID_LIST_AVAIL,              22, "")
        CONST_TBL_ENTRY(SIM_ST_EMLPP_SERVICE_AVAIL,             23, "")
        CONST_TBL_ENTRY(SIM_ST_AA_EMLPP_AVAIL,                  24, "")
        CONST_TBL_ENTRY(SIM_ST_SMSCB_DATA_DOWNLOAD_AVAIL,       115, "")
        CONST_TBL_ENTRY(SIM_ST_SMSPP_DATA_DOWNLOAD_AVAIL,       26, "")
        CONST_TBL_ENTRY(SIM_ST_MENU_SELECTION_AVAIL,            27, "")
        CONST_TBL_ENTRY(SIM_ST_CALL_CONTROL_AVAIL,              116, "")
        CONST_TBL_ENTRY(SIM_ST_PROACTIVE_SIM,                   29, "")
        CONST_TBL_ENTRY(SIM_ST_CBMIR_AVAIL,                     30, "")
        CONST_TBL_ENTRY(SIM_ST_BDN_AVAIL,                       31, "")
        CONST_TBL_ENTRY(SIM_ST_DEPERSONALIZATION_KC_AVAIL,      32, "")
        CONST_TBL_ENTRY(SIM_ST_CO_OP_NET_LIST_AVAIL,            33, "")
        CONST_TBL_ENTRY(SIM_ST_SMSR_AVAIL,                      34, "")
        CONST_TBL_ENTRY(SIM_ST_NET_IND_ALERT_IN_MS_AVAIL,       35, "")
        CONST_TBL_ENTRY(SIM_ST_MO_SMS_SIM_CONTROL_AVAIL,        36, "")
        CONST_TBL_ENTRY(SIM_ST_GPRS_AVAIL,                      37, "")
        CONST_TBL_ENTRY(SIM_ST_IMAGE_AVAIL,                     38, "")
        CONST_TBL_ENTRY(SIM_ST_SOLSA_AVAIL,                     39, "")
        CONST_TBL_ENTRY(SIM_ST_USSD_IN_CALL_CONTROL_AVAIL,      40, "")
        CONST_TBL_ENTRY(SIM_ST_RUN_AT_COMMAND_AVAIL,            41, "")
        CONST_TBL_ENTRY(SIM_ST_UPLMN_WITH_AT_AVAIL,             42, "")
        CONST_TBL_ENTRY(SIM_ST_OPLMN_WITH_AT_AVAIL,             43, "")
        CONST_TBL_ENTRY(SIM_ST_HPLMN_WITH_AT_AVAIL,             44, "")
        CONST_TBL_ENTRY(SIM_ST_CPBCCH_INFO_AVAIL,               45, "")
        CONST_TBL_ENTRY(SIM_ST_INVESTIGATION_SCAN_AVAIL,        46, "")
        CONST_TBL_ENTRY(SIM_ST_EXT_CC_PARAMS_AVAIL,             47, "")
        CONST_TBL_ENTRY(SIM_ST_MEXE_AVAIL,                      48, "")
        CONST_TBL_ENTRY(SIM_ST_RPLMN_LAST_USED_AT_AVAIL,        49, "")
        CONST_TBL_ENTRY(SIM_ST_LOCAL_PHONE_BOOK_AVAIL,          50, "")
        CONST_TBL_ENTRY(SIM_ST_ICI_AVAIL,                       51, "")
        CONST_TBL_ENTRY(SIM_ST_GSM_ACCESS_AVAIL,                52, "")
        CONST_TBL_ENTRY(SIM_ST_ENABLED_SERVICE_TABLE_AVAIL,     53, "")
        CONST_TBL_ENTRY(SIM_ST_ACL_AVAIL,                       54, "")
        CONST_TBL_ENTRY(SIM_ST_GSM_SECURITY_CONTEXT_AVAIL,      55, "")
        CONST_TBL_ENTRY(SIM_ST_GPRS_CALL_CONTROL_AVAIL,         56, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Location types used by SIM_PB_REQ                                     */
    /* --------------------------------------------------------------------- */

    #define SIM_PB_SB_START                         200 

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_PB_LOCATION_TYPE_TABLE, 16, BE, "", "")
        CONST_TBL_ENTRY(SIM_PB_ADN,                              (SIM_PB_SB_START + 0), "")
        CONST_TBL_ENTRY(SIM_PB_ADN_NUMBER_LENGTH,                (SIM_PB_SB_START + 1), "")
        CONST_TBL_ENTRY(SIM_PB_ANR,                              (SIM_PB_SB_START + 2), "")
        CONST_TBL_ENTRY(SIM_PB_BDN,                              (SIM_PB_SB_START + 3), "")
        CONST_TBL_ENTRY(SIM_PB_CC,                               (SIM_PB_SB_START + 4), "")
        CONST_TBL_ENTRY(SIM_PB_CCP,                              (SIM_PB_SB_START + 5), "")
        CONST_TBL_ENTRY(SIM_PB_CCP1,                             (SIM_PB_SB_START + 6), "")
        CONST_TBL_ENTRY(SIM_PB_CCP2,                             (SIM_PB_SB_START + 7), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_ADN_SB,                      (SIM_PB_SB_START + 8), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_ANR_SB,                      (SIM_PB_SB_START + 9), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_EMAIL_SB,                    (SIM_PB_SB_START + 10), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_FDN_SB,                      (SIM_PB_SB_START + 11), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_GAS_SB,                      (SIM_PB_SB_START + 12), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_GRP_SB,                      (SIM_PB_SB_START + 13), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_MISC_SB,                     (SIM_PB_SB_START + 14), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_PH_1,                        (SIM_PB_SB_START + 15), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_PH_3,                        (SIM_PB_SB_START + 16), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_SNE_SB,                      (SIM_PB_SB_START + 17), "")
        CONST_TBL_ENTRY(SIM_PB_CONF_AAS_SB,                      (SIM_PB_SB_START + 18), "")
        CONST_TBL_ENTRY(SIM_PB_DELETE_ALL,                       (SIM_PB_SB_START + 19), "")
        CONST_TBL_ENTRY(SIM_PB_DELETE_LOCATION,                  (SIM_PB_SB_START + 20), "")
        CONST_TBL_ENTRY(SIM_PB_EMAIL,                            (SIM_PB_SB_START + 21), "")
        CONST_TBL_ENTRY(SIM_PB_FDN,                              (SIM_PB_SB_START + 22), "")
        CONST_TBL_ENTRY(SIM_PB_FDN_LIST_STATUS,                  (SIM_PB_SB_START + 23), "")
        CONST_TBL_ENTRY(SIM_PB_FDN_NUMBER_LENGTH,                (SIM_PB_SB_START + 24), "")
        CONST_TBL_ENTRY(SIM_PB_GAS,                              (SIM_PB_SB_START + 25), "")
        CONST_TBL_ENTRY(SIM_PB_GRP,                              (SIM_PB_SB_START + 26), "")
        CONST_TBL_ENTRY(SIM_PB_HIDDEN,                           (SIM_PB_SB_START + 27), "")
        CONST_TBL_ENTRY(SIM_PB_INFO_REQUEST,                     (SIM_PB_SB_START + 28), "")
        CONST_TBL_ENTRY(SIM_PB_LDN,                              (SIM_PB_SB_START + 29), "")
        CONST_TBL_ENTRY(SIM_PB_LOC,                              (SIM_PB_SB_START + 30), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_ANR,                          (SIM_PB_SB_START + 31), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_EMAIL,                        (SIM_PB_SB_START + 32), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_FIRST,                        (SIM_PB_SB_START + 33), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_GAS,                          (SIM_PB_SB_START + 34), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_GRP,                          (SIM_PB_SB_START + 35), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_NEXT,                         (SIM_PB_SB_START + 36), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_SNE,                          (SIM_PB_SB_START + 37), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_AAS,                          (SIM_PB_SB_START + 38), "")
        CONST_TBL_ENTRY(SIM_PB_MSISDN_NUMBER_LENGTH,             (SIM_PB_SB_START + 39), "")
        CONST_TBL_ENTRY(SIM_PB_PBC,                              (SIM_PB_SB_START + 40), "")
        CONST_TBL_ENTRY(SIM_PB_PSC,                              (SIM_PB_SB_START + 41), "")
        CONST_TBL_ENTRY(SIM_PB_PUID,                             (SIM_PB_SB_START + 42), "")
	CONST_TBL_ENTRY(SIM_PB_ROOM_INFO_ERROR,                  (SIM_PB_SB_START + 43), "")
        CONST_TBL_ENTRY(SIM_PB_ROOM_INFO_REQUEST,                (SIM_PB_SB_START + 44), "")
        CONST_TBL_ENTRY(SIM_PB_SDN,                              (SIM_PB_SB_START + 45), "")
        CONST_TBL_ENTRY(SIM_PB_SELECT_PB_SB,                     (SIM_PB_SB_START + 46), "")
        CONST_TBL_ENTRY(SIM_PB_SNE,                              (SIM_PB_SB_START + 47), "")
        CONST_TBL_ENTRY(SIM_PB_STARTUP_PHASE_1,                  (SIM_PB_SB_START + 48), "")
        CONST_TBL_ENTRY(SIM_PB_STARTUP_PHASE_2,                  (SIM_PB_SB_START + 49), "")
        CONST_TBL_ENTRY(SIM_PB_STARTUP_PHASE_3,                  (SIM_PB_SB_START + 50), "")
        CONST_TBL_ENTRY(SIM_PB_STATUS,                           (SIM_PB_SB_START + 51), "")
        CONST_TBL_ENTRY(SIM_PB_UID,                              (SIM_PB_SB_START + 52), "")
        CONST_TBL_ENTRY(SIM_PB_AAS,                              (SIM_PB_SB_START + 53), "")
        CONST_TBL_ENTRY(SIM_PB_LOCATION,                         (SIM_PB_SB_START + 54), "")
        CONST_TBL_ENTRY(SIM_PB_LOCATION_SEARCH,                  (SIM_PB_SB_START + 55), "")
        CONST_TBL_ENTRY(SIM_PB_MSISDN,                           (SIM_PB_SB_START + 56), "")
        CONST_TBL_ENTRY(SIM_PB_VMBX,                             (SIM_PB_SB_START + 57), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_VMBX,                         (SIM_PB_SB_START + 58), "")
        CONST_TBL_ENTRY(SIM_PB_VMBX_NUMBER_LENGTH,               (SIM_PB_SB_START + 59), "")
        CONST_TBL_ENTRY(SIM_PB_LOC_BDN,                          (SIM_PB_SB_START + 60), "")
        CONST_TBL_ENTRY(SIM_PB_BDN_NUMBER_LENGTH,                (SIM_PB_SB_START + 61), "")
        CONST_TBL_ENTRY(SIM_PB_MBDN,                             (SIM_PB_SB_START + 62), "")
        CONST_TBL_ENTRY_VER(SIM_PB_CONF_ADN_LONG_SB,             (SIM_PB_SB_START + 63), "014.008", "")
        CONST_TBL_ENTRY_VER(SIM_PB_CONF_ANR_LONG_SB,             (SIM_PB_SB_START + 64), "014.017", "")
        CONST_TBL_ENTRY_VER(SIM_PB_CONF_EMAIL_LONG_SB,           (SIM_PB_SB_START + 65), "014.017", "")
        CONST_TBL_ENTRY_VER(SIM_PB_CONF_SNE_LONG_SB,             (SIM_PB_SB_START + 66), "014.017", "")
        CONST_TBL_ENTRY_VER(SIM_PB_CONF_GRP_LONG_SB,             (SIM_PB_SB_START + 67), "014.017", "")
        CONST_TBL_ENTRY_VER(SIM_PB_SB_END,                       (SIM_PB_SB_START + 68), "014.000", "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Presence types used by SIM_PB_REQ / SIM_PB_RESP                       */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_PRESENCE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_NONE,                           4, "")    
        CONST_TBL_ENTRY(SIM_PUBLIC,                         1, "")
        CONST_TBL_ENTRY(SIM_PRIVATE,                        2, "")
        CONST_TBL_ENTRY(SIM_BOTH,                           3, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* ATT RAT mode settings                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_ATT_RAT_MODE, 8, BE, "017.006", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "All supported bands and all supported RATs used.")
             CONST_TBL_ENTRY_VER(SIM_RAT_DUAL_MODE,                           0, "017.006", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "2G only, all supported bands on 2G used.")  
             CONST_TBL_ENTRY_VER(SIM_RAT_2G_ONLY,                             1, "017.006", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "3G only, all supported bands on 3G used.")  
             CONST_TBL_ENTRY_VER(SIM_RAT_3G_ONLY,                             2, "017.006", "")
    CONST_TBL_END

     /* --------------------------------------------------------------------- */
    /* Line types                                                            */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    CONST_TBL_BEGIN(SIM_LINE_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_PRIMARY_LINE,     0, "")
        CONST_TBL_ENTRY(SIM_ALTERNATE_LINE,   1, "")
        CONST_TBL_ENTRY(SIM_ALL_LINES,        2, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Address types                                                         */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_ADDRESS_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SMS_GSM_0340_ADDRESS,           0x01, "")
        CONST_TBL_ENTRY(SIM_SMS_GSM_0411_ADDRESS,           0x02, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Access condition types                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_ACCESS_CONDITION_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ALW,           0, "")
        CONST_TBL_ENTRY(SIM_PIN1,          1, "")
        CONST_TBL_ENTRY(SIM_PIN2,          2, "")
        CONST_TBL_ENTRY(SIM_ADM,           5, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Refresh file IDs                                                      */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_REFRESH_FILE_ID_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ICC_ID,                                            1, "Refresh ICC identification, EFicc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ADMINISTRATIVE_DATA,                               2, "Refresh administrative data, EFad.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_TABLE,                                     3, "Refresh Service Table.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_IMSI,                                              4, "Refresh IMSI, EFimsi. ")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_FORBIDDEN_PLMNS,                                   5, "Refresh forbidden PLMNs, EFfplmn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_LOCATION_INFOMATION,                               6, "Refresh location information, EFloci.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_KEY_KC,                                  7, "Refresh ciphering key Kc, EFkc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PLMN_SELECTOR,                                     8, "Refresh PLMN selector, EFplmnsel.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_CONTROL_CHANNELS,                   9, "Refresh Broadcast Control Channels, EFbcch.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_MESSAGE_IDENTIFIER,                10, "Refresh Cell Broadcast Message Identifiers, EFcbmi")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ACCESS_CONTROL_CLASS,                             11, "Refresh Access Control Class, EFacc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_LANGUAGE_PREFERENCE,                              12, "Refresh Preferred Language, EFpl.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ACCUMULATED_CALL_METER,                           13, "Refresh Accumulated Call Meter, EFacm.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ACM_MAXIMUM_VALUE,                                14, "Refresh Accumulated Call Meter Maximum value, EFacmmax.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PRICE_PER_UNIT_CURRENCY_TABLE,                    15, "Refresh Price per Unit and Currency Table, EFpuct.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_HPLMN_SEACH_PERIOD,                               16, "HPLMN search period, EFhplmn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PHASE_IDENTIFICATION,                             17, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GROUP_ID_LEVEL_1,                                 18, "Refresh Group Identifier Level 1, EFgid1.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GROUP_ID_LEVEL_2,                                 19, "Refresh Group Identifier Level 1, EFgid2.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_PROVIDER_NAME,                            20, "Refresh Service Provider Name, EFspn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_EMERGENCY_CALL_CODES,                             21, "Refresh Emergency Call Codes, EFecc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_MESSSAGE_ID_DATA_DOWNLOAD,         22, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GPRS_LOCATION_INFORMATION,                        23, "Refresh Location Information: GSM: EFlocigprs,UMTS: EFpsloci.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GPRS_CIPHERING_KEY_KCGPRS,                        24, "Refresh GPRS ciphering key, KcGPRS, EFkcgprs.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_PLMN_LIST,                               25, "Refresh operator PLMN list, EFopl.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PLMN_NETWORK_NAME,                                26, "Refresh PLMN Network Name, EFpnn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CUSTORMER_SERVICE_PROFILE,                        27, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_VOICE_MESSAGE_WAITING,                            28, "Refresh Voice Message Waiting, EFmwis.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CALL_FORWARD_FLAGS,                               29, "Refresh Call Forward flags, EFcfis.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_NAME_STRING,                             30, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_NUMBERS,                                  31, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CPHS_INFO,                                        32, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_INFO_NUMBERS,                                     33, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ABBREVIATED_DIALLING_NUMBERS,                     34, "Refresh Abbreviavted Dialling Numbers, EFadn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGES,                                   35, "Refresh Short Service Messages, EFsms.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_FIXED_DIALLING_NUMBERS,                           36, "Refresh FDN, EFfdn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MSISDN,                                           37, "Refresh MSISDN, EFmsisdn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGE_SERVICE_PARAMETERS,                 38, "Refresh SMS Service Parameters, EFsmsp.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGE_SERVICE_STATUS,                     39, "Refresh SMS Status, EFsmss.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_DIALLING_NUMBERS,                         40, "Refresh Service Dialling Numbers, EFsdn.")
        CONST_TBL_ENTRY(SIM_REFRESH_CSP_LINE_2,                                       41, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_USER_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH,        42, "Refresh User Controlled PLMN selector with Access Technology, EFplnmwact.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH,    43, "Refresh Operator Controlled PLMN selector withAccess Technology, EFoplnmwact.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_HPLMN_SELECTOR_ACCESS_TECH,                       44, "Refresh HPLNM selector with Access Technology,EFhplnmwact.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MESSAGE_WAITING_INDICATION_STATUS,                45, "Refresh Message Waiting Indication Status, EFmwis.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CALL_FORWARDING_INDICATION_STATUS,                46, "Refresh Call Forwarding Indication Status, EFcfis.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_IDENTIFIER,                               47, "Refresh Mailbox Identifier, EFmbi.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_DIALLING_NUMBERS,                         48, "Refresh Mailbox numbers, EFmbdn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_EXTENDED_LANGUAGE_PREFERENCE,                     49, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_PROVIDER_DISPLAY_INFOMARTION,             50, "Refresh Service Provider Display Information, EFspdi.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_INTEGRITY_KEYS,                         51, "Refresh Ciphering and Integrity Keys, EFkeys.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_INTEGRITY_KEYS_PACKET_SWITCHED_DOMAIN,  52, "Refresh Ciphering Keys and integrity keys for Packet Switched domain, EFkeysps.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_INITIALISATION_VALUES_FOR_HYPERFRAME_NUMBER,      53, "Refresh Inittialization values for Hypeframe number, EFstart-hpn.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MAXIMUM_VALUE_OF_START,                           54, "Refresh Maximum value of START, EFthreshold.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PACKET_SWITCHED_LOCATION_INFORMATION,             55, "Refresh Packet Switched Location Information, EFpsloci.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_NETWORK_PARAMETERS,                               56, "Refresh Network Parameters, EFnetpar.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ENABLED_SERVICES_TABLE,                           57, "Refresh Enabled Service Table. EFest.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_APPLICATION_DIRECTORY,                            58, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PHONE_BOOK_REFERENCE_FILE,                        59, "Refresh PhoneBook Reference file, EFpbr.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_INDEX_ADMINISTRATION_PHONE_BOOK,                  60, "Refresh Index Administration Phonebook, EFiap.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GROUPING_FILE,                                    61, "Refresh Grouping file, EFgrp.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_GROUPING_INFORMATION_ALPHA_STRING,                62, "Refresh Grouping Info. Alpha String, EFgas.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_SECOND_NAME_ENTRY,                                63, "Refresh Second Name Entry, EFsne")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_UNKNOWN_FILES,                                    64, "")
        CONST_TBL_ENTRY(SIM_REFRESH_TERMINAL_SUPPORT_TABLE,                           65, "")
        CONST_TBL_ENTRY(SIM_REFRESH_ACTING_HPLMN,                                     66, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_IMAGE,                                            67, "Refresh Image, EFimg.")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_PARM,                               68, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE1,                                      69, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE2,                                      70, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE3,                                      71, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE4,                                      72, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MMS_USER_PREF,                                    73, "Refresh MMS User Preferences, EFmmsup.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_MMS_ISSUER_CONN_PAR,                              74, "Refresh MMS Issuer Connectivity Parameters, EFmmsucp.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_DYNAMIC_FLAGS1,                                   75, "")
        CONST_TBL_ENTRY(SIM_REFRESH_DYNAMIC_FLAGS2,                                   76, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PSC,                                              77, "Refresh Phonebook Syncronization Counter,EFpsc")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_CC,                                               78, "Refresh Change Counter, EFcc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PUID,                                             79, "Refresh Previous Unique Identifier, EFpuid")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ANR,                                              80, "Refresh Additional Number, EFanr.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_PBC,                                              81, "Refresh PhoneBook Control, EFpbc.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_EMAIL,                                            82, "Refresh e-mail address, EFemail.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_UID,                                              83, "Refresh Unique Identifier, EFuid.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_AAS,                                              84, "Refresh Additional number Alpha String,EFaas.")
        CONST_TBL_ENTRY(SIM_REFRESH_IMS_PRIVATE_USER_ID,                              85, "")
        CONST_TBL_ENTRY(SIM_REFRESH_IMS_PUBLIC_USER_ID,                               86, "")
        CONST_TBL_ENTRY(SIM_REFRESH_IMS_HOME_NW_DOMAIN_NAME,                          87, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_1,                      88, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_2,                      89, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_3,                      90, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_4,                      91, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_TAGS,                               92, "")
        CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_UHZIUE_SETTINGS,                    93, "")
        CONST_TBL_ENTRY(SIM_REFRESH_EQUIVALENT_HPLMNS,                                94, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_REFRESH_ACL,                                              95, "Refresh Access Point Name Control List, EFacl.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "GBA bootstrapping parameters.")
        CONST_TBL_ENTRY_VER(SIM_REFRESH_GBABP,                                        96, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "GBA NAF list.")
        CONST_TBL_ENTRY_VER(SIM_REFRESH_GBANL,                                        97, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "MBMS service keys list.")
        CONST_TBL_ENTRY_VER(SIM_REFRESH_MSK,                                          98, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "MBMS user key.")
        CONST_TBL_ENTRY_VER(SIM_REFRESH_MUK,                                          99, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    CONST_TBL_ENTRY_VER(SIM_REFRESH_ATT_RAT,                                      100, "017.006", "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Causes                                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_CAUSES_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_NO_CAUSE,                       1,       "")
        CONST_TBL_ENTRY(SIM_CAUSE_3V5V_CARD,                2,       "")
        CONST_TBL_ENTRY(SIM_CAUSE_5V_CARD,                  3,       "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Card generations to be used with SIM_SB_ICC_TYPE subblock              */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_2G_3G_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_2G_GSM,                         0, "")
        CONST_TBL_ENTRY(SIM_2G_WIM,                         1, "")
        CONST_TBL_ENTRY(SIM_2G,                             2, "")
        CONST_TBL_ENTRY(SIM_3G,                             3, "")
        CONST_TBL_ENTRY(SIM_ICC_TYPE_UNKNOWN,               4, "")
        CONST_TBL_ENTRY(SIM_2G_SWIM,                        5, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Card types to be used with SIM_SB_CARD_TYPE subblock                  */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_CARD_TYPE_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_NORMAL_SIM,                      0x00, "")
        CONST_TBL_ENTRY(SIM_TYPE_APPROVAL_SIM,               0x80, "")
        CONST_TBL_ENTRY(SIM_TEST_SIM,                        0x04, "")
        CONST_TBL_ENTRY(SIM_NORMAL_SIM_SPE_FACILITY,         0x01, "")
        CONST_TBL_ENTRY(SIM_TYPE_APPROVAL_SIM_SPE_FACILITY,  0x81, "")
        CONST_TBL_ENTRY(SIM_MAINTENANCE,                     0x02, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status                                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_STATUS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SERV_NOT_AVAIL,                  0x00, "")
        CONST_TBL_ENTRY(SIM_SERV_OK,                         0x01, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_REQUIRED,        0x02, "The requested PIN needs to be verified.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_REQUIRED,               0x03, "SIM card is protected by PIN code.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED,                0x04, "SIM card blocked. SIM card protected by PUK.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_SIM_PERMANENTLY_BLOCKED,    0x05, "SIM card cannot be unblocked anymmore.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_SIM_DISCONNECTED,           0x06, "SIM card disconnected/removed.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_SIM_REJECTED,               0x07, "SIM card rejected dur to communication error.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_LOCK_ACTIVE,                0x08, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_AUTOLOCK_CLOSED,            0x09, "Simlock accepts SIM card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_AUTOLOCK_ERROR,             0x0a, "Simlock did not accept SIM card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_INIT_OK,                    0x0b, "")
        CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK,                0x0c, "")
        CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN,              0x0d, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLED,               0x0e, "PIN code is disabled.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR,        0x0f, "Communication with card lost.")
        CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE,          0x10, "")
        CONST_TBL_ENTRY(SIM_SERV_NO_SECRET_CODE_IN_SIM,      0x11, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_ENABLE_OK,              0x12, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLE_OK,             0x13, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_WRONG_UNBLOCKING_KEY,       0x15, "Unblocking key send to (U)SIM is wrong.")
        CONST_TBL_ENTRY(SIM_SERV_ILLEGAL_NUMBER,             0x2e, "")
        CONST_TBL_ENTRY(SIM_SERV_NOT_OK,                     0x1c, "")
        CONST_TBL_ENTRY(SIM_SERV_PN_LIST_ENABLE_OK,          0x1e, "")
        CONST_TBL_ENTRY(SIM_SERV_PN_LIST_DISABLE_OK,         0x1f, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_NO_PIN,                     0x20, "The requeted PIN is not supported by the application.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_OK,              0x21, "PIN is verified with success.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_BLOCKED,                0x22, "PIN blocked. PUK required.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_PERM_BLOCKED,           0x23, "PIN permanently blocked.")
        CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL,             0x24, "")
        CONST_TBL_ENTRY(SIM_SERV_IN_HOME_ZONE,               0x25, "")
        CONST_TBL_ENTRY(SIM_SERV_STATE_CHANGED,              0x27, "")
        CONST_TBL_ENTRY(SIM_SERV_INF_NBR_READ_OK,            0x28, "")
        CONST_TBL_ENTRY(SIM_SERV_INF_NBR_READ_NOT_OK,        0x29, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_IMSI_EQUAL,                 0x2a, "IMSI is equal to previous IMSI")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_IMSI_NOT_EQUAL,             0x2b, "IMSI is NOT equal to previous IMSI")
        CONST_TBL_ENTRY(SIM_SERV_INVALID_LOCATION,           0x2c, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_STA_SIM_REMOVED,            0x35, "SIM card removed.")
        CONST_TBL_ENTRY(SIM_SERV_SECOND_SIM_REMOVED_CS,      0x36, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_CONNECTED_INDICATION_CS,    0x37, "(U)SIM card connected.")
        CONST_TBL_ENTRY(SIM_SERV_SECOND_SIM_CONNECTED_CS,    0x38, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_LOST_IND_CS,     0x39, "PIN code is wrong or not entered.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_GRANTED_IND_CS,  0x3a, "PIN code correct.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_INIT_OK_CS,                 0x3b, "Urgent CS data read.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK_CS,             0x3c, "Error occured.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_FDN_ENABLED,                     0x19, "FDN feature enabled.") 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_FDN_DISABLED,                    0x1a, "FDN feature disabled.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_INVALID_FILE,               0x45, "File defined by FileID is not an EF file, or not found on (U)SIM.")
        CONST_TBL_ENTRY(SIM_SERV_DATA_AVAIL,                 0x4F, "")        
        CONST_TBL_ENTRY(SIM_SERV_ICC_EQUAL,                  0x49, "")
        CONST_TBL_ENTRY(SIM_SERV_ICC_NOT_EQUAL,              0x4a, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_NOT_INITIALISED,        0x4B, "")               
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_SERVICE_NOT_AVAIL,          0X50, "Service is not available in Service Table.")
        CONST_TBL_ENTRY(SIM_SERV_FDN_STATUS_ERROR,           0x57, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_PASSED,           0x58, "Number(s) found in FDN list.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_FAILED,           0x59, "Number(s) not found in FDN list.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_DISABLED,         0x5A, "FDN feature is not enabled on (U)SIM.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_NO_FDN_SIM,       0x5B, "No FDN feature on (U)SIM.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ISIM_AVAILEBLE_PIN_REQUIRED, 0x5C, "An ISIM application was started up. PIN code verification is requiredbefore application can be used.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ISIM_AVAILEBLE,              0x5D, "An ISIM application was started up with succes and ready to be used.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_USIM_AVAILEBLE,              0x5E, "ISIM application was not available on UICC. USIM will be used to derive ISIM data and IMS authentication.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SIM_AVAILEBLE,               0x5f, "ISIM application was not available on UICC. SIM will be used to derive ISIM data and IMS authentication.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ISIM_NOT_INITIALIZED,        0x60, "ISIM application is not started up.")
        CONST_TBL_ENTRY(SIM_STA_IMS_READY,                   0x61, "")
        CONST_TBL_ENTRY(SIM_STA_APP_DATA_READ_OK,            0x96, "") 
        CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_OK,             0x97, "") 
        CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_NOT_OK,         0x98, "") 
        CONST_TBL_ENTRY(SIM_SERV_NOT_DEFINED,                0xF9, "") 
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                  0xfa, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                   0xfb, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                      0xfc, "")
/*        CONST_TBL_ENTRY(NO_STATUS_FROM_SUBSYSTEM,            0xff, "")*/
        CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_REQUIRED,     48, "")
        CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_NOT_REQUIRED, 49, "")
        CONST_TBL_ENTRY(SIM_SERV_FILE_NOT_AVAILABLE,         0x4D, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* SIMLOCK status                                                        */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SIMLOCK_STATUS_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	CONST_TBL_ENTRY(SIM_STA_SIMLOCK_OK,                     0x01, "SIMLOck accepts current (U)SIM card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTED,             0x08, "SIMLock reject the (U)SIM card")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTION_ON,         0x09, "SIMLock autolocked to current (U)SIM card")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTION_PENDING,    0x0A, "Not all autolocks could clos on the current (U)SIM card. "
								      "SIMLock rejects the card.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SIMLOCK_STATUS_NOT_INITIALIZED, 0x24, "SIMLock validation not completed yet.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_NOSERVICE,                      0xFA, "")
        CONST_TBL_ENTRY(SIM_STA_NOTREADY,                       0xFB, "")
        CONST_TBL_ENTRY(SIM_STA_ERROR,                          0xFC, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Phonebook status                                                      */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_PB_STATUS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SERV_NOT_AVAIL,                  0x00, "")
        CONST_TBL_ENTRY(SIM_SERV_OK,                         0x01, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_REQUIRED,        0x02, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_REQUIRED,               0x03, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED,                0x04, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_PERMANENTLY_BLOCKED,    0x05, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_DISCONNECTED,           0x06, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_REJECTED,               0x07, "")
        CONST_TBL_ENTRY(SIM_SERV_LOCK_ACTIVE,                0x08, "")
        CONST_TBL_ENTRY(SIM_SERV_AUTOLOCK_CLOSED,            0x09, "")
        CONST_TBL_ENTRY(SIM_SERV_AUTOLOCK_ERROR,             0x0a, "")
        CONST_TBL_ENTRY(SIM_SERV_INIT_OK,                    0x0b, "")
        CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK,                0x0c, "")
        CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN,              0x0d, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLED,               0x0e, "")
        CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR,        0x0f, "")
        CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE,          0x10, "")
        CONST_TBL_ENTRY(SIM_SERV_NO_SECRET_CODE_IN_SIM,      0x11, "")
        CONST_TBL_ENTRY(SIM_SERV_NO_FREE_LOCATIONS,          0x12, "")
        CONST_TBL_ENTRY(SIM_SERV_WRONG_UNBLOCKING_KEY,       0x15, "")
        CONST_TBL_ENTRY(SIM_SERV_NO_MATCH,                   0x16, "")
        CONST_TBL_ENTRY(SIM_SERV_ILLEGAL_NUMBER,             0x2e, "")
        CONST_TBL_ENTRY(SIM_SERV_NOT_OK,                     0x1c, "")
        CONST_TBL_ENTRY(SIM_SERV_PN_LIST_ENABLE_OK,          0x1e, "")
        CONST_TBL_ENTRY(SIM_SERV_PN_LIST_DISABLE_OK,         0x1f, "")
        CONST_TBL_ENTRY(SIM_SERV_NO_PIN,                     0x20, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_OK,              0x21, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_BLOCKED,                0x22, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_PERM_BLOCKED,           0x23, "")
        CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL,             0x24, "")
        CONST_TBL_ENTRY(SIM_SERV_IN_HOME_ZONE,               0x25, "")
        CONST_TBL_ENTRY(SIM_SERV_STATE_CHANGED,              0x27, "")
        CONST_TBL_ENTRY(SIM_SERV_INF_NBR_READ_OK,            0x28, "")
        CONST_TBL_ENTRY(SIM_SERV_INF_NBR_READ_NOT_OK,        0x29, "")
        CONST_TBL_ENTRY(SIM_SERV_IMSI_EQUAL,                 0x2a, "")
        CONST_TBL_ENTRY(SIM_SERV_IMSI_NOT_EQUAL,             0x2b, "")
        CONST_TBL_ENTRY(SIM_SERV_INVALID_LOCATION,           0x2c, "")
        CONST_TBL_ENTRY(SIM_SERV_NAME_TOO_LONG,              0x32, "")

        CONST_TBL_ENTRY(SIM_SERV_SRES_ERROR,                 0x34, "")
        CONST_TBL_ENTRY(SIM_SERV_STA_SIM_REMOVED,            0x35, "")
        CONST_TBL_ENTRY(SIM_SERV_SECOND_SIM_REMOVED_CS,      0x36, "")
        CONST_TBL_ENTRY(SIM_SERV_CONNECTED_INDICATION_CS,    0x37, "")
        CONST_TBL_ENTRY(SIM_SERV_SECOND_SIM_CONNECTED_CS,    0x38, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_LOST_IND_CS,     0x39, "")
        CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_GRANTED_IND_CS,  0x3a, "")
        CONST_TBL_ENTRY(SIM_SERV_INIT_OK_CS,                 0x3b, "")
        CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK_CS,             0x3c, "")
        CONST_TBL_ENTRY(SIM_FDN_ENABLED,                     0X19, "") 
        CONST_TBL_ENTRY(SIM_FDN_DISABLED,                    0X1a, "")

        CONST_TBL_ENTRY(SIM_SERV_INVALID_FILE,               0x45, "")                
        
        CONST_TBL_ENTRY(SIM_SERV_ICC_EQUAL,                  0x49, "")
        CONST_TBL_ENTRY(SIM_SERV_ICC_NOT_EQUAL,              0x4a, "")
        CONST_TBL_ENTRY(SIM_SERV_SIM_NOT_INITIALISED,        0x4B, "")               
        CONST_TBL_ENTRY(SIM_SERV_ILLEGAL_LENGTH,             0x4C, "")               
        CONST_TBL_ENTRY(SIM_SERV_INIT_OK_TDMA_CS,            0x4E, "")               
        CONST_TBL_ENTRY(SIM_SERV_NUMBER_TOO_LONG,            0x4F, "")               

        CONST_TBL_ENTRY(SIM_SERV_SERVICE_NOT_AVAIL,          0x50, "")

        CONST_TBL_ENTRY(SIM_SERV_AAS_TOO_LONG,               0x51, "")
        CONST_TBL_ENTRY(SIM_SERV_ANR_TOO_LONG,               0x52, "")
        CONST_TBL_ENTRY(SIM_SERV_GAS_APLPHA_STRING_TOO_LONG, 0x53, "")
        CONST_TBL_ENTRY(SIM_SERV_ILLEGAL_CCP1_VALUE,         0x54, "")

        CONST_TBL_ENTRY(SIM_SERV_CC_COUNTER_HAS_WRAPPED,     0x55, "")
        CONST_TBL_ENTRY(SIM_SERV_PSC_COUNTER_HAS_WRAPPED,    0x56, "")

        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_PASSED,           0x58, "")
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_FAILED,           0x59, "")
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_DISABLED,         0x5A, "")
        CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_NO_FDN_SIM,       0x5B, "")

        CONST_TBL_ENTRY(SIM_STA_APP_DATA_READ_OK,            0x96, "") 
        CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_OK,             0x97, "") 
        CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_NOT_OK,         0x98, "") 

        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                  0xfa, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                   0xfb, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                      0xfc, "")
/*        CONST_TBL_ENTRY(NO_STATUS_FROM_SUBSYSTEM,            0xff, "")*/

        CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_REQUIRED,     48, "")
        CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_NOT_REQUIRED, 49, "")

        CONST_TBL_ENTRY(SIM_SERV_FILE_NOT_AVAILABLE,         0x4D, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Subblock status                                                       */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SB_STA_TABLE,8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SB_STA_OK,                    1, "")
        CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK,              2, "")
        CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL,      3, "")
        CONST_TBL_ENTRY(SIM_SB_STA_UNKNOWN_SB_ID,       4, "")
        CONST_TBL_ENTRY(SIM_SB_STA_3G_GSM_NOT_SUPPORTED,5, "")
        CONST_TBL_ENTRY(SIM_SB_STA_SYNCH_FAIL,          6, "")
        CONST_TBL_ENTRY(SIM_SB_STA_MAC_FAIL,            7, "")
        CONST_TBL_ENTRY(SIM_SB_STA_PS_NOT_SUPPORTED,    8, "")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,             0xfa, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,              0xfb, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                 0xfc, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status                                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_STA_TABLE, 8 ,  BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_OK,                             0x01, "Data available.")
        CONST_TBL_ENTRY(SIM_STA_UPDATE_IMPOSSIBLE,                16, "")
        CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE,             0x14, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_NOT_OK,                         0x1C, "An error has occurred. No details available.")
        CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAILABLE,               36, "")
        CONST_TBL_ENTRY(SIM_STA_EQUAL,                            42, "")
        CONST_TBL_ENTRY(SIM_STA_NOT_EQUAL,                        43, "")
        CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION,               0x2C, "")
        CONST_TBL_ENTRY(SIM_STA_LOCATION_EMPTY,                 0x2D, "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_SB_NOT_OK,                        75, "An error occurred in returned sub-block(s).")
        CONST_TBL_ENTRY(SIM_STA_ILLEGAL_LENGTH,                   76, "")
        CONST_TBL_ENTRY(SIM_STA_SERVICE_NOT_AVAIL,                80, "")
        CONST_TBL_ENTRY(SIM_STA_NOSERVICE,                      0xfa, "")
        CONST_TBL_ENTRY(SIM_STA_NOTREADY,                       0xfb, "")
        CONST_TBL_ENTRY(SIM_STA_ERROR,                          0xfc, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* HomeZone status                                                       */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_HZ_STATUS_TABLE, 8 ,  BE, "", "")
        CONST_TBL_ENTRY(SIM_STA_OK,                             0x01, "")
        CONST_TBL_ENTRY(SIM_STA_NOT_OK,                         0x1C, "")
        CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAIL,                 0x24, "")
        CONST_TBL_ENTRY(SIM_STA_NOSERVICE,                      0xFA, "")
        CONST_TBL_ENTRY(SIM_STA_NOTREADY,                       0xFB, "")
        CONST_TBL_ENTRY(SIM_STA_ERROR,                          0xFC, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* SIM_SERV_STA                                                          */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SERV_STA_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SERV_STA_OK,                   1,  "")
        CONST_TBL_ENTRY(SIM_SERV_STA_UPDATE_IMPOSSIBLE,    0x10,  "")
        CONST_TBL_ENTRY(SIM_SERV_STA_DATA_NOT_AVAILABLE,   0x24,  "")
        CONST_TBL_ENTRY(SIM_SERV_STA_NOT_OK,               28, "")
        CONST_TBL_ENTRY(SIM_SERV_STA_AID_NOT_ACTIVE,       29, "")
        CONST_TBL_ENTRY(SIM_SERV_STA_SB_NOT_OK,            75, "") /*SIM_STA_SB_NOT_OK*/
        CONST_TBL_ENTRY(SIM_SERV_STA_SIM_REMOVED,          53, "")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                0xfa, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                 0xfb, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                    0xfc, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status for SMS                                                        */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SMS")
    CONST_TBL_BEGIN(SIM_STATUS_SMS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_STA_OK,                        1, "")
        CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE,        20, "")
        CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION,          44, "")
        CONST_TBL_ENTRY(SIM_STA_LOCATION_EMPTY,            45, "")
        CONST_TBL_ENTRY(SIM_STA_NOT_OK,                    28, "")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                0xfa, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                 0xfb, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                    0xfc, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status for SMS messages                                               */
    /* --------------------------------------------------------------------- */

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SMS_MSG_STATUS_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_FREE_SPACE,                     0x00, "SMS Location is free.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_REC_F_NETWORK_READ,             0x01, "Message received by UE from network, message read")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_REC_F_NETWORK_TO_BE_READ,       0x03, "Message received by UE from network, message to be read")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_UE_ORG_TO_BE_SEND,              0x07, "UE originating message, message to be send")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_UE_ORG_NO_STATUS_REPORT,        0x05, "UE originating message, Status report not requested")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_UE_ORG_STATUS_REPORT_REQ,       0x0D, "UE originating message, Status report requested but (yet) received")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SMS_UE_ORG_STATUS_REP_REC_NO_SMSR,  0x15, "UE originating message, Status report received but not stored in EF-SMSR")        
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status for refresh                                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_STATUS_REFRESH_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_STA_OK,                        0x01, "")
        CONST_TBL_ENTRY(SIM_STA_NOT_OK,                    0x1C, "")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                0xFA, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                 0xFB, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                    0xFC, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status for MMS                                                        */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_STATUS_MMS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_STA_OK,                        0x01, "OK")
        CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAILABLE,        0x24, "No valid data in EF file.")
        COMMENT(COMMENT_TEXT, "EF file is not available on (U)SIM or service no. 52 'Multimedia Messaging Service (MMS)' "
                               "is not active in the Service Table.")        
	CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE,        0x14, "")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                0xFA, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                 0xFB, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                    0xFC, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Flags for HomeZone                                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    BIT_TBL_BEGIN(SIM_HZCZ_ACTIVE_FLAG, 8, BE, "001.000", "")
        COMMENT(COMMENT_TEXT, "Home zone is active.")    
        BIT_TBL_ENTRY("xxxxxxx1", SIM_HOMEZONE_ACTIVE, "")
        COMMENT(COMMENT_TEXT, "Home zone is not active.")    
        BIT_TBL_ENTRY("xxxxxxx0", SIM_HOMEZONE_NOT_ACTIVE, "")
        COMMENT(COMMENT_TEXT, "City zone is active.")    
        BIT_TBL_ENTRY("xxxxxx1x", SIM_CITYZONE_ACTIVE, "")
        COMMENT(COMMENT_TEXT, "City zone is not active.")    
        BIT_TBL_ENTRY("xxxxxx0x", SIM_CITYZONE_NOT_ACTIVE, "")
    BIT_TBL_END

    /* --------------------------------------------------------------------- */
    /* ??????????????????                                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SB_CS_WRITE_RESP_SB_ID_DEFINES_TABLE, 16, BE, "", "")
        CONST_TBL_ENTRY(SIM_SB_TMSI_ID,                        116, "")
        CONST_TBL_ENTRY(SIM_SB_BCCH_ID,                        101, "")
        CONST_TBL_ENTRY(SIM_SB_LAI_ID,                         115, "")
        CONST_TBL_ENTRY(SIM_SB_LOC_UPD_STATUS_ID,              126, "")
        CONST_TBL_ENTRY(SIM_SB_GSM_NETPAR_ID,                  135, "")
        CONST_TBL_ENTRY(SIM_SB_FDD_NETPAR_ID,                  136, "")
        CONST_TBL_ENTRY(SIM_SB_TDD_NETPAR_ID,                  137, "")
        CONST_TBL_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID,             105, "")

        CONST_TBL_ENTRY(SIM_SB_USER_PLMN_ID,                   128, "")
        CONST_TBL_ENTRY(SIM_SB_PLMN_SELECTOR_ID,               132, "")
        CONST_TBL_ENTRY(SIM_SB_RPLMN_ID,                       130, "")
        CONST_TBL_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID,      107, "")
        CONST_TBL_ENTRY(SIM_SB_GPRS_RAI_ID,                    108, "")
        CONST_TBL_ENTRY(SIM_SB_GPRS_RAUS_ID,                   109, "")
        CONST_TBL_ENTRY(SIM_SB_GPRS_TMSI_ID,                   110, "")
        CONST_TBL_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID,        111, "")
        CONST_TBL_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID,           104, "")

        CONST_TBL_ENTRY(SIM_SB_UMTS_CS_KSI_ID,                 117, "")
        CONST_TBL_ENTRY(SIM_SB_UMTS_PS_KSI_ID,                 120, "")
        CONST_TBL_ENTRY(SIM_SB_UMTS_START_PS_ID,               123, "")
        CONST_TBL_ENTRY(SIM_SB_UMTS_START_CS_ID,               125, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Applilcation selection types                                          */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SB_APP_SELECTION_TYPE_DEF_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_USIM_APPLICATION,           0x01, "")
        CONST_TBL_ENTRY(SIM_ISIM_APPLICATION,           0x02, "")
        CONST_TBL_ENTRY(SIM_UNKNOWN_APPLICATION,        0xFF, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* SIM conditions                                                        */
    /* --------------------------------------------------------------------- */

    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_CONDITION_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(NOT_PROTECTED,                        1, "EF is not protected by PIN or PIN2")
        CONST_TBL_ENTRY(PROTECTED_BY_PIN1,                    2, "EF is protected by PIN.")
        CONST_TBL_ENTRY(PROTECTED_BY_PIN2,                    3, "EF is protected by PIN2.")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Service Types for SIM_GPRS_REQ                                        */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Service types for SIM_GPRS_REQ")
    CONST_TBL_BEGIN(SIM_GPRS_REQ_ST_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_ST_ACL_STATUS,                           118, "")
        CONST_TBL_ENTRY(SIM_ST_ACL_ENABLE,                           119, "")
        CONST_TBL_ENTRY(SIM_ST_ACL_DISABLE,                          120, "")
        CONST_TBL_ENTRY(SIM_ST_ACL_READ,                             121, "")
        CONST_TBL_ENTRY(SIM_ST_ACL_WRITE,                            122, "")
        CONST_TBL_ENTRY_VER(SIM_ST_CHECK_APN,                        123, "", "020.000")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Status for SIM_GPRS_REQ                                               */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_GPRS_REQ_STATUS_TABLE, 8, BE, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ACL_ENABLED,                         105, "ACL feature is enabled in service table, EFust")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ACL_DISABLED,                        106, "ACL feature is disabled in service table, EFust")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_APN_CHECK_PASSED,                    107, "The APN is in the EFacl file.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_APN_CHECK_FAILED,                    108, "The APN is not in the EFacl file.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE,                   110, "ACL feature is not activated on USIM, i.e. meaning that card	does not support ACL.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL,                     0x24, "Information is not available e.g. due to loss of contact to	card")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_SERV_OK,                                 0x01, "Result is OK")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        CONST_TBL_ENTRY(SIM_STA_ILLEGAL_LENGTH,                      76, "The length of data has exceeded the Max Data Space returned in SIM_GPRS_RESP(SIM_ACL_READ_REQ)")
        CONST_TBL_ENTRY(SIM_SERV_NOSERVICE,                          0xFA, "")
        CONST_TBL_ENTRY(SIM_SERV_NOTREADY,                           0xFB, "")
        CONST_TBL_ENTRY(SIM_SERV_ERROR,                              0xFC, "")
    CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* Misc Status - table 1                                                 */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(MISC_STATUS_TABLE_1, 8, BE, "", "")
        CONST_TBL_ENTRY(SIM_SERV_STATUS_END,                         0xFF, "")
        CONST_TBL_ENTRY(SIM_SERV_TEXT_TOO_LONG,                      0x4E, "")
        CONST_TBL_ENTRY(SIM_SERV_ACM_MAX_VALUE_REACHED,              0x19, "")
    CONST_TBL_END

	/* --------------------------------------------------------------------- */
    /* SIM_MISC_ST_TABLE - deprecated values                                 */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Constant Table: SIM_MISC_ST_TABLE - deprecated values                   */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

/*    These constants are already defined. */
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define ADN                                      0x07")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define FDN                                      0x09")
 
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MSISDN                                   0x6D")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define PIN_UNIVERSAL                            0x97")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_AOC_AVAIL                            0x71")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_CALL_CONTROL_AVAIL                   0x74")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FDN_AVAIL                            0x72")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SMS_CB_DATA_DOWNLOAD_AVAIL           0x73")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ST_ACM                               0x10")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ST_SERVICE_TABLE                     0x11")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ST_SMS                               0x0F")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_ST_10                           0x0A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_ST_6                            0x06")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_ST_8                            0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_STA_RUIM_OFF                         0x66") /* RUIM to be removed ASAP */
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ST_RUIM_OPERATIONAL_MODE             0x02") /* RUIM to be removed ASAP */

    /* --------------------------------------------------------------------- */
    /* Misc status - table 2                                                 */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Constant Table: Misc status - table 2                                   */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_FILE_NOT_AVAIL                  0x14")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_FILE_NOT_ON_CARD                0x15")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_ILLEGAL_COMBINATION             0x18")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_LOC_NOT_VALID                   SIM_STA_INVALID_LOCATION")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_LOC_OUT_OF_RANGE                0x11")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_NUMBER_NOT_READABLE             0x17")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_SIM_REMOVED_CS                  0x35")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_SNE_TOO_LONG                    0x50")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_SIMLOCK_RESTRICTED              0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_SIMLOCK_RESTRICTION_ON          0x09")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_SIMLOCK_RESTRICTION_PENDING     0x0A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_STA_IMSI_EQUAL                       0x2A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_STA_IMSI_NOT_EQUAL                   0x2B")

    /* --------------------------------------------------------------------- */
    /* Misc constants                                                        */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Constant Table: Misc constants                                          */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define HML_SIM                                  0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_CURR_CHOICE                      0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_DOWN_CHOICE                      0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_ISROAMING_MASK                   0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_NAME_LENGTH                      0x1E")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_NEXT_CHOICE                      0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_NO_CHOICE                        0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_NUMBER_LENGTH                    0x0F")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_PREV_CHOICE                      0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define INFONUM_UP_CHOICE                        0x10")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_CSL_CNT                             0x100")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_NAME_LEN                   PR_NAME_LENGTH")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_NAM_P_RSID_CNT                       0x05")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_NUM_BHT_CNT                          0x78")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_NUM_DHT_CNT                          0x2A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_NUM_LEN                  PR_NUMBER_LENGTH")    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_REG_ACCEPT_P_RSID_CNT                0x05")    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_TEST_R_P_RSID_CNT                    0x05")    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define MAX_USER_GROUP_CNT                       0x08")    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define OPERATOR_CONTROLLED_PLMNS                0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define PHASE_1_SIM                              0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define PHASE_2_SIM                              0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define PHASE_NORMAL_SIM                         0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define PREPAID_SIM                              0x07")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RENTAL_SIM                               0x06")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_BLOCK_TYPE_ISI                       0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_BLOCK_TYPE_MSG                       0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FDN_CHECK_SB_END                     0x00B7")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FDN_CHECK_SB_START                   0xB4")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FILE_TYPE_1                          0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FILE_TYPE_2                          0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FILE_TYPE_3                          0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_IMSI_DFIELD_LEN                         9")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_LSA_DESC_FILE_ID_LEN                 0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MAX_ECC_LEN                          0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MAX_ECC_TYPE_INDICATOR_LEN           0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MBDN_EMAIL                           0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MBDN_FAX                             0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MBDN_OTHER                           0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_MBDN_VOICEMAIL                       0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_NAME_LEN             (PR_NAME_LENGTH + 1)")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_NO_ECC_ALPHA_IDENTIFIER              0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_NUMBER_LEN         (PR_NUMBER_LENGTH + 1)")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ONE_PLMN_LEN                            3")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_COMMIT_RESP_RESULT_CODE          0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_CONFIG_REQ_BLOCK_ID              0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_CONFIG_RESP_BLOCK_ID             0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_CONFIG_RESP_BLOCK_LEN            0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_CONFIG_RESP_PARAM_DATA           0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_CONFIG_RESP_RESULT_CODE          0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_DOWNLOAD_REQ_BLOCK_ID            0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_DOWNLOAD_REQ_BLOCK_LEN           0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_DOWNLOAD_REQ_PARAM_DATA          0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_DOWNLOAD_RESP_BLOCK_ID           0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_DOWNLOAD_RESP_RESULT_CODE        0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_KEY_GENERATION_REQ_BS_RESULT     0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_KEY_GENERATION_REQ_BS_RESULT_LEN 0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_KEY_GENERATION_RESP_MS_RESULT    0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_KEY_GENERATION_RESP_MS_RESULT_LEN 0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_KEY_GENERATION_RESP_RESULT_CODE  0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_A_KEY_PROTOCOL_REV    0x14")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_PARAM_G               0x57")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_PARAM_G_LEN           0x16")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_PARAM_P               0x17")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_PARAM_P_LEN           0x15")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_REQ_RAND_SEED             0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_MS_KEY_RESP_RESULT_CODE          0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_RAND_SEED_LEN              0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_REQ_RAND_SEED              0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_REQ_START_STOP             0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_RESP_NAM_LOCK_IND          0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_RESP_RAND_OTAPA            0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_OTAPA_RESP_RESULT_CODE           0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SESSION_END_NO_COMMIT            0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SESSION_END_WITH_COMMIT          0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SESSION_START                    0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_REQ_BLOCK_ID         0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_REQ_REQUEST_MAX_SIZE 0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_REQ_REQUEST_OFFSET   0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_RESP_BLOCK_ID        0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_RESP_BLOCK_LEN       0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_RESP_PARAM_DATA      0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_CONFIG_RESP_RESULT_CODE     0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_REQ_BLOCK_ID       0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_REQ_BLOCK_LEN      0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_REQ_PARAM_DATA     0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_RESP_BLOCK_ID      0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_RESP_RESULT_CODE   0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_RESP_SEGMENT_OFFSET 0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_SSPR_DOWNLOAD_RESP_SEGMENT_SIZE  0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_VALIDATE_REQ_BLOCK_ID            0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_VALIDATE_REQ_BLOCK_LEN           0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_VALIDATE_REQ_PARAM_DATA          0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_VALIDATE_RESP_BLOCK_ID           0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_OTA_VALIDATE_RESP_RESULT_CODE        0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_2G                                0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_3G                                0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_ACTIVE                            0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_FIRST                           0xFFFF")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_LOCATION_ANY                    0xFFFE")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_NOT_ACTIVE                        0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PTMSI_LEN                            0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PTMSI_SIG_VAL_LEN                    0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_REFRESH_CUSTOMER_SERVICE_PROFILE     0x1B")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_REFRESH_LAST_FILE_ID                 SIM_REFRESH_ATT_RAT")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_RES_FAC_SET_REQ                      0x5E")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_RES_FAC_SET_RESP                     0x5F")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ACCESS_OVERLOAD_CLASS             0x02")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ADDITIONAL_USER_REGISTRATION_PARAMETERS 0x1F")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ADDRESS                           0x22")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ALPHA_ID                          0x23")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ALPHA_TAGS                        0x0A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_AMPS_USAGE_INDICATORS             0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ANSI_136_USAGE_INDICATORS         0x09")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_AUT_END                         0x0130")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_AUT_START                        0x12C")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_BAND_AND_SUB_BAND_PRIORITY_ORDER  0x14")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_BAND_HISTORY_TABLE                0x1D")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_BC_REPEAT_INDICATOR               0x24")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_COOPERATIVE_SOC_LIST              0x0B")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_CPHS_START                      0x01A4")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_CS_START                          0x64")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_DCCH_HISTORY_TABLE                0x1E")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_EAP_START                       0x01CC")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ECC_HEADER_LEN                    0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ECC_RECORD_HEADER_LEN             0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_FAVORED_SOC_LIST                  0x11")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_FORBIDDEN_SOC_LIST                0x12")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_GROUP_ID                          0x06")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_GSM_ANSI_136_SIM_PHASE_ID         0x1B")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_GSM_RECONNECT_TIMER               0x2B")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_HOME_SYSTEM_OPERATOR_CODE_AND_MOBILE_COUNTRY_CODE 0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_ICC_START                       0x0190")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_IMS_START                       0x01B8")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_INITIAL_PAGING_CHANNEL            0x05")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_IRDB_PARAMETER                    0x13")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_IRDB_VERSION_TABLE                0x0C")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_LOCATION_INFORMATION              0x27")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_MMS_START                       0x01AE")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_MOBILE_IDENTIFICATION_NUMBER      0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_NAM_PSIDS_AND_RSIDS               0x15")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_NEGATIVE_FORBIDDEN_SID_LIST       0x0F")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_PARTNER_SID_LIST                  0x0D")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_PARTNER_SOC_LIST                  0x10")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_PLMN_RECORD_LEN                   0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_PLMN_SEL_HEADER_LEN               0x08")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_POSITIVE_FAVORED_SID_LIST         0x0E")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_REGISTRATION_THRESHOLD            0x1A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_REG_ACCEPT_PSIDS_AND_RSIDS        0x17")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SIM_ELECTRONIC_SERIAL_NUMBER      0x07")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SMS_START                       0x015E")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SOC_DEPERSONALIZATION_CONTROL_KEY 0x21")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SS_FEATURE_CODE_TABLE             0x18")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SS_STRING                         0x28")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SUBADDRESS                        0x29")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_SYSTEM_ID                         0x03")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_TELESERVICE_SERVER_ADDRESS_INFO   0x1C")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_TEST_REGISTRATION_PSIDS_AND_RSIDS 0x16")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_TRIGGERED_SCAN_TIMERS             0x19")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_USER_GROUP_ID_INFO                0x20")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SB_USSD_STRING                       0x2A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_PROV_NAME_LEN                     16")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_TABLE_END                            0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_TEXT_LEN             (PR_TEXT_LENGTH + 1)")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SMS_ALPHA_TAG_MAX_LENGTH                   16")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define STATE_RESERVED                           0x00")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define STATE_SIM_ANY_STATE                      0x09")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define STATE_SIM_SAME_STATE                     0x0A")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define TEST_SIM                                 0x05")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define TYPE_APPROVAL_SIM                        0x04")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define USER_CONTROLLED_PLMNS                    0x01")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PB_SB_START                          0xC8")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PUCT_CURRENCY_CODE_LEN              (3+1)")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PRIMARY_LINE                            0")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ALTERNATE_LINE                          1")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_ALL_LINES                               2")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_FILE_PATH_LEN                           8")
	COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SMS_ADDRESS_MAX_LENGTH                     12")



    /* --------------------------------------------------------------------- */
    /* Message ID's - deprecated values                                      */
    /* --------------------------------------------------------------------- */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Constant Table: Message ID's - deprecated values                        */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_240                      0xF0")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_241                      0xF1")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_242                      0xF2")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_243                      0xF3")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_244                      0xF4")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_245                      0xF5")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_246                      0xF6")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_247                      0xF7")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_248                      0xF8")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_249                      0xF9")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_250                      0xFA")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_251                      0xFB")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_252                      0xFC")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_253                      0xFD")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_254                      0xFE")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define RESERVED_MSG_ID_255                      0xFF")
/*DSS*/
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PN_LIST_STATUS_REQ                   0x58")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PN_LIST_STATUS_RESP                  0x59")
    /* --------------------------------------------------------------------- */
    /* Sequences                                                             */ 
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CARD_TYPE, CREATE_STRUCT, "", "")
        VALUE(8, BE, normal_or_type_approval, "normal or type approval", HEX)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_EMRG_CALL_CODE_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_EMRG_CALL_CODE_STR, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_TEXT,"Format of 6 digit ECC string: ECC digit1, ECC digit2, ECC digit3, ECC digit4, ECC digit5, ECC digit6 , NULL")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, emrg_call_code, "Emrg call code", 2 * SIM_ONE_EMRG_CALL_CODE_LEN + 1)
        FILLER_EX(padding, 8, 1)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_EMRG_CALL_CODES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_EMRG_CALL_CODES_STR, CREATE_STRUCT, "", "")
        SEQ_OF(emrg_call_codes, "emrg_call_codes", SIM_EMRG_CALL_CODE_STR, SIM_MAX_NBR_OF_EMRG_CALL_CODES)
    SEQ_END 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ChangeCode")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(CHANGE_CODE, CREATE_STRUCT, "", "")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, OldPword, "Old Password", MAX_CODE_LEN)        
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, NewPword, "New Password", MAX_CODE_LEN)
    SEQ_END
        
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_UnblockCode")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(UNBLOCK_CODE, CREATE_STRUCT, "", "")    
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, UnblockKey, "Unblock Key", MAX_CODE_LEN)                
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Password, "Password", MAX_CODE_LEN)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ServiceProvider")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SERVICE_PROVIDER, CREATE_STRUCT, "", "")
        COMMENT(COMMENT_PARAGRAPH, "Unicode - zero terminated")
        STRING(STRING_UNICODE, BE, serv_prov_name, "serv prov name", SIM_SERV_PROV_NAME_LEN + 1)

        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "If 0: display of registered PLMN name not required when registered PLMN"
	                      " is either HPLMN or a PLMN in the service provider PLMN list.")
        COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "If 1: display of registered PLMN name required when registered PLMN is either HPLMN"
	                      " or a PLMN in the service provider PLMN list.")	      
	VALUE(8, BE, display_condition, "display condition", DEC)

        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "If 0: display of the service provider name is required when registered PLMN"
	                      " is neither HPLMN nor a PLMN in the service provider PLMN list.")
        COMMENT(COMMENT_PARAGRAPH, "      ")
        COMMENT(COMMENT_TEXT, "If 1: display of the service provider name is not required when registered PLMN is"
	                      " neither HPLMN nor a PLMN in the service provider PLMN list.")
        VALUE(8, BE, display_con_not_in_hplmn_or_spdi, "display condition when not in hplmn or spdi", DEC)	
    SEQ_END

/* tVoiceMsg_Optionals */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tVoiceMsg_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_VOICE_MSG_OPTIONAL_DATA, CREATE_STRUCT, "013.000", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Coding:")	
        COMMENT(COMMENT_NEWLINE, "")	
        COMMENT(COMMENT_BULLET, "0:Fax data is not valid.")	
        COMMENT(COMMENT_NEWLINE, "")	
        COMMENT(COMMENT_BULLET, "1:Fax data is valid.")
	VALUE(8, BE, FaxData, "FaxData", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tVoiceMsg_Optionals;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tVoiceMsg_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_VOICE_MSG_OPTIONAL_DATA, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf FaxData:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf RFU:7;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, FaxData, "FaxData")
            VALUE(1, BE, FaxData, "FaxData", HEX)
            VALUE(7, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*SIM_SERV_VOICE_MSG_WAIT_FLAG_STR*/
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_VOICE_MSG_WAIT_FLAG_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_VOICE_MSG_WAIT_FLAG, CREATE_STRUCT, "013.000", "")
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "If message waiting: 0x0A.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If no message waiting: 0x05.")
        VALUE(8, BE, prim_line, "prim_line", DEC)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Do")
        VALUE(8, BE, alt_line, "alt_line", DEC)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Do, if valid.")
        VALUE(8, BE, fax, "fax", DEC)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Do, if valid.")
        VALUE(8, BE, data, "data", DEC)        
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_VOICE_MSG_WAIT_FLAG_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_VOICE_MSG_WAIT_FLAG_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_VOICE_MSG_WAIT_FLAG, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf prim_line:4;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf alt_line:4;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf fax:4;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf data:4;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(16, BE, MsgFlags, "MsgFlags")
            VALUE(4, BE, prim_line, "prim_line", HEX)
            VALUE(4, BE, alt_line, "alt_line", HEX)
            VALUE(4, BE, fax, "fax", HEX)
            VALUE(4, BE, data, "data", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CF_FLAGS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CALL_FWD_FLAG, CREATE_STRUCT, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x05: No Call Forwarding messages are waiting.")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "0x0A: Call Forwarding Unconditional is active.")
        VALUE(8, BE, prim_line, "prim_line", DEC)
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x05: No Call Forwarding messages are waiting.")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "0x0A: Call Forwarding Unconditional is active.")
        VALUE(8, BE, alt_line, "alt_line", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Sequence: SIM_SB_ECC_RECORD                                             */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct tSIM_SB_ECC_RECORD")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Ecc1;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Ecc2;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Ecc3;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccTypeIndicator;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    /* First byte of field and any padding bytes */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccAlphaIdentifier;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_SB_ECC_RECORD;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_VIAG_Hemozone_element")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_VIAG_HOME_ZONE_SEQ, CREATE_STRUCT, "001.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "See VIAG HomeZone SMS specification.")
        VALUE(32, BE, Zone_X, "Zone X", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "See VIAG HomeZone SMS specification.")
        VALUE(32, BE, Zone_Y, "Zone Y", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "See VIAG HomeZone SMS specification.")
        VALUE(32, BE, Zone_R2, "Zone R2", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "See VIAG HomeZone SMS specification.")
        VALUE(8, BE, HomeZoneId, "HomeZoneId", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	/*VALUE(8, BE, HzCzActiveFlag, "HzCzActiveFlag", DEC)*/
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Active zone indicator.")
        VALUE_CONST(HzCzActiveFlag, "HzCzActiveFlag", SIM_HZCZ_ACTIVE_FLAG)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Name of zone. UCS2 format and zero terminated.")
        SEQ_OF(HzCzTag, "HzCzTag", AUTOGEN_SEQ_WORD_HEX, 13)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/*  Remember that a bitfield version also exists in sim_isi_common_str.h but this is not used anymore */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_DYNAMIC_FLAGS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_INFO_DYNAMIC_FLAGS_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "0: Alternate line.")
        COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_BULLET, "1: Primary line.")
	VALUE(8, BE, selected_line, "selected_line", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "0: Calling Line Identity presentation, restricted.")
        COMMENT(COMMENT_NEWLINE, "")	
	COMMENT(COMMENT_BULLET, "1: Calling Line Identity presentation, presented.")
	VALUE(8, BE, clir_flag, "clir_flag", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
    SEQ_END

/*  SIM_DYNAMIC_FLAGS */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_DYNAMIC_FLAGS")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_DYNAMIC_FLAGS, CREATE_STRUCT, "001.000", "")
    VALUE(8, BE, line, "line", DEC)
    VALUE(8, BE, clir_flag, "clir flag", DEC)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_DYNAMIC2_FLAGS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_INFO_DYNAMIC2_FLAGS_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Coding:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0: ALS is not locked.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "1: ALS is locked.")
        VALUE(8, BE, als_status, "als_status", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

/* SIM_DYNAMIC2_FLAGS */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_DYNAMIC2_FLAGS")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_DYNAMIC2_FLAGS, CREATE_STRUCT, "001.000", "")
    VALUE(8, BE, als_status, "als status", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_ECC_RECORD, CREATE_STRUCT, "012.000", "")
        VALUE(8, BE, Ecc1, "Ecc1", DEC)
        VALUE(8, BE, Ecc2, "Ecc2", DEC)
        VALUE(8, BE, Ecc3, "Ecc3", DEC)
        VALUE(8, BE, EccTypeIndicator, "ECC Type Indicator", DEC)
        COMMENT(COMMENT_PARAGRAPH, "First byte of field and any padding bytes")
        STRING_REF(STRING_ASCII, BE, EccAlphaIdentifier, "Ecc Alpha Identifier", L, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END    

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_FORBIDDEN_PLMNS_PLMN") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_FORBIDDEN_PLMNS_PLMN, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, SIM_PLMN_LEN)
        FILLER_EX(Padding, 8, 1)
    SEQ_END    

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_PLMN_RECORD") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_PLMN_RECORD, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, SIM_PLMN_LEN)
        FILLER_EX(Padding, 8, 1)
    SEQ_END    

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_OPERATOR_PLMNS_PLMN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_OPERATOR_PLMNS_PLMN, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, SIM_PLMN_LEN)
        FILLER_EX(Padding1, 8, 1)
        SEQ_OF(PLMNAccessTechnologyID, "PLMNAccessTechnologyID", AUTOGEN_SEQ_BYTE_HEX, SIM_PLMN_ACCESS_TECHNOLOGY_LEN)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SEQ_END

    DER_CONST_TBL_BEGIN(SIM_SB_CS_WRITE_RESP_SB_ID, SIM_SB_CS_WRITE_RESP_SB_ID_DEFINES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_TMSI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_BCCH_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_LAI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GSM_NETPAR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_FDD_NETPAR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_TDD_NETPAR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_USER_PLMN_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_RPLMN_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GPRS_RAI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GPRS_RAUS_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GPRS_TMSI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_UMTS_START_PS_ID)
        DER_CONST_TBL_ENTRY(SIM_SB_UMTS_START_CS_ID)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SB_STA_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_CS_WRITE_RESP_SB, CREATE_STRUCT, "", "")
        VALUE_CONST(SubBlockID, "SubBlockID Type", SIM_SB_CS_WRITE_RESP_SB_ID)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SB_SPN_DISPLAY_INFO_PLMNS_PLMN, CREATE_STRUCT, "", "")
        SEQ_OF(PLMN, "PLMN", AUTOGEN_SEQ_BYTE_HEX, SIM_PLMN_LEN)
        FILLER_EX(Padding, 8, 1)
    SEQ_END    

    DER_CONST_TBL_BEGIN(SIM_SB_REQUEST_TAGS, SIM_PB_LOCATION_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_PB_ADN)
        DER_CONST_TBL_ENTRY(SIM_PB_ANR)
        DER_CONST_TBL_ENTRY(SIM_PB_BDN)
        DER_CONST_TBL_ENTRY(SIM_PB_CC)
        DER_CONST_TBL_ENTRY(SIM_PB_CCP)
        DER_CONST_TBL_ENTRY(SIM_PB_CCP1)
        DER_CONST_TBL_ENTRY(SIM_PB_CCP2)
	DER_CONST_TBL_ENTRY(SIM_PB_EMAIL)
        DER_CONST_TBL_ENTRY(SIM_PB_FDN)
        DER_CONST_TBL_ENTRY(SIM_PB_FDN_LIST_STATUS)
        DER_CONST_TBL_ENTRY(SIM_PB_GAS)
        DER_CONST_TBL_ENTRY(SIM_PB_GRP)
        DER_CONST_TBL_ENTRY(SIM_PB_HIDDEN)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC_ANR)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC_EMAIL)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC_GAS)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC_SNE)
        DER_CONST_TBL_ENTRY(SIM_PB_LOC_AAS)
        DER_CONST_TBL_ENTRY(SIM_PB_MSISDN)
        DER_CONST_TBL_ENTRY(SIM_PB_PBC)
        DER_CONST_TBL_ENTRY(SIM_PB_PUID)
        DER_CONST_TBL_ENTRY(SIM_PB_SDN)
        DER_CONST_TBL_ENTRY(SIM_PB_SNE)        
        DER_CONST_TBL_ENTRY(SIM_PB_UID)
        DER_CONST_TBL_ENTRY(SIM_PB_VMBX)
        DER_CONST_TBL_ENTRY(SIM_PB_MBDN)
        DER_CONST_TBL_ENTRY(SIM_PB_AAS)
    DER_CONST_TBL_END

    SEQ_BEGIN(SIM_PB_TAG, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(Tag, "Tag", SIM_SB_REQUEST_TAGS)
    SEQ_END

    /* Following sequences are data structures used by several subblocks */
    DER_CONST_TBL_BEGIN(SIM_PB_LOCATION_TYPE, SIM_PB_LOCATION_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_PB_ADN)
        DER_CONST_TBL_ENTRY(SIM_PB_ANR)
        DER_CONST_TBL_ENTRY(SIM_PB_BDN)
        DER_CONST_TBL_ENTRY(SIM_PB_EMAIL)
        DER_CONST_TBL_ENTRY(SIM_PB_FDN)
        DER_CONST_TBL_ENTRY(SIM_PB_GAS)
        DER_CONST_TBL_ENTRY(SIM_PB_GRP)
        DER_CONST_TBL_ENTRY(SIM_PB_MSISDN)
        DER_CONST_TBL_ENTRY(SIM_PB_PBC)
        DER_CONST_TBL_ENTRY(SIM_PB_SDN)
        DER_CONST_TBL_ENTRY(SIM_PB_SNE)
        DER_CONST_TBL_ENTRY(SIM_PB_VMBX)
        DER_CONST_TBL_ENTRY(SIM_PB_MBDN)
        DER_CONST_TBL_ENTRY(SIM_PB_AAS)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_LOCATION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_LOCATION, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(LocationType, "Location Type", SIM_PB_LOCATION_TYPE)
        VALUE(16, BE, Location, "Location", DEC) 
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_NAME_NUMBER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_NAME_NUMBER, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UINT16")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_UINT16, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        VALUE(16, BE, Data, "Data", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_TEXT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_TEXT, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_TEXT_LEN)
        REFERENCE(8, BE, TextLength, "TextLength", N)
        FILLER_EX(Filler1, 8, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Text, "Text", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UINT8")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_UINT8, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE(8, BE, Data, "Data", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_PRIMITIVE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_PRIMITIVE, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_TXT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_CONF_TXT, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE(8, BE, FileType, "FileType", DEC)    
        VALUE(8, BE, FileLength, "FileLegnth", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        FILLER_EX(Filler1, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_LONG_TXT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_CONF_LONG_TXT, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, Type1FilesPerAdn, "Type1FilesPerAdn", DEC)
        VALUE(8, BE, Type2FilesPerAdn, "Type2FilesPerAdn", DEC)
        FILLER_EX(Filler, 8, 3)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* tSIM_Code                                                               */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef char tSIM_Code[MAX_CODE_LEN];")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_INFO_REQUEST")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_INFO_REQUEST, CREATE_STRUCT, "", "")
        SIM_SB_16_LONG_SEQ
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_MAX_NUMBER_OF_TAGS)
        REFERENCE(8, BE, NumberOfTags, "NumberOfTags", M)
        FILLER_EX(Filler1, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SEQ_OF_REF(Tags, "Tags", SIM_PB_TAG, M, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Sequence: tSIM_Request                                                  */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   TransID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   MessageID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   ServiceType;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Paddingbyte;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Request;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_REQUEST_PIN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_REQUEST_PIN, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "TransID", DEC)
        VALUE(8, BE, MessageID, "MessageID", DEC)
        VALUE(8, BE, ServiceType, "ServiceType", DEC)
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SEQ_END
    
    /* Following sequences are structs for Generic part of ISI Request/Response */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_Request, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "TransID", DEC)
        VALUE(8, BE, MessageID, "MessageID", DEC)
        VALUE(8, BE, ServiceType, "ServiceType", DEC)
        FILLER_EX(Paddingbyte, 8, 1)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Sequence: tSIM_Response                                                 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct tSIM_Response")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   TransID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   MessageID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   ServiceType;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Status;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Response;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_Req, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "TransID", DEC)
        VALUE(8, BE, MessageID, "MessageID", DEC)
        VALUE(8, BE, ServiceType, "ServiceType", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_Response, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "TransID", DEC)
        VALUE(8, BE, MessageID, "MessageID", DEC)
        VALUE(8, BE, ServiceType, "ServiceType", DEC)
        VALUE(8, BE, Status, "Status", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_InfoResponse")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_InfoResponse, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "TransID", DEC)
        VALUE(8, BE, MessageID, "MessageID", DEC)
        VALUE(8, BE, ServiceType, "ServiceType", DEC)
        VALUE(8, BE, Status, "Status", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Icc_Id_Data") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    SEQ_BEGIN(SIM_ICC_ID_DATA, CREATE_STRUCT, "", "")
        SEQ_OF(id_data, "id_data", AUTOGEN_SEQ_BYTE_HEX, SIM_ICC_ID_LEN)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Icc") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_ICC, CREATE_STRUCT, "", "")
        SEQ_OF(Icc, "Icc", SIM_ICC_ID_DATA, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_RESP_IMSI, CREATE_STRUCT, "", "") 
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, length, "Length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "IMSI number.")
        SEQ_OF(imsi, "imsi", AUTOGEN_SEQ_BYTE_HEX, SIM_IMSI_LEN)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Imsi")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_IMSI, CREATE_STRUCT, "", "")
        SEQ_OF(Imsi, "Imsi", SIM_RESP_IMSI, 1)
    SEQ_END        

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_ACM_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_ACM, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "dword")
        VALUE(32, BE, count, "Count", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_ACM_MAX_VALUE_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_ACM_MAX_VALUE, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "dword")
        VALUE(32, BE, count, "Count", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_PUCT_UNICODE_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_PUCT_UNICODE, CREATE_STRUCT, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    	COMMENT(COMMENT_TEXT, "Currency code")
        STRING(STRING_UNICODE, BE, currency_code, "Currency Code", SIM_PUCT_CURRENCY_CODE_LEN)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Elementary price per unit")
        VALUE(16, BE, eppu, "eppu", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Multiplication factor, see GSM 11.11 for details")
        VALUE(-8, BE, ex, "ex", DEC)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_CB_MSG_IDS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_INFO_CB_MSG_IDS_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "word")
        SEQ_OF(cell_bc_msg_ids, "cell bc msg_ids", AUTOGEN_SEQ_WORD_HEX, SIM_NBR_OF_CELL_BC_MSG_IDS)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PLMNT_STRUCT") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"For instance, using 246 for the MCC and 81 for the MNC (pad = 0x00 )  the contents is as follows:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Bytes:	0x42 0xF6 0x18 0x00")
    SEQ_BEGIN(tSIM_PLMNT_STRUCT, CREATE_STRUCT, "", "") 
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mcc2_mcc1, "mcc2_mcc1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mnc3_mcc3, "mnc3_mcc3", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mnc2_mnc1, "mnc2_mnc1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(padding, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PLMN_SELECTOR_STR") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_PLMN_SELECTOR_STR, CREATE_STRUCT, "", "") 
        SEQ_OF(plmn, "plmn", tSIM_PLMNT_STRUCT, SIM_PLMN_SELECTOR_LIST_LEN)
    SEQ_END

/* tCPHS_Optionals */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCPHS_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tCPHS_Optionals, CREATE_STRUCT, "013.000", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, MailboxNumbInfo, "MailboxNumbInfo", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END    
    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tCPHS_Optionals;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCPHS_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tCPHS_Optionals, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf MailboxNumbInfo:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf RFU:7;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, MailboxNumbInfo, "MailboxNumbInfo")
            VALUE(1, BE, MailboxNumbInfo, "MailboxNumbInfo", HEX)
            VALUE(7, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END
    
/*  To be defined when sim_isi_common_str.h is removed */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CPHS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "CPHS Service table.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Indicates if the optional data-field is able to be read and updated. Data-field is available if it is 'activated' and 'allocated'.")
    SEQ_BEGIN(SIM_SERV_CPHS_STR, CREATE_STRUCT, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
  	COMMENT(COMMENT_TEXT, "CPHS phase.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x01: Phase 1.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x02: Phase 2.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "etc.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, phase, "phase", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_allocated, "csp_allocated", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
	VALUE(8, BE, csp_active, "csp_active", DEC)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is allocated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, service_string_tbl_allocated, "service_string_tbl_allocated", DEC)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is active.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, service_string_tbl_active, "service_string_tbl_active", DEC)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the Voice Mailbox.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
	VALUE(8, BE, mailbox_numbers_allocated, "mailbox_numbers_allocated", DEC)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the Voice Mailbox.")
	PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mailbox_numbers_active, "mailbox_numbers_active", DEC)
        COMMENT(COMMENT_TEXT, "Information Number data-field is allocated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, inf_nbr_allocated, "inf_nbr_allocated", DEC)
        COMMENT(COMMENT_TEXT, "Information Number data-field is active.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, inf_nbr_active, "inf_nbr_active", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_OPERATOR_NAME_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_OPERATOR_NAME, CREATE_STRUCT, "001.000", "")
        COMMENT(COMMENT_TEXT, "Null terminated.")
        SEQ_OF(operator_name, "operator_name", AUTOGEN_SEQ_WORD_DEC, SIM_OPERATOR_NAME_LEN + 1)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_OPL, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Mobile Country Code, Digit1-2.")
        VALUE(8, BE, mcc2_mcc1, "mcc2_mcc1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Mobile Country Code, Digit3.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mobile Network Code, Digit3.")
        VALUE(8, BE, mnc3_mcc3, "mnc3_mcc3", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Mobile Network Code, Digit1-2.")
        VALUE(8, BE, mnc2_mnc1, "mnc2_mnc1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "Location Area Code.")
        VALUE(8, BE, lac_lower_MSB, "lac_lower_MSB", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "Location Area Code.")
        VALUE(8, BE, lac_lower_LSB, "lac_lower_LSB", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "Location Area Code.")
        VALUE(8, BE, lac_upper_MSB, "lac_upper_MSB", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "Location Area Code.")
        VALUE(8, BE, lac_upper_LSB, "lac_upper_LSB", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "Identifier of operator name to be displayed.")
        VALUE(8, BE, PNN_identifier, "PNN_identifier", DEC)
    SEQ_END

/* tCSP_Optionals */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCSP_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tCSP_Optionals, CREATE_STRUCT, "013.000", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, HML_Spec, "HML_Spec", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, D5InfoNumbers, "D5InfoNumbers", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
    SEQ_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tCSP_Optionals;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tCSP_Optionals")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tCSP_Optionals, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf HML_Spec:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf D5InfoNumbers:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf RFU:6;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, OptionalData, "OptionalData")
            VALUE(1, BE, HML_Spec, "HML_Spec", HEX)
            VALUE(1, BE, D5InfoNumbers, "D5InfoNumbers", HEX)
            VALUE(6, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_CALL_OFFERING_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_OFFERING_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_OFFERING_STR, CREATE_STRUCT, "013.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
  	COMMENT(COMMENT_TEXT, "CPHS phasCall Transfer.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "0x01: Phase 1.")
        VALUE(8, BE, call_transfer, "call_transfer", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Call Forwarding on user Not Reachable.")
        VALUE(8, BE, not_reachable, "not_reachable", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Call Forwarding on No Reply.")
        VALUE(8, BE, no_reply, "no_reply", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Call Forwarding on user busy.")
        VALUE(8, BE, busy, "busy", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Call Forwarding Unconditional.")
        VALUE(8, BE, unconditional, "unconditional", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_CALL_OFFERING_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_OFFERING_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_OFFERING_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf call_transfer:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf not_reachable:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf no_reply:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf busy:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf unconditional:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallOffering, "CallOffering")
            VALUE(1, BE, call_transfer, "call_transfer", HEX)
            VALUE(1, BE, not_reachable, "not_reachable", HEX)
            VALUE(1, BE, no_reply, "no_reply", HEX)
            VALUE(1, BE, busy, "busy", HEX)
            VALUE(1, BE, unconditional, "unconditional", HEX)
            VALUE(3, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_CALL_RESTRICTION_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_RESTRICTION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_RESTRICTION_STR, CREATE_STRUCT, "013.000", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, incoming_if_roaming, "incoming_if_roaming", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, incoming, "incoming", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, international_ex_HPLMN, "international_ex_HPLMN", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, outgoing_international, "outgoing_international", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, outgoing, "outgoing", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_CALL_RESTRICTION_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_RESTRICTION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_RESTRICTION_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf incoming_if_roaming:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf incoming:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf international_ex_HPLMN:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf outgoing_international:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf outgoing:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, incoming_if_roaming, "incoming_if_roaming", HEX)
            VALUE(1, BE, incoming, "incoming", HEX)
            VALUE(1, BE, international_ex_HPLMN, "international_ex_HPLMN", HEX)
            VALUE(1, BE, outgoing_international, "outgoing_international", HEX)
            VALUE(1, BE, outgoing, "outgoing", HEX)
            VALUE(3, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_OTHER_SS_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_OTHER_SS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_OTHER_SS_STR, CREATE_STRUCT, "013.000", "")
        COMMENT(COMMENT_TEXT, "Advice Of Charging.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, aoc, "aoc", DEC)
        COMMENT(COMMENT_TEXT, "Closed User Group.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, cug, "cug", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Multi Party Service.")
        VALUE(8, BE, multi_party, "multi_party", DEC)
        FILLER_EX(padding1, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_OTHER_SS_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_OTHER_SS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_OTHER_SS_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf aoc:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf cug:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf multi_party:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, aoc, "aoc", HEX)
            VALUE(1, BE, cug, "cug", HEX)
            VALUE(1, BE, multi_party, "multi_party", HEX)
            VALUE(5, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END
    
/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_CALL_COMPLETION_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_COMPLETION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_COMPLETION_STR, CREATE_STRUCT, "013.000", "")
        COMMENT(COMMENT_TEXT, "Call Completion to Busy Subscriber.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, call_completion_to_busy, "call_completion_to_busy", DEC)
        COMMENT(COMMENT_TEXT, "Call Waiting.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, call_waiting, "call_waiting", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Call Hold.")
        VALUE(8, BE, call_hold, "call_hold", DEC)
        FILLER_EX(padding1, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_CALL_COMPLETION_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CALL_COMPLETION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CALL_COMPLETION_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf call_completion_to_busy:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf call_waiting:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf call_hold:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, call_completion_to_busy, "call_completion_to_busy", HEX)
            VALUE(1, BE, call_waiting, "call_waiting", HEX)
            VALUE(1, BE, call_hold, "call_hold", HEX)
            VALUE(5, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_TELESERVICES_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_TELESERVICES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_TELESERVICES_STR, CREATE_STRUCT, "013.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
  	COMMENT(COMMENT_TEXT, "Restriction of menus for SMS validity period options")
	PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_validity_period, "sms_validity_period", DEC)
  	COMMENT(COMMENT_TEXT, "Restriction of menus for SMS protocol ID options")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_protocol_id, "sms_protocol_id", DEC)
  	COMMENT(COMMENT_TEXT, "SMS delivery confirmation.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_delivery_conf, "sms_delivery_conf", DEC)
  	COMMENT(COMMENT_TEXT, "Restriction of menu option to set reply path active on outgoing SMS.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_reply_path, "sms_reply_path", DEC)
  	COMMENT(COMMENT_TEXT, "SMS - Cell Broadcast.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_cb, "sms_cb", DEC)
  	COMMENT(COMMENT_TEXT, "SMS - Mobile originated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_mo, "sms_mo", DEC)
  	COMMENT(COMMENT_TEXT, "SMS - Mobile terminated.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sms_mt, "sms_mt", DEC)
        FILLER_EX(padding1, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_TELESERVICES_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_TELESERVICES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_TELESERVICES_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_validity_period:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_protocol_id:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_delivery_conf:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_reply_path:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_cb:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_mo:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sms_mt:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, sms_validity_period, "sms_validity_period", HEX)
            VALUE(1, BE, sms_protocol_id, "sms_protocol_id", HEX)
            VALUE(1, BE, sms_delivery_conf, "sms_delivery_conf", HEX)
            VALUE(1, BE, sms_reply_path, "sms_reply_path", HEX)
            VALUE(1, BE, sms_cb, "sms_cb", HEX)
            VALUE(1, BE, sms_mo, "sms_mo", HEX)
            VALUE(1, BE, sms_mt, "sms_mt", HEX)
            VALUE(1, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_CPHS_TELESERVICES_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CPHS_TELESERVICES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CPHS_TELESERVICES_STR, CREATE_STRUCT, "013.000", "")
        COMMENT(COMMENT_TEXT, "Alternate Line Service.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, als, "als", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_CPHS_TELESERVICES_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CPHS_TELESERVICES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CPHS_TELESERVICES_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf als:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, als, "als", HEX)
            VALUE(7, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_CPHS_FEATURES_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CPHS_FEATURES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CPHS_FEATURES_STR, CREATE_STRUCT, "013.000", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sap, "sap", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, browser, "browser", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, services, "services", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sst, "sst", DEC)
    SEQ_END
    
#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_CPHS_FEATURES_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_CPHS_FEATURES_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_CPHS_FEATURES_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sap:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf browser:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf services:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sst:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, sap, "sap", HEX)
            VALUE(1, BE, browser, "browser", HEX)
            VALUE(1, BE, services, "services", HEX)
            VALUE(1, BE, sst, "sst", HEX)
            VALUE(4, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_NBR_IDENTIFICATION_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_NBR_IDENTIFICATION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_NBR_IDENTIFICATION_STR, CREATE_STRUCT, "013.000", "")
        COMMENT(COMMENT_TEXT, "Menu to block Calling Line Identity.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, cli_block, "cli_block", DEC)
        COMMENT(COMMENT_TEXT, "Menu to send Calling Line Identity.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, cli_send, "cli_send", DEC)
        COMMENT(COMMENT_TEXT, "Malicious Call Indicator.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, malicious_call_ind, "malicious_call_ind", DEC)
        COMMENT(COMMENT_TEXT, "Connected Line Identity Presentation.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, conn_line_ind_pres, "conn_line_ind_pres", DEC)
        COMMENT(COMMENT_TEXT, "Connected Line Identity Restricted.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, conn_line_ind_restriction, "conn_line_ind_restriction", DEC)
        COMMENT(COMMENT_TEXT, "Calling Line Identity Presentation.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, clip, "clip", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_NBR_IDENTIFICATION_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_NBR_IDENTIFICATION_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_NBR_IDENTIFICATION_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf cli_block:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf cli_send:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf malicious_call_ind:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf conn_line_ind_pres:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf conn_line_ind_restriction:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf clip:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, cli_block, "cli_block", HEX)
            VALUE(1, BE, cli_send, "cli_send", HEX)
            VALUE(1, BE, malicious_call_ind, "malicious_call_ind", HEX)
            VALUE(1, BE, conn_line_ind_pres, "conn_line_ind_pres", HEX)
            VALUE(1, BE, conn_line_ind_restriction, "conn_line_ind_restriction", HEX)
            VALUE(1, BE, clip, "clip", HEX)
            VALUE(2, BE, RFU, "RFU", HEX)
        MERGE_END
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_HML_SPECIFICS_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_HML_SPECIFICS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_HML_SPECIFICS_STR, CREATE_STRUCT, "013.000", "")
        COMMENT(COMMENT_TEXT, "Restriction of menus where user can change language.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, lang, "lang", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, rfu, "rfu", DEC)
        COMMENT(COMMENT_TEXT, "Restriction of menu options for Data call.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, data, "data", DEC)
        COMMENT(COMMENT_TEXT, "Restriction of menu options for Fax call.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, fax, "fax", DEC)
        COMMENT(COMMENT_TEXT, "Restriction of menu options for ability to send SMS with type Email.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sm_mo_email, "sm_mo_email", DEC)
        COMMENT(COMMENT_TEXT, "Restriction of menu options for ability to send SMS with type paging.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, sm_mo_paging, "sm_mo_paging", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "Restriction of menu options for Voice Mail Service or other similar menus.")
        VALUE(8, BE, vps, "vps", DEC)
        COMMENT(COMMENT_TEXT, "Restriction of menu options for manual PLMN selection.")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, plmn_mode, "plmn_mode", DEC)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_HML_SPECIFICS_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_HML_SPECIFICS_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_HML_SPECIFICS_STR, CREATE_STRUCT, "", "013.000")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf lang:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf rfu:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf data:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf fax:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sm_mo_email:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf sm_mo_paging:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf vps:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    bitf plmn_mode:1;")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        MERGE_BEGIN(8, BE, CallRestriction, "CallRestriction")
            VALUE(1, BE, lang, "lang", HEX)
            VALUE(1, BE, rfu, "rfu", HEX)
            VALUE(1, BE, data, "data", HEX)
            VALUE(1, BE, fax, "fax", HEX)
            VALUE(1, BE, sm_mo_email, "sm_mo_email", HEX)
            VALUE(1, BE, sm_mo_paging, "sm_mo_paging", HEX)
            VALUE(1, BE, vps, "vps", HEX)
            VALUE(1, BE, plmn_mode, "plmn_mode", HEX)
        MERGE_END
    SEQ_END
    
/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_STR, CREATE_STRUCT, "013.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Call Offering services.")
        SEQ_OF(call_offering, "call offering", SIM_SERV_CSP_CALL_OFFERING_STR, 1)
        COMMENT(COMMENT_TEXT, "Call Restriction services.")
        SEQ_OF(call_restriction, "call restriction", SIM_SERV_CSP_CALL_RESTRICTION_STR,1 )
        COMMENT(COMMENT_TEXT, "Other supplementary services.")
        SEQ_OF(other_ss, "other ss", SIM_SERV_CSP_OTHER_SS_STR, 1)
        COMMENT(COMMENT_TEXT, "Call Completion services.")
        SEQ_OF(call_completion, "call completion", SIM_SERV_CSP_CALL_COMPLETION_STR, 1)
        COMMENT(COMMENT_TEXT, "Teleservices.")
        SEQ_OF(teleservices, "teleservices", SIM_SERV_CSP_TELESERVICES_STR, 1)
        COMMENT(COMMENT_TEXT, "CPHS Teleservices.")
        SEQ_OF(cphs_teleservices, "cphs teleservices", SIM_SERV_CSP_CPHS_TELESERVICES_STR, 1)        
	COMMENT(COMMENT_TEXT, "CPHS features.")
        SEQ_OF(cphs_features, "cphs features", SIM_SERV_CSP_CPHS_FEATURES_STR, 1)
        SEQ_OF(nbr_identification, "nbr identification", SIM_SERV_CSP_NBR_IDENTIFICATION_STR, 1)
        SEQ_OF(hml_specifics, "hml specifics", SIM_SERV_CSP_HML_SPECIFICS_STR, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT(COMMENT_TEXT, "Information Numbers. The Information Numbers only have to be presented to user if this field is set to 0xFF.")
        VALUE(8, BE, byte_d5_inf_numbers, "byte d5 inf numbers", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
    SEQ_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_SERV_CSP_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_SERV_CSP_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_SERV_CSP_STR, CREATE_STRUCT, "", "013.000")
        SEQ_OF(call_offering, "call offering", SIM_SERV_CSP_CALL_OFFERING_STR, 1)
        SEQ_OF(call_restriction, "call restriction", SIM_SERV_CSP_CALL_RESTRICTION_STR,1 )
        SEQ_OF(other_ss, "other ss", SIM_SERV_CSP_OTHER_SS_STR, 1)
        SEQ_OF(call_completion, "call completion", SIM_SERV_CSP_CALL_COMPLETION_STR, 1)
        SEQ_OF(teleservices, "teleservices", SIM_SERV_CSP_TELESERVICES_STR, 1)
        SEQ_OF(cphs_teleservices, "cphs teleservices", SIM_SERV_CSP_CPHS_TELESERVICES_STR, 1)
        SEQ_OF(cphs_features, "cphs features", SIM_SERV_CSP_CPHS_FEATURES_STR, 1)
        SEQ_OF(nbr_identification, "nbr identification", SIM_SERV_CSP_NBR_IDENTIFICATION_STR, 1)
        SEQ_OF(hml_specifics, "hml specifics", SIM_SERV_CSP_HML_SPECIFICS_STR, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        VALUE(8, BE, byte_d5_inf_numbers, "byte d5 inf numbers", DEC)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_SERV_CSP_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_CBMID_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_INFO_CBMID_STR, CREATE_STRUCT, "", "")
        SEQ_OF(cbmid, "cbmid", AUTOGEN_SEQ_WORD_DEC, SIM_MAX_NBR_OF_CBMIDS)
    SEQ_END

/* tSIM_REFRESH_FILE_LIST_STR */
    DER_CONST_TBL_BEGIN(SIM_REFERSH_FILE_IDS, SIM_REFRESH_FILE_ID_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ICC_ID)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ADMINISTRATIVE_DATA)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_TABLE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_IMSI)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_FORBIDDEN_PLMNS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_LOCATION_INFOMATION)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_KEY_KC)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PLMN_SELECTOR)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_CONTROL_CHANNELS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_MESSAGE_IDENTIFIER)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ACCESS_CONTROL_CLASS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_LANGUAGE_PREFERENCE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ACCUMULATED_CALL_METER)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ACM_MAXIMUM_VALUE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PRICE_PER_UNIT_CURRENCY_TABLE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_HPLMN_SEACH_PERIOD)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PHASE_IDENTIFICATION)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GROUP_ID_LEVEL_1)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GROUP_ID_LEVEL_2)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_PROVIDER_NAME)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_EMERGENCY_CALL_CODES)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CELL_BROADCAST_MESSSAGE_ID_DATA_DOWNLOAD)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GPRS_LOCATION_INFORMATION)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GPRS_CIPHERING_KEY_KCGPRS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_PLMN_LIST)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PLMN_NETWORK_NAME)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CUSTORMER_SERVICE_PROFILE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VOICE_MESSAGE_WAITING)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CALL_FORWARD_FLAGS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_NAME_STRING)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CPHS_INFO)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_INFO_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ABBREVIATED_DIALLING_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGES)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_FIXED_DIALLING_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MSISDN)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGE_SERVICE_PARAMETERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SHORT_MESSAGE_SERVICE_STATUS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_DIALLING_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CSP_LINE_2)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_USER_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_OPERATOR_CONTROLLED_PLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_HPLMN_SELECTOR_ACCESS_TECH)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MESSAGE_WAITING_INDICATION_STATUS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CALL_FORWARDING_INDICATION_STATUS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_IDENTIFIER)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MAILBOX_DIALLING_NUMBERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_EXTENDED_LANGUAGE_PREFERENCE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SERVICE_PROVIDER_DISPLAY_INFOMARTION)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_INTEGRITY_KEYS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CIPHERING_INTEGRITY_KEYS_PACKET_SWITCHED_DOMAIN)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_INITIALISATION_VALUES_FOR_HYPERFRAME_NUMBER)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MAXIMUM_VALUE_OF_START)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PACKET_SWITCHED_LOCATION_INFORMATION)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_NETWORK_PARAMETERS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ENABLED_SERVICES_TABLE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_APPLICATION_DIRECTORY)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PHONE_BOOK_REFERENCE_FILE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_INDEX_ADMINISTRATION_PHONE_BOOK)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GROUPING_FILE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_GROUPING_INFORMATION_ALPHA_STRING)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_SECOND_NAME_ENTRY)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_UNKNOWN_FILES)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_TERMINAL_SUPPORT_TABLE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ACTING_HPLMN)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_IMAGE)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_PARM)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE1)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE2)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE3)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_CACHE4)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_1)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_2)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_3)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_SUBS_LAC_CI_4)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_TAGS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_VIAG_HOMEZONE_UHZIUE_SETTINGS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_EQUIVALENT_HPLMNS)
        DER_CONST_TBL_ENTRY_VER(SIM_REFRESH_ATT_RAT, "017.006", "")
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ACL)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MMS_USER_PREF)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_MMS_ISSUER_CONN_PAR)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_DYNAMIC_FLAGS1)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_DYNAMIC_FLAGS2)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PSC)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_CC)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PUID)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_ANR)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_PBC)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_EMAIL)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_UID)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_AAS)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_IMS_PRIVATE_USER_ID)
        DER_CONST_TBL_ENTRY(SIM_REFRESH_IMS_PUBLIC_USER_ID) 
        DER_CONST_TBL_ENTRY(SIM_REFRESH_IMS_HOME_NW_DOMAIN_NAME)
        DER_CONST_TBL_ENTRY_VER(SIM_REFRESH_GBABP,                  "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_REFRESH_GBANL,                  "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_REFRESH_MSK,                    "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_REFRESH_MUK,                    "017.003", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_REFRESH_FILE_LIST_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_REFRESH_FILE_LIST_STR, CREATE_STRUCT, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "FileID of elementary file to refresh.")
        VALUE_CONST(FileID, "FileID", SIM_REFERSH_FILE_IDS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Ask client if refresh of elementary file is allowed before refresh is executed")
        VALUE_CONST(AskBeforeRefresh, "Ask before Refresh", TRUE_FALSE)
    SEQ_END

    SEQ_BEGIN(SIM_REFERSH_FILE_LIST, DONT_CREATE_STRUCT, "", "")
        VALUE_CONST(FileID, "File ID", SIM_REFERSH_FILE_IDS)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_IMS_READ_DATA_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_ST_IMS_READ_DATA_REQ, CREATE_STRUCT, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        VALUE(8, BE, MessageID, "Message ID", DEC)
        VALUE(8, BE, ServiceType, "Service Type", DEC)
        VALUE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", DEC) /* Changed from 'REFERENCE' because it was not used as such */
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_INFO_PLMN_STR */
#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) SIM_INFO_PLMN_STR;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_PLMN_STR")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"For instance, using 246 for the MCC and 81 for the MNC (pad = 0x00 )  the contents is as follows:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Bytes:	0x42 0xF6 0x18 0x00")
    SEQ_BEGIN(SIM_INFO_PLMN_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mcc2_mcc1, "mcc2_mcc1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mnc3_mcc3, "mnc3_mcc3", DEC)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, mnc2_mnc1, "mnc2_mnc1", DEC)
    SEQ_END

   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Enum: Fieldtest display                                                 */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef enum")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "{")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_FTD_FIRST_SUB_BLOCK = 0x3200,")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_VOL_SEL,         /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_BAUDRATE,        /* WORD   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_CLOCK_STOP_ALL,      /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_CLOCK_STOP_COND,     /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_PIN1_ATT,            /* BYTE   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_PIN2_ATT,            /* BYTE   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_PUK1_ATT,            /* BYTE   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_PUK2_ATT,            /* BYTE   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_ATR_RETRANS,         /* BYTE   */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_SERV_TAB,        /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_CSP1,            /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_CSP2,            /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    FTD_SB_SIM_HIST_DATA        /* STRING */")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} SIM_FTD_SB_VALUES;")
   COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

/* tSIM_Number */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Number")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_Number, CREATE_STRUCT, "", "")
        VALUE(8, BE, NameLen, "NameLen", DEC)
        VALUE(8, BE, NumLen, "NumLen", DEC)
        STRING(STRING_UNICODE_ZERO_TERMINATED, BE, NamNum, "NamNum name", MAX_NAME_LEN + 1 + MAX_NUM_LEN + 1)
    SEQ_END

/* SIM_FTD_DATA_ASCII_STRING_STR */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_FTD_DATA_ASCII_STRING_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_FTD_DATA_ASCII_STRING_STR, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, string_lenght, "string_lenght", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "char")
        SEQ_OF(string, "string", AUTOGEN_SEQ_BYTE_DEC, COMM_MAX_FTD_STRING_LENGTH)
    SEQ_END

/* SIM_FTD_DATA_BYTE_STR */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_FTD_DATA_BYTE_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_FTD_DATA_BYTE_STR, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, data, "data", DEC)
    SEQ_END

/* SIM_FTD_DATA_FAIL_STR */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_FTD_DATA_FAIL_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_FTD_DATA_FAIL_STR, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler1, "filler1", DEC)
        VALUE(16, BE, not_identified_subblockID, "not_identified_subblockID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, fail_reason, "fail_reason", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler2, "filler2", DEC)
    SEQ_END

/* SIM_FTD_DATA_WORD_STR */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_FTD_DATA_WORD_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_FTD_DATA_WORD_STR, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler1, "filler1", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "word")
        VALUE(16, BE, data, "data", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler2, "filler2", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler3, "filler3", DEC)
    SEQ_END

/* tGeneralSubblock */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGeneralSubblock")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tGeneralSubblock, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        VALUE(16, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, status, "status", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, rec_length, "rec_length", DEC)
        REFERENCE(16, BE, data_length, "data_length", N)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        SEQ_OF_REF(Content, "Content", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
    SEQ_END
    
/* tGeneralSubblockResp */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tGeneralSubblockResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tGeneralSubblockResp, CREATE_STRUCT, "", "")
        VALUE(16, BE, subblockID, "subblockID", DEC)
        VALUE(16, BE, subblock_length, "subblock_length", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, status, "status", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, filler2, "filler2", DEC)
        REFERENCE(16, BE, data_length, "data_length", N)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        SEQ_OF_REF(Content, "Content", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
    SEQ_END

    DER_CONST_TBL_BEGIN(SIM_SB_PHONE_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_PHONE_NUMBER_FIELD  tSIM_FDN_CHECK_GENERIC_SB")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_SMS_DEST_ADR        tSIM_FDN_CHECK_GENERIC_SB")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_SMSC_ADR            tSIM_FDN_CHECK_GENERIC_SB")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_FDN_CHECK_GENERIC_SB") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(tSIM_FDN_CHECK_GENERIC_SB, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "SubBlockID", DEC)
        VALUE(16, BE, SubBlockLength, "SubBlockLength", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PHONE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, NumLen, "NumLen", N)
        FILLER_EX(padding1, 8, 1)   
        FILLER_EX(padding2, 8, 1)   
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END
    
/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_INFO_ZONE_IDENTITY_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_ZONE_IDENTITY_STR") 
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(SIM_INFO_ZONE_IDENTITY_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        SEQ_OF(ci, "ci", AUTOGEN_SEQ_BYTE_HEX, 2)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_INFO_ZONE_COORD_STR and SIM_SERV_ZONE_COORD_STR */
#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_SERV_ZONE_COORD_STR SIM_INFO_ZONE_COORD_STR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_INFO_ZONE_COORD_STR") 
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(SIM_INFO_ZONE_COORD_STR, CREATE_STRUCT, "", "")
        VALUE(32, BE, square_radius, "square_radius", DEC)
        VALUE(32, BE, x_coord, "x_coord", DEC)
        VALUE(32, BE, y_coord, "y_coord", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, grid_id, "grid_id", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(SIM_SERV_ZONE_COORD_STR, CREATE_STRUCT, "", "")
        VALUE(32, BE, square_radius, "square_radius", DEC)
        VALUE(32, BE, x_coord, "x_coord", DEC)
        VALUE(32, BE, y_coord, "y_coord", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, grid_id, "grid_id", DEC)
    SEQ_END

/*  To be defined when sim_isi_common_str.h is removed */
/* SIM_JACOB_ID_READ_STR */
#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "SIM_JACOB_ID_READ_STR") 
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(SIM_JACOB_ID_READ_STR, CREATE_STRUCT, "", "")
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "word")
        VALUE(16, BE, loc_nbr, "loc_nbr", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, odd_key, "odd_key", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, even_key, "even_key", DEC)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(tSIM_SB, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "SubBlockID", DEC)
        VALUE(16, BE, SubBlockLength, "SubBlockLength", DEC)
    SEQ_END

    /* tSIM_SB_CS_STANDARD */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CS_STANDARD") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(tSIM_SB_CS_STANDARD, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "SubBlockID", DEC)
        VALUE(16, BE, SubBlockLength, "SubBlockLength", DEC)
        VALUE(8, BE, Status, "Status", DEC)
        FILLER_EX(Padding, 8, 3)
    SEQ_END
    
    /* tSIM_SB_NETPAR */
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_GSM_NETPAR tSIM_SB_NETPAR")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_FDD_NETPAR tSIM_SB_NETPAR")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SB_TDD_NETPAR tSIM_SB_NETPAR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_NETPAR") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(tSIM_SB_NETPAR, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "SubBlockID", DEC)
        VALUE(16, BE, SubBlockLength, "SubBlockLength", DEC)
        VALUE(8, BE, Status, "Status", DEC)
        VALUE(8, BE, FileSize, "File size", DEC)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, DataLength, "Length of Data", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SEQ_END

    /* tSIM_SB_UNSUPPORTED */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UNSUPPORTED") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SEQ_BEGIN(tSIM_SB_UNSUPPORTED, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "SubBlockID", DEC)
        VALUE(16, BE, SubBlockLength, "SubBlockLength", DEC)
        VALUE(8, BE, Status, "Status", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SEQ_END

    /* tSIM_SB_PLMN_INFO */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_PLMN_INFO")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_PLMN_INFO, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "Sub Block ID", DEC)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE(8, BE, Status, "Status", DEC)
        VALUE(8, BE, UserControlledPlmns, "UserControlledPlmns", DEC)
        VALUE(8, BE, OperatorControlledPlmns, "OperatorControlledPlmns", DEC)
        FILLER_EX(Padding, 8, 1)
    SEQ_END
    
    /* tSIM_SB_PREF_PLMN */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_PREF_PLMN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(tSIM_SB_PREF_PLMN, CREATE_STRUCT, "", "")
        VALUE(16, BE, SubBlockID, "Sub Block ID", DEC)
        VALUE(16, BE, SubBlockLength, "Sub Block Length", DEC)
        VALUE(8, BE, Status, "Status", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SEQ_END

    /* --------------------------------------------------------------------- */
    /* Sub blocks                                                            */ 
    /* --------------------------------------------------------------------- */

/*
    DER_CONST_TBL_BEGIN(SIM_SB_FILE_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_FILE_NOT_AVAILABLE)
    DER_CONST_TBL_END
*/
    /* --------------------------------------------------------------------- */
    /* Subblocks: SIM_CS_READ */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ACC") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This sub-block contains the Access Control Class")     
    SB_BEGIN(SIM_SB_ACC_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        SEQ_OF(ACCData, "ACC Data", AUTOGEN_SEQ_BYTE_HEX, SIM_ACC_CTRL_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_BCCH") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_BCCH_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(BCCHInfo, "BCCH information", AUTOGEN_SEQ_BYTE_HEX, SIM_BCCH_INFO_LEN)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_CARD_GENERATION, SIM_2G_3G_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_2G)
        DER_CONST_TBL_ENTRY(SIM_3G)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SB_CARD_TYPE, SIM_CARD_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_NORMAL_SIM)
        DER_CONST_TBL_ENTRY(SIM_TYPE_APPROVAL_SIM)
        DER_CONST_TBL_ENTRY(SIM_TEST_SIM)
        DER_CONST_TBL_ENTRY(SIM_NORMAL_SIM_SPE_FACILITY)
        DER_CONST_TBL_ENTRY(SIM_TYPE_APPROVAL_SIM_SPE_FACILITY)
        DER_CONST_TBL_ENTRY(SIM_MAINTENANCE)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Sub block: SIM_SB_ECC_ID                                                */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct tSIM_SB_ECC")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if SIM_ISI_MIN_VERSION(12,0)")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Status;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   NumberOfEccCodes;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccCodeLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccAlphaIdentifierLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccRecord;    /* First byte of array of tSIM_SB_ECC_RECORDs */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Status;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   NumberOfEccCodes;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EccCodeLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Padding;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Ecc;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif /* SIM_ISI_MIN_VERSION(12,0) */ ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_SB_ECC;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CARD_TYPE") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_CARD_TYPE_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(CardGeneration, "Card Generation", SIM_SB_CARD_GENERATION)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(CardType, "Card Type", SIM_SB_CARD_TYPE)
        FILLER_EX(Padding1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This sub-block contains the Emergency Control Codes.")
    SB_BEGIN(SIM_SB_ECC_ID, "", "012.000")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, NumberOfEccCodes, "NumberOfEccCodes", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 4)
        VALUE(8, BE, EccCodeLength, "ECC Code Length", DEC)
        FILLER_EX(Padding, 8, 1)
        VALUE(8, BE, Ecc, "ECC", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ECC_ID, "012.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfEccCodes, "NumberOfEccCodes", N)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 254)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 4)
        VALUE(8, BE, EccCodeLength, "ECC Code Length", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 251)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, EccAlphaIdentifierLength, "ECC Alpha ID Length", L)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of tSIM_SB_ECC_RECORDs")
        SEQ_OF_REF(EccRecord, "EccRecord", SIM_SB_ECC_RECORD, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_FORBIDDEN_PLMNS_FPLMN, SIM_PLMN_OPERATIONS_TABLE, "", "")    
        DER_CONST_TBL_ENTRY(PLMN_ADD)
        DER_CONST_TBL_ENTRY(PLMN_REMOVE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_FORBIDDEN_PLMNS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")  
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains the forbidden PLMNs")      
    SB_BEGIN(SIM_SB_FORBIDDEN_PLMNS_ID, "", "")
        REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID)
        REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(FPLMNListOperation, "FPLMN list operation", SIM_SB_FORBIDDEN_PLMNS_FPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 4)
        VALUE(16, BE, MaxNoOfFPLMNS, "Max No of FPLMNs", DEC)
        SEQ_OF_REF(fplmns, "fplmns", SIM_SB_FORBIDDEN_PLMNS_PLMN, REF_AS_MANY_AS_POSSIBLE,  ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_HPLMN") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")           
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains the Home PLMN")  
    SB_BEGIN(SIM_SB_HPLMN_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        VALUE(8, BE, NoOfDigitsInMNC, "No of digits in MNC", DEC)
        SEQ_OF(HPLMN, "HPLMN", AUTOGEN_SEQ_BYTE_HEX, SIM_HPLMN_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_HPLMN_SEARCH") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains the time interval between two searches for a higher priority PLMN.")  
    SB_BEGIN(SIM_SB_HPLMN_SEARCH_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, TimeInterval, "Time Interval", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_LAI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains Location Area Information from EFloci.")      
    SB_BEGIN(SIM_SB_LAI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")
        SEQ_OF(LAI, "LAI", AUTOGEN_SEQ_BYTE_HEX, SIM_LAI_LEN)
        FILLER_EX(Padding4, 8, 1)
        FILLER_EX(Padding5, 8, 1)
        FILLER_EX(Padding6, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_LOC_UPD_STATUS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains Location update status from EFloci.")      
    SB_BEGIN(SIM_SB_LOC_UPD_STATUS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")      
        VALUE(8, BE, LocationUpdateStatus, "Location Update Status", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_OPERATOR_PLMNS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_OPERATOR_PLMN_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, OPLMNListOperation, "OPLMNListOperation", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfOPLMNS, "MaxNoOfOPLMNS", DEC)    
        SEQ_OF_REF(oplmns, "oplmns", SIM_SB_OPERATOR_PLMNS_PLMN, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_USER_PLMN_UPLMN, SIM_PLMN_OPERATIONS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(PLMN_ADD)
        DER_CONST_TBL_ENTRY(PLMN_REMOVE)
    DER_CONST_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_USER_PLMNS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains User Controlled PLMNs from EFplnmwact.")
    SB_BEGIN(SIM_SB_USER_PLMN_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(UPLMNListOperation, "UPLMNListOperation", SIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfUPLMNS, "MaxNoOfUPLMNS", DEC)    
        SEQ_OF_REF(uplmns, "uplmns", SIM_SB_OPERATOR_PLMNS_PLMN, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)                
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_HOME_PLMNS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains Home PLMNs from EFhplnmwact.")
     SB_BEGIN(SIM_SB_HOME_PLMN_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(HPLMNListOperation, "HPLMNListOperation", SIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        VALUE(16, BE, MaxNoOfHPLMNS, "MaxNoOfHPLMNS", DEC)    
        SEQ_OF_REF(hplmns, "hplmns", SIM_SB_OPERATOR_PLMNS_PLMN, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Sub block: SIM_SB_EQUIVALENT_HPLMNS_ID                                  */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct tSIM_SB_EQUIVALENT_HPLMNS")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  SubBlockLength;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Status;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Padding1;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16  NoEHPLMNs;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EHPLMNRecord; /* First byte of array of tSIM_SB_PLMN_RECORD */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_SB_EQUIVALENT_HPLMNS;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_PLMN_SELECTOR") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_PLMN_SELECTOR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(PLMNSelListOperation, "PLMNSelListOperation", SIM_SB_USER_PLMN_UPLMN)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 8)
        VALUE(16, BE, MaxNoOfPLMNS, "MaxNoOfPLMNS", DEC)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of tSIM_SB_PLMN_RECORD")
        SEQ_OF_REF(PLMNRecord, "PLMNRecord", SIM_SB_PLMN_RECORD, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)        
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ATT_RAT") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_ATT_RAT_ID, "017.006", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "AT&T RAT mode settings from EFrat.")
        VALUE_CONST(ATT_RAT_mode, "AT&T RAT mode", SIM_ATT_RAT_MODE)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_EQUIVALENT_HPLMNS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        VALUE(16, BE, NoEHPLMNs, "NoEHPLMNs", DEC)
        COMMENT(COMMENT_PARAGRAPH, "First byte of array of tSIM_SB_PLMN_RECORD")
        SEQ_OF_REF(EHPLMNRecord, "EHPLMNRecord", SIM_SB_PLMN_RECORD, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)        
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_RPLMN") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_RPLMN_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SEQ_OF(RPLMNLastUsedAT, "RPLMN Access Technology ID", AUTOGEN_SEQ_BYTE_HEX, RPLMN_LAST_USED_AT_LEN)
        FILLER_EX(Pad4, 8, 1)
        FILLER_EX(Pad5, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_GSM_NETPAR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, FileSize, "File size", DEC)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, DataLength, "Length of Data", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_FDD_NETPAR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, FileSize, "File size", DEC)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, DataLength, "Length of Data", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_TDD_NETPAR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, FileSize, "File size", DEC)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, DataLength, "Length of Data", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_IMSI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_IMSI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, LengthOfIMSI, "Length of IMSI", DEC)
        VALUE(8, BE, NoOfDigitsInMNC, "No of digits in MNC", DEC)
        FILLER_EX(Padding, 8, 1)
        SEQ_OF(IMSI, "IMSI",AUTOGEN_SEQ_BYTE_HEX, SIM_IMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_TMSI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock contains Temporary Mobile Subscriber Identity from EFloci.")      
    SB_BEGIN(SIM_SB_TMSI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Coded according to 3GPP TS 31.102.")
        SEQ_OF(TMSI, "TMSI",AUTOGEN_SEQ_BYTE_HEX, SIM_TMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_CIPHERING_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_GPRS_CIPHERING_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(GprsCipheringKey, "GPRS ciphering key", AUTOGEN_SEQ_BYTE_HEX, SIM_GPRS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_CIPHERING_KEY_SNR") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, GprsCipheringKeySNR, "GPRS ciphering key sequence number", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_RAI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_GPRS_RAI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(Rai, "Rai", AUTOGEN_SEQ_BYTE_HEX, SIM_RAI_LEN)
        FILLER_EX(Padding4, 8, 1)
        FILLER_EX(Padding5, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_RAUS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_GPRS_RAUS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, GprsRaus, "GPRS RAUS", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_TMSI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_GPRS_TMSI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(GprsTMSI, "GprsTMSI", AUTOGEN_SEQ_BYTE_HEX, SIM_GPRS_TMSI_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GPRS_TMSI_SIGN_VALUE") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")         
    SB_BEGIN(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID, "", "")
        SIM_SB_16_LONG    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        SEQ_OF(GprsTMSISignatureValue, "GPRS_TMSI signature value", AUTOGEN_SEQ_BYTE_HEX, SIM_GPRS_TMSI_SIGN_VAL_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CIPHERING_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_CIPHERING_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(CipheringKey, "Ciphering key", AUTOGEN_SEQ_BYTE_HEX, SIM_CIPH_KEY_LEN)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_CIPHERING_KEY_SNR_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_3G_GSM_NOT_SUPPORTED)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CIPHERING_KEY_SNR") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_CIPHERING_KEY_SNR_ID, "", "")
        SIM_SB_16_LONG                
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_CIPHERING_KEY_SNR_STATUS)
        VALUE(8, BE, CipheringKeySequenceNumber, "Ciphering key sequence number", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_CS_KSI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_CS_KSI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, CsKsi, "The key set identifier", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_CS_CIPHERING_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_CS_CIPHERING_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(CsCipheringKey, "Cs ciphering key", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_CS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_CS_INTEGRITY_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(CsIntegrityKey, "Cs integrity key", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_CS_INTE_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_EAP_CIPHERING_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_EAP_CIPHERING_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(EAPCipheringKey, "EAP ciphering key", AUTOGEN_SEQ_BYTE_HEX, SIM_EAP_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_EAP_INTEGRITY_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_EAP_INTEGRITY_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(EAPIntegrityKey, "EAP integrity key", AUTOGEN_SEQ_BYTE_HEX, SIM_EAP_INTE_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_PS_KSI") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_PS_KSI_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        VALUE(8, BE, PsKsi, "key set identifier", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_PS_CIPHERING_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_PS_CIPHERING_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(PsCipheringKey, "Ps ciphering key", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_PS_CIPH_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_PS_INTEGRITY_KEY") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(PsIntegrityKey, "UMTS integrity key", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_PS_INTE_KEY_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_START_PS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_START_PS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        SEQ_OF(Hfn, "Hfn", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_PS_HFN_LEN)
    SB_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_START_CS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_START_CS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        SEQ_OF(Hfn, "Hfn", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_CS_HFN_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_START_MAX") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_UMTS_START_MAX_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        SEQ_OF(StartMax, "Maximum value of START_CS or START_PS", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_START_MAX_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_PHONE_NUMBER_FIELD_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PHONE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, NumLen, "NumLen", N)
        FILLER_EX(padding1, 8, 1)   
        FILLER_EX(padding2, 8, 1)   
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END
       
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_SMS_DEST_ADR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PHONE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, NumLen, "NumLen", N)
        FILLER_EX(padding1, 8, 1)   
        FILLER_EX(padding2, 8, 1)   
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SB_BEGIN(SIM_SB_SMSC_ADR_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PHONE_STATUS)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(8, BE, NumLen, "NumLen", N)
        FILLER_EX(padding1, 8, 1)   
        FILLER_EX(padding2, 8, 1)   
        SEQ_OF_REF(Num, "Number", AUTOGEN_SEQ_WORD_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_ICC_TYPE_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SB_ICC_CARD_GENERATION, SIM_2G_3G_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_2G_GSM)
        DER_CONST_TBL_ENTRY(SIM_2G_WIM)
        DER_CONST_TBL_ENTRY(SIM_3G)
        DER_CONST_TBL_ENTRY(SIM_ICC_TYPE_UNKNOWN)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ICC_TYPE") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ICC_TYPE_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_ICC_TYPE_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(CardGeneration, "Card Generation", SIM_SB_ICC_CARD_GENERATION)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_AID_ID_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AID") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AID_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AID_ID_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(8, BE, AIDLength, "AID Length", L)
        COMMENT(COMMENT_PARAGRAPH, "First byte AID array with AID LENGTH incl. padding")
        SEQ_OF_REF(AID, "AID", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_ICCID_ID_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_FILE_NOT_AVAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ICCID") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ICCID_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_ICCID_ID_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(IccID, "IccID", AUTOGEN_SEQ_BYTE_HEX, ICCID_LENGTH)
        FILLER_EX(Padding4, 8, 1)
        FILLER_EX(Padding5, 8, 1)
    SB_END 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_REFRESH_FILE") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_REFRESH_FILE_ID, "", "")
        SIM_SB_16_LONG
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, DataLength, "Length of the file path", L)
        SEQ_OF_REF(FilePath, "Path of elementary file starting from the MF", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)        
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ICON_DATA") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ICON_DATA_ID, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Width, "Width of image instance in raster image points", DEC)
        VALUE(16, BE, Height, "Height of image instance in raster image points", DEC)
        VALUE(8, BE, Depth, "Color depth of image instance in bits per raster image point", DEC)        
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        VALUE(32, BE, CM_Source_instance, "CM_source id of image instances", DEC)        
        VALUE(32, BE, CM_Source_category, "CM_source category of image instance", DEC)        
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ICON_DATA_CLUT") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ICON_DATA_CLUT_ID, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Width, "Width of image instance in raster image points", DEC)
        VALUE(16, BE, Height, "Height of image instance in raster image points", DEC)
        VALUE(8, BE, Depth, "Color depth of image instance in bits per raster image point", DEC)        
        VALUE(8, BE, NumberOfCLUT, "Number of CLUT entries", DEC)        
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "The color lookup table data. Length is NumberOfClut*3 + filler")
        SEQ_OF_REF(CLUT, "CLUT", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
        /* FILLER(FILLER_VARIABLE, 32) */
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_ICON_BODY_DATA") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_ICON_BODY_DATA_ID, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Width, "Width of image instance in raster image points", DEC)
        VALUE(16, BE, Height, "Height of image instance in raster image points", DEC)
        VALUE(8, BE, Depth, "Color depth of image instance in bits per raster image point", DEC)        
        VALUE(8, BE, NumberOfCLUT, "Number of CLUT entries", DEC)        
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "The icon data. Length is (With*Height*Depth/8) + filler")
        SEQ_OF_REF(IconBodyData, "IconBodyData", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_ANYSIZE)
        /* FILLER(FILLER_VARIABLE, 32) */
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_NETWORK_NAME_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
    DER_CONST_TBL_END

/* CS has been asked whether they use this or not. No answer yet. */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_FULL_NETWORK_NAME") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_FULL_NETWORK_NAME, "", "")
        REFERENCE(16, BE, SubblockID, "Sub Block ID", SB_ID)
        REFERENCE(16, BE, Subblock_length, "Sub Block Length", SB_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE_CONST(Status, "Status", SIM_SB_NETWORK_NAME_STATUS) 
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        REFERENCE(8, BE, Full_name_length, "Full name for network length", N)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        SEQ_OF_REF(Full_name, "Full name for network", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding, 8, 1)
    SB_END

/* CS has been asked whether they use this or not. No answer yet. */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SHORT_NETWORK_NAME") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SHORT_NETWORK_NAME, "", "")
        REFERENCE(16, BE, SubblockID, "Sub Block ID", SB_ID)
        REFERENCE(16, BE, Subblock_length, "Sub Block Length", SB_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE_CONST(Status, "Status", SIM_SB_NETWORK_NAME_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        REFERENCE(8, BE, Short_name_length, "Short name for network length", N)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        SEQ_OF_REF(Short_name, "Short name for network", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding, 8, 1)
    SB_END
    
    DER_CONST_TBL_BEGIN(SIM_SB_UMTS_FAIL_PARAMS_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_MAC_FAIL)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_SYNCH_FAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_AUTN_FAIL_PARAMS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_UMTS_FAIL_PARAMS_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        VALUE(8, BE, LengthOfAUTS, "LengthOfAUTS", DEC)
        SEQ_OF(AutsParams, "AutsParams", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_AUTS_PARAMS_LEN)
        FILLER_EX(Padding3, 8, 1)
        FILLER_EX(Padding4, 8, 1)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_PARAMS_STATUS, SIM_SB_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SB_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_3G_GSM_NOT_SUPPORTED)
        DER_CONST_TBL_ENTRY(SIM_SB_STA_PS_NOT_SUPPORTED)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_RES_PARAMS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_RES_PARAMS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        VALUE(8, BE, LengthOfRes, "LengthOfRes", DEC)
        SEQ_OF(RES, "RES", AUTOGEN_SEQ_BYTE_HEX, SIM_RES_MAX_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_RAND_PARAMS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_RAND_PARAMS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT(COMMENT_PARAGRAPH, "The status field can not be used, because "
        "this subblock is only used in requests. Default value = 0xFF.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(Rnd, "Random parameters", AUTOGEN_SEQ_BYTE_HEX, SIM_RND_PARAMS_LEN)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UMTS_AUTN_PARAMS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_UMTS_AUTN_PARAMS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT(COMMENT_PARAGRAPH, "The status field can not be used, because "
        "this subblock is only used in requests. Default value = 0xFF.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SEQ_OF(AutnParams, "AUTN Parameters", AUTOGEN_SEQ_BYTE_HEX, SIM_UMTS_AUTN_PARAMS_LEN)
    SB_END
     
    DER_CONST_TBL_BEGIN(SIM_SB_APP_SELECTION_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_APP_SELECTION") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_APP_SELECTION, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        VALUE(8, BE, ApplicationNumber, "Application number", DEC)
        REFERENCE(8, BE, Length, "Length", L)
        FILLER_EX(Padding1, 8, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        STRING_REF(STRING_ASCII, BE, Label, "Label", L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_SB_APP_SELECTION_TYPE, SIM_SB_APP_SELECTION_TYPE_DEF_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_USIM_APPLICATION)
        DER_CONST_TBL_ENTRY(SIM_ISIM_APPLICATION)
        DER_CONST_TBL_ENTRY(SIM_UNKNOWN_APPLICATION)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_APP_SELECTION_UNICODE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_APP_SELECTION_UNICODE, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        VALUE(8, BE, ApplicationNumber, "Application number", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ApplicationType, "Application type", SIM_SB_APP_SELECTION_TYPE)
        REFERENCE(8, BE, Length, "Length", L)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Label, "Label", L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* Subblocks for SMS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_ADDRESS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_ADDRESS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(AddressType, "Address Type", SIM_ADDRESS_TYPE_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 12)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        SEQ_OF_REF(AddressData, "AddressData", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_COMMON_DATA")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_COMMON_DATA_ID, "", "")
        SIM_SB_16_LONG
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        VALUE(8, BE, CharacterAmount, "CharacterAmount", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 248)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_VALIDITY_PERIOD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_VALIDITY_PERIOD_ID, "", "")
        SIM_SB_16_LONG
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        SEQ_OF_REF(ValidityPeriodData, "ValidityPeriodData", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_DELIVER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_DELIVER_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "MessageParameters", DEC)
        VALUE(8, BE, ProtocolID, "ProtocolID", DEC)
        VALUE(8, BE, DataCodingScheme, "DataCodingScheme", DEC)
        FILLER_EX(Pad1, 8, 1)
        SEQ_OF(SCTimeStamp, "SCTimeStamp", AUTOGEN_SEQ_BYTE_HEX, SIM_SMS_TIME_STAMP_LEN)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMON_DATA_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_STATUS_REPORT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_STATUS_REPORT_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "MessageParameters", DEC)
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        VALUE(8, BE, SMSStatus, "SMSStatus", DEC)
        FILLER_EX(Pad1, 8, 1)
        SEQ_OF(SCTimeStamp, "SCTimeStamp", AUTOGEN_SEQ_BYTE_HEX, SIM_SMS_TIME_STAMP_LEN)
        FILLER_EX(Pad2, 8, 1)
        SEQ_OF(DischargeTime, "DischargeTime", AUTOGEN_SEQ_BYTE_HEX, SIM_SMS_TIME_STAMP_LEN)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
        SB_LST_REF_END
    SB_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_SUBMIT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 2048)
    SB_BEGIN(SIM_SB_SMS_SUBMIT_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "MessageParameters", DEC)
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        VALUE(8, BE, ProtocolID, "ProtocolID", DEC)
        VALUE(8, BE, DataCodingScheme, "DataCodingScheme", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMON_DATA_ID)
            SB_LST_ENTRY(SIM_SB_SMS_VALIDITY_PERIOD_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_COMMAND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_COMMAND_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "MessageParameters", DEC)
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        VALUE(8, BE, ProtocolID, "ProtocolID", DEC)
        VALUE(8, BE, CommandType, "CommandType", DEC)
        VALUE(8, BE, MessageNumber, "MessageNumber", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMON_DATA_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_MO_UNDEFINED")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_MO_UNDEFINED_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "MessageParameters", DEC)
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMON_DATA_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SMS_MT_UNDEFINED")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_SMS_MT_UNDEFINED_ID, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, MessageParameters, "Message Parameters", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_ADDRESS_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMON_DATA_ID)
        SB_LST_REF_END
    SB_END

    /* Subblocks for Releas 4 features */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SPN_DISPLAY_INFO_PLMNS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 4096)
    SB_BEGIN(SIM_SB_SPN_DISPLAY_INFO_PLMNS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        REFERENCE(16, BE, NoOfPLMNs, "No of PLMNs", N)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        SEQ_OF_REF(plmns, "plmns", SIM_SB_SPN_DISPLAY_INFO_PLMNS_PLMN, N, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CPHS_MSG_FLAGS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_CPHS_MSG_FLAGS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
    	COMMENT(COMMENT_TEXT, "Coding:")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x05: No messages is waiting.")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x0A: Message is waiting.")
	VALUE(8, BE, VoiceLine1, "VoiceLine1", DEC)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
    	COMMENT(COMMENT_TEXT, "Coding:")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x05: No messages is waiting.")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x0A: Message is waiting.")
        VALUE(8, BE, VoiceLine2, "VoiceLine2", DEC)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
    	COMMENT(COMMENT_TEXT, "Coding:")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x05: No messages is waiting.")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x0A: Message is waiting.")
        VALUE(8, BE, Fax, "Fax", DEC)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
    	COMMENT(COMMENT_TEXT, "Coding:")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x05: No messages is waiting.")
    	COMMENT(COMMENT_NEWLINE, "")
    	COMMENT(COMMENT_BULLET, "0x0A: Message is waiting.")
        VALUE(8, BE, Data, "Data", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_REL4_MSG_FLAGS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    SB_BEGIN(SIM_SB_REL4_MSG_FLAGS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Subscriber profile number. Only profile no.1 is supported.")
	VALUE(8, BE, ProfileNo, "ProfileNo", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Status of Message Waiting Indication for Voicemail.")
	VALUE(8, BE, VoiceStatus, "VoiceStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Number of Voicemail messages waiting.")
	VALUE(8, BE, VoiceMessages, "VoiceMessages", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Status of Message Waiting Indication for Fax.")
	VALUE(8, BE, FaxStatus, "FaxStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Number of Fax messages waiting.")
	VALUE(8, BE, FaxMessages, "FaxMessages", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Status of Message Waiting Indication for Email.")
	VALUE(8, BE, EmailStatus, "EmailStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Number of Email messages waiting.")
	VALUE(8, BE, EmailMessages, "EmailMessages", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Status of Message Waiting Indication for other.")
	VALUE(8, BE, OtherStatus, "OtherStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Number of other messages waiting.")
	VALUE(8, BE, OtherMessages, "OtherMessages", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CPHS_CALL_FWD_FLAGS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
    COMMENT(COMMENT_TEXT, "Subblock contains CPHS file '6F13'.")
    SB_BEGIN(SIM_SB_CPHS_CALL_FWD_FLAGS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Voice Call Forwarding Unconditional flag for line1.")
        VALUE(8, BE, VoiceLine1, "VoiceLine1", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Voice Call Forwarding Unconditional flag for line2.")
	VALUE(8, BE, VoiceLine2, "VoiceLine2", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Voice Call Forwarding Unconditional flag.")
	VALUE(8, BE, Fax, "Fax", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Data Call Forwarding Unconditional flag.")
	VALUE(8, BE, Data, "Data", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_REL4_CALL_FWD_FLAGS") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")        
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFcfis '6FCB'. Coding see 3GPP TS 31.102. ")
    SB_BEGIN(SIM_SB_REL4_CALL_FWD_FLAGS_ID, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Subscriber profile. Profile no.1 is supported only.")
        VALUE(8, BE, ProfileNo, "ProfileNo", DEC)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Voice CFU indicator status.")
	VALUE(8, BE, VoiceStatus, "VoiceStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "FAX CFU indicator status.")
        VALUE(8, BE, FaxStatus, "FaxStatus", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Data CFU indicator status.")
        VALUE(8, BE, DataStatus, "DataStatus", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)	    
	COMMENT(COMMENT_TEXT, "Dialling number.")
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Subblocks; SIM_PB */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_INFO_REQUEST, "", "")
        SIM_SB_16_LONG
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_MAX_NUMBER_OF_TAGS)
        REFERENCE(8, BE, NumberOfTags, "NumberOfTags", N)
        FILLER_EX(Filler1, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SEQ_OF_REF(Tags, "Tags", SIM_PB_TAG, N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_LOCATION, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(LocationType, "Location Type", SIM_PB_LOCATION_TYPE)
        VALUE(16, BE, Location, "Location", DEC) 
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_LOCATION_SEARCH, "", "")
        SIM_SB_16_LONG
        VALUE_CONST(LocationType, "Location Type", SIM_PB_LOCATION_TYPE)
        VALUE(16, BE, Location, "Location", DEC) 
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_ADN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_NUMBER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_ANR, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", N)
        VALUE(8, BE, AASNumber, "AASNumber", DEC)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_BDN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CC, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Data, "Data", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CCP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CCP, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        COMMENT(COMMENT_PARAGRAPH, "the CCP data in raw format")
        SEQ_OF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, 14)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_EMAIL, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_TEXT_LEN)
        REFERENCE(8, BE, TextLength, "TextLength", N)
        FILLER_EX(Filler1, 8, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Text, "Text", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_FDN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_FDN_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_FDN_ENABLED)
        DER_CONST_TBL_ENTRY(SIM_FDN_DISABLED)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_FDN_LIST_STATUS, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Data, "Data", SIM_FDN_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_GAS, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_TEXT_LEN)
        REFERENCE(8, BE, TextLength, "TextLength", TEXT_LEN)
        FILLER_EX(Filler, 8, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Text, "Text", TEXT_LEN, ISIHDR_RESERVE_SPACE)
           FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_GROUP_LOCATIONS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_GRP, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, LocationGRP, "LocationGRP", DEC)
        SEQ_OF(LocationGAS, "LocationGAS", AUTOGEN_SEQ_WORD_HEX, 10)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_HIDDEN, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, Data, "Data", DEC)
        FILLER_EX(Filler, 8, 3)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_MSISDN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_UINT32")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_PSC, "", "")
        SIM_SB_16_LONG
        VALUE(32, BE, Data, "Data", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_SDN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_SNE, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_TEXT_LEN)
        REFERENCE(8, BE, TextLength, "TextLength", N)
        FILLER_EX(Filler1, 8, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Text, "Text", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_STATUS, "", "")
        SIM_SB_16_LONG
        VALUE_CONST(Status, "Status", SIM_PB_STATUS_TABLE)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_UID, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Data, "Data", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_VMBX, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_MBDN, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY(PROPERTY_PMD_PARAMETER)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NAME_LEN)
        REFERENCE(8, BE, NameLength, "NameLength", NAME_LEN)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_NUMBER_LEN)
        REFERENCE(8, BE, NumberLength, "NumberLength", NUM_LEN)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Name, "Name", NAME_LEN, ISIHDR_RESERVE_SPACE)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Number, "Number", NUM_LEN, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_AAS, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Location, "Location", DEC)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_TEXT_LEN)
        REFERENCE(8, BE, TextLength, "TextLength", N)
        FILLER_EX(Filler1, 8, 1)
        STRING_REF(STRING_UNICODE_ZERO_TERMINATED, BE, Text, "Text", N, ISIHDR_RESERVE_SPACE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_STARTUP_PHASE_1, "", "")
        SIM_SB_16_LONG
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_STARTUP_PHASE_2, "", "")
        SIM_SB_16_LONG
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_STARTUP_PHASE_3, "", "")
        SIM_SB_16_LONG
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_DELETE_ALL, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, Data, "Data", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_DELETE_LOCATION, "", "")
        SIM_SB_16_LONG
        VALUE_CONST(LocationType, "Location Type", SIM_PB_LOCATION_TYPE)
        VALUE(16, BE, Location, "Location", DEC) 
    SB_END

    DER_CONST_TBL_BEGIN(SIM_PB_PRESENCE_STATUS, SIM_PRESENCE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_NONE)
        DER_CONST_TBL_ENTRY(SIM_PUBLIC)
        DER_CONST_TBL_ENTRY(SIM_PRIVATE)
        DER_CONST_TBL_ENTRY(SIM_BOTH)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_PH_1")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_PH_1, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, Generation, "Generation", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(FdnListStatus, "FdnListStatus", SIM_FDN_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(PbPresence, "PbPresence", SIM_PB_PRESENCE_STATUS)
        VALUE(8, BE, PBRCountPub, "PBRCountPUB", DEC)
        VALUE_CONST(SyncSupportPub, "SyncSupportPub", TRUE_FALSE)
        FILLER_EX(Filler1, 8, 1)
        VALUE(16, BE, PSCPub, "PSCPub", DEC)
        VALUE(16, BE, CCPub, "CCPub", DEC)
        VALUE_CONST(PBC2GChangedPub, "PB2GChangedPub", TRUE_FALSE)
        VALUE(8, BE, PBRCountPriv, "PBRCountPriv", DEC)
        VALUE_CONST(SyncSupportPriv, "SyncSupportPriv", TRUE_FALSE)
        FILLER_EX(Filler2, 8, 1)
        VALUE(16, BE, PSCPriv, "PSCPriv", DEC)
        VALUE(16, BE, CCPriv, "CCPriv", DEC)
        VALUE_CONST(PBC2GChangedPriv, "PBC2GChangedPriv", TRUE_FALSE)
        FILLER_EX(Filler3, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_ADN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_ADN_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileLength, "FileLength", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, NumberLength, "NumberLength", DEC)
        VALUE(8, BE, ADNAccessStatusWhenFDNIsEnabled, "ADNAccessStatusWhenFDNIsEnabled", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_LONG_ADN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_ADN_LONG_SB, "014.008", "")
        SIM_SB_16_LONG
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, NumberLength, "NumberLength", DEC)
        VALUE(8, BE, ADNAccessStatusWhenFDNIsEnabled, "ADNAccessStatusWhenFDNIsEnabled", DEC)
        FILLER_EX(Filler, 8, 3)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_SNE_SB, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE(8, BE, FileType, "FileType", DEC)    
        VALUE(8, BE, FileLength, "FileLegnth", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        FILLER_EX(Filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_SNE_LONG_SB, "", "")
        SIM_SB_16_LONG
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, Type1FilesPerAdn, "Type1FilesPerAdn", DEC)
        VALUE(8, BE, Type2FilesPerAdn, "Type2FilesPerAdn", DEC)
        FILLER_EX(Filler, 8, 3)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_ANR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_ANR_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileType, "FileType", DEC)
        VALUE(8, BE, FileLength, "FileLegnth", DEC)
        VALUE(8, BE, NumberLength, "NumberLength", DEC)
        FILLER_EX(Filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_LONG_ANR")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_ANR_LONG_SB, "014.017", "")
        SIM_SB_16_LONG
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, NumberLength, "NumberLength", DEC)
        VALUE(8, BE, Type1FilesPerAdn, "Type1FilesPerAdn", DEC)
        VALUE(8, BE, Type2FilesPerAdn, "Type2FilesPerAdn", DEC)
        FILLER_EX(Filler1, 8, 3)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_GRP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_GRP_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, NumberOfGroups, "NumberOfGroups", DEC)
        FILLER_EX(Filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_LONG_GRP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_GRP_LONG_SB, "014.017", "")
        SIM_SB_16_LONG
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, NumberOfGroups, "NumberOfGroups", DEC)
        VALUE(8, BE, Type1FilesPerAdn, "Type1FilesPerAdn", DEC)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_AAS_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileType, "FileType", DEC)    
        VALUE(8, BE, FileLength, "FileLegnth", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        FILLER_EX(Filler1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_GAS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_GAS_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileLength, "FileLength", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_EMAIL_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileType, "FileType", DEC)    
        VALUE(8, BE, FileLength, "FileLegnth", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        FILLER_EX(Filler, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_EMAIL_LONG_SB, "014.017", "")
        SIM_SB_16_LONG
        VALUE(16, BE, EntryCount, "EntryCount", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, Type1FilesPerAdn, "Type1FilesPerAdn", DEC)
        VALUE(8, BE, Type2FilesPerAdn, "Type2FilesPerAdn", DEC)
        FILLER_EX(Filler, 8, 3)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_MISC")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_MISC_SB, "", "")
        SIM_SB_16_LONG
        VALUE_CONST(PresenceOf_EXT1, "PresenceOf_EXT1", TRUE_FALSE)
        VALUE_CONST(PresenceOf_CC, "PresenceOfCC", TRUE_FALSE)
        VALUE_CONST(PresenceOf_UID, "PresenceOf_UID", TRUE_FALSE)
        VALUE_CONST(PresenceOf_PUID, "PresenceOf_PUID", TRUE_FALSE)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_FDN")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_FDN_SB, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, FileLength, "FileLength", DEC)
        VALUE(8, BE, TextLength, "TextLength", DEC)
        VALUE(8, BE, NumberLength, "NumberLength", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(FdnListStatus, "FdnListStatus", SIM_FDN_STATUS)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_PB_CONF_CONDITION, SIM_ACCESS_CONDITION_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_PIN1)
        DER_CONST_TBL_ENTRY(SIM_ADM)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONF_PH_3")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_CONF_PH_3, "", "")
        SIM_SB_16_LONG
        VALUE(8, BE, SDN_NumberOf, "SDN NumberOf", DEC)
        VALUE(8, BE, SDN_NameLength, "SDN NameLength", DEC)
        VALUE(8, BE, SDN_NumberLength, "SDN NumberLength", DEC)
        VALUE(8, BE, BDN_NumberOf, "BDN NumberOf", DEC)
        VALUE(8, BE, BDN_NameLength, "BDN NameLength", DEC)
        VALUE(8, BE, BDN_NumberLength, "BDN NumberLength", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(MSISDN_AccessCondition, "MSISDN AccessCondition", SIM_PB_CONF_CONDITION)
        VALUE(8, BE, MSISDN_Number_of, "MSISDN NumberOf", DEC)
        VALUE(8, BE, MSISDN_NameLength, "MSISDN NameLength", DEC)
        VALUE(8, BE, MSISDN_NumberLength, "MSISDN NumberLength", DEC)
        VALUE(8, BE, VMBX_Number_of, "VMBX NumberOf", DEC)
        VALUE(8, BE, VMBX_NameLength, "VMBX NameLength", DEC)
        VALUE(8, BE, VMBX_NumberLength, "VMBX NumberLength", DEC)
        VALUE(8, BE, MBDN_NumberOfProfiles,"MBDN_NumberOfProfiles", DEC)
        VALUE(8, BE, MBDN_NumberOf,        "MBDN_NumberOf", DEC)
        VALUE(8, BE, MBDN_NameLength,      "MBDN_NameLength", DEC)
        VALUE(8, BE, MBDN_NumberLength,    "MBDN_NumberLength", DEC)
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
        FILLER_EX(Filler3, 8, 1)
    SB_END

    DER_CONST_TBL_BEGIN(SIM_PB_SELECT_PB_PB, SIM_PRESENCE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_PUBLIC)
        DER_CONST_TBL_ENTRY(SIM_PRIVATE)        
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_SELECT_PB")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_PB_SELECT_PB_SB, "", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Phonebook, "Phonebook", SIM_PB_SELECT_PB_PB)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(SlowSyncNeeded, "SlowSyncNeeded", TRUE_FALSE)
        FILLER_EX(Filler1, 8, 1)
        FILLER_EX(Filler2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_MMS_CONNECTIVITY_PARAMETERS")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "MMS connectivity TLV parameter from EFmmsicp.") 
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 0xFFFF)       
    SB_BEGIN(SIM_SB_MMS_CONNECTIVITY_PARAMETERS_ID, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "8+N+padding")
        REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
	REFERENCE(16, BE, DataLength, "Data Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "One MMS connectivity TLV parameter.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_MMS_USER_PREFERENCES")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "MMS user preference TLV object from EFmmsup on (U)SIM.")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 0xFFFF)
    SB_BEGIN(SIM_SB_MMS_USER_PREFERENCES_ID, "", "")
        PROPERTY(PROPERTY_PMD_PARAMETER)
        REFERENCE(16, BE, SubBlockID, "Sub Block ID", SB_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "8+N+padding")
        REFERENCE(16, BE, SubBlockLength, "Sub Block Length", SB_LENGTH)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(16, BE, DataLength, "Data Length", N)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "One MMS user preference TLV object.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_IMS_PRIVATE_USER_ID") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_IMS_PRIVATE_USER_ID, "", "")
        SIM_SB_16_LONG
        REFERENCE(8, BE, DataLength, "Data Length", L)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SEQ_OF_REF(IMSPrivateUserID, "IMS Private User ID", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_IMS_PUBLIC_USER_ID") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_IMS_PUBLIC_USER_ID, "", "")
        SIM_SB_16_LONG
        REFERENCE(8, BE, DataLength, "Data Length", L)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SEQ_OF_REF(IMSPublicUserID, "IMS Public User ID", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID, "", "")
        SIM_SB_16_LONG
        REFERENCE(8, BE, DataLength, "Data Length", L)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SEQ_OF_REF(IMSHomeNwNameID, "IMS Home Nw Name ID", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_CONNECTION") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_CONNECTION_ID, "", "")
        SIM_SB_16_LONG
        VALUE(16,BE, ObjectID, "ObjectID", DEC)
        VALUE_CONST(DeviseID, "DeviseID", PN_DEVICE)
        FILLER_EX(Padding, 8, 1)
    SB_END

    /* --------------------- Application Management Subblocks -------------- */

    /* --------------------------------------------------------------------- */
    /* Subblock status                                                       */
    /* --------------------------------------------------------------------- */

    DER_CONST_TBL_BEGIN(SIM_SB_AM_STA_STATUS, SIM_SB_STA_TABLE, "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SB_STA_OK,        "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SB_STA_NOT_OK,    "017.003", "")
    DER_CONST_TBL_END

    /* Application Management Handle  START                                  */
    /* --------------------------------------------------------------------- */

    /* ----------  NOTICE: From v018.000 the sim_sb_am_handle has been moved to sim_shared_isi_m.h ---------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE_TYPE, 8, BE, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is	available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      0,  "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is not available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  1,  "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "is not available, e.g. could be loss of contact to the card.")
	  CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,         0x24,  "017.003", "018.000")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE_TYPE_2, 8, BE, "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is	available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      0,  "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The requested NAA application service is not available.")
	  CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  1,  "018.000", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "is not available, e.g. could be loss of contact to the card.")
	  CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,         0x24,  "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE, SIM_SERVICE_STATUS_TABLE_TYPE, "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "017.003", "018.000")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVICE_STATUS_TABLE_2, SIM_SERVICE_STATUS_TABLE_TYPE_2, "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_AVAILABLE,      "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_APP_SERVICE_NOT_AVAILABLE,  "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "018.000", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AM_APP_TYPE_TABLE_TYPE, 8, BE, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 2G ICC SIM (TS 51.011)  aka 2G SIM")
	 CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_ICC_SIM,      0, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 3G UICC USIM (TS 31.102)  aka 3G USIM")
         CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_USIM,    1, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application is of type 3G UICC ISIM (TS 31.103)  aka 3G ISIM")
         CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_ISIM,    2, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information is not available, e.g. could be loss of contact to the card")
         CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,   0x24, "017.003", "018.000")
    CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_AM_APP_STATUS_TABLE_TYPE, 8, BE, "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application Management API is ready for usage")
        CONST_TBL_ENTRY_VER(SIM_AM_READY,                    0,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application selection procedure has been executed successful.")
        CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_SUCCESS,     1,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application selection procedure has failed.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_FAIL,        2,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application has stopped initialisation procedure due to needed user verification procedure (PIN verification needed).")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_USR_VERIFY_REQUIRED,  3,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA application has done successful selection and initialisation procedure and is ready for usage.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_READY,                4,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAA Application has done successful application closure and no further access is possible.")   
	CONST_TBL_ENTRY_VER(SIM_AM_APP_TERMINATE,            5,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Permanent error. NAA application is dysfunctional.")        
	CONST_TBL_ENTRY_VER(SIM_AM_APP_ERROR,                6,    "017.003", "018.000")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Information is not available, e.g. could be loss of contact to the card.")      
	CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,      0x24,    "017.003", "018.000")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_AM_APP_STATUS_TABLE, SIM_AM_APP_STATUS_TABLE_TYPE, "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_READY,                       "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_SUCCESS,        "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ACTIVATE_FAIL,           "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_USR_VERIFY_REQUIRED,     "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_READY,                   "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TERMINATE,               "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_ERROR,                   "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "017.003", "018.000")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_AM_APP_TYPE_TABLE, SIM_AM_APP_TYPE_TABLE_TYPE, "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_ICC_SIM,    "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_USIM,  "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_AM_APP_TYPE_UICC_ISIM,  "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,    "017.003", "018.000")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_GEC_TABLE_TYPE, 8, BE, "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OK,                       0,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_OK,                   1,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MSK,           2,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MUK,           3,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_COND_USE_NOT_SATISFIED,   4,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_AUTH_ERR_MAC,             5,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_KEY_FRESH,                6,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_DATA_NOT_FOUND,           7,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_AVAILABLE,         0xff,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_STA_ILLEGAL_LENGTH,             76,  "017.003", "018.000")
        CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,          0x24,  "017.003", "018.000")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_GEC_TABLE, SIM_GEC_TABLE_TYPE, "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OK,                      "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_OK,                  "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MSK,          "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_OUT_OF_MEM_MUK,          "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_COND_USE_NOT_SATISFIED,  "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_AUTH_ERR_MAC,            "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_KEY_FRESH,               "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_DATA_NOT_FOUND,          "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_GEC_ID_NOT_AVAILABLE,           "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_ILLEGAL_LENGTH,             "017.003", "018.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_DATA_NOT_AVAIL,            "017.003", "018.000")
    DER_CONST_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_HANDLE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Subblock used for Application Status and Application service status information.. From 018.000 this subblock is found in sim_shared_isi.h")
     SB_BEGIN(SIM_SB_AM_HANDLE_ID, "017.003", "018.000")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Internal application number reference to the target NAA application.")
        VALUE(8, BE, AppNum, "AppNum", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Type of NAA application.")
	VALUE_CONST(AppType, "AppType", SIM_AM_APP_TYPE_TABLE)
        VALUE_CONST(AppStatus, "AppStatus", SIM_AM_APP_STATUS_TABLE)
        VALUE_CONST(AppServiceStatus, "AppServiceStatus", SIM_SERVICE_STATUS_TABLE)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Generic Error Code. Holds the context dependent detailed error information.")
	VALUE_CONST(GecId, "GecId", SIM_GEC_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Application Management Handle  END                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_APP_LABEL")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFdir.")
    SB_BEGIN(SIM_SB_AM_APP_LABEL_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, AppLabelLength, "AppLabelLength", N)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The NAA applicaton label contains a string of bytes provided by the")
	COMMENT(COMMENT_TEXT, "NAA application provider to be shown to the user for information, e.g.")
	COMMENT(COMMENT_TEXT, "operator name. Used coding is defined in 3gpp TS 102.221 (both in case of UICC and ICC).")
        SEQ_OF_REF(AppLabel, "AppLabel", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_APP_INFO_RECORD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    SB_BEGIN(SIM_SB_AM_APP_INFO_RECORD_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "The number of subblocks to follow (n=2)")
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            COMMENT(COMMENT_TEXT, "The NAA application handle to be used in subsequent requests.")
            SB_LST_ENTRY(SIM_SB_AM_HANDLE_ID)
            COMMENT(COMMENT_TEXT, "The NAA application label string.")
            SB_LST_ENTRY(SIM_SB_AM_APP_LABEL_ID)
        SB_LST_REF_END
    SB_END

    /* --------------------------------------------------------------------- */
    /* File Data ID's   START                                                */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(SIM_FDI_TABLE_TYPE, 8, BE, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Private user identity of the user.")
        CONST_TBL_ENTRY_VER(SIM_FDI_IMPI,       0, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "GBA Bootstrapping parameters.")
        CONST_TBL_ENTRY_VER(SIM_FDI_GBABP,      1, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "GBA NAF List")
        CONST_TBL_ENTRY_VER(SIM_FDI_GBANL,      2, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MBMS Service Keys List")
        CONST_TBL_ENTRY_VER(SIM_FDI_MSK,        3, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MBMS User Key.")
        CONST_TBL_ENTRY_VER(SIM_FDI_MUK,        4, "017.003", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_FDI_TABLE, SIM_FDI_TABLE_TYPE, "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_FDI_IMPI,   "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_FDI_GBABP,  "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_FDI_GBANL,  "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_FDI_MSK,    "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_FDI_MUK,    "017.003", "")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_FILE_DATA_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_FILE_DATA_ID_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of file data type.")
        VALUE_CONST(FileDataId, "FileDataId", SIM_FDI_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Service ID's   START                                                  */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Notice: 3gpp TS 31.102 sec. 4.2.8 lists the services available for USIM NAA App.")
    COMMENT(COMMENT_TEXT, " 3gpp TS 31.103 sec. 4.2.7 lists the services available for ISIM NAA App. 3gpp TS")
    COMMENT(COMMENT_TEXT, " 51.011 sec. 10.3.7 lists the services available for SIM NAA App.")
    CONST_TBL_BEGIN(SIM_SERVICE_ID_TABLE_TYPE, 8, BE, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Generic Bootstrapping Architecture (GBA).")
	 CONST_TBL_ENTRY_VER(SIM_APP_GBA_AVAIL,      0,    "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MBMS Security.")
	 CONST_TBL_ENTRY_VER(SIM_APP_MBMS_AVAIL,     1,    "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "OMA BCAST.")
	 CONST_TBL_ENTRY_VER(SIM_APP_BCAST_AVAIL,     2,   "018.000", "")
    CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVICE_ID_TABLE, SIM_SERVICE_ID_TABLE_TYPE, "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_APP_GBA_AVAIL,      "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_APP_MBMS_AVAIL,     "017.003", "")
        DER_CONST_TBL_ENTRY_VER(SIM_APP_BCAST_AVAIL,    "018.000", "")
    DER_CONST_TBL_END

    /* --------------------------------------------------------------------- */
    /* tSIM_SB_AM_SERVICE_ID has to be closed for v018.000 and reopened      */
    /* again because of the usage of SIM_SERVICE_STATUS_TABLE, which was     */
    /* moved to sim_shared_isi_m.h                                           */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_SERVICE_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFust and EFist.")
    SB_BEGIN(SIM_SB_AM_SERVICE_ID_ID, "017.003", "018.000")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the service within the NAA application specific service table.")
        VALUE_CONST(AppServiceId, "AppServiceId", SIM_SERVICE_ID_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(AppServiceStatus, "AppServiceStatus", SIM_SERVICE_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_SERVICE_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFust and EFist.")
    SB_BEGIN(SIM_SB_AM_SERVICE_ID_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the service within the NAA application specific service table.")
        VALUE_CONST(AppServiceId, "AppServiceId", SIM_SERVICE_ID_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(AppServiceStatus, "AppServiceStatus", SIM_SERVICE_STATUS_TABLE_2)
        FILLER_EX(Pad1, 8, 1)
    SB_END

    /* --------------------------------------------------------------------- */
    /* Service ID's   END                                                    */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_GBA_B_TID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Bootstrapping Transaction Identifier of the GBA_U bootstrapped key (B_TID).\
                           This subblock includes information from EFgbabp.")
    SB_BEGIN(SIM_SB_AM_GBA_B_TID_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "B-TID. Coding defined in TS 33.220.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_GBA_KEY_LIFETIME")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFgbabp.")
    SB_BEGIN(SIM_SB_AM_GBA_KEY_LIFETIME_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "NAF_ID. Coding defined in TS 33.220.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_GBA_NAF_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "Identifier of Network Application Function used in ")
    COMMENT(COMMENT_TEXT, " the GBA_U NAF Derivation procedure (NAF_ID).")    
    SB_BEGIN(SIM_SB_AM_GBA_NAF_ID_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Key Lifetime of the GBA_U bootstrapped keys. Coding defined in TS 33.220.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_GBA_GBANL_RECORD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFgbanl.")
    SB_BEGIN(SIM_SB_AM_GBA_GBANL_RECORD_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "The number of subblocks to follow (n=2)")
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            COMMENT(COMMENT_TEXT, "Identifier of Network Application Function used in the GBA_U NAF Derivation procedure (NAF_ID).")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_NAF_ID_ID,   "017.003", "")
            COMMENT(COMMENT_TEXT, "bootstrapping Transaction Identifier of the GBA_U bootstrapped key (B_TID).")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_B_TID_ID,    "017.003", "")
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_GBA_KS_EXT_NAF")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_GBA_KS_EXT_NAF_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Ks Ext NAF. Coding defined in TS 33.220.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    /* --------------------------------------------------------------------- */
    /* MTPx   START                                                          */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_STRUCT_AM_MBMS_MTP_X")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SEQ_BEGIN(SIM_STRUCT_AM_MBMS_MTP_X, CREATE_STRUCT, "017.003", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MSK id part of the Xth MTP. Identifier of MBMS Service Key (MSK) within the")
	COMMENT(COMMENT_TEXT, " particular key domain, as defined in TS 33.246.")
        VALUE(32, BE, XthMTP_MSK_ID, "XthMTP_MSK_ID", HEX)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Time Stamp Counter part of the Xth MTP. Counter for MIKEY replay protection")
	COMMENT(COMMENT_TEXT, " in MTK delivery. Defined in TS 33.246.")
	VALUE(32, BE, XthMTP_TimeStampCounter, "XthMTP_TimeStampCounter", HEX)
    SEQ_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_MSK_RECORD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFmsk.")
    SB_BEGIN(SIM_SB_AM_MBMS_MSK_RECORD_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 1 part of 3 bytes total.")
        VALUE(8, BE, KeyDomainIdByte1, "KeyDomainIdByte1", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 2 part of 3 bytes total.")
	VALUE(8, BE, KeyDomainIdByte2, "KeyDomainIdByte2", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 3 part of 3 bytes total.")
	VALUE(8, BE, KeyDomainIdByte3, "KeyDomainIdByte3", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, " N >= 2.Maximum number of MSK IDs with corresponding Time Stamp Counter(TS) pairs ")
	COMMENT(COMMENT_TEXT, "(MTP) within each record, that is supported by the UICC (Decoded from the File Control Parameter).")
	COMMENT(COMMENT_TEXT, " Defined by TS 33.246.")
	VALUE(8, BE, MaxNumOfMTP, "MaxNumOfMTP(N)", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Number of  MSK ID/TS Pairs (MTP). M <= N. Defined in TS 33.246.")
        VALUE(8, BE, NumOfMTP, "NumOfMTP(M)", HEX)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "mtps repeated M times. M >= 0")
        SEQ_OF_REF(mtps, "mtps", SIM_STRUCT_AM_MBMS_MTP_X, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SB_END

    /* --------------------------------------------------------------------- */
    /* MTPx   END                                                            */
    /* --------------------------------------------------------------------- */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_MUK_RECORD")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This subblock includes information from EFmuk.")
    SB_BEGIN(SIM_SB_AM_MBMS_MUK_RECORD_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Length of MUK IDr data field")
        REFERENCE(8, BE, MukIdrLength, "MukIdrLength", L)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Length of MUK IDi data field")
	REFERENCE(8, BE, MukIdiLength, "MukIdiLength", M)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Length of Time Stamp Counter data field")
	REFERENCE(8, BE, TimeStampCounterLength, "TimeStampCounterLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "IDr part of MBMS User Key (MUK). Coding as defined in TS 33.246.")
	SEQ_OF_REF(MukIdrData, "MukIdrData", AUTOGEN_SEQ_BYTE_HEX, L, ISIHDR_MARKER_ANYSIZE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "IDi part of MBMS User Key (MUK). Coding as defined in TS 33.246.")
	SEQ_OF_REF(MukIdiData, "MukIdiData", AUTOGEN_SEQ_BYTE_HEX, M, ISIHDR_MARKER_ANYSIZE)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Time Stamp Counter for the MBMS User Key (MUK).")
	COMMENT(COMMENT_TEXT, " Counter used for MIKEY replay protection in MSK delivery. Coding as defined in TS 33.246.")
        SEQ_OF_REF(TimeStampCounterData, "TimeStampCounterData", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_MIKEY")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_MIKEY_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MIKEY. Coding defined in TS 33.246, with further oma EXT BCAST")
	COMMENT(COMMENT_TEXT, " format support defined in BCAST10-ServContProt (/27/).")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_MTK_SALT")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_MTK_SALT_ID, "017.003", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "MTK. If Salt is available the Data value will hold MTK || (concatenated) SALT.Coding defined in TS 33.246.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_KEY_DOMAIN_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID, "017.003", "018.000")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 1 part of 3 bytes total.")
        VALUE(8, BE, KeyDomainIdByte1, "KeyDomainIdByte1", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 2 part of 3 bytes total.")
        VALUE(8, BE, KeyDomainIdByte2, "KeyDomainIdByte2", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 3 part of 3 bytes total.")
	VALUE(8, BE, KeyDomainIdByte3, "KeyDomainIdByte3", HEX)
        FILLER_EX(Pad1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_KEY_DOMAIN_ID")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 1 part of 3 bytes total.")
        VALUE(8, BE, KeyDomainIdByte1, "KeyDomainIdByte1", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 2 part of 3 bytes total.")
        VALUE(8, BE, KeyDomainIdByte2, "KeyDomainIdByte2", HEX)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the domain of the BM-SC, as defined in TS 33.246. Byte 3 part of 3 bytes total.")
	VALUE(8, BE, KeyDomainIdByte3, "KeyDomainIdByte3", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_KEY_GROUP_ID_PART")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID, "017.003", "018.000")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Key Group ID part of the MSK ID. Coding in 2 bytes as described in TS 33.246.")
        VALUE(16, BE, KeyGroupIdPart, "KeyGroupIdPart", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_MBMS_KEY_GROUP_ID_PART")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        FILLER_EX(Pad1, 8, 1)
        COMMENT(COMMENT_TEXT, "Key Group ID part of the MSK ID. Coding in 2 bytes as described in TS 33.246. Notice: Order of bytes is in big endian format.")
        SEQ_OF(KeyGroupIdPart, "KeyGroupIdPart", AUTOGEN_SEQ_BYTE_HEX, 2)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_KEY_NUMBER_ID_PART")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        COMMENT(COMMENT_TEXT, "Key number id part of the MSK ID. Coding in 2 bytes as described in TS 33.246. Notice: Order of bytes is in big endian format.")
        SEQ_OF(KeyNumberIdPart, "KeyNumberIdPart", AUTOGEN_SEQ_BYTE_HEX, 2)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "Key Validity Data - TS Low || TS High. Coding in 8 bytes as described in TS 33.246.")
        SEQ_OF(key_validity_tslow_tshigh, "KeyValidityTslowTshigh", AUTOGEN_SEQ_BYTE_HEX, 8)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "Security Policy Extension. Coding described in BCAST10-ServContProt (/27/) Sec. 6.6.2.2.")
        VALUE(8, BE, spe, "SPE", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_MANAGEMENT_DATA")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "OMA BCAST management data object. 1 byte status code described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, mgmt_data, "MGMT Data", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_USER_PURSE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_USER_PURSE_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE user purse value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, user_purse_value, "user_purse_value", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_LIVE_PPT_PURSE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_LIVE_PPT_PURSE_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE live ppt purse value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, live_ppt_purse_value, "live_ppt_purse_value", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_PLAYBACK_PPT_PURSE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_PLAYBACK_PPT_PURSE_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE playback ppt purse value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, playback_ppt_purse_value, "playback_ppt_purse_value", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_KEPT_TEK_COUNTER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_KEPT_TEK_COUNTER_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE kept tek counter value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, kept_tek_counter_val, "kept_tek_counter_val", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_KEY_GROUP_DESCRIPTION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    SB_BEGIN(SIM_SB_AM_BCAST_KEY_GROUP_DESCRIPTION_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "The number of subblocks to follow (n>=2)")
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            COMMENT(COMMENT_TEXT, "The key domain. (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID)
            COMMENT(COMMENT_TEXT, "The key group (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID)
            COMMENT(COMMENT_TEXT, "The user purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_USER_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The live ppt purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_LIVE_PPT_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The playback ppt purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_PLAYBACK_PPT_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The kept tek counter (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_KEPT_TEK_COUNTER_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_KEY_PROPERTIES")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_KEY_PROPERTIES_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE key property value. 1 byte code described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, key_properties, "key_properties", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_COST_VALUE")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_COST_VALUE_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE cost value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, cost_val, "cost_val", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_PLAYBACK_COUNTER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_PLAYBACK_COUNTER_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE playback counter value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, playback_counter_val, "playback_counter_val", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_TEK_COUNTER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_TEK_COUNTER_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE tek counter value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(32, BE, tek_counter_val, "tek_counter_val", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_DESCRIPTION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "The number of subblocks to follow (n>=6)")
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            COMMENT(COMMENT_TEXT, "The key domain. (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID)
            COMMENT(COMMENT_TEXT, "The key group. (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID)
            COMMENT(COMMENT_TEXT, "The key number (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID)
            COMMENT(COMMENT_TEXT, "The key validity data (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH_ID)
            COMMENT(COMMENT_TEXT, "The key property (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_KEY_PROPERTIES_ID)
            COMMENT(COMMENT_TEXT, "The security policy extension (Mandatory).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID)
            COMMENT(COMMENT_TEXT, "The cost value (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_COST_VALUE_ID)
            COMMENT(COMMENT_TEXT, "The play back counter (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_PLAYBACK_COUNTER_ID)
            COMMENT(COMMENT_TEXT, "The user purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_USER_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The live ppt purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_LIVE_PPT_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The playback ppt purse (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_PLAYBACK_PPT_PURSE_ID)
            COMMENT(COMMENT_TEXT, "The kept tek counter (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_KEPT_TEK_COUNTER_ID)
            COMMENT(COMMENT_TEXT, "The tek counter (Optional).")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_TEK_COUNTER_ID)
        SB_LST_REF_END
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_PARENTAL_RATING")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_PARENTAL_RATING_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE parental rating data: rating_type. 1 byte with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, rating_type, "rating_type", HEX)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE parental rating data: level_granted. 1 byte with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, level_granted, "level_granted", HEX)
        FILLER_EX(Pad1, 8, 1)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_PARENTAL_CONTROL_OPERATION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_PARENTAL_CONTROL_OPERATION_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE parental control operation (pco): rating type for the current program. 1 byte with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, pco_rating_type, "pco_rating_type", HEX)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE parental control operation (pco): rating value for the current program. 1 byte with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, pco_rating_value, "pco_rating_value", HEX)
        COMMENT(COMMENT_TEXT, "OMA BCAST SPE parental control operation (pco): level granted value for the current rating type. 1 byte with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, pco_level_granted_value, "pco_level_granted_value", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_TEK_DATA")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_TEK_DATA_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "TEK data object. Coding defined in TS 33.246.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_TERMINAL_IDENTIFIER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        COMMENT(COMMENT_TEXT, "OMA BCAST Terminal Identifier type. 1 byte describing the type of the terminal_id_value, with coding described in BCAST10-ServContProt (/27/).")
        VALUE(8, BE, terminal_id_type, "terminal_id_type", HEX)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST Terminal Identifier. 16 bytes with coding described in BCAST10-ServContProt (/27/).")
        SEQ_OF(terminal_id_value, "terminal_id_value", AUTOGEN_SEQ_BYTE_HEX, 16)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_CONTENT_IDENTIFIER")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Content identifier data. N bytes of data with terminal specific coding. Coding described in BCAST10-ServContProt (/27/).")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_REC_TS_INTERVAL")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_REC_TS_INTERVAL_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST TS start recording value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        SEQ_OF(ts_start_val, "ts_start_val", AUTOGEN_SEQ_BYTE_HEX, 4)
        COMMENT(COMMENT_TEXT, "OMA BCAST TS end recording value. 4 bytes with coding described in BCAST10-ServContProt (/27/).")
        SEQ_OF(ts_end_val, "ts_end_val", AUTOGEN_SEQ_BYTE_HEX, 4)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_SPE_AVAILABLE_NR_OF_REC")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SB_BEGIN(SIM_SB_AM_BCAST_SPE_AVAILABLE_NR_OF_REC_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        VALUE_CONST(Status, "Status", SIM_SB_PARAMS_STATUS)
        FILLER_EX(Pad1, 8, 1)
        COMMENT(COMMENT_TEXT, "OMA BCAST Available number of SPE records. 2 bytes with coding described in BCAST10-ServContProt (/27/).")
        VALUE(16, BE, avail_spe_rec, "avail_spe_rec", HEX)
    SB_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SB_AM_BCAST_REC_CONTENT_DESCRIPTION")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY_VALUE(PROPERTY_SB_LENGTH_LIMIT, 512)
    SB_BEGIN(SIM_SB_AM_BCAST_REC_CONTENT_DESCRIPTION_ID, "018.000", "")
        SIM_SB_16_LONG
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_AM_STA_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT(COMMENT_TEXT, "The number of subblocks to follow (n>=2)")
        REFERENCE(8, BE, NumOfSb, "NumOfSb", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            COMMENT(COMMENT_TEXT, "The terminal identifier.")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID)
            COMMENT(COMMENT_TEXT, "The content identifier.")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID)
            COMMENT(COMMENT_TEXT, "An OMA BCAST flagged SPE, identified by its content identifier. This subblock may be repeated n>= 0 times.")
            SB_LST_ENTRY(SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID)
        SB_LST_REF_END
    SB_END

    /* --------------------------------------------------------------------- */
    /* Messages                                                              */ 
    /* --------------------------------------------------------------------- */

    /* SIM_PIN_VERIFY_REQ */

    DER_CONST_TBL_BEGIN(SIM_PIN_VERIFY_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
        DER_CONST_TBL_ENTRY_VER(SIM_ST_PIN_PARENTAL_CONTROL,    "018.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_PIN_VERIFY_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE) 
        DER_CONST_TBL_ENTRY(SIM_SERV_OK) 
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLED)
        DER_CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request         Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code            Code;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_VerifyCodeReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_VERIFY_CODE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to verify PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN in the indicated application.")
    MSG_BEGIN(SIM_PIN_VERIFY_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_REQUEST_PIN     Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_VERIFY_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to verify PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code            Code;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "PIN code to verify. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Code, "Code", 9)
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_VerifyCodeResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the result of PIN verification.")
    MSG_BEGIN(SIM_PIN_VERIFY_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response        Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_VERIFY_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PIN_VERIFY_STATUS)
    MSG_END

    MSG_PAIR(SIM_PIN_VERIFY_REQ, SIM_PIN_VERIFY_RESP)


    /* SIM_PIN_CHANGE */

    DER_CONST_TBL_BEGIN(SIM_PIN_CHANGE_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
        DER_CONST_TBL_ENTRY_VER(SIM_ST_PIN_PARENTAL_CONTROL,    "018.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_PIN_CHANGE_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLED)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request         Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_ChangeCode      Code;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_ChangeCodeReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CHANGE_CODE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to change PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN in the indicated application.")
    MSG_BEGIN(SIM_PIN_CHANGE_REQ, MESSAGE_REQ, "", "")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_REQUEST_PIN     Req;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_CHANGE_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT,  "Application on (U)SIM where to change PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_ChangeCode      Code;") 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
	COMMENT(COMMENT_TEXT, "Old PIN code. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, OldCode, "Old PIN Code", 9)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "New PIN code. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, NewCode, "New PIN Code", 9)
    MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ChangeCodeResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the result of changing PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN on (U)SIM.")
    MSG_BEGIN(SIM_PIN_CHANGE_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response        Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_CHANGE_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PIN_CHANGE_STATUS)
    MSG_END

    MSG_PAIR(SIM_PIN_CHANGE_REQ, SIM_PIN_CHANGE_RESP)

    /* SIM_PIN_ENABLE */
/*
    DER_CONST_TBL_BEGIN(SIM_PIN_ENABLE_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
    DER_CONST_TBL_END
*/    

    DER_CONST_TBL_BEGIN(SIM_PIN_ENABLE_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_ENABLE_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLE_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
    DER_CONST_TBL_END

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN2.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_UNIVERSAL.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_PARENTAL_CONTROL.")

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef bool8  tSIM_Enable;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request         Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Enable          Enable;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code            Code;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_EnableCodeReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ENALBE_CODE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to enable or disble PIN in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_PIN, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "", "")    
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_REQUEST_PIN     Req;") \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        VALUE(8, BE, TransID, "Transaction ID", DEC) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM where PIN is enabled or disabled.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Enable          Enable;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(enable, "Enable TRUE or Disable FALSE", TRUE_FALSE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code            Code;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT(COMMENT_TEXT, "PIN code to enable/disable. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Code, "Code", 9)
    SUB_MSG_END


    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN2.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_UNIVERSAL.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_PARENTAL_CONTROL.")


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_EnableCodeResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the result of enabling or disbling PIN on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_PIN, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_PIN_ENABLE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_PIN, SIM_PIN_ENABLE_REQ, SIM_ST_PIN, SIM_PIN_ENABLE_RESP)
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to enable or disble universal PIN in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_PIN_UNIVERSAL, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "", "")    
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM where universal PIN is enabled or disabled.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        VALUE_CONST(enable, "Enable TRUE or Disable FALSE", TRUE_FALSE)
        COMMENT(COMMENT_TEXT, "PIN code to enable/disable. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Code, "Code", 9)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message result of enabling or disbling universal PIN in application on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_PIN_UNIVERSAL, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_PIN_ENABLE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_PIN_UNIVERSAL, SIM_PIN_ENABLE_REQ, SIM_ST_PIN_UNIVERSAL, SIM_PIN_ENABLE_RESP)
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to enable or disble PIN2 in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_PIN2, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "", "")    
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM where PIN2 is enabled or disabled.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        VALUE_CONST(enable, "Enable TRUE or Disable FALSE", TRUE_FALSE)
        COMMENT(COMMENT_TEXT, "PIN code to enable/disable. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Code, "Code", 9)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message result of enabling or disbling PIN2 in application on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_PIN2, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_PIN_ENABLE_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_PIN2, SIM_PIN_ENABLE_REQ, SIM_ST_PIN2, SIM_PIN_ENABLE_RESP)

    /*************************  begin SIM_ST_PIN_PARENTAL_CONTROL  **************************/
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to enable or disble PIN_PARENTAL_CONTROL in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "018.000", "")    
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM where PIN_PARENTAL_CONTROL is enabled or disabled.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        VALUE_CONST(enable, "Enable TRUE or Disable FALSE", TRUE_FALSE)
        COMMENT(COMMENT_TEXT, "PIN code to enable/disable. PIN code is 4-8 digits.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, Code, "Code", 9)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message result of enabling or disbling PIN_PARENTAL_CONTROL in application on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "018.000", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_PIN_ENABLE_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_ENABLE_REQ, SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_ENABLE_RESP)

    /*************************  end SIM_ST_PIN_PARENTAL_CONTROL  **************************/

    /*************************  SIM_ST_SUBSTITUTE_PIN_UNIVERSAL  ****************************/

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_SUBSTITUTE_PIN_UNIVERSAL.")

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8          TransID;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8          MessageID;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8          ServiceType;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8          Paddingbyte;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code      Code;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_SubPinReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SUB_PIN_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to substitute universal PIN with PIN1 as primary PIN in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)ICC where PIN is substituted.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Code        Code;")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "PIN code to substitute current primary PIN.")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, code, "Code", 9)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_PIN_ENABLE_SUBSTITUTE_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_WRONG_OLD_PIN)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
    DER_CONST_TBL_END
    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_SUBSTITUTE_PIN_UNIVERSAL.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SubPinResp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)    
    COMMENT(COMMENT_TEXT, "This message returns the result of substituting universal PIN with PIN1 as primary PIN in \
                           application on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PIN_ENABLE_SUBSTITUTE_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_REQ, SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to substitute PIN1 with universal PIN as primary PIN in the indicated application.")
    SUB_MSG_BEGIN(SIM_ST_SUBSTITUTE_PIN_UNIVERSAL, SIM_PIN_ENABLE_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req    Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on USIM where PIN is substituted.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "PIN code to substitute current primary PIN.")
        STRING(STRING_ASCII_ZERO_TERMINATED, BE, code, "Code", 9)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the result of substituting PIN1 with universal PIN as primary PIN \
                           in application on (U)ICC.")
    SUB_MSG_BEGIN(SIM_ST_SUBSTITUTE_PIN_UNIVERSAL, SIM_PIN_ENABLE_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_PIN_ENABLE_SUBSTITUTE_STATUS)
    SUB_MSG_END

    /* SIM_PIN_STATE_GET */

    DER_CONST_TBL_BEGIN(SIM_PIN_STATE_GET_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NO_PIN)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_PERM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_DISABLED)
    DER_CONST_TBL_END

    /* SIM_PIN_STATE_GET - SIM_ST_PIN */

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN2.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_UNIVERSAL.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_PARENTAL_CONTROL.")

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request      Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_GetCodeStatusReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_GET_CODE_STATUS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to get the status of PIN.")
    SUB_MSG_BEGIN( SIM_ST_PIN, SIM_PIN_STATE_GET_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_REQUEST_PIN      Req;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get status of PIN.")
	VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN2.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_UNIVERSAL.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_PIN_PARENTAL_CONTROL.")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_GetCodeStatusResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the status of PIN.")
    SUB_MSG_BEGIN( SIM_ST_PIN, SIM_PIN_STATE_GET_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_InfoResponse Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(status, "Status", SIM_PIN_STATE_GET_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_REQ, SIM_ST_SUBSTITUTE_PIN, SIM_PIN_ENABLE_RESP)

    /* SIM_PIN_STATE_GET - SIM_ST_PIN2 */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to get the status of PIN2.")
    SUB_MSG_BEGIN( SIM_ST_PIN2, SIM_PIN_STATE_GET_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get status of PIN2.")
	VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_TEXT, "This message returns the status of PIN2.")
    SUB_MSG_BEGIN( SIM_ST_PIN2, SIM_PIN_STATE_GET_RESP, MESSAGE_RESP, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(status, "Status", SIM_PIN_STATE_GET_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_PIN2, SIM_PIN_STATE_GET_REQ, SIM_ST_PIN2, SIM_PIN_STATE_GET_RESP)

    /* SIM_PIN_STATE_GET - SIM_ST_PIN_UNIVERSAL */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to get the status of universal PIN.")
    SUB_MSG_BEGIN( SIM_ST_PIN_UNIVERSAL, SIM_PIN_STATE_GET_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get status of universal PIN.")
	VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_TEXT, "This message returns the status of universal PIN.")
    SUB_MSG_BEGIN( SIM_ST_PIN_UNIVERSAL, SIM_PIN_STATE_GET_RESP, MESSAGE_RESP, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(status, "Status", SIM_PIN_STATE_GET_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_PIN_UNIVERSAL, SIM_PIN_STATE_GET_REQ, SIM_ST_PIN_UNIVERSAL, SIM_PIN_STATE_GET_RESP)

    /* SIM_PIN_STATE_GET - SIM_ST_PIN_PARENTAL_CONTROL */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to get the status of PIN_PARENTAL_CONTROL.")
    SUB_MSG_BEGIN( SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_STATE_GET_REQ, MESSAGE_REQ, "018.000", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get status of PIN_PARENTAL_CONTROL.")
	VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_TEXT, "This message returns the status of PIN_PARENTAL_CONTROL.")
    SUB_MSG_BEGIN( SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_STATE_GET_RESP, MESSAGE_RESP, "018.000", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(status, "Status", SIM_PIN_STATE_GET_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_STATE_GET_REQ, SIM_ST_PIN_PARENTAL_CONTROL, SIM_PIN_STATE_GET_RESP)

    /* SIM_PIN_STATE_GET - SIM_ST_GET_ACTIVE_PIN */
    DER_CONST_TBL_BEGIN(SIM_ST_PIN_STATUS, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
/* To be added when new status have been created instead of the two service types used as status
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)*/
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8      TransID;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8      MessageID;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8      ServiceType;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    uint8      Pad;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_GetActivePinReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_GET_ACTIVE_PIN_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client identify the active PIN for a selected application on USIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The active PIN is the PIN code to get access to the selected USIM application.")
    SUB_MSG_BEGIN(SIM_ST_GET_ACTIVE_PIN, SIM_PIN_STATE_GET_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get active PIN.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_GetActivePinResp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the active PIN from a selected application on USIM.")
    SUB_MSG_BEGIN(SIM_ST_GET_ACTIVE_PIN, SIM_PIN_STATE_GET_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_PIN_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_GET_ACTIVE_PIN, SIM_PIN_STATE_GET_REQ, SIM_ST_GET_ACTIVE_PIN, SIM_PIN_STATE_GET_RESP)

    /* SIM_PIN_UNBLOCK */

    DER_CONST_TBL_BEGIN(SIM_PIN_UNBLOCK_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
        DER_CONST_TBL_ENTRY_VER(SIM_ST_PIN_PARENTAL_CONTROL,    "018.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_PIN_UNBLOCK_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_WRONG_UNBLOCKING_KEY)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
    DER_CONST_TBL_END
    
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request          Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_UnblockCode      Code;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_UnblockCodeReq;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_UNBLOCK_CODE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to unblock PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN on (U)SIM.")
    MSG_BEGIN(SIM_PIN_UNBLOCK_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_REQUEST_PIN      Req;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(service_type, "Service Type", SIM_PIN_UNBLOCK_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_UnblockCode      Code;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        SEQ_OF(Unblock_code, "Unblock code", UNBLOCK_CODE, 1)
    MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_UnblockCodeResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the result of unblocking PIN, PIN2, PIN_PARENTAL_CONTROL or universal PIN on (U)SIM.")
    MSG_BEGIN(SIM_PIN_UNBLOCK_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response         Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, trans_id, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, message_id, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(service_type, "Service Type", SIM_PIN_UNBLOCK_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(status, "Status", SIM_PIN_UNBLOCK_STATUS)
    MSG_END

    MSG_PAIR(SIM_PIN_UNBLOCK_REQ, SIM_PIN_UNBLOCK_RESP)

    /* SIM_PIN_ATTEMPTS_LEFT_REQ */

    DER_CONST_TBL_BEGIN(SIM_PIN_ATTEMPTS_LEFT_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
        DER_CONST_TBL_ENTRY(SIM_ST_PUK)
        DER_CONST_TBL_ENTRY(SIM_ST_PUK2)
        DER_CONST_TBL_ENTRY(SIM_ST_PUK_UNIVERSAL)
        DER_CONST_TBL_ENTRY_VER(SIM_ST_PIN_PARENTAL_CONTROL,    "018.000", "")
        DER_CONST_TBL_ENTRY_VER(SIM_ST_PUK_PARENTAL_CONTROL,    "018.000", "")
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_PIN_ATTEMPTS_LEFT_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
    DER_CONST_TBL_END
    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_PARAGRAPH, "For the following service types:")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN2,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN_PARENTAL_CONTROL.")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN_UNIVERSAL,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK2,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK_PARENTAL_CONTROL.")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK_UNIVERSAL.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PIN_ATTEMPTS_LEFT_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message allows a client to get the number of PIN or PUK verification attempts.")
    MSG_BEGIN(SIM_PIN_ATTEMPTS_LEFT_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_ATTEMPTS_LEFT_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM to get verification attempts.")
	VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    MSG_END
    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_PARAGRAPH, "For the following service types:")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN2,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN_PARENTAL_CONTROL.")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PIN_UNIVERSAL,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK2,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK_PARENTAL_CONTROL.")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_PUK_UNIVERSAL.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PIN_ATTEMPTS_LEFT_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_TEXT, "This message returns the number of PIN or PUK verification attempts.")
    MSG_BEGIN(SIM_PIN_ATTEMPTS_LEFT_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PIN_ATTEMPTS_LEFT_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PIN_ATTEMPTS_LEFT_STATUS)
        VALUE(8, BE, RemainingAttempts, "Remaining Attempts", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
    MSG_END

    MSG_PAIR(SIM_PIN_ATTEMPTS_LEFT_REQ, SIM_PIN_ATTEMPTS_LEFT_RESP)

    /* SIM_AUTHENTICATION */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AUTHENTICATION_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to perform authentication on the (U)SIM card.")
    MSG_BEGIN(SIM_AUTHENTICATION_REQ, MESSAGE_REQ, "", "")
        SIM_MSG_HDR_AUTH
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_AUTH_SERVICE_TYPE_TABLE)
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_RAND_PARAMS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_AUTN_PARAMS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY_VER(SIM_SB_AM_HANDLE_ID,                   "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_B_TID_ID,                "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_KEY_LIFETIME_ID,         "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_NAF_ID_ID,               "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_IMS_PRIVATE_USER_ID,            "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MIKEY_ID,               "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_KEY_DOMAIN_ID_ID,       "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_KEY_GROUP_ID_PART_ID,   "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MUK_RECORD_ID,          "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID,      "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_KEY_NUMBER_ID_PART_ID,             "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_KEY_VALIDITY_DATA_TSLOW_TSHIGH_ID, "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_TERMINAL_IDENTIFIER_ID,            "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_CONTENT_IDENTIFIER_ID,             "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_REC_TS_INTERVAL_ID,                "018.000", "")
        SB_LST_REF_END
    MSG_END

    DER_CONST_TBL_BEGIN(SIM_AUTHENTIFICATION_STATUS, SIM_SERV_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_DATA_NOT_AVAILABLE)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AUTHENTICATION_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of the authentication on the (U)SIM card.")
    MSG_BEGIN(SIM_AUTHENTICATION_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR_AUTH
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_AUTH_SERVICE_TYPE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_AUTHENTIFICATION_STATUS)
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_RES_PARAMS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_AUTN_FAIL_PARAMS_ID)
            SB_LST_ENTRY(SIM_SB_EAP_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_EAP_INTEGRITY_KEY_ID)
            SB_LST_ENTRY_VER(SIM_SB_AM_HANDLE_ID,           "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_RAND_PARAMS_ID,         "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_KS_EXT_NAF_ID,   "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MIKEY_ID,       "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MTK_SALT_ID,    "017.003", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_KEY_GROUP_DESCRIPTION_ID,          "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SPE_DESCRIPTION_ID,                "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_MANAGEMENT_DATA_ID,                "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SPE_PARENTAL_RATING_ID,            "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SECURITY_POLICY_EXTENSION_ID,      "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SPE_PARENTAL_CONTROL_OPERATION_ID, "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_TEK_DATA_ID,                       "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_SPE_AVAILABLE_NR_OF_REC_ID,        "018.000", "")
            SB_LST_ENTRY_VER(SIM_SB_AM_BCAST_REC_CONTENT_DESCRIPTION_ID,        "018.000", "")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SIM_AUTHENTICATION_REQ, SIM_AUTHENTICATION_RESP)

    /* SIM_CS_READ */
    DER_CONST_TBL_BEGIN(SIM_CS_READ_RESP_STATUS, SIM_SERV_STA_TABLE, "", "")    
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_SIM_REMOVED)        
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
   
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_CS_READ_REQ       Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint16                 SubblockID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_CS_READ_REQ_ST_DATA_READ; /* Deprecated */")


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_READ_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used to read specific information for CS subsystem."
                          " It is possible to request any number of sub-blocks.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_CS_DATA_READ_ALL_REQ.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_CS_DATA_READ_ALL_GSS_REQ.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_REQ, SIM_CS_READ_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
            SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_READ_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns information to CS subsystem.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_CS_DATA_READ_ALL_REQ.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_CS_DATA_READ_ALL_GSS_REQ.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_REQ, SIM_CS_READ_RESP, MESSAGE_RESP, "", "")    
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_CS_READ_RESP_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
	    SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END
   
    SUB_MSG_PAIR(SIM_ST_CS_DATA_READ_REQ, SIM_CS_READ_REQ, SIM_ST_CS_DATA_READ_REQ, SIM_CS_READ_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message reads all possible subblocks for CS subsystem.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_ALL_REQ, SIM_CS_READ_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
            SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "020.000")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns all possible subblocks for CS subsystem.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_ALL_REQ, SIM_CS_READ_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_CS_READ_RESP_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
            SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "020.000")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used to read all sub-blocks defined for this message.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_ALL_GSS_REQ,  SIM_CS_READ_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
	    SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_READ_ALL_GSS_REQ,  SIM_CS_READ_RESP, MESSAGE_RESP, "", "")    
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_CS_READ_RESP_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ACC_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_CARD_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_ECC_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_ID)
            SB_LST_ENTRY(SIM_SB_HPLMN_SEARCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_OPERATOR_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_HOME_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_EQUIVALENT_HPLMNS_ID)
	    SB_LST_ENTRY_VER(SIM_SB_ATT_RAT_ID, "017.006", "")
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_IMSI_ID)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_CIPHERING_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_INTEGRITY_KEY_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_MAX_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
        SB_LST_REF_END
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_STATUS_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message reads the status of the SIM server.")
    SUB_MSG_BEGIN(SIM_ST_CS_STATUS_REQ,  SIM_CS_READ_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Padding, 8, 1)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_STATUS_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the status of the SIM server. No sub-blocks are returned.")
    SUB_MSG_BEGIN(SIM_ST_CS_STATUS_REQ,  SIM_CS_READ_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_CS_READ_RESP_STATUS)
    SUB_MSG_END

    /* SIM_CS_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_WRITE_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to update data on the SIM card.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_WRITE_REQ, SIM_CS_WRITE_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_BCCH_ID)
            SB_LST_ENTRY(SIM_SB_LAI_ID)
            SB_LST_ENTRY(SIM_SB_LOC_UPD_STATUS_ID)
            SB_LST_ENTRY(SIM_SB_GSM_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_TDD_NETPAR_ID)
            SB_LST_ENTRY(SIM_SB_FORBIDDEN_PLMNS_ID)
            SB_LST_ENTRY(SIM_SB_USER_PLMN_ID)
            SB_LST_ENTRY(SIM_SB_PLMN_SELECTOR_ID)
            SB_LST_ENTRY(SIM_SB_RPLMN_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_RAUS_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_ID)
            SB_LST_ENTRY(SIM_SB_GPRS_TMSI_SIGN_VALUE_ID)
            SB_LST_ENTRY(SIM_SB_CIPHERING_KEY_SNR_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_CS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_PS_KSI_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_PS_ID)
            SB_LST_ENTRY(SIM_SB_UMTS_START_CS_ID)
        SB_LST_REF_END
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_CS_WRITE_STATUS, SIM_SERV_STA_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CS_WRITE_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of updating data on the SIM card.")
    SUB_MSG_BEGIN(SIM_ST_CS_DATA_WRITE_REQ, SIM_CS_WRITE_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP(SIM_CS_WRITE_STATUS)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The returned subblocks only includes the SubBlockID and the result of updating the data."
	                       " One subblock is returned for each subblock in SIM_CS_WRITE_REQ(SIM_ST_CS_DATA_WRITE_REQ).")
        SEQ_OF_REF(sub_blocks, "Sub block", SIM_SB_CS_WRITE_RESP_SB, N,  ISIHDR_MARKER_SINGLE_ELEMENT)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_CS_DATA_WRITE_REQ, SIM_CS_WRITE_REQ, SIM_ST_CS_DATA_WRITE_REQ, SIM_CS_WRITE_RESP)

    /* SIM_READ_FIELD */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadField_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to ask the SIM server to read an arbitrary field on the SIM card.")
    COMMENT(COMMENT_TEXT, "The field to be read  is specified by a path to the files, an offset and a data length")
    SUB_MSG_BEGIN(READ_FIELD, SIM_READ_FIELD_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Padding, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Numbers of bytes to read.")
        VALUE(16, BE, Length, "Length", DEC)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Absolute path of EF file to read.")
        COMMENT(COMMENT_TEXT, "If path is shorther then not used bytes are coded 0x00 or 0xFF.")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_TEXT, "Example of FileID, EFlp(Language Preference): 0x3F 0x00 0x7F 0x20 0x6F 0x05 0x00 0x00 ")
	SEQ_OF(FileID, "FileID", AUTOGEN_SEQ_BYTE_HEX, SIM_FILE_PATH_LEN)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Offset in EF file where to start to read data.")
        SEQ_OF(OffSet, "OffSet", AUTOGEN_SEQ_BYTE_HEX, READ_FIELD_OFFSET_LEN)
        FILLER_EX(Padding4, 8, 1)
        FILLER_EX(Padding5, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_READ_FIELD_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_INVALID_FILE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadField_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    SUB_MSG_BEGIN(READ_FIELD, SIM_READ_FIELD_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_READ_FIELD_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        COMMENT(COMMENT_TEXT, "Length of data to follow")
        REFERENCE(16, BE, Length, "Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Requested data.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE_BYTE)
    SUB_MSG_END
    
    SUB_MSG_PAIR(READ_FIELD, SIM_READ_FIELD_REQ, READ_FIELD, SIM_READ_FIELD_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadAcc_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to ask the SIM server to read Access Control Class(EFacc) on (U)SIM.") 
    SUB_MSG_BEGIN(ACC, SIM_READ_FIELD_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_READ_FIELD_STATUS_ACC, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

  PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadAcc_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Access Control Class(EFacc).")  
    SUB_MSG_BEGIN(ACC, SIM_READ_FIELD_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_READ_FIELD_STATUS_ACC)    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Content of EFacc.")
        SEQ_OF(Acc, "Acc", AUTOGEN_SEQ_BYTE_HEX, SIM_ACC_CTRL_LEN)
    SUB_MSG_END

    SUB_MSG_PAIR(ACC, SIM_READ_FIELD_REQ, ACC, SIM_READ_FIELD_RESP)

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IccReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to ask for the unique identification number(EFiccid) of (U)SIM card.")  
    SUB_MSG_BEGIN(ICC, SIM_READ_FIELD_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_READ_FIELD_ICC_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IccReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the unique identification number(EFiccid) of (U)SIM card.")  
    SUB_MSG_BEGIN(ICC, SIM_READ_FIELD_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_READ_FIELD_ICC_STATUS)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Unique identification number of (U)SIM card.")  
        SEQ_OF(Icc, "Icc", SIM_ICC, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(ICC, SIM_READ_FIELD_REQ, ICC, SIM_READ_FIELD_RESP)
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCardType_Req")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to ask for data in Administrative Data in the EFad file of (U)SIM card.")
    COMMENT(COMMENT_TEXT, "Only the 'UE/MS operation mode' is accessible in this interface.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(AD, SIM_READ_FIELD_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCardType_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns 'UE/MS operation mode' from Administrative Data in the EFad file of (U)SIM card.")
    SUB_MSG_BEGIN(AD, SIM_READ_FIELD_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_READ_FIELD_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Cardtype is 'UE operation mode'(USIM) or 'MS operation mode'(SIM) byte from the EFad filefstatus.")
        SEQ_OF(Cardtype, "CardType", SIM_SERV_CARD_TYPE, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(AD, SIM_READ_FIELD_REQ, AD, SIM_READ_FIELD_RESP)

    /* SIM_DATA_SIZES */

    DER_CONST_TBL_BEGIN(SIM_READ_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY_VER(READ_ADN_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_ADN_ALPHA_LEN)
        DER_CONST_TBL_ENTRY_VER(READ_PLMN_SELECTOR_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_FDN_CNT)
        DER_CONST_TBL_ENTRY(READ_FDN_ALPHA_LEN)
        DER_CONST_TBL_ENTRY(READ_MSISDN_CNT)
        DER_CONST_TBL_ENTRY_VER(READ_MSISDN_ALPHA_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_SMS_PARAM_CNT)
        DER_CONST_TBL_ENTRY_VER(READ_SMS_PARAM_ALPHA_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_PREF_LANGUAGE_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_OPERATOR_NAME_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_MBX_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_MBX_ALPHA_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_CB_MSG_ID_CNT)
        DER_CONST_TBL_ENTRY_VER(READ_CSP1_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_INF_NBR_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_JACOB_ID_CNT)
        DER_CONST_TBL_ENTRY_VER(READ_VMWI_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_CPHS_LEN, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(READ_ECC_CNT, "", "020.000")
        DER_CONST_TBL_ENTRY(READ_ADN_NBR_LEN) 
        DER_CONST_TBL_ENTRY(READ_FDN_NBR_LEN) 
        DER_CONST_TBL_ENTRY_VER(READ_MSISDN_NBR_LEN, "", "020.000")
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DataSizeReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This command reads the length of various data field and the number of records of formated datafields.")
    MSG_BEGIN(SIM_DATA_SIZES_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request        Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(ServiceType, "ServiceType", SIM_READ_SERVICE_TYPE)
    MSG_END

    DER_CONST_TBL_BEGIN(SIM_READ_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DataSizeReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This command returns the value of requested datafield.")
    MSG_BEGIN(SIM_DATA_SIZES_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_InfoResponse   Resp;") \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        VALUE(8, BE, TransID, "Transaction ID", DEC) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "ServiceType", SIM_READ_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_READ_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Value of requested data. ServiceType give the type of data.")
        VALUE(8, BE, DataSize, "DataSize", DEC)
    MSG_END

    MSG_PAIR(SIM_READ_FIELD_REQ, SIM_READ_FIELD_RESP)

    /* SIM_PREF_LANGUAGE */

    DER_CONST_TBL_BEGIN(SIM_PREF_LANGUAGE_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* SIM_PREF_LANGUAGE - SIM_ST_READ_PL_LANGUAGE */  

    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message request the list of preferred language codes from EFpl.")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "This request only returns valid data if ICC is an USIM card")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_READ_LI_LANGUAGE.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_LanguageRead_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_READ_PL_LANGUAGE, SIM_PREF_LANGUAGE_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)         
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)      
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END
   
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns a list of Preferred Language(PL) codes from EFpl on USIM.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")    
    COMMENT(COMMENT_TEXT, "SIM_ST_READ_LI_LANGUAGE.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_LanguageRead_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_READ_PL_LANGUAGE, SIM_PREF_LANGUAGE_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PREF_LANGUAGE_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Number of language code available on card.")
        VALUE(8, BE, Count, "Count", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "List of preferred language codes from EFpl on USIM.")
        SEQ_OF_REF(Languages, "Languages", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_PL_LANGUAGE, SIM_PREF_LANGUAGE_REQ, SIM_ST_READ_PL_LANGUAGE, SIM_PREF_LANGUAGE_RESP)

    /* SIM_PREF_LANGUAGE - SIM_ST_READ_LI_LANGUAGE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message request the list of language indication(LI) codes from EFli on USIM")
    COMMENT(COMMENT_TEXT, "(language indication) at the level of the active application on the USIM card")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "This request only returns valid data if ICC is an USIM card")        
    SUB_MSG_BEGIN(SIM_ST_READ_LI_LANGUAGE, SIM_PREF_LANGUAGE_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns a list of preferred language codes from EFli on USIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_LI_LANGUAGE, SIM_PREF_LANGUAGE_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_PREF_LANGUAGE_STATUS)
	    COMMENT(COMMENT_TEXT, "Number of language indication codes available on card.")
        VALUE(8, BE, Count, "Count", DEC)
	    COMMENT(COMMENT_TEXT, "List of language indication codes from EFli on USIM.")
        SEQ_OF_REF(Languages, "Languages", AUTOGEN_SEQ_BYTE_HEX, REF_AS_MANY_AS_POSSIBLE, ISIHDR_MARKER_SINGLE_ELEMENT)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_LI_LANGUAGE, SIM_PREF_LANGUAGE_REQ, SIM_ST_READ_LI_LANGUAGE, SIM_PREF_LANGUAGE_RESP)

    /* SIM_PREF_LANGUAGE - SIM_ST_WRITE_PL_LANGUAGE */    


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_LanguageWrite_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message updates the list of preferred language codes in the Master File EFpl on USIM.")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "This update is only executed if ICC is an USIM card")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_WRITE_LI_LANGUAGE.") 
    SUB_MSG_BEGIN(SIM_ST_WRITE_PL_LANGUAGE, SIM_PREF_LANGUAGE_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)  
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Number of preferred language codes available on card.")
        REFERENCE(8, BE, Count, "Count", C)
        REFERENCE_TRANSFORM(C, D, ALG_MUL, 2)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "List of preferred language codes to write to EFpl on USIM.")
        SEQ_OF_REF(Languages, "Languages", AUTOGEN_SEQ_BYTE_HEX, D, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SUB_MSG_END
   

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_LanguageWrite_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of updating the Master File EFpl on USIM.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_WRITE_LI_LANGUAGE.") 
    SUB_MSG_BEGIN(SIM_ST_WRITE_PL_LANGUAGE, SIM_PREF_LANGUAGE_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PREF_LANGUAGE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_PL_LANGUAGE, SIM_PREF_LANGUAGE_REQ, SIM_ST_WRITE_PL_LANGUAGE, SIM_PREF_LANGUAGE_RESP)

    /* SIM_PREF_LANGUAGE - SIM_ST_WRITE_LI_LANGUAGE */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message updates the list of preferred language codes in EFli on the active application on USIM.")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "This update is only executed if ICC is an USIM card")         
    SUB_MSG_BEGIN(SIM_ST_WRITE_LI_LANGUAGE, SIM_PREF_LANGUAGE_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, Count, "Count", C)
        REFERENCE_TRANSFORM( C, D, ALG_MUL, 2)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "List of preferred language codes to write to EFli on USIM.")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SEQ_OF_REF(Languages, "Languages", AUTOGEN_SEQ_BYTE_HEX, D, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of updating EFli on USIM.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_LI_LANGUAGE, SIM_PREF_LANGUAGE_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)  
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_PREF_LANGUAGE_STATUS)
    SUB_MSG_END 

    SUB_MSG_PAIR(SIM_ST_WRITE_LI_LANGUAGE, SIM_PREF_LANGUAGE_REQ, SIM_ST_WRITE_LI_LANGUAGE, SIM_PREF_LANGUAGE_RESP)

    /* SIM_PREF_LANGUAGE - READ_PREF_LANGUAGE */    

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PrefLanguageReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the list of preferred language codes from EFlp on SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "On USIM EFlp is not available.If this request is send by server/application and current ICC is a USIM the ")
    COMMENT(COMMENT_TEXT, "response will include the langauges specified in Master file EFpl, but coded as the languages in EFlp.")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "An example:")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "Coding in EFpl : One language is coded like (ISO 639:1988): 'd','a' - Danish")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Coding in EFlp : One language is coded in one byte according to GSM 03.38. Danish has valu: 0x07.")
    COMMENT(COMMENT_PARAGRAPH, " ")
    COMMENT(COMMENT_TEXT, "The two bytes 'd','a' is translated to 0x07.")
    SUB_MSG_BEGIN(READ_PREF_LANGUAGE, SIM_PREF_LANGUAGE_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    /* These comments belong to SIM_STATUS_REQ - CARD STATUS below - but have to be placed here in the macro file
    to ensure that the lines are placed correctly in the isi header file */
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_STATUS_REQ.SIM_ST_CARD_STATUS                              */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "   ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_CardStatus_Req tSIM_Request")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PrefLanguageReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the list of preferred language codes from EFlp on SIM.")
    SUB_MSG_BEGIN(READ_PREF_LANGUAGE, SIM_PREF_LANGUAGE_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Number of language code available on card.")
        VALUE(8, BE, Count, "Count", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "List of preferred language codes from EFlp or translated from EFpl in case of USIM.")
        SEQ_OF(LanguageTable, "Languages", AUTOGEN_SEQ_BYTE_HEX, SIM_LANG_PREF_LEN) 
    SUB_MSG_END
    
    SUB_MSG_PAIR(READ_PREF_LANGUAGE, SIM_PREF_LANGUAGE_REQ, READ_PREF_LANGUAGE, SIM_PREF_LANGUAGE_RESP)
    
    /* SIM_STATUS_REQ - CARD_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request the status of the (U)SIM card."
    			  " The status indicates if card is connected or or disconncected.")
    SUB_MSG_BEGIN(SIM_ST_CARD_STATUS, SIM_STATUS_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        VALUE(8, BE, TransID, "Transaction ID", DEC) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) \
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_STATUS_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_NOT_INITIALISED)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* These comments belong to SIM_STATUS_REQ - SIM_ST_SIMLOCK_STATUS below - but have to be placed here in the macro file
    to ensure that the lines are placed correctly in the isi header file */
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_STATUS_REQ.SIM_ST_SIMLOCK_STATUS                           */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "   ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_SIMLOCK_STATUS_REQ tSIM_Request")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CardStatus_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the status of the (U)SIM card."
                          " The status indicates if card is connected or disconncected.")
    SUB_MSG_BEGIN(SIM_ST_CARD_STATUS, SIM_STATUS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) \
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
        VALUE_CONST(Status, "Status", SIM_STATUS_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "CardTypeRead is TRUE if card is connected and FALSE if card is disconnected.")
        VALUE_CONST(CardTypeRead, "CardTypeRead", TRUE_FALSE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Cardtype is 'UE operation mode'(USIM) or 'MS operation mode'(SIM) byte from the EFad filefstatus.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Cardtype is 0xFF if CardTypeRead is FALSE.")
        VALUE_CONST(Cardtype, "Cardtype", SIM_SB_CARD_TYPE)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_CARD_STATUS, SIM_STATUS_REQ, SIM_ST_CARD_STATUS, SIM_STATUS_RESP)

    /* SIM_STATUS_REQ - SIM_ST_SIMLOCK_STATUS */
    
    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request the result of SIMLock validation done by SIM server.")
    SUB_MSG_BEGIN(SIM_ST_SIMLOCK_STATUS, SIM_STATUS_REQ, MESSAGE_REQ, "", "")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_STATUS_SIMLOCK_STATUS, SIM_SIMLOCK_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_SIMLOCK_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTION_ON)
        DER_CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTED)
        DER_CONST_TBL_ENTRY(SIM_STA_SIMLOCK_RESTRICTION_PENDING)
        DER_CONST_TBL_ENTRY(SIM_STA_SIMLOCK_STATUS_NOT_INITIALIZED)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SIMLOCK_STATUS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of the validation done by SIM server.")
    SUB_MSG_BEGIN(SIM_ST_SIMLOCK_STATUS, SIM_STATUS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) \
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) \
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) \
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) \
        COMMENT(COMMENT_TEXT, "Result of SIMLock validation.")
        VALUE_CONST(Status, "Status", SIM_STATUS_SIMLOCK_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SIMLOCK_STATUS, SIM_STATUS_REQ, SIM_ST_SIMLOCK_STATUS, SIM_STATUS_RESP)

    /* SIM_IMSI_REQ - READ_IMSI */

    DER_CONST_TBL_BEGIN(SIM_IMSI_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ImsiReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request IMSI number available in EF imsi on (U)SIM.")
    SUB_MSG_BEGIN(READ_IMSI, SIM_IMSI_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ImsiReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns IMSI number available in EF imsi on (U)SIM..")
    SUB_MSG_BEGIN(READ_IMSI, SIM_IMSI_RESP, MESSAGE_RESP, "", "")  
        SUB_MSG_INFO_HDR(SIM_IMSI_STATUS)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Imsi         Imsi;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "IMSI number.")
        SEQ_OF(Imsi, "Imsi", SIM_RESP_IMSI, 1)
    SUB_MSG_END
    
    SUB_MSG_PAIR(READ_IMSI, SIM_IMSI_REQ, READ_IMSI, SIM_IMSI_RESP)

    /* SIM_IMSI_EQUAL_REQ - NO_SERVICE_TYPE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IMSI_Equal_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to compare the IMSI available at current and previous initialization of the ME .")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This indicates if the (subscription has been changed.")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_IMSI_EQUAL_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_IMSI_EQUAL_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_IMSI_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_IMSI_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IMSI_Equal_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of IMSI number comparison.")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_IMSI_EQUAL_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_IMSI_EQUAL_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(NO_SERVICE_TYPE, SIM_IMSI_EQUAL_REQ, NO_SERVICE_TYPE, SIM_IMSI_EQUAL_RESP)

    /* SIM_IMSI_EQUAL_REQ - ICC_EQUAL */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Icc_Equal_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to compare the content of the EFiccid file available at current and previous initialization of the ME .")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This indicates if the (U)SIM card has been changed.")
    SUB_MSG_BEGIN(ICC_EQUAL, SIM_IMSI_EQUAL_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_IMSI_ICC_EQUAL_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_ICC_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Icc_Equal_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of EFiccid file comparison.")
    SUB_MSG_BEGIN(ICC_EQUAL, SIM_IMSI_EQUAL_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_IMSI_ICC_EQUAL_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(ICC_EQUAL, SIM_IMSI_EQUAL_REQ, ICC_EQUAL, SIM_IMSI_EQUAL_RESP)

    /* SIM_SMS_REQ - READ_PARAMETER */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ReadParam_req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests a SMS parameters from a given location in EFsms.")     
    SUB_MSG_BEGIN(READ_PARAMETER, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Location where to get SMS parameters in EFsms.")     
        VALUE(8, BE, LocationNumber, "LocationNumber", DEC)
    SUB_MSG_END 
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ReadParam_resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(READ_PARAMETER, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location where SMS parameters in EFsms are fetched.")     
        VALUE(8, BE, LocationNumber, "LocationNumber", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 11.11 EFsmsp. Is not defined if status is different from SIM_SERV_OK.")     
        VALUE(8, BE, ParametersIndicators, "ParametersIndicators", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-PID. Is not defined if status is different from SIM_SERV_OK.")     
        VALUE(8, BE, ProtocolID, "ProtocolID", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-DCS. Is not defined if status is different from SIM_SERV_OK.")     
        VALUE(8, BE, DataCodingScheme, "DataCodingScheme", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40. Is not defined if status is different from SIM_SERV_OK.")     
        SEQ_OF(DestinationAddress, "DestinationAddress", AUTOGEN_SEQ_BYTE_HEX, SMS_ADDRESS_MAX_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 04.11 TP-PID. Is not defined if status is different from SIM_SERV_OK.")
        SEQ_OF(ServiceCenterAddress, "ServiceCenterAddress", AUTOGEN_SEQ_BYTE_HEX, SMS_ADDRESS_MAX_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-VP. Is not defined if status is different from SIM_SERV_OK.")
        VALUE(8, BE, ValidityPeriod, "ValidityPeriod", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Length of the string in the AlphaTag, incl zero termination.")
        VALUE(8, BE, Length, "Length", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "SMS message. Is not defined if status is different from SIM_SERV_OK.")
        STRING(STRING_UNICODE_ZERO_TERMINATED, BE, AlphaTag, "AlphaTag", SMS_ALPHA_TAG_MAX_LENGTH + 1)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_PARAMETER, SIM_SMS_REQ, READ_PARAMETER, SIM_SMS_RESP)

    /* SIM_SMS_REQ - UPDATE_PARAMETER */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_UpdateParam_req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message writes SMS parameters to a give location on SIM, EFsmsp.")     
    SUB_MSG_BEGIN(UPDATE_PARAMETER, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location to write SMS parameters in EFsmsp.")     
        VALUE(8, BE, LocationNumber, "LocationNumber", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
 	COMMENT(COMMENT_TEXT, "See GSM 11.11 EFsmsp.")     
        VALUE(8, BE, ParametersIndicators, "ParametersIndicators", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-PID.")     
        VALUE(8, BE, ProtocolID, "ProtocolID", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-DCS.")     
        VALUE(8, BE, DataCodingScheme, "DataCodingScheme", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40 TP-VP.")
        VALUE(8, BE, ValidityPeriod, "ValidityPeriod", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 03.40.")     
        SEQ_OF(DestinationAddress, "DestinationAddress", AUTOGEN_SEQ_BYTE_HEX, SMS_ADDRESS_MAX_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "See GSM 04.11 TP-PID.")
        SEQ_OF(ServiceCenterAddress, "ServiceCenterAddress", AUTOGEN_SEQ_BYTE_HEX, SMS_ADDRESS_MAX_LENGTH)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ALL_OUTPUTS)
        COMMENT(COMMENT_TEXT, "Length of string in AlphaTag field incl zero termination. Note: Most sw versions don't use the value! The AlphaTag is read until zero termination independent of value in this field!")
        VALUE(8, BE, Length, "Length", DEC)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "SMS message.")
        STRING(STRING_UNICODE_ZERO_TERMINATED, BE, AlphaTag, "AlphaTag", SMS_ALPHA_TAG_MAX_LENGTH + 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SMS_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_UpdateParam_resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing SMS parameters to a give location on SIM, EFsmsp.")
    SUB_MSG_BEGIN(UPDATE_PARAMETER, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SMS_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(UPDATE_PARAMETER, SIM_SMS_REQ, UPDATE_PARAMETER, SIM_SMS_RESP)

    /* SIM_SMS_REQ - READ_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ReadStatus_req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message reads SMS status (message reference and memory capacity exceeded flag) from EFsmss.")     
    SUB_MSG_BEGIN(READ_STATUS, SIM_SMS_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ReadStatus_resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns SMS status (message reference and memory capacity exceeded flag) from EFsmss.")
    SUB_MSG_BEGIN(READ_STATUS, SIM_SMS_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "TP-Message reference from last SMS. See GSM 11.11 and GSM 3.40. Is not defined if status is different from SIM_SERV_OK.")
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "True: Memory capacity available. See See GSM 11.11. Is not defined if status is different from SIM_SERV_OK.")
        VALUE(8, BE, MessageCapacityExceeded, "MessageCapacityExceeded", DEC)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_STATUS, SIM_SMS_REQ, READ_STATUS, SIM_SMS_RESP)

    /* SIM_SMS_REQ - WRITE_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WriteStatus_req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message writes SMS status (message reference and memory capacity exceeded flag) from EFsmss.")          
    SUB_MSG_BEGIN(WRITE_STATUS, SIM_SMS_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "TP-Message reference from last SMS. See GSM 11.11 and GSM 3.40.")
        VALUE(8, BE, MessageReference, "MessageReference", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "bool8")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "True: Memory capacity available. See See GSM 11.11.")
        VALUE(8, BE, MessageCapacityExceeded, "MessageCapacityExceeded", DEC)
    SUB_MSG_END
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WriteStatus_resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing SMS status (message reference and memory capacity exceeded flag) from EFsmss.")           
    SUB_MSG_BEGIN(WRITE_STATUS, SIM_SMS_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SMS_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(WRITE_STATUS, SIM_SMS_REQ, WRITE_STATUS, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_GET_NUM_OF_LOC */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_GET_NUM_OF_LOC_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the maximum number of SMS messages that can be stored on the (U)SIM card.")
    SUB_MSG_BEGIN(SIM_ST_SMS_GET_NUM_OF_LOC, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SMS_STA_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_GET_NUM_OF_LOC_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the maximum number of SMS messages that can be stored on the (U)SIM card.") 
    SUB_MSG_BEGIN(SIM_ST_SMS_GET_NUM_OF_LOC, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SMS_STA_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Maximum number of SMS messages that can be stored on the (U)SIM card.")
        VALUE(8, BE, NumOfLoc, "NumOfLoc", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_GET_NUM_OF_LOC, SIM_SMS_REQ, SIM_ST_SMS_GET_NUM_OF_LOC, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_READ_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This messages reads a specific SMS stored on (U)SIM, EFsms.")
    SUB_MSG_BEGIN(SIM_ST_SMS_READ, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Location to read SMS in EFsms.")
        VALUE(8, BE, Location, "Location", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_SMS_READ_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SIM_STA_LOCATION_EMPTY)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_READ_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This messages returns a SMS read at a specific SMS stored on (U)SIM, EFsms.")
    SUB_MSG_BEGIN(SIM_ST_SMS_READ, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_SMS_READ_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location of SMS in EFsms.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Location is between 1 and number of locations on (U)SIM.")
        VALUE(8, BE, Location, "Location", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Storage status of SMS.")
        VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, NumOfSubblocks, "NumOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "sub_blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_DELIVER_ID)
            SB_LST_ENTRY(SIM_SB_SMS_STATUS_REPORT_ID)
            SB_LST_ENTRY(SIM_SB_SMS_SUBMIT_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMAND_ID)
            SB_LST_ENTRY(SIM_SB_SMS_MO_UNDEFINED_ID)
            SB_LST_ENTRY(SIM_SB_SMS_MT_UNDEFINED_ID) 
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_READ, SIM_SMS_REQ, SIM_ST_SMS_READ, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WRITE_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message writes a specific SMS to (U)SIM, EFsms.")
    SUB_MSG_BEGIN(SIM_ST_SMS_WRITE, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location to write SMS parameters in EFsms.")
        VALUE(8, BE, Location, "Location", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Storage status of SMS.")
        VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, NumOfSubblocks, "NumOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "sub_blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SMS_DELIVER_ID)
            SB_LST_ENTRY(SIM_SB_SMS_STATUS_REPORT_ID)
            SB_LST_ENTRY(SIM_SB_SMS_SUBMIT_ID)
            SB_LST_ENTRY(SIM_SB_SMS_COMMAND_ID)
            SB_LST_ENTRY(SIM_SB_SMS_MO_UNDEFINED_ID)
            SB_LST_ENTRY(SIM_SB_SMS_MT_UNDEFINED_ID) 
        SB_LST_REF_END
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_SMS_WRITE_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WRITE_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing a specific SMS to (U)SIM, EFsms.")
    SUB_MSG_BEGIN(SIM_ST_SMS_WRITE, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_SMS_WRITE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_WRITE, SIM_SMS_REQ, SIM_ST_SMS_WRITE, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_ERASE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ERASE_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message removes one or all SMS's in EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_ERASE, SIM_SMS_REQ, MESSAGE_REQ, "","")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Location of SMS to remove from EFsms on (U)SIM..")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Remove specific SMS: Location is between 1 and number of locations on (U)SIM.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Remove all SMS's: Location is 0.")     
        VALUE(8, BE, Location, "Location", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_SMS_ERASE_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_ERASE_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of removing one or all SMS's in EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_ERASE, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_SMS_ERASE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_ERASE, SIM_SMS_REQ, SIM_ST_SMS_ERASE, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_UPDATE_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_UPDATE_STATUS_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message updates the status of a specific SMS in EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_UPDATE_STATUS, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location of SMS status to update.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Location is between 1 and number of locations on (U)SIM.")
        VALUE(8, BE, Location, "Location", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Storage status of SMS.")
        VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SMS_RESP_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_UPDATE_STATUS_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of SMS status update.")         
    SUB_MSG_BEGIN(SIM_ST_SMS_UPDATE_STATUS, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SMS_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_UPDATE_STATUS, SIM_SMS_REQ, SIM_ST_SMS_UPDATE_STATUS, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_READ_RAW */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_READ_RAW_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This messages requests a specific SMS, in raw format, from EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_READ_RAW, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location of SMS to read.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Location is between 1 and number of locations on (U)SIM.")
        VALUE(8, BE, Location, "Location", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_SMS_READ_RAW_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SIM_STA_LOCATION_EMPTY)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_READ_RAW_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns a specific SMS, in raw format, from EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_READ_RAW, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_SMS_READ_RAW_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location of SMS in EFsms.")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Location is between 1 and number of locations on (U)SIM.")
        VALUE(8, BE, Location, "Location", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Storage status of SMS.")
        VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "SMS in raw format.")
	SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_READ_RAW, SIM_SMS_REQ, SIM_ST_SMS_READ_RAW, SIM_SMS_RESP)

    /* SIM_SMS_REQ - SIM_ST_SMS_WRITE_RAW */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WRITE_RAW_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message writes a specific SMS, in raw format, in EFsms on (U)SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This request overwrites the specified location in EFsms even though the location is not empty.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The user of this interface keeps trace of the locations in EFsms on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SMS_WRITE_RAW, SIM_SMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Location to write a SMS in EFsms on (U)SIM..")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "Remove specific SMS: Location is between 1 and number of locations on (U)SIM.")
        VALUE(8, BE, Location, "Location", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Storage status of SMS.")
        VALUE_CONST(StorageStatus, "StorageStatus", SIM_SMS_MSG_STATUS_TABLE)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "SMS in raw format.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

/*
    DER_CONST_TBL_BEGIN(SIM_ST_SMS_WRITE_RAW_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_INVALID_LOCATION)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
*/
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SMS_WRITE_RAW_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing a specific SMS, in raw format, in EFsms on (U)SIM.")         
    SUB_MSG_BEGIN(SIM_ST_SMS_WRITE_RAW, SIM_SMS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Result")         
        VALUE_CONST(Status, "Status", SIM_ST_SMS_READ_RAW_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SMS_WRITE_RAW, SIM_SMS_REQ, SIM_ST_SMS_WRITE_RAW, SIM_SMS_RESP)

    /* SIM_ATK_REQ - SIM_ST_SET_POLLING */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_POLLING_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""
        "The purpose of the request is to change the time of how often the     "
        "(U)SIM Card is polled. By default the card is polled every 25 seconds."
        "With this request the polling can be changed to everything between    "
        "5 and 25 seconds.                                                     "
        "                                                                      " ) 
    SUB_MSG_BEGIN(SIM_ST_SET_POLLING, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Poll Interval */        
        COMMENT(COMMENT_PARAGRAPH,
            "The time in seconds between the polling of the (U)SIM Card. Value can be between 5 and 25 "
            "seconds. If PollInterval is set to 0, the poll interval is change to the default value of "
            "25 seconds.")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 25)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, PollInterval, "PollInterval", DEC)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ATK_RESP_STATUS, SIM_SERV_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_STA_AID_NOT_ACTIVE)        
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_POLLING_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")         
    SUB_MSG_BEGIN(SIM_ST_SET_POLLING, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
        /* Poll Interval */        
        COMMENT(COMMENT_PARAGRAPH,
            "The actual value of the poll interval. Can be different from the requested value.")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 25)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 5)
        VALUE(8, BE, PollInterval, "PollInterval", DEC)   
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET_POLLING, SIM_ATK_REQ, SIM_ST_SET_POLLING, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_INIT_FROM_PIN */

    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This structure is also valid for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")    
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_FCN,")
    COMMENT(COMMENT_NEWLINE, "")				
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_INIT_FROM_PIN_FCN,")
    COMMENT(COMMENT_NEWLINE, "")				
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_INIT_FROM_PIN_FFCN,")
    COMMENT(COMMENT_NEWLINE, "")				
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_RESET,")
    COMMENT(COMMENT_NEWLINE, "")				
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_APPLICATION_RESET,")
    COMMENT(COMMENT_NEWLINE, "")				
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_REFRESH_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'NAA initialization', see ETSI TS 102 223."
        "ICC is initialized after PIN verification                   ")
    COMMENT(COMMENT_PARAGRAPH,    ""
        "The REFRESH command is used by the ICC to tell the ME that files on the "
        "card has been changed and they should be reread if they are cached in the phone "
        "or that the ICC should be reset."
        "                                                                                  "
        "This specific message requests the ME to start the ICC initialization after PIN verification."
        "                                                                                  "
        "If the SIM_SB_AID_ID is included, then "
        "the SIM Server will check if the AID corresponds to the current active AID. The "
        "refresh will only be executed if the specified AID is the same as the current "
        "active." ) 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID. 0-255 sub blocks of type SIM_SB_REFRESH_FILE_ID, "
            "dependend on the type of refresh.")
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
  

    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This structure is also valid for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_FCN,")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_INIT_FROM_PIN_FCN,")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_INIT_FROM_PIN_FFCN,")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_RESET,")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_APPLICATION_RESET,")
    COMMENT(COMMENT_NEWLINE, "")   
    COMMENT(COMMENT_TEXT, "SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET.")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_REFRESH_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_INIT_FROM_PIN, SIM_ATK_REQ, SIM_ST_REFRESH_INIT_FROM_PIN, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_FCN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH,    ""
        "This message executes refresh of type 'File Change Notification', see ETSI TS 102 223."
        "The EF files specified in DFtelecom has been updated and has to be reread"
        "                                                                                  "
        "In this case a number of sub blocks specifying the File "
        "IDs shall be included (SIM_SB_REFRESH_FILE_ID). If the ICC is a USIM a "
        "(SIM_SB_AID_ID) sub block can be included. If the SIM_SB_AID_ID is included, then "
        "the SIM Server will check if the AID corresponds to the current active AID. The "
        "refresh will only be executed if the specified AID is the same as the current "
        "active." )     
    SUB_MSG_BEGIN(SIM_ST_REFRESH_FCN, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
	/* Card id */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID. 0-255 sub blocks of type SIM_SB_REFRESH_FILE_ID, "
            "specifies the File IDs.")        
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_FCN, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_FCN, SIM_ATK_REQ, SIM_ST_REFRESH_FCN, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_INIT_FROM_PIN_FCN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")  
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'NAA initialization' and 'File Change Notification', see ETSI TS 102 223."
        "ICC is initialized after PIN verification. Then the  EF files specified in DFtelecom has been updated and has to be reread")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN_FCN, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
	/* Card id */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID. 0-255 sub blocks of type SIM_SB_REFRESH_FILE_ID, "
            "specifies the file IDs.")
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN_FCN, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_INIT_FROM_PIN_FCN, SIM_ATK_REQ, SIM_ST_REFRESH_INIT_FROM_PIN_FCN, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_INIT_FROM_PIN_FFCN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'NAA initialization' and 'Full File Change Notification', see ETSI TS 102 223. "
        "ICC is initialized after PIN verification. All EF files are reread")
        SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN_FFCN, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
	/* Card id */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID.")
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_INIT_FROM_PIN_FFCN, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_INIT_FROM_PIN_FFCN, SIM_ATK_REQ, SIM_ST_REFRESH_INIT_FROM_PIN_FFCN, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_RESET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'UICC reset', see ETSI TS 102 223.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_RESET, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
	VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID.")
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_RESET, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_RESET, SIM_ATK_REQ, SIM_ST_REFRESH_RESET, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_APPLICATION_RESET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'NAA application reset', see ETSI TS 102 223. This is only valid on USIM.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_APPLICATION_RESET, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID. 0-255 sub blocks of type SIM_SB_REFRESH_FILE_ID, "
            "dependend on the type of refresh.")
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_APPLICATION_RESET, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_APPLICATION_RESET, SIM_ATK_REQ, SIM_ST_REFRESH_APPLICATION_RESET, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, ""               
        "This message executes refresh of type 'NAA session reset', see ETSI TS 102 223. This is only valid on USIM.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_PARAGRAPH,
            "0-1 sub block of type SIM_SB_AID_ID. 0-255 sub blocks of type SIM_SB_REFRESH_FILE_ID, "
            "dependend on the type of refresh.")
	REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_REFRESH_FILE_ID)
        SB_LST_REF_END
    SUB_MSG_END
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET, SIM_ATK_REQ, SIM_ST_REFRESH_REFRESH_3G_SESSION_RESET, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_READ_ICON */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read icon(s) from EFimg on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_ICON, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_PARAGRAPH,
            "ID representing the Card ID. The Card ID is specified by the client controling the (U)SIM, "
            "and is refereing to a specific Card. The Card ID shall be used in all communication to "
            "the client controlling the (U)SIM. Value between 0..7, 8..255 is RFU.                      ")
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Number of Location */
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The RecordNumber addresses a record in EFimg, containing one or more instances of the specified icon.")
        VALUE(8, BE, RecordNumber, "The RecordNumber addresses a record", DEC)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns icon(s) from EFimg on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_ICON, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ICON_DATA_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_ICON, SIM_ATK_REQ, SIM_ST_READ_ICON, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_READ_ICON_CLUT */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_CLUT_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the CLUT of one specific instance of an icon from EFimg on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_ICON_CLUT, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Number of Location */
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The RecordNumber addresses a record in EFimg, containing one or more instances of the specified icon.")
        VALUE(8, BE, RecordNumber, "The RecordNumber addresses a record", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Icon instance in record that should be returned. Instance numbers starts with value 1")
        VALUE(8, BE, IconInstanceNumber, "Icon instance in record", DEC)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_CLUT_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the CLUT of one specific instance of an icon from EFimg on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_ICON_CLUT, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ICON_DATA_CLUT_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_ICON_CLUT, SIM_ATK_REQ, SIM_ST_READ_ICON_CLUT, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_READ_ICON_BODY_DATA */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_BODY_DATA_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the body data of one specific instance of an icon from EFimg on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_ICON_BODY_DATA, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        /* Number of Location */
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "The RecordNumber addresses a record in EF-IMG, containing one or more instances of the specified icon.")
        VALUE(8, BE, RecordNumber, "The RecordNumber addresses a record", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Icon instance in record that should be returned. Instance numbers starts with value 1")
        VALUE(8, BE, IconInstanceNumber, "Icon instance in record", DEC)
        /* Filler bytes */
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ICON_BODY_DATA_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the body data of one specific instance of an icon from EFimg on (U)SIM.")    
    SUB_MSG_BEGIN(SIM_ST_READ_ICON_BODY_DATA, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        /* Number of sub blocks */
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)        
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ICON_BODY_DATA_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_ICON_BODY_DATA, SIM_ATK_REQ, SIM_ST_READ_ICON_BODY_DATA, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_SEND_ENVELOPE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ENVELOPE_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to send an Envelope to UICC.")    
    SUB_MSG_BEGIN(SIM_ST_SEND_ENVELOPE, SIM_ATK_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        /* Card id */
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 7)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        VALUE(8, BE, CardId, "Card ID", HEX)
        REFERENCE(8, BE, DataLength, "Data Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Data is packed in TLV format.")
        SEQ_OF_REF(EnvelopeData, "Envelope Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_ENVELOPE_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the response to an Envelope, received from UICC, to a client.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "It is the responsibility of the client to handle retransmission, if nessesary.")        
    SUB_MSG_BEGIN(SIM_ST_SEND_ENVELOPE, SIM_ATK_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ATK_RESP_STATUS)
        VALUE(8, BE, SW1, "SW1 from the UICC", HEX)
        VALUE(8, BE, SW2, "SW2 from the UICC", HEX)
        REFERENCE(16, BE, DataLength, "Data Length", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Data is packed in TLV format.")
        SEQ_OF_REF(ResponseData, "Data returned from the UICC", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SEND_ENVELOPE, SIM_ATK_REQ, SIM_ST_SEND_ENVELOPE, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_CAT_SUPPORT_ENABLE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_CAT_ENABLE_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to enable the Card Application Toolkit in the ME.")
    SUB_MSG_BEGIN(SIM_ST_CAT_SUPPORT_ENABLE, SIM_ATK_REQ, MESSAGE_REQ, "017.001", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_CAT_SUPPORT_ENABLE_STATUS_TABLE, SIM_STATUS_TABLE, "017.001", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_CAT_ENABLE_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of enabling the Card Application Toolkit in the ME.")
    SUB_MSG_BEGIN(SIM_ST_CAT_SUPPORT_ENABLE, SIM_ATK_RESP, MESSAGE_RESP, "017.001", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(status, "status", SIM_ST_CAT_SUPPORT_ENABLE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_CAT_SUPPORT_ENABLE, SIM_ATK_REQ, SIM_ST_CAT_SUPPORT_ENABLE, SIM_ATK_RESP)

    /* SIM_ATK_REQ - SIM_ST_CAT_SUPPORT_DISABLE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_CAT_DISABLE_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to disable the Card Application Toolkit in the ME.")
    SUB_MSG_BEGIN(SIM_ST_CAT_SUPPORT_DISABLE, SIM_ATK_REQ, MESSAGE_REQ, "017.001", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_CAT_SUPPORT_DISABLE_STATUS_TABLE, SIM_STATUS_TABLE, "017.001", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ATK_CAT_DISABLE_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of disabling the Card Application Toolkit in the ME.")
    SUB_MSG_BEGIN(SIM_ST_CAT_SUPPORT_DISABLE, SIM_ATK_RESP, MESSAGE_RESP, "017.001", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(status, "status", SIM_ST_CAT_SUPPORT_DISABLE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_CAT_SUPPORT_DISABLE, SIM_ATK_REQ, SIM_ST_CAT_SUPPORT_DISABLE, SIM_ATK_RESP)

    /* SIM_SERV_PROV_NAME_REQ - SIM_ST_READ_SERV_PROV_NAME */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ServProvNameReadReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Service Provider Name in EFspn on the (U)SIM card.")
    SUB_MSG_BEGIN(SIM_ST_READ_SERV_PROV_NAME, SIM_SERV_PROV_NAME_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SERV_PROV_NAME_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ServProvNameReadResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Service Provider Name in EFspn on the (U)SIM card.")
    SUB_MSG_BEGIN(SIM_ST_READ_SERV_PROV_NAME, SIM_SERV_PROV_NAME_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_SERV_PROV_NAME_STATUS)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_ServiceProvider    ServiceProvider;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Service Provider Name.")
        SEQ_OF(ServiceProvider, "ServiceProvider", SERVICE_PROVIDER, 1)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_READ_SERV_PROV_NAME, SIM_SERV_PROV_NAME_REQ, SIM_ST_READ_SERV_PROV_NAME, SIM_SERV_PROV_NAME_RESP)

    /* SIM_SERV_PROV_NAME_REQ - SIM_ST_SPN_DISPLAY_INFO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SERV_PROV_DISPLAY_INFO_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read a list of PLMNs from EFspdi on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SPN_DISPLAY_INFO, SIM_SERV_PROV_NAME_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE(8, BE, Paddingbyte, "Paddingbyte", DEC) 
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SERV_PROV_DISPLAY_INFO_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns a list of PLMNs from EFspdi on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_SPN_DISPLAY_INFO, SIM_SERV_PROV_NAME_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", REF_AS_MANY_AS_POSSIBLE, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_SPN_DISPLAY_INFO_PLMNS_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SPN_DISPLAY_INFO, SIM_SERV_PROV_NAME_REQ, SIM_ST_SPN_DISPLAY_INFO, SIM_SERV_PROV_NAME_RESP)
    
    /* SIM_VOICE_MSG_REQ - SIM_ST_WRITE_FLAGS */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tSIM_WriteVoiceMsgFlagsReq;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteVoiceMsgFlagsReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write Voice Message Waiting flags to the SIM card.")
    COMMENT(COMMENT_NEWLINE, "")	
    COMMENT(COMMENT_TEXT, "This message is related to CPHS only. Use newer version SIM_ST_WRITE_MSG_FLAGS(SIM_VOICE_MSG_REQ)")
    SUB_MSG_BEGIN(SIM_ST_WRITE_FLAGS, SIM_VOICE_MSG_REQ, MESSAGE_REQ, "013.000", "")
        SUB_MSG_REQUEST_HDR
        SEQ_OF(OptionalData, "OptionalData", SIM_SERV_VOICE_MSG_OPTIONAL_DATA, 1)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        SEQ_OF(VoiceMsgFlags, "VoiceMsgFlags", SIM_SERV_VOICE_MSG_WAIT_FLAG, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_VOICE_MSG_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
/*        DER_CONST_TBL_ENTRY(NO_STATUS_FROM_SUBSYSTEM)*/
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteVoiceMsgFlagsResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing Voice Message Waiting flags to the SIM card.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_FLAGS, SIM_VOICE_MSG_RESP, MESSAGE_RESP, "013.000", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_FLAGS, SIM_VOICE_MSG_REQ, SIM_ST_WRITE_FLAGS, SIM_VOICE_MSG_RESP)

    /* SIM_VOICE_MSG_REQ - SIM_ST_READ_FLAGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadVoiceMsgFlagsReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read Voice Message Waiting flags from the SIM card.")
    COMMENT(COMMENT_NEWLINE, "")	
    COMMENT(COMMENT_TEXT, "This message is related to CPHS only. Use newer version SIM_ST_READ_MSG_FLAGS(SIM_VOICE_MSG_REQ)")
    SUB_MSG_BEGIN(SIM_ST_READ_FLAGS, SIM_VOICE_MSG_REQ, MESSAGE_REQ, "013.000", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tSIM_ReadVoiceMsgFlagsResp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadVoiceMsgFlagsResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Voice Message Waiting flags from the SIM card.")
    SUB_MSG_BEGIN(SIM_ST_READ_FLAGS, SIM_VOICE_MSG_RESP, MESSAGE_RESP, "013.000", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
        SEQ_OF(OptionalData, "OptionalData", SIM_SERV_VOICE_MSG_OPTIONAL_DATA, 1)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        SEQ_OF(VoiceMsgFlags, "VoiceMsgFlags", SIM_SERV_VOICE_MSG_WAIT_FLAG, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_FLAGS, SIM_VOICE_MSG_REQ, SIM_ST_READ_FLAGS, SIM_VOICE_MSG_RESP)

    /* SIM_VOICE_MSG_REQ - SIM_ST_WRITE_MSG_FLAGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_WRITE_MSG_FLAGS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write the message waiting indicator flags to (U)SIM "
                          "both according to Common PCN Handset Specification(CPHS) and release 4.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "CPHS: The information is written into EF_6F11 on SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "Release 4: The information is written into EFmwis on (U)SIM.")
        SUB_MSG_BEGIN(SIM_ST_WRITE_MSG_FLAGS, SIM_VOICE_MSG_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
	PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, NbrOfSubblocks, "NbrOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_CPHS_MSG_FLAGS_ID)
            SB_LST_ENTRY(SIM_SB_REL4_MSG_FLAGS_ID)
        SB_LST_REF_END
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_REL4_MSG_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_WRITE_MSG_FLAGS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing the message waiting indicator flags to (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_MSG_FLAGS, SIM_VOICE_MSG_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_REL4_MSG_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_MSG_FLAGS, SIM_VOICE_MSG_REQ, SIM_ST_WRITE_MSG_FLAGS, SIM_VOICE_MSG_RESP)

    /* SIM_VOICE_MSG_REQ - SIM_ST_READ_MSG_FLAGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_READ_MSG_FLAGS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the message waiting indicator flags from (U)SIM.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "CPHS: The information is read from EF_6F11 on SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "Release 4: The information is read from EFmwis on (U)SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If both EF_6F11 and EFmwis is available on SIM card then EFmwis has priority.")
    SUB_MSG_BEGIN(SIM_ST_READ_MSG_FLAGS, SIM_VOICE_MSG_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE(8, BE, Padding, "Padding ID", DEC) 
    SUB_MSG_END

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_CALL_FWD_REQ.SIM_ST_WRITE_FLAGS                            */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Request     Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_SERV_CF_FLAGS_STR Call_FWD_Flags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_WriteCallFwdFlagsReq;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_READ_MSG_FLAGS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the message waiting indicator flags from (U)SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If both EF_6F11 and EFmwis is available on SIM card then EFmwis has priority.")
    SUB_MSG_BEGIN(SIM_ST_READ_MSG_FLAGS, SIM_VOICE_MSG_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_REL4_MSG_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, NbrOfSubblocks, "NbrOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "NumOfSubblocks:")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "0: none")
        COMMENT(COMMENT_NEWLINE, "")
 	COMMENT(COMMENT_TEXT, "1: SIM_SB_REL4_MSG_FLAGS_ID ||"
	                      "   SIM_SB_CPHS_MSG_FLAGS_ID.")	
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_CPHS_MSG_FLAGS_ID)
            SB_LST_ENTRY(SIM_SB_REL4_MSG_FLAGS_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_MSG_FLAGS, SIM_VOICE_MSG_REQ, SIM_ST_READ_MSG_FLAGS, SIM_VOICE_MSG_RESP)

    /* SIM_CALL_FWD_REQ - SIM_ST_WRITE_FLAGS */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteCallFwdFlagsReq")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to update the Call Forwarding flags in the Orange specific EF_6F9F file.")
    COMMENT(COMMENT_NEWLINE, "")	
    COMMENT(COMMENT_TEXT, "This message is related to CPHS only. Use newer version SIM_ST_WRITE_CALL_FWD_FLAGS(SIM_CALL_FWD_REQ)")
    SUB_MSG_BEGIN(SIM_ST_WRITE_FLAGS, SIM_CALL_FWD_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
        COMMENT(COMMENT_TEXT, "Storing the status of a ME flag that indicates if Call Forward Unconditional is active or not.")
        SEQ_OF(Call_FWD_Flags, "Call_FWD_Flags", SIM_SERV_CALL_FWD_FLAG, 1)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteCallFwdFlagsResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of updating the Call Forwarding flags in the Orange specific EF_6F9F file.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_FLAGS, SIM_CALL_FWD_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_FLAGS, SIM_CALL_FWD_REQ, SIM_ST_WRITE_FLAGS, SIM_CALL_FWD_RESP)

    /* SIM_CALL_FWD_REQ - SIM_ST_READ_FLAGS */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_CALL_FWD_RESP.SIM_ST_READ_FLAGS - Valid from version 013.000*/")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_SERV_CF_FLAGS_STR Call_FWD_Flags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_ReadCallFwdFlagsResp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCallFwdFlagsReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Call Forwarding flags in the Orange specific EF_6F9F file.")
    SUB_MSG_BEGIN(SIM_ST_READ_FLAGS, SIM_CALL_FWD_REQ, MESSAGE_REQ, "013.000", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCallFwdFlagsResp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the content of the Orange specific EF_6F9F file.")
    COMMENT(COMMENT_NEWLINE, "")	
    COMMENT(COMMENT_TEXT, "This message is related to CPHS only. Use newer version SIM_ST_READ_CALL_FWD_FLAGS(SIM_CALL_FWD_REQ)")
    SUB_MSG_BEGIN(SIM_ST_READ_FLAGS, SIM_CALL_FWD_RESP, MESSAGE_RESP, "013.000", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
        SEQ_OF(Call_FWD_Flags, "Call_FWD_Flags", SIM_SERV_CALL_FWD_FLAG, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_FLAGS, SIM_CALL_FWD_REQ, SIM_ST_READ_FLAGS, SIM_CALL_FWD_RESP)

    /* SIM_CALL_FWD_REQ - SIM_ST_WRITE_CALL_FWD_FLAGS */
    
    DER_CONST_TBL_BEGIN(SIM_WRITE_CALL_FWD_FLAGS_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_WRITE_CALL_FWD_FLAGS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write the Call Forwarding flags to (U)SIM "
                          "both according to Common PCN Handset Specification(CPHS) and release 4.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "CPHS: The information is written into EF_6F13 on SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "Release 4: The information is written into EFcfis on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_CALL_FWD_FLAGS, SIM_CALL_FWD_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
	PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
        REFERENCE(8, BE, NbrOfSubblocks, "NbrOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_CPHS_CALL_FWD_FLAGS_ID)
            SB_LST_ENTRY(SIM_SB_REL4_CALL_FWD_FLAGS_ID)
        SB_LST_REF_END
    SUB_MSG_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_WRITE_CALL_FWD_FLAGS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing the Call Forwarding flags to (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_CALL_FWD_FLAGS, SIM_CALL_FWD_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_REL4_MSG_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_CALL_FWD_FLAGS, SIM_CALL_FWD_REQ, SIM_ST_WRITE_CALL_FWD_FLAGS, SIM_CALL_FWD_RESP)

    /* SIM_CALL_FWD_REQ - SIM_ST_READ_CALL_FWD_FLAGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_READ_CALL_FWD_FLAGS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Call Forwarding flags on (U)SIM")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "CPHS: The information is read from EF_6F13 on SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_BULLET, "Release 4: The information is read from EFcfis on (U)SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If both EF_6F11 and EFmwis is available on SIM card then EFmwis has priority.")
    SUB_MSG_BEGIN(SIM_ST_READ_CALL_FWD_FLAGS, SIM_CALL_FWD_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Padding, 8, 1)
    SUB_MSG_END

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_DYNAMIC_FLAGS_REQ.WRITE_DYN_FLAGS - Valid from version 001.000 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Request     Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_DYNAMIC_FLAGS_STR DynFlags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_DynFlagsWrite_Req;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_READ_CALL_FWD_FLAGS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Call Forwarding from (U)SIM.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If both EF_6F11 and EFcfis is available on SIM card then EFcfis has priority.")
    SUB_MSG_BEGIN(SIM_ST_READ_CALL_FWD_FLAGS, SIM_CALL_FWD_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_REL4_MSG_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, NbrOfSubblocks, "NbrOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "NumOfSubblocks:")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "0: none")
        COMMENT(COMMENT_NEWLINE, "")
 	COMMENT(COMMENT_TEXT, "1: SIM_SB_REL4_CALL_FWD_FLAGS_ID ||"
	                      "   SIM_SB_CPHS_CALL_FWD_FLAGS_ID.")	
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_CPHS_CALL_FWD_FLAGS_ID)
            SB_LST_ENTRY(SIM_SB_REL4_CALL_FWD_FLAGS_ID)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_CALL_FWD_FLAGS, SIM_CALL_FWD_REQ, SIM_ST_READ_CALL_FWD_FLAGS, SIM_CALL_FWD_RESP)

    /* SIM_DYNAMIC_FLAGS_REQ - WRITE_DYN_FLAGS */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DynFlagsWrite_Req")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write dynamic flags into the Orange-directory on SIM.")
    SUB_MSG_BEGIN(WRITE_DYN_FLAGS, SIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ, "001.000", "")
        SUB_MSG_REQUEST_HDR
        SEQ_OF(DynFlags, "DynFlags", SIM_INFO_DYNAMIC_FLAGS_STR, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_NO_STATUS_FROM_SUBSYSTEM, SIM_STATUS_TABLE, "", "")
/*      DER_CONST_TBL_ENTRY(NO_STATUS_FROM_SUBSYSTEM)*/
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DynFlagsWrite_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing dynamic flags into the Orange-directory on SIM.")
    SUB_MSG_BEGIN(WRITE_DYN_FLAGS, SIM_DYNAMIC_FLAGS_RESP, MESSAGE_RESP, "001.000", "")
        SUB_MSG_INFO_HDR(SIM_NO_STATUS_FROM_SUBSYSTEM)
    SUB_MSG_END

    SUB_MSG_PAIR(WRITE_DYN_FLAGS, SIM_DYNAMIC_FLAGS_REQ, WRITE_DYN_FLAGS, SIM_DYNAMIC_FLAGS_RESP)

    /* SIM_DYNAMIC_FLAGS_REQ - READ_DYN_FLAGS */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_DYNAMIC_FLAGS_RESP.READ_DYN_FLAGS - Valid from version 001.000 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_DYNAMIC_FLAGS_STR DynFlags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_DynFlagsRead_Resp;")
#endif

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_DYNAMIC_FLAGS_REQ.WRITE_DYN2_FLAGS - Valid from version 001.000 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Request     Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_DYNAMIC2_FLAGS_STR Dyn2Flags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Dyn2FlagsWrite_Req;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DynFlagsRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read dynamic flags from the Orange-directory on SIM.")
    SUB_MSG_BEGIN(READ_DYN_FLAGS, SIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ, "001.000", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_DynFlagsRead_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the dynamic flags from the Orange-directory on SIM.")
    SUB_MSG_BEGIN(READ_DYN_FLAGS, SIM_DYNAMIC_FLAGS_RESP, MESSAGE_RESP, "001.000", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
        SEQ_OF(DynFlags, "DynaFlags", SIM_INFO_DYNAMIC_FLAGS_STR, 1)
    SUB_MSG_END
    
    SUB_MSG_PAIR(READ_DYN_FLAGS, SIM_DYNAMIC_FLAGS_REQ, READ_DYN_FLAGS, SIM_DYNAMIC_FLAGS_RESP)

    /* SIM_DYNAMIC_FLAGS_REQ - WRITE_DYN2_FLAGS */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Dyn2FlagsWrite_Req")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to update the the Orange specific EF_6F92 on SIM.")
    SUB_MSG_BEGIN(WRITE_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ, "001.000", "")
        SUB_MSG_REQUEST_HDR
        SEQ_OF(Dyn2Flags, "Dyn2Flags", SIM_INFO_DYNAMIC2_FLAGS_STR, 1)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Dyn2FlagsWrite_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message result of updating content of the Orange specific EF_6F92 on SIM.")
    SUB_MSG_BEGIN(WRITE_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_RESP, MESSAGE_RESP, "001.000", "")
        SUB_MSG_INFO_HDR(SIM_NO_STATUS_FROM_SUBSYSTEM)
    SUB_MSG_END

    SUB_MSG_PAIR(WRITE_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_REQ, WRITE_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_RESP)

    /* SIM_DYNAMIC_FLAGS_REQ - READ_DYN2_FLAGS */
    
#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_DYNAMIC_FLAGS_RESP.READ_DYN2_FLAGS - Valid from version 001.000 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_DYNAMIC2_FLAGS_STR Dyn2Flags;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Dyn2FlagsRead_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Dyn2FlagsRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the content of the Orange specific EF_6F92 on SIM.")
    SUB_MSG_BEGIN(READ_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_REQ, MESSAGE_REQ, "001.000", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Dyn2FlagsRead_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the content of the Orange specific EF_6F92 on SIM.")
    SUB_MSG_BEGIN(READ_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_RESP, MESSAGE_RESP, "001.000", "")
        SUB_MSG_INFO_HDR(SIM_VOICE_MSG_STATUS)
        SEQ_OF(Dyn2Flags, "Dyn2Flags", SIM_INFO_DYNAMIC2_FLAGS_STR, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_REQ, READ_DYN2_FLAGS, SIM_DYNAMIC_FLAGS_RESP)

    /* SIM_APP_SELECTION */

    DER_CONST_TBL_BEGIN(SIM_PREFERRED_PROTOCOL_IND_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_APP_SELECTION_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_ALL_APP_LABELS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request all Telecom Application on an (U)SIM card.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_ACTIVE_APP_LABEL,")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_ISIM_LABEL,")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_LABEL_BY_NO")
    SUB_MSG_BEGIN(SIM_ST_GET_ALL_APP_LABELS, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "ApplicationNumber is not valid for service type.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns all Telecom Application on an (U)SIM card.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_ACTIVE_APP_LABEL,")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_ISIM_LABEL,")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_GET_LABEL_BY_NO")
    SUB_MSG_BEGIN(SIM_ST_GET_ALL_APP_LABELS, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)      
	REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)        
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub bloks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION_UNICODE)
        SB_LST_REF_END
    SUB_MSG_END
 
    SUB_MSG_PAIR(SIM_ST_GET_ALL_APP_LABELS, SIM_APP_SELECTION_REQ, SIM_ST_GET_ALL_APP_LABELS, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_ACTIVE_APP_LABEL */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_GET_ACTIVE_APP_LABEL, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
	COMMENT(COMMENT_TEXT, "ApplicationNumber is not valid for service type.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_ACTIVE_APP_LABEL, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)        
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub bloks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_GET_ACTIVE_APP_LABEL, SIM_APP_SELECTION_REQ, SIM_ST_GET_ACTIVE_APP_LABEL, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_ISIM_LABEL */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_ISIM_LABEL, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
	COMMENT(COMMENT_TEXT, "ApplicationNumber is not valid for service type.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_ISIM_LABEL, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)        
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub bloks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION_UNICODE)
        SB_LST_REF_END
    SUB_MSG_END
  
    SUB_MSG_PAIR(SIM_ST_GET_ISIM_LABEL, SIM_APP_SELECTION_REQ, SIM_ST_GET_ISIM_LABEL, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_LABEL_BY_NO */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppSelection_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_LABEL_BY_NO, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
	COMMENT(COMMENT_TEXT, "Number of the Application")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppSelection_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_LABEL_BY_NO, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)        
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub bloks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION)
            SB_LST_ENTRY(SIM_SB_APP_SELECTION_UNICODE)
        SB_LST_REF_END
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_GET_LABEL_BY_NO, SIM_APP_SELECTION_REQ, SIM_ST_GET_LABEL_BY_NO, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_NUMBER_OF_APP */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppNumber_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client request the number of Telecom applications from EFdir file on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_GET_NUMBER_OF_APP, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppNumber_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the number of Telecom applications from EFdir file on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_GET_NUMBER_OF_APP, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 1)
	COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Number of Telecom applications on (U)SIM.")
        VALUE(8, BE, NumberOfAppl, "NumberOfAppl", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_GET_NUMBER_OF_APP, SIM_APP_SELECTION_REQ, SIM_ST_GET_NUMBER_OF_APP, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_SET_DEFAULT_APP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SetDefaultApp_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to specify a default Telecom Application.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The next time the ME starts up, the default Telecom Application is activated.")    
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The specific Telecom Application is selected from the list of applications in SIM_APP_SELECTION_REQ(SIM_ST_GET_ALL_APP_LABELS).")    
    SUB_MSG_BEGIN(SIM_ST_SET_DEFAULT_APP, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Application number of the specified default Telecom Application.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SetDefaultApp_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of specifying a default Telecom Application.")
    SUB_MSG_BEGIN(SIM_ST_SET_DEFAULT_APP, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET_DEFAULT_APP, SIM_APP_SELECTION_REQ, SIM_ST_SET_DEFAULT_APP, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_ACTIVATE_APP */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ActivateApp_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to activate a specific Telecom Application.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The specific Telecom Application is selected from the list of applications in SIM_APP_SELECTION_REQ(SIM_ST_GET_ALL_APP_LABELS).")    
     SUB_MSG_BEGIN(SIM_ST_ACTIVATE_APP, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Application number of the specified Telecom Application to activate.")
        VALUE(8, BE, ApplicationNumber, "Application Number", DEC)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ActivateApp_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of activating a specific Telecom Application.")
    SUB_MSG_BEGIN(SIM_ST_ACTIVATE_APP, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_APP_SELECTION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACTIVATE_APP, SIM_APP_SELECTION_REQ, SIM_ST_ACTIVATE_APP, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_SET_APP_SELECTION_AUTOMATIC */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppSelectionMode_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request ??????")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_SET_APP_SELECTION_MANUAL.")
    SUB_MSG_BEGIN(SIM_ST_SET_APP_SELECTION_AUTOMATIC, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppSelectionMode_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of ??????????")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "This is also for the following service types:")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "SIM_ST_SET_APP_SELECTION_MANUAL.")
    SUB_MSG_BEGIN(SIM_ST_SET_APP_SELECTION_AUTOMATIC, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PREFERRED_PROTOCOL_IND_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET_APP_SELECTION_AUTOMATIC, SIM_APP_SELECTION_REQ, SIM_ST_SET_APP_SELECTION_AUTOMATIC, SIM_APP_SELECTION_RESP)
    
    /* SIM_APP_SELECTION_REQ -  SIM_ST_SET_APP_SELECTION_MANUAL */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request ")
    SUB_MSG_BEGIN(SIM_ST_SET_APP_SELECTION_MANUAL, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad1, 8, 1)
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of ")
    SUB_MSG_BEGIN(SIM_ST_SET_APP_SELECTION_MANUAL, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_PREFERRED_PROTOCOL_IND_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET_APP_SELECTION_MANUAL, SIM_APP_SELECTION_REQ, SIM_ST_SET_APP_SELECTION_MANUAL, SIM_APP_SELECTION_RESP)

    /* SIM_APP_SELECTION_REQ -  SIM_ST_GET_APP_SELECTION_STATUS */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppStatusReq") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_APP_SELECTION_STATUS, SIM_APP_SELECTION_REQ, MESSAGE_REQ, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Pad, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_GET_APP_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_APP_DATA_READ_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AppStatusResp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "") 
    SUB_MSG_BEGIN(SIM_ST_GET_APP_SELECTION_STATUS, SIM_APP_SELECTION_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_GET_APP_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_GET_APP_SELECTION_STATUS, SIM_APP_SELECTION_REQ, SIM_ST_GET_APP_SELECTION_STATUS, SIM_APP_SELECTION_RESP)

    /* SIM_FDN_CHECK */

    DER_CONST_TBL_BEGIN(SIM_FDN_CHECK_SERVICE_TYPE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(NO_SERVICE_TYPE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_FDN_CHECK_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_PASSED)
        DER_CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_FAILED)
        DER_CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_DISABLED)
        DER_CONST_TBL_ENTRY(SIM_SERV_FDN_STATUS_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_FDN_CHECK_NO_FDN_SIM)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_FDN_CHECK_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message is used request FDN check.")
    MSG_BEGIN(SIM_FDN_CHECK_REQ, MESSAGE_REQ, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "ServiceType", SIM_FDN_CHECK_SERVICE_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "SubBlockStart", N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
            SB_LST_ENTRY(SIM_SB_PHONE_NUMBER_FIELD_ID)
            SB_LST_ENTRY(SIM_SB_SMS_DEST_ADR_ID)
            SB_LST_ENTRY(SIM_SB_SMSC_ADR_ID)    
        SB_LST_REF_END
    MSG_END
 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_FDN_CHECK_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns the result of FDN check.")
    MSG_BEGIN(SIM_FDN_CHECK_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "ServiceType", SIM_FDN_CHECK_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_FDN_CHECK_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 3)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", NumberOfSubblocks)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "SubBlockStart", NumberOfSubblocks, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
            SB_LST_ENTRY(SIM_SB_PHONE_NUMBER_FIELD_ID)
            SB_LST_ENTRY(SIM_SB_SMS_DEST_ADR_ID)
            SB_LST_ENTRY(SIM_SB_SMSC_ADR_ID) 
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SIM_FDN_CHECK_REQ, SIM_FDN_CHECK_RESP)

    /* SIM_CONNECTION_REQ */

    DER_CONST_TBL_BEGIN(SIM_CONNECT_SERVICE_TYPE, SIM_CONNECTION_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_SIM_DISCONNECT)
        DER_CONST_TBL_ENTRY(SIM_ST_SIM_CONNECT)
        DER_CONST_TBL_ENTRY(SIM_ST_SIM_RECONNECT)
        DER_CONST_TBL_ENTRY(SIM_ST_SIM_CONNECT_FORCED_PIN)        
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_CONNECTION_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
        DER_CONST_TBL_ENTRY(SIM_STA_OK) 
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
    DER_CONST_TBL_END

    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, "For the following service types:")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_CONNECT,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_DISCONNECT,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_RECONNECT,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_CONNECT_FORCED_PIN") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Connection_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to control the connection state of the SIM server.")
    MSG_BEGIN(SIM_CONNECTION_REQ, MESSAGE_REQ, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_CONNECT_SERVICE_TYPE)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, 1)
        PROPERTY_VALUE(PROPERTY_ITEM_MINIMUM_VALUE, 0)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, SubBlockStart, "SubBlockStart", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_CONNECTION_ID)
        SB_LST_REF_END
    MSG_END
  

    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_DISABLE)
    COMMENT(COMMENT_PARAGRAPH, "For the following service types:")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_CONNECT,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_DISCONNECT,")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_RECONNECT")
    COMMENT(COMMENT_PARAGRAPH, "SIM_ST_SIM_CONNECT_FORCED_PIN") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Connection_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    MSG_BEGIN(SIM_CONNECTION_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_CONNECT_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_CONNECTION_STATUS)
    MSG_END

    MSG_PAIR(SIM_CONNECTION_REQ, SIM_CONNECTION_RESP)

    /* SIM_PB_REQ - SIM_PB_READ */
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PB_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message is used to read information from the phonebook on (U)SIM.");    
    SUB_MSG_BEGIN(SIM_PB_READ, SIM_PB_REQ, MESSAGE_REQ, "", "")    
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_INFO_REQUEST)
            SB_LST_ENTRY(SIM_PB_LOCATION)
            SB_LST_ENTRY(SIM_PB_LOCATION_SEARCH)
        SB_LST_REF_END
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PB_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_PB_READ, SIM_PB_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_ADN)
            SB_LST_ENTRY(SIM_PB_ANR)
            SB_LST_ENTRY(SIM_PB_BDN)
            SB_LST_ENTRY(SIM_PB_CC)
            SB_LST_ENTRY(SIM_PB_CCP)
	  /*SB_LST_ENTRY(SIM_PB_CCP1)
            SB_LST_ENTRY(SIM_PB_CCP2)
	  */
            SB_LST_ENTRY(SIM_PB_EMAIL)
            SB_LST_ENTRY(SIM_PB_FDN)
            SB_LST_ENTRY(SIM_PB_FDN_LIST_STATUS)
            SB_LST_ENTRY(SIM_PB_GAS)
            SB_LST_ENTRY(SIM_PB_GRP)
            SB_LST_ENTRY(SIM_PB_HIDDEN)
            SB_LST_ENTRY(SIM_PB_MSISDN)
            SB_LST_ENTRY(SIM_PB_LOCATION)
/*            SB_LST_ENTRY(SIM_PB_PSC)*/
            SB_LST_ENTRY(SIM_PB_SDN)
            SB_LST_ENTRY(SIM_PB_SNE)
            SB_LST_ENTRY(SIM_PB_STATUS)
            SB_LST_ENTRY(SIM_PB_UID)
            SB_LST_ENTRY(SIM_PB_VMBX)
            SB_LST_ENTRY(SIM_PB_MBDN)
            SB_LST_ENTRY(SIM_PB_AAS)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_PB_READ, SIM_PB_REQ, SIM_PB_READ, SIM_PB_RESP) 

    /* SIM_PB_REQ - SIM_PB_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message is used to write information into the phonebook on (U)SIM.");    
    SUB_MSG_BEGIN(SIM_PB_WRITE, SIM_PB_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_ADN)
            SB_LST_ENTRY(SIM_PB_ANR)
            SB_LST_ENTRY(SIM_PB_BDN)
            SB_LST_ENTRY(SIM_PB_CCP)
	  /*SB_LST_ENTRY(SIM_PB_CCP1)
            SB_LST_ENTRY(SIM_PB_CCP2)
	  */
            SB_LST_ENTRY(SIM_PB_EMAIL)
            SB_LST_ENTRY(SIM_PB_FDN)
            SB_LST_ENTRY(SIM_PB_GAS)
            SB_LST_ENTRY(SIM_PB_GRP)
            SB_LST_ENTRY(SIM_PB_HIDDEN)
            SB_LST_ENTRY(SIM_PB_LOCATION)
            SB_LST_ENTRY(SIM_PB_MSISDN)
            SB_LST_ENTRY(SIM_PB_SNE)
            SB_LST_ENTRY(SIM_PB_VMBX)
            SB_LST_ENTRY(SIM_PB_MBDN)
            SB_LST_ENTRY(SIM_PB_AAS)
            SB_LST_ENTRY(SIM_PB_DELETE_ALL)
            SB_LST_ENTRY(SIM_PB_DELETE_LOCATION)
            SB_LST_ENTRY(SIM_PB_FDN_LIST_STATUS)
        SB_LST_REF_END
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_PB_WRITE, SIM_PB_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_LOCATION)
/*            SB_LST_ENTRY(SIM_PB_PSC)*/
            SB_LST_ENTRY(SIM_PB_CC)
            SB_LST_ENTRY(SIM_PB_STATUS)
        SB_LST_REF_END
    SUB_MSG_END
  
    SUB_MSG_PAIR(SIM_PB_WRITE, SIM_PB_REQ, SIM_PB_WRITE, SIM_PB_RESP) 

    /* SIM_PB_REQ - SIM_PB_GET_CONF */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message is used read the configuration of the phonebook on (U)SIM.");    
    SUB_MSG_BEGIN(SIM_PB_GET_CONF, SIM_PB_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_STARTUP_PHASE_1)
            SB_LST_ENTRY(SIM_PB_STARTUP_PHASE_2)
            SB_LST_ENTRY(SIM_PB_STARTUP_PHASE_3)
        SB_LST_REF_END
    SUB_MSG_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_PB_GET_CONF, SIM_PB_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Possible SB combinations:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "Phase 1:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_CONF_1")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_STATUS")
	COMMENT(COMMENT_PARAGRAPH, "    ")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "Phase 2:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_CONF_1")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_CONF_ADN_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_CONF_ADN_LONG_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_SNE_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_SNE_LONG_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_ANR_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_ANR_LONG_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_GRP_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_GRP_LONG_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_AAS_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_EMAIL_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_EMAIL_LONG_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_MISC_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_FDN_SB")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_STATUS")
	COMMENT(COMMENT_PARAGRAPH, "    ")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_BULLET, "Phase 3:")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT,  "SIM_PB_CONF_3")
	COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_PB_STATUS")
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
        /* Phase 1 sub blocks */
            SB_LST_ENTRY(SIM_PB_CONF_PH_1)
            SB_LST_ENTRY(SIM_PB_STATUS)
        /* Phase 2 sub blocks */
            SB_LST_ENTRY(SIM_PB_CONF_ADN_SB)
            SB_LST_ENTRY_VER(SIM_PB_CONF_ADN_LONG_SB, "014.008", "") 
            SB_LST_ENTRY(SIM_PB_CONF_SNE_SB)
            SB_LST_ENTRY_VER(SIM_PB_CONF_SNE_LONG_SB, "014.017", "") 
            SB_LST_ENTRY(SIM_PB_CONF_ANR_SB)
            SB_LST_ENTRY_VER(SIM_PB_CONF_ANR_LONG_SB, "014.017", "") 
            SB_LST_ENTRY(SIM_PB_CONF_GRP_SB)
            SB_LST_ENTRY_VER(SIM_PB_CONF_GRP_LONG_SB, "014.017", "") 
            SB_LST_ENTRY(SIM_PB_CONF_AAS_SB)
            SB_LST_ENTRY(SIM_PB_CONF_GAS_SB)
            SB_LST_ENTRY(SIM_PB_CONF_EMAIL_SB)
            SB_LST_ENTRY_VER(SIM_PB_CONF_EMAIL_LONG_SB, "014.017", "") 
            SB_LST_ENTRY(SIM_PB_CONF_MISC_SB)
            SB_LST_ENTRY(SIM_PB_CONF_FDN_SB)
        /* Phase 3 sub blocks */
            SB_LST_ENTRY(SIM_PB_CONF_PH_3)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_PB_GET_CONF, SIM_PB_REQ, SIM_PB_GET_CONF, SIM_PB_RESP) 

    /* SIM_PB_REQ - SIM_PB_SELECT_PB */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used to select the private/public phonebook on the (U)SIM card.")
    SUB_MSG_BEGIN(SIM_PB_SELECT_PB, SIM_PB_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_SELECT_PB_SB)
        SB_LST_REF_END
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_PB_SELECT_PB, SIM_PB_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransactionID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfSubBlocks, "Number of Sub Blocks", N)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_STATUS)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_PB_SELECT_PB, SIM_PB_REQ, SIM_PB_SELECT_PB, SIM_PB_RESP) 

    /* SIM_READ_EMERG_CODES */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_READ_EMERG_CODES_RESP.NO_SERVICE_TYPE                      */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse           Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_EMRG_CALL_CODES_STR     EmergCodes;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_ReadEmergCodes_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadEmergCodes_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to read the Emergency Call Codes in EFecc on (U)SIM.")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_READ_EMERG_CODES_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_READ_EMERG_CODES_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadEmergCodes_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns a list of Emergency Call Codes from EFecc on (U)SIM.")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_READ_EMERG_CODES_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_READ_EMERG_CODES_STATUS) 
        SEQ_OF(EmergCodes, "EmergCodes", SIM_EMRG_CALL_CODES_STR, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(NO_SERVICE_TYPE, SIM_READ_EMERG_CODES_REQ, NO_SERVICE_TYPE, SIM_READ_EMERG_CODES_RESP) 

    /* SIM_GSM_DIR_REQ - UPDATE_CB_MSGIDS */

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request                Req;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    SIM_INFO_CB_MSG_IDS_STR     CB_MsgIDs;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    } tSIM_Update_CB_MsgIDs_Req; /* Deprecated */")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_UPDATE_CB_MSG_IDS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(UPDATE_CB_MSGIDS, SIM_GSM_DIR_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        REFERENCE(8, BE, Length, "Length", N)
        COMMENT(COMMENT_TEXT, "First record")
        SEQ_OF_REF(cell_bc_msg_ids, "cell_bc_msg_ids", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_ANYSIZE_WORD)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Update_CB_MsgIDs_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(UPDATE_CB_MSGIDS, SIM_GSM_DIR_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_SB_APP_SELECTION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(UPDATE_CB_MSGIDS, SIM_GSM_DIR_REQ, UPDATE_CB_MSGIDS, SIM_GSM_DIR_RESP)

    /* SIM_GSM_DIR_REQ - READ_CB_MSG_IDS */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_GSM_DIR_RESP.READ_CB_MSG_IDS                               */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    word    CB_MsgIDS[SIM_NBR_OF_CELL_BC_MSG_IDS];")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Read_CB_MsgIDS_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_CB_MsgIDS_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_CB_MSG_IDS, SIM_GSM_DIR_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_CB_MsgIDS_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_CB_MSG_IDS, SIM_GSM_DIR_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_SB_APP_SELECTION_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "word")
        SEQ_OF(CB_MsgIDS, "CB Msg IDs", AUTOGEN_SEQ_WORD_HEX, SIM_NBR_OF_CELL_BC_MSG_IDS)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_CB_MSG_IDS, SIM_GSM_DIR_REQ, READ_CB_MSG_IDS, SIM_GSM_DIR_RESP)

    /* SIM_NETWORK_INFO - READ_HPLMN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_NetworkRead_HPLMN_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to request HPLMN informationm from EFimsi on (U)SIM.")
    SUB_MSG_BEGIN(READ_HPLMN, SIM_NETWORK_INFO_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_NETWORK_INFO_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
        
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_NetworkRead_HPLMN_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns the HPLMN information from EFimsi on (U)SIM.")
    SUB_MSG_BEGIN(READ_HPLMN, SIM_NETWORK_INFO_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_NETWORK_INFO_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT,"HPLMN information from EFimsi on (U)SIM.")
        SEQ_OF(hplmn, "hplmn", tSIM_PLMNT_STRUCT, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_HPLMN, SIM_NETWORK_INFO_REQ, READ_HPLMN, SIM_NETWORK_INFO_RESP)

    /* SIM_NETWORK_INFO - WRITE_FIRST_PLMN */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_NetworkWrite_FirstPLMN_Req")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to write the selected PLMN as the first network code into EFplnmsel file on SIM.")
    COMMENT(COMMENT_TEXT,"The previously stored network codes are shifted one place if needed. If the list is full, the")
    COMMENT(COMMENT_TEXT," last network code will be dropped out. NOTE! All cards do not have PLMN selector. ")
    COMMENT(COMMENT_TEXT,"However, this function can be called, but then nothing will be done.")
    SUB_MSG_BEGIN(WRITE_FIRST_PLMN, SIM_NETWORK_INFO_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQUEST_HDR
        SEQ_OF(plmn, "plmn", SIM_INFO_PLMN_STR, 1)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_NetworkWrite_FirstPLMN_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns the result of writing the selected PLMN as the first network code into EFplnmsel file on SIM.")
    SUB_MSG_BEGIN(WRITE_FIRST_PLMN, SIM_NETWORK_INFO_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_INFO_HDR(SIM_NETWORK_INFO_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(WRITE_FIRST_PLMN, SIM_NETWORK_INFO_REQ, WRITE_FIRST_PLMN, SIM_NETWORK_INFO_RESP)

    /* SIM_CPHS_REQ - READ_DATA */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCphsReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to read the Common PCN HandSet(CPHS) information in EF_6F16 on SIM. "
                         "CPHS is Orange specific information.")
    SUB_MSG_BEGIN(READ_DATA, SIM_CPHS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef struct ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "{")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "   tSIM_InfoResponse            Resp;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "   tCPHS_Optionals              OptionalData;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "   SIM_SERV_CPHS_STR            CPHS_Data;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, " ")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#if defined(SIM_AVOID_GCC_PADDING) && (PRODUCT_OS_TYPE == G_OS_ENOS)")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "} __attribute__((packed)) tSIM_ReadCphsResp;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "} tSIM_ReadCphsResp;")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "#endif")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_READ_CPHS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns the Common PCN HandSet(CPHS) information from EF_6F16.")
    SUB_MSG_BEGIN(READ_DATA, SIM_CPHS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        VALUE(8, BE, MailboxNumbInfo, "MailboxNumbInfo", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(padding1, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(padding2, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(padding3, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
  	COMMENT(COMMENT_TEXT, "CPHS phase.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x01: Phase 1.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0x02: Phase 2.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "etc.")
	VALUE(8, BE, phase, "phase", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
	VALUE(8, BE, csp_allocated, "csp_allocated", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Customer Service Profile(CSP) data-field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "CSP is a list of user accesible services.")
        VALUE(8, BE, csp_active, "csp_active", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is allocated.")
        VALUE(8, BE, service_string_tbl_allocated, "service_string_tbl_allocated", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Service String Table(SST) data-field is active.")
        VALUE(8, BE, service_string_tbl_active, "service_string_tbl_active", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is allocated.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the Voice Mailbox.")
        VALUE(8, BE, mailbox_numbers_allocated, "mailbox_numbers_allocated", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Mailbox numbers data-field is active.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Mailbox Number is the dialling number to the Voice Mailbox.")
        VALUE(8, BE, mailbox_numbers_active, "mailbox_numbers_active", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Information Number data-field is allocated.")
        VALUE(8, BE, inf_nbr_allocated, "inf_nbr_allocated", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Information Number data-field is active.")
        VALUE(8, BE, inf_nbr_active, "inf_nbr_active", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(pad1, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(pad2, 8, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_DATA, SIM_CPHS_REQ, READ_DATA, SIM_CPHS_RESP)

    /* SIM_READ_TABLE_REQ */
    
    DER_CONST_TBL_BEGIN(SIM_READ_TABLE_SERVICE_TYPE, SIM_ST_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_PIN1_DISABLE_FUNCTION)
        DER_CONST_TBL_ENTRY(SIM_ST_ADN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_FDN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SMS_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_AOC_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_CCP_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_PLMN_SELECTOR_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_MSISDN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT1_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT2_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT3_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT4_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT5_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SMSP_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_LDN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_CBMI_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GID_L1_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GID_L2_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SPN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SDN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_VGCS_GID_LIST_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_VBS_GID_LIST_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EMLPP_SERVICE_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_AA_EMLPP_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SMSCB_DATA_DOWNLOAD_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SMSPP_DATA_DOWNLOAD_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_MENU_SELECTION_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_CALL_CONTROL_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_PROACTIVE_SIM)
        DER_CONST_TBL_ENTRY(SIM_ST_CBMIR_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_BDN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_DEPERSONALIZATION_KC_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_CO_OP_NET_LIST_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SMSR_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_NET_IND_ALERT_IN_MS_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_MO_SMS_SIM_CONTROL_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GPRS_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_IMAGE_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_SOLSA_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_USSD_IN_CALL_CONTROL_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_RUN_AT_COMMAND_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_UPLMN_WITH_AT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_OPLMN_WITH_AT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_HPLMN_WITH_AT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_CPBCCH_INFO_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_INVESTIGATION_SCAN_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_EXT_CC_PARAMS_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_MEXE_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_RPLMN_LAST_USED_AT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_LOCAL_PHONE_BOOK_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_ICI_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GSM_ACCESS_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_ENABLED_SERVICE_TABLE_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_ACL_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GSM_SECURITY_CONTEXT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_ST_GPRS_CALL_CONTROL_AVAIL)
    DER_CONST_TBL_END
  
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ServiceTableReadReq") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the status of a specific service(s) in the (U)SIM Service Table.")
    MSG_BEGIN(SIM_READ_TABLE_REQ, MESSAGE_REQ, "", "") 
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request      Req;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "ServiceType", SIM_READ_TABLE_SERVICE_TYPE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER_EX(Padding1, 8, 1)
    MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ServiceTable_Resp") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the status of a specific service in the (U)SIM Service Table.")
    MSG_BEGIN(SIM_READ_TABLE_RESP, MESSAGE_RESP, "","")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response   Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "ServiceType", SIM_READ_TABLE_SERVICE_TYPE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
    MSG_END

    MSG_PAIR(SIM_READ_TABLE_REQ, SIM_READ_TABLE_RESP)

    /* SIM_OPERATOR_REQ -  SIM_ST_READ_PNN*/

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_OPERATOR_READ_PNN_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the PLNM Network Name from EFpnn on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_PNN, SIM_OPERATOR_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Identifier of the record to read in EFpnn file.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Range:0x01-0xFE")
        VALUE(8, BE, PNNIdentifier, "PNNIdentifier", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_OPERATOR_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_OPERATOR_READ_PNN_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the PLNM Network Name from EFpnn on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_PNN, SIM_OPERATOR_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_OPERATOR_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "Identifier of the read record in EFpnn file.")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_TEXT, "Range:0x01-0xFE")
	VALUE(8, BE, PNNIdentifier, "PNNIdentifier", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        REFERENCE(8, BE, NumOfSubblocks, "NumOfSubblocks", N)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding1, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
	COMMENT(COMMENT_TEXT, "NumOfSubblocks:")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "0: none")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "1: SIM_SB_FULL_NETWORK_NAME ")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "2: SIM_SB_FULL_NETWORK_NAME &"
	                      "   SIM_SB_SHORT_NETWORK_NAME.")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_FULL_NETWORK_NAME)
            SB_LST_ENTRY(SIM_SB_SHORT_NETWORK_NAME)
        SB_LST_REF_END
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_PNN, SIM_OPERATOR_REQ, SIM_ST_READ_PNN, SIM_OPERATOR_RESP)

    /* SIM_OPERATOR_REQ -  SIM_ST_READ_OPL*/

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_OPERATOR_READ_OPL_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Operator PLNM List from EFopl on (U)SIM.")
    SUB_MSG_BEGIN(SIM_ST_READ_OPL, SIM_OPERATOR_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_OPERATOR_READ_OPL_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Operator PLNM List from EFopl.")
    SUB_MSG_BEGIN(SIM_ST_READ_OPL, SIM_OPERATOR_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_OPERATOR_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Number of records of Operator PLNM List read from EFopl.")
        VALUE(8, BE, NumberOfRecords, "Number Of Records", DEC)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding1, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding2, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "List of records of Operator PLNM List read from EFopl.")
        SEQ_OF_REF(OperatorPLMNList, "OperatorPLMNList", SIM_OPL, REF_AS_MANY_AS_POSSIBLE,  1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_OPL, SIM_OPERATOR_REQ, SIM_ST_READ_OPL, SIM_OPERATOR_RESP)

    /* SIM_ICC_TYPE_REQ */

    DER_CONST_TBL_BEGIN(SIM_ICC_TYPE_ST, SIM_ICC_TYPE_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_READ_SB)
        DER_CONST_TBL_ENTRY_VER(SIM_ST_READ_ALL_SB, "", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_ST_READ_ACTIVE_AID_SB, "", "020.000")
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ICC_TYPE_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to request the type of ICC in ME, e.g. SIM, USIM, ISIM etc.")
    MSG_BEGIN(SIM_ICC_TYPE_REQ, MESSAGE_REQ, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_ICC_TYPE_ST)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "RFU")
        VALUE(8, BE, CardReaderID, "CardReaderID", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, NoOfSBID, "No Of subblock ID", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubBlockIDList, "SubBlockIDList", N, ISIHDR_MARKER_ANYSIZE)
            SB_LST_ENTRY(SIM_SB_ICC_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_ICCID_ID)
        SB_LST_END
        FILLER(FILLER_VARIABLE, 32)
    MSG_END

    DER_CONST_TBL_BEGIN(SIM_ICC_TYPE_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_SB_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ICC_TYPE_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the type of ICC in ME")
    MSG_BEGIN(SIM_ICC_TYPE_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_ICC_TYPE_ST)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ICC_TYPE_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "RFU")
        VALUE(8, BE, CardReaderID, "Card Reader Identity", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(8, BE, NumberOfSubblocks, "No Of subblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ICC_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_ICCID_ID)
        SB_LST_END
    MSG_END

    MSG_PAIR(SIM_ICC_TYPE_REQ, SIM_ICC_TYPE_RESP)

    /* SIM_READ_CI_REQ - NO_SERVICE_TYPE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_CI_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read ciphering indicator in the EFad file on USIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The ciphering indicator is included in 'additional data' in EFad.")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_READ_CI_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_READ_CI_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_REQUIRED)
        DER_CONST_TBL_ENTRY(SIM_SERV_CIPHERING_INDICATOR_DISPLAY_NOT_REQUIRED)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_CI_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the value of the ciphering indicator in EFad on USIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The EFad file is only availble on USIM. The ciphering indicator is not always available. see 3GPP TS 31.102")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_READ_CI_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_READ_CI_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(NO_SERVICE_TYPE, SIM_READ_CI_REQ, NO_SERVICE_TYPE, SIM_READ_CI_RESP)

    /* SIM_READ_ACM_ACCESS_REQ */

    /* ACM_SET, ACM_MAX_SET, PUCT_SET */

    DER_CONST_TBL_BEGIN(SIM_READ_ACM_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmAccRead_Req") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")     
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to check if EFacm, EFacmmax or EFpuct is protected by PIN, PIN2 or not protected.")
    MSG_BEGIN(SIM_READ_ACM_ACCESS_REQ, MESSAGE_REQ, "", "020.000")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Req Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "EF file indicator. Indicates if EFacm ,EFacmmax or EFpuct protection rights are requested")
        VALUE_CONST(ServiceType, "Service Type", SIM_ACM_ACCESS_SERVICE_TYPE_TABLE)
    MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_READ_ACM_CONDITION_TABLE, SIM_CONDITION_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(NOT_PROTECTED)
        DER_CONST_TBL_ENTRY(PROTECTED_BY_PIN1)
        DER_CONST_TBL_ENTRY(PROTECTED_BY_PIN2)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmAccRead_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns if EFacm, EFacmmax or EFpuct is protected by PIN, PIN2 or not protected.")
    MSG_BEGIN(SIM_READ_ACM_ACCESS_RESP, MESSAGE_RESP, "", "020.000")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_InfoResponse Resp;")
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(ServiceType, "Service Type", SIM_ACM_ACCESS_SERVICE_TYPE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Status, "Status", SIM_READ_ACM_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT(COMMENT_TEXT, "PIN protection result.")
        VALUE_CONST(Condition, "Condition", SIM_READ_ACM_CONDITION_TABLE)
    MSG_END

    MSG_PAIR(SIM_READ_ACM_ACCESS_REQ, SIM_READ_ACM_ACCESS_RESP)

    /* SIM_ACM_REQ - SIM_ST_INCREMENT */

    DER_CONST_TBL_BEGIN(SIM_SINGLE_LINE, SIM_LINE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_PRIMARY_LINE)
        DER_CONST_TBL_ENTRY(SIM_ALTERNATE_LINE)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef uint8 tLine;")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmInc_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests incrementation of Accumulated Call Meter(ACM) of specified line.")
    SUB_MSG_BEGIN(SIM_ST_INCREMENT, SIM_ACM_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR
        FILLER_EX(Padding, 8, 1)
        SEQ_OF(Value, "Value", SIM_ACM, 1)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tLine Line;")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Line, "Line", SIM_SINGLE_LINE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_INCREMENT_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
/* To be used later when the tables have been re-arranged to avoid two entries with same value    
        DER_CONST_TBL_ENTRY(SIM_SERV_ACM_MAX_VALUE_REACHED)*/
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmInc_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_INCREMENT, SIM_ACM_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_ST_INCREMENT_STATUS)        
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_INCREMENT, SIM_ACM_REQ, SIM_ST_INCREMENT, SIM_ACM_RESP)

    /* SIM_ACM_REQ - SIM_ST_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmSet_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests setting of Accumulated Call Meter(ACM) of specified line.")
    SUB_MSG_BEGIN(SIM_ST_SET, SIM_ACM_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR
        FILLER_EX(Padding, 8, 1)
        SEQ_OF(Value, "Value", SIM_ACM, 1)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tLine Line;")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Line, "Line", SIM_LINE_TYPE_TABLE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ACM_SET_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmSet_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_SET, SIM_ACM_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_ACM_SET_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET, SIM_ACM_REQ, SIM_ST_SET, SIM_ACM_RESP)

    /* SIM_ACM_REQ - SIM_ST_MAX_VALUE_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmMaxSet_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests setting of a new value of accumulated call meter(ACMmax) of specified line.")
    SUB_MSG_BEGIN(SIM_ST_MAX_VALUE_SET, SIM_ACM_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR
        FILLER_EX(Padding, 8, 1)
        SEQ_OF(Value, "Value", SIM_ACM_MAX_VALUE, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ACM_MAX_VALUE_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_UPDATE_IMPOSSIBLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmMaxSet_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_MAX_VALUE_SET, SIM_ACM_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_ACM_MAX_VALUE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_MAX_VALUE_SET, SIM_ACM_REQ, SIM_ST_MAX_VALUE_SET, SIM_ACM_RESP)

    /* SIM_ACM_REQ - SIM_ST_READ_AOC */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the value of accumulated call meter(ACM) from EFacm/EFacm2.")
    SUB_MSG_BEGIN(SIM_ST_READ_AOC, SIM_ACM_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tLine Line;")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Line, "Line", SIM_SINGLE_LINE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_STATUS_READ_AOC_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL) 
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmRead_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_READ_AOC, SIM_ACM_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_INFO_HDR(SIM_ST_STATUS_READ_AOC_STATUS)
        SEQ_OF(Value, "Value", SIM_ACM, 1)
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tLine Line;")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Line, "Line", SIM_SINGLE_LINE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_AOC, SIM_ACM_REQ, SIM_ST_READ_AOC, SIM_ACM_RESP)

    /* SIM_ACM_REQ - SIM_ST_MAX_VALUE_READ */
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmMaxRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the value of accumulated call meter maximum value from EFacmmax")
    SUB_MSG_BEGIN(SIM_ST_MAX_VALUE_READ, SIM_ACM_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_MAX_VALUE_READ_STATUS, SIM_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AcmMaxRead_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_MAX_VALUE_READ, SIM_ACM_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_INFO_HDR(SIM_ST_MAX_VALUE_READ_STATUS)
        SEQ_OF(Value, "Value", SIM_ACM, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_MAX_VALUE_READ, SIM_ACM_REQ, SIM_ST_MAX_VALUE_READ, SIM_ACM_RESP)

    /* SIM_OPERATOR_REQ - READ_NAME */ 

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadOperatorNameReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the operator name in the EF_9F14 file in the DCS1800 directory on SIM.")
    SUB_MSG_BEGIN(READ_NAME, SIM_OPERATOR_REQ, MESSAGE_REQ, "001.000", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadOperatorNameResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the operator name from the EF_9F14 file in the DCS1800 directory on SIM.")
    SUB_MSG_BEGIN(READ_NAME, SIM_OPERATOR_RESP, MESSAGE_RESP, "001.000", "")
        SUB_MSG_INFO_HDR(SIM_SB_APP_SELECTION_STATUS)
        SEQ_OF(OperatorName, "OperatorName", SIM_SERV_OPERATOR_NAME, 1)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_NAME, SIM_OPERATOR_REQ, READ_NAME, SIM_OPERATOR_RESP)

    /* SIM_CSP_REQ - READ_LINE_DATA */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_CSP_RESP.READ_LINE_DATA                                    */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tCSP_Optionals OptionalData;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_SERV_CSP_STR CSP_Data;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if defined(SIM_AVOID_GCC_PADDING) && (PRODUCT_OS_TYPE == G_OS_ENOS)")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tSIM_ReadCspResp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_ReadCspResp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCspReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read the Customer Service Profile(CSP) for a specific line on SIM card.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "CSP is a list of user accessible Services in EF_6F15")
     SUB_MSG_BEGIN(READ_LINE_DATA, SIM_CSP_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "byte")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Line, "Line", SIM_SINGLE_LINE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

#ifdef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#else")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "} __attribute__((packed)) tSIM_ReadCspResp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif")    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadCspResp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the Customer Service Profile(CSP).")
    SUB_MSG_BEGIN(READ_LINE_DATA, SIM_CSP_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_SB_APP_SELECTION_STATUS)
        SEQ_OF(OptionalData, "Optional Data", tCSP_Optionals, 1)
        COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#if ! defined(SIM_AVOID_GCC_PADDING) || (PRODUCT_OS_TYPE != G_OS_ENOS)")
        SEQ_OF(CSP_Data, "CSP Data", SIM_SERV_CSP_STR, 1)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_LINE_DATA, SIM_CSP_REQ, READ_LINE_DATA, SIM_CSP_RESP)

    /* SIM_SAT_REQ */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_SAT_RESP.READ_CBMIDS - Valid from version 001.000          */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Response        Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   EF_CBMID_Count;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   padding1;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   padding2;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   padding3;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_CBMID_STR EF_CBMID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_SAT_READ_CBMIDS_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SAT_READ_CBMIDS_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_CBMIDS, SIM_SAT_REQ, MESSAGE_REQ, "001.000", "020.000")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_SAT_READ_CBMIDS_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_CBMIDS, SIM_SAT_RESP, MESSAGE_RESP, "001.000", "020.000")
        SUB_MSG_RESP_HDR(SIM_READ_FIELD_ICC_STATUS)
        REFERENCE(8, BE, EF_CBMID_Count, "EF CBMID Count", N)
        FILLER_EX(padding1, 8, 1)
        FILLER_EX(padding2, 8, 1)
        FILLER_EX(padding3, 8, 1)
        SEQ_OF_REF(EF_CBMID, "EF CBMID", SIM_INFO_CBMID_STR, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_CBMIDS, SIM_SAT_REQ, READ_CBMIDS, SIM_SAT_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - READ_PARAM */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Param_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows clients to read VIAG homezone parameters.")
    SUB_MSG_BEGIN(READ_PARAM, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        VALUE(8, BE, Paddingbyte, "Paddingbyte", DEC)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Param_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns VIAG homezone parameters.")
    SUB_MSG_BEGIN(READ_PARAM, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "SMSC number in UCS2 format. Zero terminated.")
        SEQ_OF(SMSCNumber, "SMSC Number", AUTOGEN_SEQ_WORD_DEC, 15)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "SCP number in UCS2 format. Zero terminated.")
        SEQ_OF(SCPNumber, "SCP Number", AUTOGEN_SEQ_WORD_DEC, 15)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Subscription and version number.")
        VALUE(8, BE, SubscriptionVersion, "Subscription Version", DEC)
        FILLER_EX(Padding, 8, 1)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        SEQ_OF(Element, "Element", SIM_VIAG_HOME_ZONE_SEQ, 4)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_PARAM, SIM_VIAG_HOME_ZONE_REQ, READ_PARAM, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - READ_CACHE */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Cache_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read a specified EF file containing Home Zone Cell Cache.")
    SUB_MSG_BEGIN(READ_CACHE, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Cache to read.")
        VALUE(8, BE, Cache, "Cache", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "EF file number to read.")
        VALUE(8, BE, RecordNumber, "Record Number", DEC)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Cache_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of reading Home Zone Cell Cache.")
    SUB_MSG_BEGIN(READ_CACHE, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_APP_SELECTION_STATUS)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Lcation Area Code.")
        VALUE(16, BE, Lac, "Lac", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Cell Identifier.")
        VALUE(16, BE, CellId, "Cell ID", DEC)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_CACHE, SIM_VIAG_HOME_ZONE_REQ, READ_CACHE, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - WRITE_CACHE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneWrite_Cache_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write Home Zone Cell Cache data to a specified EF file.")
    SUB_MSG_BEGIN(WRITE_CACHE, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Cache to write Home Zone Cell into.")
        VALUE(8,BE, Cache, "Cache", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Lcation Area Code.")
        VALUE(16, BE, Lac, "LAC", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Cell Identifier.")
        VALUE(16, BE, CellId, "Cell ID", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "EF file number to write Home Zone Cell into.")
        VALUE(8, BE, RecordNumber, "Record Number", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_VIAG_HOME_ZONE_STATUS, SIM_STATUS_TABLE, "001.000", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneWrite_Cache_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing Home Zone Cell Cache data.")
    SUB_MSG_BEGIN(WRITE_CACHE, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_VIAG_HOME_ZONE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(WRITE_CACHE, SIM_VIAG_HOME_ZONE_REQ, WRITE_CACHE, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - SIM_ST_READ_SUBSCRIBED_LAC_CI */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_SubscribedLacCi_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read one of the four EF_Subscribed_LAC/CI files.")
    SUB_MSG_BEGIN(SIM_ST_READ_SUBSCRIBED_LAC_CI, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Number EF_Subscribed_LAC/CI file to read.")
        VALUE(8, BE, SubscribedLacCi, "Subscribed LAC CI", DEC)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SB_READ_O2_HOME_ZONE_STATUS, SIM_HZ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE) 
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_SubscribedLacCi_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the content of one of the four EF_Subscribed_LAC/CI files.")
    SUB_MSG_BEGIN(SIM_ST_READ_SUBSCRIBED_LAC_CI, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_READ_O2_HOME_ZONE_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(16, BE, DataLength, "Length of Data", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Content of one of the four EF_Subscribed_LAC/CI files.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_SUBSCRIBED_LAC_CI, SIM_VIAG_HOME_ZONE_REQ, SIM_ST_READ_SUBSCRIBED_LAC_CI, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - SIM_ST_READ_HZ_TAGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Tags_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read VIAG HomeZone text tag(s) from the EF_Tags file.")
    SUB_MSG_BEGIN(SIM_ST_READ_HZ_TAGS, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Zone number to read text Tag from:")
        COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "1-8: Read VIAG HomeZone text tag for specific zone.")
	COMMENT(COMMENT_NEWLINE, "")
        COMMENT(COMMENT_BULLET, "0xFF: Read VIAG HomeZone text tag for all zones.")
        VALUE(8, BE, ZoneNumber, "Zone Number", DEC)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_Tags_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the VIAG HomeZone tag(s) from the EF_Tags file.")
    SUB_MSG_BEGIN(SIM_ST_READ_HZ_TAGS, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_READ_O2_HOME_ZONE_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(16, BE, DataLength, "Length of Data", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Viag HomeZone tags from the EF_Tags file.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_READ_HZ_TAGS, SIM_VIAG_HOME_ZONE_REQ, SIM_ST_READ_HZ_TAGS, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - SIM_ST_READ_UHZIUE_SETTINGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_UHZIUESettings_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read VIAG HomeZone UHZIUE Settings from the EF_UHZIUE_Settings file.")
    SUB_MSG_BEGIN(SIM_ST_READ_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        FILLER_EX(Padding, 8, 1)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneRead_UHZIUESettings_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the VIAG HomeZone UHZIUE Settings from the EF_UHZIUE_Settings file.")
    SUB_MSG_BEGIN(SIM_ST_READ_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Content of the EF_UHZIUE_Settings file.")
        VALUE_CONST(Status, "Status", SIM_SB_READ_O2_HOME_ZONE_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(16, BE, DataLength, "Length of Data", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Content of the EF_UHZIUE_Settings file.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_REQ, SIM_ST_READ_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_VIAG_HOME_ZONE_REQ - SIM_ST_WRITE_UHZIUE_SETTINGS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneWrite_UHZIUESettings_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to write VIAG HomeZone UHZIUE Settings to the EF_UHZIUE_Settings file.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_REQ, MESSAGE_REQ, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)    
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(16, BE, DataLength, "Length of Data", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Content of the EF_UHZIUE_Settings file.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_MARKER_SINGLE_ELEMENT)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_SB_WRITE_O2_HOME_ZONE_STATUS, SIM_HZ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE) 
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ViagHomeZoneWrite_UHZIUESettings_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing VIAG HomeZone UHZIUE Settings into the EF_UHZIUE_Settings file.")
    SUB_MSG_BEGIN(SIM_ST_WRITE_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_RESP, MESSAGE_RESP, "001.000", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SB_WRITE_O2_HOME_ZONE_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_WRITE_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_REQ, SIM_ST_WRITE_UHZIUE_SETTINGS, SIM_VIAG_HOME_ZONE_RESP)

    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_REGISTER */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_REGISTER_RESP tSIM_Response")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_REQ.SIM_ST_REFRESH_UNREGISTER                      */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_UNREGISTER_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_UNREGISTER_RESP tSIM_Response")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_REQ.SIM_ST_REFRESH_OK and SIM_ST_REFRESH_NOT_OK    */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_PERMISSION_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_PERISSION_RESP tSIM_Response")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_PERMISSION_RESP tSIM_Response")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_REQ.SIM_ST_REFRESH_DONE and SIM_ST_REFRESH_ERROR   */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_RESULT_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_RESULT_RESP tSIM_Response")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_REFRESH_REGISTER_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows clients during start-up to register for refresh.")
    COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message contains a list of files that the client uses together with an indication"
			  " if the client wants to be asked for permission before refresh is done or not.")
    COMMENT(COMMENT_NEWLINE, "")			      
    COMMENT(COMMENT_TEXT, "To keep track of which clients have registered for refresh, the object ID is "
                          "retrieved from the message header and stored in the SIM Server.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Note: It is possible for a client to register a consecutive number of times."
                          "The last registration will replace former registrations.")    
    SUB_MSG_BEGIN(SIM_ST_REFRESH_REGISTER, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Number of records to refresh.")
        REFERENCE(8, BE, NumberOfFiles, "Number of files", N)
        COMMENT(COMMENT_TEXT, "First record")
        SEQ_OF_REF(FileList, "FileList", tSIM_REFRESH_FILE_LIST_STR, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_REFRESH_REGISTER_STATUS, SIM_STATUS_REFRESH_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_REGISTER, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_REGISTER_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_REGISTER, SIM_REFRESH_REQ, SIM_ST_REFRESH_REGISTER, SIM_REFRESH_RESP)
    
    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_UNREGISTER */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows clients to unregister for refresh..")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_UNREGISTER, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_REFRESH_UNREGISTER_STATUS, SIM_STATUS_REFRESH_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of unregister for refresh..")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_UNREGISTER, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_UNREGISTER_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_UNREGISTER, SIM_REFRESH_REQ, SIM_ST_REFRESH_UNREGISTER, SIM_REFRESH_RESP)
    
    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_OK */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to accept execution of refresh.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_OK, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_REFRESH_PERMISSION_STATUS, SIM_STATUS_REFRESH_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_OK, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_PERMISSION_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_OK, SIM_REFRESH_REQ, SIM_ST_REFRESH_OK, SIM_REFRESH_RESP)

    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_NOT_OK */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to reject execution of refresh.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_NOT_OK, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_NOT_OK, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_PERMISSION_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_NOT_OK, SIM_REFRESH_REQ, SIM_ST_REFRESH_NOT_OK, SIM_REFRESH_RESP)
    
    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_DONE */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used by clients to report that refresh is executed successfully.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_DONE, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_REFRESH_RESULT_STATUS, SIM_STATUS_REFRESH_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_DONE, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_RESULT_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_DONE, SIM_REFRESH_REQ, SIM_ST_REFRESH_DONE, SIM_REFRESH_RESP)
    
    /* SIM_REFRESH_REQ - SIM_ST_REFRESH_ERROR */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used by clients to report that refresh has failed.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_ERROR, SIM_REFRESH_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_ERROR, SIM_REFRESH_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_ST_REFRESH_RESULT_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_REFRESH_ERROR, SIM_REFRESH_REQ, SIM_ST_REFRESH_ERROR, SIM_REFRESH_RESP)
    
    /* SIM_REFRESH_NTF - SIM_ST_REFRESH_REQUESTED */

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_NTF.SIM_ST_REFRESH_NOW                             */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_NOW_NTF tSIM_REFRESH_REQUESTED_NTF")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_NTF.SIM_ST_REFRESH_CANCELLED                       */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_CANCELLED_NTF tSIM_Request")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_REFRESH_NTF.SIM_ST_REFRESH_STARTING                        */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_REFRESH_STARTING_NTF tSIM_Request")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_MMS_REQ.SIM_ST_MMS_ICP_READ                                */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_MMS_ICP_READ_REQ tSIM_Request")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_REFRESH_REQUESTED_NTF")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests clients for permission to execute refresh.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message includes a list of the FileIDs to refresh. "
                          "Each Client may accept/reject the request. "
			  "Only clients that has registered to refresh of one or more of the files to refresh, receives this request.")
        SUB_MSG_BEGIN(SIM_ST_REFRESH_REQUESTED, SIM_REFRESH_NTF, MESSAGE_NTF, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfFiles, "Number of files", N)
        COMMENT(COMMENT_TEXT, "First record")
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SEQ_OF_REF(FileList, "File list", SIM_REFERSH_FILE_LIST, N, ISIHDR_MARKER_ANYSIZE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
    
    /* SIM_REFRESH_NTF - SIM_ST_REFRESH_NOW */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests a client to start to re-read data from (U)SIM.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The message includes a list of the FileIDs to refresh.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Only clients that has registered to refresh of one or more of the files to refresh, receives this request.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_NOW, SIM_REFRESH_NTF, MESSAGE_NTF, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        REFERENCE(8, BE, NumberOfFiles, "Number of files", N)
        SEQ_OF_REF(FileList, "File list", SIM_REFERSH_FILE_LIST, N, ISIHDR_MARKER_SINGLE_ELEMENT_BYTE)
        FILLER(FILLER_VARIABLE, 32)
    SUB_MSG_END
    
    /* SIM_REFRESH_NTF - SIM_ST_REFRESH_CANCELLED */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT(COMMENT_TEXT, "This notification informs clients that the refresh is cancelled.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Only clients that has registered to refresh of one or more of the files to refresh, receives this notification.")
    SUB_MSG_BEGIN(SIM_ST_REFRESH_CANCELLED, SIM_REFRESH_NTF, MESSAGE_NTF, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    /* SIM_REFRESH_NTF - SIM_ST_REFRESH_STARTING */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT(COMMENT_TEXT, "This notification informs a client that refresh is starting.")
        SUB_MSG_BEGIN(SIM_ST_REFRESH_STARTING, SIM_REFRESH_NTF, MESSAGE_NTF, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    /* SIM_MMS_REQ - SIM_ST_MMS_ICP_READ */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read all MMS Issuer Connectivity Parameters in EFmmsicp on USIM")
    SUB_MSG_BEGIN(SIM_ST_MMS_ICP_READ, SIM_MMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_MMS_ICP_READ_STATUS, SIM_STATUS_MMS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
   
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_MMS_REQ.SIM_ST_MMS_UP_READ                                 */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_MMS_UP_READ_REQ tSIM_Request")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_MMS_ICP_READ_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns all MMS Issuer Connectivity Parameters in EFmmsicp on USIM")
    SUB_MSG_BEGIN(SIM_ST_MMS_ICP_READ, SIM_MMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	VALUE_CONST(Status, "Status", SIM_ST_MMS_ICP_READ_STATUS)
	FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_MMS_CONNECTIVITY_PARAMETERS_ID)
        SB_LST_END
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_MMS_ICP_READ, SIM_MMS_REQ, SIM_ST_MMS_ICP_READ, SIM_MMS_RESP)
    
    /* SIM_MMS_REQ - SIM_ST_MMS_UP_READ */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read MMS User Preferences in EFsup on USIM")
    SUB_MSG_BEGIN(SIM_ST_MMS_UP_READ, SIM_MMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_MMS_UP_READ_STATUS, SIM_STATUS_MMS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_DATA_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_STA_FILE_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_IMS_REQ.SIM_ST_IMS_START_SESSION                           */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_START_SESSION_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_START_SESSION_RESP tSIM_Response")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_IMS_REQ.SIM_ST_IMS_END_SESSION                             */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_END_SESSION_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_END_SESSION_RESP tSIM_Response")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_IMS_REQ.SIM_ST_IMS_STATUS                                  */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_STATUS_REQ tSIM_Request")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define tSIM_ST_IMS_STATUS_RESP tSIM_Response")
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_MMS_UP_READ_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the MMS User Preferences in EFsup on USIM")
    SUB_MSG_BEGIN(SIM_ST_MMS_UP_READ, SIM_MMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_MMS_UP_READ_STATUS)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_MMS_USER_PREFERENCES_ID)
        SB_LST_END
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_MMS_UP_READ, SIM_MMS_REQ, SIM_ST_MMS_UP_READ, SIM_MMS_RESP)
    
    /* SIM_IMS_REQ - SIM_ST_IMS_START_SESSION */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to check if an ISIM application exists on UICC.")
    SUB_MSG_BEGIN( SIM_ST_IMS_START_SESSION, SIM_IMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_IMS_START_SESSION_STATUS, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_ISIM_AVAILEBLE_PIN_REQUIRED)
        DER_CONST_TBL_ENTRY(SIM_STA_ISIM_AVAILEBLE)
        DER_CONST_TBL_ENTRY(SIM_STA_USIM_AVAILEBLE)
        DER_CONST_TBL_ENTRY(SIM_STA_SIM_AVAILEBLE)
        DER_CONST_TBL_ENTRY(SIM_STA_ISIM_NOT_INITIALIZED)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END
  
    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the type of application on UICC.")
    SUB_MSG_BEGIN(SIM_ST_IMS_START_SESSION, SIM_IMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_ST_IMS_START_SESSION_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_IMS_START_SESSION, SIM_IMS_REQ, SIM_ST_IMS_START_SESSION, SIM_IMS_RESP)

    /* SIM_IMS_REQ - SIM_ST_IMS_END_SESSION */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to terminate a ISIM session.")
    SUB_MSG_BEGIN( SIM_ST_IMS_END_SESSION, SIM_IMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    DER_CONST_TBL_BEGIN(SIM_ST_IMS_END_SESSION_STATUS, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
  
    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns result of terminating an ISIM session.")
    SUB_MSG_BEGIN(SIM_ST_IMS_END_SESSION, SIM_IMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_HTML_ONLY)
        COMMENT(COMMENT_TEXT, "SIM_STA_NOT_OK: No ISIM session was running.")
        VALUE_CONST(Status, "Status", SIM_ST_IMS_END_SESSION_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_IMS_END_SESSION, SIM_IMS_REQ, SIM_ST_IMS_END_SESSION, SIM_IMS_RESP)

    /* SIM_IMS_REQ - SIM_ST_IMS_STATUS */

    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client request the state of support for ISIM/IMS.")
    SUB_MSG_BEGIN( SIM_ST_IMS_STATUS, SIM_IMS_REQ, MESSAGE_REQ, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    /* Define placed as a comment above */
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the state of support for ISIM/IMS.")
    SUB_MSG_BEGIN(SIM_ST_IMS_STATUS, SIM_IMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        VALUE_CONST(Status, "Status", SIM_ST_IMS_START_SESSION_STATUS)
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_IMS_STATUS, SIM_IMS_REQ, SIM_ST_IMS_STATUS, SIM_IMS_RESP)

    /* SIM_IMS_REQ - SIM_ST_IMS_READ_DATA */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_IMS_READ_DATA_REQ_READ_DATA")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message allows a client to read data from ISIM application on UICC. If ISIM application is not "
                          "available then the information is derived from IMSI from USIM or SIM application on UICC.")
    SUB_MSG_BEGIN(SIM_ST_IMS_READ_DATA, SIM_IMS_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_ST_IMS_READ_DATA_REQ  Req;") \
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Blocks", N, ISIHDR_MARKER_SINGLE_ELEMENT)
            SB_LST_ENTRY(SIM_SB_IMS_PRIVATE_USER_ID)
            SB_LST_ENTRY(SIM_SB_IMS_PUBLIC_USER_ID)
            SB_LST_ENTRY(SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID)
        SB_LST_REF_END
    SUB_MSG_END
   
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_IMS_READ_DATA_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")    
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns data from ISIM application")
    SUB_MSG_BEGIN(SIM_ST_IMS_READ_DATA, SIM_IMS_RESP, MESSAGE_RESP, "", "")
        SIM_MSG_HDR
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_IMS_END_SESSION_STATUS)
        REFERENCE(8, BE, NumberOfSubblocks, "Number of Sub Blocks", N)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_IMS_PRIVATE_USER_ID)
            SB_LST_ENTRY(SIM_SB_IMS_PUBLIC_USER_ID)
            SB_LST_ENTRY(SIM_SB_IMS_HOME_NW_DOMAIN_NAME_ID)
        SB_LST_END
    SUB_MSG_END
    
    SUB_MSG_PAIR(SIM_ST_IMS_READ_DATA, SIM_IMS_REQ, SIM_ST_IMS_READ_DATA, SIM_IMS_RESP)
    

    /* SIM_TRACFONE_SIMLOCK_STATUS_REQ - NO_SERVICE_TYPE */
    
    DER_CONST_TBL_BEGIN(SIM_TRACFONE_SIMLOCK_STATUS_RESP_STATUS_TABLE, SIM_STA_TABLE, "", "016.000")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END


    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_TRACFONE_SIMLOCK_STATUS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_TRACFONE_SIMLOCK_STATUS_REQ, MESSAGE_REQ, "", "016.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        FILLER_EX(Padding, 8, 1)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_TRACFONE_SIMLOCK_STATUS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(NO_SERVICE_TYPE, SIM_TRACFONE_SIMLOCK_STATUS_RESP, MESSAGE_RESP, "", "016.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_TRACFONE_SIMLOCK_STATUS_RESP_STATUS_TABLE)
    SUB_MSG_END
    
    SUB_MSG_PAIR(NO_SERVICE_TYPE, SIM_TRACFONE_SIMLOCK_STATUS_REQ, NO_SERVICE_TYPE, SIM_TRACFONE_SIMLOCK_STATUS_RESP)

    /* SIM_TRACFONE_REQ(SIM_ST_TRACFONE_STATUS) */

    DER_CONST_TBL_BEGIN(SIM_ST_TRACFONE_STATUS_TABLE, SIM_STA_TABLE, "016.000", "020.000")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END

    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_STATUS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to get the status of the Tracfone simlock feature.")
    SUB_MSG_BEGIN( SIM_ST_TRACFONE_STATUS, SIM_TRACFONE_REQ, MESSAGE_REQ, "016.000", "020.000")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_STATUS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message returns the status of the Tracfone simlock feature.")
     SUB_MSG_BEGIN(SIM_ST_TRACFONE_STATUS, SIM_TRACFONE_RESP, MESSAGE_RESP, "016.000", "020.000")
        SUB_MSG_RESP(SIM_ST_TRACFONE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_TRACFONE_STATUS, SIM_TRACFONE_REQ, SIM_ST_TRACFONE_STATUS, SIM_TRACFONE_RESP)


    /* SIM_TRACFONE_REQ(SIM_ST_TRACFONE_COMPLETED_SUCCESS) */

    DER_CONST_TBL_BEGIN(SIM_ST_TRACFONE_COMPLETED_SUCCESS_TABLE, SIM_STA_TABLE, "016.000", "020.000")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_COMPLETED_SUCCESS_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to inform the SIM server that the Tracfone simlock feature is successfully completed.")
    SUB_MSG_BEGIN( SIM_ST_TRACFONE_COMPLETED_SUCCESS, SIM_TRACFONE_REQ, MESSAGE_REQ, "016.000", "020.000")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_COMPLETED_SUCCESS_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_TRACFONE_COMPLETED_SUCCESS, SIM_TRACFONE_RESP, MESSAGE_RESP, "016.000", "020.000")
        SUB_MSG_RESP(SIM_ST_TRACFONE_COMPLETED_SUCCESS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_TRACFONE_COMPLETED_SUCCESS, SIM_TRACFONE_REQ, SIM_ST_TRACFONE_COMPLETED_SUCCESS, SIM_TRACFONE_RESP)


    /* SIM_TRACFONE_REQ(SIM_ST_TRACFONE_COMPLETED_FAIL) */

    DER_CONST_TBL_BEGIN(SIM_ST_TRACFONE_COMPLETED_FAIL_TABLE, SIM_STA_TABLE, "016.000", "020.000")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_STA_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_STA_ERROR)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_COMPLETED_FAIL_REQ")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This message allows a client to inform the SIM server that the Tracfone simlock feature is unsuccessfully completed.")
    SUB_MSG_BEGIN( SIM_ST_TRACFONE_COMPLETED_FAIL, SIM_TRACFONE_REQ, MESSAGE_REQ, "016.000", "020.000")
        SUB_MSG_REQ
        FILLER_EX(Paddingbyte, 8, 1)
    SUB_MSG_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_COMPLETED_FAIL_RESP")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(SIM_ST_TRACFONE_COMPLETED_FAIL, SIM_TRACFONE_RESP, MESSAGE_RESP, "016.000", "020.000")
        SUB_MSG_RESP(SIM_ST_TRACFONE_COMPLETED_FAIL_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_TRACFONE_COMPLETED_FAIL, SIM_TRACFONE_REQ, SIM_ST_TRACFONE_COMPLETED_FAIL, SIM_TRACFONE_RESP)

    
    /* SIM_TRACFONE_NTF(SIM_ST_TRACFONE_REQUESTED) */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ST_TRACFONE_REQUESTED_NTF")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT,"This notification requests the Tracfone server to verify the Tracfone simlock.")
    SUB_MSG_BEGIN(SIM_ST_TRACFONE_REQUESTED, SIM_TRACFONE_NTF, MESSAGE_NTF, "016.000", "020.000")
        SUB_MSG_REQ
        FILLER_EX(Pad1, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT,"The ICCID of the inserted UICC")
        SEQ_OF(ICC_id, "ICCID", AUTOGEN_SEQ_BYTE_HEX, 10)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_GAIT_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOSERVICE)
        DER_CONST_TBL_ENTRY(SIM_SERV_NOTREADY)
        DER_CONST_TBL_ENTRY(SIM_SERV_ERROR)
    DER_CONST_TBL_END


    /* SIM_PN_READ_REQ */
    
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Number index at SIM Card")
    COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "typedef uint16 tSIM_NumberLoc;")

    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define SIM_PutLocation(pReqMsg, location) PUTB16(&(pReqMsg->Location),location)")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadNumberReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    MSG_BEGIN(SIM_PN_READ_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request     Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(ServiceType, "Service Type", SIM_PN_SERVICE_TYPE_TABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tSIM_NumberLoc")
        VALUE(16, BE, Location, "Location", DEC)
    MSG_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ReadNumberResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    MSG_BEGIN(SIM_PN_READ_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response        Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(ServiceType, "Service Type", SIM_PN_SERVICE_TYPE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_GAIT_STATUS_TABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tSIM_NumberLoc")
        VALUE(16, BE, Location, "Location", DEC)
        FILLER_EX(padding, 8, 1)    
        FILLER_EX(padding1, 8, 1)   
        SEQ_OF(NameNumber, "NameNumber", tSIM_Number, ISIHDR_MARKER_ANYSIZE)
    MSG_END

    MSG_PAIR(SIM_PN_READ_REQ, SIM_PN_READ_RESP)




    /* SIM_PN_WRITE_REQ */
    
    DER_CONST_TBL_BEGIN(SIM_PN_WRITE_REQ_ST_TABLE, SIM_PN_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_VMBX)
    DER_CONST_TBL_END
        
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Request     Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_NumberLoc Location;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   padding;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   padding1;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Number NameNumber;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_NumberStr;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define  SIM_GetLocation(pMsgReq) GETB16(&(pMsgReq->Location))")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define  SIM_GetNamePtr(pMsgReq)  ((char16*)(pMsgReq->NameNumber.NamNum))")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#define  SIM_GetNumPtr(pMsgReq)   ((char16*)(pMsgReq->NameNumber.NamNum + pMsgReq->NameNumber.NameLen))")

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteNumberReq")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    MSG_BEGIN(SIM_PN_WRITE_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request     Req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(ServiceType, "Service Type", SIM_PN_WRITE_REQ_ST_TABLE)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "tSIM_NumberLoc")
        VALUE(16, BE, Location, "Location", DEC)
        FILLER_EX(padding, 8, 1)
        FILLER_EX(padding1, 8, 1)
        SEQ_OF(NameNumber, "NameNumber", tSIM_Number, ISIHDR_MARKER_ANYSIZE)
    MSG_END
     
#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_HOME_ZONE_REQ.CHECK_CELL_ID                                */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Request     Req;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Line;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_PLMN_STR Current_PLMN;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Paddingbyte;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_INFO_ZONE_IDENTITY_STR Current_Zone;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_HomeZoneCheck_CellID_Req;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_WriteNumberResp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    MSG_BEGIN(SIM_PN_WRITE_RESP, MESSAGE_RESP, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Response        Resp;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(ServiceType, "Service Type", SIM_PN_WRITE_REQ_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE_CONST(Status, "Status", SIM_GAIT_STATUS_TABLE)
    MSG_END

    MSG_PAIR(SIM_PN_WRITE_REQ, SIM_PN_WRITE_RESP)





    /* SIM_PUCT_REQ - SIM_ST_SET */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PuctSet_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests setting of price per unit and currency table(PUCT) in EFpuct.")
    SUB_MSG_BEGIN(SIM_ST_SET, SIM_PUCT_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR 
        FILLER_EX(Padding, 8, 1)
        SEQ_OF(PuctStr, "PuctStr", SIM_PUCT_UNICODE, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PuctSet_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of setting the price per unit and currency table(PUCT)in EFpuct.")
    SUB_MSG_BEGIN(SIM_ST_SET, SIM_PUCT_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_GAIT_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_SET, SIM_PUCT_REQ, SIM_ST_SET, SIM_PUCT_RESP)

/* SIM_PUCT_REQ - SIM_ST_READ_AOC */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PuctRead_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the value of price per unit and currency table(PUCT) in EFpuct.")
    SUB_MSG_BEGIN(SIM_ST_READ_AOC, SIM_PUCT_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ_HDR 
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PuctRead_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the value of price per unit and currency table(PUCT) in EFpuct.")
    SUB_MSG_BEGIN(SIM_ST_READ_AOC, SIM_PUCT_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_INFO_HDR(SIM_GAIT_STATUS_TABLE)
        SEQ_OF(PuctStr, "PuctStr", SIM_PUCT_UNICODE, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_READ_AOC, SIM_PUCT_REQ, SIM_ST_READ_AOC, SIM_PUCT_RESP)

/* SIM_HOME_ZONE_REQ - CHECK_CELL_ID */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_HomeZoneCheck_CellID_Req")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(CHECK_CELL_ID, SIM_HOME_ZONE_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQUEST_HDR
        VALUE(8, BE, Line, "Line", DEC)
        SEQ_OF(Current_PLMN, "Current_PLMN", SIM_INFO_PLMN_STR, ISIHDR_MARKER_ANYSIZE)
        FILLER_EX(Paddingbyte, 8, 1)
        SEQ_OF(Current_Zone, "Current_Zone", SIM_INFO_ZONE_IDENTITY_STR, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_HomeZoneCheck_CellID_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(CHECK_CELL_ID, SIM_HOME_ZONE_RESP, MESSAGE_RESP, "", "020.000")
        SUB_MSG_RESP_HDR(SIM_READ_FIELD_STATUS)
    SUB_MSG_END

    SUB_MSG_PAIR(CHECK_CELL_ID, SIM_HOME_ZONE_REQ, CHECK_CELL_ID, SIM_HOME_ZONE_RESP)

/* SIM_HOME_ZONE_REQ - READ_COORDINATES */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_HOME_ZONE_RESP.READ_COORDINATES                            */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_SERV_ZONE_COORD_STR ZoneCoordinates;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_HomeZoneRead_Coord_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_HomeZoneRead_Coord_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_COORDINATES, SIM_HOME_ZONE_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR
    SUB_MSG_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_HomeZoneRead_Coord_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_COORDINATES, SIM_HOME_ZONE_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_READ_FIELD_STATUS)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "SIM_SERV_ZONE_COORD_STR")
        SEQ_OF(ZoneCoordinates, "ZoneCoordinates", SIM_SERV_ZONE_COORD_STR, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_COORDINATES, SIM_HOME_ZONE_REQ, READ_COORDINATES, SIM_HOME_ZONE_RESP)

    /* SIM_JACOB_REQ - READ_ID */

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_JACOB_RESP.READ_ID                                         */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_InfoResponse Resp;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_JACOB_ID_READ_STR JACOB_ID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_JacobRead_ID_Resp;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_JacobRead_ID_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_ID, SIM_JACOB_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR 
        VALUE(16, BE, Location, "Location", DEC)
    SUB_MSG_END
     
    DER_CONST_TBL_BEGIN(SIM_JACOB_REQ_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_JacobRead_ID_Resp")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(READ_ID, SIM_JACOB_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_JACOB_REQ_STATUS_TABLE)
        SEQ_OF(JACOB_ID, "JACOB_ID", SIM_JACOB_ID_READ_STR, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_ID, SIM_JACOB_REQ, READ_ID, SIM_JACOB_RESP)


    /* SIM_JACOB_REQ - READ_REAL_JACOB_IDS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_Real_JacobIDs_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    SUB_MSG_BEGIN(READ_REAL_JACOB_IDS, SIM_JACOB_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQUEST_HDR 
    SUB_MSG_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Read_Real_JacobIDs_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    SUB_MSG_BEGIN(READ_REAL_JACOB_IDS, SIM_JACOB_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(SIM_JACOB_REQ_STATUS_TABLE)
        VALUE(8, BE, jacob_count, "jacob_count", DEC)
        FILLER_EX(paddingbyte, 8, 1)
        PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "word")
        SEQ_OF(Real_JacobIDs, "Real_JacobIDs", AUTOGEN_SEQ_WORD_DEC, SIM_MAX_NBR_OF_JACOB_IDS)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_REAL_JACOB_IDS, SIM_JACOB_REQ, READ_REAL_JACOB_IDS, SIM_JACOB_RESP)


    /* SIM_TARIFF_REQ - READ_PACKAGE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_TariffRead_Package_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    SUB_MSG_BEGIN(READ_PACKAGE, SIM_TARIFF_REQ, MESSAGE_REQ, "", "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF, "    tSIM_Request     req;") 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        VALUE(8, BE, TransID, "Transaction ID", DEC) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID) 
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE) 
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
    SUB_MSG_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_TariffRead_Package_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    PROPERTY(PROPERTY_HTML_DONT_GENERATE)
    COMMENT(COMMENT_TEXT, "DON'T USE THIS MESSAGE IN FUTURE DEVELOPMENT") 
    SUB_MSG_BEGIN(READ_PACKAGE, SIM_TARIFF_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_INFO_HDR(SIM_JACOB_REQ_STATUS_TABLE)
        VALUE(8, BE, TariffPackage, "TariffPackage", DEC)
    SUB_MSG_END

    SUB_MSG_PAIR(READ_PACKAGE, SIM_TARIFF_REQ, READ_PACKAGE, SIM_TARIFF_RESP)

    /* SIM_GPRS_REQ - SIM_ST_ACL_STATUS */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Status_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message requests the status of the ACL feature in EFust on USIM.")
    SUB_MSG_BEGIN(SIM_ST_ACL_STATUS, SIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_STATUS_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_ENABLED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Status_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the status of the ACL feature in EFust on USIM.")
    SUB_MSG_BEGIN(SIM_ST_ACL_STATUS, SIM_GPRS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Status of the ACL feature in EFust on USIM.")
        VALUE_CONST(status, "status", SIM_ST_ACL_STATUS_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACL_STATUS, SIM_GPRS_REQ, SIM_ST_ACL_STATUS, SIM_GPRS_RESP)

    /* SIM_GPRS_REQ - SIM_ST_ACL_ENABLE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Enable_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message enables the ACL feature in EFust on USIM. ")
    COMMENT(COMMENT_TEXT, "The request is PIN2 protected.")
    SUB_MSG_BEGIN(SIM_ST_ACL_ENABLE, SIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_ENABLE_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Enable_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of enabling the ACL feature in EFust on USIM.")
    SUB_MSG_BEGIN(SIM_ST_ACL_ENABLE, SIM_GPRS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(status, "status", SIM_ST_ACL_ENABLE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACL_ENABLE, SIM_GPRS_REQ, SIM_ST_ACL_ENABLE, SIM_GPRS_RESP)

    /* SIM_GPRS_REQ - SIM_ST_ACL_DISABLE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Disable_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message disables the ACL feature in EFust on USIM. ")
    COMMENT(COMMENT_TEXT, "The request is PIN2 protected.")
    SUB_MSG_BEGIN(SIM_ST_ACL_DISABLE, SIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_DISABLE_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Disable_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of disabling the ACL feature in EFust on USIM.")
    SUB_MSG_BEGIN(SIM_ST_ACL_DISABLE, SIM_GPRS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(status, "status", SIM_ST_ACL_DISABLE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACL_DISABLE, SIM_GPRS_REQ, SIM_ST_ACL_DISABLE, SIM_GPRS_RESP)

    /* SIM_GPRS_REQ - SIM_ST_ACL_READ */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Read_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message reads the content of the ACL file on USIM (EFacl).")
    SUB_MSG_BEGIN(SIM_ST_ACL_READ, SIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        FILLER_EX(pad1, 8, 1)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_READ_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Read_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the content of the ACL file on USIM (EFacl).")
    SUB_MSG_BEGIN(SIM_ST_ACL_READ, SIM_GPRS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_ACL_READ_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Maximum size of free data space available in the ACL file on USIM (EFacl) for APN TLV's.")
	COMMENT(COMMENT_TEXT, "MaxDataSpace is used when writing data to the ACL file.")
        VALUE(16, BE, MaxDataSpace, "MaxDataSpace", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "The length of the data including APN TLv's.")
        REFERENCE(16, BE, DataLength, "DataLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Number of APN TLVs in ACL file.")
        VALUE(8, BE, DataNumTLV, "DataNumTLV", DEC)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        FILLER_EX(Pad3, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "List of APN's in  TLV format. Format is APN TLV is avalilable in 3GPP TS 31.102.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACL_READ, SIM_GPRS_REQ, SIM_ST_ACL_READ, SIM_GPRS_RESP)

    /* SIM_GPRS_REQ - SIM_ST_ACL_WRITE */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Write_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message writes content to the ACL file on USIM (EFacl).")
    COMMENT(COMMENT_TEXT, "This request is PIN2 protected.")
    SUB_MSG_BEGIN(SIM_ST_ACL_WRITE, SIM_GPRS_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Number of APN TLVs in ACL file.")
        VALUE(8, BE, DataNumTLV, "DataNumTLV", DEC)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "The length of the APN's to write to ACL file.")
	COMMENT(COMMENT_TEXT, "Length must not exceed the ACL file size-1(=Max Data Space-1) returned in SIM_GPRE_REQ(SIM_ACL_READ_RESP).")
        REFERENCE(16, BE, DataLength, "DataLength", N)
        FILLER_EX(Pad1, 8, 1)
        FILLER_EX(Pad2, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "List of APN's in  TLV format to write into ACL file. Format is APN TLV is avalilable in 3GPP TS 31.102.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_WRITE_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_ILLEGAL_LENGTH)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_Write_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of writing APN's into the ACL file on USIM (EFacl).")
    SUB_MSG_BEGIN(SIM_ST_ACL_WRITE, SIM_GPRS_RESP, MESSAGE_RESP, "", "")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_ACL_WRITE_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_ACL_WRITE, SIM_GPRS_REQ, SIM_ST_ACL_WRITE, SIM_GPRS_RESP)

    /* SIM_GPRS_REQ - SIM_ST_CHECK_APN */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CheckAPN_Req")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message checks if an APN is available in the ACL file, EFacl.")
    COMMENT(COMMENT_TEXT, "The format of APN shall follow the APN TLV format in 3GPP TS 31.102 but without the tag value and length.")
    COMMENT(COMMENT_TEXT, "The length is given in the APNlength field.")
    COMMENT(COMMENT_TEXT, "An example of an APN:5nokia3com")
    SUB_MSG_BEGIN(SIM_ST_CHECK_APN, SIM_GPRS_REQ, MESSAGE_REQ, "", "020.000")
        SUB_MSG_REQ
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "Length of APN to check. If length is zero then there will be checked for the network provided APN.")
        REFERENCE(8, BE, APNLength, "APNLength", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "APN to be checked against EFacl. Format see above.")
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_DEC, N, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(SIM_ST_ACL_CHECK_APN_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_APN_CHECK_PASSED)
        DER_CONST_TBL_ENTRY(SIM_STA_APN_CHECK_FAILED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END
     
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_CheckAPN_Resp")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message returns the result of checking if an APn is available in the ACL file, EFacl.")
    SUB_MSG_BEGIN(SIM_ST_CHECK_APN, SIM_GPRS_RESP, MESSAGE_RESP, "", "020.000")
        VALUE(8, BE, TransID, "Transaction ID", DEC)
        REFERENCE(8, BE, MessageID, "Message ID", MSG_ID)
        REFERENCE(8, BE, ServiceType, "Service Type", SUB_MSG_ID)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ST_ACL_CHECK_APN_STATUS_TABLE)
    SUB_MSG_END

    SUB_MSG_PAIR(SIM_ST_CHECK_APN, SIM_GPRS_REQ, SIM_ST_CHECK_APN, SIM_GPRS_RESP)

    /* SIM Application Management Request/Response */

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AM_REQ") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message is used for various application management functions.")
        MSG_BEGIN(SIM_AM_REQ, MESSAGE_REQ, "017.003", "020.000")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_AM_SERVICE_TYPE_TABLE)
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY_VER(SIM_SB_AM_HANDLE_ID,       "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_SERVICE_ID_ID,   "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_FILE_DATA_ID_ID, "017.003", "020.000")
        SB_LST_REF_END
    MSG_END

    DER_CONST_TBL_BEGIN(SIM_AM_STATUS, SIM_SERV_STA_TABLE, "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_STA_OK,        "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_STA_SB_NOT_OK, "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_STA_NOT_OK,    "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_NOSERVICE,     "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_NOTREADY,      "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_SERV_ERROR,         "017.003", "020.000")
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AM_RESP") 
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "The server returns this message to the requesting application.")
    MSG_BEGIN(SIM_AM_RESP, MESSAGE_RESP, "017.003", "020.000")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_AM_SERVICE_TYPE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_AM_STATUS)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, NoOfSubBlocks, "NoOfSubBlocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, sub_blocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY_VER(SIM_SB_AM_HANDLE_ID,           "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_APP_INFO_RECORD_ID,  "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_SERVICE_ID_ID,       "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_IMS_PRIVATE_USER_ID,    "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_RAND_PARAMS_ID,         "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_B_TID_ID,        "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_KEY_LIFETIME_ID, "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_GBA_GBANL_RECORD_ID, "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MSK_RECORD_ID,  "017.003", "020.000")
            SB_LST_ENTRY_VER(SIM_SB_AM_MBMS_MUK_RECORD_ID,  "017.003", "020.000")
        SB_LST_REF_END
    MSG_END

    MSG_PAIR(SIM_AM_REQ, SIM_AM_RESP)
    
    /* --------------------------------------------------------------------- */
    /* Indications                                                           */ 
    /* --------------------------------------------------------------------- */

/* SIM_ICC_TYPE_IND */

    DER_CONST_TBL_BEGIN(SIM_ICC_TYPE_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(NO_SERVICE_TYPE)
    DER_CONST_TBL_END
    
    DER_CONST_TBL_BEGIN(SIM_ICC_TYPE_IND_STATUS_TABLE, SIM_STA_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_SB_NOT_OK)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ICC_TYPE_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when the type of card inserted in ME is identified.")
    COMMENT(COMMENT_PARAGRAPH,  "    ")
    COMMENT(COMMENT_TEXT, "This indication is broadcasted before the PIN code is verified.")
    MSG_BEGIN(SIM_ICC_TYPE_IND, MESSAGE_IND, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_ICC_TYPE_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_ICC_TYPE_IND_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        COMMENT(COMMENT_TEXT, "RFU")
        VALUE(8, BE, CardReaderID, "CardReaderID", DEC)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        REFERENCE(8, BE, NumberOfSubblocks, "NumberOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "SIM_SB_AID_ID is repeated as many times as there are AIDs in the DIR file.")
        COMMENT(COMMENT_PARAGRAPH,  "    ")
	    COMMENT(COMMENT_TEXT, "SIM_SB_AID_ID is not always available. It is only available if there are a new card inserted.")
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCKS, Subblocks, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_SB_ICC_TYPE_ID)
            SB_LST_ENTRY(SIM_SB_AID_ID)
            SB_LST_ENTRY(SIM_SB_ICCID_ID)
        SB_LST_REF_END
    MSG_END

/* SIM_IMS_IND */

    DER_CONST_TBL_BEGIN(SIM_IMS_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(NO_SERVICE_TYPE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_IMS_IND_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_STA_IMS_READY)
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IMS_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when and ISIM/IMS session has been initialized with succes and all relevant PIN codes been verified.")
    MSG_BEGIN(SIM_IMS_IND, MESSAGE_IND, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_IMS_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_IMS_IND_STATUS_TABLE)
    MSG_END

/* SIM_IND - tSIM_Ind */

    DER_CONST_TBL_BEGIN(SIM_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_ALL_SERVICES )
	DER_CONST_TBL_ENTRY(SIM_ST_PIN)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN2)
        DER_CONST_TBL_ENTRY(SIM_ST_PIN_UNIVERSAL)
        DER_CONST_TBL_ENTRY(SIM_ST_APP_SELECTION)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_IND_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_INIT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_DISCONNECTED)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIM_REJECTED)
/* To be defined when the tables have been re-arranged to avoid two entries with same value
        DER_CONST_TBL_ENTRY(SIM_SERV_SIMLOCK_RESTRICTION_ON)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIMLOCK_RESTRICTED)
        DER_CONST_TBL_ENTRY(SIM_SERV_SIMLOCK_RESTRICTION_PENDING)*/
        DER_CONST_TBL_ENTRY(SIM_SERV_COMMUNICATION_ERROR)
        DER_CONST_TBL_ENTRY(SIM_SERV_STATE_CHANGED)
        DER_CONST_TBL_ENTRY(SIM_SERV_IMSI_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_IMSI_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_ICC_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_ICC_NOT_EQUAL)
        DER_CONST_TBL_ENTRY(SIM_SERV_PN_LIST_ENABLE_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_PN_LIST_DISABLE_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_APP_DATA_READ_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_OK)
        DER_CONST_TBL_ENTRY(SIM_STA_APP_ACTIVATE_NOT_OK)
    DER_CONST_TBL_END
    
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   TransID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   MessageID;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   ServiceType;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Status;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   State;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   Cause;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    uint8   ApplicationNumber;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_Indication;")
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Ind")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This indication is broadcasted whenever an event occurs in the SIM server.")
    MSG_BEGIN(SIM_IND, MESSAGE_BASE, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "| SIM_SERV_SIMLOCK_RESTRICTION |")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_SERV_SIMLOCK_RESTRICTION_ON |")
        COMMENT(COMMENT_NEWLINE, "")
	COMMENT(COMMENT_TEXT, "SIM_SERV_SIMLOCK_RESTRICTION_PENDING")
        VALUE_CONST(Status, "Status", SIM_IND_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(State, "State", SIM_STATE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Cause, "Cause", SIM_CAUSES_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Application on (U)SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        FILLER_EX(Pad1, 8, 1)
    MSG_END

/* SIM_IND - PREF_LANGUAGE */

    DER_CONST_TBL_BEGIN(SIM_IND_PREF_LANG_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_OK)
        DER_CONST_TBL_ENTRY(SIM_SERV_DATA_NOT_AVAIL)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_IND_PREF_LANG_STATE_TABLE, SIM_STATE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(STATE_SIM_INIT_WAIT)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_IND_PREF_LANG_CAUSE_TABLE, SIM_CAUSES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_NO_CAUSE)
    DER_CONST_TBL_END

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* Message: SIM_IND.EMERGENCY_CODES                                        */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/* ----------------------------------------------------------------------- */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "typedef struct")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    {")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    tSIM_Ind        Head;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    SIM_EMRG_CALL_CODES_STR EmergCodes;")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "    } tSIM_IndEmergencyCalls;")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_Ind_PrefLanguage")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message includes the Preferred Language information avaialble in EFlp or EFpl \
                           depending on which application on UICC that is selected. \
                            The indication is broadcasted when the SIM server is initializing.")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "Note: The coding of EFpl is converted from 2 byte IS=639 format to 1 byte GSM 03.30/23.038. format.")
    SUB_MSG_BEGIN(PREF_LANGUAGE, SIM_IND, MESSAGE_IND, "", "")
        SUB_MSG_IND_HDR(SIM_IND_PREF_LANG_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(State, "State", SIM_IND_PREF_LANG_STATE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Cause, "Cause", SIM_IND_PREF_LANG_CAUSE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Application on (U)SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER_EX(Pad, 8, 1)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Number of language codes N, 0=\<N<=4 ")
        VALUE(8, BE, Count, "Count", DEC)
	    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	    COMMENT(COMMENT_TEXT, "Language codes, highest priority first.")
        SEQ_OF(LanguageTable, "LanguageTable", AUTOGEN_SEQ_BYTE_DEC, SIM_LANG_PREF_LEN)
    SUB_MSG_END

/* SIM_IND - EMERGENCY_CODES */

#ifdef S60_INTERFACE
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_IndEmergencyCalls")
#else
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
#endif
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message includes the Emergency Call Codes avaialble in EFecc")
    COMMENT(COMMENT_TEXT, "The indication is broadcasted when the SIM server is initilizing")
    SUB_MSG_BEGIN(EMERGENCY_CODES, SIM_IND, MESSAGE_IND, "", "")
        SUB_MSG_IND_HDR(SIM_IND_PREF_LANG_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(State, "State", SIM_IND_PREF_LANG_STATE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        VALUE_CONST(Cause, "Cause", SIM_IND_PREF_LANG_CAUSE_TABLE)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
	COMMENT(COMMENT_TEXT, "Application on (U)SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
        FILLER_EX(Pad, 8, 1)
	COMMENT(COMMENT_TEXT, "If an Emergency Call Code is less than 6 digits a Null terminator is inserted after the last digit.")
	COMMENT(COMMENT_TEXT, "Due to backward compatibility reasons only the first 5 ECC without alpha identifier are send out in 3G mode")
        SEQ_OF(EmergCodes, "EmergCodes", SIM_EMRG_CALL_CODES_STR, ISIHDR_MARKER_ANYSIZE)
    SUB_MSG_END

/* SIM_PB_IND */

    DER_CONST_TBL_BEGIN(SIM_PB_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(NO_SERVICE_TYPE)
    DER_CONST_TBL_END

#ifndef S60_INTERFACE
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "/******************************************************************************")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "*  This include statement will include if propriate flags is set, include")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "*  the remaining structures,definitions  and  other include file needed to")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "*  build the old DSS SIM Server.")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "*")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "******************************************************************************/")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#ifdef SIM_HYBRID")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " #include \"dct4_srvsim_msg.h\"")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, "#endif /* SIM_HYBRID */")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
    COMMENT(COMMENT_ISIHDR_AFTER_DEF, " ")
#endif

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_PB_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when the status of FDN on (U)SIM is changed or during ME startup.")
    MSG_BEGIN(SIM_PB_IND, MESSAGE_IND, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_PB_IND_ST_TABLE)
        REFERENCE(8, BE, NumberOfSubBlocks, "NumberOfSubBlocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, Subblocks, "Subblocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY(SIM_PB_FDN_LIST_STATUS)
        SB_LST_REF_END
    MSG_END

/* SIM_SERVER_READY_IND */

    DER_CONST_TBL_BEGIN(SIM_SERVER_READY_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_ST_ALL_SERVICES)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVER_READY_IND_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_SERV_INIT_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVER_READY_IND_STATE_TABLE, SIM_STATE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(STATE_SIM_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_SERVER_READY_IND_CAUSE_TABLE, SIM_CAUSES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_NO_CAUSE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when the SIM server is ready to received ISI messages. ")
    COMMENT(COMMENT_TEXT, "This indication is broadcasted at the same time as SIM_IND(ST=SIM_ST_INFO, STA=SIM_SERV_INIT_OK. ")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "If a Server or an Application only needs to know when the SIM server is ready then it is \
    strongly recommended to use the SIM_SERVER_READY_IND indication")
    MSG_BEGIN(SIM_SERVER_READY_IND, MESSAGE_IND, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_SERVER_READY_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_SERVER_READY_IND_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(State, "State", SIM_SERVER_READY_IND_STATE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Cause, "Cause", SIM_SERVER_READY_IND_CAUSE_TABLE)
	COMMENT(COMMENT_TEXT, "Application on (U)SIM that is started.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
	FILLER_EX(pad1, 8, 1)
    MSG_END

/* SIM_CS_IND */

    DER_CONST_TBL_BEGIN(SIM_CS_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(CS)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_CS_IND_STATUS_TABLE, SIM_STATUS_TABLE, "", "")
     /* To be defined when the tables have been re-arranged to avoid two entries with same value
      DER_CONST_TBL_ENTRY(SIM_SERV_SIM_REMOVED_CS)*/    
        DER_CONST_TBL_ENTRY(SIM_SERV_CONNECTED_INDICATION_CS)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_LOST_IND_CS)
        DER_CONST_TBL_ENTRY(SIM_SERV_PIN_RIGHTS_GRANTED_IND_CS)
        DER_CONST_TBL_ENTRY(SIM_SERV_INIT_OK_CS)
        DER_CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK_CS)
     /* To be defined when the tables have been re-arranged to avoid two entries with same value
     DER_CONST_TBL_ENTRY(SIM_SERV_INIT_OK_TDMA_CS)
     DER_CONST_TBL_ENTRY(SIM_SERV_INIT_NOT_OK_TDMA_CS)*/
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_CS_IND_STATE_TABLE, SIM_STATE_TABLE, "", "")
        DER_CONST_TBL_ENTRY(STATE_SIM_INIT_WAIT)
        DER_CONST_TBL_ENTRY(STATE_SIM_LOCK_OPERATIVE)
        DER_CONST_TBL_ENTRY(STATE_SIM_PIN_VERIFY_REQUIRED)
        DER_CONST_TBL_ENTRY(STATE_SIM_PERMANENTLY_BLOCKED)
        DER_CONST_TBL_ENTRY(STATE_SIM_REMOVED)
        DER_CONST_TBL_ENTRY(STATE_SIM_REJECTED)
        DER_CONST_TBL_ENTRY(STATE_SIM_BLOCKED)
        DER_CONST_TBL_ENTRY(STATE_SIM_OK)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_CS_IND_CAUSE_TABLE, SIM_CAUSES_TABLE, "", "")
        DER_CONST_TBL_ENTRY(SIM_NO_CAUSE)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT(COMMENT_TEXT, "This indication is broadcasted when an event that is relevant to CS subsystem has occured.")
    MSG_BEGIN(SIM_CS_IND, MESSAGE_IND, "", "")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_CS_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "or SIM_SERV_SIM_REMOVED_CS ")
        VALUE_CONST(Status, "Status", SIM_CS_IND_STATUS_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(State, "State", SIM_CS_IND_STATE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Cause, "Cause", SIM_CS_IND_CAUSE_TABLE)
        COMMENT(COMMENT_TEXT, "Application on (U)SIM that is active.")
        VALUE(8, BE, ApplicationNumber, "ApplicationNumber", DEC)
        FILLER_EX(Pad1, 8, 1)
    MSG_END

/* SIM_ACL_IND */

    DER_CONST_TBL_BEGIN(SIM_ACL_IND_ST_TABLE, SIM_MISC_SERVICE_TYPE_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(NO_SERVICE_TYPE)
    DER_CONST_TBL_END

    DER_CONST_TBL_BEGIN(SIM_ACL_IND_STATUS_TABLE, SIM_GPRS_REQ_STATUS_TABLE, "", "020.000")
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_ENABLED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_DISABLED)
        DER_CONST_TBL_ENTRY(SIM_STA_ACL_NOT_AVAILABLE)
    DER_CONST_TBL_END

/* SIM_AM_IND */

    DER_CONST_TBL_BEGIN(SIM_AM_IND_ST_TYPE_TABLE, SIM_AM_SERVICE_TYPE_TABLE, "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_ST_APP_INFO,  "017.003", "020.000")
    DER_CONST_TBL_END
    
    DER_CONST_TBL_BEGIN(SIM_AM_IND_STATUS_TYPE_TABLE, SIM_STA_TABLE, "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_OK,         "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_NOT_OK,     "017.003", "020.000")
        DER_CONST_TBL_ENTRY_VER(SIM_STA_SB_NOT_OK,  "017.003", "020.000")
    DER_CONST_TBL_END
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_AM_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message distributed to clients indicating events concerning NAA application on (U)SIM.")
    MSG_BEGIN(SIM_AM_IND, MESSAGE_IND, "017.003", "020.000")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_AM_IND_ST_TYPE_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(Status, "Status", SIM_AM_IND_STATUS_TYPE_TABLE)
        FILLER_EX(Padding1, 8, 1)
        FILLER_EX(Padding2, 8, 1)
        FILLER_EX(Padding3, 8, 1)
        REFERENCE(8, BE, NumberOfSubblocks, "NumberOfSubblocks", N)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        SB_LST_REF_BEGIN(LIST_OF_SUBBLOCK_IDS, SubblockID, "Sub Blocks", N, ISIHDR_DONT_GENERATE)
            SB_LST_ENTRY_VER(SIM_SB_AM_HANDLE_ID,           "017.003", "020.000")
        SB_LST_REF_END
    MSG_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "tSIM_ACL_IND")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
    COMMENT(COMMENT_TEXT, "This message indicates a state change of the ACL feature present in the USIM service table, EFust")
    COMMENT(COMMENT_NEWLINE, "")
    COMMENT(COMMENT_TEXT, "The indication is distributed when the ACL feature is enabled or disabled and during start-up.")
    MSG_BEGIN(SIM_ACL_IND, MESSAGE_IND, "", "020.000")
        SIM_MSG_HDR
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
        VALUE_CONST(ServiceType, "Service Type", SIM_ACL_IND_ST_TABLE)
        COMMENT_PROPERTY(COMMENT_PROPERTY_ISIHDR_DISABLE)
	COMMENT(COMMENT_TEXT, "Status of ACL feature.")
        VALUE_CONST(Status, "Status", SIM_ACL_IND_STATUS_TABLE)
    MSG_END
    

    /* --------------------------------------------------------------------- */
    /* APDU interface - Should not be present here as the APDU isi file also is autogenerated  */ 
    /* --------------------------------------------------------------------- */

/* Defined hos APDU
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(APDU_APPLICATION_TYPES, 8, BE, "", "")
        CONST_TBL_ENTRY(APDU_SIM_APPLICATION,          0x00, "")
        CONST_TBL_ENTRY(APDU_WIM_APPLICATION,          0x01, "")
    CONST_TBL_END
*/


/* Defineret i APDU
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(APDU_RFU, 8, BE, "", "")
        CONST_TBL_ENTRY(APDU_RFU,                          0x00, "")
    CONST_TBL_END
*/

    /* APDU_REQ SEND_APDU */

/*    PROPERTY(PROPERTY_ISIHDR_DONT_GENERATE)
    PROPERTY_STRING(PROPERTY_ISIHDR_DEFINITION_NAME, "")
    CONST_TBL_BEGIN(APDU_STATUS_TABLE, 8, BE, "", "")
        CONST_TBL_ENTRY(APDU_SERVER_NOT_ACTIVATED,       0x00, "")
        CONST_TBL_ENTRY(APDU_ACTIVATE_OK,                0x01, "")
        CONST_TBL_ENTRY(APDU_SERVER_ALREADY_ACTIVATED,   0x02, "")
        CONST_TBL_ENTRY(APDU_DEACTIVATE_OK,              0x03, "")
        CONST_TBL_ENTRY(APDU_WARM_RESET_PERFORMED,       0x05, "")
        CONST_TBL_ENTRY(APDU_COLD_RESET_PERFORMED,       0x06, "")
        CONST_TBL_ENTRY(APDU_RESET_IN_PROGRESS,          0x07, "")
        CONST_TBL_ENTRY(APDU_RECOVERY_PERFORMED,         0x08, "")
        CONST_TBL_ENTRY(APDU_CARD_POWERED_OFF,           0x09, "")
        CONST_TBL_ENTRY(APDU_CARD_POWERED_ON,            0x0a, "")
        CONST_TBL_ENTRY(APDU_CARD_INSERTED,              0x0b, "")
        CONST_TBL_ENTRY(APDU_CARD_READER_REMOVED,        0x0e, "")
        CONST_TBL_ENTRY(APDU_SESSION_TIMEOUT,            0x10, "")
        CONST_TBL_ENTRY(APDU_SESSION_PAC_NOT_VALID,      0x12, "")
        CONST_TBL_ENTRY(APDU_NO_SESSION,                 0x13, "")
        CONST_TBL_ENTRY(APDU_DATA_NOT_AVAIL,             0x15, "")
        CONST_TBL_ENTRY(APDU_VOLTAGE_NOT_SUPP,           0x16, "")
        CONST_TBL_ENTRY(APDU_POWER_OFF_NOT_ALLOWED,      0x18, "")
        CONST_TBL_ENTRY(APDU_CARD_ALREADY_OFF,           0x19, "")
        CONST_TBL_ENTRY(APDU_CARD_ALREADY_ON,            0x1a, "")
        CONST_TBL_ENTRY(APDU_RESET_ERROR,                0x1d, "")
        COMMENT(COMMENT_ISIHDR_BEFORE_DEF,
            "/* These values must match the values in the old SIM servers interface: start *//*")
        CONST_TBL_ENTRY(APDU_OK,                         0x3d, "")
        CONST_TBL_ENTRY(APDU_TRANSMISSION_ERROR,         0x3e, "")
        CONST_TBL_ENTRY(APDU_CARD_MUTE,                  0x3f, "")
        CONST_TBL_ENTRY(APDU_CARD_REMOVED,               0x40, "")
        CONST_TBL_ENTRY(APDU_ERROR,                      0x41, "")
        CONST_TBL_ENTRY(APDU_READER_NOT_VALID,           0x42, "")
        CONST_TBL_ENTRY(APDU_FORMAT_ERROR,               0x43, "")
        COMMENT(COMMENT_ISIHDR_AFTER_DEF,
            "/* These values must match the values in the old SIM servers interface: end *//*")
        CONST_TBL_ENTRY(APDU_TYPE_NOT_VALID,             0x44, "")
        CONST_TBL_ENTRY(APDU_PROT_EXEC_ERROR,            0x45, "")
    CONST_TBL_END   
    
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(APDU_ST_SEND_APDU, APDU_REQ, MESSAGE_REQ, "", "")
        SUB_MSG_REQ_HDR
        VALUE(8, BE, CardReaderIdentity, "CardReaderIdentity", DEC)
        VALUE_CONST(CardReaderIdentity, "Card reader identity", APDU_RFU)
        VALUE(8, BE, Type, "Type", DEC)
        VALUE_CONST(Type, "Type", APDU_APPLICATION_TYPES)
        VALUE(8, BE, padding, "Session PAC", HEX)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_MAX_APDU_LEN)
        REFERENCE(16, BE, Length, "Length", N)
        SEQ_OF_REF(APDU, "APDU", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
    SUB_MSG_END

    DER_CONST_TBL_BEGIN(APDU_ST_SEND_STATUS, APDU_STATUS_TABLE, "", "")
        DER_CONST_TBL_ENTRY(APDU_OK)
        DER_CONST_TBL_ENTRY(APDU_CARD_POWERED_OFF)
        DER_CONST_TBL_ENTRY(APDU_FORMAT_ERROR)
        DER_CONST_TBL_ENTRY(APDU_TYPE_NOT_VALID)
        DER_CONST_TBL_ENTRY(APDU_CARD_MUTE)
        DER_CONST_TBL_ENTRY(APDU_SESSION_PAC_NOT_VALID)
        DER_CONST_TBL_ENTRY(APDU_SERVER_NOT_ACTIVATED)
        DER_CONST_TBL_ENTRY(APDU_RESET_IN_PROGRESS)
        DER_CONST_TBL_ENTRY(APDU_TRANSMISSION_ERROR)
        DER_CONST_TBL_ENTRY(APDU_PROT_EXEC_ERROR)
        DER_CONST_TBL_ENTRY(APDU_RESET_ERROR)
    DER_CONST_TBL_END

    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_NAME, "")
    PROPERTY_STRING(PROPERTY_ISIHDR_STRUCT_LENGTH_NAME, "")
    SUB_MSG_BEGIN(APDU_ST_SEND_APDU, APDU_RESP, MESSAGE_RESP, "", "")
        SUB_MSG_RESP_HDR(APDU_ST_SEND_STATUS)
        PROPERTY_VALUE(PROPERTY_ITEM_MAXIMUM_VALUE, SIM_MAX_APDU_DATA_LENGTH)
        REFERENCE(16, BE, Length, "Length", N)
        SEQ_OF_REF(Data, "Data", AUTOGEN_SEQ_BYTE_HEX, N, ISIHDR_RESERVE_SPACE)
    SUB_MSG_END

    SUB_MSG_PAIR(APDU_ST_SEND_APDU, APDU_REQ, APDU_ST_SEND_APDU, APDU_RESP)*/


RES_END




/*  5    DATA TYPES */

/*  6    CLASSES */

/*  7    OBJECTS */

/*  8    DATA STRUCTURES */

/*  9    FUNCTION PROTOTYPES */

#endif /* _SIM_ISI_M_H_

/* End of file sim_isi_m.h */
