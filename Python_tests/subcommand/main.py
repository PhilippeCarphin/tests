import argparse

def commit_function(args):
    print(f'commit : args = {args}')

def rebase_function(args):
    print(f'rebase : args = {args}')

def get_parser():
    p = argparse.ArgumentParser()
    subparsers = p.add_subparsers()
    commit = subparsers.add_parser('commit')
    commit.add_argument('--no-edit', action='store_true')
    commit.add_argument('--amend', action='store_true')
    commit.set_defaults(func=commit_function)

    rebase = subparsers.add_parser('rebase')
    rebase.add_argument('--interactive', action='store_true')
    rebase.add_argument('--continue', action='store_true')
    rebase.set_defaults(func=rebase_function)
    p.add_argument('--verbose', action='store_true')
    p.add_argument('--version', action='store_true')

    return p

def test():
    argvv = [
        ['commit', '--no-edit'],
        ['rebase', '--interactive'],
        ['--verbose', 'commit', '--amend'],
        # ['commit', '--interactive']  # ERROR Unknown arg for commit will be rejected by argparse
    ]

    def run_with_args(args):
        args = p.parse_args(args)
        args.func(args)

    p = get_parser()
    for argv in argvv:
        run_with_args(argv)
    print('======= help ========')
    p.print_help()
    print('======= help commit ========')
    p.parse_args(['commit', '--help'])
    # p.choices.get('commit').print_help()


test()