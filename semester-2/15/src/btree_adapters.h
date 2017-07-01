
/// \file
/// \brief     Адаптеры для некоторых типов для B-дерева.
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#ifndef BTREE_BTREEADAPTERS_H_
#define BTREE_BTREEADAPTERS_H_


#include <string>
#include <fstream>

#include "btree.h"


namespace xi {


/** \brief Класс свойств (черт, traits), определяющий необходимые всопомогательные компоненты,
 *  ассоциированные с типом данных T.
 *
 *  Введение в классы свойств см. https://accu.org/index.php/journals/442
 */
template <typename T>
struct BTreeAdapterTraits {


    //-----<объявляем нужные типы>-----

    /** \brief Тип неизменяемого аргумента: в большинстве случаев — конст. ссылка, но для некоторых 
        (интегральных в частности) типов дешевле передавать по значению.
     */
    typedef const T&                TArg;

    /** \brief Тип-ссыка основного типа ключа. */
    typedef T&                      TRef;


    /** \brief Тип результата получения ключа. В большинстве случаев по значению, 
     *  так как придется выполнять преобразование типов.
     *  // TODO: Для случаев, когда дорого дважды копировать, можно рассмотреть
     *  семантику перемещения (проверить со string)
     */
    typedef T                       TRes;


    /** \brief Тип для получение значения ключа через ссылку, передаваемую в параметр метода. */
    typedef T&                      TRefRes;


    /** \brief Описывает константный указатель на тип. */
    typedef const T*                TConstPtr;

    


    //-----<Константы>-----
    /** \brief Размер записи, по умолчанию определяется размером типа. 
     *
     *  Константу необходимо переопределять для сложных типов, например, string
     */
    static const UShort REC_SIZE = sizeof(T);


    //-----<статические методы>-----

    /** \brief Выполняет сравнение двух ключей дерева B-tree, как это указано 
     *  в компараторе BaseBTree::IComparator. Наивная реализация приводит указатели к
     *  соответствующим указателям на типы, разыменовывает их и сравнивает без учета размера.
     */
    //static int compare(const Byte* lhv, const Byte* rhv, UInt sz)
    static bool compare(const Byte* lhv, const Byte* rhv, UInt sz)
    {
        TConstPtr lp = (TConstPtr)lhv;
        TConstPtr rp = (TConstPtr)rhv;

        if (*lp < *rp)
            return true;
        return false;


        //if (*lp < *rp)
        //    return -1;
        //if (*lp > *rp)
        //    return 1;
        //return 0;
    }


    // простейшая реализация — побайтное сравнение
    static bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz)
    {
        TConstPtr lp = (TConstPtr)lhv;
        TConstPtr rp = (TConstPtr)rhv;

        for (UInt i = 0; i < sz; ++i)
            if (*lp != *rp)
                return false;

        return true;
    }

    /** \brief Дефолтная реализация метода преобразования потока байт в тип ключа. */
    static void raw2keyRes(const Byte* raw, TRef key)
    {
        key = *((const T*)raw);
    }

    /** \brief Дефолтная реализация метода преобразования ключа (типом) в поток байт. */
    static void key2Raw(Byte* raw, TArg key)
    {
        *((T*)raw) = key;
    }


}; //  class BTreeAdapterTraits



/** \brief Реализация компаратора по умолчанию, основанная на соответствуем методе compare()
 *  из класса свойств.
 */
template<
    typename T,                                 // тип данных, как его видит программист
    typename Traits = BTreeAdapterTraits<T>      // класс свойств ПО УМОЛЧАНИЮ
>
struct BTreeComparator : public BaseBTree::IComparator {
    
    virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz) override 
    {
        // по умолчанию — передаем право выполнить сравнение классу свойств
        return Traits::compare(lhv, rhv, sz);
    }

    // простейшая реализация — побайтное сравнение
    virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        return Traits::isEqual(lhv, rhv, sz);
    }

}; // struct BTreeComparator


/** \brief Адаптер для B-дерева, получающий тип ключа из параметра шаблона, а дополнительную
 *  информацию из специального класса свойств (traits).
 *
 *  elaborate
 */
template<   
    typename T,                                 // тип данных, как его видит программист
    typename Traits = BTreeAdapterTraits<T>,     // класс свойств ПО УМОЛЧАНИЮ
    typename Compar = BTreeComparator<T, Traits> // компаратор
        >
