////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Определение классов B-дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Реализация соответствующих методов располагается в файле btree.cpp.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef BTREE_BTREE_H_
#define BTREE_BTREE_H_


#include <string>
#include <fstream>
#include <list>

#include "utils.h"


namespace xi
{


/** \brief Базовое B-дерево.
 *
 *  Класс включает базовые компоненты B-дерева, ориентированные на нетипизированную бинарную запись
 *  фиксированного размера (в байтах).
 *  Типизация подразумевается в наследующих классах.
 *
 *  Поле BaseBTree::_order определяет порядок дерева, которое будет содержать в узлах
 *  от <em>(_order - 1)<\em> до <em>(2* _order - 1)<\em> ключей (не считая корня, который
 *  для непустого дерева содержит от 1 ключа).
 *  Поле BaseBTree::_recSize определяет размер (длину) записи ключа в байтах. Запись обрабатывается,
 *  как нетипизированная, то есть массив байт размер \c _recSize. Для типизации необходимо
 *  наследовать этот класс и в производном осуществлять приведение к нужному типу.
 *
 *  Страницы везде нумеруются с 1-цы, а 0 — несуществующая страница (nullptr).
 */
class BaseBTree
{
public:

    //static const char* SIGN; // = "XIBT";
    //static const Byte SIGN_SIZE = 4;

#pragma pack(push, 1)                           

    /** \brief Структура заголовка файла.
     *
     *  Явно указываем компилятору, что структура должна быть упакована, т.е. никаких выравниваний
     *  полей. Этот параметр поддерживается VS и, если верить документации, gcc тоже:
     *  https://gcc.gnu.org/onlinedocs/gcc/Structure-Layout-Pragmas.html
     */
    struct Header
    {
        static const UInt VALID_SIGN = 0x54424958;  ///< правильная сигнатура
    public:
        Header() : order(0), recSize(0), sign(0)
        {}

        Header(UShort ord, UShort rs) :
                order(ord), recSize(rs), sign(VALID_SIGN)
        {
        }

    public:
        /** \brief Проверяет структуру на целостность и возвращает истину, если все ок.*/
        bool checkIntegrity();

    public:
        UInt sign;  // = 0x54424958;       // сигнатура
        UShort order;
        UShort recSize;
    }; // struct Header
#pragma pack(pop)

    /** \brief Смещение структуры заголовка известен уже на этапе компиляции. */
    static const Byte HEADER_OFS = 0;

    /** \brief Размер структуры заголовка известен уже на этапе компиляции. */
    static const Byte HEADER_SIZE = sizeof(Header);

    /** \brief Смещение для поля записи номера текущей свободной страницы (оно же — число страниц). */
    static const UInt PAGE_COUNTER_OFS = HEADER_SIZE;

    /** \brief Размер поля записи номера текущей свободной страницы. */
    static const UInt PAGE_COUNTER_SZ = 4;

    /** \brief Размер одного курсора (номера страницы). */
    static const UInt CURSOR_SZ = 4;


    /** \brief Смещение для поля записи номера корневой страницы. */
    static const UInt ROOT_PAGE_NUM_OFS = PAGE_COUNTER_OFS + PAGE_COUNTER_SZ; //HEADER_SIZE;

    /** \brief Размер поля записи номера корневой страницы. */
    static const UInt ROOT_PAGE_NUM_SZ = CURSOR_SZ; // 4;

    /** \brief Смещение первой реальной страницы. */
    static const UInt FIRST_PAGE_OFS = ROOT_PAGE_NUM_OFS + ROOT_PAGE_NUM_SZ;//PAGE_COUNTER_OFS + PAGE_COUNTER_SZ;

    /** \brief Смещение поля информации об узле/странице. */
    static const UInt NODE_INFO_OFS = 0;

    /** \brief Размер поля информации об узле/странице. */
    static const UInt NODE_INFO_SZ = 2;

    /** \brief Смещение области ключей в узле. */
    static const UInt KEYS_OFS = NODE_INFO_SZ;

