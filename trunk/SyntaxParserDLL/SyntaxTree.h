#pragma once

#include "SyntaxParserInterface.h"

Node *createNode(nodeType type);
void appendChild(Node *parent,Node *child);
Node *getChildAt(Node *parent , unsigned int idx);
unsigned int getChildsCount(Node *parent);
void print(Node *root, unsigned int level);