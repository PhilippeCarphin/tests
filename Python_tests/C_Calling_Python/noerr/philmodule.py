
global_dict = {}
# to show that PyImport_ImportModule can be called multiple times and that
# seems OK.
# print("IMPORTING");

def set_value(key, value):
    global_dict[key] = value
    return 0

def get_value(key):
    return global_dict[key]