    /** \brief Определяет максимальное возможное число для дерева любого порядка. */
    static const UShort MAX_KEYS_NUM = 32767;

    /** \brief Маска (поз.) для выделения флага, что нод — листовой. */
    static const UShort LEAF_NODE_MASK = 0x8000;

    ///** \brief Маска (нег.) для выделения флага, что нод — листовой. */
    //static const UShort LEAF_NODE_NMASK = ~LEAF_NODE_PMASK;

    //-/** \brief Определяет тип нода для страницы. */
    //enum NodeType
    //{
    //    nRegular,               ///< Обычный внутренний нод, обычное ограничение для числа ключей.
    //    nRoot,                  ///< Корень. Может содержить меньше ключей.
    //    nLeaf                   ///< Лист, нулевые курсоры на детей.
    //};

    /** \brief Структура-обертка над сырым (raw) массивом байт.
     *
     *  Предоставляет удобный интерфейс для доступа к индивидуальным значениям страницы/ключа.
     */
    class PageWrapper
    {
    public:
        PageWrapper(BaseBTree* tr);

        ~PageWrapper();

        /** \brief Перераспределяет память под рабочую страницу/узел. */
        void reallocData(UInt sz);

        /** \brief Обнуляет массив данных. */
        void clear();


        /** \brief Устанаваливает сразу два поля: число ключей в ноде \c keyNum и признак, что это  
         *  лист \c isLeaf.
         *  Проверяет на правильность число ключей. Кидает эксцепцию, если число ключей неправильное.
         */
        //void setKeyNumLeaf(UShort keysNum, NodeType nt);
        void setKeyNumLeaf(UShort keysNum, bool isRoot, bool isLeaf);

        /** \brief Устанаваливает число ключей в ноде \c keyNum.
         *  Проверяет на правильность число ключей. Кидает эксцепцию, если число ключей неправильное.
         */
        void setKeyNum(UShort keysNum, bool isRoot);
        //void setKeyNum(UShort keysNum, NodeType nt);

        /** \brief Перегруженный вариант метода setKeyNum(), самостоятельно опред. тип страницы. */
        void setKeyNum(UShort keysNum)
        {
            setKeyNum(keysNum, isRoot());   // getNodeType());
        }

        /** \brief Возвращает число ключей в ноде. */
        UShort getKeysNum() const;

        // /** \brief Определяет и возвращает тип нода/страницы. */
        //NodeType getNodeType() const;

        /** \brief Устанаваливает флаг, является ли нод узловым. */
        void setLeaf(bool isLeaf);


        /** \brief Возвращает истину, если нод — листовой, ложь иначе. */
        bool isLeaf() const;


        /** \brief Возвращает указатель на массив сырых данных с возможностью записи. */
        Byte* getData()
        { return _data; }

        /** \brief Возвращает константный указатель на массив сырых данных. */
        Byte* getData() const
        { return _data; }

        /** \brief Возвращает указатель на область памяти, соответствующую ключу номер \c num. 
         *
         *  Нумерация ключей — с нуля!!
         *  Если такого ключа нет, возвращает nullptr.
         */
        Byte* getKey(UShort num);

        /** \brief Копирует значение ключа в адрес \c dst из адреса \c src. 
         *
         *  Ключи могут принадлежать разным страницам, но размер страницы берется из текущей.
         */
        inline void copyKey(Byte* dst, const Byte* src);

        /** \brief Копирует значения неск. ключей, начиная с адреса \c dst, из адреса \c src.
         *  Число ключей определяется параметром \c num.
         *
         *  Ключи могут принадлежать разным страницам, но размер страницы берется из текущей.
         */
        inline void copyKeys(Byte* dst, const Byte* src, UShort num);

        /** \brief Копирует набор курсоров принципиально как и в методе copyKeys(). */
        inline void copyCursors(Byte* dst, const Byte* src, UShort num);


        /** \brief Перегруженный константный вариант метода getKey(). */
        const Byte* getKey(UShort num) const;

