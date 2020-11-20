import re

class PysedError(Exception):
    pass

def pysed(sed_expr, sed_input):
    if isinstance(sed_input, str):
        sed_input = sed_input.splitlines()
        return '\n'.join(pysed_gen(sed_expr, sed_input))
    elif isinstance(sed_input, list):
        return list(pysed_gen(sed_expr, sed_input))
    else:
        return pysed_gen(sed_expr, sed_input)

def pysed_gen(sed_expr, line_list):
    sed_single_line = parse_sed_expr(sed_expr)
    yield from map(sed_single_line, line_list)

def parse_sed_expr(sed_expr):
    tokens = re.split(r'(?<!\\)/', sed_expr)
    if len(tokens) < 4:
        raise PysedError("Invalid expression must be 's/expr/string/[x]'")
    if tokens[0] != 's':
        raise PysedError(f"First token in sed_expr must be 's', got '{tokens[0]}'")
    in_re = re.compile(tokens[1])
    substitution=tokens[2]
    last_part = tokens[3] if tokens[3] != '' else None
    return get_mapping(in_re, substitution, last_part)

def get_mapping(in_re, substitution, last_part):
    if last_part:
        if last_part == 'g':
            count = 0
        elif last_part.isnumeric():
            count = int(last_part)
            return lambda l: replace_nth_match(in_re, substitution, l, count-1)
        else:
            raise PysedError("Don't know what to do with last_part='{last_part}'")
    else:
        count = 1
    return lambda l: in_re.sub(substitution, l, count=count)

def nth_value(generator, n):
    """ Advance the generator to the nth element and return it """
    for i, v in enumerate(generator):
        if i == n:
            return v

def all_matches(pattern, string):
    """ Generator of all match objects obtained by using a scanner """
    scan = pattern.scanner(string)
    while True:
        match = scan.search()
        if match:
            yield match
        else:
            raise StopIteration

def get_nth_match(pattern, string, n):
    """ Get a match object for the nth match of pattern in string """
    return nth_value(all_matches(pattern, string), n)

def replace_nth_match(pattern, substitution, string, n):
    """ Replace the nth match of pattern in string with m.expand(substitution)
    where m is the nth match object """
    m = get_nth_match(pattern, string, n)
    if m:
        return f'{string[:m.start()]}{m.expand(substitution)}{string[m.end():]}'
    else:
        return string

import subprocess
def compare_with_shell_sed(sed_expr, string):
    expected = get_shell_sed_result(sed_expr, string)
    compare = pysed(sed_expr, s)
    return compare == expected

def get_shell_sed_result(sed_expr, string):
    modded_expr = sed_expr.replace('(',r'\(').replace(')', r'\)').replace('+',r'\+')
    result = subprocess.run(f'echo {string} | sed \'{modded_expr}\'', shell=True,
            universal_newlines=True, stdout=subprocess.PIPE, check=True)
    return result.stdout.strip('\n')


if __name__ == '__main__':
    import unittest
    class TestPysed(unittest.TestCase):
        def test_unhandled_cases(self):
            s = 'aaaaaaaaaaa'
            self.assertRaises(PysedError, parse_sed_expr, 'Y/asdf/zxcv/')
            self.assertRaises(PysedError, parse_sed_expr, 's/asdf/zxcv/v')
        def test_wront_number_elements(self):
            s = 'aaaaaaaaaaa'
            self.assertRaises(PysedError, parse_sed_expr, '/asdf/zxcv/')
            self.assertRaises(PysedError, parse_sed_expr, '/asdf/')
            self.assertRaises(PysedError, parse_sed_expr, '//')
            self.assertRaises(PysedError, parse_sed_expr, 's/asdf/bcde')
        def test_valid_expr(self):
            parse_sed_expr('s/asdf/zxcv/3')
            parse_sed_expr('s/asdf/zxcv/g')
            parse_sed_expr('s/asdf/zxcv/')
            parse_sed_expr('s/asdf//')
        def run_test_case(self, sed_expr, string, expected):
            result = pysed(sed_expr, string)
            self.assertEqual(result, expected)
            self.run_shell_test_case(sed_expr, string)
        def run_shell_test_case(self, sed_expr, string):
            self.assertEqual(
                    pysed(sed_expr, string),
                    get_shell_sed_result(sed_expr, string))
        def test_simple(self):
            self.run_test_case(
                sed_expr=r's/cd*/YY/',
                string='abxxcddddeasdfabxxcddeasd',
                expected='abxxYYeasdfabxxcddeasd')
        def test_group(self):
            self.run_test_case(
                sed_expr=r's/ab(x*)(cd*e)(asd)/=\1-\2-\3=/',
                string='abxxcddddeasdf',
                expected='=xx-cdddde-asd=f')
        def test_g(self):
            self.run_test_case(
                sed_expr=r's/pysed/PYSED/g',
                string='pysed pysed pysed pysed',
                expected='PYSED PYSED PYSED PYSED')
        def test_no_g(self):
            self.run_test_case(
                sed_expr=r's/pysed/PYSED/',
                string='pysed pysed pysed pysed',
                expected='PYSED pysed pysed pysed')
        def test_empty_replacement(self):
            self.run_test_case(
                sed_expr=r's/yse//',
                string='pysed pysed pysed pysed',
                expected='pd pysed pysed pysed'
            )
        def test_replace_nth_match(self):
            self.run_test_case(
                sed_expr=r's/pysed/PYSED/3',
                string='pysed pysed pysed pysed',
                expected='pysed pysed PYSED pysed')
            self.run_test_case(
                sed_expr=r's/pysed/PYSED/8',
                string='pysed pysed pysed pysed',
                expected='pysed pysed pysed pysed')
    unittest.main()
