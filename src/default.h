#ifndef DEFAULT_H
#define DEFAULT_H

 	#define _GNU_SOURCE
	
	#include <stdio.h>
	#include <stdlib.h>


	/* === CUSTOM TYPES === */
	
	/* boolean type */
	typedef int bool;
	#define TRUE 1
	#define FALSE 0
	
	
	/* === GLOBAL VARS === */

	// verbose mode
	extern bool verbose;
	
	
	/* === DEFAULT INCLUDED COMPONENTS === */
	
	#include "log.h"
	#include "ui.h"

#endif
