
global_dict = {}

def set_value(key, value):
    global_dict[key] = value
    return 0

def get_value(key):
    return global_dict[key]