class BTreeAdapter {
public:
    // основные рабочие типы берем из класса свойств!

    
    typedef typename Traits::TArg       TArg;
    typedef typename Traits::TRes       TRes;


public:
    // основные рабочие константы берем из класса свойств!
    /** \brief Размер записи, по умолчанию определяется размером типа. */
    static const UShort REC_SIZE = Traits::REC_SIZE;


public:

    /** \brief Конструктор по умолчанию.
     *
     *  Для "открытия" дерева необходимо использовать метод open().
     */
    BTreeAdapter() { _btree.setComparator(&_comparator); };

    /** \brief Конструирует дерево и загружает его содержимое из файла \c fileName. */
    BTreeAdapter(const std::string& fileName) : BTreeAdapter()
    {
        openInternal(fileName);
    }


    /** \brief Конструирует дерево с заданным порядком \c order и и ассоциирует его с файлом \c fileName. */
    BTreeAdapter(UShort order, const std::string& fileName) : BTreeAdapter()
    {
        createInternal(order, fileName);
    }


    /** \brief Деструктор. */
    ~BTreeAdapter()
    {
        _btree.close();
    }

protected:
    BTreeAdapter(const BTreeAdapter&);                          ///< КК не доступен.
    BTreeAdapter& operator= (BTreeAdapter&);                    ///< Оператор присваивания недоступен.

public:

    /** \brief Конструирует дерево по типу конструктора BTreeAdapter(const std::string& fileName). */
    void open(const std::string& fileName)
    {
        openInternal(fileName);
    }


    /** \brief Конструирует дерево по типу конструктора BTreeAdapter(UShort order, const std::string& fileName). */
    void create(UShort order, const std::string& fileName)
    {
        createInternal(order, fileName);
    }

public:
    // основные методы доступа к типизированным объектам
    

    /** \brief Получает ключ по значению, номер ключа — \c num.
     *
     *  Политика относительно номера ключа та же, что и для метода
     *  BaseBTree::PageWrapper::getKey() .
     */
    //TRes getKeyWork(UShort num)
    TRes getKey(BaseBTree::PageWrapper& pw, UShort num)
    {
        // получаем указатель на сырые данные, представляющие ключ
        //Byte* kp = _btree.getWorkPage().getKey(num);
        Byte* kp = pw.getKey(num);
        

        TRes res;
        Traits::raw2keyRes(kp, res);

        return res;         // вот это чуть дороговато
    }

    /** \brief Устанавливает ключ по значению, номер ключа — \c num.
     *
     *  Политика относительно номера ключа та же, что и для метода
     *  BaseBTree::PageWrapper::getKey() .
     *  В зависимости от типа в адаптере, значение для установки передается либо по ссылке,
     *  либо по значению (опреляется типом TArg).
     */

    //void setKeyWork(UShort num, TArg key)
    void setKey(BaseBTree::PageWrapper& pw, UShort num, TArg key)
    {
        // получаем указатель на сырые данные, представляющие ключ
        //Byte* kp = _btree.getWorkPage().getKey(num);
        Byte* kp = pw.getKey(num);

        Traits::key2Raw(kp, key);
    }



//public:
//    // некоторые прокси-методы, для удо



public:
    // сеттеры/геттеры

    /** \brief Возвращает подлежащее дерево. */
    FileBaseBTree& getTree() { return _btree;  }

    /** \brief Возвращает константно подлежащее дерево. */
    const FileBaseBTree& getTree() const { return _btree; }


protected:

    /** \brief Реализует конструктор BTreeAdapter(const std::string& fileName). */
    void openInternal(const std::string& fileName)
    {
        _btree.open(fileName, &_comparator);

        // если открылось нормально, проверим, подходит ли дерево под параметры шаблона
        if (_btree.getRecSize() != REC_SIZE)                // размер записи
            throw std::runtime_error("Key size mismatch. Wrong file");

        //if (_btree.getOrder() != REC_SIZE)                // размер записи
        //    throw std::runtime_error("Key size mismatch. Wrong file")

    }

    /** \brief Реализует конструктор BTreeAdapter(UShort order, const std::string& fileName). */
    void createInternal(UShort order, const std::string& fileName)
    {
        _btree.create(order, REC_SIZE, fileName);
    }

protected:

    /** \brief Подлежащий объект-дерево. */
    FileBaseBTree _btree;

    /** \brief Компаратор, как отдельный объект */
    Compar _comparator;

}; // class Int32BTree 






//class BTreeIntAdapter : public BTreeAdapter<>
typedef BTreeAdapter<int> BTreeIntAdapter;





} // namespace xi






#endif // BTREE_BTREEADAPTERS_H_
