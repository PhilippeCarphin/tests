
import os
import pexpect
import logging
import argparse

def get_args():
    p = argparse.ArgumentParser()
    p.add_argument("-f", nargs='*')
    p.add_argument("-d")
    p.add_argument("cmd")
    p.add_argument("--debug", action='store_true')
    return p.parse_args()

def main():
    args = get_args()
    fmt="[{levelname} - {funcName}] {message}"
    logging.basicConfig( format=fmt, style='{',
        level=(logging.DEBUG if args.debug else logging.INFO)
    )
    comp = CompletionRunner(init_files=args.f, directory=args.d)
    results = comp.get_completion_candidates(args.cmd, timeout=1)
    print(results)

class CompletionRunner:
    def __init__(self, directory=None, init_files=None, init_commands=None):
        self.PS1 = "/@"
        env = os.environ.copy()
        env['PS1']=self.PS1
        env['TERM']='dumb'
        self.bash = pexpect.spawn(
            "bash --norc",
            cwd=(os.path.realpath(directory) if directory else os.getcwd()),
            encoding='utf-8',
            env=env,
            dimensions=(24,240)
        )
        if init_files:
            # To load bash_completion and the completion definitions for
            # the command we want to test.
            for f in init_files:
                self.run_command(f"source {f}")
        self._setup_readline()

    def _setup_readline(self):
        # Pagin could prevent us from getting a PS1 after hitting TAB
        self.run_command('bind "set page-completions off"')
        # Don't query when there are lots of completions
        self.run_command('bind "set completion-query-items -1"')
        # Print each completion on its own line
        self.run_command('bind "set completion-display-width 0"')
        # Press TAB once to see all completions
        self.run_command('bind "set show-all-if-ambiguous"')
        # Prevent output from getting polluted with Bell (\a) or ANSI color codes
        self.run_command('bind "set bell-style none"')
        self.run_command('bind "set colored-completion-prefix off"')
        self.run_command('bind "set colored-stats off"')

    def run_command(self, cmd, nl_after_command=False, nl_before_ps1=True):
        logging.debug(f"{cmd}")
        self.bash.sendline(cmd)
        self.bash.expect_exact(cmd + ('\r\n' if nl_after_command else ''))
        self.bash.expect_exact(('\r\n' if nl_before_ps1 else '') + self.PS1)
        logging.debug(f"Found ps1 after command '{cmd}'")
        return self.bash.before

    def get_completion_candidates(self, cmd, timeout=None):
        # NOTE: bash-completion do something with 'MAGIC_MARK' which seems
        # to be some token that is super unlikely to arise in the ouput of
        # a command.
        logging.debug(f"Getting candidates for command {cmd}")
        self.bash.send(cmd + "\t")
        self.bash.expect_exact(cmd)
        try:
            self.bash.expect_exact(self.PS1, timeout=timeout)
        except pexpect.exceptions.TIMEOUT as t:
            logging.debug(f"Timeout reached")
        result = self.bash.before.strip().splitlines()
        self.bash.sendintr()
        self.bash.expect_exact(self.PS1)
        return result

if __name__ == "__main__":
    main()
