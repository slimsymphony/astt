/*
NOKIA MOBILE PHONES
R&D Oulu

Copyright (c) Nokia Mobile Phones. All rights reserved.

-----------------------------------------------------------------------

*/

/*  <conf_file>
     Owner                : Zoran Stevanovic
     SCF                  : TP PP Core SW SASW
     Team                 : MCU Impl & FE FI
     SCF contacts         : Zoran Stevanovic, Anssi Aamurusko
     Parent feature       : ICF_INFO_SERV
</conf_file>*/

/*
------------------------------------------------------------------------
  DESCRIPTION
           The definitions contained herein configure the INFO Server
           system specific features.

---------------------------------------------------------------------------
*/

#ifndef INFO_CONF_H
#define INFO_CONF_H

#include "isa_core_conf.h"

#define INFO_PP_CUSTOMER_ID_DEFAULT     1
/* <conf>
     Name                 : INFO_PP_CUSTOMER_ID_DEFAULT
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Product Profile Default Table ID
                            This product profile table is loaded whenever INFO
                            server detects that permanent memory area of table
                            id is empty. In ISI msg this is the field that is
                            being set when INFO_PP_CUSTOMER_DEFAULTS_REQ
                            is being set.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : Valid range for this constant is between 1 to 10.
     Affected modules     : i_pp.c, i_srvmgr.c
     Responsible          : Mika Halttunen
     Configuration type   : parameter, default setting
     Other comments       :
</conf> */


/*********************************
 * Calypso version query support *
 *********************************/

#define FEA_INFO_MCUSW_VERSION_QUERY_FROM_EPOC     DISABLED
/* <conf>
     Name                 : FEA_INFO_MCUSW_VERSION_QUERY_FROM_EPOC
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable MCUSW version query forward to EPOC
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server forwards version query to EPOC
     If feature is off    : INFO server doesn't forward version query to EPOC
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define FEA_INFO_LANGUAGE_VERSION_QUERY_FROM_EPOC     DISABLED
/* <conf>
     Name                 : FEA_INFO_LANGUAGE_VERSION_QUERY_FROM_EPOC
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable language version query forward to EPOC
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server forwards version query to EPOC
     If feature is off    : INFO server doesn't forward version query to EPOC
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define FEA_INFO_BT_MCM_VERSION_QUERY_FROM_EPOC     DISABLED
/* <conf>
     Name                 : FEA_INFO_BT_MCM_VERSION_QUERY_FROM_EPOC
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable BT MCM version query forward to EPOC
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server forwards version query to EPOC
     If feature is off    : INFO server doesn't forward version query to EPOC
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define FEA_INFO_LCD_VERSION_QUERY     ENABLED
/* <conf>
     Name                 : FEA_INFO_LCD_VERSION_QUERY
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable LCD version query
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server LCD version query is enabled
     If feature is off    : INFO server LCD version query is disabled
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define FEA_INFO_ADSP_VERSION_QUERY     DISABLED
/* <conf>
     Name                 : FEA_INFO_ADSP_VERSION_QUERY
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable adsp version query
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server adsp version query is enabled
     If feature is off    : INFO server adsp version query is disabled
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define FEA_INFO_FLIP_MCUSW_VERSION_QUERY     DISABLED
/* <conf>
     Name                 : FEA_INFO_FLIP_MCUSW_VERSION_QUERY
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable/ disable Flip mcusw version query
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : INFO server flip mcusw version query is enabled
     If feature is off    : INFO server flip mcusw version query is disabled
     Valid range/ values  : enabled/ disabled
     Affected modules     : i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#define INFO_PARALLEL_PRODUCT_EXISTS TRUE /* check for sales_sw_config */
/* <conf>
     Name                 : INFO_PARALLEL_PRODUCT_EXISTS
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : When this flag is set TRUE, the query of mcusw
                            version of parallel product is supported
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : TRUE/FALSE
     Affected modules     : i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       : Set this flag TRUE, when product has an parallel
                            product( e.g. Vanessa has parallel product 6610 )
</conf> */

#define INFO_SERV_DSP_CORE_FEA     FALSE
/* <conf>
     Name                 : INFO_SERV_DSP_CORE_FEA
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : When this flag is set TRUE, the dsp core server
                            specific messages is used
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : TRUE/FALSE
     Affected modules     : i_proxy.c, i_srvmgr.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       : Set this flag TRUE, when dsp core server is used by
                            product(e.g. if Kenny -> set this TRUE)
</conf> */

