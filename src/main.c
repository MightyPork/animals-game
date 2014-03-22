#include "default.h"
#include "ui.h"

#include <getopt.h>

#define OPTIONS_END {0,0,0,0}



// == prototypes ==

int main(int argc, char **argv);
void parse_opts(int argc, char* argv[]);
void print_help();



// == variables ==

bool verbose = FALSE; // extern
char* datafile = "animals.dat"; // extern



// == functions ==

/* main function */
int main (int argc, char **argv) {
	
	parse_opts(argc, argv);

	exit(0);
}

/* process command line arguments */
void parse_opts (int argc, char* argv[]) {
	bool err_flag = FALSE;
	bool help_flag = FALSE;
	
	struct option long_opts[] =
	{
		{ "verbose", no_argument,       &verbose,   TRUE },
		{ "help",    no_argument,       &help_flag, TRUE },
		{ "file",    optional_argument, 0,          'f'  },
		OPTIONS_END
	};

	while(TRUE) {
		
		
		int long_opts_cnt = 0;
		char c = getopt_long(argc, argv, "hvf:", long_opts, &long_opts_cnt);

		if (c == -1) break; // end of options

		switch(c) {
			case 0:
				// flag option, already processed
				break;

			case 'f':
				// file name
				datafile = optarg;
				break;
				
			case 'v':
				// verbose on
				verbose = TRUE;
				break;
				
			case 'h':
				// help requested
				help_flag = TRUE;
				break;

			default:
				printf("Unknown option %c\n", c);
			case '?':
				err_flag = TRUE;
				break;
		}
	}
	
	if(err_flag OR help_flag) {
		print_help();
		exit(1);
	}
	
	log_msg(INFO, "Verbose mode enabled.");
	log_msg(INFO, "Data file: %s", datafile);
}

void print_help() {
	println( "" );
	println( " <u><b><fg:white>Animals Game<r>" );
	println( " <fg:lmagenta>usage: animals [-v] [-f DB_FILE] [-h]<r>" );
	println( "  <fg:white>-v, --verbose</fg>  Enable extra debug messages" );
	println( "  <fg:white>-f, --file</fg>     Specify location of data file (default: animals.dat)" );
	println( "  <fg:white>-h, --help</fg>     Show this help" );
	println( "" );
}
