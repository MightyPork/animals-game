#include "default.h"
#include "game.h"

#include <getopt.h>
#include <string.h>

#define OPTIONS_END {0,0,0,0}



// == prototypes ==

int main(int argc, char **argv);
void parse_opts(int argc, char* argv[]);
void print_help();



// == variables ==

bool verbose = FALSE; // extern

char* datafile = "animals.dat";



// == functions ==

/* main function */
int main (int argc, char **argv) {
	
  	parse_opts(argc, argv);

	game_start(datafile);
	
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
				// fall-thru
			case '?':
				err_flag = TRUE;
				break;
		}
	}
	
	if(err_flag || help_flag) {
		print_help();
		exit(1);
	}
	
	log_msg(INFO, "Verbose mode enabled.");
	log_msg(INFO, "Data file: %s", datafile);
}


void print_help() {
	endl();
	println( " <u><b><fg:white>Animals Game<r>" );
	println( " <fg:lmagenta>usage: animals [-v] [-f DB_FILE] [-h]<r>" );
	println( "  <b><fg:white>-v, --verbose<r>  Enable extra debug messages" );
	println( "  <b><fg:white>-f, --file<r>     Specify location of data file (default: animals.dat)" );
	println( "  <b><fg:white>-h, --help<r>     Show this help" );
	endl();
}
