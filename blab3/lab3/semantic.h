#ifndef SEM_HASINCLUDE
#define SEM_HASINCLUDE
#include "multitree.h"
#include "tablenode.h"
extern tablenode* chainheader;
tablenode* Create_tablenode (char* nodename, Type nodetype, tablenode* chainheader);
int checkrepeat(char* nodename,int lineno);
struct Variable getVarDec(node* root,Type type);
void dealparam(node* param);
int lookuptable(char* name);
void checkerror(node* root);
void Analysis (node* root);
#endif
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
