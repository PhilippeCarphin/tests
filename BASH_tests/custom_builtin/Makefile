BASH_DEV_DIR=$(shell repos -get-dir bash)/localinstall
INC := -I$(BASH_DEV_DIR)/include/bash/builtins \
       -I$(BASH_DEV_DIR)/include/bash/include \
       -I$(BASH_DEV_DIR)/include/bash \
       -I$(BASH_DEV_DIR)/lib/bash

tilde-expand.so: tilde-expand.c
	gcc $(INC) -shared -fPIC -o $@ $<

test:tilde-expand.so
	@bash -c "enable -f ./tilde-expand.so tilde_expand ;pushd /fs/ssm ; pushd /fs/site5 ; pushd /fs/site6 ;  tilde-expand '~-1'" 
	@echo "=================================================="
	@bash -c "enable -f ./tilde-expand.so tilde_expand ; tilde-expand --help || true;   tilde-expand x y z ASDF \"uvw xyz\" ; enable -d tilde-expand"
	@echo "=================================================="
	@bash -c "enable -f ./tilde-expand.so tilde_expand ; tilde-expand -h "
