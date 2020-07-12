from lark import Lark
from lark.reconstruct import Reconstructor


macro = """((liftedFrom, "allo", string, TRUE,  FALSE, "", "Level " NAME "\\nrom which parcel is lifted.")) ((virtualTemperature, "", VIRTUALTEMPERATURE_ENUM_t, TRUE,  FALSE, "", "Specify if the virtual temperature correction should be apn"))"""

macro = """((liftedFrom, "", string, TRUE,  FALSE, "", "Level from which parcel is lifted. \n  " "Supported types: [STRING" LIFTEDFROM "] \n  " "Ex: --liftedFrom SURFACE \n")) ((virtualTemperature, "", VIRTUALTEMPERATURE_ENUM_t, TRUE,  FALSE, "", "Specify if the virtual temperature correction should be applied. \n  " "Supported types: [STRING" VIRTUALTEMPERATURE "] \n  " "Ex: --virtualTemperature YES \n")) ((baseMeanLayer, "", string, FALSE, FALSE, "", "Base level of the mean layer.\n  " "Mandatory if '--liftedFrom MEAN_LAYER' is used.\n  " "Supported types: [ STRING[SURFACE] | [ FLOAT[0 to +infinity]+STRING" VALID_UNITS_BASEMEANLAYER " ] ]\n  " "Ex: --base SURFACE or --base 400mb\n")) ((deltaMeanLayer, "", string, FALSE, FALSE, "", "Difference between the top and the base of the mean layer.\n  " "Mandatory if '--liftedFrom MEAN_LAYER' is used.\n  " "Supported types: [ [ FLOAT[0 to +infinity]+STRING" VALID_UNITS_DELTAMEANLAYER " ] ]\n  " "Ex: --deltaMeanLayer 400mb\n")) ((deltaMostUnstable, "", string, FALSE, FALSE, "", "Depth in pressure coordinates above the surface where to search for the most unstable parcel.\n  " "Can be used with '--liftedFrom MOST_UNSTABLE'.\n  " "Supported types: [ FLOAT [>0.0 to +infinity] + STRING" VALID_UNITS_DELTAMOSTUNSTABLE " ]\n  " "Default: 300hPa\n  " "Ex: --deltaMostUnstable 500hPa\n")) ((increment,"", string, FALSE, TRUE, "1.0hPa", "Specify pressure increment between levels\n  " "Supported types: [ FLOAT [>0.0 to +infinity] + STRING" VALID_UNITS_INCREMENT " ]\n  " "Default: 1.0hPa\n  " "Ex: --increment 5.0mb\n")) ((verticalLevel,"",           string, FALSE, FALSE, "", "Vertical level defined by user from which parcel is lifted.\n  " "Mandatory if '--liftedFrom USER_DEFINED' is used. \n  " "Supported types: [ FLOAT[0 to +infinity] ]\n  " "Ex: --verticalLevel 850 \n")) ((outputConvectiveLevels,"",           string, FALSE, FALSE, "", "List of optimal convective level fields required in the output.\n  " "Supported types: [ STRING " OUTPUTCONVLEVELS " ]\n  " "Ex: --outputConvectiveLevels LFC_PRESSURE,EL_PRESSURE  or --outputConvectiveLevels LFC_HEIGHT  \n")) ((capeType, "", string, FALSE,  TRUE, "UNBOUNDED", "The cape type is either unbounded, bounded vertically or both. \n  " "Supported types: [ STRING" CAPETYPE " ] \n  " "Ex: --capeType UNBOUNDED \n")) ((lowerBoundary,"",           string, FALSE, FALSE, , "Value of the lower boundary.\n  " "Mandatory if '--capeType BOUNDED or --capeType BOTH' is used.\n  " "Supported types: [ FLOAT [-infinity to +infinity] + STRING" VALID_UNITS_FOR_BOUNDS " ]\n  " "Ex: --lowerBoundary 0km or --lowerBoundary -10C \n")) ((upperBoundary,"",           string, FALSE, FALSE, , "Value of the upper boundary.\n  " "Mandatory if '--capeType BOUNDED or --capeType BOTH' is used.\n  " "Supported types: [ FLOAT [-infinity to +infinity] + STRING" VALID_UNITS_FOR_BOUNDS " ]\n  " "Ex: --upperBoundary 8km or --upperBoundary 15C\n"))"""
macro = macro.replace('\n', '\\n')

macro_grammar = """
    ?start:value
    ?value: macro
    item : (name | string)*
    
    macro : [array (array)*]
    array  : "((" name "," string "," name "," name "," name "," item "," item "))"

    string: ESCAPED_STRING
    name : NAME

    %import common.CNAME -> NAME
    %import common.ESCAPED_STRING
    %import common.WS

    %ignore WS
"""

macro_parser = Lark(macro_grammar, parser='earley', lexer='standard')

parsed = macro_parser.parse(macro)

import pprint


print(parsed.pretty())
