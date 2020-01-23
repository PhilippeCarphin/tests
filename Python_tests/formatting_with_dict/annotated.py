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

        # inline RunConfigTestCaseFixture::RunConfigTestCaseFixture(){
        #     this->set_spooki_tmp_dir();
        # }

        # inline void RunConfigTestCaseFixture::set_spooki_tmp_dir(){
        #     if (pst::spooki_utility::existEnvironmentVariable("TMPDIR")) {
        #         this->tmp_dir = pst::spooki_utility::getEnvironmentVariable("TMPDIR");
        #         if (not boost::filesystem::exists(NORMALIZE_FILENAME(this->tmp_dir))) {
        #             BOOST_LOG_ERROR( "Le repertoire specifie par TMPDIR " + this->tmp_dir + "n'existe plus! Vous devez le recreer ou bien ouvrir une nouvelle session!");
        #             throw;
        #         }
        #     }

        #     this->spooki_tmp_dir = "/tmp";
        #     if (pst::spooki_utility::existEnvironmentVariable("SPOOKI_TMPDIR")) {
        #         this->spooki_tmp_dir = pst::spooki_utility::getEnvironmentVariable("SPOOKI_TMPDIR");
        #     }

        #     if (not boost::filesystem::exists(boost::filesystem::system_complete( boost::filesystem::path(this->spooki_tmp_dir)))) {
        #         BOOST_LOG_ERROR("$SPOOKI_TMPDIR POINTS TO " + this->spooki_tmp_dir + " AND IT'S NOT A VALID PATH!");
        #         throw;
        #     }
        #     if (not pst::spooki_utility::isWritablePath(this->spooki_tmp_dir)) {
        #         BOOST_LOG_ERROR("CANNOT WRITE TO " + this->spooki_tmp_dir + " -- NO WRITE PERMISSION --");
        #         throw;
        #     }
        # }
        # Envorionment must have TMPDIR : CHECK : exception will be thrown
        # Environment must have SPOOKI_TMPDIR : CHECK : excepton will be thrown
        # SPOOKI_TMPDIR and TMPDIR must be existing directories TODO
        # TMPDIR must exist TODO
        self.output_dir = os.path.join(
            os.environ['SPOOKI_TMPDIR'],
            test_run,
            plugin_name,
            self.test_name
        )

        # FROM THE BODY OF A TEST

        # set_test_description("Test #7 :  Interpolation d'un champ scalaire (TT) d'une grille U vers une grille Z");
        self.test_description = input_data['test_description']
        # set_plugin_name("InterpolationHorizontalGrid");
        # CHECK : plugin_name global variable

        # set_test_name("PhilNewTest");
        # CHECK: got from input data at the top

        # std::string ordenv_truehost = pst::spooki_utility::getEnvironmentVariable("ORDENV_TRUEHOST");
        # if(ordenv_truehost == "eccc-ppp1" || ordenv_truehost == "eccc-ppp2") {
        # set_file2compare(OVERWRITE_FILE2COMPARE, "", "InterpHorizGridUtoZ_ppp1ppp2_file2cmp.std");
        # } else {
        # set_file2compare(OVERWRITE_FILE2COMPARE, "", "InterpHorizGridUtoZ_rmn19_file2cmp.std");
        # }
        # CHECK: Got from input_data at the top

        # add_source("2015072100_240_TTESUUVV_YinYang.std");
        # add_source("2015072100_240_TTESUUVV_GridZ.std");
        # CHECK: Got from input_data at the top

        # configuration = "([ReaderStd --input " + source_data[0].source_path + "] >> "
        # "[Select --fieldName TT]) + "
        # "([ReaderStd --input " + source_data[1].source_path + "] >> "
        # "[Select --fieldName ES]) >> "
        # "[InterpolationHorizontalGrid -m FIELD_DEFINED --fieldName ES "
        # "                             --interpolationType BI-CUBIC --extrapolationType NEAREST] >> "
        # "[WriterStd --output " + destination_path + " " + write_options +"]" + overwrite_file2compare_str;
        # CHECK: Got from input_data at the top

        # cmp_fst_comp = true;
        # cmp_voir = true;
        # erase_tmpdir = false;
        self.cmp_fstcomp = input_data['cmp_fstcomp']
        self.cmp_voir = input_data['cmp_voir']
        self.erase_tmpdir = input_data['erase_tmpdir']

    def run_test(self):

        self.output_file = os.path.join(self.output_dir, f'result_{self.test_name}')

        self.expected_output_file = os.path.join(self.output_dir, f'expected_result_{self.test_name}')

        self.expanded_config = self.configuration.format(**self.__dict__)
        self.complete_config = os.path.expandvars(self.expanded_config)
        self.command = ['spooki_run', self.complete_config]

        # std::shared_ptr<pst::OperationBase> op = pst::meteo_operations::evaluateConfig(this->configuration);
        # runOp(op);
        result = mocking.mock_shell_command(self.command, f'STDOUT of {self.configuration}')
        # result = subprocess.run(self.command, stdout=subprocess.PIPE)

        # std::string file2compare_link = create_test_file_link();
        # BOOST_LOG_INFO << "" << file2compare_link << " -> " << this->file2compare_path;
        # TODO And replace the filenames with the links in what follows

        # if(this->cmp_voir){
        #     this->fixture_assert(pst::spooki_utility::compareVoir(this->destination_path, file2compare_link));
        # }
        if self.cmp_fstcomp:
            fst_result = cmp_fst(self.output_file, self.expected_output_file)
            if fst_result.returncode != 0:
                self.report_fst_result(fst_result, self)
                raise SpookiTestFailedException('fstcomp', fst_result.returncode)

        # if(this->cmp_fst_comp) {
        #     this->fixture_assert(pst::spooki_utility::compareStdFilesWithFstComp(this->destination_path, file2compare_link));
        # }
        if self.cmp_voir:
            cmp_voir_result = cmp_voir(self.output_file, self.expected_output_file)
            if len(cmp_voir_result['different_lines']):
                self.report_cmp_voir_result(cmp_voir_result)
                raise SpookiTestFailedException('fstcomp', cmp_voir_result.returncode)

        # if(this->erase_tmpdir) {
        #     this->do_erase_tmp_dir();
        # }
        # TODO
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

