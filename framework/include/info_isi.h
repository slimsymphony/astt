/*
NOKIA                                                             CONFIDENTIAL
Tampere
ENO SW / PTSW
Olli Porola



                  info_isi.h
                  --------------------------------
                  SW Include Document - ANSI C/C++



Continuus Ref:
--------------
database:        ou1gif

project path:    global_interface/ISI/Core

name:            info_isi.h

version:         009.000

type:            incl

instance:        ou_pcms#1


ISI header file for Info Server

Current   ISI Version : 009.000
Supported ISI Versions: 001.000, 001.027, 002.000, 002.001, 002.002, 002.004, 
                        002.005, 003.000, 003.001, 004.000, 004.002, 004.003, 
                        004.004, 004.005, 004.006, 004.007, 004.008, 004.009, 
                        004.010, 004.011, 004.012, 004.013, 004.014, 004.015, 
                        004.016, 004.017, 005.000, 005.001, 005.002, 005.003, 
                        005.004, 005.005, 005.007, 005.008, 005.009, 005.010, 
                        005.011, 005.012, 005.013, 006.000, 006.001, 007.000, 
                        008.000, 008.001, 008.002, 008.003, 008.004, 008.005, 
                        008.006, 008.007, 008.008, 008.009, 008.010, 008.011, 
                        008.012, 008.013, 008.014, 008.015, 008.016, 008.017, 
                        008.018, 008.019, 008.020, 008.021, 008.022, 008.023, 
                        008.024, 008.025, 008.026, 008.027, 008.028, 009.000

Generated with autogen version 12w33 on 28-Nov-2012 09:49:20
DO NOT EDIT - changes will be lost at next autogeneration

Copyright (c) Nokia Corporation. All rights reserved.


ISI version change history

Version     : 009.000    NON-DRAFT   17-Nov-2012    Lin Tarzan
Reason      : Accept360 Story
Reference   : 3372564
Description : Added Subblock INFO_SB_CONTENT_FOTAID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_MCUSW_FOTAID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_ROFS_FOTAID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_SW_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CONTENT_FOTAID
              Added Subblock INFO_SB_MCUSW_FOTAID
              Added Subblock INFO_SB_ROFS_FOTAID
              Added Subblock INFO_SB_SW_VERSION
              Added Entry INFO_ROFS_FOTAID to INFO_VERSION_TARGETS
              Added Entry INFO_CONTENT_FOTAID to INFO_VERSION_TARGETS_2
              Added Entry INFO_MCUSW_FOTAID to INFO_VERSION_TARGETS_2
              Added Entry INFO_SW_VERSION to INFO_VERSION_TARGETS_2
              Add new sw version block.

Version     : 008.028    NON-DRAFT   26-Sep-2012    Zhou Ningbo
Reason      : Accept360 Story
Reference   : 3372564
Description : Added Subblock INFO_SB_USB_NSM_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_NSM_LOCAL_TEST_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_NSM_ID
              Added Subblock INFO_SB_USB_NSM_LOCAL_TEST_ID
              Added Entry INFO_USB_NSM_ID to INFO_PRODUCT_INFO_TARGET
              Added Entry INFO_USB_NSM_LOCAL_TEST_ID to INFO_PRODUCT_INFO_TARGET
              Implement 2 PIDs for USB service mode.

Version     : 008.027    NON-DRAFT   07-May-2012    Olli Porola
Reason      : Accept360 Story
Reference   : 3051708
Description : Added Subblock INFO_SB_SIM_SLOTS to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_SIM_SLOTS
              Added Entry INFO_SIM_SLOTS to INFO_PRODUCT_INFO_TARGET
              Number of SIM slots product info added.

Version     : 008.026    NON-DRAFT   15-Dec-2011    Jukka Pussinen
Reason      : Accept360 Story
Reference   : 2227326
Description : Discontinued Subblock INFO_SB_ADSP_DEVICE_ID in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_ADSP_REVISION_ID in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_ADSP_VERSION in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_APE_CUI_LCD_VERSION in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_HW_VER in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_SW_VER in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_APE_IPDC_VERSION in INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CHARGER_DET to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_EM_ASIC to INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_FLIP_MCUSW_VERSION in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_GAZOO in INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_GPS to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_MEMORY to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_PMU to INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_RAP_VERSION in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_RETU_VER in INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_SIM_SWITCH to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_SYSTEM_ASIC to INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_TAHVO_VER in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_UEM_VERSION in INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_UPP_VERSION in INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_WLAN to INFO_VERSION_READ_RESP
              Discontinued Subblock INFO_SB_ADSP_DEVICE_ID
              Discontinued Subblock INFO_SB_ADSP_REVISION_ID
              Discontinued Subblock INFO_SB_ADSP_VERSION
              Discontinued Subblock INFO_SB_APE_CUI_LCD_VERSION
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_HW_VER
              Discontinued Subblock INFO_SB_APE_DVB_H_RX_SW_VER
              Discontinued Subblock INFO_SB_APE_IPDC_VERSION
              Added Subblock INFO_SB_CHARGER_DET
              Added Subblock INFO_SB_EM_ASIC
              Discontinued Subblock INFO_SB_FLIP_MCUSW_VERSION
              Discontinued Subblock INFO_SB_GAZOO
              Added Subblock INFO_SB_GPS
              Added Subblock INFO_SB_MEMORY
              Added Subblock INFO_SB_PMU
              Discontinued Subblock INFO_SB_RAP_VERSION
              Discontinued Subblock INFO_SB_RETU_VER
              Added Subblock INFO_SB_SIM_SWITCH
              Added Subblock INFO_SB_SYSTEM_ASIC
              Discontinued Subblock INFO_SB_TAHVO_VER
              Discontinued Subblock INFO_SB_UEM_VERSION
              Discontinued Subblock INFO_SB_UPP_VERSION
              Added Subblock INFO_SB_WLAN
              Discontinued Constant table INFO_RAP_TYPE
              Changed Bitmask table INFO_VERSION_TARGETS
              Changed Bitmask table INFO_VERSION_TARGETS_2
              Added Constant INFO_SB_EM_ASIC_LEN
              Added Constant INFO_SB_MEMORY_STR_LEN
              Discontinued Constant INFO_SB_RAP_LEN
              Discontinued Constant INFO_SB_RETU_LEN
              Added Constant INFO_SB_SYSTEM_ASIC_LEN
              Discontinued Constant INFO_SB_TAHVO_LEN
              Quark SCR: Study info server coverage with Electrical version
              numbers in Chipset

Version     : 008.025    NON-DRAFT   20-May-2011    Olli Porola
Reason      : Accept360 Story
Reference   : 968910
Description : Unicus: NokiaCode length change from 7 characters to 9-15

Version     : 008.024    NON-DRAFT   24-Nov-2010    Olli Porola
Reason      : Accept360 Story
Reference   : 985185
Description : Added Message INFO_LIFETIME_READ_REQ
              Added Message INFO_LIFETIME_READ_RESP
              Added Subblock INFO_SB_LIFETIME
              Added Subblock INFO_SB_REBOOTS
              Added Subblock INFO_SB_UPDATES
              Added Bitmask table INFO_LIFETIME_TARGET
              Meego/TB9.2: creation of ISI for lifetimer Message &
              documentation +relasing to TB9.2 for review

Version     : 008.023    NON-DRAFT   05-Oct-2010    Olli Porola
Reason      : Accept360 Story
Reference   : 689029
Description : Added Subblock INFO_SB_MCU_SPEED_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_MCU_SPEED_VERSION
              Added Constant table INFO_MCU_SPEED
              Added Entry INFO_MCU_SPEED_VERSION to INFO_VERSION_TARGETS_2
              CS79u: Production Testing:Test to separate speed sorted
              RapuYama components

Version     : 008.022    NON-DRAFT   09-Sep-2010    Marko Kaapu
Reason      : Accept360 Task
Reference   : 734696
Description : Added Subblock INFO_SB_HW_DRIVER_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_HW_DRIVER_VERSION
              Added Entry INFO_HW_DRIVER_VERSION to INFO_VERSION_TARGETS_2
              HW driver version:Specify info ISI interface

Version     : 008.021    NON-DRAFT   01-Jyl-2010    Olli Porola
Reason      : SUB
Reference   : 417-68132.
Description : Fix task for this: Info server: ISI update, Possibility to read
              FWID with PCSW.

Version     : 008.020    NON-DRAFT   22-Apr-2010    Olli Porola
Reason      : SUB
Reference   : 417-71875.
Description : Added Subblock INFO_SB_DBI_ID to INFO_VERSION_READ_RESP
              Fix task for this: CS79: Info server ISI interface to read DBI
              circuit data, ICPR9.2.

Version     : 008.019    NON-DRAFT   26-May-2010    Olli Porola
Reason      : SUB
Reference   : 417-73442. SWAM CR: OP10052645942
Description : Added Subblock INFO_SB_MAGNETOMETER_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_MAGNETOMETER_ID
              Added Constant table INFO_COMPASS_3D_HW_TYPE
              Magnetometer ID read in HW 61 - info server ISI interface
              support.

Version     : 008.018    NON-DRAFT   12-May-2010    Olli Porola
Reason      : SUB
Reference   : 417-73022. SWAM CR: OP10051246406
Description : Added Message INFO_SERIAL_NUMBER_WRITE_REQ
              Added Message INFO_SERIAL_NUMBER_WRITE_RESP
              Info server ISI interface support to writing of battery serial
              number.

Version     : 008.017    NON-DRAFT   11-May-2010    Olli Porola
Reason      : SUB
Reference   : 417-71718. SWAM CR: OP10042247110
Description : Added Subblock INFO_SB_USB_NCM_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_NCM_ID
              Added Entry INFO_USB_NCM_ID to INFO_PRODUCT_INFO_TARGET
              Info server: ISI interface support for reading USB NCM for S40.

Version     : 008.016    NON-DRAFT   22-Apr-2010    Olli Porola
Reason      : SUB
Reference   : 417-71875. SWAM CR: OP10042244370
Description : Added Subblock INFO_SB_DBI_ID
              Added Constant table INFO_DBI_BATTERY_CHEMISTRY
              Added Constant table INFO_DBI_BATTERY_VENDOR
              Added Entry INFO_DBI_ID to INFO_VERSION_TARGETS_2
              CS79: Info server ISI interface to read DBI circuit data,
              ICPR9.2.

Version     : 008.015    NON-DRAFT   26-Mar-2010    Olli Porola
Reason      : SUB
Reference   : 417-70562. SWAM CR: OP10032632855
Description : Added Entry INFO_MAGNETOMETER_ID to INFO_VERSION_TARGETS_2
              Info server: magnetometer ID support (ISI interface) in
              Peripherals in HW 61, ICPR9.2.

Version     : 008.014    NON-DRAFT   2-Mar-2010     Olli Porola
Reason      : SUB
Reference   : 417-68132. SWAM CR: OP10030242397
Description : Info server: ISI update, Possibility to read FWID with PCSW.

Version     : 008.013    NON-DRAFT   1-Mar-2010     Olli Porola
Reason      : SUB
Reference   : 417-69280. SWAM CR: OP10030234354
Description : Added Subblock INFO_SB_SN_BATTERY to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_BATTERY
              Added Entry INFO_SN_BATTERY to INFO_SN_TARGET_IDENTIFIER
              Added Constant INFO_SB_SN_BATTERY_DATA_LEN
              ISI interface support to write/read battery serial number.

Version     : 008.012    NON-DRAFT   1-Feb-2010     Olli Porola
Reason      : SUB
Reference   : 417-67740. SWAM CR: OP10020149002
Description : Added Subblock INFO_SB_NFC_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_NFC_VERSION
              Added Entry INFO_NFC_VERSION to INFO_VERSION_TARGETS_2
              Info server: NFC1.0D:Info ISI Interface for NFC module's HW ID.
              + Moved proximity sensor sub block to the shared header.

Version     : 008.011    NON-DRAFT   15-Jan-2010    Olli Porola
Reason      : SUB
Reference   : 417-65333. SWAM CR: OP10011344592
Description : Added Subblock INFO_SB_SN_IMEI2_PLAIN to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_IMEI2_SPARE_TO_NET to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_IMEI2_SV_TO_NET to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_IMEI2_PLAIN
              Added Subblock INFO_SB_SN_IMEI2_SPARE_TO_NET
              Added Subblock INFO_SB_SN_IMEI2_SV_TO_NET
              Added Entry INFO_SN_IMEI2_PLAIN to INFO_SN_TARGET_IDENTIFIER
              Added Entry INFO_SN_IMEI2_SPARE_TO_NET to INFO_SN_TARGET_IDENTIFIER
              Added Entry INFO_SN_IMEI2_SV_TO_NET to INFO_SN_TARGET_IDENTIFIER
              Added Constant INFO_SB_SN_IMEI2_PLAIN_STR_LEN
              Added Constant INFO_SB_SN_IMEI2_SPARE_TO_NET_STR_LEN
              Added Constant INFO_SB_SN_IMEI2_SV_TO_NET_STR_LEN
              Info server: ISI specification for Dual SIM-Secondary IMEI

Version     : 008.010    NON-DRAFT   10-Dec-2009    Olli Porola
Reason      : SUB
Reference   : 417-63680. SWAM CR: OP09121044616
Description : Added Message INFO_RESET_REASON_READ_REQ
              Added Message INFO_RESET_REASON_READ_RESP
              Added Constant table INFO_RESET_REASON
              Info server ISI: delivery of reset reason to tester (MCL
              &ICPR9.2)

Version     : 008.009    NON-DRAFT   01-Oct-2009    Olli Porola
Reason      : SUB
Reference   : 417-57872. SWAM CR: OP09100149581
Description : Added Subblock INFO_SB_PROXIMITY_SENSOR_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_PROXIMITY_SENSOR_ID
              Added Entry INFO_PROXIMITY_SENSOR_ID to INFO_VERSION_TARGETS_2
              Info server: ISI interface update to support proximity sensorx

Version     : 008.008    NON-DRAFT   10-Aug-2009    Olli Porola
Reason      : SUB
Reference   : 417-52191. SWAM CR: OP09082841753
Description : Added Message INFO_STARTUP_REASON_READ_REQ
              Added Message INFO_STARTUP_REASON_READ_RESP
              Added Bitmask table INFO_STARTUP_REASON
              ISA info server: wake-up reason read to production.

Version     : 008.007    NON-DRAFT   10-Aug-2009    Olli Porola
Reason      : SUB
Reference   : 417-29283. SWAM CR: OP09081057475
Description : Added Subblock INFO_SB_TOUCH_SENSOR_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_TOUCH_SENSOR_ID
              Added Entry INFO_TOUCH_SENSOR_ID to INFO_VERSION_TARGETS_2
              PTSW Info: Capacitive Touch Sensor Prof. Test & Custom Care
              supp. - ID readings

Version     : 008.006    NON-DRAFT   23-Jun-2009    Olli Porola
Reason      : SUB
Reference   : 417-42786. SWAM CR: OP09062341721
Description : Added Subblock INFO_SB_CWS_CHIP_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CWS_CHIP_ID
              Added Entry INFO_CWS_CHIP_ID to INFO_VERSION_TARGETS_2
              PTSW ISA info server: support for TOM1.0D: Version ID reading

Version     : 008.005    NON-DRAFT   27-Jan-2009    Olli Porola
Reason      : SUB
Reference   : 417-31612, 417-30624
Description : Added Subblock INFO_SB_ACCELEROMETER_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_NAVISCROLL_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_ACCELEROMETER_VERSION
              Added Subblock INFO_SB_NAVISCROLL_VERSION
              Added Entry INFO_ACCELEROMETER_VERSION to INFO_VERSION_TARGETS_2
              Added Entry INFO_NAVISCROLL_VERSION to INFO_VERSION_TARGETS_2
              PTSW info: Merlin PR2: API for Naviscroll firmware version.
              PTSW Info: CTS 71 : Production test: Accelerometer version info
              reading in production.

Version     : 008.004    NON-DRAFT   31-Oct-2008    Olli Porola
Reason      : SUB
Reference   : 417-24223
Description : Added Subblock INFO_SB_BOM_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_BOM_ID
              Added Entry INFO_BOM_ID_VERSION to INFO_VERSION_TARGETS_2
              PTSW INFO: BCOM B1: BOM Detection

Version     : 008.003    NON-DRAFT   17-Mar-2008    Winfried Gamroth
Reason      : RM-RIM 010-30180
Reference   : ADB for SWAM WG08031741277
Description : Added Entry INFO_EUTRAN_POS to INFO_BAND_POS
              Added Bitmask table INFO_EUTRAN_BAND
              Added Entry INFO_RAT_EUTRAN to INFO_RAT_ID
              EUTRAN band information to be available from INFO server.

Version     : 008.002    NON-DRAFT   14-Feb-2008    Winfried Gamroth
Reason      : RM-RIM 010-28684
Reference   : ADB for SWAM WG08021342778
Description : Added Subblock INFO_SB_USB_RNDIS_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_RNDIS_ID
              Added Entry INFO_USB_RNDIS_ID to INFO_PRODUCT_INFO_TARGET
              Support for USB RNDIS added.

Version     : 008.001    NON-DRAFT   14-Nov-2007    Zoran Stevanovic
Reason      : RM-RIM 414-2275, 414-3045
Reference   : ADB for SWAM ZS07111540118.
Description : Added Entry INFO_WCDMA_RX_DIV_POS to INFO_BAND_POS
              Added Entry INFO_RAT_WCDMA_RX_DIV to INFO_RAT_ID
              Added Entry INFO_WCDMA_FDD_BAND7 to INFO_WCDMA_BAND
              Added Entry INFO_WCDMA_FDD_BAND8 to INFO_WCDMA_BAND
              Added Entry INFO_WCDMA_FDD_BAND9 to INFO_WCDMA_BAND
              Added Bitmask table INFO_WCDMA_RX_DIV_BAND
              WCDMA bands 7-9 activated. New RAT added to support WCDMA RX
              diversity. Some obsolete macros replaced.

Version     : 008.000    NON-DRAFT   11-Sep-2007    Zoran Stevanovic
Reason      : RM-RIM 404-2088
Reference   : ADB for SWAM ZS07091145641.
Description : Changed Sequence CS_TYPE_SEC
              Changed Constant INFO_SW_ID_LEN
              The definition of the CS_TYPE_SEC modified not to include the
              RSA signature, i.e. rolled back to the one before the version
              007.000.

Version     : 007.000    NON-DRAFT   03-Apr-2007    Zoran Stevanovic
Reason      : RM-RIM 407-6
Reference   : ADB for SWAM ZS07040438377.
Description : Changed Sequence CS_TYPE_SEC
              Changed Constant INFO_SW_ID_LEN
              The definition of the CS_TYPE_SEC modified to include the RSA
              signature.

Version     : 006.001    NON-DRAFT   28-Feb-2007    Mika Halttunen
Reason      : SCO / inspection
Reference   : LN WP-PT-MS RM-RIM 010-33211, LN SWAM ADB MH07022841663.
Description : Added Subblock INFO_SB_ROFS_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_ROFS_VERSION
              Added Constant table INFO_ROFS_ID
              Added Entry INFO_ROFS_VERSIONS to INFO_VERSION_TARGETS_2

Version     : 006.000    NON-DRAFT   16-Oct-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06101642986.
Description : AEM version query support removed.

Version     : 005.013    NON-DRAFT   12-Oct-2006    Mika Halttunen
Reason      : SCO
Reference   : see info_shared_isi_m.h v005.013.
Description : Added Subblock INFO_SB_APE_CUI_LCD_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_IPDC_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_CUI_LCD_VERSION
              Added Subblock INFO_SB_APE_IPDC_VERSION
              Added Entry INFO_APE_CUI_LCD_VERSION to INFO_VERSION_TARGETS_2
              Added Entry INFO_APE_IPDC_VERSION to INFO_VERSION_TARGETS_2
              Moved several sub block defintions to info_shared_isi_m.h.
              INFO_SB_APE_CUI_LCD_VERSION and INFO_SB_APE_CUI_LCD_VERSION are
              renamed from they original name in einfo_isi_m.h.

Version     : 005.012    NON-DRAFT   02-Oct-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06100245043.
Description : Added Subblock INFO_SB_GAZOO to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_GAZOO
              Added Entry INFO_GAZOO to INFO_VERSION_TARGETS

Version     : 005.011    NON-DRAFT   01-Sep-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06090454347.
Description : Comment corrections & additions to INFO_SB_PRODUCTION_SN,
              INFO_SB_LONG_PRODUCTION_SN, INFO_PROD_INFO_READ_REQ and
              INFO_PROD_INFO_WRITE_REQ.

Version     : 005.010    NON-DRAFT   28-Jun-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06062862043.
Description : Added Subblock INFO_SB_CONTENT_VERSIONS to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CONTENT_VERSIONS
              Added Constant table INFO_CONTENT_LOCATION
              Added Entry INFO_CONTENT_VERSIONS to INFO_VERSION_TARGETS_2

Version     : 005.009    NON-DRAFT   15-May-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06052344843, PCP Errors AT06031055080.
Description : MSG SPEC: INFO_SB_SN_MEID_PLAIN description corrected.

Version     : 005.008    NON-DRAFT   18-Apr-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06022337728, WP-PT-MS RM-RIM 010-22223.
Description : Added Subblock INFO_SB_CAMERA_DETAILED_VERSION_INFO to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CAMERA_DETAILED_VERSION_INFO
              Added Entry INFO_CAMERA2 to INFO_VERSION_TARGETS_2

Version     : 005.007    NON-DRAFT   28-Feb-2006    Juho Heikkilä
Reason      : Inspection
Reference   : LN ADB SWAM JH06022837365, WP-PT-MS RM-RIM 010-22536.
Description : Added Subblock INFO_SB_BT_ID_PLAIN to INFO_BT_ID_WRITE_REQ

Version     : 005.005    NON-DRAFT   19-Jan-2006    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH06011950424, WP-PT-MS RM-RIM 009-19253.
Description : Added Subblock INFO_SB_PRODUCT_VARIANT_NUMBER to INFO_PROD_INFO_WRITE_REQ
              Added Subblock INFO_SB_PRODUCT_VARIANT_NUMBER

Version     : 005.004    NON-DRAFT   02-Nov-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05110257369, WP-PT-MS RM-RIM 009-20804,
              009-22054.
Description : Added Subblock INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_DVB_H_RX_HW_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_DVB_H_RX_SW_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER
              Added Subblock INFO_SB_APE_DVB_H_RX_HW_VER
              Added Subblock INFO_SB_APE_DVB_H_RX_SW_VER
              Added Entry INFO_APE_DVB_H_RX_BOOTLOADER_VER to INFO_VERSION_TARGETS_2
              Added Entry INFO_APE_DVB_H_RX_HW_VER to INFO_VERSION_TARGETS_2
              Added Entry INFO_APE_DVB_H_RX_SW_VER to INFO_VERSION_TARGETS_2

Version     : 005.003    NON-DRAFT   24-Oct-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05102438391, WP-PT-MS RM-RIM 009-18943.
Description : Added Entry INFO_WT_SN_TYPE_MEID to INFO_WT_SN

Version     : 005.002    NON-DRAFT   17-Oct-2005    Mika Halttunen
Reason      : Inspection, comments
Reference   : LN ADB SWAM MH05101255652, KM05101444837, WP RM-RIM 009-21354.
Description : Added Subblock INFO_SB_BT_PID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_BT_PID
              Added Entry INFO_BT_PID to INFO_PRODUCT_INFO_TARGET
              KM05101444837: Sequence INFO_USB_IDS is not used anymore ->
              defined it obsolete.

Version     : 005.001    NON-DRAFT   06-Oct-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05100540860, WP RM-RIM 009-20651.
Description : Added Message INFO_PRODUCT_RAT_BAND_READ_REQ
              Added Message INFO_PRODUCT_RAT_BAND_READ_RESP
              Added Message INFO_PRODUCT_RAT_BAND_WRITE_REQ
              Added Message INFO_PRODUCT_RAT_BAND_WRITE_RESP
              Added Subblock INFO_SB_RAT_BAND_INFO
              Added Constant table INFO_BAND_POS
              Added Bitmask table INFO_GSM_BAND
              Added Bitmask table INFO_RAT_ID
              Added Bitmask table INFO_WCDMA_BAND
              Added Constant INFO_BAND_ID_TABLE_MAX_CNT

Version     : 005.000    NON-DRAFT   14-Sep-2005    Mika Halttunen
Reason      : Inspection, Comment
Reference   : LN ADB SWAM MH05090149734, KM05091353162, WP RM-RIM 009-20425,
              009-20458.
Description : Changed Entry INFO_TYPE_CS_CDMA2100 in INFO_CS_TYPE_1
              Added Entry INFO_TYPE_CS_PREPAID to INFO_CS_TYPE_1
              Added Entry INFO_TYPE_CS_RUIM to INFO_CS_TYPE_1

Version     : 004.017    NON-DRAFT   04-May-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05051041809
Description : Added Message INFO_PP_DATA_IND
              Added Message INFO_PP_DATA_READ_REQ
              Added Message INFO_PP_DATA_READ_RESP
              Added Message INFO_PP_DATA_WRITE_REQ
              Added Message INFO_PP_DATA_WRITE_RESP
              Added Subblock INFO_SB_PP_DATA
              Added messages INFO_PP_DATA_READ_REQ/RESP,
              INFO_PP_DATA_WRITE_REQ/RESP, INFO_PP_DATA_IND and sub block
              INFO_SB_PP_DATA.

Version     : 004.016    NON-DRAFT   02-May-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05013144180
Description : Added Message INFO_WLAN_INFO_WRITE_REQ
              Added Message INFO_WLAN_INFO_WRITE_RESP
              Added few comments +  INFO_WLAN_INFO_WRITE_REQ/RESP.

Version     : 004.015    NON-DRAFT   23-Mar-2005    Mika Halttunen
Reason      : Inspection
Reference   : LN ADB SWAM MH05032345918
Description : Added Message INFO_IP_PASSTHROUGH_READ_REQ
              Added Message INFO_IP_PASSTHROUGH_READ_RESP
              Added Sequence INFO_IPP_MACS
              Added msgs INFO_IP_PASSTHROUGH_READ_REQ/RESP.

Version     : 004.014    NON-DRAFT   25-Feb-2005    Mika Halttunen
Reason      : Inspection & comments
Reference   : LN ADB SWAM MH05030154628, LN WP RM-RIM 010-9887
Description : Added Subblock INFO_SB_USB_SICD_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_SICD_ID
              Added Entry INFO_USB_SICD_ID to INFO_PRODUCT_INFO_TARGET
              Added target INFO_USB_SICD_ID for INFO_PRODUCT_INFO_READ_REQ
              and new sub block for INFO_PRODUCT_INFO_READ_RESP.Change by
              comment: 004.015 -> 004.014.

Version     : 004.013    NON-DRAFT   30-Nov-2004    Mika Halttunen
Reason      : SCO
Reference   : LN WP RM-RIM 009-13900
Description : Added Entry INFO_TYPE_CS_CDMA2100 to INFO_CS_TYPE_1
              INFO_TYPE_CS_CDMA2100 added to INFO_CS_TYPE_1.

Version     : 004.012    NON-DRAFT   14-Oct-2004    Mika Halttunen
Reason      : SCO
Reference   : ADB SWAM MH04101458438
              LN WP RM-RIM 009-12873.
Description : Added Subblock INFO_SB_SN_MEID_HEX to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_MEID_HEX_ASCII to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_MEID_PLAIN to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_SN_MEID_HEX
              Added Subblock INFO_SB_SN_MEID_HEX_ASCII
              Added Subblock INFO_SB_SN_MEID_PLAIN
              Added Entry INFO_SN_MEID_HEX to INFO_SN_TARGET_IDENTIFIER
              Added Entry INFO_SN_MEID_HEX_ASCII to INFO_SN_TARGET_IDENTIFIER
              Added Entry INFO_SN_MEID_PLAIN to INFO_SN_TARGET_IDENTIFIER
              Added Constant INFO_SN_MEID_HEX_ASCII_LEN
              Added Constant INFO_SN_MEID_PLAIN_LEN
              Added Constant INFO_SN_RAW_MEID_LEN
              Added targets INFO_SN_MEID_HEX, INFO_SN_MEID_HEX_ASCII and
              INFO_SN_MEID_PLAIN( INFO_SERIAL_NUMBER_READ_REQ ) and sub
              blocks INFO_SB_SN_MEID_HEX, INFO_SB_SN_MEID_HEX_ASCII and
              INFO_SB_SN_MEID_PLAIN( INFO_SERIAL_NUMBER_READ_RESP ).

Version     : 004.011    NON-DRAFT   27-Sep-2004    Mika Halttunen
Reason      : SCO
Reference   : LN WP RM-RIM 009-10970.
Description : Added Subblock INFO_SB_WT_RPF to INFO_WT_READ_RESP
              Added Subblock INFO_SB_WT_RPF to INFO_WT_WRITE_REQ
              Added Subblock INFO_SB_WT_RPF
              Added Entry INFO_WT_RPF to INFO_WT_READ_BITS
              Added Constant INFO_WT_RPF_LEN
              Added target INFO_WT_RPF and sub block INFO_SB_WT_RPF.

Version     : 004.010    NON-DRAFT   23-Sep-2004    Mika Halttunen
Reason      : SCO
Reference   : LN WP RM-RIM 009-13813, ADB SWAM MH040
Description : Added Subblock INFO_SB_USB_MASS_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_NOKIA_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_VENDOR_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_USB_MASS_ID
              Added Subblock INFO_SB_USB_NOKIA_ID
              Added Subblock INFO_SB_USB_VENDOR_ID
              Added Entry INFO_USB_MASS_ID to INFO_PRODUCT_INFO_TARGET
              Added Entry INFO_USB_NOKIA_ID to INFO_PRODUCT_INFO_TARGET
              Added Entry INFO_USB_VENDOR_ID to INFO_PRODUCT_INFO_TARGET
              Added targets INFO_USB_VENDOR_ID, INFO_USB_MASS_ID,
              INFO_USB_NOKIA_ID for INFO_PRODUCT_INFO_READ_REQ and new sub
              blocks to INFO_PRODUCT_INFO_READ_RESP.

Version     : 004.009    NON-DRAFT   30-Aug-2004    Mika Halttunen
Reason      : SCO
Reference   : LN WP RM-RIM 009-12385, ADB SWAM MH04090657967
Description : Added Message INFO_WLAN_INFO_READ_REQ
              Added Message INFO_WLAN_INFO_READ_RESP
              Added Constant INFO_WLAN_MAC_ADDR_LEN
              Added INFO_WLAN_INFO_READ_REQ/RESP.

Version     : 004.008    NON-DRAFT   07-Apr-2004    Mika Halttunen
Reason      : SUB
Reference   : LN ADB SWAM MH04040744171, WP RM-RIM 010-1111
Description : Added Subblock INFO_SB_RAP_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_RAP_VERSION
              Added Constant table INFO_RAP_TYPE
              Added Entry INFO_RAP to INFO_VERSION_TARGETS_2
              Added Constant INFO_SB_RAP_LEN
              Added INFO_RAP to INFO_VERSION_TARGETS_2, sub block
              INFO_SB_RAP_VERSION to INFO_VERSION_READ_RESP, constants for
              RAP types. Increased values INFO_SB_RETU_LEN and
              INFO_SB_TAHVO_LEN. Added comments to INFO_WT_STATUS and
              ITEM_PARAMETERs to warranty data sub blocks.

Version     : 004.007    NON-DRAFT   12-Feb-2004    Mika Halttunen
Reason      : SCO
Reference   : LN ADB SWAM MH, ISA RM-RIM ID 010-3596
Description : Added Subblock INFO_SB_PRODUCT_TYPE_CS_SEC to INFO_PRODUCT_TYPE_READ_RESP
              Added Entry INFO_PRODUCT_TYPE_CS_SEC to INFO_PRODUCT_TYPE_TARGET
              Added target INFO_PRODUCT_TYPE_CS_SEC to
              INFO_PRODUCT_TYPE_TARGET and sub block
              INFO_SB_PRODUCT_CS_TYPE_SEC to INFO_PRODUCT_TYPE_READ_RESP.
              Added new document properties.

Version     : 004.006    NON-DRAFT   29-Jan-2004    Mika Halttunen
Reason      : SCO
Reference   : LN ADB SWAM MH04011566405, ISA RM-RIM ID 009-8633
Description : Added Message INFO_LONG_DATA_READ_REQ
              Added Message INFO_LONG_DATA_READ_RESP
              Added Message INFO_LONG_DATA_WRITE_REQ
              Added Message INFO_LONG_DATA_WRITE_RESP
              Minor changes, Messages INFO_LONG_DATA_READ_REQ/RESP added. Sub
              block INFO_SB_PRODUCT_INFO removed from this file due to fact
              it is only used by Info srv.

Version     : 004.005    NON-DRAFT   18-Dec-2003    Mika Halttunen
Reason      : SCO
Reference   : LN ADB SWAM MH03120856566, LN ISA RM-RIM ID 009-5301
Description : Added Subblock INFO_SB_PRODUCT_INFO_NUM_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_PRODUCT_INFO_TYPE_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_PRODUCT_INFO_XCVR_ID to INFO_PRODUCT_INFO_READ_RESP
              Added Subblock INFO_SB_PRODUCT_INFO_NUM_ID
              Added Subblock INFO_SB_PRODUCT_INFO_TYPE_ID
              Added Subblock INFO_SB_PRODUCT_INFO_XCVR_ID
              Added Entry INFO_PRODUCT_NUM_ID to INFO_PRODUCT_INFO_TARGET
              Added Entry INFO_PRODUCT_TYPE_ID to INFO_PRODUCT_INFO_TARGET
              Added Entry INFO_PRODUCT_XCVR_ID to INFO_PRODUCT_INFO_TARGET
              Added three new targets to INFO_PRODUCT_INFO_READ_REQ and sub
              blocks to INFO_PRODUCT_INFO_READ_RESP.

Version     : 004.004    NON-DRAFT   19-Nov-2003    Mika Halttunen
Reason      : File location change + Inspection correction
Reference   : LN ADB SWAM MH03102361903
Description : Made status comments in INFO_VERSION_READ_RESP more clear and
              moved ISI files to Continuus project global_interface and
              GIF_SPECS.

Version     : 004.003    NON-DRAFT   15-Aug-2003    Mika Halttunen
Reason      : SUBs and inspection
Reference   : LN ISA RM-RIM 009-6673, LN ADB SWAM MH03082747192
              LN ISA RM-RIM
              009-4423,009-4425,009-4424,009-4422,009-4467,009-4466,009-4471,009-2049,010-1111
Description : Changed Message INFO_VERSION_READ_REQ
              Added Subblock INFO_SB_APE_ADSP_SW to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_BT_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_HW_VERSION to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_SW_CORE_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_TEST_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_BOOTCODE_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CAMERA_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_CONTENT_PACK_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_RETU_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_TAHVO_VER to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_APE_ADSP_SW
              Added Subblock INFO_SB_APE_BT_VERSION
              Added Subblock INFO_SB_APE_HW_VERSION
              Added Subblock INFO_SB_APE_SW_CORE_VER
              Added Subblock INFO_SB_APE_TEST_VER
              Added Subblock INFO_SB_BOOTCODE_VER
              Added Subblock INFO_SB_CAMERA_VER
              Added Subblock INFO_SB_CONTENT_PACK_VER
              Added Subblock INFO_SB_RETU_VER
              Added Subblock INFO_SB_TAHVO_VER
              Added Bitmask table INFO_VERSION_TARGETS_2
              Added Constant INFO_SB_APE_ADSP_VER_LEN
              Added Constant INFO_SB_APE_HW_VER_LEN
              Added Constant INFO_SB_RETU_LEN
              Added Constant INFO_SB_TAHVO_LEN
              Added Reference related stuff.

Version     : 004.002    NON_DRAFT   30-Jul-2003    Mika Halttunen
Reason      : Error correction
Reference   : LN PCP Errors JL03070342503
Description : Changed member name to correct one in INFO_SB_BAND_CS_TYPE_t.

Version     : 004.000                               
Reason      : -
Reference   : -
Description : Official version for inspection:
              NOTE: Warranty data reading and writing messages, sub blocks
              etc. added here differs from original ones in warranty srv.

Version     : 003.001                               
Reason      : -
Reference   : -
Description : Added Message INFO_WT_READ_REQ
              Added Message INFO_WT_READ_RESP
              Added Message INFO_WT_WRITE_REQ
              Added Message INFO_WT_WRITE_RESP
              Added Subblock INFO_SB_WT_ORIG_MAN_MONTH_YEAR
              Added Subblock INFO_SB_WT_ORIG_SN_INFO
              Added Subblock INFO_SB_WT_OWN_MAN_MONTH_YEAR
              Added Subblock INFO_SB_WT_PURCH_MONTH_YEAR
              Added Subblock INFO_SB_WT_REPAIR_MONTH_YEAR
              Added Subblock INFO_SB_WT_WIS
              Added Bitmask table INFO_WT_READ_BITS
              Added Constant table INFO_WT_SN
              Added Constant table INFO_WT_STATE
              Added Constant table INFO_WT_STATUS
              Added Constant INFO_WT_SERIAL_NUMBER_LENGTH
              Warranty messages added, this is unofficial version of the
              file.(Inspection nor Acceptance round not done)

Version     : 003.000                               
Reason      : -
Reference   : -
Description : Changed Sequence CS_TYPE_SEC
              Added Constant INFO_SW_ID_LEN
              Fillers replaced with sw_id[5+1] within CS_TYPE_SEC

Version     : 002.005                               
Reason      : -
Reference   : -
Description : Added Message INFO_BT_ID_READ_REQ
              Added Message INFO_BT_ID_READ_RESP
              Added Message INFO_BT_ID_WRITE_REQ
              Added Message INFO_BT_ID_WRITE_RESP
              Added Sequence INFO_BT_ID_SEC
              Added Subblock INFO_SB_BT_ID_PLAIN
              Added Subblock INFO_SB_BT_ID_SEC
              Added Constant table INFO_BT_DATA_TARGET
              Added Constant INFO_BT_ID_LEN
              Added messages: INFO_BT_ID_READ_REQ/RESP and
              INFO_BT_ID_WRITE_REQ/RESP,sub blocks: INFO_SB_BT_ID_PLAIN and
              INFO_SB_BT_ID_SEC.

Version     : 002.004                               
Reason      : -
Reference   : -
Description : Added Subblock INFO_SB_BAND_CS_TYPE to INFO_PROD_INFO_WRITE_REQ
              Added Subblock INFO_SB_BAND_CS_TYPE
              Added sub block INFO_SB_BAND_CS_TYPE in
              INFO_PROD_INFO_WRITE_REQ msg

Version     : 002.002                               
Reason      : -
Reference   : -
Description : Added FTD data FTD_SB_TEXT_VERSION to FTD table
              Added FTD_SB_TEXT_VERSION to FTD data table.

Version     : 002.001                               
Reason      : -
Reference   : -
Description : Added Subblock INFO_SB_ADSP_DEVICE_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_ADSP_REVISION_ID to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_ADSP_DEVICE_ID
              Added Subblock INFO_SB_ADSP_REVISION_ID
              Added Entry INFO_ADSP_DEVICE_ID to INFO_VERSION_TARGETS
              Added Entry INFO_ADSP_REVISION_ID to INFO_VERSION_TARGETS
              Added version targets INFO_ADSP_DEVICE_ID,
              INFO_ADSP_REVISION_ID and sub blocks INFO_SB_ADSP_DEVICE_ID,
              INFO_SB_ADSP_REVISION_ID.

Version     : 002.000                               
Reason      : -
Reference   : -
Description : Added Subblock INFO_SB_SN_DEFAULT_PLAIN to INFO_SERIAL_NUMBER_READ_RESP
              Added Subblock INFO_SB_VERSION_BY_DSP_CORE_SRV to INFO_VERSION_READ_RESP
              Added Subblock INFO_SB_SN_DEFAULT_PLAIN
              Added Subblock INFO_SB_VERSION_BY_DSP_CORE_SRV
              Added Entry INFO_SN_DEFAULT_PLAIN to INFO_SN_TARGET_IDENTIFIER
              Added sub block INFO_SB_SN_DEFAULT_PLAIN_t, sub block
              INFO_SB_VERSION_BY_DSP_CORE_SRV_t, target
              INFO_SB_SN_DEFAULT_PLAIN.

Version     : 001.027                               
Reason      : -
Reference   : -
Description : Modified to comply with i_info_m.doc v.28

Version     : 001.000                               
Reason      : -
Reference   : -
Description : First version of the interface

------------------------------------------------------------------------------

Description

SEE RESERVED SUB BLOCK ID INFORMATION /18/.

*/

