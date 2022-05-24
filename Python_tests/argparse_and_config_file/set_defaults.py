import yaml
import argparse

with open("conf.yml", 'r') as y:
    file_config_dict = yaml.safe_load(y)

p = argparse.ArgumentParser()

p.add_argument("--list", nargs='+')
p.add_argument("--multiple-words", nargs='+')

p.set_defaults(**file_config_dict)

args = p.parse_args()

print(args)
