import os
import re
import subprocess
import copy
import mocking
from pyfstcomp import cmp_fst
from pyvoir import cmp_voir

class SpookiTestFailedException(Exception):
    pass


data = {
    'configuration': "([ReaderStd --input $SPOOKI_DIR/{sources[0]}] >> [Select --fieldName TT]) + ([ReaderStd --input $SPOOKI_DIR/{sources[1]}] >> [Select --fieldName ES]) >> [InterpolationHorizontalGrid -m FIELD_DEFINED --fieldName ES --interpolationType BI-CUBIC --extrapolationType NEAREST] >> [WriterStd --output {output_file} --ignoreExtended --IP1EncodingStyle OLDSTYLE]",
    'sources': [
        "2015072100_240_TTESUUVV_YinYang.std",
        "2015072100_240_TTESUUVV_GridZ.std"
    ],
    'test_name': '"InterpHorizGridUtoZ_rmn19_file2cmp.std"',
    'test_description': 'This test verifies this type of grid',
    'cmp_voir': True,
    'cmp_fstcomp': True,
    'erase_tmpdir': True,
    'overwrite_file2_compare': True,
}

def make_destination_path(test_data):
    return f'{os.environ["SPOOKI_TMPDIR"]}/{test_data["plugin_name"]}/result_{test_data["test_name"]}'

class SpookiTestCaseError(Exception):
    pass


def main():
    from pprint import pprint
    os.environ['SPOOKI_DIR'] = '/home/spst900/spooki/spooki_dir_ppp4/'
    os.environ['SPOOKI_TMPDIR'] = '/tmp/spooki_tmp/'
    s = SpookiTestCase(data)
    s.run_test()


plugin_name = "AbsoluteValue"
test_run = 'spooki_test_output_82xb7s'  # Genre le mktemp()

class SpookiTestCase:
    def __init__(self, input_data):
        self.configuration = input_data['configuration']
        self.sources = input_data['sources']
        self.test_name = input_data['test_name']

        # SPOOKI_TMPDIR and TMPDIR must be existing directories TODO
        # TMPDIR must exist TODO
        self.output_dir = os.path.join(
            os.environ['SPOOKI_TMPDIR'],
            test_run,
            plugin_name,
            self.test_name
        )

        self.test_description = input_data['test_description']
        self.cmp_fstcomp = input_data['cmp_fstcomp']
        self.cmp_voir = input_data['cmp_voir']
        self.erase_tmpdir = input_data['erase_tmpdir']

    def run_test(self):

        self.output_file = os.path.join(self.output_dir, f'result_{self.test_name}')

        self.expected_output_file = os.path.join(self.output_dir, f'expected_result_{self.test_name}')

        self.expanded_config = self.configuration.format(**self.__dict__)
        self.complete_config = os.path.expandvars(self.expanded_config)
        self.command = ['spooki_run', self.complete_config]

        result = mocking.mock_shell_command(self.command, f'STDOUT of {self.configuration}')
        # result = subprocess.run(self.command, stdout=subprocess.PIPE)

        # std::string file2compare_link = create_test_file_link();
        # BOOST_LOG_INFO << "" << file2compare_link << " -> " << this->file2compare_path;
        # TODO And replace the filenames with the links in what follows

        if self.cmp_fstcomp:
            fst_result = cmp_fst(self.output_file, self.expected_output_file)
            if fst_result.returncode != 0:
                self.report_fst_result(fst_result, self)
                raise SpookiTestFailedException('fstcomp', fst_result.returncode)

        if self.cmp_voir:
            cmp_voir_result = cmp_voir(self.output_file, self.expected_output_file)
            if len(cmp_voir_result['different_lines']):
                self.report_cmp_voir_result(cmp_voir_result)
                raise SpookiTestFailedException('fstcomp', cmp_voir_result.returncode)

        if self.erase_tmpdir:
            mocking.mock_shell_command(['rm', 'f', self.output_file], '')
            pass


    def cleanup(self):
        pass

    def report_fst_result(self, result):
        pass

    def report_cmp_voir_result(self, result):
        pass


if __name__ == "__main__":
    quit(main())

