#ifndef _ESPRHOT3000_H
#define _ESPRHOT3000_H

#ifdef _WIN32
#pragma warning (disable: 4786) //to disable annoying "identifier was truncated to '255' characters in the debug information" in VC++
#endif

#define fTOL               0.01  // tolerance (1 cm)
#define fDIM_TOL           0.3   // dimension tolerance (~ 1 foot)
#define fWATER_DRAW_TOL    0.001 // total water draw tolerance (fractions must add to ~1.0)

#define BC                 0
#define PRARIES            1
#define ONTARIO            2
#define QUEBEC             3
#define MARITIMES          4
#define NORTH_OF_60        5
#define NWT                6
#define YUKON              7
#define OTHER_REGION       14

#define NUM_REGIONS        8

#define NUM_SETTINGS       3
#define URBAN              1
#define SUBURBAN           2
#define RURAL              3
 
#define MWALLS             100             // max number of walls

#define BC_REGION          0

#define ALTA_REGION        0
#define SASK_REGION        1
#define MAN_REGION         2

#define ONT_REGION         0

#define QUE_REGION         0

#define NB_REGION          0
#define PEI_REGION         1
#define NS_REGION          2
#define NFLD_REGION        3

#define YUKON_REGION       0

#define NWT_REGION         0

#define NUNAVUT_REGION     0

#define NUM_PROVINCES      16 

#define NUM_PROV           4 

#define NUM_CITIES         123


/* hot3000 */
#define SINGLE_LAYER             BASIC_PERF  
#define LOW_INSULATION           ENTRY_PERF
#define TYPICAL_INSULATION       AVERAGE_PERF
#define HIGH_INSULATION          HIGH_PERF

/* building defaults */
#define UNDEFINED_STOREY        UNDEFINED
#define ONE_STOREY              1
#define ONE_AND_A_HALF_STOREYS  2
#define TWO_STOREYS             3
#define TWO_AND_A_HALF_STOREYS  4
#define THREE_STOREYS           5
#define SPLIT_LEVEL             6

#define STOREY_HEIGHT           2.6

#define MAX_NUM_STORIES             5
#define UNDEFINED_STOREY_TXT        "999"
#define ONE_STOREY_TXT              "1"
#define ONE_AND_A_HALF_STOREYS_TXT  "1.5"
#define TWO_STOREYS_TXT             "2"
#define TWO_AND_A_HALF_STOREYS_TXT  "2.5"
#define THREE_STOREYS_TXT           "3"

/* foundation types */
#define NO_BASEMENT    0
#define BASEMENT       1
#define CRAWLSPACE     2
#define SLAB_ON_GRADE  3
#define WALKOUT        4
#define PIERS          5

// 09-Mar-2011 BAL: added
/* extension types */
#define EXT_GARAGE                100
#define EXT_WINE_CELLAR           101
#define EXT_SUNROOM               102
#define EXT_MUDROOM               103
#define EXT_LIV_AREA_W_THERMOSTAT 104


#define BASEMENT_ZONE   1
#define MAIN_FLOOR_ZONE 2
#define CRAWLSPACE_ZONE 3
#define ATTIC_ZONE      4

/* basement door types */
#define BD_NO_DOOR          0
#define BD_STD_DOOR_OPEN    1
#define BD_STD_DOOR_CLOSED  2
#define BD_STAIRWELL        3
#define BD_USER_SPECIFIED   4

/* crawlspace ventilation */
#define VENTED  1
#define OPEN    2
#define CLOSED  1

/*---- door types -----------*/
// Wood hollow core
// Solid wood
// Steel fibreglass core
// Steel polystyrene core
// Steel polyurethane core
// Fibreglass polystyrene core
// Fibreglass polyurethane core
// User specified

#define DT_NO_DOOR                     0
#define DT_WOOD_HOLLOW_CORE            1
#define DT_SOLID_WOOD                  2
#define STEEL_FIBERGLASS_CORE          3
#define STEEL_POLYSTYRENE_CORE         4
#define STEEL_POLYURETHANE_CORE        5
#define FIBREGLASS_POLYSTYRENE_CORE    6
#define FIBREGLASS_POLYURETHANE_CORE   7
#define DT_USER_SPECIFIED              8

/* window distribution */
#define STANDARD_EVEN_DISTRIBUTION        0    
#define STANDARD_MOSTLY_FRONT_AND_BACK    1
#define LARGE_EVEN_DISTRIBUTION           2
#define LARGE_MOSTLY_FRONT_AND_BACK       3

#define STANDARD_EVEN_DISTRIBUTION_TXT      "standard_even_distribution"
#define STANDARD_MOSTLY_FRONT_AND_BACK_TXT  "standard_mostly_front_and_back"
#define LARGE_EVEN_DISTRIBUTION_TXT         "large_even_distribution"
#define LARGE_MOSTLY_FRONT_AND_BACK_TXT     "large_mostly_front_and_back"
#define NUM_WIND_AREAS                    4

/* window age */

#define ORIGIONAL           0
#define LESS_THEN_TEN_YEARS 1
#define ELEVEN_TO_25_YEARS  2
#define UNKNOWN             3

#define FRAME     0
#define GLAZING   1
#define OTHER     2

#define TYPICAL 0
#define LOTS 1

#define NUM_MATERIALS 3

#define ANGLE_0   0
#define ANGLE_40  1
#define ANGLE_55  2
#define ANGLE_70  3
#define ANGLE_80  4

#define NUM_ANGLES    5

/* 
Hot3000 envelope defaults 
    User specified;  - 1
    Before 1920      - 2
    1920-29          - 3
    1930-39          - 4
    1940-49          - 5
    1950-59          - 6
    1960-69          - 7
    1970-79          - 8
    1980-89          - 9
    1990-99          - 10
    2000             - 11
*/
#define HOT3000_USER_SPECIFIED 1
#define HOT3000_BEFORE_1920    2
#define HOT3000_1920_29        3
#define HOT3000_1930_39        4
#define HOT3000_1940_49        5
#define HOT3000_1950_59        6
#define HOT3000_1960_69        7
#define HOT3000_1970_79        8
#define HOT3000_1980_89        9
#define HOT3000_1990_99        10
#define HOT3000_2000           11


/* envelope defaults */
#define PRE_1945     0
#define D1945_1959   1
#define D1960_1969   2
#define D1970_1979   3
#define D1980_1989   4

#define PRE_1990     5
#define D1990_1999   6
#define POST_1990    7

#define POST_1999    8
#define POST_2000    9

#define NUM_DECADES  10

#define PRE_1945_TXT     "pre_1945"
#define D1945_1959_TXT   "1945_1959"
#define D1960_1969_TXT   "1960_1969"
#define D1970_1979_TXT   "1970_1979"
#define D1980_1989_TXT   "1980_1989"
#define D1990_1999_TXT   "1990_1999"
#define POST_2000_TXT    "post_2000"

#define BASEMENT_TXT       "basement"
#define SLAB_ON_GRADE_TXT  "slab_on_grade"
#define NO_BASEMENT_TXT    "no_basement"
#define CRAWL_TXT          "crawl"
#define WALKOUT_TXT        "walkout"
#define NUM_BASEMENTS_TYPES 5

#define SINGLE_DETACHED_TXT "single"
#define ROW_END_UNIT_TXT    "row_end_unit"
#define ROW_MIDDLE_TXT      "row_middle_unit"
#define MAX_NUM_ATTACHMENTS 3

