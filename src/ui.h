#ifndef UI_H
#define UI_H
	
	/* Ask for confirmation */
	bool ask_yes_no(char* prompt);
	
	/* Get user input of max length */
	char* get_input(char* target, int len, char* prompt);
	
	/* print with color tags, newline */
	void cprintln(char* text);
	
	/* print with color tags */
	void cprint(char* text);
	
	/* printf with color tags */
	void cprintf(char* text, ...);
	
	/* newline */
	void endl();

	/* wait for end of line, discard read stuff. */
	void wait_enter();

#endif