#ifndef _INFO_ISI_H
#define _INFO_ISI_H

#include "isi_conf.h"

#ifndef INFO_ISI_VERSION
#define INFO_ISI_VERSION
#define INFO_ISI_VERSION_Z   9
#define INFO_ISI_VERSION_Y   0
#endif

#define INFO_ISI_MIN_VERSION(z,y) \
 ((INFO_ISI_VERSION_Z == (z) && INFO_ISI_VERSION_Y >= (y)) || \
  (INFO_ISI_VERSION_Z > (z)))

#if !INFO_ISI_MIN_VERSION(1,0)
#error The specified interface version is not supported by this header file
#elif INFO_ISI_MIN_VERSION(9,1)
#error The specified interface version is not supported by this header file
#endif

/* This is used internally by info-srv */
#define INFO_RESERVE   0x00
#define SIZEOF_BAND_CS_TYPE   sizeof(uint32)

/* ----------------------------------------------------------------------- */
/* Constants                                                               */
/* ----------------------------------------------------------------------- */


#if INFO_ISI_MIN_VERSION(3,0)
#define INFO_SW_ID_LEN                           0x06
#endif /* INFO_ISI_MIN_VERSION(3,0) */

#define INFO_SB_SN_IMEI_PLAIN_STR_LEN            0x10
#define INFO_SB_SN_IMEI2_PLAIN_STR_LEN           0x10
#define INFO_SB_SN_IMEI_SPARE_TO_NET_STR_LEN     0x08
#define INFO_SB_SN_IMEI2_SPARE_TO_NET_STR_LEN    0x08
#define INFO_SB_SN_IMEI2_SV_TO_NET_STR_LEN       0x09
#define INFO_SB_SN_ESN_PLAIN_STR_LEN             0x0C
#define INFO_SB_SN_ESN_HEX_DATA_LEN              0x04
#define INFO_SB_SN_ESNX_PLAIN_STR_LEN            0x09
#define INFO_SB_SN_ESNX_HEX_DATA_LEN             0x03
#define INFO_SN_RAW_MEID_LEN                     0x07
#define INFO_SN_MEID_HEX_ASCII_LEN               0x0F
#define INFO_SN_MEID_PLAIN_LEN                   0x14
#define INFO_SB_SN_PDC_DATA_LEN                  0x08
#define INFO_SB_SN_BATTERY_DATA_LEN              0x1B