/*
1  BCIN_1   26 BCEB_2   51 SCB_24   76  BCEB_8  101   BCEB_6   126   BCEB_10
2  BCIN_2   27 BCEB_3   52 SCB_25   77  BCEB_9  102   BWIA_1   127   BCEB_11
3  BCIN_3   28 SCN_1    53 SCB_26   78  BWEN_3  103   BWIA_2   128   BCEA_3
4  BCIN_4   29 SCN_2    54 SCB_29   79  BBIB_3  104   SCA_1    129   BCEA_9
5  BCEN_1   30 SCN_3    55 SCB_30   80  BBIB_4  105   SCA_2    130   BCEA_10
6  BCEN_2   31 SCN_4    56 SCB_33   81  SCB_31  106   SCA_9    131   BCEA_11
7  BCEN_3   32 SCN_7    57 SCB_34   82  SCB_32  107   SCA_10   132   BWIB_1
8  BCEN_4   33 SCN_8    58 SCB_35   83  SCB_37  108   BBIN_1   133   BWIB_2
9  BCNN_1   34 SCB_1    59 SCB_36   84  SCB_38  109   BCEN_5   134   BWIB_4
10 BCNN_2   35 SCB_2    60 SCA_17   85  SCB_39  110   BCEN_6   135   BWIA_3
11 BCCN_1   36 SCB_3    61 SCA_18   86  SCB_40  111   BBIA_1   136   BWEB_1
12 BCCN_2   37 SCB_4    62 SCA_19   87  BBEB_1  112   BBIB_1   137   BWEB_2
13 BWNN_1   38 SCB_5    63 SCA_20   88  BBEN_1  113   BBIB_2   138   BWEB_3
14 BWIN_1   39 SCB_6    64 SCA_21   89  BBEN_2  114   BCCB_9   139   BWEB_4
15 BWIN_2   40 SCB_9    65 SCA_22   90  BBIA_2  115   BCCB_10  140   BBIB_5
16 BWIN_3   41 SCB_10   66 SCA_23   91  BBIN_2  116   BCCA_1   141   BBIB_6
17 BWEN_1   42 SCB_11   67 SCA_24   92  BCCB_8  117   BCCA_4   142   BBEB_3
18 BWEN_2   43 SCB_12   68 BCCN_3   93  BCCA_7  118   BCIB_7   143   BBEB_4
19 BCIB_1   44 SCB_13   69 BCCB_4   94  BCCA_8  119   BCIB_8   144   BBEB_5
20 BCIB_2   45 SCB_14   70 BCEA_1   95  BCCN_4  120   BBEB_2   145   BBEA_2
21 BCIB_3   46 SCB_17   71 BCEA_4   96  BCCN_5  121   BCIA_3      
22 BCIB_4   47 SCB_18   72 BCIA_1   97  BCEA_5  122   BCIA_5      
23 BCIB_5   48 SCB_21   73 BCIA_4   98  BCEA_6  123   BCIA_6      
24 BCIB_6   49 SCB_22   74 BCEA_7   99  BCEB_4  124   BCIB_9      
25 BCEB_1   50 SCB_23   75 BCEA_8   100 BCEB_5  125   BCIB_10     

  */
#define BCIN_1 1
#define BCIN_2 2
#define BCIN_3 3
#define BCIN_4 4

#define BCEN_1 5
#define BCEN_2 6
#define BCEN_3 7
#define BCEN_4 8
#define BCEN_5 109
#define BCEN_6 110

#define BCNN_1 9
#define BCNN_2 10

#define BCCN_1 11
#define BCCN_2 12
#define BCCN_3 68
#define BCCN_4 95
#define BCCN_5 96

#define BWNN_1 13

#define BWIN_1 14
#define BWIN_2 15
#define BWIN_3 16

#define BWEN_1 17
#define BWEN_2 18
#define BWEN_3 103

#define BCIB_1  19
#define BCIB_2  20
#define BCIB_3  21
#define BCIB_4  22
#define BCIB_5  23
#define BCIB_6  24
#define BCIB_7  118
#define BCIB_8  119
#define BCIB_9  124
#define BCIB_10 125

#define BCEB_1  25
#define BCEB_2  26
#define BCEB_3  27
#define BCEB_4  99
#define BCEB_5  100
#define BCEB_6  101
#define BCEB_8  76
#define BCEB_9  77
#define BCEB_10 126
#define BCEB_11 127

#define SCN_1  28  
#define SCN_2  29  
#define SCN_3  30  
#define SCN_4  31  
#define SCN_7  32  
#define SCN_8  33  

#define SCB_1  34 
#define SCB_2  35 
#define SCB_3  36 
#define SCB_4  37 
#define SCB_5  38 
#define SCB_6  39 
#define SCB_9  40 
#define SCB_10 41 
#define SCB_11 42 
#define SCB_12 43 
#define SCB_13 44 
#define SCB_14 45 
#define SCB_17 46 
#define SCB_18 47 
#define SCB_21 48 
#define SCB_22 49 
#define SCB_23 50
#define SCB_24 51   
#define SCB_25 52   
#define SCB_26 53   
#define SCB_29 54   
#define SCB_30 55 
#define SCB_31 81
#define SCB_32 82
#define SCB_33 56   
#define SCB_34 57
#define SCB_35 58
#define SCB_36 59 
#define SCB_37 83
#define SCB_38 84
#define SCB_39 85
#define SCB_40 86

#define SCA_1  104
#define SCA_2  105
#define SCA_9  106
#define SCA_10 107
#define SCA_17 60   
#define SCA_18 61 
#define SCA_19 62   
#define SCA_20 63 
#define SCA_21 64 
#define SCA_22 65 
#define SCA_23 66   
#define SCA_24 67
   
#define BCCB_4  69
#define BCCB_8  92
#define BCCB_9  114
#define BCCB_10 115

#define BCEA_1 70   
#define BCEA_3 128
#define BCEA_4 71
#define BCEA_5 97
#define BCEA_6 98
#define BCEA_7 74   
#define BCEA_8 75   
#define BCEA_9 129
#define BCEA_10 130
#define BCEA_11 131

#define  BCIA_1 72   
#define  BCIA_3 121
#define  BCIA_4 73 
#define  BCIA_5 122
#define  BCIA_6 123
  
#define  BWIB_1 132
#define  BWIB_2 133
#define  BWIB_4 134

#define  BBEA_2 145

#define  BBEB_1 87
#define  BBEB_2 120
#define  BBEB_3 142
#define  BBEB_4 143
#define  BBEB_5 144

#define  BBEN_1 88
#define  BBEN_2 89

#define  BBIA_1 111
#define  BBIA_2 90

#define  BBIB_1 112
#define  BBIB_2 113
#define  BBIB_3 79
#define  BBIB_4 80
#define  BBIB_5 140
#define  BBIB_6 141

#define  BBIN_1 108
#define  BBIN_2 91

#define  BCCA_1 116
#define  BCCA_4 117
#define  BCCA_7 93
#define  BCCA_8 94

#define  BWEB_1 136
#define  BWEB_2 137
#define  BWEB_3 138
#define  BWEB_4 139

#define  BWIA_1 102
#define  BWIA_2 103
#define  BWIA_3 135

/* system type */

#define   HOT2000_BASEBOARD          1
#define   HOT2000_FURNACE            2
#define   HOT2000_BOILER             3
#define   HOT2000_COMBO_SYSTEMS      4
#define   HOT2000_FUEL_CELL          5

// 10-Apr-2011 BAL: Added for independent heat pumps which are specified 
// as a primary system in the zonal heating tab.
#define   HOT3000_HEAT_PUMP          5

// 10-Apr-2011 BAL: Added primary and backup hvac priority 
#define   PRIMARY                    1
#define   SECONDARY                  2

//#define   HOT2000_WOOD_STOVE         6
//#define   HOT2000_ASHP               7
//#define   HOT2000_GSHP               8
//#define   HOT2000_FORCED_AIR_FURNACE 12

//#define   HOT2000_NO_FC                 0
//#define   HOT2000_FC_SPACE_HEATING      1
//#define   HOT2000_FC_DHW                2
//#define   HOT2000_FC_SPACE_HEATING_DHW  3

/* fuels */

#define   HOT2000_ELECTRIC     1
#define   HOT2000_NATURAL_GAS  2
#define   HOT2000_OIL          3
#define   HOT2000_PROPANE      4
#define   HOT2000_MIXED_WOOD   5
#define   HOT2000_HARWOOD      6
#define   HOT2000_SOFTWOOD     7
#define   HOT2000_WOOD_PELLETS 8

// 29-Aug-2011 BAL: Added
/* fuel energy unit conversions based on HOT2000 conversion factors*/
//
// electricity
#define ELEC_KWHR_TO_GJ (float)(1.0f / 277.778f)

#define ELEC_GJ_TO_KWHR (float)(277.778f)

// natural gas
#define NG_MCF_TO_GJ (float)(1.0f / 0.947817f)
#define NG_CCF_TO_GJ (float)(1.0f / 9.47817f)
#define NG_M3_TO_GJ (float)(1.0f / 26.8392f)

#define NG_GJ_TO_M3 (float)26.8392f  // ( 1 / NG_M3_TO_GJ ) 
#define NG_MCF_TO_M3 (float)28.31686 // ( NG_MCF_TO_GJ * NG_GJ_TO_M3 ) 
#define NG_CCF_TO_M3 (float)2.831686 // ( NG_CCF_TO_GJ * NG_GJ_TO_M3 )

