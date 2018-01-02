import module
import user_of_module

module.module_var = 9
print(module.module_var)

module.module_var = 7
print(user_of_module.get_module_var())

