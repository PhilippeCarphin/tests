import mocking

def cmp_fst(file_a, file_b):
    cmd = [
        'fstcomp', '-iment',
        '-A', file_a,
        '-B', file_b,
    ]
    # fst_result = subprocess.run(cmd, stdout=subprocess.PIPE)
    fst_result = mocking.mock_shell_command(cmd, f'STDOUT of {cmd}')

    return fst_result


