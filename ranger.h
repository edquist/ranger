#pragma once

#include <set>
#include <iosfwd>

struct ranger {
    struct range;
    typedef int                       int_type;
    typedef std::set<range>           set_type;
    typedef set_type::iterator        iterator;
    typedef set_type::const_iterator  const_iterator;

    iterator insert(range r);
    iterator erase(range r);

    std::pair<iterator, bool> find(int_type x) const;

    bool contains(int_type x) const { return find(x).second; }
    bool empty()              const { return forest.empty(); }
    void clear()                    { forest.clear(); }

    // the state of our ranger
    set_type forest;
};

struct ranger::range {
    // for a range to be valid, safe to assume start < end

    struct iterator;
    typedef ranger::int_type int_type;

    range(int_type e) : start(0), end(e) {}
    range(int_type s, int_type e) : start(s), end(e) {}

    int_type size()           const { return end - start; }
    bool contains(int_type x) const { return start <= x && x < end; }

    // only for use in our disjoint ranger forest context
    bool operator< (const range &r2) const { return end < r2.end; }

    // data members
    int_type start;
    int_type end;
};

struct ranger::range::iterator {
    typedef ranger::int_type int_type;

    int_type i;

    iterator() : i(0) {}
    iterator(int_type n) : i(n) {}

    int_type &operator*()                 { return i; }
    int_type  operator*()           const { return i; }
    iterator  operator+(int_type n) const { return i+n; }
    iterator  operator-(int_type n) const { return i-n; }
    iterator &operator++()                { ++i; return *this; }
    iterator &operator--()                { --i; return *this; }
    iterator  operator++(int)             { return i++; }
    iterator  operator--(int)             { return i--; }
};

std::ostream &operator<<(std::ostream &os, const ranger::range &ir);
std::ostream &operator<<(std::ostream &os, const ranger &r);

