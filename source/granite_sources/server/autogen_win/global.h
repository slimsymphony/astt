/*
-------------------------------------------------------------------------
NOKIA MOBILE PHONES
TEC Oulu













                GLOBAL DEFINITIONS
                -------------------
                SW Include Document




Project  : coresw

Name     : global.h

Version  : 179

Type     : incl

Instance : ou_pcms#1

Copyright (c) Nokia Corporation


*/

#ifndef GLOBAL_H
#define GLOBAL_H


/* Global constants */

#ifndef NULL
#if defined(__cplusplus) || defined(GLOBAL_H_NULL_BE_0)
#define NULL                    0
#else
#define NULL                    (void *) 0
#endif
#endif

#ifndef NUL
#define NUL                     '\0'
#endif

#ifdef  YES                             /* defined in some environments */
#undef  YES
#endif

#ifdef  NO                              /* defined in some environments */
#undef  NO
#endif

#define TRUE                    1       /* Boolean TRUE value           */
#define FALSE                   0       /* Boolean FALSE value          */
#define YES                     TRUE
#define NO                      FALSE
#define ON                      TRUE
#define OFF                     FALSE
#define OK                      TRUE
#define FAIL                    FALSE
#define ENABLED                 TRUE
#define DISABLED                FALSE
#define COLD                    0
#define WARM                    1

/* More global constants */

#define G_ERROR                 0
#define G_DISABLE               0
#define G_ENABLE                1
#define G_NEITHER               2
#define G_FOREVER               1
#define G_NO_EVENT              0
#define G_NO_RESPONSE           0
#define FOREVER                 G_FOREVER
#define NO_EVENT                G_NO_EVENT
#define NO_RESPONSE             G_NO_RESPONSE

/* AND, OR , NOT macros (define GLOBAL_H_EXCLUDE_LOGICAL_MACROS if you use
 * f. ex. conversion tool h -> inc) */

#ifndef GLOBAL_H_EXCLUDE_LOGICAL_MACROS

#define AND                     &&      /* logical-AND-expression       */
#define OR                      ||      /* logical-OR-expression        */
#define NOT                     !       /* logical-NEGATION-expression  */

#endif

/* Definition for LOCAL. Define LOCAL with -DLOCAL in compilation of a 
 * module to make local variables to global variables for debugging purposes. 
 * Note that there may become naming conflicts if you do this for several 
 * modules in one build */

#ifndef DSP_USE_HC2INC   /* DSP does not use LOCAL definition */

#ifndef LOCAL
#define LOCAL static
#endif

#endif


/* Projects (values of PROJECT) */
/* NOTE! PROJECT definition SHOULD NOT BE USED for flagging out any         */ 
/*       features, feature flags should be used instead!                    */
/*       PROJECT definition may be used for example to tell the product     */
/*       type to external device (like service tool).                       */
/*       So, please, no conditional compilation using PROJECT definition!   */  

