#ifndef OPTIONS_H_
#define OPTIONS_H_

enum flag {
	FLAG_YELLOW = 4,
	FLAG_GREEN = 1,
	FLAG_RED = 2,
	FLAG_BLUE = 3
};

enum cmd {
	CMD_DO_A = 0,
	CMD_DO_B = 1,
};

struct my_options {
	int int_value;
	int arg2;
	char *string_arg;
	enum flag flag_value;
	enum cmd cmd_value;
};


int parse_opts(int argc, char * const * argv, struct my_options *opts);
int print_opts(struct my_options *opts);

#endif