        /** \brief Возвращает курсор номер \c cnum. 
         *
         *  Для числа n ключей в ноде, там же будет (n+1) курсоров на дочерние элементы.
         *  Если \c cnum превышает (n+1) (нумерация с нуля), кидает исключение.
         */
        UInt getCursor(UShort cnum);

        /** \brief Возвращает указатель на соотв. курсор \c cnum. Для удобства... */
        Byte* getCursorPtr(UShort cnum);

        /** \brief Задает значение \c cval для курсора номер \c cnum. 
         *
         *  Если такого курсора нет, кидает исключение.
         */
        void setCursor(UShort cnum, UInt cval);


        /** \brief Для заданного номера курсора \c cnum возвращает его смещение в области курсоров.
         *
         *  Если такого курсора не существует, возвращает -1!
         */
        int getCursorOfs(UShort cnum) const;

        /** \brief Для заданного номер ключа (записи) \c num возвращает его смещение в области ключей.
         *
         *  Если такого ключа не существует, возвращает -1!
         */
        int getKeyOfs(UShort num) const;


        /** \brief Возвращает номер ассоциированной страницы. */
        UInt getPageNum() const
        { return _pageNum; }

        /** \brief Возвращает истину, если данная страница является корневой. */
        bool isRoot() const
        { return _tree->getRootPageNum() == getPageNum(); }
        //bool isRoot() const { return _tree->getRootPage() == this; }

        /** \brief Устанавливает данную страницу в дереве в качестве корневой. 
         *
         *  Флаг \c writeFlag определяет, нужно ли записать номер корневой страницы сразу в файл.
         *  Для (writeFlag), если под врапер не распределена страница в файле, будет 
         *  сформирована исключительная ситуация.
         */
        void setAsRoot(bool writeFlag = true);

        /** \brief Возвращает истину, если узел заполнен по максимуму. */
        bool isFull() const
        { return getKeysNum() == _tree->getMaxKeys(); };

    public:
        //----<Прокси методы для работы со страницами и IO>----

        /** \brief Распределяет в файле следующую по очереди страницу и ассоциирует врапер с нем.
         *
         *  Требования аналогичны методу BaseBTree::allocPage().
         */
        //void allocPage(UShort keysNum, NodeType nt)
        void allocPage(UShort keysNum, bool isLeaf)
        {
            _pageNum = _tree->allocPage(*this, keysNum, isLeaf);
            //_pageNum = _tree->allocPage(keysNum, nt, *this);
        }

        /** \brief Распределяет страницу для нового корня. */
        void allocNewRootPage()
        {
            _pageNum = _tree->allocNewRootPage(*this);
        }


        /** \brief Читает содержимое страницы номер \c pnum из файла в память текущего врепера.
        *
         *  Требования аналогичны методу BaseBTree::readPage();
         */
        void readPage(UInt pnum)
        {
            _tree->readPage(pnum, _data);
            _pageNum = pnum;
        }

        /** \brief Загружает в текущую страницу дочернюю страницу (номер \c chNum) страницы \c pw. 
         *
         *  Если номер курсора неправильный, или он не указывает на правильную страницу,
         *  кидает эксцепцию.
         */
        void readPageFromChild(PageWrapper& pw, UShort chNum);


        /** \brief Записывает страницу в файл. 
         *
         *  Для страницы не задан номер, полетит исключение.
         */
        void writePage();

    public:
        //----<Основные части алгоритма работы над b-деревом>----


        /** \brief Для не полностью заполненного текущего узла разделяет напополам его 
         *  полностью заполненного ребенка, определяемого курсором номер \c iChild на два нода/страницы.
         *  
         *  Параметр \c iChild представляет индекс курсора, который не может быть 0, что означает
         *  нарушение целостности (нет страницы с таким ребенком).
         *  Т.к. в процессе сплита один из ключей ребенка уйдет в этот родительский нод,
         *  данный нод должен иметь хотя бы один свободный слот под этот ключ. Если это не так,
         *  полетит исключительная ситуация.
         *  Для того, чтобы не было неопределенности по поводу индексов, заполненности и проч.
         *  в соответствующем ребенке, подразумеваем, что он полностью заполнен. Если это не так,
         *  кидаем искл. ситуацию.
         */
        void splitChild(UShort iChild);

