#pragma once

typedef enum {
	CONDITION_IF, 
	CONDITION_IF_ELSE, 
	STATEMENT, 
	COMPOUND_STATEMENT,
	STATEMENT_LIST,
	EXPRESSION_STATEMENT,
	SELECTION_STATEMENT,
	EXPRESSION,
	CONDITIONAL_EXPRESSION,
	ASSIGNMENT_EXPR,
	LOGICAL_OR_EXPR,
	LOGICAL_AND_EXPR,
	EQUAL_EXPR,
	NOT_EQUAL_EXPR,
	LESS_THAN_EXPR,
	GREATER_THAN_EXPR,
	LESS_EQ_THAN_EXPR,
	GREATER_EQ_THAN_EXPR,
	AND_EXPR,
	ADD_EXPR,
	SUB_EXPR,
	MULT_EXPR,
	DIV_EXPR,
	MOD_EXPR,
	PRE_INCREMENT_UNARY_EXPR,
	PRE_DECREMENT_UNARY_EXPR,
	POST_INCREMENT_EXPR,
	POST_DECREMENT_EXPR,
	PREFIX_OP_UNARY_EXPR,
	PREFIX_PLUS,
	PREFIX_MINUS,
	PREFIX_NOT,
	BLOCK,
	NONE,
	ID,
	CONST_TYPE,
	STR_LITERAL,
	DECLARATION,
	INIT_DECLARATOR_LIST,
	TYPE_SPECIFIER,
	PARAM_LIST,
	PARAM_DECLARATION,
	DECLARATION_LIST,
	TRANSLATION_UNIT,
	WHILE_LOOP,
	DO_WHILE_LOOP,
	FOR_LOOP,
	NOP} nodeType;

typedef struct tagNode{
	nodeType m_type;
	unsigned int m_childCount;
	unsigned int m_size;
	char* m_name;
	int   m_constVal;
	int   m_row;
	int   m_column;
	struct tagNode **m_childs;
} NodeData;

#ifdef __cplusplus 
	extern "C"
	{
		int parseSyntax(char* filename, NodeData** root, char* errorLogFileName);
	}
#endif
