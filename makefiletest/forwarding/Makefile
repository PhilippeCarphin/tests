
default: delegate-precise-subshell
vars:
	$(MAKE) -C subdir
delegate:
	$(MAKE) -C subdir

delegate-precise:
	$(MAKE) -C subdir precise

delegate-precise-subshell:
	(cd subdir && $(MAKE) precise)

.PHONY: delegate-precise-phony
delegate-precise-phony:
	$(MAKE) -C subdir precise
