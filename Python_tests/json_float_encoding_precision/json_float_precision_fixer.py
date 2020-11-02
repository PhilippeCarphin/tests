#/usr/bin/env python2
from _ctypes import PyObj_FromPtr
import json
import re
import sys

if sys.version_info.major != 2:
    print("""This program needs to be run with python 2, it may work with python3
but it's weird.  Ideally, whoever reads your json should be able to parse
floats with arbitrary number of digits""")
    sys.exit(1)

# This is based on this answer on Stack Overflow:
# https://stackoverflow.com/a/54371667/5795941
# With an added modification for it to do the same with integers.
# and some extra fluff to allow it to be a command line tool.


import argparse

p = argparse.ArgumentParser()
p.add_argument('--input', help="Input json filename")
p.add_argument('--output', help="Output json filename")
p.add_argument('--convert-ints', action='store_true', help="Converts all ints to floats")
args = p.parse_args()

class FloatWrapper(object):
    """ Float value wrapper. """
    def __init__(self, value):
        self.value = value


class MyEncoder(json.JSONEncoder):
    FORMAT_SPEC = '@@{}@@'
    regex = re.compile(FORMAT_SPEC.format(r'(\d+)'))  # regex: r'@@(\d+)@@'

    def default(self, obj):
        return (self.FORMAT_SPEC.format(id(obj)) if isinstance(obj, FloatWrapper)
                else super(MyEncoder, self).default(obj))

    def iterencode(self, obj, **kwargs):
        for encoded in super(MyEncoder, self).iterencode(obj, **kwargs):
            # Check for marked-up float values (FloatWrapper instances).
            match = self.regex.search(encoded)
            if match:  # Get FloatWrapper instance.
                id = int(match.group(1))
                float_wrapper = PyObj_FromPtr(id)
                json_obj_repr = '%.2f' % float_wrapper.value  # Create alt repr.
                encoded = encoded.replace(
                            '"{}"'.format(self.FORMAT_SPEC.format(id)), json_obj_repr)
            yield encoded

def wrap_number(n):
    if isinstance(n, float) or (isinstance(n, int) and args.convert_ints):
        return FloatWrapper(float(n))
    else:
        return n

def wrap_type(obj, kind, wrapper):
    """ Recursively wrap instances of type kind in dictionary and list
        objects.
    """
    if isinstance(obj, dict):
        new_dict = {}
        for key, value in obj.items():
            if not ( isinstance(value, dict) or isinstance(value, list)):
                new_dict[key] = wrap_number(value)
            else:
                new_dict[key] = wrap_type(value, kind, wrapper)
        return new_dict

    elif isinstance(obj, list):
        new_list = []
        for value in obj:
            if not isinstance(value, (dict, list)):
                new_list.append(wrap_number(value))
            else:
                new_list.append(wrap_type(value, kind, wrapper))
        return new_list

    else:
        return obj


def json_encode_fixed_point(d, **kwargs):
    if 'cls' in kwargs:
        raise Exception("Cannot specify encoder, this method already does it")
    return json.dumps(wrap_type(d, float, FloatWrapper), cls=MyEncoder, **kwargs)

# d = {'four':4, 'pi': 3.14159, 'asdf':[1,2,3,4]}
# print(json_encode_fixed_point(d))


with open(args.input, 'r') as f:
    json_in = json.load(f)

json_out = json_encode_fixed_point(json_in)

if args.output:
    with open(args.output, 'w') as f:
        f.write(json_out)
else:
    print(json_encode_fixed_point(json_in))