#define G_D31                   1       /* Project is D31                   */
#define G_MOTRA                 2       /* Project is MOTRA                 */
#define G_TANKA                 3       /* Project is TANKA                 */
#define G_D26                   4       /* Project is D26                   */
#define G_OTTO                  5       /* Project is OTTO                  */
#define G_MOTRA_450_NMT         8       /* Project is MOTRA 450 NMT         */
#define G_KP15                  9       /* Project is KP15                  */
#define G_M11                   10      /* Project is M11                   */
#define G_KITE                  11      /* Project is KITE                  */
#define G_M11T                  12      /* Project is M11T                  */
#define G_H300                  13      /* Project is H300                  */
#define G_ELMO                  14      /* Project is ELMO                  */
#define G_CD600                 15      /* Project is CD600                 */
#define G_C300                  16      /* Project is C300                  */
#define G_H300B                 17      /* Project is H300B                 */
#define G_RINGA                 18      /* Project is RINGA                 */
#define G_H300N                 19      /* Project is H300N                 */
#define G_HD720                 20      /* Project is HD720                 */
#define G_HD740                 21      /* Project is HD740                 */
#define G_HD760                 22      /* Project is HD760                 */
#define G_H400C                 23      /* Project is H400C                 */
#define G_DCT                   24      /* Project is DCT                   */
#define G_H300LTC               25      /* Project is H300LTC               */
#define G_HD823                 26      /* Project is HD843                 */
#define G_DCT2                  27      /* Project is DCT2                  */
#define G_HD881                 28      /* Project is CCT                   */
#define G_THF5                  29      /* Project is THF5 (SP project)     */
#define G_H600                  30      /* Project is h600                  */
#define G_HD841                 31      /* Project is HD841                 */
#define G_HD842                 32      /* Project is HD842                 */
#define G_HD843                 33      /* Project is HD843                 */
#define G_HD861                 34      /* Project is HD861                 */
#define G_HD862                 35      /* Project is HD862                 */
#define G_HD863                 36      /* Project is HD863                 */
#define G_HD821                 37      /* Project is HD821                 */
#define G_DAPHNE                38      /* Project is DAPHNE (Responder RU) */
#define G_H700                  39      /* Project is H700                  */
#define G_TESLA                 40      /* Project is TESLA                 */
#define G_HD846                 41      /* Project is HD846                 */
#define G_HD844                 42      /* Project is HD844                 */
#define G_HD845                 43      /* Project is HD845                 */
#define G_HD913                 44      /* Project is HD913                 */
#define G_HD931                 45      /* Project is HD931                 */
#define G_HD933                 46      /* Project is HD933                 */
#define G_HD941                 47      /* Project is HD941                 */
#define G_HD943                 48      /* Project is HD943                 */
#define G_HD953                 49      /* Project is HD953                 */
#define G_HD961                 50      /* Project is HD961                 */
#define G_HD963                 51      /* Project is HD963                 */
#define G_HD965                 52      /* Project is HD965                 */
#define G_POWDER                53      /* Project is POWDER                */
#define G_SPOCK                 54      /* Project is SPOCK                 */
#define G_HD945                 55      /* Project is HD945                 */
#define G_LINDA                 56      /* Project is LINDA                 */
#define G_TFE3                  57      /* Project is FIW: TFE3             */
#define G_TFK3                  58      /* Project is FIW: TFK3             */
#define G_TFB3                  59      /* Project is FIW: TFB3             */
#define G_CD900                 60      /* Project is CD900                 */
#define G_HD951                 61      /* Project is HD951                 */
#define G_CD940_PU              62      /* Project is CD940 PU              */
#define G_CD940_HS              63      /* Project is CD940 HS              */
#define G_HD962                 64      /* Project is HD962                 */
#define G_HD972                 65      /* Project is HD972                 */
#define G_HD925                 66      /* Project is HD925                 */
#define G_HD927                 67      /* Project is HD927                 */
#define G_HD928                 68      /* Project is HD928                 */
#define G_HD947                 69      /* Project is HD947                 */
#define G_HD914                 70      /* Project is HD914                 */
#define G_HD946                 71      /* Project is HD946                 */
#define G_HD955                 72      /* Project is HD955                 */
#define G_DRAGON                73      /* Project is DRAGON                */
#define G_HD976                 74      /* Project is HD976                 */
#define G_HD956                 75      /* Project is HD956                 */
#define G_HDA13                 76      /* Project is HDA13                 */
#define G_HDA15                 77      /* Project is HDA15                 */
#define G_HD9A3                 78      /* Project is HD9A3                 */
#define G_HDA12                 79      /* Project is HDA12                 */
#define G_HDA23                 80      /* Project is HDA23                 */
#define G_HDA25                 81      /* Project is HDA25                 */
#define G_HDAB3                 82      /* Project is HDAB3                 */
#define G_HDA73                 83      /* Project is HDA73                 */
#define G_HDAD5                 84      /* Project is HDAD5                 */
#define G_HDA76                 85      /* Project is HDA76                 */
#define G_HD986                 86      /* Project is HD986                 */
#define G_HD916                 87      /* Project is HD916                 */
#define G_HARALD                88      /* Project is HARALD                */
#define G_HDA52                 89      /* Project is HDA52 (Bandit)        */
#define G_HDA56                 90      /* Project is HDA56 (Pluto)         */
#define G_HDA16                 91      /* Project is HDA16                 */
#define G_HDAC3                 92      /* Project is Amadeus               */
#define G_HDAC5                 93      /* Project is HDAC5                 */
#define G_HDADB                 94      /* Project is HDADB                 */
#define G_HDB13                 95      /* Project is HDB13                 */
#define G_HDB25                 96      /* Project is HDB25                 */
#define G_SIMBA                 97      /* Project is SIMBA                 */
#define G_HD981                 98      /* Project is HD981                 */
#define G_HD982                 99      /* Project is HD982                 */
#define G_HD983                100      /* Project is HD983                 */
#define G_HD984                101      /* Project is HD984                 */
#define G_HD991                102      /* Project is HD991                 */
#define G_HDA62                103      /* Project is HDA62                 */
#define G_HDA87                104      /* Project is HDA87                 */
#define G_HDAG7                105      /* Project is HDAG7                 */
#define G_HDBC2                106      /* Project is Enigma                */
#define G_HDA14                107      /* Project is Lilly                 */
#define G_HDA27                108      /* Project is HDA27                 */
#define G_HDA72                109      /* Project is HDA72                 */
#define G_HDA74                110      /* Project is HDA74                 */
#define G_HDAA3                111      /* Project is Columbia              */
#define G_HDAF3                112      /* Project is Kenny                 */
#define G_HDAF5                113      /* Project is HDAF5                 */
#define G_HDAH3                114      /* Project is Wolfgang              */
#define G_HDB12                115      /* Project is Pippi                 */
#define G_HDB16                116      /* Project is Vanessa               */
#define G_HDD16                117      /* Project is HDD16                 */
#define G_HDB15                118      /* Project is Calypso               */
#define G_ADI110               119      /* Project is ADI110 (Ramses)       */
#define G_ADI120               120      /* Project is ADI120 (Amun)         */
#define G_ADI130               121      /* Project is ADI130 (Isis)         */
#define G_HD942                122      /* Project is HD942                 */
#define G_HDW_1                123      /* Project is HDW_1 (Headset)       */
#define G_HFW_1                124      /* Project is HFW_1 (Handsfree)     */
#define G_HDD14                125      /* Project is Soul                  */
#define G_HDD18                126      /* Project is Funky                 */
#define G_HDB56                127      /* Project is Milou                 */
#define G_THELMA               128      /* Project is Thelma                */
#define G_THELMA380            129      /* Project is Thelma380             */
#define G_THELMA800            130      /* Project is Thelma800             */
#define G_MAVERICK             131      /* Project is Maverick              */
#define G_HDE13                132      /* Project is Triton                */
#define G_HDA53                133      /* Project is Hugo                  */
#define G_US_LINDA             134      /* Project is US LINDA              */
#define G_CAMERON              135      /* Project is Cameron               */
#define G_HDB18                136      /* Project is Hermes                */
#define G_HDB14                137      /* Project is Wagner                */
#define G_HDC18                138      /* Project is Mercurius             */
#define G_HDB76                139      /* Project is Giovanni              */
#define G_HDAA2                140      /* Project is Charles               */
#define G_HDG13                141      /* Project is Maxwell               */
#define G_HDD12                142      /* Project is Dragonfly             */
#define G_HDE16                143      /* Project is Jade                  */
#define G_HDH13                144      /* Project is Libai                 */
#define G_HDBF3                145      /* Project is Cartman               */
#define G_HDAD6                146      /* Project is Kirin                 */
#define G_HITCHHIKER           147      /* Project is Hitchhiker            */
#define G_DTE1                 148      /* Project is Griffin               */
#define G_DTE3                 149      /* Project is Taru                  */
#define G_HOLLYWOOD            150      /* Project is Hollywood             */
#define G_HDE18                151      /* Project is Foxy                  */
#define G_HDF16                152      /* Project is James                 */
#define G_TME3                 153      /* Project is TME3                  */
#define G_HDW2                 154      /* Project is BT Headset            */
#define G_HDB58                155      /* Project is Iris                  */
#define G_CALIMERO             156      /* Project is Calimero              */
#define G_HDF13                157      /* Project is Krypton               */
#define G_HDC13                158      /* Project is Clark                 */
#define G_HDE12                159      /* Project is Matrix                */
#define G_POPEYE               160      /* Project is Popeye                */
#define G_MATISSE              161      /* Project is Matisse               */
#define G_TME4                 162      /* Project is Albert                */
#define G_HDI13                163      /* Project is Jesse                 */
#define G_HDAH0                164      /* Project is HDAH0                 */
#define G_HDA1B                165      /* Project is Ninja                 */
#define G_SU_1B                166      /* Project is SU 1B                 */
#define G_SU_2                 167      /* Project is SU 2                  */ 
#define G_HDDC2                168      /* Project is Cobra                 */
#define G_HDA58                169      /* Project is Debra                 */
#define G_HDBA2                170      /* Project is Eagle                 */
#define G_HDCC2                171      /* Project is Excelsior             */
#define G_HDJ13                172      /* Project is Jacqueline            */
#define G_HDAF6                173      /* Project is Mango                 */
#define G_HDG12                174      /* Project is Maxine                */
#define G_HDBC3                175      /* Project is Salieri               */
#define G_HDG16                176      /* Project is Sirius                */
#define G_HDH12                177      /* Project is Rio                   */
#define G_STARSHIP             178      /* Project is Starship              */
#define G_CK_1W                179      /* Project is CK-1W                 */
#define G_CK_2W                180      /* Project is CK-2W                 */
#define G_HS_3W                181      /* Project is HS-3W                 */
#define G_HDA11                182      /* Project is Penny                 */
#define G_HDA51                183      /* Project is Nikel                 */
#define G_MORPHEUS             184      /* Project is Morpheus (HDe12 platf)*/
#define G_NEO                  185      /* Project is Neo      (HDe12 platf)*/
#define G_HDF18                186      /* Project is Neptun                */
#define G_HDF16i               187      /* Project is James Global          */
#define G_CALISTA              188      /* Project is Calista               */
#define G_HDB63                189      /* Project is Hobbes                */
#define G_NEO_US               190      /* Project is Neo US version        */
#define G_HDJ12                191      /* Project is Asterix               */
#define G_HDG52                192      /* Project is MaxUs                 */
#define G_AQUARIUS             193      /* Project is Aquarius              */
#define G_HDJ12_T              194      /* Project is Troubadix             */
#define G_HDJ12_O              195      /* Project is Obelix                */
#define G_Q                    196      /* Project is Q                     */
#define G_JINX                 197      /* Project is Jinx                  */
#define G_CATALINA             198      /* Project is Catalina              */
#define G_CATALINA_US          199      /* Project is Catalina US version   */
#define G_HDH52                200      /* Project is Rio US version        */
#define G_ERIN                 201      /* Project is Erin                  */
#define G_CALVIN               202      /* Project is Calvin                */
#define G_MX                   203      /* Project is MX                    */
#define G_HDK12                204      /* Project is Hudson                */
#define G_PT5                  205      /* Project is Universal Digital Camera, 3 MP */
#define G_MINI                 206      /* Project is Mini                  */
#define G_HDI12                207      /* Project is Dufu                  */
#define G_HDF17                208      /* Project is Yoda                  */
#define G_HDC58                209      /* Project is Gigbag                */
#define G_STARLIGHT            210      /* Project is Starlight             */
#define G_LIGHTNING            211      /* Project is Lightning             */
#define G_LIGHTNING_US         212      /* Project is Lightning             */
#define G_CAPELLA              213      /* Project is Capella               */
#define G_REMIX                214      /* Project is Remix                 */
#define G_ANTARES              215      /* Project is Antares               */
#define G_CUMULUS              216      /* Project is Cumulus               */
#define G_RANSI                217      /* Project is Ransi                 */
#define G_CASTOR               218      /* Project is Castor                */
#define G_ZEUS                 219      /* Project is Zeus                  */
#define G_MARS                 220      /* Project is Mars                  */
#define G_SU_8W                221      /* Project is SU-8W                 */
#define G_CAPELLA_US           222      /* Project is Capella US            */
#define G_CASTOR_US            223      /* Project is Castor US             */
#define G_MATRIX2              224      /* Project is Matrix 2              */
#define G_MILAN                225      /* Project is Milan                 */
#define G_MUNICH               226      /* Project is Munich                */
#define G_ALEX                 227      /* Project is Alex                  */
#define G_AXIS                 228      /* Project is Axis                  */
#define G_AUSTIN               229      /* Project is Austin                */
#define G_MOJO                 230      /* Project is Mojo                  */
#define G_HELIOS               231      /* Project is Helios                */
#define G_HDJ12_P              232      /* Project is Photonix              */
#define G_HDJ12_I              233      /* Project is Idefix                */
#define G_CHARLIE              234      /* Project is Charlie               */
#define G_SMAILER              235      /* Project is Smailer               */
#define G_YANGTZE              236      /* Project is Yangtze               */
#define G_YANGTZE_US           237      /* Project is Yangtze US            */
#define G_STARSKY              238      /* Project is Starsky               */
#define G_STARSKY_US           239      /* Project is Starsky US            */
#define G_HUTCH                240      /* Project is Hutch                 */
#define G_HUTCH_US             241      /* Project is Hutch US              */
#define G_KOWLOON              242      /* Project is Kowloon               */
#define G_DARLA                243      /* Project is Darla                 */
#define G_MINIME               244      /* Project is Minime                */
#define G_JONNA                245      /* Project is Jonna                 */
#define G_ZEUS_3G              246      /* Project is Zeus 3G               */
#define G_ZEUS_US              247      /* Project is Zeus US               */
#define G_PARIS                248      /* Project is Paris                 */
#define G_HDJ12_S              249      /* Project is Sofix                 */
#define G_SOHO                 250      /* Project is P2465 Soho            */
#define G_MOJITO               251      /* Project is P2730 Mojito          */
#define G_COSMO                252      /* Project is P2912 Cosmo           */
#define G_FULOON               253      /* Project is Fuloon EU             */
#define G_FULOON_US            254      /* Project is Fuloon US             */
#define G_HDJ12_BL             255      /* Project is Bluefix               */
#define G_PANDA                 1       /* Project is Panda                 */
#define G_SHAOLONG              2       /* Project is Shaolong              */
#define G_HDJ12_M               3       /* Project is Majestix              */
#define G_QUEEN                 4       /* Project is Queen                 */
#define G_SIPERIA               5       /* Project is Siperia               */
#define G_SARA                  6       /* Project is Sara                  */
#define G_MAXI                  7       /* Project is Maxi                  */
#define G_POSTMAN               8       /* Project is Postman               */
#define G_COSMOLITE             9       /* Project is P2907 CosmoLite       */
#define G_PICCOLO               10      /* Project is P2908 Piccolo         */
#define G_BIJOU                 11      /* Project is P2911 Bijou           */
#define G_GABBANA               12      /* Project is Gabbana               */
#define G_BOBCAT                13      /* Project is Bobcat                */
#define G_XPRESS                14      /* Project is P2928                 */
#define G_AFRODITE              15      /* Project is P3047                 */
#define G_SLENDER               16      /* Project is P3129                 */
#define G_MACAU                 17      /* Project is P3116                 */
#define G_MACAU_US              18      /* Project is Macau US              */
#define G_SKIPPER               19      /* Project is P3262 Skipper */
#define G_RICO                  20      /* Project is P3263 Rico */
#define G_TIGER                 21      /* Project is Tiger */
#define G_PANTHER               22      /* Project is Panther */
#define G_BARRACUDA             23      /* Project is Barrucuda */
#define G_MUMBAI                24      /* Project is Mumbai */
#define G_SHANGHAI              25      /* Project is Shanghai */
#define G_JAGGER                26      /* Project is Jagger */
#define G_PICCOLINO             27      /* Project is Piccolino */
#define G_SIIRI                 28      /* Project is Siiri */
#define G_VIIVI                 29      /* Project is P2677 */
#define G_DAWN                  30      /* Project is P3385 */
#define G_LEEVI                 31      /* Project is P3386 */
#define G_VICTORIA              32      /* Project is P3387 */

