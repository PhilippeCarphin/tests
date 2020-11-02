import json
from json import encoder
encoder.FLOAT_REPR = lambda o: ("%.12g" % o)
    
print(json.dumps(23.67))
print(json.dumps([23.0, 23.9, 23.8700123]))
