/*
NOKIA
R&D Copenhagen
CoreSW/Corleone









                autogen_def.h
                -------------
                SW Include






Project:          autogen

%name:            autogen_def.h %
%version:         co1tss#339 %
%instance:        co_pctls_1 %
%derived_by:      eliasen %
%date_modified:   Mon Mar 14 11:54:13 2011 %

Copyright (c) Nokia. All rights reserved
*/


/* ============================================================================================= */
/* Abstract */
/* ============================================================================================= */

/*  Header file for autogen

    Contains global variable definitions and error codes
*/

#ifndef _AUTOGEN_DEF_H_
#define _AUTOGEN_DEF_H_

#define AUTOGEN_XTI_UNKNOWN         0
#define AUTOGEN_XTI_V2              1
#define AUTOGEN_XTI_V3              2

#define AUTOGEN_STRING_TYPE_FORMATTED                   0
#define AUTOGEN_STRING_TYPE_UNFORMATTED_LE              1
#define AUTOGEN_STRING_TYPE_UNFORMATTED_BE              2
#define AUTOGEN_STRING_TYPE_UNFORMATTED_UNICODE         3


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "global.h"
#include "pn_const.h"


#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #include "product.h"
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU */

#if (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU || defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE)
 #include "type_def.h"
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU || AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */


#include "autogen_internal_conf.h"

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #include "autogen_local_conf.h"
#else
 #include "autogen_conf.h"
#endif

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #ifndef AUTOGEN_BINARY_RELEASE 
  #define AUTOGEN_INCLUDE_INTERFACES /* Moved from autogen_internal_conf.h */
 #endif
#endif

#if (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU || defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE)
 #include "pn_conf.h"
#endif

#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #include "pn_obj.h"
#endif

#if (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU || defined AUTOGEN_ENVIRONMENT_PRODUCT_DSP)
 #include "isi_conf.h"
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_MCU || AUTOGEN_ENVIRONMENT_PRODUCT_DSP */

#ifndef AUTOGEN_DO_NOT_INCLUDE_ISI_MACROS
 #include "isi_macros.h"
#endif

#include "master_trace.h"

/* ============================================================================================= */
/* Define environment */
/* ============================================================================================= */

/* Flags for MCU product environment */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_MCU
 #ifndef AUTOGEN_ENVIRONMENT_PRODUCT
  #define AUTOGEN_ENVIRONMENT_PRODUCT
 #endif
#endif

/* Flags for CDSP product environment */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DSP
 #ifndef AUTOGEN_ENVIRONMENT_PRODUCT
  #define AUTOGEN_ENVIRONMENT_PRODUCT
 #endif
 #ifndef AUTOGEN_PMD_FILE_TYPE
  #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_DSP5_CDSP
 #endif
#endif

/* Flags for ADSP product environment */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_ADSP
 #ifndef AUTOGEN_ENVIRONMENT_PRODUCT
  #define AUTOGEN_ENVIRONMENT_PRODUCT
 #endif
 #ifndef AUTOGEN_PMD_FILE_TYPE
  #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_DSP5_ADSP
 #endif
#endif

/* Flags for Symbian product environment */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN
 #ifndef AUTOGEN_ENVIRONMENT_PRODUCT
  #define AUTOGEN_ENVIRONMENT_PRODUCT
 #endif
 #ifndef AUTOGEN_PMD_FILE_TYPE
  #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_SYMBIAN
 #endif
#endif

/* Flags for Device product environment */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
 #ifndef AUTOGEN_DEVICE_ID
  #error "AUTOGEN_DEVICE_ID has not been specified. Please specify in autogen_conf.h"
 #endif
 #ifndef AUTOGEN_DEVICE_NAME
  #error "AUTOGEN_DEVICE_NAME has not been specified. Please specify in autogen_conf.h"
 #endif
 #ifndef AUTOGEN_DEVICE_LOGICAL_NAME
  #error "AUTOGEN_DEVICE_LOGICAL_NAME has not been specified. Please specify in autogen_conf.h"
 #endif
 #ifndef AUTOGEN_ENVIRONMENT_PRODUCT
  #define AUTOGEN_ENVIRONMENT_PRODUCT
 #endif
 #ifndef AUTOGEN_PMD_FILE_TYPE
  #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_DEVICE
 #endif
#endif

/* Ensure that environment is set */
#ifndef AUTOGEN_ENVIRONMENT_PRODUCT
 #ifndef AUTOGEN_ENVIRONMENT_LOCAL
  #define AUTOGEN_ENVIRONMENT_LOCAL
 #endif
#endif /* !AUTOGEN_ENVIRONMENT_PRODUCT */

/* Flags for local environment */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #ifndef AUTOGEN_INCLUDE_RESOURCE_LEGACY
  #define AUTOGEN_INCLUDE_RESOURCE_LEGACY
 #endif
#endif /* AUTOGEN_ENVIRONMENT_LOCAL */

/* Set environment string */
#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define AUTOGEN_ENVIRONMENT_STRING "Local"
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DSP)
 #define AUTOGEN_ENVIRONMENT_STRING "Product CDSP"
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_ADSP)
 #define AUTOGEN_ENVIRONMENT_STRING "Product ADSP"
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU)
 #define AUTOGEN_ENVIRONMENT_STRING "Product MCU"
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN)
 #define AUTOGEN_ENVIRONMENT_STRING "Product Symbian"
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE)
 #define AUTOGEN_ENVIRONMENT_STRING "Product Device"
#else
 #define AUTOGEN_ENVIRONMENT_STRING "Product"
#endif

/* Ensure that PMD file type is set */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT
 #ifndef AUTOGEN_PMD_FILE_TYPE
  #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_PRODUCT
 #endif
#endif

#ifndef AUTOGEN_PMD_FILE_TYPE
 #define AUTOGEN_PMD_FILE_TYPE PMD_FILE_TYPE_RESOURCES
#endif

/* Ensure that PMD file format is set */
#ifndef PMD_FILE_FORMAT
 #define PMD_FILE_FORMAT 501
#endif

#if PMD_FILE_FORMAT == 500
 #define PMD_FILE_FORMAT_STRING "5.00"
#elif PMD_FILE_FORMAT == 501
 #define PMD_FILE_FORMAT_STRING "5.01"
#elif PMD_FILE_FORMAT == 600
/* 64-bits support */
 #define PMD_FILE_FORMAT_STRING "6.00"
#elif PMD_FILE_FORMAT == 610
 #define PMD_FILE_FORMAT_STRING "6.10"
#else
 #error "PMD_FILE_FORMAT is not valid. Must be 500, 501 (default), 600 or 610"
#endif

/* Trace checks */
#ifdef AUTOGEN_INCLUDE_VENDOR_TRACES
 #ifndef AUTOGEN_VENDOR_IDENTIFIER
  #define AUTOGEN_VENDOR_IDENTIFIER "vend"
 #endif

 #ifdef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
  #ifndef AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME
   #define AUTOGEN_VENDOR_DLL_TRACE_TYPE_NAME "Vendor DLL traces"
  #endif

  #ifndef AUTOGEN_VENDOR_DLL_TRACE_NAME
   #define AUTOGEN_VENDOR_DLL_TRACE_NAME "Vendor"
  #endif

  #ifndef AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION
   #ifndef AUTOGEN_VENDOR_DLL_TRACE_DLL_FILE_NAME
    #define AUTOGEN_VENDOR_DLL_TRACE_DLL_FILE_NAME "vendor.dll"
   #endif
   #ifndef AUTOGEN_VENDOR_DLL_TRACE_DLL_FUNCTION_NAME
    #define AUTOGEN_VENDOR_DLL_TRACE_DLL_FUNCTION_NAME "fnTrace"
   #endif
  #endif

 #endif
#endif

#ifdef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
 #ifndef AUTOGEN_INCLUDE_VENDOR_TRACES
  #error "AUTOGEN_INCLUDE_VENDOR_DLL_TRACE can't be defined without AUTOGEN_INCLUDE_VENDOR_TRACES"
 #endif
#endif

#ifdef AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION
 #ifndef AUTOGEN_INCLUDE_VENDOR_DLL_TRACE
  #error "AUTOGEN_USE_CHIPSET_SUPPLIER_DESCRIPTION can't be defined without AUTOGEN_INCLUDE_VENDOR_DLL_TRACE"
 #endif
#endif

#ifdef AUTOGEN_INCLUDE_VENDOR_COMPONENT_TRACES
 #ifndef AUTOGEN_INCLUDE_VENDOR_TRACES
  #error "AUTOGEN_INCLUDE_VENDOR_COMPONENT_TRACES can't be defined without AUTOGEN_INCLUDE_VENDOR_TRACES"
 #endif
#endif

/* Device checks */
#ifdef AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE
 #if (defined AUTOGEN_INCLUDE_INVARIANT_TRACES || defined AUTOGEN_INCLUDE_MCU_TRACES || defined AUTOGEN_INCLUDE_NOS_TRACES || defined AUTOGEN_INCLUDE_HAL_TRACES || defined AUTOGEN_INCLUDE_VENDOR_TRACES)
  #ifndef AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID
   #error "AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID has not been specified. Please specify in autogen_conf.h"
  #endif /* AUTOGEN_DEVICE_MONITOR_SERVER_RESOURCE_ID */
 #endif /* Any monitor server handled trace type */
#endif /* AUTOGEN_ENVIRONMENT_PRODUCT_DEVICE */

/* XTI version checks */
#ifndef AUTOGEN_XTI_VERSION
 #define AUTOGEN_XTI_VERSION AUTOGEN_XTI_UNKNOWN
#endif

#if AUTOGEN_XTI_VERSION == AUTOGEN_XTI_UNKNOWN
 #define AUTOGEN_XTI_VERSION_STRING "Unknown"
#elif AUTOGEN_XTI_VERSION == AUTOGEN_XTI_V2
 #define AUTOGEN_XTI_VERSION_STRING "XTI v2"
#elif AUTOGEN_XTI_VERSION == AUTOGEN_XTI_V3
 #define AUTOGEN_XTI_VERSION_STRING "XTI v3"
#else
 #error "AUTOGEN_XTI_VERSION is not valid. Must be AUTOGEN_XTI_UNKNOWN, AUTOGEN_XTI_V2 or AUTOGEN_XTI_V3"
#endif


/* ============================================================================================= */
/* Properties */
/* ============================================================================================= */