#define FEA_INFO_ADSP_FUNC_IF_USED    FALSE
/* <conf>
     Name                 : FEA_INFO_ADSP_FUNC_IF_USED
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : When this flag is set TRUE, the function based
                            interface between ADSP server and MADI task is
                            used
     Specification        : ADSP_srv_specV05.doc
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  : TRUE/FALSE
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       : At least Hitchhiker (R0923) is using this
</conf> */

#define INFO_OSMO_TRACE       DISABLED
/* <conf>
     Name                 : INFO_OSMO_TRACE
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable / disable OSMO traces of Info server
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : ENABLED - enable INFO Server traces via OSMO
     If feature is off    : DISABLED - disable INFO Server traces via OSMO
     Valid range/ values  : ENABLED/DISABLED
     Affected modules     : info_mon.h, several info source files
     Responsible          : Mika Halttunen
     Configuration type   : "R&D feature"
     Other comments       : *** Must be set DISABLED in final products ***
</conf> */

#define FEA_INFO_WT_FUNC       ENABLED
/* <conf>
     Name                 : FEA_INFO_WT_FUNC
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable / disable Warranty functionality of Info
                            server
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : ENABLED - warranty functionality is usable
     If feature is off    : DISABLED - warranty functionality is not usable
     Valid range/ values  : ENABLED/DISABLED
     Affected modules     : i_warr_info_read / write.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       : !!! THIS DEFINITION MUST BE DISABLED until all
                            other components support warranty functionality
                            in Info srv !!!
</conf> */

#define FEA_INFO_UCP_VERSION_QUERY    ENABLED
/* <conf>
     Name                 : FEA_INFO_UCP_VERSION_QUERY
     Parent               :
     Type                 : FLAG_ONOFF
     Description          : Enable / disable support for User Content Package
                            version query.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : ENABLED - UCP version query supported
     If feature is off    : DISABLED - UCP version query not supported
     Valid range/ values  : ENABLED/DISABLED
     Affected modules     : i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       : -
</conf> */

#define INFO_SUPPORTED_PRODUCTS  3 /* check for sales_sw_config */
/* Define product IDs: */
#if INFO_SUPPORTED_PRODUCTS
/* Define one common manufacturer string, which is used for
   both products( base and parallel/s ): */
#define INFO_PROD_MANUFACT       "Nokia"

/* sales_sw_config_begin - supported products information */
/* Aqua DS EU */
#define INFO_PROD_NAME_1         "Nokia 308A"
#define INFO_PROD_CATEGORY_1     "Classic Phone"
#define INFO_PROD_XID_1          {0xB1,0x25,0x00,'N','o','k','i','a',0x20,'3','0','8','A'}
#define INFO_PROD_DEV_NAME_1     "RM-902"
#define INFO_PROD_COMP01_1       "NMPV308A"
#define INFO_PROD_NAME_COMP_1    "Nokia308A"
#define INFO_PROD_NUM_XCVR_ID_1  "308A"
#define INFO_PROD_TYPE_NUM_ID_1  "RM-902"
#define INFO_USB_VENDOR_ID_1     {0x04,0x21}  /* Vendor: Nokia */
#define INFO_USB_MASS_ID_1       {0x05,0xAF}  /* USB mass storage,    0x013A */
#define INFO_USB_NOKIA_ID_1      {0x05,0xB0}  /* PC Suite, 	      0x0139 */
#define INFO_USB_SICD_ID_1       {0x05,0xB1}  /* PictBridge,	      0x013B */
#define INFO_BT_PID_1            {0x01,0x5C}  /* from Fender,	      0x0068 */
#define INFO_USB_RNDIS_ID_1      {0x00,0x66}  /*to be checked*/
#define INFO_USB_NCM_ID_1        {0x03,0xF8}  /*to be checked*/
#define INFO_USB_NSM_ID_1        {0x06,0x7B}  /*Service mode (MTC_NORMAL)*/
#define INFO_USB_NSM_LOCAL_TEST_ID_1        {0x06,0x7C}  /*Service mode (MTC_TEST)*/
#define INFO_SAR_VALUE_1         "0.96 1.41" /*TBD. There is no TA value in SAR Result DB now*/


