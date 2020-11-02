import json

class Round7FloatEncoder(json.JSONEncoder): 
    def iterencode(self, obj, **kwargs): 
        if isinstance(obj, float): 
            yield format(obj, '.7f')

d = {'four':4, 'pi': 3.14159, 'asdf':[1,2,3,4]}

s = json.dumps(d, cls=Round7FloatEncoder)

print(s)