#if !INFO_ISI_MIN_VERSION(1,0)
/* constant for variable-length definitions */
#define INFO_ANY_SIZE                            1
#endif /* !INFO_ISI_MIN_VERSION(1,0) */

#define INFO_SB_HW_VERSION_STR_LEN               0x05
#define INFO_SB_PCI_VERSION_STR_LEN              0x05
#define INFO_SB_MEMORY_STR_LEN                   0x28
#define INFO_SB_PRODUCTION_SN_STR_LEN            0x0A
#define INFO_SB_LONG_PRODUCTION_SN_STR_LEN       0x10
#define INFO_SB_PRODUCT_CODE_STR_LEN             0x10
#define INFO_SB_BASIC_PRODUCT_CODE_STR_LEN       0x10
#define INFO_SB_MODULE_CODE_STR_LEN              0x10
#define INFO_SB_FLASH_CODE_STR_LEN               0x06
#define INFO_SB_ORDER_NUMBER_STR_LEN             0x08
#define INFO_BT_ID_LEN                           0x06
#define INFO_WT_SERIAL_NUMBER_LENGTH             0x14
#define INFO_WT_RPF_LEN                          0x04
#define INFO_SB_EM_ASIC_LEN                      0x07

#if INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_SB_RETU_LEN                         0x07
#endif /* INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_SB_TAHVO_LEN                        0x07
#endif /* INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_SB_RAP_LEN                          0x07
#endif /* INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26) */

#define INFO_SB_SYSTEM_ASIC_LEN                  0x07
#define INFO_WLAN_MAC_ADDR_LEN                   0x06

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_GENERAL_SYM - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_GENERAL_SYM_CONST;

#define INFO_OK                                  0x00
#define INFO_FAIL                                0x01
#define INFO_NO_NUMBER                           0x02
#define INFO_NOT_SUPPORTED                       0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_SN_TARGET_IDENTIFIER - Valid from version 001.000  */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_SN_TARGET_IDENTIFIER_CONST;

#define INFO_SN_IMEI_PLAIN                       0x41
#define INFO_SN_IMEI_SPARE_TO_NET                0x42
#define INFO_SN_IMEI_SV_TO_NET                   0x43
#define INFO_SN_ESN_PLAIN                        0x44
#define INFO_SN_ESNX_PLAIN                       0x56
#define INFO_SN_ESN_HEX                          0x45
#define INFO_SN_ESNX_HEX                         0x5A
#define INFO_SN_PDC                              0x46
#define INFO_SN_DEFAULT                          0x5D
#define INFO_SN_DEFAULT_PLAIN                    0x5E
#define INFO_SN_MEID_HEX                         0x61
#define INFO_SN_MEID_HEX_ASCII                   0x62
#define INFO_SN_MEID_PLAIN                       0x63
#define INFO_SN_IMEI2_PLAIN                      0x64
#define INFO_SN_IMEI2_SPARE_TO_NET               0x65
#define INFO_SN_IMEI2_SV_TO_NET                  0x66
#define INFO_SN_BATTERY                          0x67

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_BATCH_TYPE - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_BATCH_TYPE_CONST;

/* To read PP features specified in INFO_SB_PP(s) or INFO_SB_PP_DATA(s) */
#define INFO_PP_PROD_PROFILE_FEATURE             0x00
/* To read all PP features */
#define INFO_PP_ALL_FEATURE                      0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_PRODUCT_TYPE_TARGET - Valid from version 001.000   */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_PRODUCT_TYPE_TARGET_CONST;

#define INFO_PRODUCT_TYPE_CS                     0x01
#define INFO_PRODUCT_TYPE_HW_INFO                0x02
/* To read encrypted CS type as such */
#define INFO_PRODUCT_TYPE_CS_SEC                 0x03

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_PRODUCT_INFO_TARGET - Valid from version 001.000   */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_PRODUCT_INFO_TARGET_CONST;

#define INFO_PRODUCT_NAME                        0x01
#define INFO_PRODUCT_CATEGORY                    0x02
#define INFO_PRODUCT_XID                         0x03
#define INFO_PRODUCT_DEV_NAME                    0x04
#define INFO_PRODUCT_COMP01                      0x05
#define INFO_PRODUCT_NAME_COMPRESSED             0x06
#define INFO_PRODUCT_MANUFACTURER                0x07
#define INFO_PRODUCT_XCVR_ID                     0x08
#define INFO_PRODUCT_NUM_ID                      0x09
#define INFO_PRODUCT_TYPE_ID                     0x0A
#define INFO_USB_VENDOR_ID                       0x0B
#define INFO_USB_MASS_ID                         0x0C
#define INFO_USB_NOKIA_ID                        0x0D
#define INFO_USB_SICD_ID                         0x0E
#define INFO_BT_PID                              0x0F
#define INFO_USB_RNDIS_ID                        0x10
#define INFO_USB_NCM_ID                          0x11
#define INFO_SIM_SLOTS                           0x12
#define INFO_USB_NSM_ID                          0x13
#define INFO_USB_NSM_LOCAL_TEST_ID               0x14

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_BT_DATA_TARGET - Valid from version 002.005        */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_BT_DATA_TARGET_CONST;

#define INFO_BT_ID                               0x01

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_WT_SN - Valid from version 003.001                 */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_WT_SN_CONST;

#define INFO_WT_SN_TYPE_IMEI                     0x01
#define INFO_WT_SN_TYPE_ESN                      0x02
#define INFO_WT_SN_TYPE_CSN                      0x03
#define INFO_WT_SN_TYPE_MEID                     0x04

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_WT_STATUS - Valid from version 003.001             */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_WT_STATUS_CONST;

#define INFO_WT_OK                               0x01
#define INFO_WT_FAIL                             0x02
/* Possible WIS value */
#define INFO_WT_INFO_STATE_DEF                   0x03
/* Possible WIS value */
#define INFO_WT_INFO_STATE_EXC                   0x04
/* Possible WIS value */
#define INFO_WT_INFO_STATE_USE                   0x05

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_WT_STATE - Valid from version 003.001              */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_WT_STATE_CONST;

#define INFO_WT_LOCKED                           0x01
#define INFO_WT_UNLOCKED                         0x02

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_RAP_TYPE - Versions 004.008 - 008.026              */
/* ----------------------------------------------------------------------- */
/* Rap type values are derived from hw_version.h */

#if INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26)
typedef uint8 INFO_RAP_TYPE_CONST;