#if ( INFO_SUPPORTED_PRODUCTS >= 2 )
/* Aqua DS China */
#define INFO_PROD_NAME_2         "Nokia 3080A"
#define INFO_PROD_CATEGORY_2     "Classic Phone"
#define INFO_PROD_XID_2          {0xB1,0x25,0x00,'N','o','k','i','a',0x20,'3','0','8','0','A'}
#define INFO_PROD_DEV_NAME_2     "RM-902"
#define INFO_PROD_COMP01_2       "NMPV3080A"
#define INFO_PROD_NAME_COMP_2    "Nokia3080A"
#define INFO_PROD_NUM_XCVR_ID_2  "3080A"
#define INFO_PROD_TYPE_NUM_ID_2  "RM-902"
#define INFO_USB_VENDOR_ID_2     {0x04,0x21}  /* Vendor: Nokia */
#define INFO_USB_MASS_ID_2       {0x05,0xAF}  /* USB mass storage,    0x013A */
#define INFO_USB_NOKIA_ID_2      {0x05,0xB0}  /* PC Suite, 	      0x0139 */
#define INFO_USB_SICD_ID_2       {0x05,0xB1}  /* PictBridge,	      0x013B */
#define INFO_BT_PID_2            {0x01,0x5C}  /* from Fender,	      0x0068 */
#define INFO_USB_RNDIS_ID_2      {0x00,0x66}  /*to be checked*/
#define INFO_USB_NCM_ID_2        {0x03,0xF8}  /*to be checked*/
#define INFO_USB_NSM_ID_2        {0x06,0x7B}  /*Service mode (MTC_NORMAL)*/
#define INFO_USB_NSM_LOCAL_TEST_ID_2        {0x06,0x7C}  /*Service mode (MTC_TEST)*/
#define INFO_SAR_VALUE_2         "0.96 1.41" /*TBD. There is no TA value in SAR Result DB now*/

#endif /* INFO_SUPPORTED_PRODUCTS = 2 */

#if ( INFO_SUPPORTED_PRODUCTS >= 3 )
/* Aqua DS EU TA Testing */
#define INFO_PROD_NAME_3         "-"
#define INFO_PROD_CATEGORY_3     "Classic Phone"
#define INFO_PROD_XID_3          {0xB1,0x25,0x00,'N','o','k','i','a',0x20,'-'}
#define INFO_PROD_DEV_NAME_3     "RM-902"
#define INFO_PROD_COMP01_3       "-"
#define INFO_PROD_NAME_COMP_3    "-"
#define INFO_PROD_NUM_XCVR_ID_3  "-"
#define INFO_PROD_TYPE_NUM_ID_3  "RM-902"
#define INFO_USB_VENDOR_ID_3     {0x04,0x21}  /* Vendor: Nokia */
#define INFO_USB_MASS_ID_3       {0x05,0xAF}  /* USB mass storage,    0x013A */
#define INFO_USB_NOKIA_ID_3      {0x05,0xB0}  /* PC Suite, 	      0x0139 */
#define INFO_USB_SICD_ID_3       {0x05,0xB1}  /* PictBridge,	      0x013B */
#define INFO_BT_PID_3            {0x01,0x5C}  /* from Fender,	      0x0068 */
#define INFO_USB_RNDIS_ID_3      {0x00,0x66}  /*to be checked*/
#define INFO_USB_NCM_ID_3        {0x03,0xF8}  /*to be checked*/
#define INFO_USB_NSM_ID_3        {0x06,0x7B}  /*Service mode (MTC_NORMAL)*/
#define INFO_USB_NSM_LOCAL_TEST_ID_3        {0x06,0x7C}  /*Service mode (MTC_TEST)*/
#define INFO_SAR_VALUE_3         "0.96 1.41" /*TBD. There is no TA value in SAR Result DB now*/

#endif /* INFO_SUPPORTED_PRODUCTS = 3 */
/* sales_sw_config_end */
#endif /* INFO_SUPPORTED_PRODUCTS */

/* <conf>
     Name                 : INFO_SUPPORTED_PRODUCTS
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Define number of products supported. Default value
                            is 1. Set this value according to amount of parallel
                            products e.g. set value to 2, if one parallel product
                            will be produced and so on.
                            This definition was earlier in info_conf.c
                            named as INFO_NUMBER_OF_PRODUCTS_SUPPORTED.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : -
     If feature is off    : -
     Valid range/ values  : 1 to 8
     Affected modules     : i_product_info.c
     Responsible          : Mika Halttunen
     Configuration type   : parameter
     Other comments       : NOTE: INFO_PROD_NUM_XCVR_ID and INFO_PROD_TYPE_NUM_ID must be set
                                  with different type of data when phone is non-CDMA or CDMA:

                            non-CDMA type phone:
                            #define INFO_PROD_NUM_XCVR_ID_1  "1234" ( num id )
                            #define INFO_PROD_TYPE_NUM_ID_1  "NMM-4" ( type id )

                            CDMA type phone:
                            #define INFO_PROD_NUM_XCVR_ID_1  "NHP-2xx" ( xcvr id )
                            #define INFO_PROD_TYPE_NUM_ID_1  "4321" ( num id )

                            NOTE2: USB IDs must be defined as hex strings:
                            e.g. #define INFO_USB_MASS_ID_x     {0x04,0x29},
                            (granted USB "mass id" for product is 0x429 )

</conf> */


