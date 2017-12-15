class Quantity:
    def __init__(self, sname):
        self.sname = sname

    '''
    def __set__(self, instance, value):
        instance.__dict__[self.sname] = value
        print('descriptor class set method called')
        '''

    def __get__(self, instance, other):
        ''' This method need not be created '''
        print('descriptor class get method called')
        return instance.__dict__[self.sname]

class Item:
    weight = Quantity('weight')

    def __init__(self, value):
        self.weight = value

    def test(self):
        print(self.value)

    @classmethod
    def __set__(self, instance, value):
        print(self)
        print(instance)
        print(value)
