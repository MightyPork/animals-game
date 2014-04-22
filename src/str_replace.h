#ifndef STR_REPLACE_H
#define STR_REPLACE_H

	/**
	 * replace substrings in a newly allocated string
	 * 
	 * @param src string to process 
	 * @param from searched substring
	 * @param to replacement
	 * 
	 * @returns newly allocated string with the result
	 */
	char* str_replace(const char *src, const char *from, const char *to);

#endif
