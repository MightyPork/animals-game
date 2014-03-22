
#include "utils.h"

#include <stdlib.h>
#include <string.h>

/*
* Replace occurences in input string.
* 
* Returned string is alloc'd and the caller has the
* responsibility to clean it up.
*/
char *str_replace(char *subject, char *search, char *replace) {
	
	char *subject_ptr = subject;
	char *find_ptr;
	
	// lengths
	int search_l = strlen(search);
	int replace_l = strlen(replace);
	int subject_l = strlen(subject_ptr);
	
	// (step 1) count occurences and allocate target string
	int cnt = 0;
	find_ptr = subject_ptr-1;
	while(1) {
		// find a match
		find_ptr = strstr( (find_ptr+1), search);
		if(find_ptr == NULL) break;
		
		cnt++; // count it
	}
	
	// allocate output buffer
	int len = strlen(subject_ptr) - cnt*search_l + cnt*replace_l;
	
	char *target_ptr = (char *) malloc( len + 1 );
	
	// (step 2) fill target string
	int copy_begin = 0;
	int paste_pos = 0;
	int copy_size = 0;
	
	find_ptr = subject_ptr-1;
	while(1) {
		// try find next match
		find_ptr = strstr( (find_ptr+1), search);
		
		if(find_ptr == NULL) break;
		
		// compute copy coords
		copy_size = (find_ptr-subject_ptr) - copy_begin;
		
		// copy in chunk before replacement
		strncpy( (target_ptr+paste_pos), (subject_ptr+copy_begin), copy_size);
		paste_pos += copy_size;
		
		// copy in replacement
		strcpy( (target_ptr+paste_pos), replace);
		paste_pos += replace_l;
		
		// move copy_begin pointer to the end of find
		copy_begin += copy_size + search_l;
	}
	
	// add in the remainder
	if(copy_begin < subject_l) strcpy( (target_ptr+paste_pos), (subject_ptr+copy_begin) );
	
	return target_ptr;
}