#define INFO_RAP3G                               0x08
#define INFO_RAPGSM                              0x09
#define INFO_RAPCDMA                             0x0A
#define INFO_RAPHSDPA                            0x0B
#define INFO_RAPTOR                              0x0C
#endif /* INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_RESET_REASON - Valid from version 008.010          */
/* ----------------------------------------------------------------------- */
/* Reset reason values are derived from hw_power.h */
typedef uint8 INFO_RESET_REASON_CONST;

#define INFO_RESET_REASON_UNKNOWN                0x01
#define INFO_RESET_REASON_POWER_OFF_CHARGER_CONNECTED 0x02
#define INFO_RESET_REASON_POWER_OFF_KEY_PRESSED  0x03
#define INFO_RESET_REASON_SW_RESET_REQUESTED     0x04
#define INFO_RESET_REASON_INT_ERROR              0x05
#define INFO_RESET_REASON_STACK_OVERFLOW         0x06
#define INFO_RESET_REASON_WD_RESET_REQUESTED     0x07
#define INFO_RESET_REASON_DIV_BY_ZERO            0x08
#define INFO_RESET_REASON_DSP_NO_RESPONSE_ERROR  0x09
#define INFO_RESET_REASON_DSP_ERROR              0x0A
#define INFO_RESET_REASON_DSP_INVALID_MSG_ERROR  0x0B
#define INFO_RESET_REASON_PRODUCTION_RESET       0x0C
#define INFO_RESET_REASON_ASSERTION_FAILED       0x0D
#define INFO_RESET_REASON_UNDEFINED_INSTRUCTION  0x0E
#define INFO_RESET_REASON_IO_ABORT               0x0F
#define INFO_RESET_REASON_NULL_ACCESS            0x10
#define INFO_RESET_REASON_ADDRESS_ERROR          0x11
#define INFO_RESET_REASON_ALIGNMENT_ERROR        0x12
#define INFO_RESET_REASON_FLASH_WRITE_PROTECTION 0x13
#define INFO_RESET_REASON_CBUS_ERROR             0x14
#define INFO_RESET_REASON_POWER_OFF_RTC          0x15
#define INFO_RESET_REASON_OS_FATAL_HANDLER       0x16
#define INFO_RESET_REASON_FLASH_BLOCK_OVERFLOW   0x17
#define INFO_RESET_REASON_DSP_STARTUP_FAILED     0x18
#define INFO_RESET_REASON_ASIC_WD_RESET          0x19
#define INFO_RESET_REASON_EPOC_RESET             0x1A
#define INFO_RESET_REASON_ADSP_NO_RESPONSE_ERROR 0x1B
#define INFO_RESET_REASON_ADSP_ERROR             0x1C
#define INFO_RESET_REASON_ADSP_INVALID_MSG_ERROR 0x1D
#define INFO_RESET_REASON_ADSP_STARTUP_FAILED    0x1E
#define INFO_RESET_REASON_ABORT_EBUSC            0x1F
#define INFO_RESET_REASON_ABORT_PREFETCH         0x20
#define INFO_RESET_REASON_ABORT_DATA             0x21
#define INFO_RESET_REASON_UNHANDLED_ABORT        0x22
#define INFO_RESET_REASON_SISA_EXIT              0x23
#define INFO_RESET_REASON_OS_WARNING_HANDLER     0x24
#define INFO_RESET_REASON_SECURE_VIOLATION       0x25
#define INFO_RESET_REASON_USER_RESET             0x26

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_DBI_BATTERY_CHEMISTRY - Valid from version 008.016 */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_DBI_BATTERY_CHEMISTRY_CONST;

#define INFO_DBI_BATTERY_CHEMISTRY_4V20_LI_ION   0x01
#define INFO_DBI_BATTERY_CHEMISTRY_4V20_LI_PO    0x02
#define INFO_DBI_BATTERY_CHEMISTRY_4V35_SDI_HIGH_VOLTAGE 0x03
#define INFO_DBI_BATTERY_CHEMISTRY_UNKNOWN       0xFF

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_DBI_BATTERY_VENDOR - Valid from version 008.016    */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_DBI_BATTERY_VENDOR_CONST;

#define INFO_DBI_BATTERY_VENDOR_ID_SDI           0x01
#define INFO_DBI_BATTERY_VENDOR_UNKNOWN          0xFF

/* ----------------------------------------------------------------------- */
/* Constant Table: INFO_MCU_SPEED - Valid from version 008.023             */
/* ----------------------------------------------------------------------- */
typedef uint8 INFO_MCU_SPEED_CONST;

#define INFO_MCU_SPEED_1GHz                      0x01
#define INFO_MCU_SPEED_1_28GHz                   0x02
#define INFO_MCU_SPEED_UNKNOWN                   0xFF

/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_VERSION_TARGETS - Valid from version 008.026        */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(8,26)
typedef uint16 INFO_VERSION_TARGETS_CONST;

#define INFO_MCUSW                               0x0001  /* ---------------1 */
#define INFO_HW                                  0x0002  /* --------------1- */
#define INFO_PCI                                 0x0004  /* -------------1-- */
#define INFO_SIM_SWITCH                          0x0008  /* ------------1--- */
#define INFO_MEMORY                              0x0010  /* -----------1---- */
#define INFO_RFIC                                0x0020  /* ----------1----- */
#define INFO_DSP                                 0x0040  /* ---------1------ */
#define INFO_LCD                                 0x0080  /* --------1------- */
#define INFO_ROFS_FOTAID                         0x0100  /* -------1-------- */
#define INFO_BT_MCM                              0x0200  /* ------1--------- */
#define INFO_PMU                                 0x0400  /* -----1---------- */
#define INFO_WLAN                                0x0800  /* ----1----------- */
#define INFO_GPS                                 0x1000  /* ---1------------ */
#define INFO_CHARGER_DET                         0x2000  /* --1------------- */
#endif /* INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_VERSION_TARGETS - Versions 001.000 - 008.026        */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26)
typedef uint16 INFO_VERSION_TARGETS_CONST;

/* #define INFO_MCUSW                            0x0001 (already defined) */
/* #define INFO_HW                               0x0002 (already defined) */
/* #define INFO_PCI                              0x0004 (already defined) */
#define INFO_UEM                                 0x0008  /* ------------1--- */
#define INFO_UPP                                 0x0010  /* -----------1---- */
/* #define INFO_RFIC                             0x0020 (already defined) */
/* #define INFO_DSP                              0x0040 (already defined) */
/* #define INFO_LCD                              0x0080 (already defined) */
/* #define INFO_BT_MCM                           0x0200 (already defined) */
#define INFO_ADSP                                0x0400  /* -----1---------- */
#define INFO_FLIP_MCUSW                          0x1000  /* ---1------------ */

#if INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_ADSP_DEVICE_ID                      0x2000  /* --1------------- */
#endif /* INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_ADSP_REVISION_ID                    0x4000  /* -1-------------- */
#endif /* INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,12) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_GAZOO                               0x8000  /* 1--------------- */
#endif /* INFO_ISI_MIN_VERSION(5,12) && !INFO_ISI_MIN_VERSION(8,26) */

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_VERSION_TARGETS_2 - Valid from version 008.026      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(8,26)
typedef uint32 INFO_VERSION_TARGETS_2_CONST;

#define INFO_BOOTCODE_VER                        0x00000001  /* -------------------------------1 */
#define INFO_APE_SW_CORE_VER                     0x00000002  /* ------------------------------1- */
#define INFO_CONTENT_FOTAID                      0x00000004  /* -----------------------------1-- */
#define INFO_APE_TEST_VER                        0x00000008  /* ----------------------------1--- */
#define INFO_EM_ASIC                             0x00000010  /* ---------------------------1---- */
#define INFO_SW_VERSION                          0x00000020  /* --------------------------1----- */
#define INFO_APE_HW_VERSION                      0x00000040  /* -------------------------1------ */
#define INFO_APE_ADSP_SW                         0x00000080  /* ------------------------1------- */
#define INFO_CAMERA                              0x00000100  /* -----------------------1-------- */
#define INFO_APE_BT_VERSION                      0x00000200  /* ----------------------1--------- */
#define INFO_CONTENT_PACK                        0x00000400  /* ---------------------1---------- */
#define INFO_SYSTEM_ASIC                         0x00000800  /* --------------------1----------- */
#define INFO_CAMERA2                             0x00020000  /* --------------1----------------- */
#define INFO_CONTENT_VERSIONS                    0x00040000  /* -------------1------------------ */
#define INFO_ROFS_VERSIONS                       0x00080000  /* ------------1------------------- */
#define INFO_BOM_ID_VERSION                      0x00100000  /* -----------1-------------------- */
#define INFO_NAVISCROLL_VERSION                  0x00200000  /* ----------1--------------------- */
#define INFO_ACCELEROMETER_VERSION               0x00400000  /* ---------1---------------------- */
#define INFO_CWS_CHIP_ID                         0x00800000  /* --------1----------------------- */
#define INFO_TOUCH_SENSOR_ID                     0x01000000  /* -------1------------------------ */
#define INFO_PROXIMITY_SENSOR_ID                 0x02000000  /* ------1------------------------- */
#define INFO_NFC_VERSION                         0x04000000  /* -----1-------------------------- */
#define INFO_MCUSW_FOTAID                        0x08000000  /* ----1--------------------------- */
#define INFO_MAGNETOMETER_ID                     0x10000000  /* ---1---------------------------- */
#define INFO_DBI_ID                              0x20000000  /* --1----------------------------- */
#define INFO_HW_DRIVER_VERSION                   0x40000000  /* -1------------------------------ */
#define INFO_MCU_SPEED_VERSION                   0x80000000  /* 1------------------------------- */
#endif /* INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_VERSION_TARGETS_2 - Versions 004.003 - 008.026      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26)
typedef uint32 INFO_VERSION_TARGETS_2_CONST;

/* #define INFO_BOOTCODE_VER                     0x00000001 (already defined) */
/* #define INFO_APE_SW_CORE_VER                  0x00000002 (already defined) */
/* #define INFO_APE_TEST_VER                     0x00000008 (already defined) */
#define INFO_RETU                                0x00000010  /* ---------------------------1---- */
#define INFO_TAHVO                               0x00000020  /* --------------------------1----- */
/* #define INFO_APE_HW_VERSION                   0x00000040 (already defined) */
/* #define INFO_APE_ADSP_SW                      0x00000080 (already defined) */
/* #define INFO_CAMERA                           0x00000100 (already defined) */
/* #define INFO_APE_BT_VERSION                   0x00000200 (already defined) */
/* #define INFO_CONTENT_PACK                     0x00000400 (already defined) */

#if INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_RAP                                 0x00000800  /* --------------------1----------- */
#endif /* INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,13) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_APE_CUI_LCD_VERSION                 0x00001000  /* -------------------1------------ */
#endif /* INFO_ISI_MIN_VERSION(5,13) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,13) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_APE_IPDC_VERSION                    0x00002000  /* ------------------1------------- */
#endif /* INFO_ISI_MIN_VERSION(5,13) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_APE_DVB_H_RX_HW_VER                 0x00004000  /* -----------------1-------------- */
#endif /* INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_APE_DVB_H_RX_SW_VER                 0x00008000  /* ----------------1--------------- */
#endif /* INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26) */


#if INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26)
#define INFO_APE_DVB_H_RX_BOOTLOADER_VER         0x00010000  /* ---------------1---------------- */
#endif /* INFO_ISI_MIN_VERSION(5,4) && !INFO_ISI_MIN_VERSION(8,26) */

/* #define INFO_CAMERA2                          0x00020000 (already defined) */
/* #define INFO_CONTENT_VERSIONS                 0x00040000 (already defined) */
/* #define INFO_ROFS_VERSIONS                    0x00080000 (already defined) */
/* #define INFO_BOM_ID_VERSION                   0x00100000 (already defined) */
/* #define INFO_NAVISCROLL_VERSION               0x00200000 (already defined) */
/* #define INFO_ACCELEROMETER_VERSION            0x00400000 (already defined) */
/* #define INFO_CWS_CHIP_ID                      0x00800000 (already defined) */
/* #define INFO_TOUCH_SENSOR_ID                  0x01000000 (already defined) */
/* #define INFO_PROXIMITY_SENSOR_ID              0x02000000 (already defined) */
/* #define INFO_NFC_VERSION                      0x04000000 (already defined) */
/* #define INFO_MAGNETOMETER_ID                  0x10000000 (already defined) */
/* #define INFO_DBI_ID                           0x20000000 (already defined) */
/* #define INFO_HW_DRIVER_VERSION                0x40000000 (already defined) */
/* #define INFO_MCU_SPEED_VERSION                0x80000000 (already defined) */
#endif /* INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_PRODUCT_TARGETS - Valid from version 001.000        */
/* ----------------------------------------------------------------------- */
typedef uint16 INFO_PRODUCT_TARGETS_CONST;

#define INFO_PRODUCTION_SN                       0x0001  /* ---------------1 */
#define INFO_PRODUCT_CODE                        0x0002  /* --------------1- */
#define INFO_MODULE_CODE                         0x0004  /* -------------1-- */
#define INFO_BASIC_PRODUCT_CODE                  0x0008  /* ------------1--- */
#define INFO_FLASH_CODE                          0x0010  /* -----------1---- */
#define INFO_ORDER_NUMBER                        0x0020  /* ----------1----- */
#define INFO_PRODUCT_SPECIFIC_DATA               0x0040  /* ---------1------ */
#define INFO_LONG_PRODUCTION_SN                  0x0080  /* --------1------- */
#define INFO_ATO                                 0x0100  /* -------1-------- */
#define INFO_SN_DEFAULT_TYPE                     0x0200  /* ------1--------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_CS_TYPE_1 - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */
typedef uint32 INFO_CS_TYPE_1_CONST;

#define INFO_TYPE_CS_WCDMA1900                   0x00000001  /* -------------------------------1 */
#define INFO_TYPE_CS_AMPS                        0x00000002  /* ------------------------------1- */
#define INFO_TYPE_CS_CDMA800                     0x00000004  /* -----------------------------1-- */
#define INFO_TYPE_CS_CDMA1700                    0x00000008  /* ----------------------------1--- */
#define INFO_TYPE_CS_CDMA1900                    0x00000010  /* ---------------------------1---- */
#define INFO_TYPE_CS_US_TDMA                     0x00000020  /* --------------------------1----- */
#define INFO_TYPE_CS_GSM400                      0x00000040  /* -------------------------1------ */
#define INFO_TYPE_CS_GSM700                      0x00000080  /* ------------------------1------- */
#define INFO_TYPE_CS_GSM850                      0x00000100  /* -----------------------1-------- */
#define INFO_TYPE_CS_GSM900                      0x00000200  /* ----------------------1--------- */
#define INFO_TYPE_CS_GSM1800                     0x00000400  /* ---------------------1---------- */
#define INFO_TYPE_CS_GSM1900                     0x00000800  /* --------------------1----------- */
#define INFO_TYPE_CS_PREPAID                     0x00001000  /* -------------------1------------ */

#if INFO_ISI_MIN_VERSION(4,13) && !INFO_ISI_MIN_VERSION(5,0)
#define INFO_TYPE_CS_CDMA2100                    0x00001000  /* -------------------1------------ */
#endif /* INFO_ISI_MIN_VERSION(4,13) && !INFO_ISI_MIN_VERSION(5,0) */


#if INFO_ISI_MIN_VERSION(5,0)
#define INFO_TYPE_CS_CDMA2100                    0x00002000  /* ------------------1------------- */
#endif /* INFO_ISI_MIN_VERSION(5,0) */

#define INFO_TYPE_CS_RUIM                        0x00004000  /* -----------------1-------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_WT_READ_BITS - Valid from version 003.001           */
/* ----------------------------------------------------------------------- */
typedef uint16 INFO_WT_READ_BITS_CONST;

#define INFO_WT_ORIG_SN                          0x0001  /* ---------------1 */
#define INFO_WT_ORIG_MAN_MONTH_YEAR              0x0002  /* --------------1- */
#define INFO_WT_OWN_MAN_MONTH_YEAR               0x0004  /* -------------1-- */
#define INFO_WT_PURCH_MONTH_YEAR                 0x0008  /* ------------1--- */
#define INFO_WT_REPAIR_MONTH_YEAR                0x0010  /* -----------1---- */
#define INFO_WT_WIS                              0x0020  /* ----------1----- */
#define INFO_WT_RPF                              0x0040  /* ---------1------ */
#define INFO_WT_ALL_BITS                         0x007F  /* ---------1111111 */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_STARTUP_REASON - Valid from version 008.008         */
/* ----------------------------------------------------------------------- */
typedef uint32 INFO_STARTUP_REASON_CONST;

