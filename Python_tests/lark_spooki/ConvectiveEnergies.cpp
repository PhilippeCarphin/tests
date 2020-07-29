#define LIFTEDFROM "[SURFACE|MEAN_LAYER|MOST_UNSTABLE]"

#define CAPETYPE "[UNBOUNDED|BOUNDED|BOTH]"

//#define VIRTUALTEMPERATURE_CHOICES (YES)(NO)(BOTH)
#define VIRTUALTEMPERATURE_CHOICES (YES)(NO)
#define VIRTUALTEMPERATURE CREATE_DEFINE_CHOICES ( VIRTUALTEMPERATURE_CHOICES )
CREATE_ENUM ( VIRTUALTEMPERATURE_ENUM, VIRTUALTEMPERATURE_CHOICES )

//#define VALID_UNITS_BASEMEANLAYER "[mb|Pa|hPa|kPa|ft|m|dm|km]"
//#define VALID_UNITS_DELTAMEANLAYER "[mb|Pa|hPa|kPa|ft|m|dm|km]"
#define VALID_UNITS_BASEMEANLAYER     "[mb|Pa|hPa|kPa]"
#define VALID_UNITS_DELTAMEANLAYER    "[mb|Pa|hPa|kPa]"
#define VALID_UNITS_DELTAMOSTUNSTABLE "[mb|Pa|hPa|kPa]"

#define VALID_UNITS_ENDLEVEL  "[mb|Pa|hPa|kPa]"
#define VALID_UNITS_INCREMENT "[mb|Pa|hPa|kPa]"

#define VALID_UNITS_FOR_BOUNDS "[m|dam|km|C]"

#define OUTPUTCONVLEVELS      "[LFC_PRESSURE|LFC_HEIGHT|EL_PRESSURE|EL_HEIGHT]"

#define SELECTCRITERIA_CHOICES (TEMPERATURE)(HEIGHT)
#define SELECTCRITERIA  CREATE_DEFINE_CHOICES ( SELECTCRITERIA_CHOICES )
CREATE_ENUM ( SELECTCRITERIA_ENUM, SELECTCRITERIA_CHOICES )

#define INPUTFIELDNAME_TT    "TT"

#define INPUTFIELDNAME_PEL  "PEL"
#define INPUTFIELDNAME_PVE  "PVE"
#define INPUTFIELDNAME_ZEL  "ZEL"
#define INPUTFIELDNAME_ZVE  "ZVE"

#define INPUTFIELDNAME_PFC  "PFC"
#define INPUTFIELDNAME_PVC  "PVC"
#define INPUTFIELDNAME_ZFC  "ZFC"
#define INPUTFIELDNAME_ZVC  "ZVC"

#define INPUTFIELDNAME_DPEL  "DPEL"
#define INPUTFIELDNAME_DPVE  "DPVE"
#define INPUTFIELDNAME_DZEL  "DZEL"
#define INPUTFIELDNAME_DZVE  "DZVE"

#define INPUTFIELDNAME_DPFC  "DPFC"
#define INPUTFIELDNAME_DPVC  "DPVC"
#define INPUTFIELDNAME_DZFC  "DZFC"
#define INPUTFIELDNAME_DZVC  "DZVC"

#define INPUTFIELDNAME_MPEL  "MPEL"
#define INPUTFIELDNAME_MPVE  "MPVE"
#define INPUTFIELDNAME_MZEL  "MZEL"
#define INPUTFIELDNAME_MZVE  "MZVE"

#define INPUTFIELDNAME_MPFC  "MPFC"
#define INPUTFIELDNAME_MPVC  "MPVC"
#define INPUTFIELDNAME_MZFC  "MZFC"
#define INPUTFIELDNAME_MZVC  "MZVC"

#define INPUTFIELDNAME_UPEL  "UPEL"
#define INPUTFIELDNAME_UPVE  "UPVE"
#define INPUTFIELDNAME_UZEL  "UZEL"
#define INPUTFIELDNAME_UZVE  "UZVE"

#define INPUTFIELDNAME_UPFC  "UPFC"
#define INPUTFIELDNAME_UPVC  "UPVC"
#define INPUTFIELDNAME_UZFC  "UZFC"
#define INPUTFIELDNAME_UZVC  "UZVC"

#define OUTPUTFIELDNAME_CAPE "CAPE"
#define OUTPUTFIELDNAME_CINH "CINH"
#define OUTPUTFIELDNAME_VCP  "VCP"
#define OUTPUTFIELDNAME_VCN  "VCN"

#define OUTPUTFIELDNAME_DCP  "DCP"
#define OUTPUTFIELDNAME_DCN  "DCN"
#define OUTPUTFIELDNAME_DVCP "DVCP"
#define OUTPUTFIELDNAME_DVCN "DVCN"

#define OUTPUTFIELDNAME_MCP  "MCP"
#define OUTPUTFIELDNAME_MCN  "MCN"
#define OUTPUTFIELDNAME_MVCP "MVCP"
#define OUTPUTFIELDNAME_MVCN "MVCN"

#define OUTPUTFIELDNAME_UCP  "UCP"
#define OUTPUTFIELDNAME_UCN  "UCN"
#define OUTPUTFIELDNAME_UVCP "UVCP"
#define OUTPUTFIELDNAME_UVCN "UVCN"

#define CODE_PDSLABEL_SFC    "CNVEGY"
#define CODE_PDSLABEL_OTHER  "CE"

