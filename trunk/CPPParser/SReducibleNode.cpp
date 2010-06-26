#include "SReducibleNode.h"

SReducibleNode::~SReducibleNode(void)
{
}

bool SReducibleNode::ShouldBeReduced()
{
	bool rc = true;

	//if (parent() && parent()->Type() == COMPOUND_STATEMENT) {
	//	rc = false;
	//}
	//else {
		switch(Type()) {
		case STATEMENT:
			rc = parent()->Type() == STATEMENT ||
				 parent()->Type() == STATEMENT_LIST;
			break;
		}
	//}

	return rc;
}
