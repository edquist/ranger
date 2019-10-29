#pragma once

#include <set>
#include <iosfwd>

struct ranger {
    struct range;
    typedef std::set<range>           set_type;
    typedef set_type::iterator        iterator;
    typedef set_type::const_iterator  const_iterator;

    set_type mr_set;

    iterator insert(range r);
    iterator erase(range r);

    std::pair<iterator, bool> find(int x) const;

    bool contains(int x) const { return find(x).second; }
    bool empty() const         { return mr_set.empty(); }
    void clear()               { mr_set.clear(); }

    friend std::ostream &operator<<(std::ostream &os, const ranger::range &ir);
    friend std::ostream &operator<<(std::ostream &os, const ranger &r);
};

struct ranger::range {
    // for a range to be valid, safe to assume start < end

    int start;
    int end;

    range(int e) : start(0), end(e) {}
    range(int s, int e) : start(s), end(e) {}

    // assumes we use it in our disjoint context
    bool operator< (const range &r2) const { return end < r2.end; }

    int size() const { return end - start; }
    bool contains(int x) const { return start <= x && x < end; }
};


