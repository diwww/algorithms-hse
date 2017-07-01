#pragma once

#include "OrderedList.h"
#include "SkipList.h"
#include "NetActivity.h"
#include "TimeStamp.h"

//=============================================================================
//== JournalNetActivity =======================================================
//=============================================================================

template <int numLevels>
class JournalNetActivity
{
	// typedef OrderedList<NetActivity, TimeStamp> TypeList;
	typedef SkipList<NetActivity, TimeStamp, numLevels> TypeList;

	// Log storage
	TypeList m_Journal;
public:
	JournalNetActivity(void);
	~JournalNetActivity(void);

	void dumpJournal(ostream & out);
	void parseLog(string fullpath);
	void outputSuspiciousActivities(string site, const TimeStamp & from, const TimeStamp & to) const;
};

//=============================================================================
//== End of: JournalNetActivity ===============================================
//=============================================================================
#include "JournalNetActivity.hpp"