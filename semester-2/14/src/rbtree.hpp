////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" (шаблонов) методов, описанных в файле rbtree.h
///
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>


namespace xi
{


//==============================================================================
// class RBTree::node
//==============================================================================

template<typename Element, typename Compar>
RBTree<Element, Compar>::Node::~Node()
{
    if (_left)
        delete _left;
    if (_right)
        delete _right;
}


template<typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
{
    // предупреждаем повторное присвоение
    if (_left == lf)
        return nullptr;

    // если новый левый — действительный элемент
    if (lf)
    {
        // если у него был родитель
        if (lf->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (lf->_parent->_left == lf)
                lf->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                lf->_parent->_right = nullptr;
        }

        // задаем нового родителя
        lf->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevLeft = _left;
    _left = lf;

    if (prevLeft)
        prevLeft->_parent = nullptr;

    return prevLeft;
}


template<typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
{
    // предупреждаем повторное присвоение
    if (_right == rg)
        return nullptr;

    // если новый правый — действительный элемент
    if (rg)
    {
        // если у него был родитель
        if (rg->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (rg->_parent->_left == rg)
                rg->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                rg->_parent->_right = nullptr;
        }

        // задаем нового родителя
        rg->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevRight = _right;
    _right = rg;

    if (prevRight)
        prevRight->_parent = nullptr;

    return prevRight;
}


//==============================================================================
// class RBTree
//==============================================================================

template<typename Element, typename Compar>
RBTree<Element, Compar>::RBTree()
{
    _root = nullptr;
    _dumper = nullptr;
}

template<typename Element, typename Compar>
RBTree<Element, Compar>::~RBTree()
{
    // грохаем пока что всех через корень
    if (_root)
        delete _root;
}


template<typename Element, typename Compar>
void RBTree<Element, Compar>::deleteNode(Node* nd)
{
    // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
    if (nd == nullptr)
        return;

    // потомков убьет в деструкторе
    delete nd;
}


template<typename Element, typename Compar>
void RBTree<Element, Compar>::insert(const Element& key)
{
    // этот метод можно оставить студентам целиком
    Node* newNode = insertNewBstEl(key);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

    rebalance(newNode);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

}


template<typename Element, typename Compar>
const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
{
    Node* temp = _root;
    while (temp)
    {
        if (key < temp->_key)
            temp = temp->_left;
        else if (key > temp->_key)
            temp = temp->_right;
        else
            return temp;
    }
    return nullptr;
}


template<typename Element, typename Compar>
typename RBTree<Element, Compar>::Node*
RBTree<Element, Compar>::insertNewBstEl(const Element& key)
{
    Node* toInsert = new Node(key); // Node to insert
    Node* temp = _root; // Start traversing from root
    Node* tempParent = nullptr; // Parent of temp (to remember previous node before NIL)
    while (temp)
    {
        tempParent = temp;
        if (toInsert->_key < temp->_key)
            temp = temp->_left;
        else if (toInsert->_key > temp->_key)
            temp = temp->_right;
        else
            throw std::invalid_argument("Equal keys.");
    }
    toInsert->_parent = tempParent;
    if (!tempParent) // If tree is empty
        _root = toInsert;
    else if (toInsert->_key < tempParent->_key)
        tempParent->_left = toInsert;
    else
        tempParent->_right = toInsert;
    toInsert->_color = RED;
    return toInsert;
}


template<typename Element, typename Compar>
typename RBTree<Element, Compar>::Node*
RBTree<Element, Compar>::rebalanceDUG(Node* nd)
{
    // TODO: этот метод студенты могут оставить и реализовать при декомпозиции балансировки дерева
}


template<typename Element, typename Compar>
void RBTree<Element, Compar>::rebalance(Node* nd)
{
    Node* y = nullptr; // Uncle
    while (nd->_parent && nd->_parent->_color == RED)
    {
        if (nd->_parent->isLeftChild())
        {
            y = nd->_parent->_parent->_right;
            if (y && y->_color == RED)
            {
                nd->_parent->_color = BLACK;
                y->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                nd = nd->_parent->_parent;
            }
            else
            {
                if (nd->isRightChild())
                {
                    nd = nd->_parent;
                    rotLeft(nd);
                }
                nd->_parent->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                rotRight(nd->_parent->_parent);
            }
        }
        else if (nd->_parent->isRightChild())
        {
            y = nd->_parent->_parent->_left;
            if (y && y->_color == RED)
            {
                y->_color = BLACK;
                nd->_parent->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                nd = nd->_parent->_parent;
            }
            else
            {
                if (nd->isLeftChild())
                {
                    nd = nd->_parent;
                    rotRight(nd);
                }
                nd->_parent->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                rotLeft(nd->_parent->_parent);
            }
        }
    }
    _root->_color = BLACK;
}


template<typename Element, typename Compar>
void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
{
    // Right child
    Node* y = nd->_right;
    if (!y)
        throw std::invalid_argument("Can't rotate left since the right child is nil");
    if (nd->isLeftChild())
        nd->_parent->setLeft(y);
    else if (nd->isRightChild())
        nd->_parent->setRight(y);
    else
        _root = y;

    nd->setRight(y->_left);
    y->setLeft(nd);

    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
}


template<typename Element, typename Compar>
void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
{
    Node* y = nd->_left;
    if (!y)
        throw std::invalid_argument("Can't rotate right since the left child is nil");
    if (nd->isLeftChild())
        nd->_parent->setLeft(y);
    else if (nd->isRightChild())
        nd->_parent->setRight(y);
    else
        _root = y;

    nd->setLeft(y->_right);
    y->setRight(nd);

    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
}

} // namespace xi

