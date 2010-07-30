#pragma once

class UniqueObjectIdMgr
{
public:
	static unsigned int NewFlowPointId()
	{
		return the().newFlowPointIdInternal();
	}
	static unsigned int NewMCId()
	{
		return the().newMCIdInternal();
	}

	static void Reset()
	{
		the().resetInternal();
	}

private:
	static UniqueObjectIdMgr& the();
	unsigned int newFlowPointIdInternal();
    unsigned int newMCIdInternal();
	void resetInternal();

	UniqueObjectIdMgr(void);

	unsigned int m_flowPointIdCounter;
	unsigned int m_MCIdCounter;
};
