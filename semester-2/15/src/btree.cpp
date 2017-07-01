////////////////////////////////////////////////////////////////////////////////
// Module Name:  btree.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "btree.h"
#include <cstring>

// #include <stdexcept>        // std::invalid_argument



namespace xi
{


//==============================================================================
// class BaseBTree
//==============================================================================



bool BaseBTree::Header::checkIntegrity()
{
    return (sign == VALID_SIGN) && (order >= 1) && (recSize > 0);
}


BaseBTree::BaseBTree(UShort order, UShort recSize, IComparator* comparator, std::iostream* stream)
        : _order(order),
          _recSize(recSize),
          _comparator(comparator),
          _stream(stream),
          _lastPageNum(0),
          _rootPageNum(0), _rootPage(this)
{
}


BaseBTree::BaseBTree(IComparator* comparator, std::iostream* stream) :
        BaseBTree(
                0,      // порядок, 0 — д.б. прочитан из файла!
                0,      // размер ключа, 0 —  --//--
                comparator, stream)
{

}


BaseBTree::~BaseBTree()
{
}


void BaseBTree::resetBTree()
{
    _order = 0;
    _recSize = 0;
    _stream = nullptr;
    _comparator = nullptr;      // для порядку его тоже сбасываем, но это не очень обязательно
}


void BaseBTree::readPage(UInt pnum, Byte* dst)
{
    //if (!isOpen())
    //    throw std::runtime_error("Stream is not ready");

    checkForOpenStream();
    //if (pnum == 0 || pnum >= getLastPageNum())
    if (pnum == 0 || pnum > getLastPageNum())
        throw std::invalid_argument("Can't read a non-existing page");

    readPageInternal(pnum, dst);
}


void BaseBTree::writePage(UInt pnum, const Byte* dst)
{
    checkForOpenStream();

    if (pnum == 0 || pnum > getLastPageNum())
        throw std::invalid_argument("Can't write a non-existing page");

    writePageInternal(pnum, dst);

}


bool BaseBTree::checkKeysNumber(UShort keysNum, bool isRoot)
{
    if (keysNum > getMaxKeys())
        return false;                       // превышение по максимуму

    // NOTE: для корня пока даже 0 допустим, потом уточним, надо ли до 1 сокращать
    if (isRoot)
        //if (nt == nRoot)
        return true;

    return (keysNum >= getMinKeys());
}


void BaseBTree::checkKeysNumberExc(UShort keysNum, bool isRoot)
{
    if (!checkKeysNumber(keysNum, isRoot))
        throw std::invalid_argument("Invalid number of keys for a node");
}


UInt BaseBTree::allocPage(PageWrapper& pw, UShort keysNum, bool isLeaf /*= false*/)
{
    checkForOpenStream();
    checkKeysNumberExc(keysNum, pw.isRoot());  // nt);

    return allocPageInternal(pw, keysNum, pw.isRoot(), isLeaf);
}


xi::UInt BaseBTree::allocNewRootPage(PageWrapper& pw)
{
    checkForOpenStream();
    return allocPageInternal(pw, 0, true, false);
}


void BaseBTree::insert(const Byte* k)
{
    _rootPage.insertNonFull(k);
    // TODO: реализовать студентам!
}

Byte* BaseBTree::search(PageWrapper& page, const Byte* k)
{
    UShort i = 0;
    while (i < page.getKeysNum() && _comparator->compare(page.getKey(i), k, _recSize))
        i++;
    if (i < page.getKeysNum() && _comparator->isEqual(k, page.getKey(i), _recSize))
        return _rootPage.getKey(i);
    else if (page.isLeaf())
        return nullptr;
    else
    {
        PageWrapper temp(this);
        temp.readPage(page.getCursor(i));
        return search(temp, k);
    }
}

Byte* BaseBTree::search(const Byte* k)
{
    search(_rootPage, k);
}


int BaseBTree::searchAll(const Byte* k, std::list<Byte*>& keys)
{
    // TODO: релаизовать студентам!

}


UInt BaseBTree::allocPageInternal(PageWrapper& pw, UShort keysNum, bool isRoot, bool isLeaf)
{
    // подготовим страничку для вывода
    pw.clear();
    pw.setKeyNumLeaf(keysNum, isRoot, isLeaf);    // nt);

    // пока что просто позиционируемся в конец, считая, что так и будет, но держать под контролем
    _stream->seekg(0, std::ios_base::end);
    _stream->write((const char*) pw.getData(), getNodePageSize());

    ++_lastPageNum;
    writePageCounter();


    // TODO: flush-им на диск сразу?!
    //_stream->flush();

    return _lastPageNum;
}


void BaseBTree::readPageInternal(UInt pnum, Byte* dst)
{
    // позиционируемся и читаем
    gotoPage(pnum);
    _stream->read((char*) dst, getNodePageSize());
}


void BaseBTree::writePageInternal(UInt pnum, const Byte* dst)
{
    // позиционируемся и пишем
    gotoPage(pnum);
    _stream->write((const char*) dst, getNodePageSize());
}


void BaseBTree::gotoPage(UInt pnum)
{
    // рассчитаем смещение до нужной страницы
    UInt pageOfs = FIRST_PAGE_OFS + getNodePageSize() * (pnum - 1);     // т.к. нумеруются с единицы
    _stream->seekg(pageOfs, std::ios_base::beg);
}


void BaseBTree::loadTree()
{

    Header hdr;
    readHeader(hdr);

    // если при чтении случилась пичалька
    if (_stream->fail())
    {
        //_stream->close();
        throw std::runtime_error("Can't read header");
    }

    // проверяет заголовок на корректность
    if (!hdr.checkIntegrity())
    {
        //_stream->close();
        throw std::runtime_error("Stream is not a valid xi B-tree file");
    }

    // задаем порядок и т.д.
    setOrder(hdr.order, hdr.recSize);

    // далее без проверки читаем два следующих поля
    readPageCounter();             // номер текущей свободной страницы
    readRootPageNum();             // номер корневой страницы

    // если при чтении случилась пичалька
    if (_stream->fail())
    {
        //_fileStream.close();
        throw std::runtime_error("Can't read necessary fields. File corrupted");
    }

    // DONE: загрузить корневую страницу
    loadRootPage(); // _rootPage);    // _wp0);

}


void BaseBTree::loadRootPage()  //PageWrapper& pw)
{
    if (getRootPageNum() == 0)
        throw std::runtime_error("Root page is not defined");

    _rootPage.readPage(getRootPageNum());
    _rootPage.setAsRoot(false);               // в файл номер страницы не пишем, т.к. только что прочитали оттуда его

}


void BaseBTree::createTree(UShort order, UShort recSize)
{
    setOrder(order, recSize);

    writeHeader();                  // записываем заголовок файла
    writePageCounter();             // и номер текущей свободной страницы
    writeRootPageNum();             // и номер корневой страницы


    // DONE: создать корневую страницу
    createRootPage();

}


void BaseBTree::createRootPage()
{
    _rootPage.allocPage(0, true);
    _rootPage.setAsRoot();
}


void BaseBTree::checkForOpenStream()
{
    if (!isOpen())
        throw std::runtime_error("Stream is not ready");

}


void BaseBTree::writeHeader()
{
    Header hdr(_order, _recSize);
    _stream->write((const char*) (void*) &hdr, HEADER_SIZE);

}

void BaseBTree::readHeader(Header& hdr)
{
    _stream->seekg(HEADER_OFS, std::ios_base::beg);
    _stream->read((char*) &hdr, HEADER_SIZE);

}


void BaseBTree::writePageCounter() //UInt pc)
{
    _stream->seekg(PAGE_COUNTER_OFS, std::ios_base::beg);
    _stream->write((const char*) &_lastPageNum, PAGE_COUNTER_SZ);
}


//xi::UInt
void BaseBTree::readPageCounter()
{
    _stream->seekg(PAGE_COUNTER_OFS, std::ios_base::beg);
    _stream->read((char*) &_lastPageNum, PAGE_COUNTER_SZ);

}


void BaseBTree::writeRootPageNum() //UInt rpn)
{
    _stream->seekg(ROOT_PAGE_NUM_OFS, std::ios_base::beg);
    _stream->write((const char*) &_rootPageNum, ROOT_PAGE_NUM_SZ);

}


//xi::UInt
void BaseBTree::readRootPageNum()
{
    _stream->seekg(ROOT_PAGE_NUM_OFS, std::ios_base::beg);
    _stream->read((char*) &_rootPageNum, ROOT_PAGE_NUM_SZ);
}


void BaseBTree::setRootPageNum(UInt pnum, bool writeFlag /*= true*/)
{
    _rootPageNum = pnum;
    if (writeFlag)
        writeRootPageNum();
}


void BaseBTree::setOrder(UShort order, UShort recSize)
{
    // метод закрытый, корректность параметров должно проверять в вызывающих методах

    _order = order;
    _recSize = recSize;

    _minKeys = order - 1;
    _maxKeys = 2 * order - 1;

    // проверим максимальное число ключей
    if (_maxKeys > MAX_KEYS_NUM)
        throw std::invalid_argument("For a given B-tree order, there is an excess of the maximum number of keys");

    _keysSize = _recSize * _maxKeys;                // область памяти под ключи
    _cursorsOfs = _keysSize + KEYS_OFS;             // смещение области курсоров на дочерние
    _nodePageSize = _cursorsOfs + CURSOR_SZ * (2 * order);  // размер узла целиком, опр. концом области страницы

    // Q: номер текущей корневой надо устанавливать?

    // пока-что распределяем память под рабочую страницу/узел здесь, но это сомнительно
    //_workPage.reallocData(_nodePageSize);
    reallocWorkPages();
}


void BaseBTree::reallocWorkPages()
{
    _rootPage.reallocData(_nodePageSize);
}


//==============================================================================
// class BaseBTree::PageWrapper
//==============================================================================



BaseBTree::PageWrapper::PageWrapper(BaseBTree* tr) :
        _data(nullptr), _tree(tr), _pageNum(0)
{
    // если к моменту создания странички дерево уже в работе (открыто), надо
    // сразу распределить память!
    if (_tree->isOpen())
        reallocData(_tree->getNodePageSize());

}


BaseBTree::PageWrapper::~PageWrapper()
{
    reallocData(0);
}


void BaseBTree::PageWrapper::reallocData(UInt sz)
{
    if (_data)
        delete[] _data;

    if (sz)
        _data = new Byte[sz];

}

void BaseBTree::PageWrapper::clear()
{
    if (!_data)
        return;

    // работая с сырыми блоками данных единственно и можно применять низкоуровневые C-функции
    memset(_data, 0, _tree->getNodePageSize());
}


void BaseBTree::PageWrapper::setKeyNumLeaf(UShort keysNum, bool isRoot, bool isLeaf) //NodeType nt)
{
    //if (!_tree->checkKeysNumber(keysNum, nt))
    //    throw std::invalid_argument("Invalid number of keys for a node");

    _tree->checkKeysNumberExc(keysNum, isRoot);

    // логически приплюсовываем
    if (isLeaf)
        //if (nt == nLeaf)
        keysNum |= LEAF_NODE_MASK; // 0x8000;

    // способ записи типизированного объекта, начиная с адреса [0]
    *((UShort*) &_data[0]) = keysNum;
}


void BaseBTree::PageWrapper::setKeyNum(UShort keysNum, bool isRoot) //NodeType nt)
{
    _tree->checkKeysNumberExc(keysNum, isRoot);


    UShort kldata = *((UShort*) &_data[0]);      // взяли сущ. значение
    kldata &= LEAF_NODE_MASK;                   // оставили от него только флаг "лист"
    kldata |= keysNum;                          // приилили число ключей (там точно не будет 1 в старшем)

    *((UShort*) &_data[0]) = kldata;             // записали
}


void BaseBTree::PageWrapper::setLeaf(bool isLeaf)
{
    UShort kldata = *((UShort*) &_data[0]);      // взяли сущ. значение
    kldata &= ~LEAF_NODE_MASK;                  // оставили от него только часть с числом ключей
    if (isLeaf)
        kldata |= LEAF_NODE_MASK;   // 0x8000;  // приилили флаг, если надо

    *((UShort*) &_data[0]) = kldata;             // записали
}


bool BaseBTree::PageWrapper::isLeaf() const
{
    UShort info = *((UShort*) &_data[0]);

    return (info & LEAF_NODE_MASK) != 0;
}

UShort BaseBTree::PageWrapper::getKeysNum() const
{
    UShort info = *((UShort*) &_data[0]);

    return (info & ~LEAF_NODE_MASK);
}


Byte* BaseBTree::PageWrapper::getKey(UShort num)
{
    //if (num >= getKeysNum())
    //    return nullptr;

    //// рассчитываем смещение
    //UInt kofst = KEYS_OFS + _tree->getRecSize() * num;
    int kofst = getKeyOfs(num);
    if (kofst == -1)
        return nullptr;

    return (_data + kofst);
}


const Byte* BaseBTree::PageWrapper::getKey(UShort num) const
{
    int kofst = getKeyOfs(num);
    if (kofst == -1)
        return nullptr;

    return (_data + kofst);
}


void BaseBTree::PageWrapper::copyKey(Byte* dst, const Byte* src)
{
    memcpy(
            dst,                        // куда
            src,                        // откуда
            _tree->getRecSize());       // размер ключа
}

void BaseBTree::PageWrapper::copyKeys(Byte* dst, const Byte* src, UShort num)
{
    memcpy(
            dst,                        // куда
            src,                        // откуда
            _tree->getRecSize() * num   // размер: размер записи на число элементов
    );

}

void BaseBTree::PageWrapper::copyCursors(Byte* dst, const Byte* src, UShort num)
{
    memcpy(
            dst,                        // куда
            src,                        // откуда
            num * CURSOR_SZ             // размер
    );
}

UInt BaseBTree::PageWrapper::getCursor(UShort cnum)
{
    //if (cnum > getKeysNum())
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    return *((const UInt*) (_data + curOfs));
}


Byte* BaseBTree::PageWrapper::getCursorPtr(UShort cnum)
{
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    return (_data + curOfs);

}

void BaseBTree::PageWrapper::setCursor(UShort cnum, UInt cval)
{
    int curOfs = getCursorOfs(cnum);
    if (curOfs == -1)
        throw std::invalid_argument("Wrong cursor number");

    *((UInt*) (_data + curOfs)) = cval;
}


int BaseBTree::PageWrapper::getCursorOfs(UShort cnum) const
{
    if (cnum > getKeysNum())
        return -1;

    // рассчитываем смещением
    return _tree->getCursorsOfs() + CURSOR_SZ * cnum;
}

int BaseBTree::PageWrapper::getKeyOfs(UShort num) const
{
    if (num >= getKeysNum())
        return -1;

    // рассчитываем смещение
    return KEYS_OFS + _tree->getRecSize() * num;
}


void BaseBTree::PageWrapper::setAsRoot(bool writeFlag /*= true*/)
{
    //_tree->_rootPage = this;
    _tree->_rootPageNum = _pageNum;         // ид корень по номеру страницы в памяти

    if (!writeFlag)
        return;

    // если же надо записать в файл сразу...
    if (_pageNum == 0)
        throw std::runtime_error("Can't set a page as root until allocate a page in a file");

    // если же под страницу есть номер, запишем его в файл
    _tree->setRootPageNum(_pageNum, true);
}


void BaseBTree::PageWrapper::readPageFromChild(PageWrapper& pw, UShort chNum)
{
    UInt cur = pw.getCursor(chNum);
    if (cur == 0)
        throw std::invalid_argument("Cursor does not point to a existing node/page");

    readPage(cur);
}


void BaseBTree::PageWrapper::writePage()
{
    if (getPageNum() == 0)
        throw std::runtime_error("Page number not set. Can't write");

    _tree->writePage(getPageNum(), _data);
}


void BaseBTree::PageWrapper::splitChild(UShort iChild)
{
    if (isFull())
        throw std::domain_error("A parent node is full, so its child can't be splitted");

    if (iChild > getKeysNum())
        throw std::invalid_argument("Cursor not exists");



    // TODO: реализовать студентам
}

void BaseBTree::PageWrapper::insertNonFull(PageWrapper page, const Byte* k)
{
    UShort i = getKeysNum();
    if (page.isLeaf())
    {
        while (i >= 0 && page._tree->getComparator()->compare(k, page.getKey(i), page._tree->getRecSize()))
        {
            page.copyKey(page.getKey(i + 1), page.getKey(i));
            --i;
        }
        page.copyKey(page.getKey(i + 1), k);
        page.setKeyNum(page.getKeysNum() + 1);
        page.writePage();
//        // FIXME: true or false is leaf?
//        page.allocPage();
    }

}

void BaseBTree::PageWrapper::insertNonFull(const Byte* k)
{
    if (isFull())
        throw std::domain_error("Node is full. Can't insert");

    IComparator* c = _tree->getComparator();
    if (!c)
        throw std::runtime_error("Comparator not set. Can't insert");

    // TODO: реализовать студентам
}







//==============================================================================
// class FileBaseBTree
//==============================================================================

FileBaseBTree::FileBaseBTree()
        : BaseBTree(0, 0, nullptr, nullptr)
{
    //_stream = nullptr;              // в базовом классе пока про поток ничего не знают
}


FileBaseBTree::FileBaseBTree(UShort order, UShort recSize, IComparator* comparator,
                             const std::string& fileName)
        : FileBaseBTree()
{
    _comparator = comparator;

    checkTreeParams(order, recSize);
    createInternal(order, recSize, fileName);
}


FileBaseBTree::FileBaseBTree(const std::string& fileName, IComparator* comparator)
        : FileBaseBTree()
{
    _comparator = comparator;
    loadInternal(fileName); // , comparator);
}

FileBaseBTree::~FileBaseBTree()
{
    close();            // именно для удобства такого использования не кидаем внутри искл. ситуацию!
}


void FileBaseBTree::create(UShort order, UShort recSize, //IComparator* comparator,
                           const std::string& fileName)
{
    if (isOpen())
        throw std::runtime_error("B-tree file is already open");

    checkTreeParams(order, recSize);
    createInternal(order, recSize, fileName);
}


void FileBaseBTree::createInternal(UShort order, UShort recSize, // IComparator* comparator,
                                   const std::string& fileName)
{
    _fileStream.open(fileName,
                     std::fstream::in | std::fstream::out |      // чтение запись
                     std::fstream::trunc |
                     // обязательно грохнуть имеющееся (если вдруг) содержимое
                     std::fstream::binary);                      // бинарничек

    // если открыть не удалось
    if (_fileStream.fail())
    {
        // пытаемся закрыть и уходим
        _fileStream.close();
        throw std::runtime_error("Can't open file for writing");
    }

    // если же все ок, сохраняем параметры и двигаемся дальше
    //_comparator = comparator;
    _fileName = fileName;
    _stream = &_fileStream;         // привязываем к потоку

    createTree(order, recSize);                     // в базовом дереве
}


void FileBaseBTree::open(const std::string& fileName) //, IComparator* comparator)
{
    if (isOpen())
        throw std::runtime_error("B-tree file is already open");

    loadInternal(fileName); // , comparator);
}


void FileBaseBTree::loadInternal(const std::string& fileName) // , IComparator* comparator)
{
    _fileStream.open(fileName,
                     std::fstream::in | std::fstream::out |      // чтение запись
                     //  здесь не должно быть trunc, чтобы сущ. не убить
                     std::fstream::binary);                      // бинарничек

    // если открыть не удалось
    if (_fileStream.fail())
    {
        // пытаемся закрыть и уходим
        _fileStream.close();
        throw std::runtime_error("Can't open file for reading");
    }

    // если же все ок, сохраняем параметры и двигаемся дальше
    //_comparator = comparator;
    _fileName = fileName;
    _stream = &_fileStream;         // привязываем к потоку


    try
    {
        loadTree();
    }
    catch (std::exception& e)
    {
        _fileStream.close();
        throw e;
    }
    catch (...)                     // для левых исключений
    {
        _fileStream.close();
        throw std::runtime_error("Error when loading btree");
    }
}


void FileBaseBTree::close()
{
    if (!isOpen())
        return;

    closeInternal();
}


void FileBaseBTree::closeInternal()
{
    // NOTE: возможно, перед закрытием надо что-то записать в файл? — иметь в виду!
    _fileStream.close();

    // переводим объект в состояние сконструированного БЕЗ параметров
    resetBTree();
}

void FileBaseBTree::checkTreeParams(UShort order, UShort recSize)
{
    if (order < 1 || recSize == 0)
        throw std::invalid_argument("B-tree order can't be less than 1 and record siaze can't be 0");

}

bool FileBaseBTree::isOpen() const
{
    return (_fileStream.is_open()); // && _fileStream.good());
}


} // namespace xi