typedef enum e_autogen_property_id
{
/*
///<property name="PROPERTY_ALIGNMENT_64_BITS" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>The presence of this property will inform autogen that 64-bit alignment is to be used. 
///<br/>
///The property can't be used together with <see cref_property="PROPERTY_ALIGNMENT_CHECK_DISABLE"/> and it is only valid when PMD file format 6.00 or higher is used.
///<br/>
///In case the property has not been applied to a resource autogen will generate an error if a 64-bit macro is used.
///<b>NOTE:</b> If a message macro file is including a shared file using 64-bits alignment then it must be updated to 64-bits alignment.
///<br/>
///For a discussion of 64-bit alignment issues please see <see cref_subtopic="Alignment"/>
///Examples of updating to 64-bit aligment can be found at <see cref_subtopic="Updating an existing message macro file"/> and <see cref_subtopic="Shared files"/>.
///</summary>
///</property>
*/
    PROPERTY_ALIGNMENT_64_BITS,

/*
///<property name="PROPERTY_ALIGNMENT_CHECK_BREAK" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>The presence of this property will force autogen to exit when any alignment problem is encountered. 
///Otherwise, alignment problems only result in warnings.</summary>
///</property>
*/
    PROPERTY_ALIGNMENT_CHECK_BREAK,

/*
///<property name="PROPERTY_ALIGNMENT_CHECK_DISABLE" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///The presence of this property will cause autogen to ignore any alignment problems encountered.
///</summary>
///</property>
*/
    PROPERTY_ALIGNMENT_CHECK_DISABLE,

/*
///<property name="PROPERTY_ARRAY_MAXIMUM_SIZE" group="Item properties">
///<types>
///<type>value</type>
///</types>
///<summary>
///Defines a maximum size for an array with undefined size 
///(<b>REF_AS_MANY_AS_POSSIBLE</b> has been used as reference name).
///</summary>
///<remarks>
///The property indicates that the array cannot contain more elements than the 
///given maximum size. This affects documentation, ISI header file output, 
///and length checks in PMD decoding/encoding. 
///<br/><br/>
///The maximum size can be given as a number or as a symbolic constant.
///<br/><br/>
///The following example defines an array, where the size is given 
///indirectly by PhoNet length. The property defines an upper limit 
///for the array size:
///<code filename="property_array_maximum_size_macro.txt"/>
///This generates the following in the ISI header file:
///<code filename="property_array_maximum_size_isihdr.txt"/>
///<br/>
///The property <see cref_property="PROPERTY_STRING_MAXIMUM_LENGTH"/> 
///does the same thing for strings.
///</remarks>
///<seealso cref_property="PROPERTY_STRING_MAXIMUM_LENGTH"/> 
///</property>
*/
    PROPERTY_ARRAY_MAXIMUM_SIZE,

/*
///<property name="PROPERTY_CHANGE_DATE" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the date of an ISI version change. 
///</summary>
///<remarks>
///The ISI version change date text is solely used as text in HTML and ISI server header outputs.
///<br/><br/>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_CHANGE_DATE,

/*
///<property name="PROPERTY_CHANGE_PERSON" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the person, responsible for the ISI version change.</summary>
///<remarks>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_CHANGE_PERSON,

/*
///<property name="PROPERTY_CHANGE_REASON" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the reason for the ISI version change. 
///</summary>
///<remarks>
///The reason text is solely used as text in HTML and ISI server header outputs.
///<br/><br/>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_CHANGE_REASON,

/*
///<property name="PROPERTY_CHANGE_REFERENCE" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the reference, defining the CR/error for the ISI version change. 
///</summary>
///<remarks>
///Note, that there can be several references defined for a given ISI version. 
///Simply use the property several times...
///<br/><br/>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_CHANGE_REFERENCE,

/*
///<property name="PROPERTY_CHANGE_STATUS" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the status of the ISI version change.
///</summary>
///<remarks>
///The property should use the normal states: "DRAFT", "NON-DRAFT", "PROPOSAL" or "APPROVED".
///<br/><br/>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_CHANGE_STATUS,

/*
///<property name="PROPERTY_COMPONENT_ID" group="Resource properties">
///<types>
///<type>value</type>
///</types>
///<summary>This value property defines the component identifier used as part of the <see cref_macro="PRINTF_BEGIN"/> macro.
///</summary>
///<remarks>
///The format string of a printf definition <see cref_macro="PRINTF_BEGIN"/> / <see cref_macro="PRINTF_BEGIN"/> is identified 
///by the component identifier, trace group identifier and trace identifier.<br/>
///This resource property defines the component identifier to be used by all printf definitions defined inside this resource.<br/><br/>
///Example, showing use of property can be found here <see cref_topic="Printf"/>.
///</remarks>
///</property>
*/
    PROPERTY_COMPONENT_ID,

/*
///<property name="PROPERTY_COPYRIGHT_YEAR" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the year(s) to be included in Copyright statement in ISI Header, HTML, and XML.
///</summary>
///<remarks>
///The default copyright statement is "Copyright (c) Nokia Corporation. All rights reserved."<br/>
///Applying PROPERTY_STRING(PROPERTY_COPYRIGHT_YEAR, "2007, 2008") to a resource causes the copyright statement to include the specified string:<br/>.
///Copyright (c) 2007, 2008 Nokia Corporation. All rights reserved.
///<br/><br/>
///Example, showing use of property can be found here <see cref_macro="ISI_VERSION_HISTORY"/>.
///</remarks>
///</property>
*/
    PROPERTY_COPYRIGHT_YEAR,

/*
///<property name="PROPERTY_DEVICE_DEPENDENT_MESSAGES" group="Resource properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_DEVICE_DEPENDENT_MESSAGES,

/*
///<property name="PROPERTY_FTD_IS_COMMAND" group="FTD properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_FTD_IS_COMMAND,

/*
///<property name="PROPERTY_FTD_IS_INPUT_DATA" group="FTD properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This simple property defines that the FTD data is an input data.
///</summary>
///<remarks>
///Input data is data which should be sent with <b>COMM_FTD_TEST_DATA_REQ</b> messages.
///For Symbian <b>SOS_FTD_EXECUTE_REQ</b> messages are used.
///<br/><br/>
///For examples of FTD data definitions using this property, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///</property>
*/
    PROPERTY_FTD_IS_INPUT_DATA,

/*
///<property name="PROPERTY_FTD_IS_STATIC_DATA" group="FTD properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This simple property defines that the FTD data does not change over time, 
///and that it is only sent once when requested from a server.
///</summary>
///<remarks>
///The following example shows how to use the property:
///<code filename="property_ftd_is_static_data_macro.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_FTD_IS_STATIC_DATA,

/*
///<property name="PROPERTY_FTD_STRING_MAXIMUM_LENGTH" group="FTD properties">
///<types>
///<type>value</type>
///</types>
///<summary>
///Defines a maximum length for the FTD string.
///</summary>
///<remarks>
///The maximum size can be given as a number or as a symbolic constant, 
///and must represent number of characters.
///</remarks>
///<seealso cref_property="PROPERTY_FTD_STRING_MINIMUM_LENGTH"/>
///</property>
*/
    PROPERTY_FTD_STRING_MAXIMUM_LENGTH,

/*
///<property name="PROPERTY_FTD_STRING_MINIMUM_LENGTH" group="FTD properties">
///<types>
///<type>value</type>
///</types>
///<summary>
///Defines a minimum length for the FTD string.
///</summary>
///<remarks>
///The minimum size can be given as a number or as a symbolic constant, 
///and must represent number of characters.
///</remarks>
///<seealso cref_property="PROPERTY_FTD_STRING_MAXIMUM_LENGTH"/>
///</property>
*/
    PROPERTY_FTD_STRING_MINIMUM_LENGTH,

/*
///<property name="PROPERTY_FTD_SUPPORTED_MODES" group="FTD properties">
///<types>
///<type>value</type>
///</types>
///<summary>This value property defines the modes for which this FTD data is supported for.
///</summary>
///<remarks>
///See <see cref_enum="E_FTD_SUPPORTED_MODES"/> for possible values.
///<br/><br/>
///For examples of FTD data definitions using this property, refer to <see cref_topic="Defining FTDs" />.
///</remarks>
///</property>
*/
    PROPERTY_FTD_SUPPORTED_MODES,

/*
///<property name="PROPERTY_HTML_CONTINUUS_PROJECT_DB" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property defines the HTML Continuus project database.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_HTML_CONTINUUS_PROJECT_DB,

/*
///<property name="PROPERTY_HTML_CONTINUUS_PROJECT_NAME" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property defines the HTML Continuus project name.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_HTML_CONTINUUS_PROJECT_NAME,

/*
///<property name="PROPERTY_HTML_DIRECTORY_PATH" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property defines the human-readable directory path information written in the HTML output.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///The property is also used by autogen to generate html output in GIF_SPECS (or similar) directory structure.
///This means, that links to/from shared resources work across directory branches,
///e.g. between GIF_SPECS/IAM and GIF_SPECS/Protocol.
///Please note that autogen always re-generates output, i.e. existing files are overwritten, NOT patched.
///To get all links to work properly it is essential that html output for all servers using a (group of) shared
///resources are generated in one batch.
///In case this property is missing autogen outputs html to autogen/html directory.
///</remarks>
///</property>
*/
    PROPERTY_HTML_DIRECTORY_PATH,

/*
///<property name="PROPERTY_HTML_DOCUMENT_NUMBER" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property defines the EDMS HTML document number. If no document number is defined, autogen prints a dash as number.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_HTML_DOCUMENT_NUMBER,

/*
///<property name="PROPERTY_HTML_DONT_GENERATE" group="HTML properties">
///<types>
///<type>simple</type>
///</types>
///<summary>No HTML will be generated for objects with this property.</summary>
///<remarks>
///The following example shows how to disable generation of a sub block in the HTML document:
///<code filename="property_html_dont_generate_macro_sb.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_HTML_DONT_GENERATE,

/*
///<property name="PROPERTY_HTML_EXPAND_CONSTANT_LISTS" group="HTML properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_HTML_EXPAND_CONSTANT_LISTS,

/*
///<property name="PROPERTY_HTML_FILENAME" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property defines the filename for the HTML document. 
///If the filename is not specified, autogen provides a default name. 
///For ISI resources, the default filename is i_xxx_m.html, 
///where xxx is the short resource name, as defined with <see cref_macro="RES_BEGIN"/>.
///</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_HTML_FILENAME,

/*
///<property name="PROPERTY_HTML_INCLUDE_INTRODUCTION" group="HTML properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property enables generation of an introduction in the HTML document.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_HTML_INCLUDE_INTRODUCTION,

/*
///<property name="PROPERTY_HTML_INCLUDE_PHONET_HEADER" group="HTML properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property enables PhoNet header in each message structure in the HTML document.
///</summary>
///<remarks>
///The resource property <see cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT"/> defines 
///the actual layout of the PhoNet header.
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT"/>
///</property>
*/
    PROPERTY_HTML_INCLUDE_PHONET_HEADER,

/*
///<property name="PROPERTY_HTML_INCLUDE_VARNAME_COLUMN" group="HTML properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property enables an extra column in the message/sub block descriptions, 
///containing the variable name of the elements in the generated ISI header file.
///</summary>
///</property>
*/
    PROPERTY_HTML_INCLUDE_VARNAME_COLUMN,

/*
///<property name="PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS" group="HTML properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_HTML_SHOW_FIELD_SIZE_IN_BITS,

/*
///<property name="PROPERTY_HTML_TITLE" group="HTML properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the title of the HTML document. 
///If no title is defined, autogen used the HTML filename as title.
///</summary>
///<remarks>
///For an example, showing use of this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_HTML_TITLE,

/*
///<property name="PROPERTY_INCLUDE_PN_TRACE_OBJECTS" group="Resource properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_INCLUDE_PN_TRACE_OBJECTS,

/*
///<property name="PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property allows a resource extension to refer to the objects defined 
///in the macro file for the resource base
///</summary>
///<remarks>
///In the example below, a base resource defines a constant table and a sequence:
///see <code filename="resource_isi_extension_base_def_1.txt"/>
///The resource extension refers to these definitions by defining the property:
///see <code filename="resource_isi_extension_base_def_2.txt"/>
///<br/>
///The property should only be used on an extension resource definítion.
///</remarks>
///</property>
*/
    PROPERTY_INHERIT_BASE_RESOURCE_DEFINITIONS,

/*
///<property name="PROPERTY_ISIHDR_ALIAS_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines an alias to a definition in the ISI header file. 
///When used with constants (from constant definitions or table items), the alias will simply generate 
///another definition with the same value. Can for example be used when a supporting several symbolic 
///names for a constant. When used with structures, a type definition will be generated for the alias.</summary>
///<remarks>
///Example, showing how to make an alias for a sub block structure:<code filename="property_isihdr_alias_name_macro.txt"/>
///which generates the following in the ISI header file:<code filename="property_isihdr_alias_name_isihdr.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_ALIAS_NAME,

/*
///<property name="PROPERTY_ISIHDR_ARRAY_MARKER" group="ISI header properties">
///<types>
///<type>E_ISIHDR_GENERATION_TYPE</type>
///</types>
///<summary>This value property defines how an array of bytes should be generated 
///in the ISI header file.</summary>
///<remarks>
///Most macros, representing arrays, contain an ISI header generation flag as last argument. 
///This property sets the same value for macros, not supporting this argument.
///<br/><br/>
///See <see cref_enum="E_ISIHDR_GENERATION_TYPE"/> for possible values.
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_ARRAY_MARKER,

/*
///<property name="PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property sets the Continuus instance name of the 8-bit ISI header file. 
///The information appears in the Continuus header for the header file. </summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME,

/*
///<property name="PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property sets the Continuus instance name of the 16-bit ISI header file. 
///The information appears in the Continuus header for the header file.
///</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME_16,

/*
///<property name="PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property sets the Continuus database name of the ISI header files. 
///The name appears in the Continuus reference in the file headers.
///</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_CONTINUUS_PROJECT_DB,

/*
///<property name="PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property sets the Continuus path to the 8-bit ISI header file. 
///The name appears in the Continuus reference in the file header. </summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH,

/*
///<property name="PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property sets the Continuus path to the 16-bit ISI header file. The name appears in the 
///Continuus reference in the file header.
///</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_CONTINUUS_PROJECT_PATH_16,

/*
///<property name="PROPERTY_ISIHDR_DEFINITION_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>
///This string property specifies the definition name in the ISI header file for an item of constant/bitmask table.
///</summary>
///<remarks>
///When used with constant or bit mask tables, the definition name can be empty (""), 
///meaning that no typedef should be generated for the table. If it is not empty, the definition name 
///is also used every place, the table is being referred (using <see cref_macro="VALUE_CONST"/>.
///<br/><br/>
///If the definition name is not specified it defaults to <b>XXX_CONST</b>, where <b>XXX</b> is the name of the table. 
///When used with items (values, strings, etc.), the definition name overrules the normal autogen type name, 
///such as <b>uint8</b> or <b>char</b>. Here, the definition name can't be empty. 
///Note that autogen does not check if the type name exists.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_isihdr_definition_name_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_definition_name_isihdr.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_DEFINITION_NAME,

/*
///<property name="PROPERTY_ISIHDR_DONT_GENERATE" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When setting this property on an object (message, item, etc.), 
///the object is not generated in the ISI header (8-bit and 16-bit).
///</summary>
///<remarks>
///By default, all objects are generated.
///<br/><br/>
///The property should ONLY be used when there is no way, autogen can generate the desired ISI header output.
///<br/><br/>
///The following example shows how to disable generation of a sub block structure in the ISI header file:
///<code filename="property_isihdr_dont_generate_macro_sb.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_DONT_GENERATE,

/*
///<property name="PROPERTY_ISIHDR_DONT_GENERATE_16" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When setting this property on an object (message, item, etc.), 
///the object is not generated in the 16-bit ISI header file.
///</summary>
///<remarks>
///By default, all objects are generated.
///<br/><br/>
///The property should ONLY be used when there is no way, autogen can generate the desired ISI header output.
///<br/><br/>
///The following example shows how to disable generation of a sub block structure in the 16-bit ISI header file:
///<code filename="property_isihdr_dont_generate_16_macro_sb.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_DONT_GENERATE_16,

/*
///<property name="PROPERTY_ISIHDR_DONT_GENERATE_8" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When setting this property on an object (message, item, etc.), 
///the object is not generated in the 8-bit ISI header file.
///</summary>
///<remarks>
///By default, all objects are generated.
///<br/><br/>
///The property should ONLY be used when there is no way, autogen can generate the desired ISI header output.
///<br/><br/>
///The following example shows how to disable generation of a sub block structure in the 8-bit ISI header file:
///<code filename="property_isihdr_dont_generate_8_macro_sb.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_DONT_GENERATE_8,

/*
///<property name="PROPERTY_ISIHDR_DONT_GENERATE_ID" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property disables generation of sub block, message or trace ID in the top section of the 
///generated ISI header file.</summary>
///<remarks>
///Whether the structure representing the message or sub block is generated or not is 
///nor affected by this property.
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_DONT_GENERATE_ID,

/*
///<property name="PROPERTY_ISIHDR_FILENAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the filename for the 8-bit ISI header file. 
///If the filename is not specified, autogen provides a default name, xxx_isi.h, 
///where xxx is the short resource name, as defined with <see cref_macro="RES_BEGIN"/>. 
///If an empty name is defined (""), no 8-bit ISI header file is generated.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_ISIHDR_FILENAME,

/*
///<property name="PROPERTY_ISIHDR_FILENAME_16" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the filename for the 16-bit ISI header file. 
///If the filename is not specified, autogen provides a default name, xxx_isi_16.h, 
///where xxx is the short resource name, as defined with <see cref_macro="RES_BEGIN"/>. 
///If an empty name is defined (""), no 16-bit ISI header file is generated.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_FILENAME_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this value property is set, all message elements in the structures will be generated in the 
///ISI header file, also if several dynamically sized elements occur within same structure.</summary>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_AS_BITFIELD" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that <b>bitxx</b> types are generated rather than <b>uintxx</b> for this item.
///</summary> 
///<remarks>
///This property is ignored unless the <see cref_property="PROPERTY_ISIHDR_GENERATE_BITFIELDS"/> 
///property is set on the resource.
///<br/><br/>
///There are two uses of the property. 
///<br/>
///It can be set on a bit table, which is the normal case. 
///All items referring to the table (using the macro <see cref_macro="VALUE_CONST"/>) will 
///be defined using the <b>bitxx</b> type in the ISI header file.
///<br/>
///When the property is set on the individual item, only this item is generated as <b>bitxx</b>.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_isihdr_generate_as_bitfield_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_generate_as_bitfield_isihdr_after.txt"/>
///Without the property, the following is generated in the ISI header file:
///<code filename="property_isihdr_generate_as_bitfield_isihdr_before.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_BITFIELDS"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_AS_BITFIELD,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_AS_BOOL" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that <b>boolxx</b> types are generated rather than <b>uintxx</b> for this item in the ISI header file. 
///</summary>
///<remarks>
///This property is ignored unless the property <see cref_property="PROPERTY_ISIHDR_GENERATE_BOOLS" /> 
///is set on the resource. 
///This property can also be set on the table itself, which affects all items using that table.<br/><br/>
///Example, showing use of property:<code filename="property_isihdr_generate_as_bool_macro.txt"/>
///which generates the following in the ISI header file:<code filename="property_isihdr_generate_as_bool_isihdr_after.txt"/>
///Without the property set, the following is generated in the ISI header file:<code filename="property_isihdr_generate_as_bool_isihdr_before.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_AS_BOOL,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_AS_ENUM_16" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property enables generation of enum in 16-bit version ISI header 
///file for a constant table definition.
///</summary>
///<remarks>
///As argument to the property macro, pass the type name of the generated enumeration.
///<br/><br/>
///See <see cref_property="PROPERTY_ISIHDR_GENERATE_AS_ENUM_8"/> for an example of using the property.
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_AS_ENUM_8"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_AS_ENUM_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_AS_ENUM_8" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property enables generation of enum in 8-bit version ISI header 
///file for a constant table definition.
///</summary>
///<remarks>
///As argument to the property macro, pass the type name of the generated enumeration.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_isihdr_generate_as_enum_macro.txt"/>
///which generates the following in the -bit ISI header file.
///<code filename="property_isihdr_generate_as_enum_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_AS_ENUM_16"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_AS_ENUM_8,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_BITFIELDS" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///When this value property is set, <b>bitxx</b> types are generated rather than <b>uintxx</b> in the ISI header file 
///for those bit tables that have the property <see cref_property="PROPERTY_ISIHDR_GENERATE_AS_BITFIELD" /> set.<br/><br/>
///</summary>
///<remarks>For example, see <see cref_property="PROPERTY_ISIHDR_GENERATE_AS_BITFIELD" /></remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_AS_BITFIELD"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_BITFIELDS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS_16" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_BITTABLE_MASKS_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_BOOLS" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///When this value property is set, boolxx types are generated rather than uintxx in the ISI header file 
///for those tables that have the property <see cref_property="PROPERTY_ISIHDR_GENERATE_AS_BOOL" />.<br/>
///Several predefined constant tables, such as TRUE/FALSE and ON/OFF, have this property.
///</summary>
///<remarks>For example, see <see cref_property="PROPERTY_ISIHDR_GENERATE_AS_BOOL" /></remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_AS_BOOL" />
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_BOOLS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
	PROPERTY_ISIHDR_GENERATE_CHOICE_UNIONS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property causes additional constants to be generated in the 8-bit ISI header file for the resource it is applied to. The constants are generated for merged fields, and can be used to extract the values of the individual fields from the merged field.</summary>
///<remarks></remarks>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16"/>
///<seealso cref_property="PROPERTY_ISIHDR_MERGED_MASK_PREFIX"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_MERGED_MASKS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property works exactly like <see cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS" />, 
///except it applies to 16-bit ISI header files.
///</summary>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS"/>
///<seealso cref_property="PROPERTY_ISIHDR_MERGED_MASK_PREFIX"/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS_16" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_MIN_MAX_CONSTANTS_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX_16" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_STRUCT_BYTE_INDEX_16,

/*
///<property name="PROPERTY_ISIHDR_GENERATE_SUBMSG_UNIONS_16" group="ISI header properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_ISIHDR_GENERATE_SUBMSG_UNIONS_16,

/*
///<property name="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this property is set, the PhoNet header items are inserted in all the message structures 
///in the 8-bit ISI header file.
///</summary>
///<remarks>
///If these elements should not be inserted in a particular message structure, 
///property <see cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE"/> can be set on that message.<br/>
///The actual layout of the generated items depend on the property <see cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT"/>.
///<br/><br/>
///Example, showing use of property:<code filename="property_isihdr_include_phonet_header_macro.txt"/>
///which generates the following in the ISI header file, using layout type 0:<code filename="property_isihdr_phonet_header_layout_isihdr_0.txt"/>
///and the following, using layout type 1:<code filename="property_isihdr_phonet_header_layout_isihdr_1.txt"/>
///and the following, using layout type 2:<code filename="property_isihdr_phonet_header_layout_isihdr_2.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" />
///<seealso cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE" />
///<seealso cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT" />
///</property>
*/
    PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER,

/*
///<property name="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this property is set, the PhoNet header items are inserted in all the message structures 
///in the 16-bit ISI header file.
///</summary>
///<remarks>
///If these elements should not be inserted in a particular message structure, 
///property <see cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE"/> can be set on that message.<br/>
///The actual layout of the generated items depend on the property <see cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT"/>.
///<br/><br/>
///Example, showing use of property:<code filename="property_isihdr_include_phonet_header_16_macro.txt"/>
///which generates the following in the ISI header file, using layout type 0:<code filename="property_isihdr_phonet_header_layout_isihdr_16_0.txt"/>
///and the following, using layout type 1:<code filename="property_isihdr_phonet_header_layout_isihdr_16_1.txt"/>
///and the following, using layout type 2:<code filename="property_isihdr_phonet_header_layout_isihdr_16_2.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" />
///<seealso cref_property="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE" />
///<seealso cref_property="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT" />
///</property>
*/
    PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16,

/*
///<property name="PROPERTY_ISIHDR_MERGED_MASK_PREFIX" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This property has no effect unless <see cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS" /> 
///or <see cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16" /> have been set. 
///It causes the names defined by these properties to be prefixed with the given string.</summary>
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS" />
///<seealso cref_property="PROPERTY_ISIHDR_GENERATE_MERGED_MASKS_16" />
///</property>
*/
    PROPERTY_ISIHDR_MERGED_MASK_PREFIX,

/*
///<property name="PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE" group="ISI header properties">
///<types>
///<type>value</type>
///</types>
///<summary>This property disables phonet header generation for this particular message structure.</summary>
///<remarks>
///The property has only effect, if PhoNet header generation is enabled for the resource using either 
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER"/> or 
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16"/>.
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" />
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" />
///</property>
*/
    PROPERTY_ISIHDR_PHONET_HEADER_DONT_GENERATE,

/*
///<property name="PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT" group="ISI header properties">
///<types>
///<type>value</type>
///</types>
///<summary>This property controls the layout of the items in the PhoNet header in the generated ISI header file.
///</summary>
///<remarks>
///Supported values for the layout are 0, 1 and 2.
///<br/>
///For 8-bit and 16-bit ISI headers, this property only has effect if the properties 
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" /> or 
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" /> have been set, respectively.
///<br/>
///For HTML, this property only has effect if the properties <see cref_property="PROPERTY_HTML_INCLUDE_PHONET_HEADER" /> 
///and <see cref_property="PROPERTY_HTML_INCLUDE_VARNAME_COLUMN" /> both have been set.
///<br/><br/>
///For examples of using this property, please refer to 
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" /> and
///<see cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" />. 
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER_16" />
///<seealso cref_property="PROPERTY_ISIHDR_INCLUDE_PHONET_HEADER" />
///<seealso cref_property="PROPERTY_HTML_INCLUDE_PHONET_HEADER" />
///<seealso cref_property="PROPERTY_HTML_INCLUDE_VARNAME_COLUMN" />
///</property>
*/
    PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_AS_ARRAY" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>If this property is set on an item, 
///the item will be generated as an array of bytes in the ISI header file.
///</summary>
///<remarks>
///Example, showing use of the property:
///<code filename="property_isihdr_split_as_array_macro.txt"/>
///which generates the following in the 8-bit ISI header file:
///<code filename="property_isihdr_split_as_array_isihdr_with_8.txt"/>
///and the following in the 16-bit ISI header file:
///<code filename="property_isihdr_split_as_array_isihdr_with_16.txt"/>
///Without the property, the following would have been generated:
///<code filename="property_isihdr_split_as_array_isihdr_without.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_AS_ARRAY,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_DWORDS_16" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this property is set, all 32-bit value variables are split to word variables in the 16-bit 
///ISI header file.</summary>
///<remarks>The prefix <b>_msw</b> and <b>_lsw</b> are added the two new variables
///<br/><br/>
///Example, showing use of the property:
///<code filename="property_isihdr_split_dwords_16_macro.txt"/>
///which generates the following in the 16-bit ISI header file:
///<code filename="property_isihdr_split_dwords_16_isihdr_with.txt"/>
///Without the property, the following would have been generated:
///<code filename="property_isihdr_split_dwords_16_isihdr_without.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_DWORDS_16,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>When applied to a 32-bit item, 
///this property causes the item to be generated as two signed 16-bit words in the ISI header file.
///</summary>
///<remarks>
///The variable name of the first word is simply the variable name of the original 32-bit item, 
///while the variable name of the second word is the property parameter.
///<br/><br/>
///Example of splitting a 32-bit value to two signed 16-bit values:
///<code filename="property_isihdr_split_dword_signed_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_split_dword_signed_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>When applied to a 32-bit item, 
///this property causes the item to be generated as two unsigned 16-bit words in the ISI header file.
///</summary>
///<remarks>
///The variable name of the first word is simply the variable name of the original 32-bit item, 
///while the variable name of the second word is the property parameter.
///<br/><br/>
///Example of splitting a 32-bit value to two unsigned 16-bit values:
///<code filename="property_isihdr_split_dword_unsigned_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_split_dword_unsigned_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>When applied to a 16-bit item, 
///the property causes the item to be generated as two signed bytes in the ISI header file.
///</summary>
///<remarks>
///The variable name of the first generated byte is simply the variable name of the original 16-bit item, 
///while the variable name of the second byte is the property parameter.
///<br/><br/>
///Example of splitting a 16-bit value into two signed 8-bit values:
///<code filename="property_isihdr_split_word_signed_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_split_word_signed_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_WORD_SIGNED,

/*
///<property name="PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>When applied to a 16-bit item, 
///the property causes the item to be generated as two unsigned bytes in the ISI header file.
///</summary>
///<remarks>
///The variable name of the first generated byte is simply the variable name of the original 16-bit item, 
///while the variable name of the second byte is the property parameter.
///<br/><br/>
///Example of splitting a 16-bit value into two unsigned 8-bit values:
///<code filename="property_isihdr_split_word_unsigned_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_split_word_unsigned_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_WORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED"/>
///<seealso cref_property="PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED"/>
///</property>
*/
    PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the name for the structure length definition for the object 
///(message, sub block or sequence) in the ISI header file (8-bit and 16-bit).
///</summary>
///<remarks>
///If no structure length name is defined, 
///autogen provides a default name, <b>SIZE_XXX_STR</b>, where <b>XXX</b> is the name of the object, 
///e.g. message name.
///<br/><br/>
///Example of changing the structure length name using this property:
///<code filename="property_isihdr_struct_length_name_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_length_name_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SUM" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_NAME" />
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_LENGTH_NAME,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF" group="ISI header properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property causes the structure length in the ISI header file to be 
///defined as a sizeof calculation.
///</summary>
///<remarks>
///Example, showing use the property:
///<code filename="property_isihdr_struct_length_sizeof_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_length_sizeof_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SUM" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_NAME" />
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_LENGTH_SUM" group="ISI header properties">
///<types>
///<type>siple</type>
///</types>
///<summary>This property causes the structure length in the ISI header file to be defined as a sum 
///of sizes of the individual items.
///</summary>
///<remarks>
///Example, showing use the property:
///<code filename="property_isihdr_struct_length_sum_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_length_sum_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_NAME" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_NAME" />
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_LENGTH_SUM,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE" group="ISI header properties">
///<types>
///<type>value</type>
///</types>
///<summary>This property is used to explicitly set the value of the size constant generated for structures.
///</summary>
///<remarks>
///If this property is not set, autogen generates a constant expression that calculates the size. 
///Any expression can be used, but it must evaluate to a number both when compiling autogen and 
///when compiling the product software.
///<br/><br/>
///Example of changing the structure length using this property:
///<code filename="property_isihdr_struct_length_value_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_length_value_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_DONT_GENERATE" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SIZEOF" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_SUM" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE" />
///<seealso cref_property="PROPERTY_ISIHDR_STRUCT_NAME" />
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_LENGTH_VALUE,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the structure name for the object (message, sub block or sequence) 
///in the ISI header file (8-bit and 16-bit).
///</summary>
///<remarks>
///If no structure name is defined, autogen provides a default name, 
///<b>XXX_STR</b>, where <b>XXX</b> is the name of the object (e.g. message name).
///<br/><br/>
///Example of changing the structure name using this property:
///<code filename="property_isihdr_struct_name_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_name_isihdr.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ISIHDR_DONT_GENERATE" />
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_NAME,

/*
///<property name="PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>Adds a size constant to the message structure in the ISI header file, 
///which includes the receiver and sender object fields.</summary>
///<remarks>
///Example, showing use of property:
///<code filename="property_isihdr_struct_phonet_length_name_macro.txt"/>
///which generates the following in the ISI header file:
///<code filename="property_isihdr_struct_phonet_length_name_isihdr.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_STRUCT_PHONET_LENGTH_NAME,

/*
///<property name="PROPERTY_ISIHDR_TITLE" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the title of the ISI header file. 
///If no title is defined, autogen uses the ISI header filename as title.
///</summary>
///<remarks>
///For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_TITLE,

/*
///<property name="PROPERTY_ISIHDR_VARNAME_16" group="ISI header properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property set the variable name to be generated in the 16-bit ISI header file when auto-merging 
///two 8-bit items.
///</summary>
///<remarks>
///Default, autogen merges two 8-bit items in the 16-bit ISI header file by combining 
///the two variable names with an underscore between.
///<br/><br/>
///Example, showing use of the property:
///<code filename="property_isihdr_varname_16_macro.txt"/>
///which generates the following in the 16-bit ISI header file:
///<code filename="property_isihdr_varname_16_isihdr_with.txt"/>
///Without the property, the following would have been generated:
///<code filename="property_isihdr_varname_16_isihdr_without.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_ISIHDR_VARNAME_16,

/*
///<property name="PROPERTY_ISI_VERSIONING_NOT_SUPPORTED" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property disables ISI versioning support.</summary>
///<remarks>
///When the property is used, the versioning arguments are obolete, and nothing related to ISI versioning is generated to outputs
///</remarks>
///</property>
*/
    PROPERTY_ISI_VERSIONING_NOT_SUPPORTED,

/*
///<property name="PROPERTY_ISI_VERSION_AUTO_GENERATE" group="Versioning properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property determines from which version of the resource, 
///version history will be auto-generated.</summary>
///<remarks>
///If the property is not present, version history will be auto-generated for all versions.
///</remarks>
///</property>
*/
	PROPERTY_ISI_VERSION_AUTO_GENERATE,

/*
///<property name="PROPERTY_ITEM_DEFAULT_VALUE" group="Item properties">
///<types>
///<type>value</type>
///</types>
///<summary>Sets the default value of the item that it is applied to</summary>
///<remarks>
///The default value is used when building messages in the PMD Message Sender, XML or the TSS Server API. 
///For backward compatibility, all changed message items should be applied a default 
///value of 0 using this property.
///<br/>
///Note that the property must be used with either <see cref_macro="PROPERTY_VALUE"/> or <see cref_macro="PROPERTY_STRING"/>
///depending on the type of message item that it is attached to. Please see examples below.
///<br/><br/>
///The following example shows how to define a default value for a constant. 
///<see cref_macro="PROPERTY_STRING"/> must be used:
///<code filename="property_item_default_value_macro_consttbl.txt"/>
///The following example shows how to define a default value for a bitfield. 
///Again <see cref_macro="PROPERTY_STRING"/> must be used:
///<code filename="property_item_default_value_macro_bittbl.txt"/>
///The following example shows how to define a default value for a normal value.
///Here <see cref_macro="PROPERTY_VALUE"/> must be used:
///<code filename="property_item_default_value_macro_value.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///</property>
*/
    PROPERTY_ITEM_DEFAULT_VALUE,

/*
///<property name="PROPERTY_ITEM_EXCEPTIONAL_VALUE" group="Item properties">
///<types>
///<type>value</type>
///<type>string</type>
///</types>
///<summary>Indicates that the given value is an exceptional value for the item it is applied to.
///</summary>
///<remarks>
///Exceptional values can be defined in two ways, using either <see cref_macro="PROPERTY_VALUE"/> or 
///<see cref_macro="PROPERTY_STRING"/>. If the value is defined using <b>#define</b> in the macro file, or
///is simply a number, e.g. <b>0x00</b>, <see cref_macro="PROPERTY_VALUE"/> should be used.
///<br/><br/>
///Exceptional values will appear in the HTML documentation and in PMD decoding (as well as PMD encoding). 
///In ISI header files, a constant definition will be generated, if the value is defined as a symbolic name.
///<br/><br/>
///If a minimum and/or maximum value property has been 
///defined, using <see cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/> and/or <see cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>, 
///the exceptional value(s) should lie outside these bounds.
///<br/><br/>
///Multiple different exceptional values may be assigned to the same item.
///<br/><br/>
///Example of defining an execptional value to an item:
///<code filename="property_item_exceptional_value_macro.txt"/>
///Example, where the value is defined implicitly in the macro file, 
///<code filename="property_item_exceptional_value_macro_string.txt"/>
///Note that the output of the two examples (ISI header, HTML and PMD) are identical.
///<br/><br/>
///For an example, including minimum and maximum value properties, 
///see <see cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>.
///</remarks>
///<seealso cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///</property>
*/
    PROPERTY_ITEM_EXCEPTIONAL_VALUE,


/*
///<property name="PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION" group="Item properties">
///<types>
///<type>value</type>
///<type>string</type>
///</types>
///<summary>Indicates that the item, to which the property is applied was a filler before the specified version.
///</summary>
///<remarks>
///Filler replacement is considered a minor change (backward compatible), thus the default value of the new 
///field must be 0 or, for <see cref_macro="VALUE_CONST"/>, the <see cref_macro="CONST_TBL_ENTRY"/> or the <see cref_macro="BIT_TBL_ENTRY"/> corresponding to the value 0.
///<br/><br/>
///PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION must always be accompanied by <see cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>. 
///<br/><br/>
///The effect of the property is that autogen records the filler replacement in the version history.
///<br/><br/>
///Example, showing a message with a filler byte being replaced in version 001.001: <code filename="property_item_filler_replacement_version_before_m.txt"/>
///Same message after replacing filler with VALUE:  <code filename="property_item_filler_replacement_version_after_m.txt"/>
///<br/>
///Same message after replacing filler with VALUE_CONST:  <code filename="fillerReplacementVersionValueConstMacro.txt"/>
///<br/>
///</remarks>
///<seealso cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///</property>
*/
    PROPERTY_ITEM_FILLER_REPLACEMENT_VERSION,

/*
///<property name="PROPERTY_ITEM_MAXIMUM_VALUE" group="Item properties">
///<types>
///<type>value</type>
///<type>string</type>
///</types>
///<summary>Indicates that the given value is the maximum acceptable value for the item it is applied to.</summary>
///<remarks>
///Maximum values can be defined in two ways, using either <see cref_macro="PROPERTY_VALUE"/> or 
///<see cref_macro="PROPERTY_STRING"/>. If the values are defined using <b>#define</b> in the macro file, or
///is simply a number, e.g. <b>0x00</b>, <see cref_macro="PROPERTY_VALUE"/> should be used.
///<br/><br/>
///The maximum value will appear in the HTML documentation, and warnings are issued in detailed PMD decoding for values 
///that exceed this maximum (unless it's an exceptional value).
///In ISI header files, a constant definition will be generated, if the value is defined as a symbolic name.
///<br/><br/>
///Example of defining a value with minimum, maximum and exceptional information:
///<code filename="property_item_minmax_value_macro.txt"/>
///In HTML, the following comment will be generated for the value:
///<code filename="property_item_minmax_value_html.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MINIMUM_VALUE"/>
///</property>
*/
    PROPERTY_ITEM_MAXIMUM_VALUE,

/*
///<property name="PROPERTY_ITEM_MINIMUM_VALUE" group="Item properties">
///<types>
///<type>value</type>
///<type>string</type>
///</types>
///<summary>Indicates that the given value is the minimum acceptable value for the item it is applied to.</summary>
///<remarks>
///Minimum values can be defined in two ways, using either <see cref_macro="PROPERTY_VALUE"/> or 
///<see cref_macro="PROPERTY_STRING"/>. If the values are defined using <b>#define</b> in the macro file, or
///is simply a number, e.g. <b>0x00</b>, <see cref_macro="PROPERTY_VALUE"/> should be used.
///<br/><br/>
///The minimum value will appear in the HTML documentation, and warnings are issued in detailed PMD decoding for values 
///that exceed this minimum (unless it's an exceptional value).
///In ISI header files, a constant definition will be generated, if the value is defined as a symbolic name.
///<br/><br/>
///For an example of defining a value with minimum boundary information, see <see cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>.
///</remarks>
///<seealso cref_property="PROPERTY_ITEM_DEFAULT_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_EXCEPTIONAL_VALUE"/>
///<seealso cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/>
///</property>
*/
    PROPERTY_ITEM_MINIMUM_VALUE,

/*
///<property name="PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC" group="Message properties">
///<not_to_be_documented/>
///<types>
///<type>simple</type>
///</types>
///<summary>This property is useful only for media controller. <br />
///Indicates that the message is a media control message specific message, which can not be sent to the media modules.</summary>
///<remarks></remarks>
///</property>
*/
    PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC,

/*
///<property name="PROPERTY_MSG_LENGTH_LIMIT" group="Message properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_MSG_LENGTH_LIMIT,

/*
///<property name="PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY" group="Message properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this property is set, the message length is only the length of the data part, 
///and does not include the header fields themselves.</summary>
///</property>
*/
    PROPERTY_MSG_LENGTH_RELATES_TO_DATA_PART_ONLY,

/*
///<property name="PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When this property is set, sensitive information is not generated to ISI header 
///and HTML documentation.</summary>
///<remarks>
///It is recommended to apply the property inside #ifdef ... #endif as illustrated below
///<code filename="apply_prop_nokia_3rd_party.txt"/>
///and leave the lines in the message macro file for future use.
///<br/><br/>
///To activate generation of 3rd party vendor output, simply add the following #define to autogen_local_conf.h
///<code filename="activate_nokia_3rd_party_output.txt"/>
///Remember to remove #define afterwards!
///</remarks>
///</property>
*/
    PROPERTY_NOKIA_3RD_PARTY_VENDOR_OUTPUT,

/*
///<property name="PROPERTY_PMD_ANCHOR" group="PMD properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_ANCHOR,

/*
///<property name="PROPERTY_PMD_DONT_GENERATE" group="PMD properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///The property assures that a certain object (e.g. message or message element) is not generated in the PMD file.
///</summary>
///<remarks>
///The following example shows how to disable generation of a sub block in the PMD file:
///<code filename="property_pmd_dont_generate_macro_sb.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_PMD_DONT_GENERATE,

/*
///<property name="PROPERTY_PMD_ENVIRONMENT_VARIABLE" group="PMD properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets a global PMD environment variable</summary>
///<remarks>
///An environment variable property can be set everywhere, 
///and it always affects the entire PMD file regardless of the placement of the property. 
///</remarks>
///</property>
*/
    PROPERTY_PMD_ENVIRONMENT_VARIABLE,

/*
///<property name="PROPERTY_PMD_IS_NOT_PARAMETER" group="Item properties">
///<types>
///<type>simple</type>
///</types>
///<summary>Indicates that the given item is not marked as a parameter in the PMD file.</summary>
///<remarks>As a parameter, the item is displayed in compact PMD decoding.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_PARAMETER"/>
///</property>
*/
    PROPERTY_PMD_IS_NOT_PARAMETER,

/*
///<property name="PROPERTY_PMD_MESSAGE_IN_SUMMARY" group="Message properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that the given message is decoded as part of summary generated 
///when converting BLX files to ASCII and as part of public peer views in FastTrace.
///</summary>
///<remarks>
///Some items in the message can be decoded as well, 
///if the property <see cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/> 
///is set on these.
///<br/><br/>
///FastTrace 2.4 will support this property.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///<seealso cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///</property>
*/
    PROPERTY_PMD_MESSAGE_IN_SUMMARY,

/*
///<property name="PROPERTY_PMD_MESSAGE_IS_CARRIER" group="PMD properties">
///<not_to_be_documented/>
///</property>
*/

    PROPERTY_PMD_MESSAGE_IS_CARRIER,

/*
///<property name="PROPERTY_PMD_MESSAGE_IS_NOT_FILTERABLE" group="PMD properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_MESSAGE_IS_NOT_FILTERABLE,

/*
///<property name="PROPERTY_PMD_NUMBER_SPECIAL_TYPE" group="Item properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_NUMBER_SPECIAL_TYPE,

/*
///<property name="PROPERTY_PMD_PARAMETER" group="Item properties">
///<types>
///<type>simple</type>
///</types>
///<summary>Indicates that the given item is marked as a parameter in the PMD file.</summary>
///<remarks>As a parameter, the item is displayed in compact PMD decoding.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_IS_NOT_PARAMETER"/>
///</property>
*/
    PROPERTY_PMD_PARAMETER,

/*
///<property name="PROPERTY_PMD_PARAMETER_IN_SUMMARY" group="Item properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that the given item will be decoded as part of summaries generated 
///when converting BLX files to ASCII and as part of public peer views in FastTrace.
///</summary>
///<remarks>
///For this property to have effect, 
///the property <see cref_property="PROPERTY_PMD_MESSAGE_IN_SUMMARY"/> or 
///<see cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/> 
///must be set on the message/trace 
///containing the item.
///<br/><br/>
///FastTrace 2.4 will support this property.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_MESSAGE_IN_SUMMARY"/>
///<seealso cref_property="PROPERTY_PMD_TRACE_IN_SUMMARY"/>
///</property>
*/
    PROPERTY_PMD_PARAMETER_IN_SUMMARY,

/*
///<property name="PROPERTY_PMD_PHONET_DEVICE_ID" group="Resource properties">
///<types>
///<type>value</type>
///</types>
///<summary>This value property defines the symbolic device ID for the resource.</summary>
///<remarks>
///The property should be used when defining a PhoNet/ISI resource, which is not a MCU resource, 
///or in other words, when defining a resource, not using device <b>PN_DEV_HOST</b>.
///<br/><br/>
///When encoding messages with PMD/XML, this property will be used to ensure that the message is 
///sent to the correct device.
///<br/><br/>
///The value of the device ID must exist in <b>pn_const.h</b>, or autogen doesn't compile!
///<br/><br/>
///Example, showing use of the property:
///<code filename="property_pmd_phonet_device_id_macro.txt"/>
///</remarks>
///<seealso cref_property="PROPERTY_PMD_PHONET_OBJECT_ID" />
///</property>
*/
    PROPERTY_PMD_PHONET_DEVICE_ID,

/*
///<property name="PROPERTY_PMD_PHONET_OBJECT_ID" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>This string property defines the symbolic object ID for the resource.</summary>
///<remarks>
///This property is relevant when defining private interfaces (using <b>PN_PRIVATE</b> resource ID). 
///<b>PN_PRIVATE</b> is not a valid address, so object ID <b>PN_OBJ_ROUTING_REQ</b> can't be used. 
///The only way to send messages to these objects is by using correct object ID as receiver object.
///<br/><br/>
///Object ID values are generated during build time to the file <b>pn_obj_auto.h</b>. 
///The property defines the object ID by name, and the value is resolved when generating the PMD file, 
///by looking up the name in <b>pn_obj_auto.h</b>. If the name is not found (due to misspell?), 
///<b>PN_OBJ_ROUTING_REQ</b> is used, and this basically means that the object can't be accessed from PC!
///<br/><br/>
///Note, that the property only works for MCU ISI resources. Besides, only one object ID can be assigned, 
///and some objects have a range of possible object ID's.
///<br/><br/>
///Example, showing use of the property:
///<code filename="property_pmd_phonet_object_id_macro.txt"/>
///An entire message macro template for private interfaces: 
///<see cref_example="Template file for private ISI resources"/>
///<br/><br/>
///For a more general description of private interfaces, see 
///<see cref_topic="ISI private resources"/>
///</remarks>
///<seealso cref_property="PROPERTY_PMD_PHONET_DEVICE_ID" />
///</property>
*/
    PROPERTY_PMD_PHONET_OBJECT_ID,

/*
///<property name="PROPERTY_PMD_PROTOCOL_IS_LE" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///This property is applied to RES_BEGIN(RESOURCE_PROTOCOL, ...) to indicate to autogen
///that the protocol is running in Little Endian. This information will be stored in the PMD file.
///</summary>
///<remarks>
///</remarks>
///</property>
*/
    PROPERTY_PMD_PROTOCOL_IS_LE,

/*
///<property name="PROPERTY_PMD_PUBLIC" group="PMD properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_PUBLIC,

/*
///<property name="PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER" group="PMD properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///This property is applied to RES_BEGIN(RESOURCE_TRC_MASTER, ...) to indicate to autogen
///that the resource holds Master HW traces. This information will be stored in the PMD file.
///</summary>
///<remarks>
///For this property to have effect, resource type must be RESOURCE_TRC_MASTER.
///Example, showing use of the property:
///<code filename="property_pmd_resource_trc_is_hw_master_macro.txt"/>
///<br/><br/>
///For a description of Master HW Traces, see 
///<see cref_topic="XTI master HW traces"/>
///</remarks>
///</property>
*/
    PROPERTY_PMD_RESOURCE_TRC_IS_HW_MASTER,

/*
///<property name="PROPERTY_PMD_RESTRICTED" group="PMD properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_RESTRICTED,

/*
///<property name="PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON" group="Trace properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When set on a trace group / trace, this trace (group) will be shown as default ON in the trace activation UI. Should be done, if trace(group) is default on in product.
///</summary>
///<remarks>
///</remarks>
///</property>
*/
    PROPERTY_PMD_TRACE_ACTIVATION_DEFAULT_STATE_ON,

/*
///<property name="PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE" group="Trace properties">
///<types>
///<type>simple</type>
///</types>
///<summary>When set on a trace group / trace, this name will not be shown in the trace activation UI in FastTrace. 
///</summary>
///<remarks>
///</remarks>
///</property>
*/
    PROPERTY_PMD_TRACE_ACTIVATION_EXCLUDE,

/*
///<property name="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" group="Trace properties">
///<types>
///<type>string</type>
///</types>
///<summary>For DSP5 traces, the trace activation entry in FastTrace is the name of the DSP5 trace sub block definition. 
///Using this property on the sub block, the trace activation name can be overruled.
///</summary>
///<remarks>
///The argument to the macro must be one of the DSP5 trace source constants from <b>pmd_constants.h</b>.
///<br/>
///This property only works when set on DSP5 trace sub blocks.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_LOGICAL_GROUP" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_FLAGS" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_NAME" />
///</property>
*/
    PROPERTY_PMD_TRACE_ACTIVATION_TEXT,

/*
///<property name="PROPERTY_PMD_TRACE_DECODE_TEXT" group="Trace properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_TRACE_DECODE_TEXT,

/*
///<property name="PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT" group="Trace properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_PMD_TRACE_GROUP_DECODE_TEXT,

/*
///<property name="PROPERTY_PMD_TRACE_IDENTIFIER" group="Trace properties">
///<types>
///<type>string</type>
///</types>
///<summary>
///This property defines the trace identifier for a certain group of traces. The trace identifi This affects the way DSP5 traces are displayed during trace activation in FastTrace.
///</summary>
///<remarks>
///The trace identifier is a 4 character name, which is displayed when a trace is decoded with PMD in compact format. 
///<br/><br/>
///See <see cref_topic="General trace structure"/> for a general description of trace structures and how to use this property.
///</remarks>
///</property>
*/
    PROPERTY_PMD_TRACE_IDENTIFIER,

/*
///<property name="PROPERTY_PMD_TRACE_LOGICAL_GROUP" group="Trace properties">
///<types>
///<type>string</type>
///</types>
///<summary>
///This property causes the trace to be associated with the given logical group. This affects the way DSP5 traces are displayed during trace activation in FastTrace.
///</summary>
///<remarks>
///This property only works when set on DSP5 trace sub blocks.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_FLAGS" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_NAME" />
///</property>
*/
    PROPERTY_PMD_TRACE_LOGICAL_GROUP,

/*
///<property name="PROPERTY_PMD_TRACE_SOURCE" group="Trace properties">
///<types>
///<type>value</type>
///</types>
///<summary>
///This property defines the trace source for DSP5 trace sub block definition.
///</summary>
///<remarks>
///The argument to the macro must be one of the DSP5 trace source constants from <b>pmd_constants.h</b>.
///<br/>
///This property only works when set on DSP5 trace sub blocks.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" />
///<seealso cref_property="PROPERTY_PMD_TRACE_LOGICAL_GROUP" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_FLAGS" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_NAME" />
///</property>
*/
    PROPERTY_PMD_TRACE_SOURCE,

/*
///<property name="PROPERTY_PMD_TRACE_SOURCE_FLAGS" group="Trace properties">
///<types>
///<type>value_index</type>
///</types>
///<summary>
///This property sets flags for the trace source given as first argument to the macro.
///</summary>
///<remarks>
///The trace source is identified by one of the DSP5 (ADSP or CDSP) trace source constants 
///in the autogen file <b>pmdconstants.h.</b>.
///<br/>
///Following flags are supported: <see cref_enum="E_DSP5_TRACE_SOURCE_FLAGS" />.
///<br/><br/>
///This property can be used in any context.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" />
///<seealso cref_property="PROPERTY_PMD_TRACE_LOGICAL_GROUP" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_NAME" />
///</property>
*/
    PROPERTY_PMD_TRACE_SOURCE_FLAGS,

/*
///<property name="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" group="Trace properties">
///<types>
///<type>string_index</type>
///</types>
///<summary>
///This property defines the trace identifier for the trace source given as first argument to the macro. 
///</summary>
///<remarks>
///The trace identifier is a 4 character name, which is displayed when the trace is decoded with PMD. 
///Default, "cdsp" is used for any DSP5 CDSP trace source and "adsp" is used for any DSP5 ADSP trace source. 
///<br/><br/>
///This property can be used in any context.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" />
///<seealso cref_property="PROPERTY_PMD_TRACE_LOGICAL_GROUP" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_FLAGS" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_NAME" />
///</property>
*/
    PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER,

/*
///<property name="PROPERTY_PMD_TRACE_SOURCE_NAME" group="Trace properties">
///<types>
///<type>string_index</type>
///</types>
///<summary>
///This property defines the printable name for the trace source given as first argument to the macro. 
///</summary>
///<remarks>
///The trace source name is displayed in Trace Activation in FastTrace as the trace type. 
///<br/>
///autogen contains a list of names to be used default. The names in the list are overruled with this property.
///<br/><br/>
///This property can be used in any context.
///<br/><br/>
///See <see cref_topic="DSP5 traces"/> for a general description of DSP5 traces and an example of using the propety.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_TRACE_ACTIVATION_TEXT" />
///<seealso cref_property="PROPERTY_PMD_TRACE_LOGICAL_GROUP" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_FLAGS" />
///<seealso cref_property="PROPERTY_PMD_TRACE_SOURCE_IDENTIFIER" />
///</property>
*/
    PROPERTY_PMD_TRACE_SOURCE_NAME,

/*
///<property name="PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT" group="PMD properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///The property can only be applied to a CONST_TBL.
///</summary>
///<remarks>
///The property causes autogen to store the comment field rather than the name of a CONST_TBL_ENTRY in the PMD file.
///</remarks>
///</property>
*/
    PROPERTY_PMD_USE_CONST_TBL_ENTRY_COMMENT,

/*
///<property name="PROPERTY_PROJECT_CONFIDENTIALITY" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets the confidentiality that should appear in HTML and ISI header files. 
///If this property has not been set, autogen uses "CONFIDENTIAL".</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_PROJECT_CONFIDENTIALITY,

/*
///<property name="PROPERTY_PROJECT_NAME" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets the project name that should appear in HTML and ISI header files.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_PROJECT_NAME,

/*
///<property name="PROPERTY_PROJECT_NOKIA_ENTITY" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets the business entity that should appear in HTML and ISI header files. If this property has not been set, autogen uses "Nokia Mobile Phones" or "NOKIA MOBILE PHONES" depending on context.</summary>
///</property>
*/
    PROPERTY_PROJECT_NOKIA_ENTITY,

/*
///<property name="PROPERTY_PROJECT_OWNER_NAME" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets the document owner name that should appear in HTML and ISI header files.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_PROJECT_OWNER_NAME,

/*
///<property name="PROPERTY_PROJECT_SITE_NAME" group="Resource properties">
///<types>
///<type>string</type>
///</types>
///<summary>Sets the project site name that should appear in HTML and ISI header files.</summary>
///<remarks>For an example of using this property, 
///see <see cref_example="Template file for ISI resources"/></remarks>
///</property>
*/
    PROPERTY_PROJECT_SITE_NAME,

/*
///<property name="PROPERTY_PROTOCOL_HAS_NO_MESSAGES" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>Defines that the resource has no messages.</summary>
///<remarks>The protocol must still be defiend as a message, 
///just jusing the message type MESSAGE_NONE.</remarks>
///</property>
*/
    PROPERTY_PROTOCOL_HAS_NO_MESSAGES,

/*
///<property name="PROPERTY_SB_LENGTH_LIMIT" group="Sub block properties">
///<types>
///<type>value</type>
///</types>
///<summary>This property defines a maximum length of the sub block.</summary>
///<remarks>
///When used, autogen will use this value rather than calculate a value on its own. 
///This could result in some length warnings not being shown by autogen.
///<br/><br/>
///Is especially relevant when sub blocks contain nested sub blocks. 
///In cases like that, autogen sometimes report rather large possible 
///sub block lengths for the parent sub block.
///<br/><br/>
///The following example shows how to use the property:
///<code filename="property_sb_length_limit_macro.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_SB_LENGTH_LIMIT,

/*
///<property name="PROPERTY_SB_LENGTH_MISSING" group="Sub block properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property defines that the sub block does not contain a sub block length field.
///</summary>
///<remarks>
///Under normal circumstances, autogen expects a sub block to contain a sub block length field. 
///Setting this property, autogen will not require this. Can be used when defining sub blocks which don't follow ISA standards. 
///<br/><br/>
///The following example shows how to use the property:
///<code filename="property_sb_length_missing_macro.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_SB_LENGTH_MISSING,

/*
///<property name="PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4" group="Sub block properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///This property defines that the sub block is not necessarily divisible by 4 in length, as ISA rules demand.
///</summary>
///<remarks>
///Using this property will remove the length check on the sub block and thereby remove the generated warning.
///<br/><br/>
///The following example shows how to use the property:
///<code filename="property_sb_length_not_divisible_by_4_macro.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_4,

/*
///<property name="PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_8" group="Sub block properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///This property is for use with 64-bit macros only. 
///The property defines that the sub block is not necessarily divisible by 8 in length, as is required when 64-bit items are used.
///</summary>
///<remarks>
///Using this property will remove the length check on the sub block and thereby remove the generated warning.
///<br/><br/>
///</remarks>
///</property>
*/
    PROPERTY_SB_LENGTH_NOT_DIVISIBLE_BY_8,

/*
///<property name="PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY" group="Sub block properties">
///<types>
///<type>simple</type>
///</types>
///<summary>Defines that the sub block length relates to the data part rather than the whole sub block.
///</summary>
///<remarks>
///The following example shows how to use the property:
///<code filename="property_sb_length_relates_to_data_part_only_macro.txt"/>
///in this case, the sub block length field is expected to contain the value 2 rather than 4, which would be normal.
///</remarks>
///</property>
*/
    PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY,

/*
///<property name="PROPERTY_SEQ_ASSIGN_MESSAGE_TYPE" group="Sequence properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_SEQ_ASSIGN_MESSAGE_TYPE,

/*
///<property name="PROPERTY_STRING_BCD_MAP" group="Item properties">
///<types>
///<type>string</type>
///</types>
///<summary>
///This string property defines the mapping between BCD and ASCII characters for a BCD string item. 
///</summary>
///<remarks>
///The property string should contain 16 characters.
///<br/><br/>
///In case less than 16 characters are needed, 0-character padding must be placed at the end of the string.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_string_bcd_map_macro.txt"/>
///</remarks>
///</property>
*/
	PROPERTY_STRING_BCD_MAP,

/*
///<property name="PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH" group="Item properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Defines that the zero-termination is not part of the string length.
///</summary>
///<remarks>
///The property can only be used with zero-terminated strings with a length defined.
///<br/><br/>
///Example, showing use of property for a variable length string:
///<code filename="property_string_excl_zero_from_length.txt"/>
///If string length is 2, there are three bytes in the string.<br/><br/>
///Example, showing use of property for a fixed length string:
///<code filename="property_string_excl_zero_from_length_fixed.txt"/>
///</remarks>
///</property>
*/
    PROPERTY_STRING_EXCLUDE_ZERO_TERMINATION_FROM_LENGTH,

/*
///<property name="PROPERTY_STRING_MAXIMUM_LENGTH" group="Item properties">
///<types>
///<type>value</type>
///</types>
///<summary>
///Defines a maximum length for string without any length defined 
///(<b>REF_AS_LONG_AS_POSSIBLE</b> or <b>REF_LENGTH_DETERMINED_BY_ZERO</b>) 
///has been used as reference name).
///</summary>
///<remarks>
///The property indicates that the string length can't exceed the 
///given maximum length. This affects documentation, ISI header file output, 
///and length checks in PMD decoding/encoding. 
///<br/><br/>
///The maximum size can be given as a number or as a symbolic constant.
///<br/><br/>
///The following example defines a string, where the length is determined 
///by the terminating 0. However, there is a limit to the length, which 
///is defined with the property:
///<code filename="property_string_maximum_length_macro.txt"/>
///This generates the following in the ISI header file:
///<code filename="property_string_maximum_length_isihdr.txt"/>
///<br/>
///The property <see cref_property="PROPERTY_ARRAY_MAXIMUM_SIZE"/> 
///does the same thing for arrays.
///</remarks>
///<seealso cref_property="PROPERTY_ARRAY_MAXIMUM_SIZE"/> 
///</property>
*/
	PROPERTY_STRING_MAXIMUM_LENGTH,


/*
///<property name="PROPERTY_STRING_UNFORMATTED" group="Item properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Defines that the string formatting is done on PC side, such as the tracing SDK (FastTrace).
///</summary>
///</property>
*/
    PROPERTY_STRING_UNFORMATTED,


/*
///<property name="PROPERTY_SUBMSG_NAMES_ARE_UNIQUE" group="Resource properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that sub message namess are uniquely named within their resource, 
///and base name is removed when printing message name.
///</summary>
///<remarks>
///If this property is not set, 
///autogen assumes that there might be different sub messages 
///(with different base messages) 
///that have the same name, and will generate output that avoids any ambiguity.
///<br/><br/>
///Note that this flag does not affect the ISI header file output; 
///you need to explicitly specify a struct name and struct length name 
///for each clashing message.
///</remarks>
///</property>
*/
    PROPERTY_SUBMSG_NAMES_ARE_UNIQUE,

/*
///<property name="PROPERTY_SUPPRESS_AUTOGEN_WARNINGS" group="General properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Disables warnings in autogen.log for this definition
///</summary>
///</property>
*/
    PROPERTY_SUPPRESS_AUTOGEN_WARNINGS,

/*
///<property name="PROPERTY_TSA_NAMESPACE" group="Resource properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_TSA_NAMESPACE,

/*
///<property name="PROPERTY_VERSION_NOT_YET_SUPPORTED" group="Versioning properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property indicates that the ISI version is not yet supported.
///</summary>
///<remarks>
///This property will result in comments in the HTML document, 
///and will give a compile error if using the ISI header file with this ISI version.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_isi_version_not_yet_supported_macro.txt"/>.
///</remarks>
///<seealso cref_property="PROPERTY_VERSION_NO_LONGER_SUPPORTED"/>
///</property>
*/
    PROPERTY_VERSION_NOT_YET_SUPPORTED,

/*
///<property name="PROPERTY_VERSION_NO_LONGER_SUPPORTED" group="Versioning properties">
///<types>
///<type>simple</type>
///</types>
///<summary>This property indicates that the ISI version is no longer supported.
///</summary>
///<remarks>
///This property will result in comments in the HTML document, 
///and will give a compile error if using the ISI header file with this ISI version. 
///The ISI header file contents are similar to the property 
///<see cref_property="PROPERTY_VERSION_NOT_YET_SUPPORTED"/>.
///<br/><br/>
///Example, showing use of property:
///<code filename="property_isi_version_no_longer_supported_macro.txt"/>.
///</remarks>
///<seealso cref_property="PROPERTY_VERSION_NOT_YET_SUPPORTED"/>
///</property>
*/
    PROPERTY_VERSION_NO_LONGER_SUPPORTED,

/*
///<property name="PROPERTY_XML_FILENAME" group="Resource properties">
///<not_to_be_documented/>
///</property>
*/
    PROPERTY_XML_FILENAME,

    /* obsolete properties */
    PROPERTY_HTML_PCMS_ITEM,
    PROPERTY_HTML_PCMS_PART,
    PROPERTY_ISIHDR_CONTINUUS_PROJECT_NAME,
    PROPERTY_ISIHDR_PCMS_ITEM,
    PROPERTY_ISIHDR_PCMS_ITEM_16,
    PROPERTY_ISIHDR_PCMS_PART,
    PROPERTY_ISIHDR_PCMS_WORKSET,

    PROPERTY_TOTAL_COUNT

} autogen_property_id;

