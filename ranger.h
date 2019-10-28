
#include <set>
#include <ostream>

struct irange {
    // for an irange to be valid, safe to assume start < end

    int start;
    int end;

    // assumes we use it in our disjoint context
    bool operator< (const irange &r2) const { return end < r2.end; }

    int size() const { return end - start; }
    bool contains(int x) const { return start <= x && x < end; }
};

// Or...
inline bool irange_set_cmp(const irange &r1, const irange &r2)
{ return r1.end < r2.end; }

struct ranger {
    typedef std::set<irange>          mr_set_t;
    typedef mr_set_t::iterator        mr_set_it;
    typedef mr_set_t::const_iterator  mr_set_cit;

    mr_set_t mr_set;

    void add(irange r);       // -->  operator|
    void remove(irange r);    // -->  operator-

    bool contains(int x);
    bool contains(irange r);  // ?

    std::pair<bool, mr_set_it> find(int x);
};

void ranger::add(irange r)
{
    auto rs = find(r.start);
    auto re = find(r.end);
}

std::pair<bool, ranger::mr_set_it>
ranger::find(int x)
{
    auto it = mr_set.upper_bound({x,x});
    return {it != mr_set.end() && it->start <= x, it};
}

bool ranger::contains(int x)
{
    return find(x).first;
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