// oil
#define OIL_IMPGAL_TO_GJ (float)(1.0f / 5.70991f)
#define OIL_USGAL_TO_GJ (float)(1.0f / 6.85735f)
#define OIL_LITRE_TO_GJ (float)(1.0f / 25.9578f)

#define IMPGAL_TO_LITRE (float)4.546096f
#define USGAL_TO_LITRE (float)3.785398f
#define OIL_GJ_TO_LITRE (float)25.9578f

// propane
#define PROP_IMPGAL_TO_GJ (float)(1.0f / 8.59254f)
#define PROP_USGAL_TO_GJ (float)(1.0f / 10.3192f)
#define PROP_LITRE_TO_GJ (float)(1.0f / 39.0625f)

#define PROP_GJ_TO_LITRE (float)39.0625f

// wood
#define WOOD_TONNE_TO_GJ (float)(1.0f / 0.0716538f)
#define WOOD_TON_TO_GJ (float)(1.0f / 0.0789846f)
#define WOOD_CORDS_TO_GJ (float)(1.0f / 0.041670f)

#define WOOD_GJ_TO_TONNE (float)0.07165f
#define WOOD_TON_TO_TONNE (float)0.90719f   // (WOOD_TON_TO_GJ * WOOD_GJ_TO_TONNE)
#define WOOD_CORDS_TO_TONNE (float)1.71955f // (WOOD_CORDS_TO_GJ * WOOD_GJ_TO_TONNE)




// 29-Aug-2011 BAL: Added fuel unit indices mapped from fuel cost editor
#define ELEC_KWHR 1

#define NG_MCF 2
#define NG_CCF 3
#define NG_M3 4

#define OIL_LITRE 2
#define OIL_IMPGAL 3
#define OIL_USGAL 4

#define PROP_LITRE 2
#define PROP_IMPGAL 3
#define PROP_USGAL 4

#define WOOD_TONNE 2
#define WOOD_TON 3
#define WOOD_CORDS 4

#define GJ 0 

#define FUEL_CELL_DHW_AND_SPACE_HEATING               0
#define HOT_WATER_TANK_DHW_SPACE_HEATING              1
#define HEATING_FUEL_CELL_CIRC_PUMP_DHW_SPACE_HEATING 2
#define HEATING_COIL_CIRC_PUMP_SPACE_HEATING_ONLY     3
#define HEATING_COIL_CIRC_FAN_SPACE_HEATING_ONLY      4
#define HEATING_COIL_HEATING_ONLY                     5

// 0 N/A, 1 air,2 water,3 ground,4 central air
#define  HOT2000_NA              0
#define  HOT2000_ASHP            1
#define  HOT2000_WSHP            2
#define  HOT2000_GSHP            3
#define  HOT2000_CENTRAL_AIR     4


#define NO_CASUAL_GAINS                0

#define CASUAL_GAIN_OCC_AREA_PERSON    -1
#define CASUAL_GAIN_LIGHTS_FLOOR_AREA  -2
#define CASUAL_GAIN_EQUIP_FLOOR_AREA   -3

#define ADULTS    0
#define CHILDREN  1
#define INFANTS   1

#define ESPR_DAYTYPES  3
#define ESPR_WEEKDAYS  0
#define ESPR_SATURDAY  1
#define ESPR_SUNDAY    2


// Heat/Cool dialog A/C tab
#define   CALCULATED   2

#define   NUM_MECH_VENT 2

#define   EQ_AGE1_5_TXT            "1_5"
#define   EQ_AGE6_10_TXT           "6_10"
#define   EQ_AGE11_15_TXT          "11_15"
#define   EQ_AGE16_20_TXT          "16_20"
#define   EQ_AGEMORE_THEN_21_TXT   "more_then_21"
#define   EQ_AGE_UNKNOWN_TXT       "dont_know"

#define   EQ_AGE1_5           1
#define   EQ_AGE6_10          2
#define   EQ_AGE11_15         3
#define   EQ_AGE16_20         4
#define   EQ_AGEMORE_THEN_21  5
#define   EQ_AGE_UNKNOWN      UNDEFINED

#define   LOCATED_IN_BSMT                 "basement"
#define   LOCATED_IN_WALKOUT_HALF_BSMT    "walkout_half_basement"
#define   LOCATED_IN_MAIN                 "main_floor"

#define   OTHER_HEATED     "other_heated"
#define   OTHER_NOT_HEATED "other_not_heated"


#define DBL_WINDOW         0
#define WINDOW_SINGLE_PANE 1
#define WINDOW_DOUBLE_PANE 2
#define WINDOW_TRIPLE_PANE 3

#define AWNING         0
#define HORIZONTAL_OBS 1
#define VERTICAL_OBS   2

#define BASIC_PERF               0
#define ENTRY_PERF               1
#define AVERAGE_PERF             2
#define HIGH_PERF                3
#define SUPERIOR_PERF            4

#define NUM_WINDOW_TYPES         5

/* window defaults h3kweb*/
/*
#define BASIC_PERFORMANCE        5
#define ENTRY_PERFORMANCE        6
#define AVERAGE_PERFORMANCE      7
#define HIGH_PERFORMANCE         8
#define SUPERIOR_PERFORMANCE     9
*/

/*  DHW tank location */
   /*
   Main Floor = 1
   Basement   = 2
   Attic      = 3
   Crawl Space= 4
   Garage     = 5
   Porch      = 6
   Outside    = 7
   */

#define TL_UNDEFINED   0
#define TL_MAIN_FLOOR  1
#define TL_BASEMENT    2
#define TL_ATTIC       3
#define TL_CRAWL_SPACE 4
#define TL_GARAGE      5
#define TL_PORCH       6
#define TL_OUTSIDE     7

/* solar DHW system types */
#define SYSTEM1 1
#define SYSTEM2 2
#define SYSTEM3 3
#define SYSTEM4 4

#define NATURAL_GAS_CONVENTIONAL_TANK        1
#define NATURAL_GAS_CONVENTIONAL_TANK_PILOT  2
#define NATURAL_GAS_INDUCED_DRAFT_FAN        3
#define NATURAL_GAS_INDUCED_DRAFT_FAN_PILOT  4
#define NATURAL_GAS_DIRECT_VENT_SEALED       5
#define NATURAL_GAS_DIRECT_VENT_SEALED_PILOT 6
#define NATURAL_GAS_CONDENSING               7


#define PRIMARY_DHW_TANK   0
#define SECONDARY_DHW_TANK 1

// 22-Apr-2011 BAL: Added
#define DHW_TANK_NA  1   // not-applicable tank type

//#define MaxFoundations 1
#define UNDEFINED     999


#define BASEMENT_WALLS   0
#define BASEMENT_CEILING 1
#define MAIN_FLOOR       BASEMENT_CEILING
#define MAIN_WALLS       2
#define MAIN_CEILING     3
#define ATTIC_ROOF       4

#define NUM_SURFACES     ATTIC_ROOF

#define UNKNOWN_FLOOR    0
#define BSMT_FLOOR       -1
#define FIRST_FLOOR      1
#define SECOND_FLOOR     2
#define THIRD_FLOOR      3
#define FOUR_FLOOR       4

// roof types (shapes)
#define NO_ROOF           0
#define SINGLE_SLOPE      1
#define ATTIC_GABLE       2
#define GABLE             2
#define ATTIC_HIP         3
#define HIP               3
#define CATHEDRAL         4
#define FLAT              5
#define SCISSOR           6
#define ATTIC             7

#define   ROOF_ANGLE    (float)0.0

#define IS_GABLE_END     true
#define IS_NOT_GABLE_END false

#define  UNKNOWN_TXT "unknown"
/* calender macros */
#define  JAN 1
#define  FEB 2
#define  MAR 3
#define  APR 4
#define  MAY 5
#define  JUN 6
#define  JUL 7
#define  AUG 8
#define  SEP 9
#define  OCT 10
#define  NOV 11
#define  DEC 12

#define  MON 1
#define  TUE 2
#define  WED 3
#define  THU 4
#define  FRI 5
#define  SAT 6
#define  SUN 7


#define EARLY_WINTER 1
#define SPRING       2
#define SUMMER       3
#define FALL         4
#define LATE_WINTER  5


#define NUM_MONTHS 12
#define NUM_DAYS_IN_WEEK 7
#define NUM_WEEKS_IN_YR 52

#define NUM_SIM_PERIODS 5

#define ONE_SET 1
#define TWO_SETS 2
#define THREE_SETS 3
#define FOUR_SETS 4
#define FIVE_SETS 5