#define INFO_STARTUP_REASON_UNKNOWN              0x00000000  /* -------------------------------- */
#define INFO_STARTUP_REASON_NORMAL               0x00000001  /* -------------------------------1 */
#define INFO_STARTUP_REASON_RTC_ALARM            0x00000002  /* ------------------------------1- */
#define INFO_STARTUP_REASON_CHARGER_CONNECTED    0x00000004  /* -----------------------------1-- */
#define INFO_STARTUP_REASON_SERVICE_BATTERY      0x00000008  /* ----------------------------1--- */
#define INFO_STARTUP_REASON_RESET                0x00000010  /* ---------------------------1---- */
#define INFO_STARTUP_REASON_TEST_BATTERY         0x00000020  /* --------------------------1----- */
#define INFO_STARTUP_REASON_PRODUCTION_RESET     0x00000040  /* -------------------------1------ */
#define INFO_STARTUP_REASON_SW_RESET             0x00000080  /* ------------------------1------- */
#define INFO_STARTUP_REASON_SW_WATCHDOG_RESET    0x00000100  /* -----------------------1-------- */
#define INFO_STARTUP_REASON_PROMMER_RESET        0x00000200  /* ----------------------1--------- */
#define INFO_STARTUP_REASON_MBUS_CONNECTED       0x00000400  /* ---------------------1---------- */
#define INFO_STARTUP_REASON_SECURE_VIOLATION     0x00000800  /* --------------------1----------- */
#define INFO_STARTUP_REASON_FLASH_MODE           0x00001000  /* -------------------1------------ */
#define INFO_STARTUP_REASON_PURX                 0x00002000  /* ------------------1------------- */
#define INFO_STARTUP_REASON_USB_CABLE_CONNECT    0x00004000  /* -----------------1-------------- */
#define INFO_STARTUP_REASON_FAKE_POWER_OFF       0x00008000  /* ----------------1--------------- */

/* ----------------------------------------------------------------------- */
/* Bitmask Table: INFO_LIFETIME_TARGET - Valid from version 008.024        */
/* ----------------------------------------------------------------------- */
typedef uint32 INFO_LIFETIME_TARGET_CONST;

#define INFO_LIFETIME_TARGET_LIFETIME            0x00000001  /* -------------------------------1 */
#define INFO_LIFETIME_TARGET_REBOOTS             0x00000002  /* ------------------------------1- */
#define INFO_LIFETIME_TARGET_UPDATES             0x00000004  /* -----------------------------1-- */

/* ----------------------------------------------------------------------- */
/* FTD Data Table - Valid from version 001.000                             */
/* ----------------------------------------------------------------------- */
/* Version number of MCU SW */
#define FTD_SB_MCU_VERSION                       0x0101  /* String */
/* PPM version */
#define FTD_SB_PPM_VERSION                       0x0102  /* String */
/* Date of version */
#define FTD_SB_VERSION_DATE                      0x0103  /* String */
/* Version of DSP SW */
#define FTD_SB_DSP_VERSION                       0x0104  /* String */
#define FTD_SB_MCU_CHECKSUM                      0x0105  /* Word */
/* HW Version */
#define FTD_SB_HW_VERSION                        0x0106  /* String */
/* Language package version */
#define FTD_SB_TEXT_VERSION                      0x0107  /* String */

/* ----------------------------------------------------------------------- */
/* Message ID's                                                            */
/* ----------------------------------------------------------------------- */

#define INFO_SERIAL_NUMBER_READ_REQ              0x00
#define INFO_SERIAL_NUMBER_READ_RESP             0x01
#define INFO_PP_READ_REQ                         0x02
#define INFO_PP_READ_RESP                        0x03
#define INFO_PP_WRITE_REQ                        0x04
#define INFO_PP_WRITE_RESP                       0x05
#define INFO_PP_IND                              0x06
#define INFO_VERSION_READ_REQ                    0x07
#define INFO_VERSION_READ_RESP                   0x08
#define INFO_VERSION_WRITE_REQ                   0x09
#define INFO_VERSION_WRITE_RESP                  0x0A
#define INFO_PROD_INFO_READ_REQ                  0x0B
#define INFO_PROD_INFO_READ_RESP                 0x0C
#define INFO_PROD_INFO_WRITE_REQ                 0x0D
#define INFO_PROD_INFO_WRITE_RESP                0x0E
#define INFO_PP_CUSTOMER_DEFAULTS_REQ            0x0F
#define INFO_PP_CUSTOMER_DEFAULTS_RESP           0x10
#define INFO_PRODUCT_TYPE_WRITE_REQ              0x11
#define INFO_PRODUCT_TYPE_WRITE_RESP             0x12
#define INFO_PRODUCT_TYPE_READ_REQ               0x13
#define INFO_PRODUCT_TYPE_READ_RESP              0x14
#define INFO_PRODUCT_INFO_READ_REQ               0x15
#define INFO_PRODUCT_INFO_READ_RESP              0x16
#define INFO_BT_ID_READ_REQ                      0x17
#define INFO_BT_ID_READ_RESP                     0x18
#define INFO_BT_ID_WRITE_REQ                     0x19
#define INFO_BT_ID_WRITE_RESP                    0x1A
#define INFO_WT_READ_REQ                         0x1B
#define INFO_WT_READ_RESP                        0x1C
#define INFO_WT_WRITE_REQ                        0x1D
#define INFO_WT_WRITE_RESP                       0x1E
#define INFO_LONG_DATA_READ_REQ                  0x1F
#define INFO_LONG_DATA_READ_RESP                 0x20
#define INFO_LONG_DATA_WRITE_REQ                 0x21
#define INFO_LONG_DATA_WRITE_RESP                0x22
#define INFO_WLAN_INFO_READ_REQ                  0x23
#define INFO_WLAN_INFO_READ_RESP                 0x24
#define INFO_IP_PASSTHROUGH_READ_REQ             0x25
#define INFO_IP_PASSTHROUGH_READ_RESP            0x26
#define INFO_WLAN_INFO_WRITE_REQ                 0x27
#define INFO_WLAN_INFO_WRITE_RESP                0x28
#define INFO_PP_DATA_READ_REQ                    0x29
#define INFO_PP_DATA_READ_RESP                   0x2A
#define INFO_PP_DATA_WRITE_REQ                   0x2B
#define INFO_PP_DATA_WRITE_RESP                  0x2C
#define INFO_PP_DATA_IND                         0x2D
#define INFO_PRODUCT_RAT_BAND_READ_REQ           0x2E
#define INFO_PRODUCT_RAT_BAND_READ_RESP          0x2F
#define INFO_PRODUCT_RAT_BAND_WRITE_REQ          0x30
#define INFO_PRODUCT_RAT_BAND_WRITE_RESP         0x31
#define INFO_STARTUP_REASON_READ_REQ             0x32
#define INFO_STARTUP_REASON_READ_RESP            0x33
#define INFO_RESET_REASON_READ_REQ               0x34
#define INFO_RESET_REASON_READ_RESP              0x35
#define INFO_SERIAL_NUMBER_WRITE_REQ             0x36
#define INFO_SERIAL_NUMBER_WRITE_RESP            0x37
#define INFO_LIFETIME_READ_REQ                   0x38
#define INFO_LIFETIME_READ_RESP                  0x39

/* ----------------------------------------------------------------------- */
/* Subblock ID's                                                           */
/* ----------------------------------------------------------------------- */

#define INFO_SB_SN_IMEI_PLAIN                    0x41
#define INFO_SB_SN_IMEI2_PLAIN                   0x7A
#define INFO_SB_SN_IMEI_SPARE_TO_NET             0x42
#define INFO_SB_SN_IMEI2_SPARE_TO_NET            0x7B
#define INFO_SB_SN_IMEI2_SV_TO_NET               0x7C
#define INFO_SB_SN_ESN_PLAIN                     0x44
#define INFO_SB_SN_ESN_HEX                       0x45
#define INFO_SB_SN_ESNX_PLAIN                    0x56
#define INFO_SB_SN_ESNX_HEX                      0x5A
#define INFO_SB_SN_MEID_HEX                      0x61
#define INFO_SB_SN_MEID_HEX_ASCII                0x62
#define INFO_SB_SN_MEID_PLAIN                    0x80
#define INFO_SB_SN_PDC                           0x46
#define INFO_SB_SN_BATTERY                       0x7D
#define INFO_SB_MCUSW_VERSION                    0x48
#define INFO_SB_BT_MCM_VERSION                   0x5B
#define INFO_SB_HW_VERSION                       0x49
#define INFO_SB_PCI_VERSION                      0x4A
#define INFO_SB_UEM_VERSION                      0x4B
#define INFO_SB_UPP_VERSION                      0x4C
#define INFO_SB_RFIC_VERSION                     0x54
#define INFO_SB_BOM_ID                           0x77
#define INFO_SB_DSP_VERSION                      0x55
#define INFO_SB_ADSP_VERSION                     0x5F
#define INFO_SB_ADSP_DEVICE_ID                   0x65
#define INFO_SB_ADSP_REVISION_ID                 0x66
#define INFO_SB_VERSION_BY_DSP_CORE_SRV          0x64
#define INFO_SB_ROFS_FOTAID                      0x58
#define INFO_SB_PP                               0x47
#define INFO_SB_PP_DATA                          0x74
#define INFO_SB_SIM_SWITCH                       0x85
#define INFO_SB_MEMORY                           0x86
#define INFO_SB_PMU                              0x87
#define INFO_SB_WLAN                             0x88
#define INFO_SB_GPS                              0x89
#define INFO_SB_CHARGER_DET                      0x8A
#define INFO_SB_PRODUCTION_SN                    0x4D
#define INFO_SB_LONG_PRODUCTION_SN               0x59
#define INFO_SB_PRODUCT_CODE                     0x4E
#define INFO_SB_BASIC_PRODUCT_CODE               0x4F
#define INFO_SB_MODULE_CODE                      0x50
#define INFO_SB_FLASH_CODE                       0x51
#define INFO_SB_ORDER_NUMBER                     0x52
#define INFO_SB_PRODUCT_SPECIFIC_DATA            0x53
#define INFO_SB_ATO                              0x5C
#define INFO_SB_SN_DEFAULT                       0x5D
#define INFO_SB_SN_DEFAULT_TYPE                  0x5E
#define INFO_SB_BAND_CS_TYPE                     0x67
#define INFO_SB_SN_DEFAULT_PLAIN                 0x63
#define INFO_SB_PRODUCT_TYPE_CS_SEC              0x03
#define INFO_SB_PRODUCT_TYPE_CS                  0x01
#define INFO_SB_PRODUCT_TYPE_HW_INFO             0x02
#define INFO_SB_PRODUCT_INFO_NAME                0x01
#define INFO_SB_PRODUCT_INFO_CATEGORY            0x02
#define INFO_SB_PRODUCT_INFO_XID                 0x03
#define INFO_SB_PRODUCT_INFO_DEV_NAME            0x04
#define INFO_SB_PRODUCT_INFO_COMP01              0x05
#define INFO_SB_PRODUCT_INFO_NAME_COMPRESSED     0x06
#define INFO_SB_PRODUCT_INFO_MANUFACTURER        0x07
#define INFO_SB_PRODUCT_INFO_XCVR_ID             0x08
#define INFO_SB_PRODUCT_INFO_NUM_ID              0x09
#define INFO_SB_PRODUCT_INFO_TYPE_ID             0x0A
#define INFO_SB_USB_VENDOR_ID                    0x0B
#define INFO_SB_USB_MASS_ID                      0x0C
#define INFO_SB_USB_NOKIA_ID                     0x0D
#define INFO_SB_USB_SICD_ID                      0x0E
#define INFO_SB_USB_RNDIS_ID                     0x10
#define INFO_SB_USB_NCM_ID                       0x11
#define INFO_SB_USB_NSM_ID                       0x13
#define INFO_SB_USB_NSM_LOCAL_TEST_ID            0x14
#define INFO_SB_SIM_SLOTS                        0x12
#define INFO_SB_BT_PID                           0x0F
#define INFO_SB_BT_ID_PLAIN                      0x01
#define INFO_SB_BT_ID_SEC                        0x02
#define INFO_SB_WT_ORIG_SN_INFO                  0x01
#define INFO_SB_WT_ORIG_MAN_MONTH_YEAR           0x02
#define INFO_SB_WT_OWN_MAN_MONTH_YEAR            0x03
#define INFO_SB_WT_REPAIR_MONTH_YEAR             0x04
#define INFO_SB_WT_PURCH_MONTH_YEAR              0x05
#define INFO_SB_WT_WIS                           0x06
#define INFO_SB_WT_RPF                           0x07
#define INFO_SB_EM_ASIC                          0x6C
#define INFO_SB_RETU_VER                         0x6C
#define INFO_SB_TAHVO_VER                        0x6D
#define INFO_SB_RAP_VERSION                      0x73
#define INFO_SB_SYSTEM_ASIC                      0x73
#define INFO_SB_PRODUCT_VARIANT_NUMBER           0x60
#define INFO_SB_GAZOO                            0x76
#define INFO_SB_CWS_CHIP_ID                      0x78
#define INFO_SB_DBI_ID                           0x7F
#define INFO_SB_HW_DRIVER_VERSION                0x81
#define INFO_SB_MCU_SPEED_VERSION                0x82
#define INFO_SB_SW_VERSION                       0x8B

/* ----------------------------------------------------------------------- */
/* Shared file inclusion                                                   */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0)
#include "info_shared_isi.h"
#endif /* INFO_ISI_MIN_VERSION(1,0) */


/* ----------------------------------------------------------------------- */
/* Sequence: CS_TYPE_SEC - Versions 001.000 - 003.000                      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(3,0)

typedef struct
    {
    uint32  cs_type1;     /* Values from the bitmask table INFO_CS_TYPE_1 */
    uint32  cs_type2;
    uint8   filler[6];
    uint16  checksum;
    } CS_TYPE_SEC;

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(3,0) */


/* ----------------------------------------------------------------------- */
/* Sequence: CS_TYPE_SEC - Versions 003.000 - 007.000                      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(3,0) && !INFO_ISI_MIN_VERSION(7,0)

typedef struct
    {
    uint32  cs_type1;     /* Values from the bitmask table INFO_CS_TYPE_1 */
    uint32  cs_type2;
    char    sw_id[INFO_SW_ID_LEN];
    /* Check Sum value is calculated from plain data(CS Type 1 + CS Type 2 +
       sw id)before encryption(TDS-6)
    */
    uint16  checksum;
    } CS_TYPE_SEC;

#endif /* INFO_ISI_MIN_VERSION(3,0) && !INFO_ISI_MIN_VERSION(7,0) */


/* ----------------------------------------------------------------------- */
/* Sequence: CS_TYPE_SEC - Versions 007.000 - 008.000                      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(7,0) && !INFO_ISI_MIN_VERSION(8,0)

typedef struct
    {
    uint32  cs_type1;     /* Values from the bitmask table INFO_CS_TYPE_1 */
    uint32  cs_type2;
    char    sw_id[INFO_SW_ID_LEN];
    /* Check Sum value is calculated from plain data(CS Type 1 + CS Type 2 +
       sw id)before encryption(TDS-6)
    */
    uint16  checksum;
    uint8   reserved[4];  /* Reserved for future use */
    /* 1024 bits RSA signed certificate on SHA-1 */
    uint8   rsa_signature[128];
    } CS_TYPE_SEC;

#endif /* INFO_ISI_MIN_VERSION(7,0) && !INFO_ISI_MIN_VERSION(8,0) */


/* ----------------------------------------------------------------------- */
/* Sequence: CS_TYPE_SEC - Valid from version 008.000                      */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(8,0)

typedef struct
    {
    uint32  cs_type1;     /* Values from the bitmask table INFO_CS_TYPE_1 */
    uint32  cs_type2;
    char    sw_id[INFO_SW_ID_LEN];
    /* Check Sum value is calculated from plain data(CS Type 1 + CS Type 2 +
       sw id)before encryption(TDS-6)
    */
    uint16  checksum;
    } CS_TYPE_SEC;

#endif /* INFO_ISI_MIN_VERSION(8,0) */


/* ----------------------------------------------------------------------- */
/* Sequence: INFO_BT_ID_SEC - Valid from version 002.005                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    /* Sequence:
       LSB:| LAP | UAP | NAP |:MSB
    */
    uint8   bt_id_enc[6];
    uint16  checksum;
    } INFO_BT_ID_SEC;

#define SIZEOF_INFO_BT_ID_SEC   sizeof(INFO_BT_ID_SEC)


