import mocking
import re

def voir(file):
    shell_command = [
        'voir',
        file
    ]
    result = mocking.mock_shell_command(shell_command, f'STDOUT of {shell_command}')
    # result = subprocess.run(shell_command, stdout=subprocess.PIPE)
    return result


def cmp_voir(file_a, file_b):
    voir_a_result = voir(file_a)
    voir_b_result = voir(file_b)

    voir_a_filtered_output = filter_voir_output(voir_a_result.stdout.decode('utf-8'))
    voir_b_filtered_output = filter_voir_output(voir_b_result.stdout.decode('utf-8'))

    different_lines = compare_filtered_voir_outputs(voir_a_filtered_output, voir_b_filtered_output)

    return {
        'different_lines': different_lines,
    }


def crazy_regex_filtering(lines):
    # from verification_utilities.cpp string perlCommand("
    # | egrep '^[ ]+[0-9]+[-][ ][A-Z0-9|\\*|\\!|\\^|\\>]+ '
    # | perl -pe 's/^[ ]+[0-9]+[-][ ](.*)/\\1/g'
    # | sort >");
    filter_re = re.compile(r'^[ ]+[0-9]+[-][ ][A-Z0-9*!|^>]+ ')
    select_re = re.compile(r'[ ]+[0-9]+[-][ ](.*)')

    new_lines = [select_re.match(l).group(0) for l in lines if filter_re.match(l)]

    return sorted(new_lines)


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