//N/A;South;Southeast;East;Northeast;North;Northwest;West;Southwest
// 1,2,3,4,5,6,7,8
#define HOT3000_NA    0
#define HOT3000_SOUTH 1
#define HOT3000_SE    2
#define HOT3000_EAST  3
#define HOT3000_NE    4
#define HOT3000_NORTH 5
#define HOT3000_NW    6
#define HOT3000_WEST  7
#define HOT3000_SW    8
#define NUM_DIRECTIONS 9

#define HOT2000_WEST  7 //23-Oct-09 JTB: was 8
#define HOT2000_NORTH 5 //23-Oct-09 JTB: was 6
#define HOT2000_EAST  3 //23-Oct-09 JTB: was 4
#define HOT2000_SOUTH 1 //23-Oct-09 JTB: was 2
#define HOT2000_NA    0

#define GUI_FRONT 1
#define GUI_LEFT  2
#define GUI_BACK  3
#define GUI_RIGHT 4

#define SHAPE_W         1
#define SHAPE_N         2
#define SHAPE_E         3
#define SHAPE_S         4
#define SHAPE_NW        5
#define SHAPE_NE        6
#define SHAPE_SW        7
#define SHAPE_SE        8

#define SAVE_LEVEL_5 5
#define NO_IMAGE     0

#define DEFAULTS       0
#define USER_SPECIFIED 1
#define OCCUPANT_DRIVEN_PROFILE 2

/* emmisions data */

#define HEATING_CO2 (float)0.0
#define HEATING_NOX (float)0.0
#define HEATING_SOX (float)0.0

#define COOLING_CO2 (float)0.0
#define COOLING_NOX (float)0.0
#define COOLING_SOX (float)0.0

#define LIGHTING_CO2 (float)0.0
#define LIGHTING_NOX (float)0.0
#define LIGHTING_SOX (float)0.0

#define PUMP_CO2 (float)0.0
#define PUMP_NOX (float)0.0
#define PUMP_SOX (float)0.0

#define SMALLPOWER_CO2 (float)0.0
#define SMALLPOWER_NOX (float)0.0
#define SMALLPOWER_SOX (float)0.0

#define DHW_CO2 (float)0.0
#define DHW_NOX (float)0.0
#define DHW_SOX (float)0.0


#define  NO_PLANT             0
#define  REGISTRATION_ONLY    0
#define  BUILDING_ONLY        1
#define  PLANT_ONLY           2 
#define  BUILDING_AND_PLANT   3

/* plant component sensor indices */
#define  DHW_TANK_NODE_SENSOR_IND 1
#define  DHW_TANK_COMP_SENSOR_IND 2


/* plant component actuator indices */
#define  DHW_TANK_COMP_ACTUATOR_IND 2
#define  DHW_TANK_NODE_ACTUATOR_IND 3

#define  DHW_TANK_VARIABLE_ACTUATOR_IND 2

#define  DHW_NUM_DAY_TYPES 3

/* window area */
#define FRONT_FACE   1
#define LEFT_SIDE    2
#define BACK_FACE    3
#define RIGHT_SIDE   4

#define   KITCHEN       1
#define   LIVING_ROOM   2
#define   DINING_ROOM   3
#define   BEDROOM       4
#define   BATHROOM      5
#define   UTILITY_ROOM  6
#define   GARAGE_ATT    7
#define   OTHER_ROOM    8


#define   INTERNAL_UNKNOWN    0
#define   INTERNAL_KNOWN      1
#define   BOUNDARY_UNKNOWN    2
#define   BOUNDARY_WIND_IND   3

#define   HEATING     1
#define   COOLING     2
#define   HEAT_COOL   3

#define   TYPICAL_HEATING     1
#define   GOOD        2
#define   POOR        3

#define   AIR_SOURCE    7

#define   NO_FAN        0
#define   AUTO_FAN      1
#define   CONTINOUS_FAN 2

//                   ? undefined               "x"
//                   1 blower door test        ?
//                   2 quick blower door test  ?
//                   3 loose                   "A"
//                   4 average                 "B"
//                   5 present                 "C"
//                   6 energy tight            "D"
#define UNDEFINED_BLOWER_DOOR_TEST 'x'
#define ESPR_BLOWER_DOOR_TEST    1
#define QUICK                    2
#define LOOSE                    3
#define AVERAGE                  4
#define PRESENT                  5
#define ENERGY_TIGHT             6

/* sensor types */
#define IDEAL_SENSOR                   0
#define PLANT_SENSOR                   1
#define FLOW_SENSOR                    2
#define GLOBAL_CNTL_RETURN_SENSOR      3
#define POWER_SYS_CNTL_RETURN_SENSOR   4

/* Thermostat types */
#define NO_THERMOSTAT      0
#define THERMOSTAT         1
#define SLAVE_ZONE         2

/* operations data  */
#define CONSTANT_TEMP      0

#define CURRENT_ZONE_TEMP      0
#define MIX_ZONE_AIR_MRT_TEMP -2
/*
basements are always zone 2 ( 1 in C++ )
*/
#define NO_ZONE            0
#define UNDEFINED_ZONE     UNDEFINED

#define MAIN_ZONE_NUM      1
#define BSMT_ZONE_NUM      2
#define ATTIC_ZONE_NUM     3
#define GARAGE_ZONE_NUM    4
#define NUM_ZONES          GARAGE_ZONE_NUM

#define MAIN_ZONE_IND      MAIN_ZONE_NUM-1
#define BSMT_ZONE_IND      BSMT_ZONE_NUM-1
#define MAIN_ZONE_IND      MAIN_ZONE_NUM-1
#define ATTIC_ZONE_IND     ATTIC_ZONE_NUM-1
#define GARAGE_ZONE_IND    GARAGE_ZONE_NUM-1

#define BSMT_ZONE_NAME     "basement"
#define BSMT_SLAB_NAME     "basement_slab"
#define MAIN_ZONE_NAME     "main"
#define ATTIC_ZONE_NAME    "attic"
#define GARAGE_ZONE_NAME   "garage"

#define NO_ZONE_MODEL         0
#define ONE_ZONE_MODEL        1
#define TWO_ZONE_MODEL        2
#define THREE_ZONE_MODEL      3
#define FOUR_ZONE_MODEL       4

#define FIRST_ZONE      0
#define SECOND_ZONE     1
#define THIRD_ZONE      2
#define FOURTH_ZONE     3
#define FIFTH_ZONE      4
#define SIXTH_ZONE      5
#define SEVENTH_ZONE    6


#define XY_PLANE        1
#define YZ_PLANE        2
#define XZ_PLANE        3
#define XY_X_ROOF_PLANE 4
#define XY_Y_ROOF_PLANE 5

// zonal hvac states
#define CENTRAL_HVAC       0
#define INDEPENDANT_HVAC   1
#define NO_HVAC            2

/*
 ICT     - connection type where:
           0 ; connection to external conditions
           1 ; connection to identical environmental conditions
               as the source zone (OR, relative temp and absolute 
               radiation can be specified, see below)
           2 ; connection to constant and known environmental conditions
           3 ; connection to another zone (as defined by IC2 & IE2 
           4 ; connected to ground
           5 ; surface is adiabatic
           6 ; basimp

*/
/*
               NBCTT 0 ; total radiation sensed,
               NBCTT 1 ; ambient temperature sensed,
               NBCTT 2 ; internal air temperature sensed,
               NBCTT 3 ; daylight coeff. sensor lux maintainance
                         by linear optical property variation,
*/

#define NOT_INSULATED   10
#define INSULATED       1

#define DIFFUSE                     3

#define TOTAL_RADIATION_SENSOR      0
#define AMBIENT_TEMPERATURE_SENSOR  1
#define INTERNAL_AIR_SENSOR         2
#define DAYLIGHT_SENSOR             3

#define OPAQUE_ESPR        0
#define TRANSPARENT        1

#define OPAQ  "OPAQ"
#define TRANS "TRANS"
#define TRAN  "TRAN"

#define NO_ASSOCIATED_SURFACE 0
#define UNKNOWN_SURF_NUM      UNDEFINED

#define SURFACE_1_IND      0
#define SURFACE_2_IND      1
#define SURFACE_3_IND      2
#define SURFACE_4_IND      3
#define SURFACE_5_IND      4
#define SURFACE_6_IND      5

#define NO_SURFACE         0
#define SURFACE_1          1
#define SURFACE_2          2
#define SURFACE_3          3
#define SURFACE_4          4
#define SURFACE_5          5
#define SURFACE_6          6

