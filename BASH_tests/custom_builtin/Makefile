BASH_DEV_DIR=$(shell repos -get-dir bash)/localinstall
INC := -I$(BASH_DEV_DIR)/include/bash/builtins \
       -I$(BASH_DEV_DIR)/include/bash/include \
       -I$(BASH_DEV_DIR)/include/bash \
       -I$(BASH_DEV_DIR)/lib/bash

shell-split.so: shell_split.c
	gcc $(INC) -shared -fPIC -o $@ $<

tilde-expand.so: tilde-expand.c
	gcc $(INC) -shared -fPIC -o $@ $<

t: shell-split.so
	@bash -c "enable -f ./shell-split.so shell_split ; shell-split 'a_command arg \"arg containing ;\" ; a_command \";\" ; echo \"a semicolon is ;.\" ; echo \;'"

test:tilde-expand.so
	@bash -c "enable -f ./tilde-expand.so tilde_expand ;pushd /fs/ssm ; pushd /fs/site5 ; pushd /fs/site6 ;  tilde-expand '~-1'" 
	@echo "=================================================="
	@bash -c "enable -f ./tilde-expand.so tilde_expand ; tilde-expand --help || true;   tilde-expand x y z ASDF \"uvw xyz\" ; enable -d tilde-expand"
	@echo "=================================================="
	@bash -c "enable -f ./tilde-expand.so tilde_expand ; tilde-expand -h "

inc: compile_commands.json
compile_commands.json: Makefile
	@echo '[' > $@
	@echo '    { "directory": "$(PWD)", "command": "gcc $(INC) tilde-expand.c", "file": "$(PWD)/tilde-expand.c", "output": "$(PWD)/tilde-expand.so"},' >> $@
	@echo '    { "directory": "$(PWD)", "command": "gcc $(INC) shell_split.c", "file": "$(PWD)/shell_split.c", "output": "$(PWD)/shell-split.so"}' >> $@
	@echo ']' >> $@