/*((NAME, SHORT_NAME (can't use h or v), TYPE, MANDATORY, HAS_DEFAULT, DEFAULT, HELP))*/
#define OPTIONS_COLLECTION                                                                                   \
((liftedFrom, "", string, TRUE,  FALSE, "",                                                                   \
    "Level from which parcel is lifted. \n  "                                                                 \
    "Supported types: [STRING" LIFTEDFROM "] \n  "                                                            \
    "Ex: --liftedFrom SURFACE \n"))                                                                           \
((virtualTemperature, "", VIRTUALTEMPERATURE_ENUM_t, TRUE,  FALSE, "",                                        \
    "Specify if the virtual temperature correction should be applied. \n  "                                   \
    "Supported types: [STRING" VIRTUALTEMPERATURE "] \n  "                                                    \
    "Ex: --virtualTemperature YES \n"))                                                                      \
((baseMeanLayer, "", string, FALSE, FALSE, "",                                                               \
    "Base level of the mean layer.\n  "                                                                      \
    "Mandatory if '--liftedFrom MEAN_LAYER' is used.\n  "                                                    \
    "Supported types: [ STRING[SURFACE] | [ FLOAT[0 to +infinity]+STRING" VALID_UNITS_BASEMEANLAYER " ] ]\n  " \
    "Ex: --base SURFACE or --base 400mb\n"))                                                                 \
((deltaMeanLayer, "", string, FALSE, FALSE, "",                                                              \
    "Difference between the top and the base of the mean layer.\n  "                                         \
    "Mandatory if '--liftedFrom MEAN_LAYER' is used.\n  "                                                    \
    "Supported types: [ [ FLOAT[0 to +infinity]+STRING" VALID_UNITS_DELTAMEANLAYER " ] ]\n  "                \
    "Ex: --deltaMeanLayer 400mb\n"))                                                                         \
((deltaMostUnstable, "", string, FALSE, FALSE, "",                                                           \
    "Depth in pressure coordinates above the surface where to search for the most unstable parcel.\n  "      \
    "Can be used with '--liftedFrom MOST_UNSTABLE'.\n  "                                                     \
    "Supported types: [ FLOAT [>0.0 to +infinity] + STRING" VALID_UNITS_DELTAMOSTUNSTABLE " ]\n  "           \
    "Default: 300hPa\n  "                                                                                    \
    "Ex: --deltaMostUnstable 500hPa\n"))                                                                     \
((increment,"", string, FALSE, TRUE, "1.0hPa",                                                               \
    "Specify pressure increment between levels\n  "                                                          \
    "Supported types: [ FLOAT [>0.0 to +infinity] + STRING" VALID_UNITS_INCREMENT " ]\n  "                   \
    "Default: 1.0hPa\n  "                                                                                    \
    "Ex: --increment 5.0mb\n"))                                                                              \
((verticalLevel,"",           string, FALSE, FALSE, "",                                                      \
    "Vertical level defined by user from which parcel is lifted.\n  "                                        \
    "Mandatory if '--liftedFrom USER_DEFINED' is used. \n  "                                                 \
    "Supported types: [ FLOAT[0 to +infinity] ]\n  "                                                         \
    "Ex: --verticalLevel 850 \n"))                                                                           \
((outputConvectiveLevels,"",           string, FALSE, FALSE, "",                                             \
    "List of optimal convective level fields required in the output.\n  "                                    \
    "Supported types: [ STRING " OUTPUTCONVLEVELS " ]\n  "                                                   \
    "Ex: --outputConvectiveLevels LFC_PRESSURE,EL_PRESSURE  or --outputConvectiveLevels LFC_HEIGHT  \n"))    \
((capeType, "", string, FALSE,  TRUE, "UNBOUNDED",                                                           \
    "The cape type is either unbounded, bounded vertically or both. \n  "                                    \
    "Supported types: [ STRING" CAPETYPE " ] \n  "                                                           \
    "Ex: --capeType UNBOUNDED \n"))                                                                          \
((lowerBoundary,"",           string, FALSE, FALSE, "" ,                                                        \
    "Value of the lower boundary.\n  "                                                                       \
    "Mandatory if '--capeType BOUNDED or --capeType BOTH' is used.\n  "                                      \
    "Supported types: [ FLOAT [-infinity to +infinity] + STRING" VALID_UNITS_FOR_BOUNDS " ]\n  "             \
    "Ex: --lowerBoundary 0km or --lowerBoundary -10C \n"))                                                   \
((upperBoundary,"",           string, FALSE, FALSE, "" ,                                                        \
    "Value of the upper boundary.\n  "                                                                       \
    "Mandatory if '--capeType BOUNDED or --capeType BOTH' is used.\n  "                                      \
    "Supported types: [ FLOAT [-infinity to +infinity] + STRING" VALID_UNITS_FOR_BOUNDS " ]\n  "             \
    "Ex: --upperBoundary 8km or --upperBoundary 15C\n"))

#define HIDDEN_OPTIONS_COLLECTION                                                                           \
((endLevel, "", string, FALSE, TRUE, "10.0hPa",                                                              \
    "Specify value and units for final parcel level. Will be converted to hPa in algorithm.\n  "             \
    "Supported types: [ FLOAT[0 to +infinity] + STRING" VALID_UNITS_ENDLEVEL " ]\n  "                        \
    "Ex: --endLevel 10.0hPa\n"))