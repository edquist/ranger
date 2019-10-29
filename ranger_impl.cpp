#include <set>
#include <ostream>

#include "ranger.h"

ranger::iterator ranger::insert(ranger::range r)
{
    if (mr_set.empty())
        return mr_set.insert(r).first;

    // NOTE: use upper_bound for fracturing (ie, not to coalesce)
    auto it_start = mr_set.lower_bound(r.start);
    if (it_start == mr_set.end())
        return mr_set.insert(r).first;

    auto it = it_start;
    while (it != mr_set.end() && it->start <= r.end)  // '<' for fracturing
        ++it;

    auto it_end = it;
    if (it_start == it_end)
        return mr_set.insert(it_end, r);

    auto it_back = --it;
    range ir_new = { std::min(it_start->start, r.start),
                     std::max(it_back->end, r.end) };

    auto hint = mr_set.erase(it_start, it_end);

    return mr_set.insert(hint, ir_new);
}

ranger::iterator ranger::erase(ranger::range r)
{
    auto it_start = mr_set.upper_bound(r.start);
    if (it_start == mr_set.end())
        return it_start;

    auto it = it_start;
    while (it != mr_set.end() && it->start < r.end)
        ++it;

    auto it_end = it;
    if (it_start == it_end)
        return it_start;

    auto it_back = --it;
    range ir_start = *it_start;
    range ir_back  = *it_back;

    auto hint = mr_set.erase(it_start, it_end);
    if (ir_start.start < r.start)
        hint = mr_set.insert(hint, {ir_start.start, r.start});

    if (r.end < ir_back.end)
        hint = mr_set.insert(hint, {r.end, ir_back.end});

    return hint;
}

std::pair<ranger::iterator, bool>
ranger::find(int x) const
{
    auto it = mr_set.upper_bound(x);
    return {it, it != mr_set.end() && it->start <= x};
}



std::ostream &operator<<(std::ostream &os, const ranger::range &ir)
{
    return os << '[' << ir.start << ',' << ir.end << ')';
}

std::ostream &operator<<(std::ostream &os, const ranger &r)
{
    os << "{";
    for (auto ir : r.mr_set)
        os << " " << ir;
    return os << " }";
}

