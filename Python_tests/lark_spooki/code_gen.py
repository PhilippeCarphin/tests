import json
from pprint import pprint

with open('input.json', 'r') as f:
    options = json.load(f)

pprint(options)

def display_default(default):
    if '::' in default:
        return default.split('::')[1]
    else:
        return default

def print_name_param(opt):
    print(f"        \"{opt['name']}\" \"{opt['sname']}\",")

def print_value_param(opt):
    opt_type = opt['type']
    if opt['has_default']:
        default = opt['default_value']
        print(f"        po::value<{opt_type}>()->default_value({default},{display_default(default)}),")
    else:
        print(f"        po::value<{opt_type}>(),")

def print_help_param(opt):
    help = opt['help'].replace('\n', '\\n')
    if opt['mandatory']:
        print(f"        \"*    {help}\"")
    else:
        print(f"        \"     {help}\"")

def print_opt(opt):
    print('    (')
    print_name_param(opt)
    print_value_param(opt)
    print_help_param(opt)
    print('    )')

def print_options(options):

    print('void addBasicOptions() {')
    print('    HighLevelOperation::addBasicOptions();')
    print('    OperationBase::addSpecificOptions()')
    for opt in options:
        print_opt(opt)
    print('    ;')
    print('}')

def declare_and_set(opt):
    get_opt_value = f"getParameterValue(\"{opt['name']}\", {opt['name']});"
    if opt['mandatory']:
        print(f"{opt['type']} {opt['name']};")
        print(get_opt_value)
    else:
        print(f"{opt['type']} {opt['name']} = {opt['type']}();")
        print("if(parameterExists(\"{opt['name']}\")){")
        print("    " + get_opt_value)
        print("}")

def get_parameter_values(options):
    for opt in options:
        declare_and_set(opt)
        

print("--------- PROGRAM OPTIONS --------------------------")
print_options(options)
print("--------- GET_PARAMETER_VALUES() -------------------")
get_parameter_values(options)