/* ----------------------------------------------------------------------- */
/* Sequence: INFO_IPP_MACS - Valid from version 004.015                    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   ipp_mac_1[6]; /* Hex string */
    uint8   ipp_mac_2[6]; /* Hex string */
    } INFO_IPP_MACS;

#define SIZEOF_INFO_IPP_MACS   sizeof(INFO_IPP_MACS)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_IMEI_PLAIN - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    /* Type Allocation Code, 8 bytes
       Serial Number, 6 bytes
       Check Digit, 1 byte
       String terminator, 1 byte
    */
    char    imei_plain_u8[INFO_SB_SN_IMEI_PLAIN_STR_LEN];
    } INFO_SB_SN_IMEI_PLAIN_t;

#define SIZEOF_INFO_SB_SN_IMEI_PLAIN   sizeof(INFO_SB_SN_IMEI_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_IMEI2_PLAIN - Valid from version 008.011           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    /* Type Allocation Code, 8 bytes
       Serial Number, 6 bytes
       Check Digit, 1 byte
       String terminator, 1 byte
    */
    char    imei2_plain_u8[INFO_SB_SN_IMEI2_PLAIN_STR_LEN];
    } INFO_SB_SN_IMEI2_PLAIN_t;

#define SIZEOF_INFO_SB_SN_IMEI2_PLAIN   sizeof(INFO_SB_SN_IMEI2_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_IMEI_SPARE_TO_NET - Valid from version 001.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   imei_spare_u8[INFO_SB_SN_IMEI_SPARE_TO_NET_STR_LEN];
    } INFO_SB_SN_IMEI_SPARE_TO_NET_t;

#define SIZEOF_INFO_SB_SN_IMEI_SPARE_TO_NET   \
        sizeof(INFO_SB_SN_IMEI_SPARE_TO_NET_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_IMEI2_SPARE_TO_NET - Valid from version 008.011    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   imei2_spare_u8[INFO_SB_SN_IMEI2_SPARE_TO_NET_STR_LEN];
    } INFO_SB_SN_IMEI2_SPARE_TO_NET_t;

#define SIZEOF_INFO_SB_SN_IMEI2_SPARE_TO_NET   \
        sizeof(INFO_SB_SN_IMEI2_SPARE_TO_NET_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_IMEI2_SV_TO_NET - Valid from version 008.011       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   imei2_sv_u8[INFO_SB_SN_IMEI2_SV_TO_NET_STR_LEN];
    uint8   fillertoo[3]; /* 0 */
    } INFO_SB_SN_IMEI2_SV_TO_NET_t;

#define SIZEOF_INFO_SB_SN_IMEI2_SV_TO_NET   \
        sizeof(INFO_SB_SN_IMEI2_SV_TO_NET_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_ESN_PLAIN - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    /* Manufacturer's Id, 3 bytes
       Serial Number, 8 bytes
       String terminator, 1 byte
    */
    char    esn_plain_u8[INFO_SB_SN_ESN_PLAIN_STR_LEN];
    } INFO_SB_SN_ESN_PLAIN_t;

#define SIZEOF_INFO_SB_SN_ESN_PLAIN   sizeof(INFO_SB_SN_ESN_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_ESN_HEX - Valid from version 001.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   data_len;
    uint8   esn_hex_c8[INFO_SB_SN_ESN_HEX_DATA_LEN];
    } INFO_SB_SN_ESN_HEX_t;

#define SIZEOF_INFO_SB_SN_ESN_HEX   sizeof(INFO_SB_SN_ESN_HEX_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_ESNX_PLAIN - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   esnx_str_len;
    /* Extended ESN Reserved, 3 bytes
       Expanded Manufacturer's Code, 5 bytes
       String terminator, 1 byte
    */
    char    esnx_plain[INFO_SB_SN_ESNX_PLAIN_STR_LEN];
    uint8   fillertoo[3]; /* 0 */
    } INFO_SB_SN_ESNX_PLAIN_t;

#define SIZEOF_INFO_SB_SN_ESNX_PLAIN   sizeof(INFO_SB_SN_ESNX_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_ESNX_HEX - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   data_len;
    uint8   esnx_hex_c8[INFO_SB_SN_ESNX_HEX_DATA_LEN];
    uint8   fillertoo;    /* 0 */
    } INFO_SB_SN_ESNX_HEX_t;

#define SIZEOF_INFO_SB_SN_ESNX_HEX   sizeof(INFO_SB_SN_ESNX_HEX_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_MEID_HEX - Valid from version 004.012              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler[2];
    uint8   meid_hex[INFO_SN_RAW_MEID_LEN];
    uint8   fillertoo;
    } INFO_SB_SN_MEID_HEX_t;

#define SIZEOF_INFO_SB_SN_MEID_HEX   sizeof(INFO_SB_SN_MEID_HEX_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_MEID_HEX_ASCII - Valid from version 004.012        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler[2];
    char    meid_hex_ascii[INFO_SN_MEID_HEX_ASCII_LEN];
    uint8   fillertoo;
    } INFO_SB_SN_MEID_HEX_ASCII_t;

#define SIZEOF_INFO_SB_SN_MEID_HEX_ASCII   \
        sizeof(INFO_SB_SN_MEID_HEX_ASCII_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_MEID_PLAIN - Valid from version 004.012            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler[2];
    uint8   meid_plain[INFO_SN_MEID_PLAIN_LEN];
    } INFO_SB_SN_MEID_PLAIN_t;

#define SIZEOF_INFO_SB_SN_MEID_PLAIN   sizeof(INFO_SB_SN_MEID_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_PDC - Valid from version 001.000                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   pdc_data_len;
    char    pdc_c8[INFO_SB_SN_PDC_DATA_LEN];
    } INFO_SB_SN_PDC_t;

#define SIZEOF_INFO_SB_SN_PDC   sizeof(INFO_SB_SN_PDC_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_BATTERY - Valid from version 008.013               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   battery_data_len;
    char    battery_c8[INFO_SB_SN_BATTERY_DATA_LEN];
    uint8   filler2;
    } INFO_SB_SN_BATTERY_t;

#define SIZEOF_INFO_SB_SN_BATTERY   sizeof(INFO_SB_SN_BATTERY_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_MCUSW_VERSION - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   mcusw_versn_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_MCUSW_VERSION_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BT_MCM_VERSION - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   mcusw_versn_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_BT_MCM_VERSION_T;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_HW_VERSION - Valid from version 001.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    char    hw_versn_str_c8[INFO_SB_HW_VERSION_STR_LEN];
    uint8   fillertoo[3]; /* 0 */
    } INFO_SB_HW_VERSION_t;

#define SIZEOF_INFO_SB_HW_VERSION   sizeof(INFO_SB_HW_VERSION_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PCI_VERSION - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    char    pci_versn_str_c8[INFO_SB_PCI_VERSION_STR_LEN];
    uint8   fillertoo[3]; /* 0 */
    } INFO_SB_PCI_VERSION_t;

#define SIZEOF_INFO_SB_PCI_VERSION   sizeof(INFO_SB_PCI_VERSION_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_UEM_VERSION - Versions 001.000 - 008.026              */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   uem_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_UEM_VERSION_t;

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_UPP_VERSION - Versions 001.000 - 008.026              */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   upp_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_UPP_VERSION_t;

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_RFIC_VERSION - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   rfic_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_RFIC_VERSION_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BOM_ID - Valid from version 008.004                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   bom_id_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_BOM_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_DSP_VERSION - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   dsp_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_DSP_VERSION_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ADSP_VERSION - Versions 001.000 - 008.026             */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   prod_id;      /* Project/product identification */
    uint8   str_len; /* Max. string length is 64 bytes + 1 NULL terminator */
    uint8   adsp_versn_str[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_ADSP_VERSION_t;

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ADSP_DEVICE_ID - Versions 002.001 - 008.026           */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   prod_id;      /* Project/product identification */
    uint8   str_len; /* Max. string length is 64 bytes + 1 NULL terminator */
    uint8   adsp_versn_str[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_ADSP_DEVICE_ID_t;

#endif /* INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ADSP_REVISION_ID - Versions 002.001 - 008.026         */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   prod_id;      /* Project/product identification */
    uint8   str_len; /* Max. string length is 64 bytes + 1 NULL terminator */
    uint8   adsp_versn_str[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_ADSP_REVISION_ID_t;

#endif /* INFO_ISI_MIN_VERSION(2,1) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_VERSION_BY_DSP_CORE_SRV - Valid from version 002.000  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint16  target;       /* INFO_DSP, INFO_RFIC, INFO_ADSP, ... */
    uint8   prod_id;      /* Project/product identification */
    uint8   str_len;
    uint8   ver_by_dsp_core_srv[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_VERSION_BY_DSP_CORE_SRV_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ROFS_FOTAID - Valid from version 009.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   rofs_fota_id[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_ROFS_FOTAID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PP - Valid from version 001.000                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   customer_id;
    uint8   str_len;
    /* xxxxxxxx--------  PP Feature
       --------xxxxxxxx  PP Value
    */
    uint16  product_profile[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_PP_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PP_DATA - Valid from version 004.017                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   filler;
    uint16  sub_block_len;
    uint8   customer_id;
    uint8   filler2;
    uint16  pp_fea_cnt;
    /* xxxxxxxxxxxxxxxx----------------  PP Feature Number
       ----------------xxxxxxxxxxxxxxxx  PP Feature Value
    */
    uint32  pp_feaval[INFO_ANY_SIZE];
    } INFO_SB_PP_DATA_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SIM_SWITCH - Valid from version 008.026               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   sim_switch_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_SIM_SWITCH_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_MEMORY - Valid from version 008.026                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   memory_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_MEMORY_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PMU - Valid from version 008.026                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   pmu_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_PMU_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WLAN - Valid from version 008.026                     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   wlan_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_WLAN_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_GPS - Valid from version 008.026                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   gps_versn_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_GPS_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_CHARGER_DET - Valid from version 008.026              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   charger_det_str_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_CHARGER_DET_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCTION_SN - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    char    prod_sn_c8[INFO_SB_PRODUCTION_SN_STR_LEN];
    } INFO_SB_PRODUCTION_SN_t;

#define SIZEOF_INFO_SB_PRODUCTION_SN   (4*sizeof(uint8) + \
        INFO_SB_PRODUCTION_SN_STR_LEN*sizeof(char))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_LONG_PRODUCTION_SN - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    char    prod_long_sn_c8[INFO_SB_LONG_PRODUCTION_SN_STR_LEN];
    } INFO_SB_LONG_PRODUCTION_SN_t;

#define SIZEOF_INFO_SB_LONG_PRODUCTION_SN   (4*sizeof(uint8) + \
        INFO_SB_LONG_PRODUCTION_SN_STR_LEN*sizeof(char))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_CODE - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    uint8   product_code_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_PRODUCT_CODE_t;

#define SIZEOF_INFO_SB_PRODUCT_CODE   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BASIC_PRODUCT_CODE - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    uint8   basic_product_code_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_BASIC_PRODUCT_CODE_t;

#define SIZEOF_INFO_SB_BASIC_PRODUCT_CODE   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_MODULE_CODE - Valid from version 001.000              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    uint8   module_code_c8[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_MODULE_CODE_t;

#define SIZEOF_INFO_SB_MODULE_CODE   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_FLASH_CODE - Valid from version 001.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    char    flash_code_c8[INFO_SB_FLASH_CODE_STR_LEN];
    uint8   fillertoo[2]; /* 0 */
    } INFO_SB_FLASH_CODE_t;

#define SIZEOF_INFO_SB_FLASH_CODE   sizeof(INFO_SB_FLASH_CODE_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ORDER_NUMBER - Valid from version 001.000             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Default string length is 1 + NULL terminator */
    char    order_number_c8[INFO_SB_ORDER_NUMBER_STR_LEN];
    } INFO_SB_ORDER_NUMBER_t;

#define SIZEOF_INFO_SB_ORDER_NUMBER   sizeof(INFO_SB_ORDER_NUMBER_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_SPECIFIC_DATA - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   stest_status;
    uint8   project;      /* PROJECT (defined in product.h) */
    uint32  cellular_type_u32; /* PRODUCT_CS_TYPE  (from product.h or PMM) */
    uint8   customer;     /* PRODUCT_CUSTOMER */
    uint8   revision_level; /* CLM_REVISION_LEVEL */
    uint8   fillertoo[2];
    } INFO_SB_PRODUCT_SPECIFIC_DATA_t;

#define SIZEOF_INFO_SB_PRODUCT_SPECIFIC_DATA   \
        sizeof(INFO_SB_PRODUCT_SPECIFIC_DATA_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_ATO - Valid from version 001.000                      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   ato_data[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_ATO_T;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_DEFAULT - Valid from version 001.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* Length of default serial number */
    uint8   default_sn[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_SN_DEFAULT_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_DEFAULT_TYPE - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   default_sn_type; /* Type of default serial number */
    uint8   filler;       /* 0 */
    } INFO_SB_SN_DEFAULT_TYPE_t;

#define SIZEOF_INFO_SB_SN_DEFAULT_TYPE   sizeof(INFO_SB_SN_DEFAULT_TYPE_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BAND_CS_TYPE - Valid from version 002.004             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler[2];    /* 0 */
    uint32  info_band_cs_type; /* See file global.h */
    } INFO_SB_BAND_CS_TYPE_t;

#define SIZEOF_SB_BAND_CS_TYPE   sizeof(INFO_SB_BAND_CS_TYPE_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SN_DEFAULT_PLAIN - Valid from version 002.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   type_id;      /* Type of default serial number */
    uint8   str_len;      /* Length of default serial number */
    uint8   default_sn[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_SN_DEFAULT_PLAIN_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_TYPE_CS_SEC - Valid from version 001.000      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler1;      /* 0 */
    uint8   filler2;      /* 0 */
    CS_TYPE_SEC cs_type_sec; /* Encrypted with TDS6 */
    } INFO_SB_PRODUCT_TYPE_CS_SEC_t;

#define SIZEOF_INFO_SB_PRODUCT_TYPE_CS_SEC   \
        sizeof(INFO_SB_PRODUCT_TYPE_CS_SEC_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_TYPE_CS - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler1;      /* 0 */
    uint8   filler2;      /* 0 */
    CS_TYPE_SEC cs_type_sec; /* Decrypted by info server */
    } INFO_SB_PRODUCT_TYPE_CS_t;

#define SIZEOF_INFO_SB_PRODUCT_TYPE_CS   sizeof(INFO_SB_PRODUCT_TYPE_CS_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_TYPE_HW_INFO - Valid from version 001.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler1;      /* 0 */
    uint8   filler2;      /* 0 */
    uint8   hw_info[22];  /* Data needed by TDS6 /15/ */
    uint8   filler3;      /* 0 */
    uint8   filler4;      /* 0 */
    } INFO_SB_PRODUCT_TYPE_HW_INFO_t;

#define SIZEOF_INFO_SB_PRODUCT_TYPE_HW_INFO   \
        sizeof(INFO_SB_PRODUCT_TYPE_HW_INFO_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_NAME - Valid from version 001.000        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   prod_info_str_c8[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_NAME_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_CATEGORY - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_CATEGORY_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_XID - Valid from version 001.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_XID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_DEV_NAME - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_DEV_NAME_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_COMP01 - Valid from version 001.000      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_COMP01_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_NAME_COMPRESSED - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_NAME_COMPRESSED_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_MANUFACTURER - Valid from version 001.000 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_MANUFACTURER_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_XCVR_ID - Valid from version 004.005     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_XCVR_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_NUM_ID - Valid from version 004.005      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_NUM_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_INFO_TYPE_ID - Valid from version 004.005     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_PRODUCT_TYPE_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_VENDOR_ID - Valid from version 004.010            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* USB Vendor ID is hex string */
    } INFO_SB_USB_VENDOR_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_MASS_ID - Valid from version 004.010              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* USB Mass ID is hex string */
    } INFO_SB_USB_MASS_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_NOKIA_ID - Valid from version 004.010             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* USB Nokia ID is hex string */
    } INFO_SB_USB_NOKIA_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_SICD_ID - Valid from version 004.014              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* USB SICD ID is hex string */
    } INFO_SB_USB_SICD_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_RNDIS_ID - Valid from version 008.002             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* USB RNDIS ID is hex string */
    } INFO_SB_USB_RNDIS_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_NCM_ID - Valid from version 008.017               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    /* USB NCM (Network Control Model) ID is hex string */
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_USB_NCM_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_NSM_ID - Valid from version 008.028               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    /* USB NSM (Normal Service Model) ID is hex string */
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_USB_NSM_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_USB_NSM_LOCAL_TEST_ID - Valid from version 008.028    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    /* USB NSM_LOCAL_TEST (Test Service Model) ID is hex string */
    uint8   string[INFO_ANY_SIZE];
    } INFO_SB_USB_NSM_LOCAL_TEST_ID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SIM_SLOTS - Valid from version 008.027                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   sim_slots;
    uint8   filler;
    } INFO_SB_SIM_SLOTS_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BT_PID - Valid from version 005.002                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   str_len;
    uint8   string[INFO_ANY_SIZE]; /* BT PID is hex string */
    } INFO_SB_BT_PID_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BT_ID_PLAIN - Valid from version 002.005              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    /* Sequence:
       LSB:| LAP | UAP | NAP |:MSB
    */
    uint8   bt_id_plain[6];
    uint8   fill1[2];
    } INFO_SB_BT_ID_PLAIN_t;

