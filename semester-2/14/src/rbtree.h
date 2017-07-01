////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Определение классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" соответствующих методов располагается в файле rbtree.hpp.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef RBTREE_RBTREE_H_
#define RBTREE_RBTREE_H_




namespace xi {



// Предварительное описание
template <typename Element, typename Compar>
class RBTree;



/** \brief Класс-интерфейс, описывающий коллбек-слушателя для событий, происходящих с деревом.
 *
 *  Реализация этого интерфейса и передача его 
 */
template <typename Element, typename Compar>
class IRBTreeDumper {
public:
    // Объявление типов дерева и узла для упрощения доступа
    typedef RBTree<Element, Compar> TTree;
    typedef typename RBTree<Element, Compar>::Node TTreeNode;
public:
    /** \brief Типы событий, на которые реагируем дампер. */
    enum RBTreeDumperEvent {
        DE_AFTER_LROT,                  ///< После осуществления левого поворота.
        DE_AFTER_RROT,                  ///< После осуществления правого поворота.
        DE_AFTER_BST_INS,               ///< После вставки элемента в BST без перебалансировки.
        DE_AFTER_INSERT,                ///< После вставки элемента в RBT и перебалансировки.
        DE_AFTER_RECOLOR1,              ///< После перекраски папы, дедушки и дяди по случаю 1.
        DE_AFTER_RECOLOR3D,             ///< После перекраски папы случаю 3.
        DE_AFTER_RECOLOR3G,             ///< После перекраски дедушки случаю 3.

        // если дерево строится с операцией удаления, тогда еще и ...
#ifdef RBTREE_WITH_DELETION
        DE_AFTER_BST_REMOVE,            ///< После удаления элемента из BST без перебалансировки.
        DE_AFTER_REMOVE,                ///< После удаления элемента из RBT и перебалансировки.

        // TODO: сюда при желании можно добавить события, связанные с перекрасной при удалении
#endif
    };
public:
    // события

    /** \brief Событие, происходящее с деревом. */
    virtual void rbTreeEvent(RBTreeDumperEvent ev, TTree* tr, TTreeNode* nd) = 0;


protected:
    ~IRBTreeDumper() {};
}; // class RBTreeDumper


template<typename, typename>
class RBTreeTest;


/** \brief Главный класс красно-черного дерева.
 *
 *  \tparam Element Определяет тип элементов, хранимых в дереве (тж. ключ, key).
 *  \tparam Compar Функтор, выполняющий сравнение элементов для определения порядка. По умолчанию
 *  реализуется стандартным компаратором \c std::less.
 */
template <typename Element, typename Compar = std::less<Element> >
class RBTree {
public:
    // Типы на экспорт
    /** \brief Тип цвета узла дерева. */
    enum Color
    {
        BLACK,
        RED
    };

    /** \brief Узел КЧД.
     *
     *  Большая часть элементов класса является закрытой для внешнего мира и доступной только
     *  для самого узла и его потомков. Это сделано с целью инкапсуляции, а само дерево объявлено
     *  по отношению к данному классу дружественным, чтобы оно имело доступ к своим узлам.
     */
    class Node {    
        // Дерево имеет полный доступ к реализации узла!
        friend class RBTree<Element, Compar>;

        // Специальный подход, позволяющий следующему (шаблонному) классу иметь доступ 
        // к закрытым членам для их тестирования.
        template<typename, typename>
        friend class RBTreeTest;

    public:

        /** \brief Определяет варианты принадлежности узла относительно родителя. */
        enum WhichChild {
            LEFT,               ///< левый потомок
            RIGHT,              ///< правый потомок
            NONE                ///< вообще не потомок
        };
    public:

        /** \brief Возвращает константный указатель на левый дочерний узел. */
        const Node* getLeft() const { return _left; }

        /** \brief Возвращает константный указатель на правый дочерний узел. */
        const Node* getRight() const { return _right; }

        /** \brief Возвращает константный указатель на родительский узел. */
        const Node* getParent() const { return _parent; }

        /** \brief Возвращает цвет узла. */
        Color getColor() const { return _color;  }

        /** \brief Возвращает истину, если узел черный, иначе ложь. */
        bool isBlack() const { return _color == BLACK;  }

        /** \brief Возвращает истину, если узел красный, иначе ложь. */
        bool isRed() const { return _color == RED; }


        // хелперные методы получения доп информации о ноде

        /** \brief Возвращает истину, если есть отец и он красный. */
        bool isDaddyRed() const
        {
            if (!_parent)
                return false;
            return (_parent->_color == RED);
        }

