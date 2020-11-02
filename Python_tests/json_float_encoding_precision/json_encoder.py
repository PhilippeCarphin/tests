import json

import json

class MyCustomEncoder(json.JSONEncoder):
    def iterencode(self, obj):
        if isinstance(obj, float):
            yield format(obj, '.7f')
        elif isinstance(obj, dict):
            last_index = len(obj) - 1
            yield '{'
            i = 0
            for key, value in obj.items():
                yield '"' + key + '": '
                for chunk in MyCustomEncoder.iterencode(self, value):
                    yield chunk
                if i != last_index:
                    yield ", "
                i+=1
            yield '}'
        elif isinstance(obj, list):
            last_index = len(obj) - 1
            yield "["
            for i, o in enumerate(obj):
                for chunk in MyCustomEncoder.iterencode(self, o):
                    yield chunk
                if i != last_index: 
                    yield ", "
            yield "]"
        else:
            for chunk in json.JSONEncoder.iterencode(self, obj):
                yield chunk

d = {'four':4, 'pi': 3.14159}

print(json.dumps(d, cls = MyCustomEncoder))
