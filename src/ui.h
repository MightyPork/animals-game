#ifndef UI_H
#define UI_H

	#include <stdio.h>
	#include "colors.h"

	// fn macros
	#define println(text) puts(color_tags(text))
	#define print(text) fputs(color_tags(text), stdout)
	#define endl() puts("")
	
	// prototypes
	char* get_input(int len, char* prompt);

#endif
