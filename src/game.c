#include "default.h"
#include "game.h"
#include "string_utils.h"

#include <string.h>

/* == DEF == */

// node type
typedef enum { QST = 0, ANS = 1 } NTYPE;

// null node index
#define NIL -1

typedef struct NODE NODE;

struct NODE {	
	char* text; // node text (question or animal name)

	NTYPE type; // type of the node

	// relation indices
	int index;  // self
	int yes; // yes-branch child
	int no; // no-branch child

	NODE* tail;
};


/* == PROTOTYPES == */

void game_start(char* fname);

NODE* make_node(char* text, NTYPE type, int i, int yi, int ni);
void free_node(NODE* node);

int list_size(NODE* head);
void list_append(NODE* head, NODE* to_append);

NODE* load_list(char* fname);
bool save_list(NODE* head, char* fname);


/* make game node */
NODE* make_node(char* text, NTYPE type, int index, int yes, int no) {

	NODE* node = malloc(sizeof(NODE));
	if (node == NULL) return NULL;

	node->text = strdup(text); // calls malloc
	
	node->type = type;
	
	node->index = index;
	node->yes = yes;
	node->no = no;

	node->tail = NULL;

	return node;	
}


/* destroy game node */
void free_node(NODE* node) {

	if (node==NULL) return;
	
	free_node(node->tail);

	if(node->text != NULL) {
		free(node->text);
	}
	
	free(node);
}


/* get list length */
int list_size(NODE* head) {

	if (head == NULL) return 0;
	
	return 1 + list_size(head->tail);
}

/* append NLL to another */
void list_append(NODE* head, NODE* to_append) {

	if(head == NULL || to_append == NULL) return;

	if (head->tail != NULL) {
		list_append(head->tail, to_append);
	} else {
		head->tail = to_append;
	}
}


NODE* find_node(NODE* head, int i) {
	if(head == NULL) return NULL;
	
	if(head->index == i) return head;

	return find_node(head->tail, i);
}

int find_next_index(NODE* head) {

	if(head == NULL) return 0;

	int amax = find_next_index(head->tail);

	if(amax > head->index) {
		return amax;
	} else {
		return head->index+1;
	}	
}

int count_of_type(NODE* head, NTYPE type) {

	if(head == NULL) return 0;

	int cnt = count_of_type(head->tail, type);

	if(head->type == type) cnt++;

	return cnt;	
}


NODE* load_list(char* fname) {
	FILE* fp = fopen(fname, "rb");

	if (fp != NULL) {

		NODE* head = NULL;
		NODE* node = NULL;

		bool failed = FALSE;

		int v_index;
		int v_yes;
		int v_no;
		char v_type;
		char v_text[512];

		int cnt = 1; // row counter

		#define LOAD_FAIL_MSG " <bg:red><fg:white>Error in data file on line %d!<r>\n"
		
		while (!feof(fp)) {

			if (2 != fscanf(fp, "%d %c", &v_index, &v_type)) {

				if(feof(fp)) break;
				
				cprintf(LOAD_FAIL_MSG, cnt);
				failed = TRUE; break;
			}

			if (v_type == 'Q') {
				
				if (3 != fscanf(fp, " (%d,%d): %[^\n]s\n", &v_yes, &v_no, v_text)) {
					cprintf(LOAD_FAIL_MSG, cnt);
					failed = TRUE; break;
				}

				node = make_node(v_text, QST, v_index, v_yes, v_no);
				
			} else if(v_type == 'A') {
				
				if (1 != fscanf(fp, ": %[^\n]s\n", v_text)) {
					cprintf(LOAD_FAIL_MSG, cnt);
					failed = TRUE; break;
				}
				
				node = make_node(v_text, ANS, v_index, NIL, NIL);			

			} else {
				cprintf(LOAD_FAIL_MSG, cnt);
				failed = TRUE; break;
			}

			// add to list
			if (head == NULL) {
				head = node;
			} else {
				list_append(head, node);
			}

			cnt++;	
		}

		fclose(fp);

		// validate
		node = head;
		while(!failed && node != NULL) {
			
			if(node->type == QST) {
				
				int y = node->yes;
				int n = node->no;
				
				if(find_node(head, y) == NULL) {
					cprintf(" <bg:red><fg:white>Node %d not found in data file!<r>\n", y);
					failed = TRUE;
					break;				
				}
				
				if(find_node(head, n) == NULL) {
					cprintf(" <bg:red><fg:white>Node %d not found in data file!<r>\n", n);
					failed = TRUE;
					break;				
				}
			}

			node = node->tail;			
		}

		

		if(failed) return NULL;

		return head;
		
	} else {
		return NULL;
	}
}


