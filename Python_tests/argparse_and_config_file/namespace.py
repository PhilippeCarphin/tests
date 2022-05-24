import argparse
import yaml

p = argparse.ArgumentParser()

p.add_argument("--list", nargs='+', help="a list of items")


with open('conf.yml', 'r') as c:
    file_config_dict = yaml.safe_load(c)

class Config():
    pass

config = Config()

config.__dict__ = file_config_dict
p.parse_args(namespace=config)
print(config.__dict__)

