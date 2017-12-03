#include <iostream>
#include "other.h"

namespace other {

static int internal_global_variable = 123;

void set_other_var(int i)
{
	internal_global_variable = i;
}

int get_other_var()
{
	return internal_global_variable;
}

// Other functions of the module

}
