import os
import sys
import io
import re

"""
Environment is a dictionnary mapping strings to ordinary strings
"""

new_environment = {
        "PYSOURCE_NEW": "Charlene",
        "PYSOURCE_HELLO" : "PYSOURCE_HELLO VALUE",
        "BASH_FUNC": """{
        }
         
        aasf
        asfdasf"

        if f\"ifdkfsdf
        """
        }

def escspc(v):
    # return re.sub(r'(?<!\\)"', r'\"', v)
    return re.sub(r"(?<!\\)'", r"\'", v)

def export(env):
    if env:
        out = io.StringIO()
        # out.write('export ')
        # out.write(' '.join(f'{key}="{escspc(value)}"' for key, value in env.items()))
        # out.write('\n'.join(f'declare -x {key}="{escspc(value)}"' for key, value in env.items()))
        out.write('\n'.join(f"declare -x {key}='{escspc(value)}'" for key, value in env.items()))
        sys.stdout.write(out.getvalue())

export(new_environment)
# print(sys.argv)
