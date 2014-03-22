#ifndef UI_H
#define UI_H

	#include "colors.h"

	// fn macros
	#define println(text) puts(color_tags(text))
	#define print(text) fputs(color_tags(text), stdout)

#endif