#if ( ICF_WLAN == ON )
#define INFO_FEA_WLAN_SUPPORT
#endif
/* <conf>
     Name                 : INFO_FEA_WLAN_SUPPORT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : Enables reading of WLAN MAC address from
                            NPC( BB5 ) and PMM(DCT4). Also writing of address
                            is enabled for DCT4.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : -
     If feature is off    : -
     Valid range/ values  : -
     Affected modules     : i_srvmgr.c, i_wireless_info.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       : -
</conf> */

/* #define INFO_FEA_WLAN_INFO_PMM_SUPPORT */
/* <conf>
     Name                 : INFO_FEA_WLAN_INFO_PMM_SUPPORT
     Parent               : ICF_WLAN
     Type                 : FLAG_SETTING
     Description          : Enables a possibility to write WLAN ID to pmm. This is for debug purposes before the WLAN MAC is
                            flashed to the phone in the production.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_wireless_info.c
     Responsible          : Jukka Pussinen
     Configuration type   :
     Other comments       : This feature works only in the R&D phones.
</conf> */

#if ( ICF_WLAN == ON )
#define INFO_FEA_HARDCODED_WLAN_MAC
#define INFO_WLAN_MAC_ADDRESS {0x20, 0x93, 0x38, 0x39, 0x7B, 0xA8}
#endif
/*#endif*/
/* <conf>
     Name                 : INFO_FEA_HARDCODED_WLAN_MAC
     Parent               : ICF_WLAN
     Type                 : FLAG_SETTING
     Description          : Take hard coded WLAN MAC address in use. This is for debug purposes before the WLAN MAC is flashed to the
                            phone in the production.
    Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_wireless_info.c
     Responsible          :
     Configuration type   :
     Other comments       : This feature works only in the R&D phones.
                            The hardcoded value is returned only if the read from the certificate or the read from the
                            PMM (see INFO_FEA_WLAN_INFO_PMM_SUPPORT) fails.
</conf> */

/* #define INFO_PP_FULL_FEATURE_FEA */
/* <conf>
     Name                 : INFO_PP_FULL_FEATURE_FEA
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : disable/enable  dynamic pp feature.
     Specification        :
     Restrictions         : If not defined dynamic product profiling feature
                            is disabled. This will affect classified permanent
                            memory allocation. If pm classified is already
                            programmed with INFO server pp data prior to
                            disabling this feature pm classified area must be
                            erased.
     Associated
     features/ parameters :
     If feature is on     : dynamic product profiling is on
     If feature is off    : dynamic product profiling is off
     Valid range/ values  : Comment out flag to turn ON dynamic pp.
                            Comment flag to turn OFF dynamic pp.
     Affected modules     : i_pp_data_def.h
                            i_pp.h
                            i_pp_if.c
     Responsible          : Mika Halttunen
     Configuration type   : feature, system definition
     Other comments       :
</conf> */

#if ICF_NO_PMM_CLASS
#define INFO_GRP_TYPE_PROT
#endif
/* <conf>
     Name                 : INFO_GRP_TYPE_PROT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : Define PMM_GROUP_INFO type to PMM_PROT.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : PMM_GROUP_INFO type is PMM_PROT
     If feature is off    : PMM_GROUP_INFO type is PMM_CLASS
     Valid range/ values  :
     Affected modules     : info_pmm.h
     Responsible          : Mika Halttunen
     Configuration type   : Architecture change
     Other comments       :
</conf> */



/* #define INFO_FEA_IP_PASSTHROUGH */
/* <conf>
     Name                 : INFO_FEA_IP_PASSTHROUGH
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : To obtain functionality two MAC addresses from
                            certificate(NPC) is needed for
                            "IP pass through sw" on APE side.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : Reading is enabled
     If feature is off    : Reading is disabled
     Valid range/ values  :
     Affected modules     : i_srvmgr.c, i_wireless_info.c
     Responsible          : Mika Halttunen
     Configuration type   : Feature
     Other comments       :
</conf> */

