#ifndef SEMANTIC_H
#define SEMENTIC_H

#define HASH_TABLE_SIZE 0x3fff
#define STACK_DEEP

#include "node.h"

typedef struct type* pType;             //类型结构体指针
typedef struct memberList* pMemberList;   //单向链表：函数参数列表指针 / 结构体域名列表
typedef struct tableItem* pItem;        //符号表项指针
typedef struct hashTable* pHash;        //哈希表
typedef struct stack* pStack;           //栈
typedef struct table* pTable;           //符号表


typedef struct memberList {
    char* name;       // 域的名字
    pType type;       // 域的类型
    pMemberList tail;  // 下一个域
} MemberList;

typedef struct type {
    Kind kind; //枚举值：符号表当前存储的类型：BASIC, ARRAY, STRUCTURE, FUNCTION
    // 确定数据存储的大小
    union {
        // 基本类型
        BasicType basic;
        // 数组：元素类型、大小
        struct {
            pType elem;
            int size;
        } array;
        // 结构体：链表
        struct {
            char* structName; // 结构体名称
            pMemberList field; // 域名链表：名称，类型，下一个
        } structure;
        // 函数
        struct {
            int argc;          // 参数个数
            pMemberList argv;   // 参数列表（单向链表）
            pType returnType;  // 返回值类型
        } function;
    } u;
} Type;



typedef struct tableItem {
    int symbolDepth;    
    pMemberList field;   
    pItem nextSymbol;  // same depth next symbol, linked from stack
    pItem nextHash;    // same hash code next symbol, linked from hash table
} TableItem;


typedef struct hashTable {
    pItem* hashArray;
} HashTable;

typedef struct stack {
    pItem* stackArray;
    int curStackDepth; // 栈高
} Stack;


//符号表
typedef struct table {
    pHash hash; // 哈希表
    pStack stack; // 栈
    int unNamedStructNum;
} Table;

extern pTable table;

// Type functions
pType newType(Kind kind, ...);
pType copyType(pType src);
void deleteType(pType type);
boolean checkType(pType type1, pType type2);
void printType(pType type);

// MemberList functions
pMemberList newMemberList(char* newName, pType newType);
pMemberList copyMemberList(pMemberList src);
void deleteMemberList(pMemberList memberList);
void setMemberListName(pMemberList p, char* newName);
void printMemberList(pMemberList memberList);

// tableItem functions

// inline pItem newItem() {
//     pItem p = (pItem)malloc(sizeof(TableItem));
//     p->symbolDepth = 0;
//     p->field = NULL;
//     p->nextHash = NULL;
//     p->nextSymbol = NULL;
//     return p;
// }

pItem newItem(int symbolDepth, pMemberList pfield);
void deleteItem(pItem item);
boolean isStructDef(pItem src);

// Hash functions
pHash newHash();
void deleteHash(pHash hash);
pItem getHashHead(pHash hash, int index);
void setHashHead(pHash hash, int index, pItem newVal);

// Stack functions
pStack newStack();
void deleteStack(pStack stack);
void addStackDepth(pStack stack);
void minusStackDepth(pStack stack);
pItem getCurDepthStackHead(pStack stack);
void setCurDepthStackHead(pStack stack, pItem newVal);

// Table functions
pTable initTable();
void deleteTable(pTable table);
pItem searchTableItem(pTable table, char* name);
boolean checkTableItemConflict(pTable table, pItem item);
void addTableItem(pTable table, pItem item);
void deleteTableItem(pTable table, pItem item);
void clearCurDepthStackList(pTable table);
// void addStructLayer(pTable table);
// void minusStructLayer(pTable table);
// boolean isInStructLayer(pTable table);
void printTable(pTable table);

// Global functions
static inline unsigned int getHashCode(char* name) {
    unsigned int val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if (i = val & ~HASH_TABLE_SIZE)
            val = (val ^ (i >> 12)) & HASH_TABLE_SIZE;
    }
    return val;
}

static inline void pError(ErrorType type, int line, char* msg) {
    printf("Error type %d at Line %d: %s\n", type, line, msg);
}

void traverseTree(pNode node);

// Generate symbol table functions
void ExtDef(pNode node);
void ExtDecList(pNode node, pType specifier);
pType Specifier(pNode node);
pType StructSpecifier(pNode node);
pItem VarDec(pNode node, pType specifier);
void FunDec(pNode node, pType returnType);
void VarList(pNode node, pItem func);
pMemberList ParamDec(pNode node);
void CompSt(pNode node, pType returnType);
void StmtList(pNode node, pType returnType);
void Stmt(pNode node, pType returnType);
void DefList(pNode node, pItem structInfo);
void Def(pNode node, pItem structInfo);
void DecList(pNode node, pType specifier, pItem structInfo);
void Dec(pNode node, pType specifier, pItem structInfo);
pType Exp(pNode node);
void Args(pNode node, pItem funcInfo);

#endif