import lark
import os
import re
import pprint
from lark_macro_sequence import macro_parser

macro_re = re.compile(r'#define ([a-zA-Z0-9_]*) *(.*)')
test_str = '#define MACRO_NAME asdf asdf asdf'
with open('ConvectiveEnergies.cpp', 'r', encoding='iso8859-1') as f:
    t = f.read()

def remove_escaped_newlines(text):
    return text.replace("\\\n", " ")

def extract_macros(text):
    lines = remove_escaped_newlines(text).splitlines()
    # pprint.pprint(lines) 
    macros = {}
    for l in lines:
        r = macro_re.search(l)
        if r:
            macros[r.group(1)] = r.group(2)
    return macros

        

# print(extract_macros(t))
# r = macro_re.search(test_str)
# print(r.group(1), r.group(2))
# print(extract_macros(t))

macros = extract_macros(t)
parsed_macros = macro_parser(macros['OPTIONS_COLLECTION'])

# for pm in parsed_macros:
#     for i in range(len(pm)):
#         if isinstance(pm[i], lark.Token):
#             print("TOKEN : ", pm[i])
#             pm[i] = str(pm[i])
def eval_and_concatenate(help, macros):
    out_list = []
    # print(help)
    for elem in help:
        # print(f'elem {elem}, type {type(elem)}')
        if isinstance(elem, lark.lexer.Token):
            # print("TOKEN")
            new_elem = macros[elem]
            if 'CREATE_DEFINE_CHOICES' in new_elem:
                # print(f'new_elem = {new_elem}')
                r = re.search(r'([a-zA-Z_]+) *\( *([a-zA-Z_]+).*', new_elem)
                # print(f'r.group(1) = {r.group(1)}')
                # print(f'r.group(2) = {r.group(2)}')
                if r:
                    new_elem = macros[r.group(2)]
                    # print(f'new_elem = {new_elem}')
            out_list.append(new_elem)
        elif isinstance(elem, str):
            out_list.append(elem)

    # print(type(help))
    return ''.join(out_list)

def macro_array_to_dict(macro_array, macros):
    return {
        'name': str(macro_array[0]),
        'sname': macro_array[1],
        'type': str(macro_array[2]),
        'mandatory' : str(macro_array[3]),
        'has_default': str(macro_array[4]),
        'default_value': str(macro_array[5]),
        'help': eval_and_concatenate(macro_array[6], macros)
    }

def process_macros(parsed_macros, macros):
    macro_dicts = map(lambda m: macro_array_to_dict(m, macros), parsed_macros)
    for md in macro_dicts:
        print(md)
        pass
# if isinstance(parsed_macros, list):
#     for macro in parsed_macros:

process_macros(parsed_macros, macros)

