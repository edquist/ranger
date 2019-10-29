#include "ranger.h"

ranger::iterator ranger::insert(ranger::range r)
{
    if (forest.empty())
        return forest.insert(r).first;

    // NOTE: use upper_bound here if you don't want to coalesce
    iterator it_start = forest.lower_bound(r.start);
    if (it_start == forest.end())
        return forest.insert(r).first;

    iterator it = it_start;
    while (it != forest.end() && it->start <= r.end)  // '<' for no coalesce
        ++it;

    iterator it_end = it;
    if (it_start == it_end)
        return forest.insert(it_end, r);

    iterator it_back = --it;
    range rr_new = { std::min(it_start->start, r.start),
                     std::max(it_back->end, r.end) };

    iterator hint = forest.erase(it_start, it_end);

    return forest.insert(hint, rr_new);
}

ranger::iterator ranger::erase(ranger::range r)
{
    iterator it_start = forest.upper_bound(r.start);
    if (it_start == forest.end())
        return it_start;

    iterator it = it_start;
    while (it != forest.end() && it->start < r.end)
        ++it;

    iterator it_end = it;
    if (it_start == it_end)
        return it_start;

    iterator it_back = --it;
    range rr_start = *it_start;
    range rr_back  = *it_back;

    iterator hint = forest.erase(it_start, it_end);
    if (rr_start.start < r.start)
        hint = forest.insert(hint, {rr_start.start, r.start});

    if (r.end < rr_back.end)
        hint = forest.insert(hint, {r.end, rr_back.end});

    return hint;
}

std::pair<ranger::iterator, bool>
ranger::find(int_type x) const
{
    iterator it = forest.upper_bound(x);
    return {it, it != forest.end() && it->start <= x};
}



#include <ostream>

std::ostream &operator<<(std::ostream &os, const ranger::range &rr)
{
    return os << '[' << rr.start << ',' << rr.end << ')';
}

std::ostream &operator<<(std::ostream &os, const ranger &r)
{
    os << "{";
    for (ranger::range rr : r.forest)
        os << " " << rr;
    return os << " }";
}