        /** \brief Возвращает истину, если у нода есть предок, для которого нод является левым ребенком. 
         *  Во всех остальных случаях (нет предка или правый) — ложь.
         */
        bool isLeftChild() const
        {
            if (!_parent)
                return false;
            return (_parent->_left == this);
        }

        /** \brief Возвращает истину, если у нода есть предок, для которого нод является правым ребенком.
         *  Во всех остальных случаях (нет предка или левый) — ложь.
         */
        bool isRightChild() const
        {
            if (!_parent)
                return false;
            return (_parent->_right == this);
        }

        /** \brief Определяет, является ли данный узел потомком родителя — левым, правым или не потомком. */
        WhichChild getWhichChild() const
        {
            if (!_parent)
                return NONE;
            if (_parent->_left == this)
                return LEFT;
            return RIGHT;
        }


        /** \brief Возвращает константную ссылку на элемент/ключ, храняющийся в узле. */
        const Element& getKey() const { return _key; }
    protected:

        Node(const Element& key = Element(),
            Node* left = nullptr,
            Node* right = nullptr,
            Node* parent = nullptr,
            Color col = BLACK)
            : _key(key), _left(left), _right(right), _parent(parent), _color(col)
        {
            // если переданы дочерние элементы, устанавливаем себя их родителем, но
            // но не говорим родителю, что мы его дочерь!
            if (_left)
                _left->_parent = this;

            if (_right)
                _right->_parent = this;
        }

        ~Node();                                ///< Деструктор нода гарантированно грохнет всех потомков.

    protected:
        Node(const Node&);                      ///< КК не доступен.
        Node& operator= (Node&);                ///< Оператор присваивания недоступен.

    protected:
        /** \brief Устанавливает левого потомка в \c lf. Если потомок не ноль, делает 
         *  для него текущий нод родителем, а у его предка отключает дочернюю связь.
         */
        Node* setLeft(Node* lf);
         
        /** \brief Устанавливает правого потомка в \c rg аналогично левому.
         *
         *  <b style='color:orange'>Для реализации студентами.</b>
         */
        Node* setRight(Node* rg);

        /** \brief Делает узел черным. */
        void setBlack() { _color = BLACK; }

        /** \brief Делает узел красным. */
        void setRed() { _color = RED; }


        // хелперные методы получение родственничков


        /** \brief Еще один метод получение папочки: если он есть, возвращает по значению и устанавливает 
         *  значение флага isLeftChild в истину, если данный ребенок левый, иначе в ложь. Если папы нет, 
         *  возвращает null
         */
        Node* getDaddy(bool& isLeftChild)
        {
            if (!_parent)
                return nullptr;

            // определяем, левый ли this детеныш
            isLeftChild = (_parent->_left == this);

            return _parent;
        }

        /** \brief Возвращает ребенка этого узла: (isLeft) — левого, иначе правого. */
        Node* getChild(bool isLeft)
        {
            return isLeft ? _left : _right;
        }

        /** \brief Проверяет, является ли данный узел "правильным" потомком для существующего 
         *  (без проверки) родителя. Для (isLeft) "правильным" является левый узел, для 
         *  (!isLeft) — правый.
         *  \returns возвращает истину, если проверяемый узел является "правильным".
         */
        bool isSpecificChildPrv(bool isLeft) const 
        { 
            if (isLeft)         // проверяем, является ли левым узлом
                return (_parent->_left == this);
                                // иначе проверяем, является ли правым узлом
            return (_parent->_right == this);
        }



    protected:
        Element _key;                           ///< Несомая узлом информация.
        Color   _color;                         ///< Цвет элемента.

        Node*   _parent;                        ///< Родитель узла.
        Node*   _left;                          ///< Левый потомок.
        Node*   _right;                         ///< Правый потомок.
    }; // class RBTree::Node

    friend class Node;

public:
    RBTree();                                   ///< Конструктор по умолчанию.    
    ~RBTree();                                  ///< Деструктор.

public:
    // Основные операции над деревом

    /** \brief Вставляет элемент \c key в дерево.
     *
     *
     *  <b style='color:orange'>Для реализации студентами.</b>
     *
     *  Т.к. дубликаты не допустимы, элемента с ключом \c key в дереве быть не должно. Если
     *  же такой элемент уже существует, генерируется исключительная ситуация \c std::invalid_argument.
     */
    void insert(const Element& key);

#ifdef RBTREE_WITH_DELETION

