////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     DNARepairer class definition
/// \authors   Sergey Shershakov, Leonid Dworzanski
/// \version   0.2.0
/// \date      06.02.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Определение класса "Починитель сломанных ДНК", DNARepairer.
///
////////////////////////////////////////////////////////////////////////////////

#ifndef BROKENDNA_DNAREPAIRER_H_
#define BROKENDNA_DNAREPAIRER_H_

#include "dna_element.h"
#include "linked_list.h"

#include <map>


/** \brief Робот-починитель сломанных ДНК
 *
 *  Умеет читать текстовый файл с отдельным фрагментами сломанных ДНК и склеивать их
 *  в правильном порядке, без мутаций!
 */
class DNARepairer {
public:
    // Открытые типы

    /// Класс представляет связанных список ДНК-узлов, которые содержат \c DNAElement объекты.
    /// Узел не то же самое, что значение, которое он несет!
    typedef xi::LinkedList<DNAElement> DNAChain;

    /// Класс представляет один узел, который содержат \c DNAElement.
    /// Список ДНК состоит из узлов \c NodeDNA.
    typedef xi::Node<DNAElement> NodeDNA;

    /// Класс представляет список цепочек ДНК.
    typedef xi::LinkedList<DNAChain> ListOfDNAChains;

    /// Класс представляет один узел-цепочку ДНК.
    typedef xi::Node<DNAChain> NodeDNAChain;

    /// Отображение идентификатора цепочки ДНК на список, представляющий эту цепочку
    typedef std::map< std::string, DNAChain* > Id2DnaMap;


public:
    /// Возвращает ссылку на хранилище цепочек ДНК
    ListOfDNAChains& getDNAStorage();


    /// Загружает отдельные «куски» цепочек ДНК из текстового файла, имя которого 
    /// приходит в качестве параметра.
    /// Если файл не может быть открыт, генерирует исключительную ситуацию \c std::runtime_error.
    void readFile(const std::string& filename);

    /// Осуществляет восстановление всех загруженных цепочек ДНК.
    void repairDNA();

    /// Выводит содержимое хранилища цепочек ДНК в стандартный поток вывода.
    void printDNAStorage();

private:
    
    /// Хранилище цепочек ДНК.
    ListOfDNAChains _dnaStorage;
}; // class DNARepairer



#endif // BROKENDNA_DNAREPAIRER_H_