/* compatible constants */
#define PROPERTY_PMD_TRACE_IS_NOT_FILTERABLE    PROPERTY_PMD_MESSAGE_IS_NOT_FILTERABLE

/*
///<property name="PROPERTY_PMD_TRACE_IN_SUMMARY" group="Trace properties">
///<types>
///<type>simple</type>
///</types>
///<summary>
///Indicates that the given trace is decoded as part of summary generated 
///when converting BLX files to ASCII and as part of public peer views in FastTrace.
///</summary>
///<remarks>
///Some items in the trace can be decoded as well, 
///if the property <see cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/> 
///is set on these.
///<br/><br/>
///FastTrace 2.4 will support this property.
///</remarks>
///<seealso cref_property="PROPERTY_PMD_MESSAGE_IN_SUMMARY"/>
///<seealso cref_property="PROPERTY_PMD_PARAMETER_IN_SUMMARY"/>
///</property>
*/
#define PROPERTY_PMD_TRACE_IN_SUMMARY     PROPERTY_PMD_MESSAGE_IN_SUMMARY


/* backward compatible constants */
#define COMMENT_ANCHOR                          PROPERTY_PMD_ANCHOR
#define AUTOGEN_COMMENT_ANCHOR                  PROPERTY_PMD_ANCHOR

