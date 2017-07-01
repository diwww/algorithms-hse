////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     SafeArray class definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Implementations" (namely, function body template definitions) for the methods declared 
/// in the classes below must be put in corresponding module named safearray.hpp.
///
///
////////////////////////////////////////////////////////////////////////////////

#ifndef SAFEARRAY_SAFEARRAY_H_
#define SAFEARRAY_SAFEARRAY_H_

#include <stdexcept>

namespace xi {


/** \brief Класс "защищенный массив"
 *
 *  Определяет класс-массив с доступом к элементам с контролем по индексу.
 */
template<class T>
class SafeArray
{


public:

    /** \brief Конструктор по умолчанию.
     *
     *  Не распределяет память, использует nullptr в качестве адреса массива.
     */
    SafeArray() : _storage(nullptr), _capacity(0)
    {
    }


    /** \brief Конструктор инициализации размером (число объектов) массива.
     *
     *  Распределяет память соответствующего размера, устанавливает значение емкости массива.
     * \param[in] cap Размер (емкость) массива.
     */
    SafeArray(size_t cap);


    /**
     * Copy constructor
     * @param other - object to copy
     */
    SafeArray(const SafeArray& other);


    /** \brief Деструктор.
     *
     *  Освобождает занимаемую массивом память.
     */
    ~SafeArray(); // destructor


    /** \brief Оператор индексирования.
     *
     *  Выполняет «защищенное» обращение к индивидуальным элементам массива.
     * Элемент возвращается по ссылке, и, таким образом, может находиться как в позиции \a rhv, так и в 
     * позиции \a lhv.
     * \param[in] k — индекс элемента. Если указанный индекс находится вне диапазона распределенной памяти,
     * генерируется исключительная ситуация \c std::out_of_range.
     * \return Возвращает ссылку на \a k -тый элемент массива.
     */
    T& operator[](size_t k);


    /** \brief Константная перегруженная версия метода Safearray::operator[].
     *
     *  Возвращает константную ссылку на элемент, которая может находиться только в позиции \a rhv.
     */
    const T& operator[](size_t k) const;


    /**
     * Overloaded assignment operator
     * @param other - reference to another SafeArray object
     * @return
     */
    SafeArray& operator=(const SafeArray& other);


    /// Возвращает "сырой" константный указатель на массив. Используется только для специальных целей
    /// в позиции \a rhv.
    const T* getRawPtr() const
    { return _storage; }

    /// Возвращает актуальный размер массива.
    size_t getCapacity() const;


protected:

    /**
     * Utility initialization function.
     * Allocates memory for _storage.
     * @param cap - capacity of an array
     */
    void init(size_t cap);

    /**
     * Utility copy function.
     * Performs deep copy of SafeArray objects.
     * This function should be called after init(other.getCapacity())
     * in order to allocate an array with size of another object's array.
     * @param other - reference to another SafeArray object
     */
    void copy(const SafeArray& other);

    /// Вспомогательный метод, проверяющий, что заданный индекс \a index не выходит за границу
    /// распределенной под массив памяти. Если индекс вне диапазона, генерирует
    /// исключительную ситуацию \c std::out_of_range.
    void checkBounds(size_t index) const;


private:
    /// Массив, представленный указателем на параметрический тип.
    T* _storage;

    /// Реальная память, распределенная под массив (в количестве элементов размера sizeof(T)).
    size_t _capacity;

}; // class Safearray<T>



} // namespace xi






// Here we simply add definitions from a file safearray.hpp. It's the same as we 
// simply put those defitions as a as a continuation of this very file.
// Not, that neither safearray.h nor safearray.hpp are compiled on their own.
#include "safearray.hpp"


#endif // SAFEARRAY_SAFEARRAY_H_
