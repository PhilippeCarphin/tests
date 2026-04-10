import abc
class Animal(abc.ABC):
    @abc.abstractmethod
    def speak(self):
        pass

class Dog(Animal):
    def speak(self):
        print("Woof")

class AbstractCat(Animal):
    # Because Cat does not implement speak, and speak is an abstract method of
    # Animal, this makes it impossible to INSTANCIATE this class
    def scratch_the_couch(self):
        pass

class Cat(AbstractCat):
    def speak(self):
        print("Meow")
    def scratch_the_couch(self):
        print("Cat is scratching the couch")

d = Dog()

# This line raises "TypeError: Can't instantiate abstract class Cat with abstract method speak"
# ac = AbstractCat()
c = Cat()