#define COMMENT_CHANGE_PERSON                   PROPERTY_CHANGE_PERSON
#define COMMENT_CHANGE_REASON                   PROPERTY_CHANGE_REASON
#define COMMENT_CHANGE_DATE                     PROPERTY_CHANGE_DATE
#define COMMENT_CHANGE_REFERENCE                PROPERTY_CHANGE_REFERENCE
#define COMMENT_CHANGE_STATUS                   PROPERTY_CHANGE_STATUS
#define COMMENT_CONFIDENTIALITY                 PROPERTY_PROJECT_CONFIDENTIALITY
#define COMMENT_CONTINUUS_INSTANCE_NAME         PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME
#define COMMENT_CONTINUUS_PROJECT_NAME          PROPERTY_ISIHDR_CONTINUUS_PROJECT_NAME

#define COMMENT_DEFINITION_NAME                 PROPERTY_ISIHDR_DEFINITION_NAME
#define COMMENT_DISABLE_ALIGNMENT_CHECK         PROPERTY_ALIGNMENT_CHECK_DISABLE

#define COMMENT_HTML_CONTINUUS_PROJECT_NAME     PROPERTY_HTML_CONTINUUS_PROJECT_NAME
#define COMMENT_HTML_DOCUMENT_NUMBER            PROPERTY_HTML_DOCUMENT_NUMBER
#define COMMENT_HTML_FILENAME                   PROPERTY_HTML_FILENAME
#define COMMENT_HTML_TITLE                      PROPERTY_HTML_TITLE

