#include <iostream>
#include "other.h"
#include <list>
#include <string>

int flag_from_string(const char *s, struct CommandOpts cmd_opts);
enum optimisation_level { FAST, SUPER_FAST, SIZE };

struct CommandOpts{
	std::string command;
	std::list<std::string> includes;
	std::string output_name;
	struct flags {
		bool flag1;
		bool flag2;
	} flags;
	optimisation_level opt_level;
};

int parse_opts(int argc, char **argv, struct CommandOpts *cmd_opts)
{
	cmd_opts->command = argv[0];
	for(int i = 1; i < argc; ++i){
		std::string arg = argv[i];
		std::string optarg = "";

		if( i < argc - 1){
			optarg = argv[i+1];
		}
		if(arg == "-I")
		{
			std::cout << "got flag -I with optarg = " << optarg << std::endl;
			cmd_opts->includes.push_back(optarg);
			++i;
		}
		if(arg == "-f" || arg == "-g")
			flag_from_string(argv[i], &cmd_opts);
	}
}

int flag_from_string(const char *s, struct CommandOpts cmd_opts)
{
	if(strcmp(s,"-f") == 0){
		cmd_opts->flags.flag_1 = true;
	} else if (strcmp(s, "-g")){
		cmd_opts->flags.flag_2 = true;
	}
	return 0;
}


int main(int argc, char **argv)
{
	// Print all the arguments
	for(int i = 0; i < argc ; ++i){
		std::cout << "argv["<<i<<"] = "<< argv[i] <<std::endl;
	}

	// Read the arguments into a structure
	struct CommandOpts cmd_opts;
	parse_opts(argc,argv, &cmd_opts);

	// Print the structure
	for(auto it = cmd_opts.includes.begin(); it != cmd_opts.includes.end(); ++it){
		std::cout << *it << std::endl;
	}
	std::cout << "opts->command = " << cmd_opts.command << std::endl;


	return 0;
}
