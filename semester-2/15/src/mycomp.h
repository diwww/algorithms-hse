#ifndef BTREE_MYCOMP_H
#define BTREE_MYCOMP_H

#include "btree.h"

namespace xi
{

struct ByteComparator : public BaseBTree::IComparator
{
    virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        if (*lhv < *rhv)
            return true;
        return false;
    }

    // простейшая реализация — побайтное сравнение
    virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        for (UInt i = 0; i < sz; ++i)
            if (lhv[i] != rhv[i])
                return false;

        return true;
    }
};

}

#endif //BTREE_MYCOMP_H