#define WINDOW_1_IND          0
#define WINDOW_2_IND          1
#define WINDOW_3_IND          2
#define WINDOW_4_IND          3

#define DOOR_1          0
#define DOOR_2          1
#define DOOR_3          2
#define DOOR_4          3


#define  ASPHALT  "asphalt"
#define  CLADDING "cladding"

#define FLATROOF           "FlatRoof"

#define FLOOR              "Floor"
#define RIGHT_SLOPE        "RightSlope"  //"WestSlope"
#define FRONT_SLOPE        "FrontSlope"  //"NorthSlope"
#define LEFT_SLOPE         "LeftSlope"   //"EastSlope"
#define BACK_SLOPE         "BackSlope"   //"SouthSlope"

#define RIGHT1_SLOPE       "Right1Slope" //"West1Slope"
#define FRONT1_SLOPE       "Front1Slope" //"North1Slope"
#define LEFT1_SLOPE        "Left1Slope"  //"East1Slope"
#define BACK1_SLOPE        "Back1Slope"  //"South1Slope"

#define RIGHT2_SLOPE       "Right2Slope" //"West2Slope"
#define FRONT2_SLOPE       "Front2Slope" //"North2Slope"
#define LEFT2_SLOPE        "Left2Slope"  //"East2Slope"
#define BACK2_SLOPE        "Back2Slope"  //"South2Slope"


#define FRONT_GABLE        "FrontGable"  //"NorthGable"
#define LEFT_GABLE         "LeftGable"   //"EastGable"
#define BACK_GABLE         "BackGable"   //"SouthGable"
#define RIGHT_GABLE        "RightGable"  //"WestGable"

#define FRONT_HIP          "FrontHip"    //"NorthHip"
#define LEFT_HIP           "LeftHip"     //"EastHip"
#define BACK_HIP           "BackHip"     //"SouthHip"
#define RIGHT_HIP          "RightHip"    //"WestHip"

#define SECOND_WEST_SLOPE  "SecondRightSlope" //"SecondWestSlope"
#define FIRST_SOUTH_SLOPE  "FirstBackSlope"   //"FirstSouthSlope"

#define SOFFIT_1           0
#define SOFFIT_2           1
#define SOFFIT_3           2
#define SOFFIT_4           3
#define SOFFIT_5           4
#define SOFFIT_6           5
#define SOFFIT_7           6
#define SOFFIT_8           7
#define SOFFIT_9           8
#define SOFFIT_10          9
#define SOFFIT_11          10

#define SOFFIT             "Soffit"
#define WEST_SOFFIT        "RightSoffit" 
#define NORTH_SOFFIT       "FrontSoffit"
#define EAST_SOFFIT        "LeftSoffit"
#define SOUTH_SOFFIT       "BackSoffit"

#define EAST1_SOFFIT       "Left1Soffit"
#define EAST2_SOFFIT       "Left2Soffit"
#define SOUTH1_SOFFIT      "Back1Soffit"
#define SOUTH2_SOFFIT      "Back2Soffit"
#define WEST1_SOFFIT       "Right1Soffit" 
#define WEST2_SOFFIT       "Right2Soffit" 
#define NORTH1_SOFFIT      "Front1Soffit"
#define NORTH2_SOFFIT      "Front2Soffit"

#define SE_SOFFIT          "BL_Soffit"
#define SW_SOFFIT          "BR_Soffit"
#define NE_SOFFIT          "FL_Soffit"
#define NW_SOFFIT          "FR_Soffit"
#define SE_SOFFIT1         "BL_Soffit1"
#define SW_SOFFIT1         "BR_Soffit1"
#define NE_SOFFIT1         "FL_Soffit1"
#define NW_SOFFIT1         "FR_Soffit1"
#define SE_SOFFIT2         "BL_Soffit2"
#define SW_SOFFIT2         "BR_Soffit2"
#define NE_SOFFIT2         "FL_Soffit2"
#define NW_SOFFIT2         "FR_Soffit2"

#define REF_TEMP       0
#define TEMP_FACTOR    1 // temp factor
#define MOISTER_FACTOR 2
/*-------- bsmt -------*/

#define EXT_WALL                    1
#define FOUNDATION                  3
#define FOUNDATION_BASESIMP         4
#define EXT_WALL_LOW                2
#define EXT_WALL_MEDIUM             5
#define EXT_WALL_HIGH               6

/*-------- main -------*/

#define FLOOR_TYPE_1 1
#define FLOOR_TYPE_2 2

#define ROOF_TYPE_1 1
#define ROOF_TYPE_2 2

#define CEILING_TYPE_1 1
#define CEILING_TYPE_2 2


#define HOT2000_SINGLE_PANE 100000
#define HOT2000_DOUBLE_PANE 200000
#define HOT2000_TRIPLE_PANE 300000
#define HOT2000_ACRYLIC_PANE 500000

#define HOT2000_SINGLE_PANE_TXT "100000"
#define HOT2000_DOUBLE_PANE_TXT "200000"
#define HOT2000_TRIPLE_PANE_TXT "300000"
#define HOT2000_ACRYLIC_PANE_TXT "500000"

#define THREE_VERTICES    3
#define FOUR_VERTICES     4
#define SIX_VERTICES      6
#define FIVE_VERTICES     5
#define EIGHT_VERTICES    8

#define FLOORS_R           1
#define FLOORS             2
#define RADIANT_SLAB       3
#define NO_BSMT_SLAB       4
#define BSMT_SLAB          5
#define RADIANT_SUBFLOOR   6
#define RADIANT_SUBFLOOR_R 7
#define ASPHALT_ROOF       8
#define CEILING            9
#define CEILING15_25       10
#define CEILING_R          11

#define WALL               20
#define FLR                21
#define ROOF               1

#define DOOR_TYPE_1 1
#define DOOR_TYPE_2 2
#define DOOR_TYPE_3 3
#define DOOR_TYPE_4 4
#define DOOR_TYPE_5 5
#define DOOR_TYPE_6 6
#define DOOR_TYPE_7 7
#define DOOR_TYPE_8 8
#define DOOR        10
#define WINDW       11
#define SKYLIGHT    12

#define VERT_1             0
#define VERT_2             1
#define VERT_3             2
#define VERT_4             3
#define VERT_5             4
#define VERT_6             5
#define VERT_7             6
#define VERT_8             7
#define VERT_9             8
#define VERT_10            9
#define VERT_11            10
#define VERT_12            11
#define VERT_13            12
#define VERT_14            13
#define VERT_15            14
#define VERT_16            15
#define VERT_17            16
#define VERT_18            17

//========== Boundary Conditions ============
//                                  IE2 value
// BASESIMP - no basement
#define BASESIMP_CONFIG_NO_BSMT_SLAB               100   
// BASESIMP - SINGLE rectangular basement or crawl space
#define BASESIMP_CONFIG_BSMT_FLR                   40
#define BASESIMP_CONFIG_BSMT_4WALLS                15
#define BASESIMP_CONFIG_BSMT_3WALLS                20
#define BASESIMP_CONFIG_BSMT_2WALLS                30
#define BASESIMP_CONFIG_BSMT_1WALLS                60
// BASESIMP - SINGLE walk out
#define BASESIMP_CONFIG_SINGLE_WALKOUT_SLAB        50
#define BASESIMP_CONFIG_SINGLE_WALKOUT_BK_WALL     30
#define BASESIMP_CONFIG_SINGLE_WALKOUT_SIDE_WALL   10
// BASESIMP - row house
#define BASESIMP_CONFIG_MIDDLE_WALKOUT_SLAB        50
#define BASESIMP_CONFIG_MIDDLE_WALKOUT_BK_WALL     50
#define BASESIMP_CONFIG_MIDDLE_WALKOUT_RGT_WALL    0
#define BASESIMP_CONFIG_MIDDLE_WALKOUT_LFT_WALL    0

#define BASESIMP_CONFIG_MIDDLE_BK_WALL             30
#define BASESIMP_CONFIG_MIDDLE_FT_WALL             30
#define BASESIMP_CONFIG_MIDDLE_SIDE_WALL           0

#define BASESIMP_CONFIG_END_WALKOUT_SLAB           50
#define BASESIMP_CONFIG_END_WALKOUT_BK_WALL        25
#define BASESIMP_CONFIG_END_WALKOUT_RGT_WALL       25
#define BASESIMP_CONFIG_END_WALKOUT_LFT_WALL       0
#define BASESIMP_CONFIG_END_WALKOUT_FRONT          0