/* NOTE! PROJECT definition SHOULD NOT BE USED for flagging out any         */ 
/*       features, feature flags should be used instead!                    */
/*       PROJECT definition may be used for example to tell the product     */
/*       type to external device (like service tool).                       */
/*       So, please, no conditional compilation using PROJECT definition!   */  


/* Customers of a project (values of PRODUCT_CUSTOMER).                     */
/* NB: these are not brands. For instance, the brands Nokia, Mobira and     */
/* Technophone all are made for the customer G_NOKIA.                       */

#define G_NOKIA                  1      /* Nokia Marketing.                 */
#define G_HML                    2      /* Hutchison Microtel Ltd = Orange. */
#define G_EPLUS                  3      /* E-Plus (Germany).                */
#define G_PHILIPS                4      /* Philips.                         */
#define G_MERCURY                5      /* Mercury Personal Communications. */
/* add here more customers */


/* Cellular system types (values of PRODUCT_CS_TYPE). */

#define G_NMT_900               1       /* cellular type is NMT 900         */
#define G_NMT_450               2       /* cellular type is NMT 450         */
#define G_TACS                  3       /* cellular type is TACS            */
#define G_AMPS                  4       /* cellular type is AMPS            */
#define G_C_NET                 5       /* cellular type is C-NET (Netz C)  */
#define G_NMT_FRENCH            6       /* cellular type is NMT FRENCH      */
#define G_DUAL_MODE_AMPS        7       /* cellular type is DUAL_MODE_AMPS  */
#define G_GSM                   8       /* cellular type is GSM             */
#define G_PCN                   9       /* cellular type is DCS1800 (PCN)   */
#define G_DCS1800               G_PCN   /* cellular type is DCS1800 (PCN)   */
#define G_JDC                   10      /* cellular type is JDC             */
#define G_CDMA                  11      /* cellular type is CDMA            */
#define G_DCS1900               12      /* cellular type is DCS1900         */
#define G_GSM_DCS1800           13      /* cs type is GSM/DCS1800 dualband  */
#define G_GSM1900_EGSM900       14      /* cs type is GSM1900/EGSM900 dualband*/
#define G_EGSM_DCS1800          15      /* cs type is EGSM/DCS1800 dualband */
#define G_GSM1900               G_DCS1900 /* cs type is GSM1900 (DCS1900)   */
#define G_WCDMA_FDD             16      /* cs type is WCDMA, FDD mode       */
#define G_WCDMA_TDD             17      /* cs type is WCDMA, TDD mode       */
#define G_WCDMA_FDD_TDD         18      /* cs type is WCDMA, FDD and TDD    */
#define G_WCDMA_FDD_EGSM        19      /* cs type is WCDMA, FDD and EGSM   */
#define G_TETRA_800             20      /* cs type is Tetra 800             */
#define G_TETRA_380             21      /* cs type is Tetra 380             */
#define G_TETRA_410             22      /* cs type is Tetra 410             */
#define G_GSM_GSM1800_GSM1900   23      /* cs type is GSM/GSM1800/GSM1900   */
#define G_GSM_DCS1800_DCS1900   G_GSM_GSM1800_GSM1900
#define G_GSM850_GSM1900        24      /* cs type is GSM850/GSM1900        */
#define G_GSM850_GSM1800_GSM1900 25     /* cs type is GSM850/GSM1800/GSM1900*/
#define G_WCDMA1900_GSM850_GSM1900  26  /* cs type is WCDMA1900_...         */
#define G_WCDMA_FDD_EGSM900_GSM1800 27  /* cs type is WCDMA_FDD_...         */
#define G_WCDMA1900_GSM1900     28
#define G_GSM850_GSM_GSM1800_GSM1900 29
#define G_GSM_GSM1800_GSM1900_WCDMA1900 30
#define G_GSM_GSM1800_GSM1900_WCDMA2100 31
#define G_GSM850_GSM1800_GSM1900_WCDMA1900 32
#define G_GSM850_GSM_GSM1800_GSM1900_WCDMA1900 33
#define G_GSM850_GSM_GSM1800_GSM1900_WCDMA2100 34
#define G_GSM850_1800_1900_WCDMA850_1900       35
#define G_GSM850_900_1800_1900_WCDMA850_1900   36
#define G_GSM900_1800_1900_WCDMA1900_2100      37
#define G_GSM850_900_1800_1900_WCDMA1900_2100  38
#define G_GSM850_900_1800_1900_WCDMA850_1900_2100 39
#define G_GSM900_1800_1900_WCDMA850_2100       40
#define G_GSM850_900_1800_1900_WCDMA850_2100   41
#define G_GSM850_900_1800_1900_WCDMA900_2100   42
#define G_GSM850_900_1800_1900_WCDMA850_1700_2100 43
#define G_GSM850_900_1800_1900_WCDMA850_900_2100 44
#define G_GSM850_900_1800_1900_WCDMA850_1700_1900_2100 45
#define G_GSM850_900_1800_1900_WCDMA1700 46

