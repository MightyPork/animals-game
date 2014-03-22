#include "default.h"

#include <getopt.h>

#define OPTIONS_END {0,0,0,0}



// == prototypes ==

int main(int argc, char **argv);
void parse_opts(int argc, char* argv[]);
void print_help();



// == variables ==

bool verbose = FALSE; // extern
char* datafile = "animals.db"; // extern



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

	while(1) {
		
		static struct option long_opts[] =
		{
			{ "verbose", no_argument,       &verbose, TRUE },
			{ "file",    optional_argument, 0,        'f'  },
			OPTIONS_END
		};
		
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
	
	if(err_flag or help_flag) {
		print_help();		
		exit(1);
	}

	if(verbose) puts("Verbose mode enabled.");
	
	printf("%s\n",datafile);
}

void print_help() {
	puts("Animals Game");
	puts("usage: animals [-v] [-f DB_FILE] [-h]");
	puts("-v, --verbose  Enable extra debug messages");
	puts("-f, --file     Specify location of database file (default: animals.db)");
	puts("-h, --help     Show this help");	
}
