#include <string.h>

#include "default.h"
#include "game.h"

/* == DEF == */

// node type
typedef enum { QST = 0, ANS = 1 } NTYPE;

// null node index
#define NIL -1

typedef int ni_t; // node index

typedef struct NODE NODE;

struct NODE {	
	char text[256]; // node text (question or animal name)

	NTYPE type; // type of the node

	// relation indices
	ni_t i;  // self
	ni_t yi; // yes-branch child
	ni_t ni; // no-branch child
};


// node linked list
typedef struct NLL NLL;

struct NLL {
	NODE* val;
	NLL* tail;
};



/* == PROTOTYPES == */

bool file_exists(char* fname);
void game_start(char* fname);

NODE* node_make(char* text, NTYPE type, int i, int yi, int ni);
void node_destroy(NODE* node);

int nll_size(NLL* head);
void nll_append(NLL* head, NLL* to_append);
void nll_prepend(NLL* head, NLL* to_prepend);
NLL* nll_make(NODE* node);
void nll_destroy(NLL* nll);

NLL* nll_load(char* fname);
bool nll_save(NLL* head, char* fname);


/* make game node */
NODE* node_make(char* text, NTYPE type, int i, int yi, int ni) {

	NODE* node = malloc(sizeof(NODE));
	if (node == NULL) return NULL;

	memset(node, 0, sizeof(NODE)); // clean memory

	node->text[0] = 0;
	strncat(node->text, text, sizeof(node->text) - 1);
	
	node->type = type;
	node->i = i;
	node->yi = yi;
	node->ni = ni;

	return node;	
}


/* destroy game node */
void node_destroy(NODE* node) {

	if (node==NULL) return;
	free(node);
}


/* get NLL length */
int nll_size(NLL* head) {

	if (head == NULL) return 0;
	
	return 1 + nll_size(head->tail);
}

/* append NLL to another */
void nll_append(NLL* head, NLL* to_append) {

	if(head == NULL || to_append == NULL) return;

	if (head->tail != NULL) {
		nll_append(head->tail, to_append);
	} else {
		head->tail = to_append;
	}
}

/* prepend NLL to another */
void nll_prepend(NLL* head, NLL* to_prepend) {

	if (head == NULL || to_prepend == NULL) return;

	NLL* tmp = head;

	head = to_prepend;
	nll_append(head, tmp);	
}

/* make a NLL */
NLL* nll_make(NODE* node) {

	NLL* nll = malloc(sizeof(NLL));
	if (nll==NULL) return NULL;
	
	nll->tail = NULL;
	nll->val = node;
	return nll;
}

/* destroy a NLL and tail, with values */
void nll_destroy(NLL* nll) {
	
	if(nll == NULL) return;
	
	nll_destroy(nll->tail);
	node_destroy(nll->val);
	free(nll);
}


NODE* nll_get_node(NLL* head, int i) {
	if(head == NULL) return NULL;
	if(head->val != NULL) {
		if(head->val->i == i) return head->val;
	}

	return nll_get_node(head->tail, i);
}


NLL* nll_load(char* fname) {

	FILE* fp = fopen(fname, "rb");

	if (fp != NULL) {
		int count;
		
		if(!fread(&count, sizeof(int), 1, fp)) return NULL;

		NLL* head = NULL;
		NODE* node = NULL;

		for(int i=0; i<count; i++) {

			node = malloc(sizeof(NODE));
			if(node == NULL) return NULL;
			if(!fread(node, sizeof(NODE), 1, fp)) return NULL;

			if (head == NULL) {
				head = nll_make(node);
			} else {
				nll_append(head, nll_make(node));
			}		
		}
		
		fclose(fp);

		return head;
		
	} else {
		return NULL;
	}
}

bool nll_save(NLL* head, char* fname) {
	// * size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);

	FILE* fp = fopen(fname, "wb");

	if (fp) {
		int count = nll_size(head);
		
		if(!fwrite(&count, sizeof(int), 1, fp)) return FALSE;

		NLL* nll = head;

		while(nll != NULL) {
			if(!fwrite(nll->val, sizeof(NODE), 1, fp)) return FALSE;
			nll = nll->tail;	
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

	NLL* list = nll_load(fname);
	
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

			NODE* n = node_make(tmp, ANS, 0, NIL, NIL);
			list = nll_make(n);

			log_msg(INFO, "Saving file.");
			nll_save(list, fname);
			
		} else {
			// actual game

			NODE* prev = NULL;
			NODE* node = nll_get_node(list, 0); // root

			while(TRUE) {
				if(node->type == QST) {
					// question
					
					bool choice = ask_yes_no(node->text);

					prev = node;
					if (choice) {
						node = nll_get_node(list, node->yi);
					} else {
						node = nll_get_node(list, node->ni);
					}
					
				} else {
					// answer

					sprintf(tmp, "Is it %s?", node->text);

					bool choice = ask_yes_no(tmp);

					if (choice) {
						cprint("\n <b><fg:cyan>*** I win! ***<r>\n");
						break;
					} else {

						if(NULL == read_animal(tmp, 254)) {
							cprintln(" <bg:red><fg:white>No input, terminating.<r>\n");
							aborted = TRUE;
							break;
						}

						NODE* nn = node_make(tmp, ANS, nll_size(list), NIL, NIL);
						if(nn == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}

						NLL* nnwrap = nll_make(nn);
						if(nnwrap == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}
						
						nll_append(list, nnwrap);
						
						sprintf(tmp2, "What <u>question</u> can help me tell apart %s and %s?", node->text, nn->text);

						if(!get_input(tmp, 254, tmp2)) {
							cprintln(" <bg:red><fg:white>No input, terminating.<r>\n");
							aborted = TRUE;
							break;
						}

						NODE* ndis = node_make(tmp, QST, nll_size(list), NIL, NIL);
						if(ndis == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}

						NLL* ndiswrap = nll_make(ndis);
						if(ndiswrap == NULL) {
							log_msg(ERROR, "Malloc error");
							aborted = TRUE;
							break;
						}
						
						nll_append(list, ndiswrap);

						sprintf(tmp, "What would be the <u>answer for %s</u>?", node->text);
						bool true_old = ask_yes_no(tmp);

						if(prev == NULL) {

							int sw = ndis->i;
							ndis->i = node->i;
							node->i = sw;
							
						} else {

							if(prev->yi == node->i) {
								prev->yi = ndis->i;
							} else {
								prev->ni = ndis->i;
							}
						}

						if(true_old) {
							ndis->yi = node->i;
							ndis->ni = nn->i;
						} else {
							ndis->yi = nn->i;
							ndis->ni = node->i;
						}

						log_msg(INFO, "Saving file.");
						nll_save(list, fname);

						break;
					}

				}
				
			}
		}

		if(aborted) break;
		
		cprint("<fg:yellow>\n---------------- GAME END ----------------<r>\n");

		if(!ask_yes_no("<b>Do you want to play again?<r>")) break;
	}

	if(!aborted) {
		log_msg(INFO, "Saving file.");
		nll_save(list, fname);
	}

	nll_destroy(list);
}
