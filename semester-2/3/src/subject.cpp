////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"
#include <string>


namespace xi {


std::ostream& operator<<(std::ostream& outs, const Subject& subj)
{
    outs << subj.name << ": " << subj.title << "\n";

    int index = 0;
    while (!subj.description[index].empty())
        outs << subj.description[index++] << "\n";

    return outs;
}

// Since line breaks are OS dependent
//
// For instance:
// Windows   Linux     Mac
// \r\n      \n        \r
//
// I used "dos2unix" util, which converts text files
// from Windows/Mac format to Unix format
//
// http://dos2unix.sourceforge.net/
std::istream& operator>>(std::istream& ins, Subject& subj)
{
    // Negative index is used to
    // read name and title first
    int index = -2;
    std::string temp = "";

    while (std::getline(ins, temp) && !temp.empty())
    {
        if (index == -2)
        {
            subj.name = temp;
            index++;
        }
        else if (index == -1)
        {
            subj.title = temp;
            index++;
        }
        else
            subj.description[index++] = temp;
    }

    return ins;
}


} // namespace xi