    /** \brief Ищет узел, соответствующий ключу \c key, и удаляет узел из дерева 
     *  с последующей перебалансировкой. 
     *  
     *  <b style='color:orange'>Для реализации студентами.</b>
     *
     *  Если соответствующего ключа нет в дереве, генерирует исключительную ситуацию \c std::invalid_argument.
     */
    void remove(const Element& key);   
#endif

    /** \brief Ищет элемент \c key в дереве и возвращает соответствующий ему узел. 
     *
     *  <b style='color:orange'>Для реализации студентами.</b>
     *
     *  \returns узел элемента \c key, если он есть в дереве, иначе \c nullptr.
     */
    const Node* find(const Element& key);

    /** \brief Возвращает истину, если дерево пусто, ложь иначе. */
    bool isEmpty() const { return _root == nullptr; }

    /** \brief Возвращает неизменяемый указатель на корневой элемент. */
    const Node* getRoot() const { return _root;  }
public:
    // Отладочные операции
    
    /** \brief Устанавливает отладочный дампер. */
    void setDumper(IRBTreeDumper<Element, Compar>* dumper)
    {
        _dumper = dumper;
    }

    /** \brief Сбрасывает отладочный дампер. */
    void resetDumper()
    {
        _dumper = nullptr;
    }


protected:


    /** \brief Добавляет новый узел в дерево, как в обычном BST. 
     *
     *  <b style='color:orange'>Для реализации студентами.</b>
     *
     *  Дубликаты не разрешены, исключение то же, что и у \c insert().
     *  \return Указатель на новодобавленный элемент.
     */
    Node* insertNewBstEl(const Element& key);

    /** \brief Выполняет перебалансировку дерева после добавления нового элемента в узел \c nd. 
     *
     *  <b style='color:orange'>Для реализации студентами.</b>
     */
    void rebalance(Node* nd);


    /** \brief Выполняет перебалансировку локальных предков узла \c nd: папы, дяди и дедушки.
     *  
     *  <b style='color:orange'>Метод может быть реализован студентами в порядке декомпозиции.</b>
     *
     *  \returns Новый актуальный узел, для которого могут нарушаться правила.
     */
    Node* rebalanceDUG(Node* nd);

    /** \brief Удаляет нод со всеми его потомками, освобождая память из-под них. */
    void deleteNode(Node* nd);

    /** \brief Вращает поддерево относительно узла \c nd влево.
     *
     *  <b style='color:orange'>Для реализации студентами.</b>
     *
     *  Требование: правый ребенок узла \c nd не должен быть null, иначе генерируется
     *  исключительная ситуация \c std::invalid_argument.
     * 
     *  \return Если у текущего узла был предыдущий левый, возвращает его (для дальнейшего использования),
     *  иначен возвращает \c nullptr.
     */
    void rotLeft(Node* nd);

    /** \brief Вращает поддерево относительно узла \c nd вправо. Условия и ограничения 
      * аналогичны (симметрично) левому вращению. 
      *
      *  <b style='color:orange'>Для реализации студентами.</b>
      */
    void rotRight(Node* nd);


protected:
    RBTree(const RBTree&);                      ///< КК не доступен.
    RBTree& operator= (RBTree&);                ///< Оператор присваивания недоступен.

protected:
    Compar _compar;                             ///< Компаратор сравнения двух элементов.

protected:
    // Структура дерева

    /** \brief Реальный корневой элемент дерева. Если \c nullptr, значит дерево пусто. 
     *
     *  NB: иногда используется реализация, где корень дерева хранится не непосредственно
     *  в виде выделенного узла, а в виде правого потомка специального сторожевого (sentinel)
     *  элемента псевдо-корня. Это позволяет несколько упростить запись алгоритма за счет того,
     *  что исключается необходимость проверки специальных случаев с корнем. Однако это, 
     *  в свою очередь, требует обеспечение корректной проверки, что левый потомок сторожевого
     *  узла всегда будет иметь порядок -INF, что, в свою очередь, накладывает дополнительные
     *  ограничения на предикат сравнение элементов, поэтому в настоящей реализации не используется.
     */
    Node* _root;



protected:
    // Секция отладочных компонент
    IRBTreeDumper<Element, Compar>* _dumper;


    // Специальный подход, позволяющий следующему классу иметь доступ к закрытым членам для их тестирования.
    template<typename, typename>
    friend class RBTreeTest;
  
}; // class RBTree



} // namespace xi



// Подключаем "реализационную" часть
#include "rbtree.hpp"



#endif // RBTREE_RBTREE_H_