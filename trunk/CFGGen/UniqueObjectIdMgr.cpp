
#include "UniqueObjectIdMgr.h"

UniqueObjectIdMgr::UniqueObjectIdMgr(void) :
	m_flowPointIdCounter(0), m_MCIdCounter(0)
{
}

UniqueObjectIdMgr& UniqueObjectIdMgr::the()
{
	static UniqueObjectIdMgr theMgr;
	return theMgr;
}

unsigned int UniqueObjectIdMgr::newFlowPointIdInternal()
{
	return ++m_flowPointIdCounter;
}

unsigned int UniqueObjectIdMgr::newMCIdInternal()
{
	return ++m_MCIdCounter;
}

void UniqueObjectIdMgr::resetInternal()
{
	m_flowPointIdCounter = 0;
	m_MCIdCounter = 0;
}