        void insertNonFull(PageWrapper page, const Byte* k);

        /** \brief Вставляет в не полностью заполненный узел ключ k с учетом порядка.
         *
         *  Если узел полный, кидает исключение.
         *  Если для дерева не задан компаратор, кидает исключение.
         */
        void insertNonFull(const Byte* k);


        //-/** \brief Используя компаратор, определяет, является ли \c lhv левее (меньше) \c rhv, 
        // *  и если да, возвращает истину, иначе ложь.
        // *
        // *  Если компаратор не задан, кидает исключение.
        // */
        //bool lessThan(const Byte* lhv, const Byte* rhv);


        //Byte*& getData() { return _pageData;  }
    protected:
        PageWrapper(const PageWrapper&);                        ///< КК не доступен.
        PageWrapper& operator=(PageWrapper&);                  ///< Оператор присваивания недоступен.

    protected:
        Byte* _data;                                            ///< Сырой массив данных.
        BaseBTree* _tree;                                       ///< Указатель на само дерево, нужно оно.

        /** \brief Номер страницы в файле, ассоциированный с текущим (в)репером. 
         *
         *  Необходим для осуществления логической привязки обертки к реальной странице 
         *  диске. Привязка осуществляется при вычитке страницы или распределения новой.
         *  Значение 0 означает, что страница не привязана, что не позволит выполнить 
         *  операции чтения/записи на диск.
         */
        UInt _pageNum;

    }; // class PageWrapper

    friend class PageWrapper;

    /** \brief Интерфейс, определяющий операцию сравнения двух ключей дерева.
     *
     *  Конкретная реализация зависит от типов ключей и подразумевает явное
     *  приведение нетипизированного потока байт ключа к нужному значению.
     */
    class IComparator
    {
    public:

        /** \brief Выполняет сравнение двух ключей: левого \c lhv и правого \c rhv.
         *
         *  (Максимальный) размер ключей определяется параметром \c sz.
         *
         *  \returns истину, если <tt>lhv < rhv<\tt>; иначе ложь.
         *
         *  Если по какой-то причине ключи не могут быть сравнены (красное с квадратным),
         *  генерируется исключительная ситуация std::invalid_argument.
         */
        virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz) = 0;

        /** \brief Сравнивает два ключа и если они считаются эквивалентными, возвращает истину, 
          * иначе ложь.
          *
          * Если два ключа являются эквивалентными, это не обязательно значит, что подлежащие
          * под ними массивы побайтно равны.
          */
        virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz) = 0;

    protected:
        ~IComparator()
        {};

    }; // class IComparator



public:
    /** \brief Деструктор. */
    ~BaseBTree();

protected:
    /** \brief Конструирует новое B-дерево со структурой, определяемой переданными параметрами.
     *
     *  Создает новое дерево и записывает его в поток \c stream. Если файл существует, 
     *  он перезаписывается. Если файл не может быть открыт, генерируется исключительная ситуация.
     *  Параметр \c order определяет порядок дерева, параметр \c recSize определяет 
     *  размер (длину) записи ключа в байтах.
     */
    BaseBTree(UShort order, UShort recSize, IComparator* comparator, std::iostream* stream);

    /** \brief Конструирует заготовку под B-дерево, параметры которого будут прочитаны из
     *  существующего деревофайла.
     */
    BaseBTree(IComparator* comparator, std::iostream* stream);

    BaseBTree(const BaseBTree&);                        ///< КК не доступен.
    BaseBTree& operator=(BaseBTree&);                  ///< Оператор присваивания недоступен.

