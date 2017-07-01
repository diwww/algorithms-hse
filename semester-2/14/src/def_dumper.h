////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация дампера дерева по умолчанию
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Дампер по умолчанию выводит информации об изменении дерева в event log, 
/// сопровождая выводом структуры в виде заготовки для последующей визуализации
/// утилитой GraphViz
///
////////////////////////////////////////////////////////////////////////////////

#ifndef RBTREE_TESTS_DEF_DUMPER_H_
#define RBTREE_TESTS_DEF_DUMPER_H_


#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "rbtree.h"
using namespace xi;

/** \brief Осуществляет вывод дерева в виде структуры на языке DOT утилиты GraphViz.
 */
template <typename Element, typename Compar> // = std::less<Element> >
class RBTreeGvDumper {
public:
    // Объявление типов дерева и узла для упрощения доступа
    typedef xi::RBTree<Element, Compar> TTree;
    typedef typename xi::RBTree<Element, Compar>::Node TTreeNode;
    //typedef TTree::Node TTreeNode;

public:
    /** \brief Выполняет дамп.  
     *
     *  Если файл не может быть открыт, кидает исключение \c std::invalid_argument.
     */
    void dump(const std::string& fn, const TTree& tree, const char* grLbl = nullptr)
    {
        //std::invalid_argument
        std::ofstream dfile(fn.c_str());
        if (!dfile.is_open())
            throw std::invalid_argument("Can't open dump file for GraphViz");


        // заголовок
        outHeader(dfile, grLbl);

        // тело
        outTree(dfile, tree);

        // хвост
        outTail(dfile);

        dfile.flush();

    }

protected:

    /** \brief Выводит в поток собственно элементы дерева. 
     *
     *  Для возможности работы этого метода необходимо, чтобы для типа Element был перегружен
     *  оператор вывода в поток: <tt>ostream& operator<<(ostream&, const Element& el)</tt>.
     */
    void outTree(std::ostream& str, const TTree& tree)
    {
        if (tree.getRoot())
            outNode(str, tree.getRoot());
        // TODO: пока-что, если нет корня, просто ничего не выводим
    }


    /** \brief Выводит в поток информацию об узле \с и связей с его дочками, но не с предком: 
        предок должен сам эту информацию про этого своего потока вывести будет
     */
    void outNode(std::ostream& str, const TTreeNode* node)
    {
        // если переданный узел пустой, ничего не выводим
        if (!node)
            return;

        // выводим информацию об узле: идентификатор берем из оператора operator<<
        str << "    " << node->getKey() << " [fillcolor=";
        if (node->isBlack())        // TODO: могут ли тут быть другие варианты?!
            str << "black]\n";
        else
            str << "red]\n";

        str.flush();        // TODO: временно, убрать!

        // рисуем связи к дочерним элементам
        outArcBtwNodes(str, node, node->getLeft(), true);
        outArcBtwNodes(str, node, node->getRight(), false);        

        // обраатываем рекурсивно дочерние элементы
        outNode(str, node->getLeft());
        outNode(str, node->getRight());
    }

    /** \brief Рисует дугу между родительским нодом \c par и одной из его дочек \c chld. 
     *  \c ifLeft определяет, что узел левый, иначе — правый — нужен для формирования идентификатора*/
    void outArcBtwNodes(std::ostream& str, const TTreeNode* par, const TTreeNode* chld, bool ifLeft)
    {
        std::stringstream ss;           // опр. идентификатор дочки
        if (chld)
            ss << chld->getKey(); // << std::endl;
        else
        {
            // если дочернего элемента реально нет, надо вывести специальный null-узел
            ss << "NULL";
            ss << (ifLeft ? "l" : "r");
            ss <<  par->getKey(); // << std::endl;
        }

        // собственно дуга
        str << "    " << par->getKey() << " -> " 
            << ss.str()//ss.rdbuf()
            << std::endl;

        str.flush();        // TODO: временно, убрать!
        // если дочка была null, специально под нее элемент
        if (!chld)
        {
            str << "    " 
                << ss.str()//ss.rdbuf()
                << " [label=\"nil\",width=0.3,height=0.2,shape=box,fillcolor=black]\n";
            str.flush();        // TODO: временно, убрать!
        }
        
    }



    /** \brief Выводит в поток заголовочную часть графа. */
    void outHeader(std::ostream& str, const char* grLbl = nullptr)
    {
        str << "digraph G {\n";

        // если есть метка графа, добавим:
        if (grLbl)
            str << "    label=\"" << grLbl << "\";\n";

        str << "    node [width=0.5,fontcolor=white,style=filled];\n";
    }

