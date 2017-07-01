#pragma once

#include <string>
#include <iostream>

using namespace std;

//=============================================================================
//== NetActivity ==============================================================
//== What user did what - i.e. the name of a user and the URL of its query   ==
//=============================================================================

class NetActivity
{
public:
	NetActivity(void);
	~NetActivity(void);

	// Name of the user
	string m_user;
	// URL of the host
	string m_host;
};

ostream & operator << (ostream & out, const NetActivity & na);

//=============================================================================
//== End of: NetActivity ======================================================
//=============================================================================