/* Alternative definitions (recommended) for Cellular system type
 * (values of PRODUCT_CS_TYPE_MASK). Please, before taking these new
 * types into use, make sure these mask type selections are supported 
 * by all product programs using your code.
 * Usage:
 *   product.h: #define PRODUCT_CS_TYPE_MASK  (G_EGSM_MASK + G_GSM_1900_MASK)
 *   foo.c:     #if (PRODUCT_CS_TYPE_MASK & G_GSM_1900_MASK)
 */
 
#define G_DAMPS_MASK            0x00000001
#define G_CDMA_MASK             0x00000002
#define G_PDC_MASK              0x00000004
#define G_GSM_MASK              0x00000008
#define G_EGSM_MASK             0x00000010
#define G_GSM_1800_MASK         0x00000020
#define G_GSM_1900_MASK         0x00000040
#define G_WCDMA_FDD_MASK        0x00000080
#define G_WCDMA_TDD_MASK        0x00000100
#define G_AMPS_MASK             0x00000200
#define G_CDMA_800_MASK         0x00000400
#define G_CDMA_1700_MASK        0x00000800
#define G_CDMA_1900_MASK        0x00001000
#define G_TETRA_800_MASK        0x00002000
#define G_TETRA_380_MASK        0x00004000
#define G_TETRA_410_MASK        0x00008000
#define G_GSM_850_MASK          0x00010000
#define G_WCDMA_1900_MASK       0x00020000
#define G_WCDMA_2100_MASK       0x00040000


