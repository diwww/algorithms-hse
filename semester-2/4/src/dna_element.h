////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     DNAElement class definition
/// \authors   Sergey Shershakov, Leonid Dworzanski
/// \version   0.2.0
/// \date      06.02.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Определение класса "Элемент ДНК", DNAElement.
///
////////////////////////////////////////////////////////////////////////////////

#ifndef BROKENDNA_DNAELEMENT_H_
#define BROKENDNA_DNAELEMENT_H_

#include <iostream>
#include <string>

/** \brief Класс представляет собой простейшую структуру элемента ДНК.
 *
 *  Элемент ДНК включает следующие атрибуты: идентификатор (a..z), номер в цепочке, кислотное основание.
 */
class DNAElement
{
public:

    /// Конструктор по умолчанию — нужен контейнерам
    DNAElement();

    /// Конструктор инициализации строкой
    DNAElement(const std::string& description);

public:
    /**
     * \brief Инициализирует объект на основе переданной строки.
     *
     * Fill the fields id, number, base from a description in the format [name][number]:[type] where
     * [id] - a..z
     * [number] - the number of this element in the DNA sequence a1 a2 a3 a4 a5...
     * [base] - biological component of the element (A, C, T or G)
     *
     * So for description "a1:G"
     * name = "a";
     * number = 1;
     * type = "G";
     *
     * Throws invalid_argument if the format is wrong
     *                      or if the type of element is not in [A, C, T, G]
     */
    void readFromString(const std::string& description);

public:

    /// Идентификатор элемента (a..z).
    std::string id;


    /// Номер элемента в ДНК.
    int number;

    /// Кислотное основание.
//    enum Base
//    {
//        A, C, T, G
//    }
    std::string base;


}; // class DNAElement

#endif // BROKENDNA_DNAELEMENT_H_