#define SIZEOF_INFO_SB_BT_ID_PLAIN   sizeof(INFO_SB_BT_ID_PLAIN_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_BT_ID_SEC - Valid from version 002.005                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   fill1[2];     /* 0 */
    INFO_BT_ID_SEC bt_id_sec; /* Encrypted data from client */
    } INFO_SB_BT_ID_SEC_t;

#define SIZEOF_INFO_SB_BT_ID_SEC   sizeof(INFO_SB_BT_ID_SEC_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_ORIG_SN_INFO - Valid from version 003.001          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    /* Values from the constant table INFO_WT_SN */
    uint8   serial_number_type;
    /* Original serial number in ASCII format */
    char    sn[INFO_WT_SERIAL_NUMBER_LENGTH];
    } INFO_SB_WT_ORIG_SN_INFO_t;

#define SIZEOF_INFO_SB_WT_ORIG_SN_INFO   sizeof(INFO_SB_WT_ORIG_SN_INFO_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_ORIG_MAN_MONTH_YEAR - Valid from version 003.001   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   fill1;
    uint8   month;
    uint16  year;
    uint8   fill2[2];
    } INFO_SB_WT_ORIG_MAN_MONTH_YEAR_t;

#define SIZEOF_INFO_SB_WT_ORIG_MAN_MONTH_YEAR   \
        sizeof(INFO_SB_WT_ORIG_MAN_MONTH_YEAR_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_OWN_MAN_MONTH_YEAR - Valid from version 003.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   fill1;
    uint8   month;
    uint16  year;
    uint8   fill2[2];
    } INFO_SB_WT_OWN_MAN_MONTH_YEAR_t;

#define SIZEOF_INFO_SB_WT_OWN_MAN_MONTH_YEAR   \
        sizeof(INFO_SB_WT_OWN_MAN_MONTH_YEAR_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_REPAIR_MONTH_YEAR - Valid from version 003.001     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   fill1;
    uint8   month;
    uint16  year;
    uint8   fill2[2];
    } INFO_SB_WT_REPAIR_MONTH_YEAR_t;

#define SIZEOF_INFO_SB_WT_REPAIR_MONTH_YEAR   \
        sizeof(INFO_SB_WT_REPAIR_MONTH_YEAR_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_PURCH_MONTH_YEAR - Valid from version 003.001      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   fill1;
    uint8   month;
    uint16  year;
    uint8   state;        /* Values from the constant table INFO_WT_STATE */
    uint8   fill2;
    } INFO_SB_WT_PURCH_MONTH_YEAR_t;

#define SIZEOF_INFO_SB_WT_PURCH_MONTH_YEAR   \
        sizeof(INFO_SB_WT_PURCH_MONTH_YEAR_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_WIS - Valid from version 003.001                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    uint8   wis;          /* Values from the constant table INFO_WT_STATUS */
    } INFO_SB_WT_WIS_t;

#define SIZEOF_INFO_SB_WT_WIS   sizeof(INFO_SB_WT_WIS_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_WT_RPF - Valid from version 004.011                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler[2];
    char    rpf[INFO_WT_RPF_LEN];
    } INFO_SB_WT_RPF_t;

#define SIZEOF_INFO_SB_WT_RPF   sizeof(INFO_SB_WT_RPF_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_EM_ASIC - Valid from version 008.026                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* str_len = str + null byte */
    uint8   hw_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_EM_ASIC_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_RETU_VER - Versions 004.003 - 008.026                 */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* str_len = str + null byte */
    uint8   hw_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_RETU_VER_t;

#endif /* INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_TAHVO_VER - Versions 004.003 - 008.026                */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* str_len = str + null byte */
    uint8   hw_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_TAHVO_VER_t;

#endif /* INFO_ISI_MIN_VERSION(4,3) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_RAP_VERSION - Versions 004.008 - 008.026              */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   rap_type;     /* Values from the constant table INFO_RAP_TYPE */
    uint8   str_len;      /* str_len = str + null byte */
    uint8   rap_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_RAP_VERSION_t;

#endif /* INFO_ISI_MIN_VERSION(4,8) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SYSTEM_ASIC - Valid from version 008.026              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;      /* str_len = str + null byte */
    uint8   system_asic_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_SYSTEM_ASIC_t;


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_PRODUCT_VARIANT_NUMBER - Valid from version 005.005   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   customer;
    uint8   revision_level;
    } INFO_SB_PRODUCT_VARIANT_NBR_t;

#define SIZEOF_INFO_SB_PRODUCT_VARIANT_NBR   \
        sizeof(INFO_SB_PRODUCT_VARIANT_NBR_t)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_GAZOO - Versions 005.012 - 008.026                    */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(5,12) && !INFO_ISI_MIN_VERSION(8,26)

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   version_major;
    uint8   version_minor;
    uint8   version_spare;
    uint8   filler[3];
    } INFO_SB_GAZOO_STR;

#define SIZE_INFO_SB_GAZOO_STR   sizeof(INFO_SB_GAZOO_STR)

#endif /* INFO_ISI_MIN_VERSION(5,12) && !INFO_ISI_MIN_VERSION(8,26) */


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_CWS_CHIP_ID - Valid from version 008.006              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   version_major;
    uint8   filler;
    } INFO_SB_CWS_CHIP_ID_STR;

#define SIZE_INFO_SB_CWS_CHIP_ID_STR   sizeof(INFO_SB_CWS_CHIP_ID_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_DBI_ID - Valid from version 008.016                   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    /* Values from the constant table INFO_DBI_BATTERY_CHEMISTRY */
    uint8   dbi_battery_chemistry;
    uint8   filler;
    uint16  target_voltage;
    uint16  max_current;
    uint16  capacity_nominal;
    /* Values from the constant table INFO_DBI_BATTERY_VENDOR */
    uint8   dbi_battery_vendor;
    uint8   battery_vendor_chemistry_variant;
    uint8   str_len;
    uint8   battery_designator[INFO_ANY_SIZE];
    } INFO_SB_DBI_ID_STR;

#define SIZE_INFO_SB_DBI_ID_STR   (7*sizeof(uint8) + 3*sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_HW_DRIVER_VERSION - Valid from version 008.022        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint16  filler;
    uint32  version;
    } INFO_SB_HW_DRIVER_VERSION_STR;

#define SIZE_INFO_SB_HW_DRIVER_VERSION_STR   \
        sizeof(INFO_SB_HW_DRIVER_VERSION_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_MCU_SPEED_VERSION - Valid from version 008.023        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;
    /* Values from the constant table INFO_MCU_SPEED */
    uint8   mcu_speed_version;
    } INFO_SB_MCU_SPEED_VERSION_STR;

#define SIZE_INFO_SB_MCU_SPEED_VERSION_STR   \
        sizeof(INFO_SB_MCU_SPEED_VERSION_STR)


/* ----------------------------------------------------------------------- */
/* Subblock: INFO_SB_SW_VERSION - Valid from version 009.000               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   sub_block_id;
    uint8   sub_block_len;
    uint8   filler;       /* 0 */
    uint8   str_len;
    uint8   sw_version[INFO_ANY_SIZE];
    /* 0 */
    } INFO_SB_SW_VERSION_t;


/* ----------------------------------------------------------------------- */
/* Message: INFO_SERIAL_NUMBER_READ_REQ - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table INFO_SN_TARGET_IDENTIFIER */
    uint8   target;
    } INFO_SERIAL_NUMBER_READ_REQ_t;

#define SIZEOF_INFO_SERIAL_NUMBER_READ_REQ   \
        sizeof(INFO_SERIAL_NUMBER_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_SERIAL_NUMBER_READ_RESP - Valid from version 001.000      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_SN_BATTERY
       INFO_SB_SN_DEFAULT
       INFO_SB_SN_DEFAULT_PLAIN
       INFO_SB_SN_DEFAULT_TYPE
       INFO_SB_SN_ESNX_HEX
       INFO_SB_SN_ESNX_PLAIN
       INFO_SB_SN_ESN_HEX
       INFO_SB_SN_ESN_PLAIN
       INFO_SB_SN_IMEI2_PLAIN
       INFO_SB_SN_IMEI2_SPARE_TO_NET
       INFO_SB_SN_IMEI2_SV_TO_NET
       INFO_SB_SN_IMEI_PLAIN
       INFO_SB_SN_IMEI_SPARE_TO_NET
       INFO_SB_SN_IMEI_SV_TO_NET
       INFO_SB_SN_MEID_HEX
       INFO_SB_SN_MEID_HEX_ASCII
       INFO_SB_SN_MEID_PLAIN
       INFO_SB_SN_PDC
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_SERIAL_NUMBER_READ_RESP_t;

#define SIZEOF_INFO_SERIAL_NUMBER_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_SERIAL_NUMBER_WRITE_REQ - Valid from version 008.018      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_SN_BATTERY
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_SERIAL_NUMBER_WRITE_REQ_t;

#define SIZEOF_INFO_SERIAL_NUMBER_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_SERIAL_NUMBER_WRITE_RESP - Valid from version 008.018     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_SERIAL_NUMBER_WRITE_RESP_t;

#define SIZEOF_INFO_SERIAL_NUMBER_WRITE_RESP   \
        sizeof(INFO_SERIAL_NUMBER_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_CUSTOMER_DEFAULTS_REQ - Valid from version 001.000     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   customer_id;
    } INFO_PP_CUSTOMER_DEFAULTS_REQ_t;

#define SIZEOF_INFO_PP_CUSTOMER_DEFAULTS_REQ   \
        sizeof(INFO_PP_CUSTOMER_DEFAULTS_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_CUSTOMER_DEFAULTS_RESP - Valid from version 001.000    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_PP_CUSTOMER_DEFAULTS_RESP_t;

#define SIZEOF_INFO_PP_CUSTOMER_DEFAULTS_RESP   \
        sizeof(INFO_PP_CUSTOMER_DEFAULTS_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_READ_REQ - Valid from version 001.000                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;      /* Values from the constant table INFO_BATCH_TYPE */
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_READ_REQ_t;

#define SIZEOF_INFO_PP_READ_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_READ_RESP - Valid from version 001.000                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_READ_RESP_t;

#define SIZEOF_INFO_PP_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_WRITE_REQ - Valid from version 001.000                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_WRITE_REQ_t;

#define SIZEOF_INFO_PP_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_WRITE_RESP - Valid from version 001.000                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_PP_WRITE_RESP_t;

#define SIZEOF_INFO_PP_WRITE_RESP   sizeof(INFO_PP_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_IND - Valid from version 001.000                       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_IND_t;

#define SIZEOF_INFO_PP_IND   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_DATA_READ_REQ - Valid from version 004.017             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;      /* Values from the constant table INFO_BATCH_TYPE */
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP_DATA
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_DATA_READ_REQ_t;

#define SIZEOF_INFO_PP_DATA_READ_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_DATA_READ_RESP - Valid from version 004.017            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP_DATA
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_DATA_READ_RESP_t;

#define SIZEOF_INFO_PP_DATA_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_DATA_WRITE_REQ - Valid from version 004.017            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP_DATA
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_DATA_WRITE_REQ_t;

#define SIZEOF_INFO_PP_DATA_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_DATA_WRITE_RESP - Valid from version 004.017           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_PP_DATA_WRITE_RESP_t;

#define SIZEOF_INFO_PP_DATA_WRITE_RESP   sizeof(INFO_PP_DATA_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PP_DATA_IND - Valid from version 004.017                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PP_DATA
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PP_DATA_IND_t;

#define SIZEOF_INFO_PP_DATA_IND   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_VERSION_READ_REQ - Versions 001.000 - 004.003             */
/* ----------------------------------------------------------------------- */

#if INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(4,3)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  target;  /* Values from the bitmask table INFO_VERSION_TARGETS */
    } INFO_VERSION_READ_REQ_t;

#define SIZEOF_INFO_VERSION_READ_REQ   sizeof(INFO_VERSION_READ_REQ_t)

#endif /* INFO_ISI_MIN_VERSION(1,0) && !INFO_ISI_MIN_VERSION(4,3) */


/* ----------------------------------------------------------------------- */
/* Message: INFO_VERSION_READ_REQ - Valid from version 004.003             */
/* ----------------------------------------------------------------------- */
/* NOTICE: If version query requires only usage of one target field,
   unnecessary target field must be initialized to have value zero by client.
*/

#if INFO_ISI_MIN_VERSION(4,3)

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  target;  /* Values from the bitmask table INFO_VERSION_TARGETS */
    /* Values from the bitmask table INFO_VERSION_TARGETS_2 */
    uint32  target2;
    } INFO_VERSION_READ_REQ_t;

#define SIZEOF_INFO_VERSION_READ_REQ   sizeof(INFO_VERSION_READ_REQ_t)

#endif /* INFO_ISI_MIN_VERSION(4,3) */


/* ----------------------------------------------------------------------- */
/* Message: INFO_VERSION_READ_RESP - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Causes and included sub blocks of the responses with status other than
       INFO_OK:
       
       
       - ***INFO_FAIL***
       Cause: Both targets in the request message are zero.
       Sub blocks: None
       
       Cause: If at least one version query requested in the target/target2
       field fails.
       Sub blocks: All successfully read version sub blocks
       
       
       - ***INFO_NO_NUMBER***
       Cause: The request message contains target(s) that is/are not
       supported
       Sub blocks: All successfully read version sub blocks
       A subset of values from the constant table INFO_GENERAL_SYM
    */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_ACCELEROMETER_VERSION
       INFO_SB_ADSP_DEVICE_ID
       INFO_SB_ADSP_REVISION_ID
       INFO_SB_ADSP_VERSION
       INFO_SB_APE_ADSP_SW
       INFO_SB_APE_BT_VERSION
       INFO_SB_APE_CUI_LCD_VERSION
       INFO_SB_APE_DVB_H_RX_BOOTLOADER_VER
       INFO_SB_APE_DVB_H_RX_HW_VER
       INFO_SB_APE_DVB_H_RX_SW_VER
       INFO_SB_APE_HW_VERSION
       INFO_SB_APE_IPDC_VERSION
       INFO_SB_APE_SW_CORE_VER
       INFO_SB_APE_TEST_VER
       INFO_SB_BOM_ID
       INFO_SB_BOOTCODE_VER
       INFO_SB_BT_MCM_VERSION
       INFO_SB_CAMERA_DETAILED_VERSION_INFO
       INFO_SB_CAMERA_VER
       INFO_SB_CHARGER_DET
       INFO_SB_CONTENT_FOTAID
       INFO_SB_CONTENT_PACK_VER
       INFO_SB_CONTENT_VERSIONS
       INFO_SB_CWS_CHIP_ID
       INFO_SB_DBI_ID
       INFO_SB_DSP_VERSION
       INFO_SB_EM_ASIC
       INFO_SB_FLIP_MCUSW_VERSION
       INFO_SB_GAZOO
       INFO_SB_GPS
       INFO_SB_HW_DRIVER_VERSION
       INFO_SB_HW_VERSION
       INFO_SB_LCD_VERSION
       INFO_SB_MAGNETOMETER_ID
       INFO_SB_MCUSW_FOTAID
       INFO_SB_MCUSW_VERSION
       INFO_SB_MCU_SPEED_VERSION
       INFO_SB_MEMORY
       INFO_SB_NAVISCROLL_VERSION
       INFO_SB_NFC_VERSION
       INFO_SB_PCI_VERSION
       INFO_SB_PMU
       INFO_SB_PROXIMITY_SENSOR_ID
       INFO_SB_RAP_VERSION
       INFO_SB_RETU_VER
       INFO_SB_RFIC_VERSION
       INFO_SB_ROFS_FOTAID
       INFO_SB_ROFS_VERSION
       INFO_SB_SIM_SWITCH
       INFO_SB_SW_VERSION
       INFO_SB_SYSTEM_ASIC
       INFO_SB_TAHVO_VER
       INFO_SB_TOUCH_SENSOR_ID
       INFO_SB_UEM_VERSION
       INFO_SB_UPP_VERSION
       INFO_SB_VERSION_BY_DSP_CORE_SRV
       INFO_SB_WLAN
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_VERSION_READ_RESP_t;

#define SIZEOF_INFO_VERSION_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_VERSION_WRITE_REQ - Valid from version 001.000            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_HW_VERSION
       INFO_SB_PCI_VERSION
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_VERSION_WRITE_REQ_t;

#define SIZEOF_INFO_VERSION_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_VERSION_WRITE_RESP - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_VERSION_WRITE_RESP_t;

#define SIZEOF_INFO_VERSION_WRITE_RESP   sizeof(INFO_VERSION_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PROD_INFO_READ_REQ - Valid from version 001.000           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  target;  /* Values from the bitmask table INFO_PRODUCT_TARGETS */
    } INFO_PROD_INFO_READ_REQ_t;

