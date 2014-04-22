#include "default.h"
#include "log.h"
#include "ui.h"

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
				print("<fg:green>INFO:</fg> ");
				println(m);
			}
			break;
			
		case ERROR:
			print("<fg:red>ERROR:</fg> ");
			println(m);
			break;
	}
	
	free(m);

}
