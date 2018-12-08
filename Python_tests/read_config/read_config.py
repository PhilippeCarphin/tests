class ConfigFileError(Exception):
    pass

def read_config_file(filename):
    data = {}
    lines = []
    current_group = None

    with open(filename) as f:
        lines = map(lambda s : s.strip(), f.readlines())

    line_number = 0
    for l in lines:
        line_number += 1
        words = l.split()
        if words[0].startswith('#'):
            continue
        if words[0].startswith('['):
            current_group_name = words[0].strip('[]')
            data[current_group] = {}
            continue

        key = words[0]
        value = words[1]

        try:
            data[current_group][key] = value
        except KeyError:
            raise ConfigFileError("Expected group before line {} '{}'".format(line_number, l))

    return data

if __name__ == "__main__":
    config_data = read_config_file("config.txt")
    from pprint import pprint
    pprint(config_data)
