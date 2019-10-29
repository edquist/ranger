#include <set>
#include <ostream>

struct irange {
    // for an irange to be valid, safe to assume start < end

    int start;
    int end;

    irange(int e) : start(0), end(e) {}
    irange(int s, int e) : start(s), end(e) {}

    // assumes we use it in our disjoint context
    bool operator< (const irange &r2) const { return end < r2.end; }

    int size() const { return end - start; }
    bool contains(int x) const { return start <= x && x < end; }
};

struct ranger {
    typedef std::set<irange>          mr_set_t;
    typedef mr_set_t::iterator        mr_set_it;
    typedef mr_set_t::const_iterator  mr_set_cit;

    mr_set_t mr_set;

    mr_set_it add(irange r);
    mr_set_it remove(irange r);

    std::pair<mr_set_it, bool> find(int x) const;

    bool contains(int x) const { return find(x).second; }
    bool empty() const         { return mr_set.empty(); }
    void clear()               { mr_set.clear(); }
};


ranger::mr_set_it ranger::add(irange r)
{
    if (mr_set.empty())
        return mr_set.insert(r).first;

    // NOTE: use upper_bound for fracturing
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
    irange ir_new = { std::min(it_start->start, r.start),
                      std::max(it_back->end, r.end) };

    auto hint = mr_set.erase(it_start, it_end);

    return mr_set.insert(hint, ir_new);
}

ranger::mr_set_it ranger::remove(irange r)
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
    irange ir_start = *it_start;
    irange ir_back  = *it_back;

    auto hint = mr_set.erase(it_start, it_end);
    if (ir_start.start < r.start)
        hint = mr_set.insert(hint, {ir_start.start, r.start});

    if (r.end < ir_back.end)
        hint = mr_set.insert(hint, {r.end, ir_back.end});

    return hint;
}

std::pair<ranger::mr_set_it, bool>
ranger::find(int x) const
{
    auto it = mr_set.upper_bound(x);
    return {it, it != mr_set.end() && it->start <= x};
}



std::ostream &operator<<(std::ostream &os, const irange &ir)
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