/* #define INFO_SV_IN_SOS */
/* <conf>
     Name                 : INFO_SV_IN_SOS
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : Define if SV digits locate in SOS side.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     : SV is read from SOS side
     If feature is off    : SV is read from ISA side
     Valid range/ values  :
     Affected modules     : i_srvmgr.c, i_proxy.c, i_imei.c
     Responsible          : Mika Halttunen
     Configuration type   : System
     Other comments       :
</conf> */

/* #define INFO_CCC_ID_LENGTH 16 */
/* <conf>
     Name                 : INFO_CCC_ID_LENGTH
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this Info server supports 15 bytes (+terminating null)
                            PRODUCT_CODE, MODULE_CODE and BASIC_PRODUCT_CODE. When not defined or it differs from 16
                            length is assumed to 7 + terminator
     Specification        :
     Restrictions         : from TB11.2 onwards this should be defined to 16
     Associated
     features/ parameters :
     If feature is on     : -
     If feature is off    : -
     Valid range/ values  : -
     Affected modules     : i_srvmgr.c, i_prdifnf.c, info_pmm.h
     Responsible          : Jukka Pussinen
     Configuration type   : feature
     Other comments       : -
</conf> */

/* #define FEA_INFO_ADDR_ON_BT_CHIP */
/* <conf>
     Name                 : FEA_INFO_ADDR_ON_BT_CHIP
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this Info server support
                            pre-programmed BT address reading from BT chip.
     Specification        :
     Restrictions         : Define only if BT chip can store address on
                            its own memory(at moment this is true with
                            chips produced by TI - chip TI BFR6150 ?)
     Associated
     features/ parameters :
     If feature is on     : -
     If feature is off    : -
     Valid range/ values  : -
     Affected modules     : i_srvmgr.c, i_wireless_info.c, i_proxy.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       : -
</conf> */

/* #define INFO_FEA_BT_ID_PMM_SUPPORT */
/* <conf>
     Name                 : INFO_FEA_BT_ID_PMM_SUPPORT
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Enables a possibility to write BT ID to pmm. This is for debug purposes before the BT ID is
                            flashed to the phone in the production.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_wireless_info.c
     Responsible          : Jukka Pussinen
     Configuration type   :
     Other comments       : This feature works only in the R&D phones.
</conf> */


#if defined(SP_UI) && defined(BUILD_PRODUCTION)
#define INFO_PP_FLAG_COUNT_IN_NVD  0
#else
#define INFO_PP_FLAG_COUNT_IN_NVD  200
#endif

/* <conf>
     Name                 : INFO_PP_FLAG_COUNT_IN_NVD
     Parent               :
     Type                 : FLAG_SETTING
     Description          : Add value for amount of PP flags need to be
                            stored to NVD. This definition determines how
                            much memory is reserved for record to store
                            written PP data. Each PP flag data takes 4 bytes
                            space: 2 bytes for ID, 2 bytes for value.
                            If PP data write request contain existing values
                            for certain PP flags, Info server do not store
                            such PP flag values to nvd, only values which
                            variate from existing values are stored.

                            NOTE: Amount of secure PP flags( in CCC ) must be
                            taken account when setting value for this flag.
                            Currently known secure PP flags are
                            1) INFO_PP_TRACFONE,
                            2) INFO_PP_GPRS_MULTISLOT_CLASS,
                            3) INFO_PP_EGPRS_MULTISLOT_CLASS


     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    : If value is zero, none of PP data in write req is
                            not stored.
     Valid range/ values  :
     Affected modules     : i_pp_if.c, i_pp.h
     Responsible          : Mika Halttunen
     Configuration type   : system
     Other comments       : If value is 4, in total 4 PP flags can be written.
</conf> */
/* #define SECURE_PP_DATA_FEA */
/* <conf>
     Name                 : SECURE_PP_DATA_FEA
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : If defined PP data is read from CCC. Note CCC with
                            PP data written to it is required !!!
     Specification        :
     Restrictions         :
     Associated
     features/ parameters : SECURE_PP_DATA_FEA
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_pp_if.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_CONTENT_VERSIONS_QUERY */

/* <conf>
     Name                 : INFO_CONTENT_VERSIONS_QUERY
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this UDA, HDD and MC Content
                            Versions can be queried.
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         : For APE side versions query ONLY !!!
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_proxy.c, i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_GAZOO_VERSION_QUERY */

