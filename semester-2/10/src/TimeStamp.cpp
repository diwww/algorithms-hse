//#include "StdAfx.h"
#include "TimeStamp.h"

#include <iostream>
#include <ctime>

using namespace std;

// Default constructor
TimeStamp::TimeStamp(void)
{
    time_t tmp = time(0);
    m_time = *localtime(&tmp);
}

// Constructor with parameters
TimeStamp::TimeStamp(int year, int mon, int mday, int hour, int min, int sec)
{
    m_time.tm_year = year - 1900;
    m_time.tm_mon = mon;
    m_time.tm_mday = mday;
    m_time.tm_hour = hour;
    m_time.tm_min = min;
    m_time.tm_sec = sec;
    normalize();
}

// Destructor - who would have thought that?
TimeStamp::~TimeStamp(void)
{
}

// Auxiliary comparison function for time stamps
int TimeStamp::compareTo(const TimeStamp& another) const
{
    // ====================================================================
    // Result:
    // 0   --  equal
    // 1   --  this > anothers
    // -1  --  this < another
    // ====================================================================

    if (m_time.tm_year > another.m_time.tm_year) return 1;
    if (m_time.tm_year == another.m_time.tm_year)
    {
        if (m_time.tm_mon > another.m_time.tm_mon) return 1;
        if (m_time.tm_mon == another.m_time.tm_mon)
        {
            if (m_time.tm_mday > another.m_time.tm_mday) return 1;
            if (m_time.tm_mday == another.m_time.tm_mday)
            {
                if (m_time.tm_hour > another.m_time.tm_hour) return 1;
                if (m_time.tm_hour == another.m_time.tm_hour)
                {
                    if (m_time.tm_min > another.m_time.tm_min) return 1;
                    if (m_time.tm_min == another.m_time.tm_min)
                    {
                        if (m_time.tm_sec > another.m_time.tm_sec) return 1;
                        if (m_time.tm_sec == another.m_time.tm_sec)
                        {
                            return 0; // equal
                        }
                    }
                }
            }
        }
    }
    return -1;
}

// Checks if timestamps are equal
bool TimeStamp::operator==(const TimeStamp& another) const
{
    return (compareTo(another) == 0);
}

// Checks if timestamps are not equal
bool TimeStamp::operator!=(const TimeStamp& another) const
{
    return !(compareTo(another) == 0);
}

// Checks if left timestamp is earlier than the right one
bool TimeStamp::operator<(const TimeStamp& another) const
{
    return (compareTo(another) == -1);
}

// Checks if left timestamp is earlier than or equal to the right one
bool TimeStamp::operator<=(const TimeStamp& another) const
{
    int compare = compareTo(another);
    return (compare == 0 || compare == -1);
}

// Normalization function - needed for other functions to work
void TimeStamp::normalize(void)
{
    m_time.tm_isdst = -1;
    time_t tTime;
    tTime = mktime(&m_time);
    m_time = *localtime(&tTime);
}

// Read timestamp from the input stream in
// The format is: 2015.06.17 10:33:03
istream& operator>>(istream& in, TimeStamp& tsInput)
{
    char tmp;
    do
    {
        in >> tsInput.m_time.tm_year;
        if (!in) break;
        tsInput.m_time.tm_year -= 1900;
        in >> tmp; // skip .
        if (!in) break;
        in >> tsInput.m_time.tm_mon;
        if (!in) break;
        in >> tmp; // skip .
        if (!in) break;
        in >> tsInput.m_time.tm_mday;
        if (!in) break;
        in >> ws; // skip whitespaces
        if (!in) break;
        in >> tsInput.m_time.tm_hour;
        if (!in) break;
        in >> tmp; // skip :
        if (!in) break;
        in >> tsInput.m_time.tm_min;
        if (!in) break;
        in >> tmp; // skip :
        if (!in) break;
        in >> tsInput.m_time.tm_sec;
        if (!in) break;
        tsInput.normalize();
    } while (false);
    return in;
}

// Put timestamp to the output stream out
// The format is: 2015.06.17 10:33:03
const size_t SIZE_MAXSTRTIME = 25;  // 22 is the maximum length of such timestamps

ostream& operator<<(ostream& out, const TimeStamp& tsOutput)
{
    char buf[SIZE_MAXSTRTIME];
    strftime(buf, SIZE_MAXSTRTIME, "%Y.%m.%d %H:%M:%S", &tsOutput.m_time);
    out << buf;
    return out;
}