#define BASESIMP_CONFIG_END_BK_WALL                20
#define BASESIMP_CONFIG_END_FRONT                  20
#define BASESIMP_CONFIG_END_RGT_SIDE_WALL          20
#define BASESIMP_CONFIG_END_LFT_SIDE_WALL          0

#define BASESIMP_UNINSULATED                       10
#define BASESIMP_INSULATED                         1
#define BASESIMP_IC2_SLAB                          28
#define BASESIMP_IC2_WARM_WALL                     0

//{EXTERIOR, IDENTICAL, SIMILAR/CONSTANT, ANOTHER_ZONE, GROUND, ADIABATIC, BASESIMP}

#define ICT_EXTERIOR       0
#define ICT_SIMILAR        1
#define ICT_CONSTANT       2
#define ICT_ANOTHER_ZONE   3
#define ICT_GROUND         4
#define ICT_ADIABATIC      5
#define ICT_BASESIMP       6
#define ICT_UNKNOWN        9

#define ICT_EXTERIOR_TXT      "EXTERIOR"
#define ICT_SIMILAR_TXT       "SIMILAR"
#define ICT_CONSTANT_TXT      "CONSTANT"
#define ICT_ANOTHER_ZONE_TXT  "ANOTHER_ZONE"
#define ICT_GROUND_TXT        "GROUND"
#define ICT_ADIABATIC_TXT     "ADIABATIC"
#define ICT_BASESIMP_TXT      "BASESIMP"
#define ICT_UNKNOWN_TXT       "UNKNOWN"

/* heat & cooling defaults */

#define NO_HEATING_CAP 0.0
#define NO_COOLING_CAP 0.0

/*house type */
#define SINGLE_DETACHED       1
#define DOUBLE_SEMIDETACHED   2
#define DUPLEX                3
#define TRIPLEX               4
#define APARTMENT             5
#define ROW_END_UNIT          6
#define MOBILE_HOME           7
#define ROW_MIDDLE_UNIT       8

/* stories */
#define STORIES_ONE           0
#define STORIES_ONEandHALF    1
#define STORIES_TWO           2
#define STORIES_TWOandHALF    3
#define STORIES_THREE         4
#define STORIES_SPLIT_LEVEL   5
#define STORIES_SPLIT_ENTRY   6

#define MAX_NUM_FLOORS        8

/* building plan shape */
#define NO_SHAPE                    0
#define RECTANGULAR                 1
#define T_SHAPE                     2
#define L_SHAPE                     3
#define CROSS                       4
#define CORNERS_5to6                5
#define CORNERS_7to8                6
#define CORNERS_9to10               7
#define CORNERS_11andMore           8
#define RECTANGULAR_WITH_ADDITION   9
#define PENTACLE                    10
#define NUM_HOUSE_SHAPES            11

#define NONRECTANGULAR              1

/* shape configuration */
#define NO_SHAPE_CONF    0

#define SHAPE_W          1
#define SHAPE_N          2
#define SHAPE_E          3
#define SHAPE_S          4

#define SHAPE_NW         5
#define SHAPE_NE         6
#define SHAPE_SW         7
#define SHAPE_SE         8
 
#define MAIN_TYPE      1
#define ADDITION_TYPE  2

#define SENSOR_1        0
#define SENSOR_2        1
#define SENSOR_3        2
#define SENSOR_4        3
#define SENSOR_5        4

#define ACTUATOR_1      0
#define ACTUATOR_2      1
#define ACTUATOR_3      2
#define ACTUATOR_4      3

#define  NO_OCCUPANTS               0
#define  ONE_OCCUPANTS              1
#define  TWO_OCCUPANTS              2
#define  THREE_OCCUPANTS            3
#define  FOUR_OCCUPANTS             4
#define  FIVE_OCCUPANTS             5
#define  SIX_OR_MORE_OCCUPANTS      6

#define  NUM_OCCUPANTS              8

const std::string sPRM =  "*prm";
const std::string sMLC =  "*mlc";
const std::string sOPT =  "*opt";
const std::string sPRS =  "*prs";
const std::string sEVN =  "*evn";
const std::string sCLM =  "*clm";
const std::string sPDB =  "*pdb";

const std::string sDATE   =  "*date";
const std::string sROOT   =  "*root";
const std::string sZONPTH =  "*zonpth"; 
const std::string sNETPTH =  "*netpth";
const std::string sCTLPTH =  "*ctlpth";
const std::string sRADPTH =  "*radpth";
const std::string sIMGPTH =  "*imgpth";
const std::string sINDX   =  "*indx";

#define COMP_1_IND  0
#define COMP_2_IND  1
#define COMP_3_IND  2
#define COMP_4_IND  3
#define COMP_5_IND  4
#define COMP_6_IND  5
#define COMP_7_IND  6
#define COMP_8_IND  7
#define COMP_9_IND  8
#define COMP_20_IND 9

/* (REC), REGular (REG) and GENeral (GEN) shaped zones. */
#define   REC  RECTANGULAR
#define   REG  1
#define   GEN  2
/* envelope defaults */

#define CAPACITY_USER_SPECIFIED 1
#define CAPACITY_CALCULATE      2
#define CALCULATED_HEATING_LOADS          3
#define CALCULATED_COOLING_LOADS          7


#define LAYER_1  1
#define LAYER_2  2
#define LAYER_3  3
#define LAYER_4  4
#define LAYER_5  5

#define LAYER_1_IND  0
#define LAYER_2_IND  1
#define LAYER_3_IND  2
#define LAYER_4_IND  3
#define LAYER_5_IND  4

#define NO_LAYERS    0
#define ONE_LAYER    1
#define TWO_LAYERS   2
#define THREE_LAYERS 3
#define FOUR_LAYERS  4
#define FIVE_LAYERS  5

#define AIR_GAP_1 1
#define AIR_GAP_2 2
#define AIR_GAP_3 3
#define AIR_GAP_4 4
#define AIR_GAP_5 5

#define NO_AIR_GAP      0
#define ONE_AIR_GAP     1
#define TWO_AIR_GAPS    2
#define THREE_AIR_GAPS  3
#define FOUR_AIR_GAPS   4
#define FIVE_AIR_GAPS   5

#define INCIDENT_ANGLE_1 0
#define INCIDENT_ANGLE_2 1
#define INCIDENT_ANGLE_3 2
#define INCIDENT_ANGLE_4 3
#define INCIDENT_ANGLE_5 4
#define INCIDENT_ANGLE_6 5


#define NUM_SENSORS      5
#define NUM_ACTUATORS    4

/* 
   Global control. Return sensor type << check required if values other 
   than -3 allowed for sensor >>. 
*/
#define  UNDEFINED_COND   -3      // undefined condition
#define  FUNCTION_GENERATOR -6    // function generator
#define  AMBIENT_DRY_BULB 0       // measures ambient dry bulb temperature
#define  SOL_AIR_TEMP     1       // measures the sol-air temperature
#define  WIND_SPEED       2       // measures wind speed
#define  WIND_DIRECTION   3       // measures wind direction
#define  DIF_HOR_RAD      4       // measures dif hor rad
#define  DIR_NOR_RAD      5       // measures dir nor rad
#define  EXT_REL_HUM      6       // measures ext rel hum

#define  ON_OFF_CONTROLLER   1    // Global on-off controller
#define  CAPACITY_CONTROLLER 2    // Global capacity controller
#define  ON_CONTROLLER       3    // Global schedule on controller

#define  VOLTAGE_REACTIVE_POWER 1  // Voltage > Reactive power
#define  APPARENT_POWER_ON_OFF  10 // ApparentPower > on/off

                  /* Flow control type.   */

#define  DRY_BULB_GT_FLOW     1   // dry bulb > flow   
#define  ENTHALPY_GT_FLOW     3   // enthalpy > flow   
#define  FIRST_PHASE_GT_FLOW  5   // 1st phase > flow 
#define  SECOND_PHASE_GT_FLOW 7   // 2nd phase > flow  
#define  PLANT_GT_FLOW        9   // plant > flow      
#define  RH_GT_FLOW           11  // RH > flow         
#define  DELTA_T_GT_FLOW      24  // delt T > flow     
#define  ABS_DELTA_T_GT_FLOW  25  // abs Delta T > flow 
#define  PRESURE_GT_FLOW      26  // pressure > flow   
#define  DELTA_PRESS_GT_FLOW  27  // delta press > flow   
#define  ABS_DELTA_GT_FLOW    28  // abs delta P > flow 
#define  ABS_FLOW_GT_FLOW     29  // abs flow > flow  
#define  CONTAM_CONC_GT_FLOW  41  // contam conc > flow"
 
