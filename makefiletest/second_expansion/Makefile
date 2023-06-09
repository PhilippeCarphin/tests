#
# This test demonstrates the evaluation order of makefiles and the effect of
# .SECONDEXPANSION:.
#
# First make parses the file and creates structures defining all the
# dependencies.
#
# After the whole file has been read, either the default target or the target(s)
# requested by the user is/are built.
#
# Variables are expanded when creating the dependencies so when make gets to
# parsing the 'three: $(deps)', it registers that 'three' depends on 'one' and
# that is set.
#
# The whole file gets parsed before the recipe for any target gets executed.
# So when building 'three', '$^' expands to 'the first dependency of the target
# which was set to be 'one' during the initial pass, but prints that the
# variable 'deps' is equal to 'two'.
#
# During the parsing phase, the dependency of four is set to the text '$(deps)'
# because the '$' is escaped using '$$'.  This means that ordinarily, 'four'
# would depend on a target or file whose name is "dollar-sign open paren deps
# close paren".
#
# Combined with .SECONDEXPANSION, the text "$(deps)" is treated as Makefile
# code and evaluated.  This evaluation however happens after the entire file
# has been parsed, at which point $(deps) evaluates to 'two'.
#

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
