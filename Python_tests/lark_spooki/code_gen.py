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

def print_opt(opt):
    opt_type = opt['type']
    print('(')
    print(f"    \"{opt['name']}\" \"{opt['sname']}\",")
    if opt['has_default']:
        default = opt['default_value']
        print(f"    po::value<{opt_type}>()->default_value({default},{display_default(default)}),")
    else:
        print(f"    po::value<{opt_type}>(),")
    help = opt['help'].replace('\n', '\\n')
    if opt['mandatory']:
        print(f"    \"*    {help}\"")
    else:
        print(f"    \"     {help}\"")
    print(')')

def print_options(options):
    print('OperationBase::addSpecificOptions()')
    for opt in options:
        print_opt(opt)
    print(';')

s = "AIR_DENSITY::ACTUAL".split('::')
print(s)

def get_parameter_values(options):
    for opt in options:
        get_opt_value = f"getParameterValue(\"{opt['name']}\", {opt['name']});"
        if opt['mandatory']:
            print(f"{opt['type']} {opt['name']};")
            print(get_opt_value)
        else:
            print(f"{opt['type']} {opt['name']} = {opt['type']}();")
            print("if(parameterExists(\"{opt['name']}\")){")
            print("    " + get_opt_value)
            print("}")
        

print_options(options)
get_parameter_values(options)