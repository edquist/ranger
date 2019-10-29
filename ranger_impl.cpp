#include "ranger.h"

ranger::set_iterator ranger::insert(ranger::range r)
{
    if (forest.empty())
        return forest.insert(r).first;

    // NOTE: use upper_bound here if you don't want to coalesce
    set_iterator it_start = forest.lower_bound(r._start);
    if (it_start == forest.end())
        return forest.insert(r).first;

    set_iterator it = it_start;
    while (it != forest.end() && it->_start <= r._end)  // '<' for no coalesce
        ++it;

    set_iterator it_end = it;
    if (it_start == it_end)
        return forest.insert(it_end, r);

    set_iterator it_back = --it;
    range rr_new = { std::min(it_start->_start, r._start),
                     std::max(it_back->_end, r._end) };

    set_iterator hint = forest.erase(it_start, it_end);

    return forest.insert(hint, rr_new);
}

ranger::set_iterator ranger::erase(ranger::range r)
{
    set_iterator it_start = forest.upper_bound(r._start);
    if (it_start == forest.end())
        return it_start;

    set_iterator it = it_start;
    while (it != forest.end() && it->_start < r._end)
        ++it;

    set_iterator it_end = it;
    if (it_start == it_end)
        return it_start;

    set_iterator it_back = --it;
    range rr_start = *it_start;
    range rr_back  = *it_back;

    set_iterator hint = forest.erase(it_start, it_end);
    if (rr_start._start < r._start)
        hint = forest.insert(hint, {rr_start._start, r._start});

    if (r._end < rr_back._end)
        hint = forest.insert(hint, {r._end, rr_back._end});

    return hint;
}

std::pair<ranger::set_iterator, bool>
ranger::find(int_type x) const
{
    set_iterator it = forest.upper_bound(x);
    return {it, it != forest.end() && it->_start <= x};
}



#include <ostream>

std::ostream &operator<<(std::ostream &os, const ranger::range &rr)
{
    return os << '[' << rr._start << ',' << rr._end << ')';
}

std::ostream &operator<<(std::ostream &os, const ranger &r)
{
    os << "{";
    for (ranger::range rr : r.forest)
        os << " " << rr;
    return os << " }";
}