public:

    /** \brief Возвращает истину, если дерево открыто, ложь иначе. 
     *
     *  Базовый класс всегда будет говорить, что он не готов, чтобы избавиться
     *  в этом месте от ч.в. функции, которая при инициализации рабочих страниц
     *  в конструкторе класса (которые смотрят на его готовность) приводят к 
     *  pure virtual function called проблеме
     */
    virtual bool isOpen() const
    { return false; } // = 0;


    /** \brief Читает содержимое страницы номер \c pnum из файла в память в \c dst.
     *
     *  Методы вычитывает страницу побайтно, размер определяется getNodePageSize(). Вызывающий
     *  метод сам отстветсвеннен за распределение в необходимом объем и последующее 
     *  освобождение памяти.
     *  Если поток не открыт или такой страницы не существует, а именно — \c pnum >= getCurPage(), —
     *  генерируется исключительная ситуация.
     *
     *  Нумерация страниц с 1-цы.
     */
    void readPage(UInt pnum, Byte* dst);

    ///** \brief Читает страницу в рабочую обертку. Остальное аналогично readPage(). */
    //DEPRECATED void readWorkPage(UInt pnum);


    /** \brief Записывает в файл страницу номер \c pnum из памяти \c dst.
     *
     *  Требования к номеру страницы с товарищами такие же, как и у readPage().
     */
    void writePage(UInt pnum, const Byte* dst);


    ///** \brief Записывает рабочую страницу. Остальное аналогично writePage(). */
    //DEPRECATED void writeWorkPage(UInt pnum);



    /** \brief Распределяет в файле следующую по очереди страницу и возвращает ее номер. 
     *
     *
     *  Параметр \c keyNum определяет число ключей в ноде, а \c nt — тип нода, определяющий
     *  возможное число хранимых ключей и курсоры.
     *  Если поток не готов, генерирует исключительную ситуацию.
     */
    //UInt allocPage(UShort keysNum, NodeType nt, PageWrapper& pw);
    UInt allocPage(PageWrapper& pw, UShort keysNum, bool isLeaf = false);

    /** \brief Распределяет страницу для нового корня. */
    UInt allocNewRootPage(PageWrapper& pw);

    /** \brief Вставляет в дерево ключ k с учетом порядка.
     *
     */

    void insert(const Byte* k);

    Byte* search(PageWrapper& page, const Byte* k);

    /** \brief Для заданного ключа \c k ищет первое его вхождение в дерево по принципу эквивалентности. 
     *  Если ключ найден, возвращает указатель на подлежащий массив, иначе nullptr.
     */
    Byte* search(const Byte* k);

    /** \brief Для заданного ключа \c k ищет все его его вхождения в дерево по принципу эквивалентности.
     *  Каждый найденный ключ добавляется в переданный список ключей \c keys.
     *
     *  \returns число найденных элементов
     */
    int searchAll(const Byte* k, std::list<Byte*>& keys);

#ifdef BTREE_WITH_DELETION

    /** \brief Для заданного ключа \c k находит первое вхождение его в дерево по принципу эквивалентности
     *  и удаляет его из дерева.
     *
     *  \returns истину, если удален, ложь иначе.
     */    
    bool remove (const Byte* k);

    /** \brief Для заданного ключа \c k находит все вхождения его в дерево по принципу эквивалентности
     *  и удаляет их.
     *
     *  \returns Число удаленных узлов.
     */
    int removeAll(const Byte* k);


#endif

