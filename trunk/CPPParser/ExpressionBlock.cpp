#include "ExpressionBlock.h"

ExpressionBlock::ExpressionBlock(SNode* statement, FlowPoint* _parent) :
Block(statement, "Expression_Block", _parent)
{
}

ExpressionBlock::~ExpressionBlock()
{
}