/* Serial number type masks (values of PRODUCT_SN_TYPE_MASK).
 * Usage:
 *   product.h: #define PRODUCT_SN_TYPE_MASK (G_SN_IMEI_MASK+G_SN_ESN_MASK)
 *   foo.c:     #if (PRODUCT_SN_TYPE_MASK & G_SN_IMEI_MASK)
 */
#define G_SN_IMEI_MASK          0x00000001
#define G_SN_CSN_MASK           0x00000002
#define G_SN_ESN_MASK           0x00000004
#define G_SN_EESN_MASK          0x00000008
  

/* Test environment (values of PRODUCT_TEST_ENV) */

#define G_NORMAL_ENV            1       /* No test system code; production. */
#define G_MOSIM                 2       /* MOSIM test system code           */
#define G_FIELD_TEST            3       /* Field test code; real prototypes.*/
#define G_ANSI_SIMULATOR        4       /* ANSI test system code            */
#define G_ESIM                  5       /* ESIM test system code            */
#define G_MODULE_TEST           6       /* Module test code                 */
#define G_UNIT_TEST             7       /* Unit test code                   */
#define G_MOSAIC                8       /* MOSAIC test code                 */
#define G_CARD_TO_CARD_TEST     9       /* Card to card test code           */


/* Values for the G_SIMULATION_ENVIRONMENT flag for separating platform-dependent code */