/* <conf>
     Name                 : INFO_GAZOO_VERSION_QUERY
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this Gazoo version query is supported.
                            Gazoo is Mixed Signal ASIC.
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_CWS_CHIP_ID_SUPPORT */

/* <conf>
     Name                 : INFO_CWS_CHIP_ID_SUPPORT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the CWS chip ID query is enabled.
                            CWS = Complementary Wireless Solution (e.g. BOB and TOM).
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

#if defined( ICF_EXTERNAL_DRIVER_SUPPORT ) && (ICF_EXTERNAL_DRIVER_SUPPORT != OFF)
/* #define INFO_HW_DRIVER_VERSION_SUPPORT */
#endif

/* <conf>
     Name                 : INFO_HW_DRIVER_VERSION_SUPPORT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the HW driver version ID query is enabled.
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c
     Responsible          : Marko Kaapu
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_FEA_PROXIMITY_SENSOR_ID */

/* <conf>
     Name                 : INFO_FEA_PROXIMITY_SENSOR_ID
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the proximity sensor ID read is enabled.
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c, i_proxy.c
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

#define INFO_FEA_TOUCH_ID

/* <conf>
     Name                 : INFO_FEA_TOUCH_ID
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the touch ID read is enabled.
     Specification        : i_info_m.html(INFO_VERSION_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c, i_proxy.c
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_STARTUP_REASON_READ_SUPPORT */

/* <conf>
     Name                 : INFO_STARTUP_REASON_READ_SUPPORT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the start-up reason read feature enabled.
     Specification        : i_info_m.html(INFO_STARTUP_REASON_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_product_info.c/.h
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_RESET_REASON_READ_SUPPORT */

/* <conf>
     Name                 : INFO_RESET_REASON_READ_SUPPORT
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the reset reason read feature enabled.
     Specification        : i_info_m.html(INFO_RESET_REASON_READ_REQ/RESP)
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_product_info.c/.h
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_FEA_INFORM_MODEM_ABOUT_ANTENNA_STATUS */

/* <conf>
     Name                 : INFO_FEA_INFORM_MODEM_ABOUT_ANTENNA_STATUS
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this flag the inform modem about antenna status feature is enabled.
     Specification        :
     Restrictions         :
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_srvmgr.c
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define INFO_ROFS_VERSION_QUERY */
/* <conf>
     Name                 : INFO_ROFS_VERSION_QUERY
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : By defining this Read Only File System version
                            is possible to query.

     Specification        :
     Restrictions         : Define only for SOS phones.
     Associated
     features/ parameters :
     If feature is on     :
     If feature is off    :
     Valid range/ values  :
     Affected modules     : i_versn.c, i_proxy.c
     Responsible          : Mika Halttunen
     Configuration type   : feature
     Other comments       :
</conf> */

/* #define FEA_INFO_PRODUCT_CODE_FROM_CCC */
/* <conf>
     Name                 : FEA_INFO_PRODUCT_CODE_FROM_CCC
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : If this flag is defined and the value of the
                            ICF_RF_BAND_VARIABILITY is ICF_CS_IN_CCC, the
                            product code will be read from the CCC in non-DCT4
                            products.
     Specification        :
     Restrictions         : Makes sense only in non-DCT4 products and if the
                            ICF_RF_BAND_VARIABILITY is ICF_CS_IN_CCC.
     Associated
     features/ parameters :
     If feature is on     : The product code is read from CCC
     If feature is off    : The product code is read from NVD
     Valid range/ values  : -
     Affected modules     : i_srvmgr.c, i_proxy.c, i_prdinf.c
     Responsible          : Zoran Stevanovic
     Configuration type   : feature
     Other comments       : -
</conf> */

/* #define INFO_FEA_BOM_ID */
/* <conf>
     Name                 : INFO_FEA_BOM_ID
     Parent               :
     Type                 : FLAG_DEFINE
     Description          : If this flag is defined the BOM ID read feature is enabled.
     Specification        :
     Restrictions         : Works only with Santiago HW.
     Associated
     features/ parameters :
     If feature is on     : The BOM ID can be read
     If feature is off    : The BOM ID can not be read
     Valid range/ values  : -
     Affected modules     : i_srvmgr.c, i_proxy.c, i_versn.c
     Responsible          : Olli Porola
     Configuration type   : feature
     Other comments       : -
</conf> */


#endif /* INFO_CONF_H */

/* End of File */
