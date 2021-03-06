#include "default.h"
#include "colors.h"
#include "string_utils.h"

#define repl_count 46

char* color_tags(char* s) {
	
	char* out = s;
	
	static char* table[repl_count][2] = {
		{"<b>", BOLD},
		{"<u>", UNDERLINE},
		{"<blink>", BLINK},
		{"<inv>", INVERSE},
		{"<hide>", HIDDEN},
		
		{"</b>", BOLD_R},
		{"</u>", UNDERLINE_R},
		{"</blink>", BLINK_R},
		{"</inv>", INVERSE_R},
		{"</hide>", HIDDEN_R},
		
		{"<reset>", RESET},
		{"<r>", RESET},
		
		{"<fg:black>", FG_BLACK},     
		{"<fg:red>", FG_RED},       
		{"<fg:green>", FG_GREEN},     
		{"<fg:yellow>", FG_YELLOW},    
		{"<fg:blue>", FG_BLUE},      
		{"<fg:magenta>", FG_MAGENTA},   
		{"<fg:cyan>", FG_CYAN},      
		{"<fg:lgray>", FG_LGRAY},     
		{"<fg:dgray>", FG_DGRAY},     
		{"<fg:lred>", FG_LRED},      
		{"<fg:lgreen>", FG_LGREEN},    
		{"<fg:lyellow>", FG_LYELLOW},   
		{"<fg:lblue>", FG_LBLUE},     
		{"<fg:lmagenta>", FG_LMAGENTA},  
		{"<fg:lcyan>", FG_LCYAN},     
		{"<fg:white>", FG_WHITE},   
		{"</fg>", FG_DEFAULT},
		
		{"<bg:black>", BG_BLACK},     
		{"<bg:red>", BG_RED},       
		{"<bg:green>", BG_GREEN},     
		{"<bg:yellow>", BG_YELLOW},    
		{"<bg:blue>", BG_BLUE},      
		{"<bg:magenta>", BG_MAGENTA},   
		{"<bg:cyan>", BG_CYAN},      
		{"<bg:lgray>", BG_LGRAY},     
		{"<bg:dgray>", BG_DGRAY},     
		{"<bg:lred>", BG_LRED},      
		{"<bg:lgreen>", BG_LGREEN},    
		{"<bg:lyellow>", BG_LYELLOW},   
		{"<bg:lblue>", BG_LBLUE},     
		{"<bg:lmagenta>", BG_LMAGENTA},  
		{"<bg:lcyan>", BG_LCYAN},     
		{"<bg:white>", BG_WHITE},   
		{"</bg>", BG_DEFAULT}
	};
	  
	
	for(int r=0; r<repl_count; r++) {
		char* old = out;
		out = str_replace(old, table[r][0], table[r][1]);
		if(out == NULL) {
			puts("ERROR in STR_REPLACE");
			return NULL;
		}
		if(r>0) free(old);
 	}
 	
 	return out;
}