#define G_SIMULATION_ENVIRONMENT_NONE     1
#define G_SIMULATION_ENVIRONMENT_LINUX    2
#define G_SIMULATION_ENVIRONMENT_HPUX     3
#define G_SIMULATION_ENVIRONMENT_WINDOWS  4


/* Compiler types (values of PRODUCT_COMPILER_TYPE) */

#define G_VAX_C                 1       /* code is executed in VAX          */
#define G_RTS_NEC7811           2       /* code is executed in NEC 7811     */
#define G_IAR_H8_500            3       /* code is executed in H8 500       */
#define G_I86_C                 4       /* code is executed in Intel 80186  */
#define G_IBM_C                 5       /* compiler is IBM CSET/2 for OS/2  */
#define G_MS_C                  6       /* compiler is Microsoft C for OS/2 */
#define G_IAR_H8_300H           7       /* code is executed in H8 300H      */
#define G_IAR_AH8_300H          8       /* IAR assembler can digest .H's    */
#define G_HPUX_C                9       /* compiler is HP Unix C            */
#define G_BORLAND_C            10       /* compiler is BORLAND C            */
#define G_TI_THUMB_C           11       /* compiler is TI's Thumb C         */
#define G_MS_VISUAL_C          12       /* compiler is Microsoft Visual C   */
#define G_GCC_PE_ARM_C         13       /* compiler is GCC for ARM (WinNT PE) */
#define G_SH7K_GH_C            14       /* compiler is GH's SH-1 C          */
#define G_SH7K_HIT_C           15       /* compiler is Hitachi's SH-1 C     */
#define G_KEIL_8051_C          16       /* compiler is KEIL 8051 C          */
#define G_NORCROFT_ARM_C       17       /* compiler is Norcroft's ARM C     */
#define G_IAR_H8_H8S           18       /* code is executed in H8S          */
#define G_IAR_AH8_H8S          19       /* IAR assembler can digest .H's    */
#define G_SUN_C                20       /* compiler is SUN Unix C           */
#define G_TI_LEAD_C            21       /* compiler is TI's C for LEAD(2)   */
#define G_TI_LEAD3_C           22       /* compiler is TI's C for LEAD3     */
#define G_KEIL_C167CR_C        23       /* compiler is KEIL C16x Infineon's */
#define G_LINUX_C              24       /* compiler is Linux C              */



