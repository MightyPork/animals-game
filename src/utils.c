#include "default.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Replace occurences in input string.
* 
* Returned string is alloc'd and the caller has the
* responsibility to clean it up.
*/
char* str_replace(const char *src, const char *from, const char *to) {
	
	// helper pointers
	const char *sp; // src pointer
	char *dp; // dest pointer
	const char *mp; // match pointer
	
	// lengths
	size_t from_len = strlen(from);
	size_t to_len = strlen(to);
	size_t src_len = strlen(src);
	
	// count matches
	size_t count = 0;
	sp = src;
	while(1) {
		mp = strstr(sp, from); // find next match
		if(mp == NULL) break; // end of matches
		count++;
		sp = mp + from_len; // advance past match
	}
	
	// compute dest size
	size_t len = src_len;
	size_t sub = (from_len - to_len)*count;
	// sanity check
	if(from_len >= to_len) {
		if(sub > len || sub < 0) return NULL; // integer overflow / bad arith
	} else {
		if((len-sub) < 0 || sub > 0) return NULL; // integer overflow / underflow
	}
	
	// allocate output buffer
	char *dest = malloc( len - sub + 1 );
	
	// fill output buffer
	if(dest != NULL) {
		
		sp = src; // src pointer
		dp = dest; // dest pointer
		
		while(1) {
			mp = strstr(sp, from); // find next match
			if(mp == NULL) break; // end of matches
			
			// copy chunk before match
			memcpy(dp, sp, sp - mp);
			dp += sp-mp;
			
			// copy replacement
			memcpy(dp, to, to_len);
			dp += to_len;
			
			sp = mp + from_len;
		}
		
		// add in the remainder
		if(sp < src + src_len) {
			memcpy(dp, sp, (src + src_len) - sp);
		}
	}
	
	return dest;
}
