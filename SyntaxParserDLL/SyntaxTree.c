#include "SyntaxTree.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <crtdbg.h>

extern int column;
extern int row;

NodeData *createNode(nodeType nType)
{
	NodeData * newNode = (NodeData *) malloc(sizeof(NodeData));
	if(newNode == NULL){
		_ASSERT(!"Not Enough Memory");
		fprintf(stderr,"Error allocating memory\n");
	}
	newNode->m_type = nType;
	newNode->m_childCount = 0;
	newNode->m_childs = (NodeData **)malloc(sizeof(NodeData *));
	newNode->m_size = 1;
	newNode->m_row = row;
	newNode->m_column = column;
	return newNode;
}

void appendChild(NodeData *parent,NodeData *child)
{
	_ASSERT(parent != NULL);
	_ASSERT(child != NULL);

	if(parent->m_childCount == parent->m_size){
		//Need to reallocate with double size
		parent->m_childs = (NodeData **)realloc(parent->m_childs,sizeof(NodeData*) * parent->m_size *2);
		parent->m_size *=2;
	}
	parent->m_childs[parent->m_childCount] = child;
	parent->m_childCount++;
}

unsigned int getChildsCount(NodeData *parent)
{
	_ASSERT(parent != NULL);
	return parent->m_childCount;
}

NodeData *getChildAt(NodeData *parent , unsigned int idx)
{
	_ASSERT(parent != NULL);
	_ASSERT(idx < parent->m_childCount);

	return parent->m_childs[idx];
}