/* Following definition is for DSP use only */

#ifdef DSP_USE_HC2INC
/* The following applies to using .h to .inc filter hc2inc.awk:
*  Normally #defines are converted to .set's in the autogenerated .inc files
*     #define HUU 1     =>   HUU .set 1
*  but if the definition contains keyword asg then .asg is used instead
*     #define HAA asg 2 =>       .asg HAA, 2
*  The C compiler should not see this extra asg so it is defined empty below.
*  For further information see 'Defined Constants in Assembly Language' in 
*  'Coding Instructions for the Lead3 DSP processor' (lead3cod.doc in PCMS
*  GEMINI_DSP:GEMINI_DSP/DOCUMENTS/INSTRUCTIONS) and hc2inc.awk in 
*  GEMINI_DSP:GEMINI_DSP/TOOLS/SCRIPTS.
*
*  YES, THIS DEFINITION MUST BE EMPTY! DO NOT CHANGE IT!
*/
#define asg
#endif

/* BUILD_TARGET constants */
#define G_BUILD_TARGET_FLASH        1
#define G_BUILD_TARGET_NOSE         2
#define G_BUILD_TARGET_ENO          3
#define G_BUILD_TARGET_ENOSDRAM     4
#define G_BUILD_TARGET_UPDATE_AGENT 5
#define G_BUILD_TARGET_ENO_PROT     6
#define G_BUILD_TARGET_ISA_TTCN     7

