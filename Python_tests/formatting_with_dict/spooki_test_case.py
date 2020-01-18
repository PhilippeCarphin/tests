import os
import re
import subprocess
import copy

class SpookiTestFailedException(Exception):
    pass

data = {
    'configuration': "([ReaderStd --input $SPOOKI_DIR/{sources[0]}] >> [Select --fieldName TT]) + ([ReaderStd --input $SPOOKI_DIR/{sources[1]}] >> [Select --fieldName ES]) >> [InterpolationHorizontalGrid -m FIELD_DEFINED --fieldName ES --interpolationType BI-CUBIC --extrapolationType NEAREST] >> [WriterStd --output {output_file} {write_options}]",
    'overwrite_file2_compare': True,
    'sources': [
        "2015072100_240_TTESUUVV_YinYang.std",
        "2015072100_240_TTESUUVV_GridZ.std"
    ],
    'comparison_file': "InterpHorizGridUtoZ_rmn19_file2cmp.std",
    'write_options': 'WRITE_OPTIONS',
    'test_name': 'this_test',
    'plugin_name': 'AbsolutePhil',
    'test_description': 'This test verifies this type of grid',
    'output_filename': 'result_test_global.std', # destination_path
    'file2compare': 'InterpHorizGridUtoZ_rmn19_file2cmp.std',
    'write_options': "",
    'overwrite_file2compare_str': "",
    'cmp_voir': True,
    'cmp_fstcomp': True,
    'erase_tmpdir': True
}

def make_destination_path(test_data):
    return f'{os.environ["SPOOKI_TMPDIR"]}/{test_data["plugin_name"]}/result_{test_data["test_name"]}'

class SpookiTestCaseError(Exception):
    pass

class SpookiTestCase:
    def __init__(self, input_data):
        self.configuration = input_data['configuration']
        self.sources = input_data['sources']
        self.file2compare = input_data['file2compare']
        self.write_options = input_data['write_options']
        self.test_name = input_data['test_name']
        self.plugin_name = input_data['plugin_name']
        self.test_description = input_data['test_description']
        self.output_filename = input_data['output_filename']
        self.overwrite_file2compare_str = input_data['overwrite_file2compare_str']
        self.cmp_voir = bool(input_data['cmp_voir'])
        self.cmp_fstcomp = bool(input_data['cmp_fstcomp'])
        self.erase_tmpdir = bool(input_data['erase_tmpdir'])

        self.output_file = os.path.join(
            os.environ['SPOOKI_TMPDIR'],
            self.plugin_name,
            self.output_filename
        )

        self.expanded_config = self.configuration.format(**self.__dict__)
        self.complete_config = os.path.expandvars(self.expanded_config)

        # here we should know that input_data was valid as far as
        # the criteria for being a correct test object
        # whether the paths exist should come after

    def run_test(self):
        self.command = [
            'echo',
            'spooki_run', self.complete_config,
            '--writeOptions', self.write_options,
        ]

        result = subprocess.run(self.command, stdout=subprocess.PIPE)

        fst_result = cmp_fst(self.output_file, self.file2compare)

        if fst_result.returncode != 0:
            self.report_fst_result(fst_result, self)
            raise SpookiTestFailedException()

        cmp_voir_result = cmp_voir(self.output_file, self.file2compare)

        if len(cmp_voir_result['different_lines']):
            self.report_cmp_voir_result(cmp_voir_result)
            raise SpookiTestFailedException()



    def report_fst_result(self, result):
        pass

    def report_cmp_voir_result(self, result):
        pass


def cmp_fst(file_a, file_b):
    fst_result = subprocess.run([
        'echo',
        'fstcomp', '-iment',
        '-A', file_a,
        '-B', file_b,
    ], stdout=subprocess.PIPE)
    return fst_result


def voir(file):
    result = subprocess.run([
        'echo',
        'voir\n',
        file
    ], stdout=subprocess.PIPE)

    result.stdout = result.stdout.decode('utf-8')
    return result



def cmp_voir(file_a, file_b):
    voir_a_result = voir(file_a)
    voir_b_result = voir(file_b)

    voir_a_filtered_output = filter_voir_output(voir_a_result.stdout)
    voir_b_filtered_output = filter_voir_output(voir_b_result.stdout)

    different_lines = compare_filtered_voir_outputs(voir_a_filtered_output, voir_b_filtered_output)

    return {
        'different_lines': different_lines,
    }


def crazy_regex_filtering(lines):
    # string perlCommand("
    # | egrep '^[ ]+[0-9]+[-][ ][A-Z0-9|\\*|\\!|\\^|\\>]+ '
    r1 = r'^[ ]+[0-9]+[-][ ][A-Z0-9|\*|\!|\^|\>]+ '
    re_1 = re.compile(r1)

    # | perl -pe 's/^[ ]+[0-9]+[-][ ](.*)/\\1/g'
    get_good_stuff_re = r's/^[ ]+[0-9]+[-][ ](.*)/\\1/g'
    re_2 = re.compile(get_good_stuff_re)
    # | sort >");

    def extract_good_stuff(line):
        m = re_2.match(line)
        if m:
            return m.group(0)

    good_stuff_lines = [re_2.match(l).group(0) for l in lines if re_1.match(l)]

    print(lines)
    return lines


def filter_voir_output(voir_output):
    lines = sorted(voir_output.split('\n'))
    filtered_lines = crazy_regex_filtering(lines)
    return filtered_lines


def compare_filtered_voir_outputs(output_a, output_b):
    different_lines = []
    for l_a, l_b in zip(['a','s','d','f'], output_b):
        if l_a != l_b:
            different_lines += (l_a, l_b)
    return different_lines


def main():
    from pprint import pprint
    os.environ['SPOOKI_TMPDIR'] = '/tmp/spooki_tmp/'
    s = SpookiTestCase(data)
    s.run_test()


if __name__ == "__main__":
    quit(main())

