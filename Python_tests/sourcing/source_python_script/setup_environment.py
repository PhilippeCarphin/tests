import bash_escape
import io
import os
import sys

output = io.StringIO("# Code to change bash environment\n")

function_code = """
some_function(){
    s="$(python3 setup_environment.py 2>/dev/null)"
    echo '----------------------------------------------------------------'
    echo "$s"
    echo '----------------------------------------------------------------'
    eval "$s"
    echo $PY_NEW_ENVVAR
}
"""

new_path_l = list(sorted(set(os.environ['PATH'].split(':'))))
# sys.stderr.write(str(new_path_l))

env = {
        "PY_NEW_ENVVAR": 'New "environment variable"',
        "PY_SOURCE": __file__,
        "PATH": ':'.join(new_path_l)
}


output.write(bash_escape.export_env_with_extra_escaping(env, shell='fish'))
# output.write(function_code)
sys.stdout.write(output.getvalue())
# sys.stderr.write(output.getvalue())