#define  OUTSIDE_AMBIENT_GT_FLOW -3     // outside ambient > flow 

                       /* Control law.   */

#define  ON_OFF 0 // on / off                
#define  PROPORTIONAL 1 // proportional + hysteresis
#define  LOW_DEFAULT_MID_HIGH 2 // low/default/mid/hi       
#define  MULTI_SENSOR_ON_OFF 3 // multi sensor on/off      
// Electric
#define  ESPR_ELECTRIC_FORCED_AIR            12
// natural gas
#define  CONTINOUS_PILOT                     1   
#define  SPARK_IGNITION                      2 
#define  SPARK_IGNITION_AND_VENTDAMPER       3 
#define  INDUCED_DRAFT                       4
#define  CONDENSING                          5
#define  NATURNAL_DRAFT                      4

#define  ESPR_CONTINOUS_PILOT                7
#define  ESPR_SPARK_IGNITION                 5
#define  ESPR_SPARK_IGNITION_AND_VENTDAMPER  6
#define  ESPR_INDUCED_DRAFT                  10
#define  ESPR_CONDENSING                     8
#define  ESPR_UNKNOWN_TYPE                   0
// oil
#define  FLUE_VENT_DAMPER               2
#define  FLAME_RETENTION_HEAD           3
#define  MID_EFFICIENCY                 4
#define  CONDENSING                     5
#define  DIRECT_VENT_NON_CONDENSING     6

#define  ESPR_FLUE_VENT_DAMPER               4
#define  ESPR_FLAME_RETENTION_HEAD           3
#define  ESPR_MID_EFFICIENCY                11
#define  ESPR_CONDENSING                     8
#define  ESPR_NONCONDENSING                  14
#define  ESPR_FLAME_RETENTION_HEAD           3
#define  ESPR_DIRECT_VENT_NON_CONDENSING     9

// wood
#define  ADVANCED_AIR_TIGHT         1
#define  CATALYTIC_CONVERTER        2
#define  WOOD_FURNACE               3
#define  CONVENTIONAL_FURNACE       4
#define  CONVENTIONAL_STOVE         5
#define  PELLET_STOVE               6
#define  MANSONARY_HEATER           7
#define  CONVENTIONAL_FIREPLACE     8
#define  FIREPLACE_INSERT           10

#define  ESPR_ADVANCED_AIR_TIGHT      1
#define  ESPR_CATALYTIC_CONVERTER     2
#define  ESPR_WOOD_FURNACE            13
#define  ESPR_FIREPLACE_INSERT        13
#define  ESPR_CONVENTIONAL_FURNACE    13
#define  ESPR_CONVENTIONAL_STOVE      13
#define  ESPR_PELLET_STOVE            13
#define  ESPR_MANSONARY_HEATER        13
#define  ESPR_CONVENTIONAL_FIREPLACE  13
#define  ESPR_FIREPLACE_INSERT        13

// building miscellaneous data bmiscd

#define MAX_HEATING_CAP          0
#define MIN_HEATING_CAP          1
#define MAX_COOLING_CAP          2
#define MIN_COOLING_CAP          3
#define HEATING_SETPT            4
#define COOLING_SETPT            5
#define COOLING_THROTTLING_RANGE 6
#define UPPER_REL_HUM_SETPT      7    // Upper relative humidity set point (%)
#define LOWER_REL_HUM_SETPT      8    // Lower relative humidity set point (%).
#define HUMIDIFICATION_CAP       9    // Humidification capacity limit (W)
#define DEHUMIDIFICATION_CAP     10   // Dehumidification capacity limit (W)
#define REL_HUMIDITY_CNTL_METHOD 11   // Relative humidity control method 
#define NUM_ITEMS                26   // Relative humidity control method 

// plant miscellaneous data pmiscd
#define NUM_DATA_ITEMS           0    // number of data items
#define COGEN_SYS_CON_OUTPUT     1    // cogen system constant output (W)
#define MINIMUM_COOLING_CAP      2    // Thermal load following priority (1   cooling system, 2 heating system)
#define HOT_WATER_TANK_INDEX     3    // Hot water storage tank pointers -1 for none
#define HOT_TANK_NODE            4    // Cold water storage tank pointers -1 for none

#define COLD_WATER_TANK_INDEX    5
#define COLD_TANK_NODE           6    // Upper relative humidity set point (%)
#define HEATING_SEASON_START     7    // Heating season start (1-365).
#define HEATING_SEASON_END       8    // Heating season end   (1-365)
#define HOT_STORAGE              9    // hot storage algorithm

#define DHW_TANK_LOWER_SETPOINT  10   // Hot tank lower setpoint (oC) 
#define DHW_TANK_UPPER_SETPOINT  11   // Hot tank upper setpoint (oC)
#define HWT_COEFF_A              12   // Coefficient for target temp (0<a<1)
#define HWT_COEFF_KP             13   // Proportional gain (0<Kp<oo)
#define HWT_COEFF_KI             14   // Integral gain (0<Ki<oo) 

#define HWT_COEFF_KD             15   // Derivitive gain (0<Kd<oo)
#define HWT_PER_INTEGRAL         16   // Integral period (hours)
#define HWT_PER_DERIVATIVE       17   // Derivitive period (hours)     
#define TIME_STEP_OUTPUT_FLAG    18

#define PL_FREE_FLOATING         0   //   0   FREE FLOAT
#define PL_CON_ELEC_OUTPUT       1   //   1   Constant electrical output
#define PL_ELEC_LOAD_FOLLOWING   2   //   2   electrical load following
#define PL_THERMAL_FOLLOWING     3   //   3   PID (thermal following)
#define PL_THERMAL_PRIORITY      4   //   4   PID (thermal priority)


#define PL_HEATING_COIL          6 
#define PL_HC_AIR_NODE           2
#define PL_FLUX_EVAL_CALCULATION 1
#define PL_MAX_HEATING_FLUX 99000.0
#define PL_MAX_COOLING_FLUX 99000.0
#define PL_AIR_HANDLER_FAN       5
#define PL_AIR_HANDLER_NODE      1
#define PL_COUPLED_NODE_EXT_COMP 1
#define PL_HWT_PTR               2
#define PL_HW_SENSOR_PTR         1
#define PL_BURNER_ON             1.0
#define PL_BURNER_OFF            0.0

#define PL_CTL_CONFIG            1
#define PL_HWT_POINTER           2

//////////////////////////////control law
#define NO_CONTROL               0
#define IDEAL_CTL                1
#define BASIC_CONTROLLER         1 
#define FREE_FLOATING_CTL        2 
#define IDEAL_CTL_PRE_HEAT_COOL  3
#define IDEAL_FIXED_INJ          4
#define BASIC_PROPORTIONAL_CTL   5
#define FLUX_ZONE_CTL            6
#define MULTI_STAGE_HYST_CTL     7
#define VARIABLE_SUPPLY_CTL      8
#define HEAT_PIPE_IN_CONTR_CTL   9
#define SEPARATE_ON_OFF          10
#define MATCH_TEMP_IDEAL_CTL     11
#define MATCH_TEMP_ON_OFF_CTL    12 
#define TIME_PROPORTIONAL_CTL    13
#define FLOATING_CTL             14
#define OPT_START_LOGIC_CTL      15
#define OPT_STOP_LOGIC_CTL       16
#define FUZZY_LOGIC_PI_PD_CTL    17
#define NULL_CTL                 18
#define IDEAL_MULTI_SENSOR_CTL   19
#define EVAPORATIVE_SOURCE       20
#define SLAVE_CAP_SOURCE         21
#define PLANT_MAS_RT             22
#define RH_MAS_RT                23
#define DELTA_T                  24   
#define ABS_DELTA_T              25
#define PRESSURE                 26
#define BASIC_CTL_W_FREE_COOL    27 // 17-Mar-2012 BAL: Added free cooling control
#define ABS_DELTA_PRESSURE       28
#define ABS_FLOW                 29

// 17-Mar-2012 BAL: minimum difference between indoor and outdoor T for free cooling.
#define DEFAULT_FREE_COOL_DELTA_T 3.0f // [deg C]