public:

    // сеттеры/геттеры

    /** \brief Возвращает порядок (order) \c b B-дерева. */
    UShort getOrder() const
    { return _order; }

    /** \brief Возвращает максимальное число ключей в ноде. Определяется порядком дерева: <em>(2* _order - 1)<\em>. */
    UInt getMaxKeys() const
    { return _maxKeys; }

    /** \brief Возвращает минимальное число ключей в ноде. Определяется порядком дерева: <em>(_order - 1)<\em>. */
    UInt getMinKeys() const
    { return _minKeys; }

    /** \brief Возвращает размер области под ключи, как максимальное число ключей в ноде на их размер.
     *  Поле требуется рассчитывать для определения смещения области указателей.
     */
    UInt getKeysSize() const
    { return _keysSize; }

    /** \brief Возвращает смещение области курсоров на дочерние элементы, как конец области ключей. */
    UInt getCursorsOfs() const
    { return _cursorsOfs; }


    /** \brief Возвращает размер всего узла, он же определяет размер страницы. */
    UInt getNodePageSize() const
    { return _nodePageSize; }

    /** \brief Возвращает длину записи ключа. */
    UShort getRecSize() const
    { return _recSize; }

    /** \brief Возвращает номер последней записанной страницы и оно же — число записанных страниц. 
     *
     *  Страницы нумеруются с 1-цы (реальные), число 0 означает специальный случай — нулевой курсор,
     *  т.е. не указывает на страницу, а значит ни одной страницы не записано.
     */
    UInt getLastPageNum() const
    { return _lastPageNum; }


    /** \brief Возвращает ненулевой номер страницы корня дерева или 0, если в д. нет ни одного узла. */
    UInt getRootPageNum() const
    { return _rootPageNum; }


    //--- страницы в оперативной памяти
    /** \brief Возвращает ссылку на текущую корневую страницу. */
    PageWrapper& getRootPage()
    { return _rootPage; }

    /** \brief Константный вариант метода getRootPage(). */
    const PageWrapper& getRootPage() const
    { return _rootPage; }

    //-/** \brief Возвращает указатель на текущую корневую страницу. */
    //PageWrapper* getRootPage() { return _rootPage; }

    ///** \brief Возвращает константный указатель на текущую корневую страницу. */
    //const PageWrapper* getRootPage() const { return _rootPage; }


    ///** \brief Возвращает ссылку на текущую рабочую страницу. */
    //PageWrapper& getWorkPage() { return _workPage; }

    ///** \brief Константный вариант метода getWorkPage(). */
    //const PageWrapper& getWorkPage() const { return _workPage; }


    //PageWrapper& getWP0() { return _wp0; }  ///< DONE:
    //PageWrapper& getWP1() { return _wp1; }  ///< DONE:
    //PageWrapper& getWP2() { return _wp2; }  ///< DONE:

    /** \brief Задает компаратор для дерева. */
    void setComparator(IComparator* c)
    { _comparator = c; }

    /** \brief Возвращает компаратор. */
    IComparator* getComparator() const
    { return _comparator; }