bool save_list(NODE* head, char* fname) {
	FILE* fp = fopen(fname, "w");

	if (fp) {

		NODE* node = head;

		while(node != NULL) {
			if(node->type == QST) {
				fprintf(fp, "%d Q (%d,%d): %s\n", node->index, node->yes, node->no, node->text);
			}
			node = node->tail;
		}

		node = head;

		while(node != NULL) {
			if(node->type == ANS) {
				fprintf(fp, "%d A: %s\n", node->index, node->text);					
			}
			node = node->tail;	
		}

		fclose(fp);

		return TRUE;
		
	} else {
		return FALSE;
	}		
}


char* read_animal(char* target, int len) {
	cprint("\n <b><fg:cyan>*** You win! ***<r>\n");
	if(!get_input(target, len, "What <u>animal</u> is it?")) return NULL;

	cprintf("\n Animal learned: <fg:cyan><b>%s<r>\n", target);
	
	return target;
}

void game_start(char* fname) {
	cprint("\n <b><fg:cyan>Animals game<r>\n");
	cprint(" <fg:cyan>© MightyPork 2014<r>\n");

	log_msg(INFO, "Loading tree from: %s", fname);

	NODE* list = load_list(fname);

	cprintf("\n <fg:white>Known animals: %d<r>\n", count_of_type(list, ANS));

	
	char tmp[512];
	char tmp2[512];

	bool aborted = FALSE;

	while(!aborted) {
		
		cprint("<fg:yellow>\n---------------- NEW GAME ----------------<r>\n\n");

		cprint(" <fg:cyan>Think of an <u>animal</u>, and press enter.<r>");
		wait_enter();

		if(list == NULL) {

			endl();
			if(NULL == read_animal(tmp, 254)) {
				cprintln(" <bg:red><fg:white>No input, terminating.<r>\n");
				break;
			}

			list = make_node(tmp, ANS, 0, NIL, NIL);

			log_msg(INFO, "Saving file.");
			save_list(list, fname);
			
		} else {
			// actual game

			NODE* prev = NULL;
			NODE* cur = find_node(list, 0); // root

			while(TRUE) {
				if(cur->type == QST) {
					// question
					
					bool choice = ask_yes_no(cur->text);

					prev = cur;
					if (choice) {
						cur = find_node(list, cur->yes);
					} else {
						cur = find_node(list, cur->no);
					}
					
				} else {
					// answer

					sprintf(tmp, "Is it <fg:cyan><b>%s<r>?", cur->text);

					bool choice = ask_yes_no(tmp);

					if (choice) {
						cprint("\n <b><fg:cyan>*** I win! ***<r>\n");
						break;
					} else {

						if(NULL == read_animal(tmp, 512)) {
							cprintln(" <bg:red><fg:white>No input, terminating.<r>\n");
							aborted = TRUE;
							break;
						}

						NODE* nn = make_node(tmp, ANS, find_next_index(list), NIL, NIL);
						if(nn == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}						
						list_append(list, nn);
						
						sprintf(tmp2, "What <u>question</u> can help me tell apart <fg:cyan><b>%s<r> and <fg:cyan><b>%s<r>?", cur->text, nn->text);

						if(!get_input(tmp, 512, tmp2)) {
							cprintln(" <bg:red><fg:white>No input, terminating.<r>\n");
							aborted = TRUE;
							break;
						}

						NODE* ndis = make_node(tmp, QST, find_next_index(list), NIL, NIL);
						if(ndis == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}						
						list_append(list, ndis);

						sprintf(tmp, "What would be the <u>answer</u> for <fg:cyan><b>%s<r>?", cur->text);
						bool true_old = ask_yes_no(tmp);

						if(prev == NULL) {

							int sw = ndis->index;
							ndis->index = cur->index;
							cur->index = sw;
							
						} else {

							if(prev->yes == cur->index) {
								prev->yes = ndis->index;
							} else {
								prev->no = ndis->index;
							}
						}

						if(true_old) {
							ndis->yes = cur->index;
							ndis->no = nn->index;
						} else {
							ndis->yes = nn->index;
							ndis->no = cur->index;
						}

						log_msg(INFO, "Saving file.");
						save_list(list, fname);

						break;
					}

				}
				
			}
		}

		if(aborted) break;
		
		cprint("<fg:yellow>\n---------------- GAME END ----------------<r>\n");

		if(!ask_yes_no("<fg:white>Do you want to play again?<r>")) break;
	}

	if(!aborted) {
		log_msg(INFO, "Saving file.");
		save_list(list, fname);
	}

	free_node(list);
}
