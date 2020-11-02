import threading
from json import encoder

def FLOAT_REPR(f):
    """
    Serialize a float to a string, with a given number of digits
    """
    decimal_places = getattr(encoder.thread_local, 'decimal_places', 0)
    format_str = '%%.%df' % decimal_places
    return format_str % f

encoder.thread_local = threading.local()
encoder.FLOAT_REPR = FLOAT_REPR

#As an example, call like this:
import json

encoder.thread_local.decimal_places = 1
s = json.dumps([1.56, 1.54]) #Should result in '[1.6, 1.5]'

print(s)
quit()
import json
json.encoder.FLOAT_REPR = lambda flt: format(flt, '.2f')

float_list = [23.678134, 23.971234, 23.8134447]

# print(json.dumps(float_list))


print(json.dumps(float_list, parse_float=lambda x: format(x, '.2f')))