// 17-Mar-2012 BAL: Adding allowable rise options for free cooling
#define ALLOWABLE_RISE_MEDIUM    1
#define ALLOWABLE_RISE_HIGH      2
#define ALLOWABLE_RISE_NO_LIMIT  3

/* day type scheduling */
#define OCCUPIED_IND             0
#define LIGHTS_IND               1
#define EQUIPMENT_IND            2

#define NO_TYPE               0
#define OCCUPANCY             1
#define LIGHTS                2
#define EQUIPMENT             3
#define USER_CONT_GAIN        4  // User controllable gain (not fully utilised as yet)
#define OCCUPANCY_PER_PERSON  -1 // Occupancy as floor area per person
#define LIGHTS_PER_SQFT       -2 // Lights in w/m^2 per floor area
#define EQUIPMENT_PER_SQFT    -3 // Equipment in w/m^2 per floor area

#define NO_DATA_ITEMS 0
#define ONE_DATA_ITEMS 1
#define TWO_DATA_ITEMS 2
#define THREE_DATA_ITEMS 3
#define FOUR_DATA_ITEMS 4
#define FIVE_DATA_ITEMS 5
#define SIX_DATA_ITEMS 6
#define SEVEN_DATA_ITEMS 7
#define EIGHT_DATA_ITEMS 8
#define EIGHTEEN_DATA_ITEMS 18


#define LEADING              1   // reactive
#define LAGGING             -1   // capacitance
#define UNITY                0   // pure resistive

/* thermostat control*/
#define INFIL_ONLY_WIND_SPEED    -14 // infil only: wind speed
#define INFIL_ONLY_EXIT_DB       -13 // infil only: ext db temp
#define INFIL_ONLY_ADJ_ZONE_TMP  -12 // infil only: adj zone tmp
#define INFIL_ONLY_ZONE_TMP      -11 // infil only: zone temp
#define VENT_ONLY_WIND_SPEED     -4  // vent only: wind speed
#define VENT_ONLY_EXIT_DB        -3  // vent only: ext db temp
#define VENT_ONLYADJ_ZONE_TMP    -2  // vent only: adj zone temp
#define VENT_ONLY_ZONE_TMP       -1  // vent only: zone temp
#define INFIL_VENT_WIND_SPEED    4   // infil & vent: wind speed
#define INFIL_VENT_EXIT_DB       3   // infil & vent: ext db T
#define INFIL_VENT_ADJ_ZONE_TMP  2   // infil & vent: adj zone T
#define INFIL_VENT_ZONE_TMP      1   // infil & vent: zone T
#define NO_AIR_FLOW_CNTL         0   // no control of air flow

#define NO_DAY_TYPE           0
#define ONE_DAY_TYPE          1
#define TWO_DAY_TYPES         2
#define THREE_DAY_TYPES       3
#define FOUR_DAY_TYPES        4

#define DAY_TYPE_1   1
#define DAY_TYPE_2   2
#define DAY_TYPE_3   3
#define DAY_TYPE_4   4
#define DAY_TYPE_5   5


#define START_DAY        0
#define END_DAY          1

#define NO_PERIOD           0
#define ONE_PERIOD          1
#define TWO_PERIODS         2
#define THREE_PERIODS       3
#define FOUR_PERIODS        4

#define CNTL_PERIOD_1       1
#define CNTL_PERIOD_2       2
#define CNTL_PERIOD_3       3
#define CNTL_PERIOD_4       4
#define CNTL_PERIOD_5       5
#define NUM_CNTL_PERIODS    6

#define CNTL_PERIOD_1_IND       0
#define CNTL_PERIOD_2_IND       1
#define CNTL_PERIOD_3_IND       2
#define CNTL_PERIOD_4_IND       3
#define CNTL_PERIOD_5_IND       4

#define CNTL_FUNCTION_1       1
#define CNTL_FUNCTION_2       2
#define CNTL_FUNCTION_3       3
#define CNTL_FUNCTION_4       4
#define CNTL_FUNCTION_5       5

#define NO_CNTL_FNS      0
#define ONE_CNTL_FN      1
#define TWO_CNTL_FNS     2
#define THREE_CNTL_FNS   3
#define FOUR_CNTL_FNS    4
#define FIVE_CNTL_FNS    5


#define TMC_TYPE_1          1
#define TMC_TYPE_2          2
#define TMC_TYPE_3          3
#define TMC_TYPE_4          4

#define TMC_TYPE_1_IND      0
#define TMC_TYPE_2_IND      1
#define TMC_TYPE_3_IND      2
#define TMC_TYPE_4_IND      3

#define NO_WINDOWS        0
#define ONE_WINDOW        1
#define TWO_WINDOWS       3
#define THREE_WINDOWS     3
#define FOUR_WINDOWS      4
#define FIVE_WINDOWS      5
#define SIX_WINDOWS       6
#define SEVEN_WINDOWS     7

#define NO_DOORS        0
#define ONE_WINDOW        1
#define TWO_DOORS       3
#define THREE_DOORS     3
#define FOUR_DOORS      4
#define FIVE_DOORS      5
#define SIX_DOORS       6
#define SEVEN_DOORS     7


/* Control data types                 */
#define FIRST_CTL_FN     1
#define SECOND_CTL_FN    2
#define THIRD_CTL_FN     3
#define FOURTH_CTL_FN    4

#define FIRST_CTL_FN_IND     0
#define SECOND_CTL_FN_IND    1
#define THIRD_CTL_FN_IND     2
#define FOURTH_CTL_FN_IND    3

#define FIRST_PERIOD_IND     0
#define SECOND_PERIOD_IND    1
#define THIRD_PERIOD_IND     2
#define FOURTH_PERIOD_IND    3
#define FIFTH_PERIOD_IND     4

#define FIRST_PERIOD    1
#define SECOND_PERIOD   2
#define THIRD_PERIOD    3
#define FOURTH_PERIOD   4
#define FIFTH_PERIOD    5
#define SIXTH_PERIOD    6
#define SEVENTH_PERIOD  7
#define EIGTH_PERIOD    8
#define NINTH_PERIOD    9
#define TENTH_PERIOD    10

#define SOIL_LAYERS 12
#define INC_A  5               // max number of incident angles

#define NUM_ROOF_SURFS 20
#define ROOF_SIDE 1
#define ROOF_END  2


#define FIRST	 0
#define SECOND  1
#define THIRD   2	
#define FOURTH  3	
#define FIFTH   4	
#define SIXTH   5
#define SEVENTH 6
#define EIGTH   7	
#define NINTH   8
#define TENTH   9


#define FIRST_WALL  1
#define SECOND_WALL 2
#define THIRD_WALL  3	
#define FOURTH_WALL 4

#define ROOF_SURF_1  0
#define ROOF_SURF_2  1
#define ROOF_SURF_3  2
#define ROOF_SURF_4  3
#define ROOF_SURF_5  4
#define ROOF_SURF_6  5
#define ROOF_SURF_7  6
#define ROOF_SURF_8  7
#define ROOF_SURF_9  8
#define ROOF_SURF_10 9
#define ROOF_SURF_11 10
#define ROOF_SURF_12 11
#define ROOF_SURF_13 12
#define NUM_ROOF_SURFACES 13

#define PV_ZONE_NAME         "PVZone"

// Error codes

#define ERROR_NO_ERROR              0
#define ERROR_WALLS_NOT_IN_ORDER    1
#define ERROR_WALL_DATA_INCORRECT   2
#define ERROR_DOOR_DATA_INCORRECT   3
#define ERROR_WINDOW_DATA_INCORRECT 4
#define ERROR_FLOOR_DATA_INCORRECT  5

/*----------------( units )-------*/
#define METRIC   0
#define IMPERIAL 1
#define US       2

#define BTU_PER_HR_TO_WATT_HRS     0.2930711f
#define CAPACITY_METRIC   1
#define CAPACITY_IMPERIAL 0

#define PV_POWER 10

#define PI_VAL  3.14159265358979323846

// JTB: ESP-R RUN FEEDBACK OPTIONS
#define NORMAL   1
#define DETAILED 2

#define BASEHOUSE    1
#define UPGRADEHOUSE 2
#define ESC_RUN      3 

#define DESLD_KITCHEN_ROOM 1001
#define DESLD_LIVING_ROOM  1002
#define DESLD_DINING_ROOM  1003
#define DESLD_BEDROOM      1004
#define DESLD_BATHROOM     1005
#define DESLD_UTILITY_ROOM 1006
#define DESLD_OTHER_ROOM   1007

#endif // _ESPRHOT3000_H