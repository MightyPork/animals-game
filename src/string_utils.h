#ifndef STRING_UTILS_H
#define STRING_UTILS_H

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
	
	/**
	 * Copy a string to newly allocated memory.
	 * 
	 * @param original string
	 * 
	 * @returns newly allocated string with the same value
	 * 
	 */
	char *strdup(const char *str);

#endif
