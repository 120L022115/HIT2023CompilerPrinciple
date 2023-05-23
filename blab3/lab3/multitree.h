#ifndef NUM_TREE11
#define NUM_TREE11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char* name;
    int numchild; 
    char* typevalue;
    char* IDvalue;
    int intvalue;
    int relopvalue;
    float floatvalue; 
    struct node_t** children;
    int linenum; 
    int type ;
    int dim ;
    int arraytype;
    int canleft;
} node;


node* Create_new_node( char* nodename , int number , node** childs , int yylineno);

void Travel (node* root,int space);
#endif
