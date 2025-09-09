import comptest
import os
import logging

fmt="[{levelname} - {funcName}] {message}"
logging.basicConfig( format=fmt, style='{',
    level=(logging.DEBUG if os.environ['DEBUG_TESTS'] else logging.INFO)
)

this_dir = os.path.dirname(__file__)

c = comptest.CompletionRunner(
    init_commands=[
        "source /usr/share/bash-completion/bash_completion",
        "source /home/phc001/Repositories/github.com/philippecarphin/utils/etc/profile.d/git-colon-path-support.bash",
        "complete -F _gcps_complete_cd cd",
    ]
)

result = set(c.get_completion_candidates("cd :/"))

expected = set(['.git', 'ASM_tests', 'AppleScript_tests', 'Autotools_tests', 'BASH_tests', 'CMakeTests', 'CPP_tests', 'CS_tests', 'C_tests', 'Clojure_tests', 'Elisp_tests', 'Fortran_tests', 'GNU_stow_tests', 'Go_tests', 'Haskell_test', 'JS_tests', 'Java_tests', 'LaTeX_tests', 'Meson_tests', 'NodeJS_tests', 'OpenMP_tests', 'Python_tests', 'Raku_tests', 'Rust_tests', 'Swift_tests', 'TCL_tests', 'TMUX_tests', 'Xcode', 'Yacc_tests', 'd3_tests', 'git_demo', 'git_tests', 'lang_compare', 'lisp_tests', 'make_tests', 'makefiletest', 'misc', 'notes', 'perl_test', 'rmtest'])

if result == expected:
    print("SUCCESS")
else:
    print("FAIL")
    print(result - expected)

if c.expect_single_candidate("cd :/make_tests/", "makefile_eval_order", timeout=2):
    print("SUCCESS")
else:
    print("FAIL")

if c.expect_single_candidate("ls :/make_tests/makefile_eval_order/vari", "ables/ ", timeout=2):
    print("SUCCESS")
else:
    print("FAIL")