    /** \brief Выводит в поток хвостовую часть графа. */
    void outTail(std::ostream& str)
    {
        str << "}\n";
    }

}; // class RBTreeGvDumper




/** \brief Реализация по умолчанию отладочного дампера дерева.
 *
 *  
 */
template <typename Element, typename Compar>
class RBTreeDefDumper : public xi::IRBTreeDumper<Element, Compar> {
public:
    /** \brief Создает дампер с путями к файлу журнала \c evLogFile 
     *  и каталогу для картинок \c imgPath.
     */
    RBTreeDefDumper(const std::string& evLogFileName, const std::string& imgPath) //;
        : _imgPath(imgPath)
        , _imgCounter(0)
    {
        _evLogFile.open(evLogFileName.c_str());
        if (!_evLogFile.is_open())
            throw std::invalid_argument("Error opening event log for output");


        // Выводим приветствие
        _evLogFile << "RBTree Event Log opened\n-----------------------\n";

    }

    /** \brief Деструктор. */
    ~RBTreeDefDumper() //;
    //RBTreeDefDumper::~RBTreeDefDumper()
    {
        _evLogFile << "-----------------------\nRBTree Event Log closed\n";
        _evLogFile.close();
    }

public:
    virtual void rbTreeEvent(typename IRBTreeDumper<Element,Compar>::RBTreeDumperEvent ev,
                             typename IRBTreeDumper<Element, Compar>::TTree* tr,
                             typename IRBTreeDumper<Element, Compar>::TTreeNode* nd) override
    {
        // для любых сообщений формируем имя файла
        char fnBuf[255];
        sprintf(fnBuf, "%sdump_#_%04d.gv", _imgPath.c_str(), _imgCounter);
        
        // формируем информационную строку с помощью потока-строки       
        std::stringstream ss;
        ss << getInfoStr(ev);

        // для всех сообщений доформируем строку с узлом-инициатором
        ss << " [" << nd->getKey() << "]";
        _evLogFile << ss.str();
        _evLogFile << " # " << std::setw(4) << _imgCounter << std::endl;

        _gvDumper.dump(fnBuf, *tr, ss.str().c_str());
        ++_imgCounter;
    } // rbTreeEvent()

protected:

    /** \brief Для переданного типа события, возвращает соответствующую ему информационную строку. */
    const char* getInfoStr(typename IRBTreeDumper<Element, Compar>::RBTreeDumperEvent ev)
    {
        // храним строки прямо здесь (в единственном статическом экземпляре)
        // данный подход не очень хорош, особенно с точки зрения потокобезопасности,
        // однако возвращать адрес на статический объект, объявленный внутри функции,
        // все же возможно, т.к. время жизни этого объекта дольше вызова функции.
        // этому подходу лучше было бы предпочесть объявление этих констант статическими
        // вне класса, что, однако, несколько громоздко из-за необходимости таскать
        // за каждым выносням объявлением описание шаблона.
        static const char* INFOS_ROTL   = "Rot Left";
        static const char* INFOS_ROTR   = "Rot Right";
        static const char* INFOS_BSTINS = "BST Insert";
        static const char* INFOS_INSERT = "RBT Insert";
        static const char* INFOS_REC1   = "Recolor 1";
        static const char* INFOS_ROT3D  = "Recolor 3 dad";
        static const char* INFOS_ROT3G  = "Recolor 3 grandpa";


        // повороты
        if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_LROT ||
            ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RROT)
        {

            if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_LROT)
                return INFOS_ROTL;
            return INFOS_ROTR;
        }

        // обычная BST-вставка
        if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS)
            return INFOS_BSTINS;


        // RBT-вставка после балансировки
        if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT)
            return INFOS_INSERT;

        // NB: в принципе, в следующем if-е нет необходимости, т.к. это единственная
        // возможная ветка, однако, если вдруг будут свдиги вверх/вниз или появятся новые
        // секции, обработать этот момент будет проще.

        // перекраски
        //if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1 ||
        //    ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D ||
        //    ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G)
        //{

            if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1)
                return INFOS_REC1;
            if (ev == IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D)
                return INFOS_ROT3D;
            return INFOS_ROT3G;
        //}


    };


protected:
    std::ofstream _evLogFile;               ///< Файл журнала.
    std::string _imgPath;                   ///< Путь к каталогу с картинками.

    unsigned int _imgCounter;               ///< Счетчик для номеров картинок.

    /** \brief Выводить в формате GraphViz. */
    RBTreeGvDumper<int, std::less<int>> _gvDumper;

}; // class RBTreeDefDumper 


#endif // RBTREE_TESTS_DEF_DUMPER_H_