#define SIZEOF_INFO_PROD_INFO_READ_REQ   sizeof(INFO_PROD_INFO_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PROD_INFO_READ_RESP - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_ATO
       INFO_SB_BASIC_PRODUCT_CODE
       INFO_SB_FLASH_CODE
       INFO_SB_LONG_PRODUCTION_SN
       INFO_SB_MODULE_CODE
       INFO_SB_ORDER_NUMBER
       INFO_SB_PRODUCTION_SN
       INFO_SB_PRODUCT_CODE
       INFO_SB_PRODUCT_SPECIFIC_DATA
       INFO_SB_SN_DEFAULT_TYPE
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PROD_INFO_READ_RESP_t;

#define SIZEOF_INFO_PROD_INFO_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PROD_INFO_WRITE_REQ - Valid from version 001.000          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_ATO
       INFO_SB_BAND_CS_TYPE
       INFO_SB_BASIC_PRODUCT_CODE
       INFO_SB_FLASH_CODE
       INFO_SB_LONG_PRODUCTION_SN
       INFO_SB_MODULE_CODE
       INFO_SB_ORDER_NUMBER
       INFO_SB_PRODUCTION_SN
       INFO_SB_PRODUCT_CODE
       INFO_SB_PRODUCT_VARIANT_NUMBER
       INFO_SB_SN_DEFAULT_TYPE
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PROD_INFO_WRITE_REQ_t;

#define SIZEOF_INFO_PROD_INFO_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PROD_INFO_WRITE_RESP - Valid from version 001.000         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_PROD_INFO_WRITE_RESP_t;

#define SIZEOF_INFO_PROD_INFO_WRITE_RESP   \
        sizeof(INFO_PROD_INFO_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_TYPE_WRITE_REQ - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Before Info srv writes data to NVD, data validity is checked by Info
       srv.
       Subblock list:
       INFO_SB_PRODUCT_TYPE_CS_SEC
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PRODUCT_TYPE_WRITE_REQ_t;

#define SIZEOF_INFO_PRODUCT_TYPE_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_TYPE_WRITE_RESP - Valid from version 001.000      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    } INFO_PRODUCT_TYPE_WRITE_RESP_t;

#define SIZEOF_INFO_PRODUCT_TYPE_WRITE_RESP   \
        sizeof(INFO_PRODUCT_TYPE_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_TYPE_READ_REQ - Valid from version 001.000        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table INFO_PRODUCT_TYPE_TARGET */
    uint8   type;
    uint8   filler;
    } INFO_PRODUCT_TYPE_READ_REQ_t;

#define SIZEOF_INFO_PRODUCT_TYPE_READ_REQ   \
        sizeof(INFO_PRODUCT_TYPE_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_TYPE_READ_RESP - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_PRODUCT_TYPE_CS
       INFO_SB_PRODUCT_TYPE_CS_SEC
       INFO_SB_PRODUCT_TYPE_HW_INFO
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PRODUCT_TYPE_READ_RESP_t;

#define SIZEOF_INFO_PRODUCT_TYPE_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_INFO_READ_REQ - Valid from version 001.000        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* Values from the constant table INFO_PRODUCT_INFO_TARGET */
    uint8   target;
    uint8   filler;
    } INFO_PRODUCT_INFO_READ_REQ_t;

#define SIZEOF_INFO_PRODUCT_INFO_READ_REQ   \
        sizeof(INFO_PRODUCT_INFO_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_INFO_READ_RESP - Valid from version 001.000       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_BT_PID
       INFO_SB_PRODUCT_INFO_CATEGORY
       INFO_SB_PRODUCT_INFO_COMP01
       INFO_SB_PRODUCT_INFO_DEV_NAME
       INFO_SB_PRODUCT_INFO_MANUFACTURER
       INFO_SB_PRODUCT_INFO_NAME
       INFO_SB_PRODUCT_INFO_NAME_COMPRESSED
       INFO_SB_PRODUCT_INFO_NUM_ID
       INFO_SB_PRODUCT_INFO_TYPE_ID
       INFO_SB_PRODUCT_INFO_XCVR_ID
       INFO_SB_PRODUCT_INFO_XID
       INFO_SB_SIM_SLOTS
       INFO_SB_USB_MASS_ID
       INFO_SB_USB_NCM_ID
       INFO_SB_USB_NOKIA_ID
       INFO_SB_USB_NSM_ID
       INFO_SB_USB_NSM_LOCAL_TEST_ID
       INFO_SB_USB_RNDIS_ID
       INFO_SB_USB_SICD_ID
       INFO_SB_USB_VENDOR_ID
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PRODUCT_INFO_READ_RESP_t;

#define SIZEOF_INFO_PRODUCT_INFO_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_BT_ID_WRITE_REQ - Valid from version 002.005              */
/* ----------------------------------------------------------------------- */
/* INFO_SB_BT_ID_PLAIN subblock is not supported in ISA or APE products. */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_BT_ID_PLAIN
       INFO_SB_BT_ID_SEC
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_BT_ID_WRITE_REQ_t;

#define SIZEOF_INFO_BT_ID_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_BT_ID_WRITE_RESP - Valid from version 002.005             */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    } INFO_BT_ID_WRITE_RESP_t;

#define SIZEOF_INFO_BT_ID_WRITE_RESP   sizeof(INFO_BT_ID_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_BT_ID_READ_REQ - Valid from version 002.005               */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   target;  /* Values from the constant table INFO_BT_DATA_TARGET */
    uint8   filler;
    } INFO_BT_ID_READ_REQ_t;

#define SIZEOF_INFO_BT_ID_READ_REQ   sizeof(INFO_BT_ID_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_BT_ID_READ_RESP - Valid from version 002.005              */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_BT_ID_PLAIN
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_BT_ID_READ_RESP_t;

#define SIZEOF_INFO_BT_ID_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_WT_READ_REQ - Valid from version 003.001                  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  read_bits;  /* Values from the bitmask table INFO_WT_READ_BITS */
    } INFO_WT_READ_REQ_t;

#define SIZEOF_INFO_WT_READ_REQ   sizeof(INFO_WT_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_WT_READ_RESP - Valid from version 003.001                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table INFO_WT_STATUS */
    uint8   fill1;
    uint16  read_bits;  /* Values from the bitmask table INFO_WT_READ_BITS */
    uint8   fill2;
    uint8   sb_cnt;
    /* Subblock list:
       INFO_SB_WT_ORIG_MAN_MONTH_YEAR
       INFO_SB_WT_ORIG_SN_INFO
       INFO_SB_WT_OWN_MAN_MONTH_YEAR
       INFO_SB_WT_PURCH_MONTH_YEAR
       INFO_SB_WT_REPAIR_MONTH_YEAR
       INFO_SB_WT_RPF
       INFO_SB_WT_WIS
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_WT_READ_RESP_t;

#define SIZEOF_INFO_WT_READ_RESP   (6*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: INFO_WT_WRITE_REQ - Valid from version 003.001                 */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   fill1;
    uint8   sb_cnt;
    /* Subblock list:
       INFO_SB_WT_ORIG_MAN_MONTH_YEAR
       INFO_SB_WT_ORIG_SN_INFO
       INFO_SB_WT_OWN_MAN_MONTH_YEAR
       INFO_SB_WT_PURCH_MONTH_YEAR
       INFO_SB_WT_REPAIR_MONTH_YEAR
       INFO_SB_WT_RPF
       INFO_SB_WT_WIS
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_WT_WRITE_REQ_t;

#define SIZEOF_INFO_WT_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_WT_WRITE_RESP - Valid from version 003.001                */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;       /* Values from the constant table INFO_WT_STATUS */
    uint8   fill1;
    uint16  read_bits;  /* Values from the bitmask table INFO_WT_READ_BITS */
    uint8   fill2[2];
    } INFO_WT_WRITE_RESP_t;

#define SIZEOF_INFO_WT_WRITE_RESP   sizeof(INFO_WT_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_LONG_DATA_READ_REQ - Valid from version 004.006           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_LONG_DATA_READ_REQ_t;

#define SIZEOF_INFO_LONG_DATA_READ_REQ   sizeof(INFO_LONG_DATA_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_LONG_DATA_READ_RESP - Valid from version 004.006          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    uint16  data_length;  /* Length details:/17/ */
    uint8   data[INFO_ANY_SIZE]; /* Format:/16/ */
    /* 0 */
    } INFO_LONG_DATA_READ_RESP_t;

#define SIZEOF_INFO_LONG_DATA_READ_RESP   (4*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: INFO_LONG_DATA_WRITE_REQ - Valid from version 004.006          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint16  data_length;  /* Length details:/17/ */
    uint8   data[INFO_ANY_SIZE]; /* Required format:/16/ */
    /* 0 */
    } INFO_LONG_DATA_WRITE_REQ_t;

#define SIZEOF_INFO_LONG_DATA_WRITE_REQ   (2*sizeof(uint8) + sizeof(uint16))


/* ----------------------------------------------------------------------- */
/* Message: INFO_LONG_DATA_WRITE_RESP - Valid from version 004.006         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    } INFO_LONG_DATA_WRITE_RESP_t;

#define SIZEOF_INFO_LONG_DATA_WRITE_RESP   \
        sizeof(INFO_LONG_DATA_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_WLAN_INFO_READ_REQ - Valid from version 004.009           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_WLAN_INFO_READ_REQ_t;

#define SIZEOF_INFO_WLAN_INFO_READ_REQ   sizeof(INFO_WLAN_INFO_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_WLAN_INFO_READ_RESP - Valid from version 004.009          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   address[INFO_WLAN_MAC_ADDR_LEN]; /* WLAN MAC address */
    uint8   filler[3];    /* 0 */
    } INFO_WLAN_INFO_READ_RESP_t;

#define SIZEOF_INFO_WLAN_INFO_READ_RESP   sizeof(INFO_WLAN_INFO_READ_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_IP_PASSTHROUGH_READ_REQ - Valid from version 004.015      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_IP_PASSTHROUGH_READ_REQ_t;

#define SIZEOF_INFO_IP_PASSTHROUGH_READ_REQ   \
        sizeof(INFO_IP_PASSTHROUGH_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_IP_PASSTHROUGH_READ_RESP - Valid from version 004.015     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    INFO_IPP_MACS ipp_macs;
    } INFO_IP_PASSTHROUGH_READ_RESP_t;

#define SIZEOF_INFO_IP_PASSTHROUGH_READ_RESP   \
        sizeof(INFO_IP_PASSTHROUGH_READ_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_WLAN_INFO_WRITE_REQ - Valid from version 004.016          */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    uint8   enc_data[8];
    } INFO_WLAN_INFO_WRITE_REQ_t;

#define SIZEOF_INFO_WLAN_INFO_WRITE_REQ   sizeof(INFO_WLAN_INFO_WRITE_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_WLAN_INFO_WRITE_RESP - Valid from version 004.016         */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_WLAN_INFO_WRITE_RESP_t;

#define SIZEOF_INFO_WLAN_INFO_WRITE_RESP   \
        sizeof(INFO_WLAN_INFO_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_RAT_BAND_READ_REQ - Valid from version 005.001    */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_PRODUCT_RAT_BAND_READ_REQ_t;

#define SIZEOF_INFO_PRODUCT_RAT_BAND_READ_REQ   \
        sizeof(INFO_PRODUCT_RAT_BAND_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_RAT_BAND_READ_RESP - Valid from version 005.001   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   status;
    uint8   sb_cnt;
    /* Subblock list:
       INFO_SB_RAT_BAND_INFO
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PRODUCT_RAT_BAND_READ_RESP_t;

#define SIZEOF_INFO_PRODUCT_RAT_BAND_READ_RESP   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_RAT_BAND_WRITE_REQ - Valid from version 005.001   */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    /* Subblock list:
       INFO_SB_RAT_BAND_INFO
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_PRODUCT_RAT_BAND_WRITE_REQ_t;

#define SIZEOF_INFO_PRODUCT_RAT_BAND_WRITE_REQ   (4*sizeof(uint8))


/* ----------------------------------------------------------------------- */
/* Message: INFO_PRODUCT_RAT_BAND_WRITE_RESP - Valid from version 005.001  */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    } INFO_PRODUCT_RAT_BAND_WRITE_RESP_t;

#define SIZEOF_INFO_PRODUCT_RAT_BAND_WRITE_RESP   \
        sizeof(INFO_PRODUCT_RAT_BAND_WRITE_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_STARTUP_REASON_READ_REQ - Valid from version 008.008      */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_STARTUP_REASON_READ_REQ_t;

#define SIZEOF_INFO_STARTUP_REASON_READ_REQ   \
        sizeof(INFO_STARTUP_REASON_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_STARTUP_REASON_READ_RESP - Valid from version 008.008     */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   filler;
    /* Values from the bitmask table INFO_STARTUP_REASON */
    uint32  startup_reason;
    } INFO_STARTUP_REASON_READ_RESP_t;

#define SIZEOF_INFO_STARTUP_REASON_READ_RESP   \
        sizeof(INFO_STARTUP_REASON_READ_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_RESET_REASON_READ_REQ - Valid from version 008.010        */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    } INFO_RESET_REASON_READ_REQ_t;

#define SIZEOF_INFO_RESET_REASON_READ_REQ   \
        sizeof(INFO_RESET_REASON_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_RESET_REASON_READ_RESP - Valid from version 008.010       */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    /* Values from the constant table INFO_RESET_REASON */
    uint8   reset_reason;
    } INFO_RESET_REASON_READ_RESP_t;

#define SIZEOF_INFO_RESET_REASON_READ_RESP   \
        sizeof(INFO_RESET_REASON_READ_RESP_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_LIFETIME_READ_REQ - Valid from version 008.024            */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    uint8   filler[2];
    uint32  target;  /* Values from the bitmask table INFO_LIFETIME_TARGET */
    } INFO_LIFETIME_READ_REQ_t;

#define SIZEOF_INFO_LIFETIME_READ_REQ   sizeof(INFO_LIFETIME_READ_REQ_t)


/* ----------------------------------------------------------------------- */
/* Message: INFO_LIFETIME_READ_RESP - Valid from version 008.024           */
/* ----------------------------------------------------------------------- */

typedef struct
    {
    uint8   trans_id;
    uint8   message_id;
    /* A subset of values from the constant table INFO_GENERAL_SYM */
    uint8   status;
    uint8   sub_block_count;
    /* Subblock list:
       INFO_SB_LIFETIME
       INFO_SB_REBOOTS
       INFO_SB_UPDATES
    */
    uint8   sub_block[INFO_ANY_SIZE];
    } INFO_LIFETIME_READ_RESP_t;

#define SIZEOF_INFO_LIFETIME_READ_RESP   (4*sizeof(uint8))




/* ----------------------------------------------------------------------- */
/* Notes                                                                   */
/* ----------------------------------------------------------------------- */
/*
   /2/   Technical specfication 3GPP TS 25.101 V6.6.0( Frequency bands ).

   /15/  Workset: GSM_SEC:WS_DCT4_SPEC
         Part: GSM_SEC:DCT4_SPEC
         Item: GSM_SEC:TDSB6_MSG.SPEC.DOC
         Filename: Tdsb6_msg_spec.doc

   /16/  One string, which can contain several fields(e.g. various version
         information ). Fields are separated with \n. Last field ends to \0 (
         end of data ):
         str1\nstr2\n...\nstrN\0

   /17/  In total maximum length for string is 512 bytes. Length field
         indicates total length including \ns and \0.

   /18/  *** WHENEVER ADDING NEW SUB BLOCK, KEEP IN MIND THAT 0xF0 IS
         RESERVED FOR 16 BITS SUB BLOCK IDs ***
*/


#endif /* _INFO_ISI_H */
