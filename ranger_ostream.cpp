#include <ostream>

#include "ranger.h"

std::ostream &operator<<(std::ostream &os, const ranger::range &rr)
{
    return os << '[' << rr._start << ',' << rr._end << ')';
}

std::ostream &operator<<(std::ostream &os, const ranger &r)
{
    os << "{";
    for (ranger::range rr : r)
        os << " " << rr;
    return os << " }";
}

