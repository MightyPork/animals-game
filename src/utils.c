#include "default.h"
#include "utils.h"

#include <string.h>
#include <ctype.h>
#include <stddef.h>

// TODO rewrite, super ugly and has a memory leak

    char *
    str_replace ( char *substr, char *replacement, char *string ){
      char *tok = NULL;
      char *newstr = NULL;
      char *oldstr = NULL;
      char *head = NULL;
     
      /* if either substr or replacement is NULL, duplicate string a let caller handle it */
      if ( substr == NULL || replacement == NULL ) return string;
      newstr = strdup(string);
      head = newstr;
      while ( (tok = strstr ( head, substr ))){
		free(oldstr);
		oldstr = NULL;
        oldstr = newstr;
        newstr = malloc( strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) + 1 );
        /*failed to alloc mem, free old string and return NULL */
        if(newstr == NULL){
          free(oldstr);
          return NULL;
        }
        memcpy ( newstr, oldstr, tok - oldstr );
        memcpy ( newstr + (tok - oldstr), replacement, strlen ( replacement ) );
        memcpy ( newstr + (tok - oldstr) + strlen( replacement ), tok + strlen ( substr ), strlen ( oldstr ) - strlen ( substr ) - ( tok - oldstr ) );
        memset ( newstr + strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) , 0, 1 );
        /* move back head right after the last replacement */
        head = newstr + (tok - oldstr) + strlen( replacement );
        free (oldstr);
		oldstr = NULL;
      }
      
      //if(head!=NULL) free(head);
      if(oldstr!=NULL) free(string);
      //if(newstr!=NULL) free(string);
      //if(string!=NULL) free(string);
      return newstr;
    }