protected:

    /** \brief Загружает дерево из потока.
     *
     *  Включая корневую страницу.
     */
    void loadTree();

    /** \brief Загружает корневую страницу в одну из рабочих страниц, переданных параметром \c pw. 
     *
     *  Если файле информации о корневой странице не значится, кидает исключение.
     */
    void loadRootPage();    // PageWrapper& pw);

    /** \brief Создает дерево и записывает его в поток.
     *
     *  Создает дерево с нуля, создает страницу под корень и записывает их в поток.
     */
    void createTree(UShort order, UShort recSize);

    /** \brief Создает и записывает корневую страницу при создании дерева с нуля. */
    void createRootPage();

    /** \brief Метод проверяет, открыт ли поток (готово ли дерево), если нет, кидает исключение. */
    void checkForOpenStream();

    /** \brief Для заданного порядка и переданного числа ключей определяет, соответствует ли оно
     *  ограничениям на число ключей в ноде для данного порядка, или нет.
     *  
     *  \c keysNum — запрашиваемое число ключей.
     *  \с isRoot — признак, что это корень. Если истина, минимальное число ключей 
     *  может быть 1 (0?), в отличие от всех других нод.
     *  \returns true, если соответствует.
     */
    //bool checkKeysNumber(UShort keysNum, NodeType nt); // bool isRoot);
    bool checkKeysNumber(UShort keysNum, bool isRoot);


    /** \brief Вариант метода checkKeysNumber(), кидающий исключение для неправильного числа ключей. */
    void checkKeysNumberExc(UShort keysNum, bool isRoot);
    //void checkKeysNumberExc(UShort keysNum, NodeType nt); // bool isRoot);


    /** \brief Записывает в поток (в текущую позицию!) заголовок дерева. */
    void writeHeader();

    /** \brief Читает из потока заголовок дерева. */
    void readHeader(Header& hdr);


    // /** \brief Записывает в потоктекущее значение числа страниц (последняя записанная). */
    //void writePageCounter() { writePageCounter(_lastPageNum); }


    /** \brief Записывает в поток поле \c pc, обозначающее число страниц (последняя записанная). */
    void writePageCounter(); // UInt pc);

    /** \brief Читает из потока поле \c pc, обозначающее число страниц (последняя записанная), в поле. */
    //UInt 
    void readPageCounter();


    /** \brief Осуществляет запись номера страницы/нода, соответствующего корню дерева. */
    void writeRootPageNum(); // UInt rpn);

    // /** \brief Запись текущего номера корневой страницы. */
    //void writeRootPageNum() { writeRootPageNum(_rootPageNum); }

    /** \brief Читает из потока номер страницы/нода, соответствующего корню дерева, в поле. */
    //UInt 
    void readRootPageNum();

    /** \brief Устаналивает значение номера корневой страницы. 
     *
     *  Если флаг \c writeFlag == true, тут же записывает этот номер в файл.
     */
    void setRootPageNum(UInt pnum, bool writeFlag = true);

    /** \brief Задает порядок дерва и пересчитывает связанные значения. */
    void setOrder(UShort order, UShort recSize);

    /** \brief Перераспределяе память для/под рабочие страницы. */
    void reallocWorkPages();


    /** \brief Закрытая и основная часть метода readPage(). */
    void readPageInternal(UInt pnum, Byte* dst);

    /** \brief Закрытая и основная часть метода writePage(). */
    void writePageInternal(UInt pnum, const Byte* dst);

    /** \brief Позиционируется на смещение в файле, соответствующее номеру страницы \c pnum. */
    void gotoPage(UInt pnum);

    /** \brief Закрытая и основная часть метода allocPage(). */
    UInt allocPageInternal(PageWrapper& pw, UShort keysNum, bool isRoot, bool isLeaf);
    //UInt allocPageInternal(UShort keysNum, NodeType nt, PageWrapper& pw); // bool isLeaf);

    /** \brief Выполняет "сброс" параметров дерева.
     *
     *  Реализуется для дочерних классов, которые могут "переоткрывать" дерево.
     */
    void resetBTree();


protected:

    /** \brief Определяет порядок (order) \c b B-дерева. */
    UShort _order;

    /** \brief Максимальное число ключей в ноде. Определяется порядком дерева: <em>(2* _order - 1)<\em>. */
    UInt _maxKeys;

    /** \brief Минимальное число ключей в ноде. Определяется порядком дерева: <em>(_order - 1)<\em>. */
    UInt _minKeys;

    /** \brief Определяет размер области под ключи, как максимальное число ключей в ноде на их размер. 
     *  Поле требуется рассчитывать для определения смещения области указателей.
     */
    UInt _keysSize;

    /** \brief Определяет смещение области курсоров на дочерние элементы, как конец области ключей. */
    UInt _cursorsOfs;


    /** \brief Размер всего узла, он же определяет размер страницы. */
    UInt _nodePageSize;


    /** \brief Определяет длину записи ключа. */
    UShort _recSize;

    /** \brief Номер текущей свободной страницы и оно же — число записанных страниц + 1. */
    UInt _lastPageNum;

    /** \brief Хранит номер текущей страницы с корневым элементом дерева. */
    UInt _rootPageNum;


    // /** \brief Минимальное число элементов — определяется порядком (order - 1) */
    //UWord _minKeyNum;

    /** \brief Поток, ассоциированный с объектом, куда дерево пишется и откуда читается. */
    std::iostream* _stream;


    /** \brief Обертка над корневой страницей, которая всегда в памяти хранится. */
    PageWrapper _rootPage;

    ///** \brief Указатель на корневую страницу, если существует. 
    // *
    // *  Для nullptr — нет корневой страницы, дерево не инициализировано или пусто.
    // */
    //PageWrapper* _rootPage;

    ///** \brief Обертка над текущей рабочей страницей, предоставляющая интерфейс для удобного доступа. */
    //PageWrapper _workPage;


    //PageWrapper _wp0;               ///< TODO: рабочая страница 0
    //PageWrapper _wp1;               ///< TODO: рабочая страница 1
    //PageWrapper _wp2;               ///< TODO: рабочая страница 2




    /** \brief Компаратор для сравнения ключей. */
    IComparator* _comparator;


}; // class BaseBTree





