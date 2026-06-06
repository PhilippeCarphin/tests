
deps: sleep1 sleep2 sleep3 sleep4
sleep1:
	sleep 1
	@echo "Done sleep 1"
sleep2:
	sleep 2
	@echo "Done sleep 2"
sleep3:
	sleep 3
	@echo "Done sleep 3"
sleep4:
	sleep 4
	@echo "Done sleep 4"

vars:
	@echo "target:$@"
	@echo "MAKEFLAGS=$(MAKEFLAGS)"

precise: deps
	@echo "target:$@"
	@echo "MAKEFLAGS=$(MAKEFLAGS)"