#define COMMENT_INCLUDE_HTML_INTRODUCTION       PROPERTY_HTML_INCLUDE_INTRODUCTION
#define COMMENT_INCLUDE_PN_TRACE_OBJECTS        PROPERTY_INCLUDE_PN_TRACE_OBJECTS

#define COMMENT_ISIHDR_ALIAS_NAME               PROPERTY_ISIHDR_ALIAS_NAME
#define COMMENT_ISIHDR_DEFINITION_NAME          PROPERTY_ISIHDR_DEFINITION_NAME
#define COMMENT_ISIHDR_DONT_GENERATE            PROPERTY_ISIHDR_DONT_GENERATE
#define COMMENT_ISIHDR_FILENAME                 PROPERTY_ISIHDR_FILENAME
#define COMMENT_ISIHDR_FILENAME_16              PROPERTY_ISIHDR_FILENAME_16
#define COMMENT_ISIHDR_GENERATE_BITFIELDS       PROPERTY_ISIHDR_GENERATE_BITFIELDS
#define COMMENT_ISIHDR_GENERATE_BOOLS           PROPERTY_ISIHDR_GENERATE_BOOLS
#define COMMENT_ISIHDR_GENERATE_AS_BITFIELD     PROPERTY_ISIHDR_GENERATE_AS_BITFIELD
#define COMMENT_ISIHDR_GENERATE_AS_BOOL         PROPERTY_ISIHDR_GENERATE_AS_BOOL
#define COMMENT_ISIHDR_SPLIT_DWORD_UNSIGNED     PROPERTY_ISIHDR_SPLIT_DWORD_UNSIGNED
#define COMMENT_ISIHDR_SPLIT_DWORD_SIGNED       PROPERTY_ISIHDR_SPLIT_DWORD_SIGNED
#define COMMENT_ISIHDR_SPLIT_WORD_UNSIGNED      PROPERTY_ISIHDR_SPLIT_WORD_UNSIGNED
#define COMMENT_ISIHDR_SPLIT_WORD_SIGNED        PROPERTY_ISIHDR_SPLIT_WORD_SIGNED
#define COMMENT_ISIHDR_STRUCT_LENGTH_NAME       PROPERTY_ISIHDR_STRUCT_LENGTH_NAME
#define COMMENT_ISIHDR_STRUCT_NAME              PROPERTY_ISIHDR_STRUCT_NAME
#define COMMENT_ISIHDR_TITLE                    PROPERTY_ISIHDR_TITLE
#define COMMENT_ISIHDR_VARNAME_16               PROPERTY_ISIHDR_VARNAME_16

