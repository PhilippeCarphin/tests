from future-fstrings imp
from collections import namedtuple

#
# Name 'Car' is what will be printed when asking for the type of instances
# however we need to use the object Car_t which refers to the type. Hence they
# should have the same name (I.E. TypeName = namedtuple('TypeName', ...)) to
# make things easy.  I'm putting them with different names here only to
# illustrate the point.
#
Car_t = namedtuple('Car', ['manufacturer', 'model', 'year'])

c = Car_t(manufacturer='Tesla', model='Model 3', year=2018)

# No print can result in seeing 'Car_t' as far as I can tell, it's just the name
# of a variable that holds a type.
print(c)
print(type(c).__name__)
