#ifndef COLORS_H
#define COLORS_H

	// color macros

	// \033 = \e
    
	#define RESET       "\033[0m"
	#define FR          RESET	
	#define BOLD        "\033[1m"
	#define UNDERLINE   "\033[4m"
	#define BLINK       "\033[5m"
	#define INVERSE     "\033[7m"
	#define HIDDEN      "\033[8m"
	
	#define BOLD_R       "\033[22m"
	#define UNDERLINE_R  "\033[24m"
	#define BLINK_R      "\033[25m"
	#define INVERSE_R    "\033[27m"
	#define HIDDEN_R     "\033[28m"
	
	#define FG_DEFAULT   "\033[39m"
	#define FG_BASE      FG_DEFAULT
	#define FG_BLACK     "\033[30m"
	#define FG_RED       "\033[31m"
	#define FG_GREEN     "\033[32m"
	#define FG_YELLOW    "\033[33m"
	#define FG_BLUE      "\033[34m"
	#define FG_MAGENTA   "\033[35m"
	#define FG_CYAN      "\033[36m"
	#define FG_LGRAY     "\033[37m"
	#define FG_DGRAY     "\033[90m"
	#define FG_LRED      "\033[91m"
	#define FG_LGREEN    "\033[92m"
	#define FG_LYELLOW   "\033[93m"
	#define FG_LBLUE     "\033[94m"
	#define FG_LMAGENTA  "\033[95m"
	#define FG_LCYAN     "\033[96m"
	#define FG_WHITE     "\033[97m"
	
	#define BG_DEFAULT   "\033[49m"
	#define BG_BASE      BG_DEFAULT
	#define BG_BLACK     "\033[40m"
	#define BG_RED       "\033[41m"
	#define BG_GREEN     "\033[42m"
	#define BG_YELLOW    "\033[43m"
	#define BG_BLUE      "\033[44m"
	#define BG_MAGENTA   "\033[45m"
	#define BG_CYAN      "\033[46m"
	#define BG_LGRAY     "\033[47m"
	#define BG_DGRAY     "\033[100m"
	#define BG_LRED      "\033[101m"
	#define BG_LGREEN    "\033[102m"
	#define BG_LYELLOW   "\033[103m"
	#define BG_LBLUE     "\033[104m"
	#define BG_LMAGENTA  "\033[105m"
	#define BG_LCYAN     "\033[106m"
	#define BG_WHITE     "\033[107m"
	
	#define COLOR_R      FG_DEFAULT""BG_DEFAULT
	
	
	// prototypes
	char* color_tags(char* str);

#endif