#define COMMENT_ISI_VERSION_NO_LONGER_SUPPORTED PROPERTY_VERSION_NO_LONGER_SUPPORTED
#define COMMENT_ISI_VERSION_NOT_YET_SUPPORTED   PROPERTY_VERSION_NOT_YET_SUPPORTED

#define COMMENT_MEDIA_CTRL_SPECIFIC_MSG         PROPERTY_MSG_IS_MEDIA_CTRL_SPECIFIC

#define COMMENT_OWNER_NAME                      PROPERTY_PROJECT_OWNER_NAME

#define COMMENT_PCMS_HTML_PART                  PROPERTY_HTML_PCMS_PART
#define COMMENT_PCMS_HTML_ITEM                  PROPERTY_HTML_PCMS_ITEM
#define COMMENT_PCMS_ISIHDR_PART                PROPERTY_ISIHDR_PCMS_PART
#define COMMENT_PCMS_ISIHDR_ITEM                PROPERTY_ISIHDR_PCMS_ITEM
#define COMMENT_PCMS_ISIHDR_ITEM_16             PROPERTY_ISIHDR_PCMS_ITEM_16
#define COMMENT_PCMS_WORKSET                    PROPERTY_ISIHDR_PCMS_WORKSET

#define COMMENT_PROJECT_NAME                    PROPERTY_PROJECT_NAME

