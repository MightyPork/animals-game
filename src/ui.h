#ifndef UI_H
#define UI_H

	#include "colors.h"
	
	/* Ask for confirmation */
	bool ask_yes_no(char* prompt);
	
	/* Get user input of max length */
	char* get_input(int len, char* prompt);
	
	/* print with color tags, newline */
	void println(char* text);
	
	/* print with color tags */
	void print(char* text);
	
	/* newline */
	void endl();

#endif
