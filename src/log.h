#ifndef LOG_H
#define LOG_H

	#include "types.h"

	// log levels
	#define INFO 0
	#define ERROR 1
	
	/*
	 * Print a log message
	 * Logging can be supressed using a global variable verbose
	 */
	void log_msg(int level, char* message, ...);

#endif
