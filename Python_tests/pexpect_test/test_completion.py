#!/usr/bin/env python3

import pexpect
import pexpect.replwrap
import os

#
# Create pexpect.spawn
# - We need to tightly control what is output so we use --norc because we don't
#   want any output from our startup files
# - We wait for a PS1 to appear and once we have it, our shell is ready.
#
PS1 = "/@"
env = os.environ.copy()
env['PS1']=PS1
env['TERM']='dumb'
bash = pexpect.spawn("bash --norc", encoding='utf-8', env=env, dimensions=(24,240))
bash.expect_exact(PS1)

def run_command(p, cmd, newline_after_command=False, newline_before_ps1=True):
    p.sendline(cmd)
    # Because of echoing of characters, we will get the command
    # If command produces no output, the empty output of the command will not
    # there will only be one '\r\n' between the echoed command so if we did
    # p.expect_exact(cmd+'\r\n'), then we would strip the '\r\n' from the
    # beginning of the output of commands that produce output but then we
    # would expect '\r\n\r\n' from commands that produce no output and we
    # would hang.
    p.expect_exact(cmd + ('\r\n' if newline_after_command else ''))
    # Then the output of the command, followed by PS1
    p.expect_exact(('\r\n' if newline_before_ps1 else '') + PS1)
    print(f"Found ps1 after command '{cmd}'")
    # The text between the echoed cmd and PS1 is the output of our command
    return p.before

def print_run_command(p, cmd):
    print(f"{cmd} -> {run_command(p, cmd).encode('ASCII')}")

#
# Prepare the shell
# - bash-completion has a bashrc that they load and an inputrc.  Since
#   the completion file doesn't use anything from bash-completion like
#   _init_completion, we don't need to load it and for the inputrc, we
#   can just run commands here to set readline options that will make
#   give us the best output.
#   bash-completion uses their inputrc by setting the environment variable
#   INPUTRC in their env before starting BASH and they use their 'bashrc'
#   by starting BASH with '--norc' and sourcing their bashrc explicitly.
#
this_dir = os.path.dirname(__file__)
comp_file = os.path.normpath(f"{this_dir}/../../BASH_tests/completion/custom_auto_complete.sh")
print_run_command(bash, f"source {comp_file}")
# Pagin could prevent us from getting a PS1 after hitting TAB
run_command(bash, 'bind "set page-completions off"')
# Don't query when there are lots of completions
run_command(bash, 'bind "completion-query-items -1"')
# Print each completion on its own line
run_command(bash, 'bind "set completion-display-width 0"')
# Press TAB once to see all completions
run_command(bash, 'bind "set show-all-if-ambiguous"')
# Prevent output from getting polluted with Bell (\a) or ANSI color codes
run_command(bash, 'bind "set bell-style none"')
run_command(bash, 'bind "set colored-completion-prefix off"')
run_command(bash, 'bind "set colored-stats off"')

def get_completion_candidates(p, cmd, timeout=None):
    p.send(cmd + "\t")
    p.expect_exact(cmd)
    try:
        p.expect_exact(PS1, timeout=timeout)
    except pexpect.exceptions.TIMEOUT as t:
        print("Timeout reached")
    result = p.before.strip().splitlines()
    # We need to cancel the current command otherwise our next call to this
    # function will still be completing the arguments from the first call since
    # we never sent a newline, the first call will put 'to_complete ', then
    # the following one will just add to that: 'to_complete to_complete a'
    # etc until we get 'to_complete to_complete a... one ' and bash will
    # still run the completion for to_complete.
    p.sendintr()
    p.expect_exact(PS1)
    print(f"INTR: {p.before}")
    return result

def show_completion_candidates(p, cmd, timeout=None):
    result = get_completion_candidates(p, cmd, timeout=timeout)
    print(f"Candidates for '{cmd}': {result}")

show_completion_candidates(bash, "to_complete ")
show_completion_candidates(bash, "to_complete a")
show_completion_candidates(bash, "to_complete b", timeout=1)
show_completion_candidates(bash, "to_complete c", timeout=1)

show_completion_candidates(bash, "one ", timeout=1)
show_completion_candidates(bash, "one a", timeout=1)
show_completion_candidates(bash, "one p", timeout=1)

bash.kill(1)