#define COMMENT_SB_LENGTH_RELATES_TO_DATA_PART_ONLY PROPERTY_SB_LENGTH_RELATES_TO_DATA_PART_ONLY

#define COMMENT_SITE_NAME                       PROPERTY_PROJECT_SITE_NAME

#define COMMENT_STATIC_DATA                     PROPERTY_FTD_IS_STATIC_DATA

#define COMMENT_STRUCT_LENGTH_NAME              PROPERTY_ISIHDR_STRUCT_LENGTH_NAME
#define COMMENT_STRUCT_NAME                     PROPERTY_ISIHDR_STRUCT_NAME

#define COMMENT_SUBMSG_NAMES_ARE_UNIQUE         PROPERTY_SUBMSG_NAMES_ARE_UNIQUE

#define COMMENT_SUPPORT_BOOLS_IN_ISIHDR         PROPERTY_ISIHDR_GENERATE_BOOLS
#define COMMENT_SUPPORT_BITFIELDS_IN_ISIHDR     PROPERTY_ISIHDR_GENERATE_BITFIELDS
#define COMMENT_SUPPORT_DYN_STRUCTS_IN_ISIHDR   PROPERTY_ISIHDR_GENERATE_ALL_STRUCTURE_ELEMENTS

#define COMMENT_OBJECT_ID                       PROPERTY_PMD_PHONET_OBJECT_ID
#define COMMENT_DEVICE_ID                       PROPERTY_PMD_PHONET_DEVICE_ID

#define PROPERTY_CONTINUUS_INSTANCE_NAME        PROPERTY_ISIHDR_CONTINUUS_INSTANCE_NAME
#define PROPERTY_CONTINUUS_PROJECT_NAME         PROPERTY_ISIHDR_CONTINUUS_PROJECT_NAME
#define PROPERTY_ITEM_PMD_ANCHOR                PROPERTY_PMD_ANCHOR
#define PROPERTY_PCMS_WORKSET                   PROPERTY_ISIHDR_PCMS_WORKSET

#define PROPERTY_SITE_NAME                      PROPERTY_PROJECT_SITE_NAME
#define PROPERTY_OWNER_NAME                     PROPERTY_PROJECT_OWNER_NAME
#define PROPERTY_CONFIDENTIALITY                PROPERTY_PROJECT_CONFIDENTIALITY

#define PROPERTY_PHONET_OBJECT_ID               PROPERTY_PMD_PHONET_OBJECT_ID
#define PROPERTY_PHONET_DEVICE_ID               PROPERTY_PMD_PHONET_DEVICE_ID
#define PROPERTY_PHONET_HEADER_LAYOUT           PROPERTY_ISIHDR_PHONET_HEADER_LAYOUT


/* ============================================================================================= */
/* Comments */
/* ============================================================================================= */

typedef enum e_autogen_comment_id
{
/*
///<enum name="E_COMMENT_TYPE">
///<summary>This enumeration defines the possible comment types for macro <see cref_macro="COMMENT" />.</summary>
///[enum]
*/
    COMMENT_NONE = 0,                        /* <not_to_be_documented/> */

    COMMENT_TEXT = PROPERTY_TOTAL_COUNT + 1, /* <summary>Inserts the comment text at the insertion point in the ISI header file / HTML document.</summary> */
    COMMENT_NEWLINE,                         /* <summary>Inserts a new-line character as a comment at the insertion point in the ISI header file / HTML document.</summary> */
    COMMENT_PARAGRAPH,                       /* <summary>Inserts the comment text followed by a new-line character at the insertion point in the ISI header file / HTML document.</summary> */
    COMMENT_BULLET,                          /* <summary>Inserts the comment text as a bullet. In ISI header files, the bullet is shown as a dash sign, and in HTML as a dot.</summary> */
    COMMENT_WEB_LINK,                        /* <summary>Inserts a web link. In ISI header file, the link will be displayed as text.</summary> */
    COMMENT_ISIHDR_TOP,                      /* <summary>Places the text before inclusion of isi_conf.h. 8 bit header file only.</summary> */
    COMMENT_ISIHDR_BEFORE_DEF,               /* <summary>Places the text before the definition it relates to. 8 bit header file only.</summary> */
    COMMENT_ISIHDR_AFTER_DEF,                /* <summary>Places the text after the definition it relates to. 8 bit header file only.</summary> */
    COMMENT_ISIHDR_TOP_16,                   /* <summary>Places the text before inclusion of isi_conf.h. 16 bit header file only.</summary> */
    COMMENT_ISIHDR_BEFORE_DEF_16,            /* <summary>Places the text before the definition it relates to. 16 bit header file only.</summary> */
    COMMENT_ISIHDR_AFTER_DEF_16,             /* <summary>Places the text after the definition it relates to. 16 bit header file only.</summary> */
    COMMENT_LINK_TYPE,                       /* <not_to_be_documented/> */
    COMMENT_RAW_DATA,                        /* <not_to_be_documented/> */
    GENERAL_COMMENT,                         /* <not_to_be_documented/> */
/*
///</enum>
*/

/*
///<enum name="E_COMMENT_PROPERTY_TYPE">
///<summary>This enumeration defines various properties to be used with comments. To set the properties below, use the macro <see cref_macro="COMMENT_PROPERTY" />.
///</summary>
///[enum]
*/
    COMMENT_PROPERTY_HTML_ONLY,              /* <summary>The following comments are written to html output only.</summary> */
    COMMENT_PROPERTY_HTML_DISABLE,           /* <summary>The following comments are not written to html output.</summary> */
    COMMENT_PROPERTY_ISIHDR_ONLY,            /* <summary>The following comments are written to isihdr output only.</summary> */
    COMMENT_PROPERTY_ISIHDR_DISABLE,         /* <summary>The following comments are not written to isihdr output.</summary> */
    COMMENT_PROPERTY_ALL_OUTPUTS             /* <summary>The following comments are written to all outputs.</summary> */
/*
///</enum>
*/
} autogen_comment_id;

/* obsolete comments */
#define COMMENT_FIRST                           COMMENT_TEXT
#define COMMENT_LAST                            GENERAL_COMMENT

#define COMMENT_PROPERTY_FIRST                  COMMENT_PROPERTY_HTML_ONLY
#define COMMENT_PROPERTY_LAST                   COMMENT_PROPERTY_ALL_OUTPUTS

/* backward compatible text comment types */
#define FIELD_COMMENT                           COMMENT_TEXT
#define AUTOGEN_COMMENT_FIELD                   COMMENT_TEXT

/* text comment properties - backward compatibility definitions */
#define COMMENT_HTML_ONLY                       COMMENT_PROPERTY_HTML_ONLY
#define COMMENT_HTML_DISABLE                    COMMENT_PROPERTY_HTML_DISABLE
#define COMMENT_ISIHDR_ONLY                     COMMENT_PROPERTY_ISIHDR_ONLY
#define COMMENT_ISIHDR_DISABLE                  COMMENT_PROPERTY_ISIHDR_DISABLE
#define COMMENT_ALL_OUTPUTS                     COMMENT_PROPERTY_ALL_OUTPUTS


/* ============================================================================================= */
/* Miscellanous constants */
/* ============================================================================================= */

/* ISI header generation flag */
typedef enum e_isihdr_marker_type
{
/*
///<enum name="E_ISIHDR_GENERATION_TYPE">
///<summary>This enumeration defines the possible ISI header generation types.</summary>
///[enum]
*/
    ISIHDR_DONT_GENERATE = 0,           /* <summary>Nothing is generated for the item</summary> */
    ISIHDR_MARKER_ANYSIZE,              /* <summary>Generates <b>type varname[XXX_ANY_SIZE]</b></summary> */
    ISIHDR_MARKER_ANYSIZE_BYTE,         /* <summary>Generates <b>uint8 varname[XXX_ANY_SIZE]</b></summary> */
    ISIHDR_MARKER_ANYSIZE_WORD,         /* <summary>Generates <b>uint16 varname[XXX_ANY_SIZE]</b></summary> */
    ISIHDR_MARKER_SINGLE_ELEMENT,       /* <summary>Generates <b>type varname</b></summary> */
    ISIHDR_MARKER_SINGLE_ELEMENT_BYTE,  /* <summary>Generates <b>uint8 varname</b></summary> */
    ISIHDR_RESERVE_SPACE,               /* <summary>Generates <b>type varname[XXX]</b>, XXX being maximum possible, defined with <see cref_property="PROPERTY_ITEM_MAXIMUM_VALUE"/> (reference), <see cref_property="PROPERTY_STRING_MAXIMUM_LENGTH"/> (string) or <see cref_property="PROPERTY_ARRAY_MAXIMUM_SIZE"/> (infinite array).</summary> */
    ISIHDR_POINTER_VOID,                /* <summary>Generates <b>void* varname</b></summary> */
    ISIHDR_POINTER,                     /* <summary>Generates <b>type* varname</b></summary> */
    ISIHDR_MARKER_UNION,                /* <summary>Generates a union</summary> */
    ISIHDR_MARKER_NONE                  /* <not_to_be_documented/> */
/*
///</enum>
*/
} isihdr_marker_type;

