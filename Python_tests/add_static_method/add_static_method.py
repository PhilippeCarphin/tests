class DemoClass:
    @staticmethod
    def true_static(param):
        print(f"True static method : param = {param}")
    
    def normal_method(self, **kwargs):
        print(f"normal_method(): self={self}, kwargs={kwargs}")

    """
    To help the IDE, these do nothing
    """
    def added_method(self, **kwargs):
        pass
    @staticmethod
    def added_static_method(**kwargs):
        pass
    @classmethod
    def added_class_method(cls, **kwargs):
        pass


def added_method(self, **kwargs):
    if not isinstance(self, DemoClass):
        raise TypeError("Argument self must be an instance of DemoClass")
    print(f'added_method(): self={self}, kwargs={kwargs}')


demo_instance = DemoClass()

print("========== added_method ============")
setattr(DemoClass, "added_method", added_method)
demo_instance.added_method(a='b', c='d')
# DemoClass.added_method(e='f', g='h')  # Doesn't work (missing one positional argument 'self)
try:
    DemoClass.added_method(DemoClass, e='f', g='h')  # Raises TypeError
except TypeError as e:
    print(f'Caught {type(e)} : {e} because there is a type check')
    
DemoClass.added_method(demo_instance, e='f', g='h')  # Behaves the same as normal methods
DemoClass.normal_method(demo_instance, e='f', g='h')  # <- This can already be done with normal methods
DemoClass.normal_method(DemoClass, e='f', g='h')  # <- We don't need the type check in added_method because
                                                  # This is already the default behavior


print("========== added_static_method =====")
@staticmethod
def added_static_method(**kwargs):
    print(f'added_static_method(): kwargs={kwargs}')
setattr(DemoClass, "added_static_method", added_static_method)
DemoClass.added_static_method()
demo_instance.added_static_method()

print("========== added_class_method ======")
@classmethod
def added_class_method(cls, **kwargs):
    print(f'added_class_method(): cls={cls}, kwargs={kwargs}')
setattr(DemoClass, "added_class_method", added_class_method)
DemoClass.added_class_method(q='r', s='t')
demo_instance.added_class_method(u='v', w='x')