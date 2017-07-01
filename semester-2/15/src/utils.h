////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Вспомогательные определения (типов и др.)
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef BTREE_UTILS_H_
#define BTREE_UTILS_H_


// чтобы отметить метод нежелательным
#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED
#endif


namespace xi {

//==============================================================================
// Типы
//==============================================================================

typedef unsigned char Byte;
typedef unsigned short UShort;
typedef unsigned int UInt;



} // namespace xi






#endif // BTREE_UTILS_H_
