#include "ranger.h"

ranger::set_iterator ranger::insert(ranger::range r)
{
    // lower_bound here will coalesce an adjacent disjoint range;
    // can use upper_bound instead to avoid this and leave them fractured
    set_iterator it_start = forest.lower_bound(r._start);
    set_iterator it = it_start;
    while (it != forest.end() && it->_start <= r._end)  // '<' for no coalesce
        ++it;

    set_iterator it_end = it;
    if (it_start == it_end)
        return forest.insert(it_end, r);

    if (it_start->contains(r))
        return it_start;

    set_iterator it_back = --it;
    range rr_new = { std::min(it_start->_start, r._start),
                     std::max(it_back->_end, r._end) };

    // avoid erase+insert if only expanding a range
    if (it_start == it_back) {
        it_start->_start = rr_new._start;
        it_start->_end = rr_new._end;
        return it_start;
    }

    set_iterator hint = forest.erase(it_start, it_end);

    return forest.insert(hint, rr_new);
}

static
bool shrink_single_edge(const ranger::range &rm, const ranger::range &at)
{
    bool erase_start = rm._start <= at._start;
    bool erase_back  = at._end   <= rm._end;
    if (erase_start ^ erase_back) {
        if (erase_start)
            at._start = rm._end;
        else
            at._end = rm._start;
        return true;
    }
    return false;
}

ranger::set_iterator ranger::erase(ranger::range r)
{
    set_iterator it_start = forest.upper_bound(r._start);
    set_iterator it = it_start;
    while (it != forest.end() && it->_start < r._end)
        ++it;

    set_iterator it_end = it;
    if (it_start == it_end)
        return it_start;

    set_iterator it_back = --it;
    // avoid erase+insert if only shrinking an edge of a range
    if (it_start == it_back && shrink_single_edge(r, *it_start))
        return it_start;
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
ranger::find(value_type x) const
{
    set_iterator it = forest.upper_bound(x);
    return {it, it != forest.end() && it->_start <= x};
}

ranger::ranger(const std::initializer_list<ranger::range> &il)
{
    for (const range &rr : il)
        insert(rr);
}

