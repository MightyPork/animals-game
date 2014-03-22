#include "default.h"
#include "ui.h"
#include "colors.h"



char* get_input(int len, char* prompt) {
	
	char* buffer = malloc(sizeof(char)*len);
	
	print("<fg:cyan><b>[");
	print(prompt);
	print("]:</b></fg> ");
	
	if(!fgets(buffer, len, stdin)) {
		free(buffer);
		return NULL;
	}
	
	return buffer;
}

void println(char* text) {
	print(text);
	endl();
}

void print(char* text) {
	text = color_tags(text);
	fputs(text, stdout);
	free(text);
}

void endl() {
	puts("");
}