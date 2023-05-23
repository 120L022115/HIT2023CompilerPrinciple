#ifndef INTERHINCLUDE
#define INTERHINCLUDE
#include "semantic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct InterCodes_ *InterCodes;

struct Operand_
{
	enum
	{
		VARIABLE,
		CONSTANT,
		ADDRESS,
		LABEL_OP,
		RELOP1,
		DER
	} kind;
	union
	{
		char *name;
		int value;
	} u;
};

struct InterCode_
{
	enum
	{
		LABEL_IR,
		FUNCTION,
		ASSIGN,
		ADD1,
		SUB1,
		MUL1,
		DIV1,
		GOTO,
		IF_GOTO,
		RETURN1,
		DEC,
		ARG,
		CALL,
		PARAM,
		READ,
		WRITE
	} kind;
	union
	{
		struct
		{
			Operand op;
		} oneop;
		struct
		{
			Operand right, left;
		} assign;
		struct
		{
			Operand result, op1, op2;
		} binop;
		struct
		{
			Operand x, relop, y, z;
		} ifgoto;
		struct
		{
			Operand op;
			int size;
		} dec;
	} u;
};

struct InterCodes_
{
	InterCode code;
	struct InterCodes_ *prev, *next;
};
extern int tmpnum;
extern int labelnum;
extern FILE *out;
void translate_Exp(node *Exp, tablenode *sym_table, Operand place);
void translate_Args(node *Args, tablenode *sym_table, Operand *arg_list, int num);
void translate_Cond(node *Exp, Operand label_true, Operand label_false, tablenode *sym_table);
void translate_Stmt(node *Stmt, tablenode *sym_table);
void translate_StmtList(node *StmtList, tablenode *sym_table);
void translate_VarDec(node *VarDec, tablenode *sym_table);
void translate_Dec(node *Dec, tablenode *sym_table);
void translate_DecList(node *DecList, tablenode *sym_table);
void translate_Def(node *Def, tablenode *sym_table);
void translate_DefList(node *DefList, tablenode *sym_table);
void translate_CompSt(node *CompSt, tablenode *sym_table);
void translate_ParamDec(node *ParamDec, tablenode *sym_table);
void translate_VarList(node *VarList, tablenode *sym_table);
void translate_FunDec(node *FunDec, tablenode *sym_table);
void translate_ExtDecList(node *ExtDecList, tablenode *sym_table);
void translate_ExtDef(node *ExtDef, tablenode *sym_table);
void translate_ExtDefList(node *ExtDefList, tablenode *sym_table);
void translate_Program(node *Program, tablenode *sym_table);
void intergenerate(node *root, tablenode *sym_table, FILE *fp);

#endif