#define ISIHDR_MARKER_POINTER           ISIHDR_POINTER

typedef enum e_autogen_agg_type
{
    AGG_TYPE_UNKNOWN,
    AGG_TYPE_FIXED_SINGLE,
    AGG_TYPE_FIXED_MULTIPLE,
    AGG_TYPE_DYNAMIC_REF,
    AGG_TYPE_DYNAMIC_ASMANYASPOSSIBLE,
    AGG_TYPE_DYNAMIC_ZEROTERMINATED,
    AGG_TYPE_DYNAMIC_ALIGNMENT,
    AGG_TYPE_DYNAMIC_OPTIONAL,
    AGG_TYPE_DYNAMIC_UNKNOWN_LENGTH
} autogen_agg_type;


/* ============================================================================================= */
/* Includes */
/* ============================================================================================= */

#include "autogen_object.h"
#include "pmdconstants.h"

#include <stdio.h>


/* ============================================================================================= */
/* Global definitions */
/* ============================================================================================= */

/* pointer to the list of resources in the data mode */
extern autogen_obj_list* g_res_list;

/* pointer to trace group lists */
#define AUTOGEN_OBJ_TRACEGRP_NONE               0
#define AUTOGEN_OBJ_TRACEGRP_MCU                1
#define AUTOGEN_OBJ_TRACEGRP_SYMBIAN            2
#define AUTOGEN_OBJ_TRACEGRP_INVARIANT          3
#define AUTOGEN_OBJ_TRACEGRP_OS                 4
#define AUTOGEN_OBJ_TRACEGRP_HAL                5
#define AUTOGEN_OBJ_TRACEGRP_CDSP5              6
#define AUTOGEN_OBJ_TRACEGRP_ADSP5              7
#define AUTOGEN_OBJ_TRACEGRP_VENDOR             8
#define AUTOGEN_OBJ_TRACEGRP_MASTER             9
#define AUTOGEN_OBJ_TRACEGRP_HSP               10

/* When changing this value, remember to update the static variables s_trcgrp_id and s_trc_id in autogen_init.c */

#define AUTOGEN_OBJ_TRACEGRP_MAX               11

typedef struct t_autogen_trcgrp_conf
{
    unsigned int res_type;
    autogen_obj_list** list;
    unsigned int* map;
    int has_groups;
    const char* trace_entity_id_refname;
    int entity_size;
    unsigned short entity_special_type;
    const char* trace_group_id_refname;
    int group_size;
    unsigned short group_special_type;
    const char* trace_id_refname;
    int id_size;
    unsigned short id_special_type;
    int support_table;
    int length_size;
    int support_short;
    unsigned int max_entities;
    unsigned int n_entities;
    unsigned int trc_res_ids;
    const char* anchor;
    int conflicts;
    unsigned int msg_type;
    unsigned short entry_point_id;
    unsigned int entry_point_info_type_id;
    int pmd_class;
} autogen_trcgrp_conf;

extern autogen_trcgrp_conf g_trcgrp_conf[AUTOGEN_OBJ_TRACEGRP_MAX];


#define AUTOGEN_RESOURCE_TYPES_MAX 32

typedef struct t_autogen_res_conf
{
    unsigned int res_type;
    int res_sel;
    unsigned int ext_res_type;
    unsigned short device_id;
    int is_unique;
    int msg_id_size;
    int msg_id_offset;
    int submsg_id_size;
    int submsg_id_offset;
    int msg_length_size;
    int msg_length_offset;
    unsigned int msg_type;
    unsigned int msg_type_flags;
    const char* anchor;
    const char* xml_name;
} autogen_res_conf;

extern autogen_res_conf g_res_conf[AUTOGEN_RESOURCE_TYPES_MAX];

#define AUTOGEN_DEVICE_CURRENT  0xFFFE
#define AUTOGEN_DEVICE_GENERAL  PMD_DEVICE_GENERAL

/* 60 general symbols
    7 OS related symbols
    1 MCU product related symbol
   - All included in local env.
*/
#define AUTOGEN_SYMBOLS_COUNT_GENERAL      60
#define AUTOGEN_SYMBOLS_COUNT_OS            7
#define AUTOGEN_SYMBOLS_COUNT_MCU_PRODUCT   1
#define AUTOGEN_SYMBOLS_COUNT_ALL         (AUTOGEN_SYMBOLS_COUNT_GENERAL + AUTOGEN_SYMBOLS_COUNT_OS + AUTOGEN_SYMBOLS_COUNT_MCU_PRODUCT)

#ifdef AUTOGEN_ENVIRONMENT_LOCAL
 #define AUTOGEN_SYMBOL_TYPES_MAX AUTOGEN_SYMBOLS_COUNT_ALL
#elif (defined AUTOGEN_INCLUDE_NOS_TRACES && defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU)
 #define AUTOGEN_SYMBOL_TYPES_MAX AUTOGEN_SYMBOLS_COUNT_ALL
#elif (defined AUTOGEN_ENVIRONMENT_PRODUCT_MCU)
 #define AUTOGEN_SYMBOL_TYPES_MAX (AUTOGEN_SYMBOLS_COUNT_GENERAL + AUTOGEN_SYMBOLS_COUNT_MCU_PRODUCT)
#elif (defined AUTOGEN_INCLUDE_NOS_TRACES)
 #define AUTOGEN_SYMBOL_TYPES_MAX (AUTOGEN_SYMBOLS_COUNT_GENERAL + AUTOGEN_SYMBOLS_COUNT_OS)
#else
 #define AUTOGEN_SYMBOL_TYPES_MAX AUTOGEN_SYMBOLS_COUNT_GENERAL
#endif

typedef struct t_autogen_symbol_conf
{
    unsigned int type;          /* Type, defined in isi_macros.h, e.g. OS_TASK_NAME */
    const char* name;           /* name in VALUE_CONST macro, e.g. "OS_TASK_NAME" */
    const char* tblname;        /* symbol table name in autogen_symbols.c */
    int length;                 /* size of constants */
    unsigned short device_id;     /* device ID, where symbol belongs */
    unsigned int pres_flag;     /* presentation type AUTOGEN_PRESENTATION_XXX */
    unsigned int pmd_info_type; /* PMD info type PMD_INFO_TYPE_XXX */
    const pmd_constant* pmd_const_map; /* Map to constaht configuration in pmd_constants.c */
    unsigned int pmd_const_map_size; /* Size of map */
    unsigned int pmd_flag; /* should symbols be included in public/restricted PMD files? */
    const char* xml_type_name; /* presentation type name in XML, eg. "PhonetConstant" */
    const char* xml_const_name; /* presentation constant name in XML, eg. "PhonetResource" */
    int xml_generate; /* should constant table be generated in symbols.xml file? */
} autogen_symbol_conf;

extern autogen_symbol_conf g_symbol_conf[AUTOGEN_SYMBOL_TYPES_MAX];


/* pointer to the list of embedded files */
extern autogen_obj_list* g_emb_file_list;

/* list of PMD environment constants */
extern struct t_autogen_obj g_pmd_environment_variables;

/* is any warnings found during the analysis of the data model? */
extern int g_has_warnings;

/* autogen environment */
extern unsigned int g_autogen_env;

/* pointer to the log file handle */
extern FILE* g_log;

/* generic STI trace definitions */
extern unsigned int g_sti_trace_id;
extern const char*  g_sti_trace_name;


/* ============================================================================================= */
/* General definitions */
/* ============================================================================================= */

#define AUTOGEN_VERSION                 6029
#define AUTOGEN_VERSION_NUMBER          "11w13"
#define AUTOGEN_VERSION_DATE            "25-Mar-2011"

#define AUTOGEN_ENV_NONE                0x00000000U
#define AUTOGEN_ENV_LOCAL               0x00000001U
#define AUTOGEN_ENV_PRODUCT             0x00000002U
#define AUTOGEN_ENV_PRODUCT_DSP        (0x00000004U | AUTOGEN_ENV_PRODUCT)
#define AUTOGEN_ENV_PRODUCT_MCU        (0x00000008U | AUTOGEN_ENV_PRODUCT)
#define AUTOGEN_ENV_PRODUCT_SYMBIAN    (0x00000010U | AUTOGEN_ENV_PRODUCT)
#define AUTOGEN_ENV_PRODUCT_DEVICE     (0x00000020U | AUTOGEN_ENV_PRODUCT)
#define AUTOGEN_ENV_PRODUCT_ADSP       (0x00000040U | AUTOGEN_ENV_PRODUCT)
#define AUTOGEN_ENV_ALL                 0xFFFFFFFFU

#define AUTOGEN_ERROR_INFO              1
#define AUTOGEN_ERROR_WARNING           2
#define AUTOGEN_ERROR_WARNING_INTERNAL  3
#define AUTOGEN_ERROR_FATAL             4
#define AUTOGEN_ERROR_FATAL_INTERNAL    5

#define AUTOGEN_NOT_SUPPORTED           -1
#define AUTOGEN_VALUE_VARIES            -2

#ifndef _MSC_VER
 #define strcmpi strcasecmp
 #define stricmp strcasecmp
#endif

#ifndef __LINE__
 #define __LINE__  0
#endif /* __LINE__ */


#ifndef __NOKIA_FILE__
 #ifndef __FILE__
  #define __NOKIA_FILE__  "<unknown file name>"
 #else
  #define __NOKIA_FILE__ __FILE__
 #endif /* __FILE__ */
#endif /* __NOKIA_FILE__ */


/* ============================================================================================= */
/* Trace structures */
/* ============================================================================================= */


/* MCU trace structure */

#define AUTOGEN_MCU_TRACE_STRUCTURE(dev) \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, dev) \
   BLOCK_REF(BE, trace_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_MCU_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* Invariant traces */

#define AUTOGEN_INVARIANT_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, AUTOGEN_DEVICE_GENERAL) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_INVARIANT_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* HAL traces */

#define AUTOGEN_HAL_TRACE_STRUCTURE(dev) \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, dev) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_HAL_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* NOS trace structure */

#define AUTOGEN_NOS_TRACE_STRUCTURE(dev) \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, dev) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_NOS_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* ADSP trace structure (old SB structure) */

#define AUTOGEN_ADSP5_OLD_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_AUX) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_ADSP5_TRACE_OLD", NULL, 0, REF_LENGTH_UNKNOWN)


/* ADSP trace structure */

#define AUTOGEN_ADSP5_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_AUX) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_ADSP5_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* CDSP trace structure (old SB structure) */

#define AUTOGEN_CDSP5_OLD_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_MAIN) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_CDSP5_TRACE_OLD", NULL, 0, REF_LENGTH_UNKNOWN)


/* CDSP trace structure */

#define AUTOGEN_CDSP5_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_DSP_MAIN) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_CDSP5_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* Symbian traces */

#define AUTOGEN_SYMBIAN_TRACE_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, PN_DEV_SOS) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_SYMBIAN_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)


/* OST structure */

#define AUTOGEN_OST_STRUCTURE() \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, AUTOGEN_DEVICE_GENERAL) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "PROTOCOL_OST", NULL, 0, REF_LENGTH_UNKNOWN)


/* Vendor component trace structure */

#define AUTOGEN_VENDOR_COMPONENT_TRACE_STRUCTURE() \
  PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, AUTOGEN_DEVICE_CURRENT) \
  BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_VENDOR_COMPONENT_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)

/* HRC XTI trace structure */
#define AUTOGEN_HSP_TRACE_STRUCTURE(dev) \
   PROPERTY_VALUE(PROPERTY_PMD_PHONET_DEVICE_ID, dev) \
   BLOCK_REF(BE, trc_data, "Trace data", BLOCK_PROTOCOL, "ENTRY_POINT_HSP_TRACE", NULL, 0, REF_LENGTH_UNKNOWN)



/* ============================================================================================= */
/* Error codes */
/* ============================================================================================= */

#define AUTOGEN_OK                                          0x000000U

#define AUTOGEN_ERROR_INVALID_ARGUMENT                      0x000001U
#define AUTOGEN_ERROR_ITEM_REDEFINITION                     0x000002U
#define AUTOGEN_ERROR_ITEM_VERSION_CONFLICT                 0x000003U
#define AUTOGEN_ERROR_MISSING_OBJ_VERSION                   0x000005U

#endif /* _AUTOGEN_DEF_H_ */

/*  End of file autogen_def.h  */
