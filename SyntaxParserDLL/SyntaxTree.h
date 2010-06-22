#pragma once

#include "SyntaxParserInterface.h"

NodeData *createNode(nodeType type);
void appendChild(NodeData *parent,NodeData *child);
NodeData *getChildAt(NodeData *parent , unsigned int idx);
unsigned int getChildsCount(NodeData *parent);