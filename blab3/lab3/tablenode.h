#ifndef TABLENODEH
    #define TABLENODEH

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct node1
{
	char* symname;
	Type symtype;
	struct node1* next;
} tablenode;

struct Type_
{
	enum { BASIC, ARRAY, STRUCTURE, FUNC} kind;
	union
	{
		int basic;
		struct { Type elem; int size; } array;
	} u;
};

struct Variable
{
	char* name ;
	Type head ;
	int line;
};
#endif