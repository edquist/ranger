#include "ranger.h"

/* Frankly, the user would be better served by the tremendously simpler:
 *
 *      for (auto &rr : myranger.forest)
 *          for (int i : rr)
 *              process_int(i);
 */


void ranger::iterator::mk_valid()
{
    if (!rit_valid) {
        rit = sit->begin();
        rit_valid = true;
    }
}

ranger::value_type ranger::iterator::operator*()
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
    // at this point neither sit nor it.sit points to the end() of its set,
    // thus it's OK to call mk_valid() on each, which may dereference *sit
    mk_valid();
    it.mk_valid();
    return rit == it.rit;
}

bool ranger::iterator::operator!=(iterator &it)
{
    return !(*this == it);
}

