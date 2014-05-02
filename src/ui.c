#include "default.h"
#include "ui.h"
#include "colors.h"
#include "string.h"

#include <stdarg.h>

// private prototype
void _print_prompt(char* prompt);


bool ask_yes_no(char* prompt) {
	
	while(1) {
		char c;
		
		endl();
		cprint(" ");
		cprintln(prompt);
		_print_prompt("Y/N");
		
		c = getchar();
		while ( getchar() != '\n' ); // clear
		
		// yes
		if(c=='y' || c=='Y' || c=='a' || c=='A') {
			return TRUE;
		}
		
		// no
		if(c=='n' || c=='N') {
			return FALSE;
		}
		
		endl();
		cprint(" <b><bg:red><fg:white>Please, try again.<r>\n");
	}
}

char* get_input(char* target, int len, char* prompt) {
	
	endl();
	cprint(" ");
	cprintln(prompt);
	_print_prompt("IN");
	
	if(!fgets(target, len, stdin)) {
		return NULL;
	}

	int alen = strlen(target);
	if(target[alen-1]=='\n') {
		target[alen-1] = 0;
	}

	if(strlen(target) == 0) return NULL;
	
	return target;
}


void _print_prompt(char* prompt) {
	cprint(" <fg:green><b>[");
	cprint(prompt);
	cprint("]:</b></fg> ");	
}


void cprintln(char* text) {
	cprint(text);
	endl();
}


void cprint(char* text) {
	char* colorized = color_tags(text);
	if(colorized != NULL) {
		fputs(colorized, stdout);
		free(colorized);
	} else {
		puts("ERROR in CPRINT");
		fputs(text, stdout);
	}
}

void cprintf(char* format, ...) {	
	va_list args;
    va_start(args, format);
	char* m;
	if(vasprintf(&m, format, args) == -1) return;
    va_end(args);
	
	cprint(m);
	
	free(m);
}

void endl() {
	puts("");
}

void wait_enter() {
	scanf("%*[^\n]");
	scanf("%*c");
}
