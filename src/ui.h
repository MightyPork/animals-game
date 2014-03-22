#ifndef UI_H
#define UI_H

	#include "colors.h"

	#define println(text) puts(color_tags(text))
	#define print(text) fputs(color_tags(text), stdout)
	
	#define INFO 0
	#define ERROR 1
	
	void msg(int severity, char* message, ...);

#endif