#include "ranger.h"

ranger::int_type ranger::iterator::operator*()
{
    mk_valid();
    return *rit;
}

ranger::iterator &ranger::iterator::operator++()
{
    mk_valid();
    if (++rit == sit->end()) {
        ++sit;
        rit_valid = false;
    }
    return *this;
}

ranger::iterator &ranger::iterator::operator--()
{
    mk_valid();
    if (rit == sit->begin()) {
        --sit;
        rit = sit->end();
        --rit;
    }
    return *this;
}

bool ranger::iterator::operator==(iterator &it)
{
    if (sit != it.sit)
        return false;
    if (!rit_valid && !it.rit_valid)
        return true;
    mk_valid();
    it.mk_valid();
    return rit == it.rit;
}

bool ranger::iterator::operator!=(iterator &it)
{
    return !(*this == it);
}

void ranger::iterator::mk_valid()
{
    if (!rit_valid) {
        rit = sit->begin();
        rit_valid = true;
    }
}

