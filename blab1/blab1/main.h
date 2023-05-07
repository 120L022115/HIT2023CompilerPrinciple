# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# define maxNum 10
extern int yylineno;
extern char* yytext;
extern int yylex(void);

struct TREE{
    int line; //行号
    char* name; //文法符号名称
    int n; // 子结点数量
    struct TREE *child[maxNum];
    union{
        char* ID; //标识符名称
        int INT;
        float FLOAT;
    };
};
typedef struct TREE *treeNode;

int hasFault;
int nodeNum;
treeNode nodeList[1000];
int nodeIsChild[1000];

int stoi(char * p);

void setChildTag (treeNode node);

treeNode newNode(char *name, int num, int yyline, treeNode childList[]);

void preOrder(treeNode t, int level);

void printTree();

void yyerror(const char *msg);
