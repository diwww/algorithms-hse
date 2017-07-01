#pragma once

#include <iostream>
#include <ctime>

using namespace std;

//=============================================================================
//== TimeStamp ================================================================
//=============================================================================

class TimeStamp
{
	// struct tm - internal structure of <ctime> library
	struct tm m_time;

	// Auxiliary function for comparison of time stamps
	int compareTo (const TimeStamp & another) const;

	// Structure "struct tm" normalization
	// fills "week day" and similiar fields
	// This is needed for correct work of other
	// <ctime> functions
	void normalize (void);

public:
	TimeStamp(void);
	TimeStamp(int year, int mon = 1, int mday = 1, int hour = 0, int min = 0, int sec = 0);

	~TimeStamp(void);

	bool operator == (const TimeStamp & another) const;
	bool operator != (const TimeStamp & another) const;
	bool operator < (const TimeStamp & another) const;
	bool operator <= (const TimeStamp & another) const;

	friend istream &operator>>(istream &in, TimeStamp &tsInput);
	friend ostream &operator<<(ostream &out, const TimeStamp &tsOutput);
};

//=============================================================================
//== End of: TimeStamp ========================================================
//=============================================================================
