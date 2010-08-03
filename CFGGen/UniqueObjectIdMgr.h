#pragma once

//////////////////////////////////////////////////////////////////////////
/// A a factory for unique numeric IDs given to Flow Points,
/// MC's and Undefined Values.
//////////////////////////////////////////////////////////////////////////
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

	static size_t NewUndefinedValueId()
	{
		return the().newUndefinedValueIdInternal();
	}

	static void Reset()
	{
		the().resetInternal();
	}

private:
	static UniqueObjectIdMgr& the();
	unsigned int newFlowPointIdInternal();
    unsigned int newMCIdInternal();
	size_t newUndefinedValueIdInternal();
	void resetInternal();

	UniqueObjectIdMgr(void);

	unsigned int m_flowPointIdCounter;
	unsigned int m_MCIdCounter;
	size_t m_UndefinedValueCounter;
};
