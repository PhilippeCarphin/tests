import os
import sys
import io
import re

"""
This demonstrates escaping string values for BASH parsing.

The demonstration uses a dictionnary.  We want to produce
BASH code that will cause set environment variables to
EXACTLY the values inside the string.  I.E. If the string
contains backslashes, the value of the environment will have
exactly the same backslashes etc.

We print lines like: f'{var}="{esc(value)}"\n' for var, value
in new_environment.items().

We first replace all backslash chars by two backslash chars.
we subsequently replace all '"' by r'\"'
"""

new_environment = {
        "PYSOURCE_NEW": "Charlene",
        "PYSOURCE_HELLO" : "PYSOURCE_HELLO VALUE",
        "BASH_FUNC": r"""{}

        odd  : \\\"\n$USER
        even : \\\\"
        asfdasf"
        some_quotes : ""

        if f\"\"\"ifdkfsdf
        """,
        "Q3bs1q" : r'\\\"',
        "SQ4bs1sq": r"\\\\"
        }


def esc_quote(v):
    return re.sub('\$', r'\$', re.sub('"', r'\"', re.sub(r'\\', r'\\\\', v)))

def esc_single_quote(v):
    return re.sub(r"'", r"\'", v)

def export_env_with_extra_escaping(env, shell='bash'):
    out = io.StringIO()
    if shell == "bash":
        out.write(''.join(f'declare -x {key}="{esc_quote(value)}"\n' for key, value in env.items()))
    else:
        out.write(''.join(f'set -x {key} "{esc_quote(value)}"\n' for key, value in env.items()))
    # out.write(''.join(f"declare -x {key}='{esc_single_quote(value)}'\n" for key, value in env.items()))
    return out.getvalue()

def export(env):
    if env:
        out = io.StringIO()
        out.write(''.join(f'declare -x {key}="{value}"\n' for key, value in env.items()))
        return out.getvalue()
    else:
        return None

if __name__ == "__main__":
    sys.stdout.write(export_env_with_extra_escaping(new_environment))
    # print(sys.argv)
