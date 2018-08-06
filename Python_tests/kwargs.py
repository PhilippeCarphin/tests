import inspect

def kwarg_function(**kwargs):
    funcname = inspect.stack()[0][3]
    print(funcname + ' ' + generate_cpp_opts(kwargs))

def generate_cpp_opts(kwargs):
    ''' generates a '--key value' string for each 'key: value' pair in
    a dictionnary '''
    return ' '.join([ "--{} {}".format(key, kwargs[key]) for key in kwargs])

def generate_cpp_command(funcname, argvalues):
    ARGS=0
    LOCALS=3
    kwargs = { arg: argvalues[LOCALS][arg] for arg in argvalues[ARGS]}
    return ' '.join([funcname, generate_cpp_opts(kwargs)]).strip()


def named_arg_function(humeur, couleur):
    cpp_cmd = get_caller_cpp_cmd()
    print("=="+cpp_cmd+"==")

def get_caller_cpp_cmd():
    caller_funcname = inspect.stack()[1][3]
    caller_argvalues = inspect.getargvalues(inspect.currentframe().f_back)
    kwargs = { arg: caller_argvalues[3][arg] for arg in caller_argvalues[0]}
    return ' '.join([caller_funcname, generate_cpp_opts(kwargs)]).strip()

def named_noarg_function():
    cpp_cmd = generate_cpp_command(
        inspect.stack()[0][3],
        inspect.getargvalues(inspect.currentframe())
    )
    print("=="+cpp_cmd+"==")

plugin_spec = {
        'WindChill': ['param1', 'param2'],
        'AbsoluteValue' : []
        }

def generate_function(plugin_name, argument_names):
    func_decl = "def " + plugin_name + "(" + ', '.join(argument_names) + '):'
    common_body = '''
    cpp_cmd = generate_cpp_command(
        inspect.stack()[0][3],
        inspect.getargvalues(inspect.currentframe())
    )
    return libmeteo_operations.evaluatePlugin(cpp_cmd)
'''
    return func_decl + common_body

def generate_python_functions(plugin_spec):
    functions = ""
    for plugin in plugin_spec:
        func_def = generate_function(plugin, plugin_spec[plugin])
        functions += "\n\n" + func_def
    return functions


if __name__ == "__main__":
    kwarg_function(humeur="joyeux", temperature="fa-chaud")
    kwarg_function(couleur="rose", vent="y-vente")
    named_arg_function(humeur=8, couleur=7)
    named_noarg_function()
    # print(generate_python_functions(plugin_spec))
