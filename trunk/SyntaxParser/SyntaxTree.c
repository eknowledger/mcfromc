#include "SyntaxTree.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <crtdbg.h>

Node *createNode(nodeType nType)
{
	Node * newNode = (Node *) malloc(sizeof(Node));
	if(newNode == NULL){
		_ASSERT(!"Not Enough Memory");
		fprintf(stderr,"Error allocating memory\n");
	}
	newNode->m_type = nType;
	newNode->m_childCount = 0;
	newNode->m_childs = (Node **)malloc(sizeof(Node *));
	newNode->m_size = 1;
	return newNode;
}

void appendChild(Node *parent,Node *child)
{
	_ASSERT(parent != NULL);
	_ASSERT(child != NULL);

	if(parent->m_childCount == parent->m_size){
		//Need to reallocate with double size
		parent->m_childs = (Node **)realloc(parent->m_childs,sizeof(Node*) * parent->m_size *2);
		parent->m_size *=2;
	}
	parent->m_childs[parent->m_childCount] = child;
	parent->m_childCount++;
}

unsigned int getChildsCount(Node *parent)
{
	_ASSERT(parent != NULL);
	return parent->m_childCount;
}

Node *getChildAt(Node *parent , unsigned int idx)
{
	_ASSERT(parent != NULL);
	_ASSERT(idx < parent->m_childCount);

	return parent->m_childs[idx];
}

void print(Node *root, unsigned int level)
{
	unsigned int nChilds = 0;
	unsigned int i=0, j=0;

	int ignore = 0;
	_ASSERT(root != NULL);
	switch(root->m_type)
	{
	case STATEMENT: 
		printf("STATEMENT ");
		break;
	case STATEMENT_LIST: printf("STATEMENT_LIST ");
		break;
	case CONDITION_IF: printf("IF ");
		break;
	case CONDITION_IF_ELSE: printf("IF_ELSE ");
		break;
	case EXPRESSION: printf("EXPRESSION ");
		break;
	case CONDITIONAL_EXPRESSION: printf("CONDITIONAL_EXPRESSION ");
		break;
	case EXPRESSION_STATEMENT: printf("EXPRESSION_STATEMENT ");
		break;
	case ASSIGNMENT_EXPR: printf("ASSIGNMENT_EXPRESSION ");
		break;
	case BLOCK: printf("BLOCK ");
		break;
	case NONE: printf("NONE ");
		break;
	case ID: printf("IDENTIFIER %s", root->m_name);
		break;
	case CONST_TYPE: printf("CONSTANT %d", root->m_constVal);
		break;
	case SELECTION_STATEMENT: printf("SELECTION_STATEMENT ");
		break;
	case ADD_EXPR: printf("ADD ");
		break;
	case SUB_EXPR: printf("SUBTRACT ");
		break;
	case MULT_EXPR: printf("MULTIPLY ");
		break;
	case DIV_EXPR: printf("DIV_EXPR ");
		break;
	case PRE_INCREMENT_UNARY_EXPR: printf("PRE_INCREMENT ");
		break;
	case PRE_DECREMENT_UNARY_EXPR: printf("PRE_DECREMENT ");
		break;
	case POST_INCREMENT_EXPR: printf("POST_INCREMENT ");
		break;
	case POST_DECREMENT_EXPR: printf("POST_INCREMENT ");
		break;
	case PREFIX_PLUS: printf("PREFIX_PLUS ");
		break;
	case PREFIX_MINUS: printf("PREFIX_MINUS ");
		break;
	case PREFIX_NOT: printf("PREFIX_NOT ");
		break;
	case LESS_THAN_EXPR: printf("LESS ");
		break;
	case GREATER_THAN_EXPR: printf("GREATER ");
		break;
	case LESS_EQ_THAN_EXPR: printf("LESS_OR_EQUAL ");
		break;
	case GREATER_EQ_THAN_EXPR: printf("GREATER_OR_EQUAL ");
		break;
	case DECLARATION: printf("DECLARATION ");
		break;
	case INIT_DECLARATOR_LIST: printf("INIT_DECLARATOR_LIST ");
		break;
	case TYPE_SPECIFIER: printf("TYPE_SPECIFIER %s", root->m_name);
		break;
	case PARAM_LIST: printf("PARAM_LIST ");
		break;
	case PARAM_DECLARATION: printf("PARAM_DECLARATION ");
		break;
	case DECLARATION_LIST: ignore = 1; printf("DECLARATION_LIST ");
		break;
	case TRANSLATION_UNIT: printf("TRANSLATION_UNIT ");
		break;
	case COMPOUND_STATEMENT: printf("COMPOUND_STATEMENT ");
		break;
	case WHILE_LOOP: printf("WHILE_LOOP ");
		break;
	case DO_WHILE_LOOP: printf("DO_WHILE_LOOP ");
		break;
	case FOR_LOOP: printf("FOR_LOOP ");
		break;
	default:
		printf("?? what ?? ");
		break;
	}

	printf("\n");

	//go over the children 
	nChilds = root->m_childCount;
	for(i=0; i<nChilds; i++) {
		for(j=0; j<level+1; j++) {
			printf("   ");
		}
		print(root->m_childs[i], level+1);
	}
}