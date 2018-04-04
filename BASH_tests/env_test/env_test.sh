PATH=/usr/bin/
PHIL="phil's shell variable"
export PHIL_ENV="phil's environment variable"

python env_test.py
echo $(echo 'In a subshell PHIL=$PHIL')
