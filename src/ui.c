#include "default.h"
#include "ui.h"

// private prototype
char* _print_prompt(char* prompt);


bool ask_yes_no(char* prompt) {
	
	while(1) {
		char c;
		
		println(prompt);
		_print_prompt("Y/N");
		
		c = getchar();
		while ( getchar() != '\n' ); // clear
		
		// yes
		if(c=='y' || c=='Y' || c=='a' || c=='A') return TRUE;
		
		// no
		if(c=='n' || c=='N') return FALSE;
		
		print("<fg:red>Please, try again.</fg>\n");
	}
}

char* get_input(int len, char* prompt) {
	
	char* buffer = malloc(sizeof(char)*len);
	
	_print_prompt(prompt);
	
	if(!fgets(buffer, len, stdin)) {
		free(buffer);
		return NULL;
	}
	
	return buffer;
}


char* _print_prompt(char* prompt) {
	print(" <fg:green><b>[");
	print(prompt);
	print("]:</b></fg> ");	
}


void println(char* text) {
	print(text);
	endl();
}


void print(char* text) {
	char* colorized = color_tags(text);
	if(colorized != NULL) {
		fputs(colorized, stdout);
		free(colorized);
	}else{
		puts("ERROR in PRINT");
		fputs(text, stdout);
	}
}


void endl() {
	puts("");
}
