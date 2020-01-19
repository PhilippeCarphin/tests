import os
import subprocess
import json


def main():
    source_file('./sourced_file.sh')
    assert('SOURCED_FILE_VARIABLE' in os.environ)


def source_file(file_to_source):
    """ Updates the environment with the environment created by sourcing the file in bash """
    os.environ.update(env_after_source(file_to_source))


def env_after_source(file_to_source):
    """ Returns the environment after sourcing the file as a dictionnary """
    return env_after_command(f'source {file_to_source}')


def env_after_command(command):
    """ Returns the environment after the command as a dictionnary """
    json_dump_env_python_code = 'import os,json; print(json.dumps(dict(os.environ)))'
    json_dump_env_command = f'python3 -c "{json_dump_env_python_code}"'

    env_as_json_string = subprocess.run([
        'sh',
        '-c', f'{command} ; {json_dump_env_command}'
    ], stdout=subprocess.PIPE).stdout.decode('utf-8')

    return json.loads(env_as_json_string)


if __name__ == '__main__':
    quit(main())

