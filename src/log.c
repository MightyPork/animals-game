#include "default.h"
#include "log.h"

#include <stdarg.h>


void log_msg(int level, char* message, ...) {
	
	if(!verbose) return;

	va_list args;
    va_start(args, message);
	char* m;
	if(vasprintf(&m, message, args) == -1) return;
    va_end(args);
	
	switch(level) {
		default:
		case INFO:
			if(verbose) {
				cprint("<fg:green>INFO:</fg> ");
				cprintln(m);
			}
			break;
			
		case ERROR:
			cprint("<fg:red>ERROR:</fg> ");
			cprintln(m);
			break;
	}
	
	free(m);

}
