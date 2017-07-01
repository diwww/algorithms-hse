////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of an auxillary class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Note \c std:: prefix in definition of std::string's. Do not use 
/// \verbatim using namespace std; \endverbatim in any headers. Never!
///
///
////////////////////////////////////////////////////////////////////////////////


#ifndef SAFEARRAY_SUBJECT_H_
#define SAFEARRAY_SUBJECT_H_


#include <iostream> 
#include <string>

#include "safearray.h"


namespace xi {



/** \brief Класс, определяющий некоторую учебную дисциплину.
 *
 *  Большинство полей класса представлены в открытой области, т.к. у нас нет необходимости
 *  в их инкапсуляции в силу простоты задачи. В этом смысле класс подобен обычным структурам.
 *
 * <b>Вопрос для размышления:</b> как ввести такое же определение «предмета» с использованием
 * ключевого слова \c struct?
 */
class Subject {
public:

    /** \brief Максимальное число строк в описании дисциплины.
     *
     *  Ключевое слово \c const в действительности заставляет комлилятор выделить 
     *  место для размещения неизменяемого объекта (избежать этого можно с использованием
     *  «хака» с \c enum. Для того, чтобы не выделять под константу место в каждом
     *  экземпляре, мы помечаем его \c static -ом.
     */
    static const int MAX_LINES = 10;
                                        

public:

    /// Конструктор по умолчанию: инициализирует объекты пустыми строками, кроме массива описания.
    Subject() : name(""), title("") {}

    /// Конструктор инициализации \a именем и \a заголовком предмета.
    Subject(std::string name, std::string title) :
        name(name), title(title) {}


public:
    /** \brief Поле представляет название дисциплины.
    *
    *  Так как поле открытое, то не используем символ \c _ в начале имени объекта!
    */
    std::string name;

    std::string title;          ///< Поле заголовка дисциплины.

    /** \brief Поле описания дисциплины.
    *
    *  Создается в стеке (локально), несмотря на использования оператора =. Признак локальности
    *  объекта: нет ключевого слова \c new.
    */
    SafeArray<std::string> description = SafeArray<std::string>(MAX_LINES);


    /** \brief Дружественная оператор-функция вывода объекта в поток вывода.
     *
     *  Конструкция расширяет семантику объекта типа Subject, позволяя его использовать
     *  в потоковых операциях, например со стандартным потоком вывода: \verbatim
        Subject s...
        cout << s;   \endverbatim
     *  \param[in,out] str Поток вывода.
     *  \param[in] subj Константный объект-предмет, для вывода его текстового представления.
     *  \return Функция возвращает тот же поток \c str, чтобы ее можно было использовать ...
     *  <span style='color:orange'>подумать, зачем это нужно.</span>
     */
    friend std::ostream& operator<<(std::ostream& outs, const Subject& subj);
    
    /// \brief Дружественная оператор-функция для ввода объекта из потока.
    /// \see Subject::operator<<
    friend std::istream& operator>>(std::istream& ins, Subject& subj);
}; // class Subject


} // namespace xi


#endif // SAFEARRAY_SUBJECT_H_
