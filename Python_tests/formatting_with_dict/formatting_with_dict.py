import os
import subprocess
from pprint import pprint


class SpookiTestError(Exception):
    pass


data = {
    'spooki_config': "([ReaderStd --input $SPOOKI_DIR/{sources[0]}] >> [Select --fieldName TT]) + ([ReaderStd --input $SPOOKI_DIR/{sources[1]}] >> [Select --fieldName ES]) >> [InterpolationHorizontalGrid -m FIELD_DEFINED --fieldName ES --interpolationType BI-CUBIC --extrapolationType NEAREST] >> [WriterStd --output {destination_path} {write_options}]",
    'overwrite_file2_compare': True,
    'sources': [
        "2015072100_240_TTESUUVV_YinYang.std",
        "2015072100_240_TTESUUVV_GridZ.std"
    ],
    'comparison_file': "InterpHorizGridUtoZ_rmn19_file2cmp.std",
    'destination_path': 'DEST_PATH',
    'write_options': 'WRITE_OPTIONS',
}

def main():
    os.environ['SPOOKI_DIR'] = '/home/spst900/spooki/spooki_dir_ppp4'
    expanded_config = data['spooki_config'].format(**data)
    print(expanded_config)
    expanded_config = os.path.expandvars(data['spooki_config'].format(**data))
    print(expanded_config)
    # run_test(data)


def make_command(test_data):
    expanded_config = os.path.expandvars(test_data['spooki_config'].format(**test_data))
    command = ['spooki_run', expanded_config]
    if test_data['overwrite_file2_compare']:
        command += '--overwrite?'
    return command


def run_test(test_data):
    try:
        cmd = make_command(test_data)
    except KeyError as e:
        print(f'KeyError: key {e} not found in data')
        return
    except IndexError as e:
        print(f"{e} : Number of source files may not match indices in spooki_config")
        return

    print(cmd)
    # result = subprocess.run(cmd)
    #
    # if result.returncode == 0:
    #     raise SpookiTestError(f"Could not run test: test_data['spooki_config']")

    # validate_test_output()


def compare_voir(file_a, file_b):
    cmd = ['voir', '-iment', '-A', file_a, '-B', file_b]
    result = subprocess.run(cmd)
    return result
def compare_fst(file_a, file_b):
    cmd = ['fstcomp', '-fst', '-A', file_a, '-B', file_b]
    result = subprocess.run(cmd)
    return result
def validate_test_output(test_data):
    result = compare_voir(test_data['destination_path'], test_data['comparison_file'])
    if result.returncode != 0:
        return False
    result = compare_fst(test_data['destination_path'], test_data['comparison_file'])
    if result.returncode != 0:
        return False
    return True

if __name__ == "__main__":
    main()