/** \brief B-дерево, основанное на файловом потоке.
 *
 *  Конкретизирует понятие дерево на случай использования файла для хранения.
 */
class FileBaseBTree : public BaseBTree
{
public:
    /** \brief Конструктор по умолчанию.
     *
     *  Для "открытия" дерева необходимо использовать метод open().
     */
    FileBaseBTree();


    /** \brief Конструирует новое B-дерево со структурой, определяемой переданными параметрами.
     *
     *  Создает новое дерево и записывает его в файл \c fileName. Если файл существует,
     *  он перезаписывается. Если файл не может быть открыт, генерируется исключительная ситуация.
     *
     *  Конструктор эквивалентен созданию объекта с параметрами по умолчанию с последующим
     *  открытием методом open().
     */
    FileBaseBTree(UShort order, UShort recSize, IComparator* comparator, const std::string& fileName);


    /** \brief Конструирует дерево на основе существующего файла B-дерева.
     *
     *  Если файл не может быть открыт, прочитан или содержит неверную структуру,
     *  кидает исключительную ситуацию.
     */
    FileBaseBTree(const std::string& fileName, IComparator* comparator);

    /** \brief Деструктор.
     *
     *  Не забывает закрыть открытые файловые потоки.
     */
    ~FileBaseBTree();

protected:
    FileBaseBTree(const FileBaseBTree&);                        ///< КК не доступен.
    FileBaseBTree& operator=(FileBaseBTree&);                  ///< Оператор присваивания недоступен.

public:

    /** \brief Открывает неактивное к моменту вызова метода дерево по типу конструктора с таким же
     *  набором параметров.
     *  Если дерево уже открыто, генерирует исключительную ситуацию.
     */
    void create(UShort order, UShort recSize, //IComparator* comparator, 
                const std::string& fileName);

    /** \brief Загружает дерево из файла.
     *
     *  Если дерево уже открыто, генерирует исключительную ситуацию.
     */
    void open(const std::string& fileName); // , IComparator* comparator);

    /** \brief Закрывает открытое дерево.
     *
     *  Закрывает дерево и ассоциированные с ним потоки.
     *  Если дерево не открыто, просто ничего не делает (искл. НЕ генерирует для удобства).
     */
    void close();

public:

    // /** \brief Возвращает истину, если дерево открыто, ложь иначе. */
    //\copydoc
    virtual bool isOpen() const override;

protected:

    /** \brief Открывает поток и подготавливает дерево. В отличие от соответствующего конструктора
     *  и метода open() не выполняет никаких проверок, которые подразумеваются быть сделанными там.
     */
    void createInternal(UShort order, UShort recSize, // IComparator* comparator, 
                        const std::string& fileName);

    /** \brief Загружает дерево из файла \c fileName.
     *
     *  Если файл не может быть открыт, прочитан или содержит неверную структуру,
     *  кидает исключительную ситуацию.
     */
    void loadInternal(const std::string& fileName); // , IComparator* comparator);


    /** \brief Закрывает файловые потоки, ассоциированные с деревом.
     *
     *  Выполняет инициализацию объекта к такому состоянию, чтобы можно было повторно открыть.
     */
    void closeInternal();

    /** \brief Проверяет параметры дерева и, если они некорректны, киает исключение. */
    void checkTreeParams(UShort order, UShort recSize);

protected:
    /** \brief Имя файла с деревом. */
    std::string _fileName;

    /** \brief Файловый поток, храняющий дерево. */
    std::fstream _fileStream;
}; // class FileBaseBTree






} // namespace xi






#endif // BTREE_BTREE_H_
