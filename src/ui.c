#include "default.h"
#include "ui.h"

void msg(int severity, char* message, ...) {
	
	va_list args;
    va_start(args, message);
	char* m;
	if(vasprintf(&m, message, args) == -1) m = message;
    va_end(args);
	
	switch(severity) {
		default:
		case INFO:
			if(verbose) {
				print("<fg:green>INFO:</fg> ");
				println(m);
			}
			break;
			
		case ERROR:
			print("<fg:lred>ERROR:</fg> <fg:red>");
			print(m);
			println("</fg>");
			break;
			
	}
}