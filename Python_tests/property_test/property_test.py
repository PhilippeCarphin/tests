# Using @property decorator
class Celsius:
    def __init__(self, temperature=0):
        print(f"start of __init__() : self.__dict__ = {self.__dict__}")
        self.temperature = temperature
        print(f"end of __init__() : self.__dict__ = {self.__dict__}")
        print(self.__dir__())

    def to_fahrenheit(self):
        return (self.temperature * 1.8) + 32

    @property
    def temperature(self):
        print("Getting value...")
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        print("Setting value...")
        if value < -273.15:
            raise ValueError("Temperature below -273 is not possible")
        self._temperature = value

    def set_temp(self, value):
        self._temperature = value
    def get_temp(self):
        return self._temperature

    temp = property(get_temp, set_temp)

# create an object
human = Celsius(37)

print(human.temperature)

print(human.to_fahrenheit())

coldest_thing = Celsius(-300)