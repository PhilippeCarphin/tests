#include <iostream>
#include "other.h"
#include <list>
#include <string>
#include <string.h>

int print_usage(){
	std::cout << "Usage : philcc cmd [options]\n"
			<< "	cmd\n"
			<< "		compile : description\n"
			<< "		link : description\n"
			<< "		do_c : description\n"
			<< "	options\n"
			<< "		-I dir : add dir to the list of paths to search for includes"
			<< "		--flag-1 : if this is set bla bla\n"
			<< "		--flag-2 : bla bla" << std::endl;
}


enum optimisation_level { FAST, SUPER_FAST, SIZE };
enum CMD { COMPILE, LINK, DO_C};

struct Command{
	const char *name;
	enum CMD cmd;
};
static std::list<struct Command> cmd_lookup{
	{ .name = "compile", .cmd = COMPILE},
	{ .name = "link",    .cmd = LINK},
	{ .name = "do_c",    .cmd = DO_C}
};

struct CommandOpts{
	struct Command command;
	std::list<std::string> includes;
	std::string output_name;
	struct flags {
		bool flag_1;
		bool flag_2;
	} flags;
	optimisation_level opt_level;
};

static int compile_cmd(struct CommandOpts * cmd_opts)
{
	std::cout << "Running " <<  __FUNCTION__ << "()" << std::endl;
	return 0;
}
static int link_cmd(struct CommandOpts * cmd_opts)
{
	std::cout << "Running " <<  __FUNCTION__ << "()" << std::endl;
	return 0;
}
static int do_c_cmd(struct CommandOpts * cmd_opts)
{
	std::cout << "Running " <<  __FUNCTION__ << "()" << std::endl;
	return 0;
}



int flag_from_string(const char *s, struct CommandOpts *cmd_opts);

int parse_command(const char *command, struct CommandOpts *cmd_opts)
{
	for(auto it = cmd_lookup.begin(); it != cmd_lookup.end(); ++it){
		if( (*it).name == std::string(command)){
			cmd_opts->command = *it;
			return 0;
		}
	}
	std::cout << "ERROR Command " << command << " invalid" << std::endl;
	print_usage();
	exit(1);
}
int parse_options(int argc, char **argv, struct CommandOpts *cmd_opts)
{
	for(int i = 2; i < argc; ++i){
		std::string option = argv[i];
		std::string optarg = (i < argc-1 ? argv[i+1] : "");

		if(option == "-I")
		{
			if(cmd_opts->command.cmd != COMPILE){
				std::cout << "Error : -I is only when compiling" << std::endl;
				print_usage();
				exit(1);
			}
			cmd_opts->includes.push_back(optarg);
			++i;
		} else if(option == "-f" || option == "-g"){
			flag_from_string(argv[i], cmd_opts);
		} else {
			std::cout << argv[0] << " : Invalid flag " << option << std::endl;
			print_usage();
			exit(1);
		}
	}
	return 0;
}

int parse_opts(int argc, char **argv, struct CommandOpts *cmd_opts)
{
	if(argc < 1){
		std::cout << "Error : no command specified" << std::endl;
		print_usage();
		exit(1);
	}
	parse_command(argv[1], cmd_opts);
	parse_options(argc, argv, cmd_opts);
}

int flag_from_string(const char *s, struct CommandOpts *cmd_opts)
{
	if(strcmp(s,"-f") == 0){
		cmd_opts->flags.flag_1 = true;
	} else if (strcmp(s, "-g")){
		cmd_opts->flags.flag_2 = true;
	}
	return 0;
}

int run_command_dispatch(struct CommandOpts *cmd_opts)
{
	switch(cmd_opts->command.cmd){
		case COMPILE:
			return compile_cmd(cmd_opts);
		case LINK:
			return link_cmd(cmd_opts);
		case DO_C:
			return do_c_cmd(cmd_opts);
		default:
			std::cout << "unknown command" << std::endl;
			print_usage();
			exit(1);
	}
}

int main(int argc, char **argv)
{
	// Print all the arguments
#if 0
	for(int i = 0; i < argc ; ++i){
		std::cout << "argv["<<i<<"] = "<< argv[i] <<std::endl;
	}
#endif

	// Read the arguments into a structure
	struct CommandOpts cmd_opts;
	parse_opts(argc,argv, &cmd_opts);

	// Print the structure
	std::cout << "opts->command = " << cmd_opts.command.name << std::endl;
	for(auto it = cmd_opts.includes.begin(); it != cmd_opts.includes.end(); ++it){
		if(it == cmd_opts.includes.begin()){
			std::cout << "includes : " << std::endl;
		}
		std::cout << "    " << *it << std::endl;
	}

	run_command_dispatch(&cmd_opts);

	return 0;
}