/* SW Arch: MS07101830361:  dllimport directive to functions on various IF header files */

#if  ( SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_NONE ) && defined( S40_NG_DYNAMIC_COMPILATION ) /* dynamic part of target dll build */
  #define G_DLL_IMPORT __declspec(dllimport)
#elif defined( WIN32 ) && defined( S40_NG_DYNAMIC_COMPILATION )    /* dynamic part of Win dll build */
  #define G_DLL_IMPORT __declspec(dllimport)
#elif defined( WIN32 ) && (!defined( S40_NG_DYNAMIC_COMPILATION )) /* static part of Win dll build */
  #define G_DLL_IMPORT __declspec(dllexport)
#elif ( SIMULATION_ENVIRONMENT == G_SIMULATION_ENVIRONMENT_LINUX ) /* dynamic and static parts of Linux dll build */
  #define G_DLL_IMPORT __attribute__ ((visibility("default")))
#else                                                              /* static part of target dll build or anything else */
  #define G_DLL_IMPORT
#endif


/* Simulation build */ 
#if ( SIMULATION_ENVIRONMENT != G_SIMULATION_ENVIRONMENT_NONE )

#define UNICODE

#undef PRODUCT_COMPILER_TYPE

#ifdef _MSC_VER
#define PRODUCT_COMPILER_TYPE G_MS_VISUAL_C
#else
#define PRODUCT_COMPILER_TYPE G_LINUX_C
#endif

#ifdef _MSC_VER
/* Redefine MS Visual C++ warnings which are ARM compilation errors */
#pragma warning(error: 4133)
#endif /* _MSC_VER */


#endif /* !G_SIMULATION_ENVIRONMENT_NONE */

#endif /* GLOBAL_H */
