deps = one
all: three
one:
	@echo "building $@"
two:
	@echo "building $@"
three: $(deps)
	@echo "buiding $@"
	@echo "    when the dependency for the rule was evaluated, deps was equal to '$^'"
	@echo "    in the rule: deps = '$(deps)'"
.SECONDEXPANSION:
four: $$(deps)
	@echo "buiding $@"
	@echo "    when the dependency for the rule was evaluated, deps was equal to '$^'"
	@echo "    in the rule: deps = '$(deps)'"

deps = two
