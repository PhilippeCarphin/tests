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

macros = extract_macros(t)
parsed_macros = macro_parser(macros['OPTIONS_COLLECTION'])

def reformat_define_choices(choices_sequence):
    return '[' + choices_sequence.replace(')(', '|').strip('()') + ']'

def resolve_create_define_choices(macro):
    r = re.search(r'([a-zA-Z_]+) *\( *([a-zA-Z_]+).*', macro)
    if r:
        return reformat_define_choices(macros[r.group(2)])

def evaluate_macro(macro):
    evaluated = macros[macro]
    if 'CREATE_DEFINE_CHOICES' in evaluated:
        evaluated = resolve_create_define_choices(evaluated)
    return evaluated.strip('"\'')

def eval_and_concatenate(help, macros):
    out_list = []
    for elem in help:
        if isinstance(elem, lark.lexer.Token):
            out_list.append(evaluate_macro(elem))
        elif isinstance(elem, str):
            out_list.append(elem)
    return ' '.join(out_list).replace('\\n', '\n')

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
        print(md['name'])
        print(md['help'])
        print('-------------------------')

        pass

process_macros(parsed_macros, macros)



