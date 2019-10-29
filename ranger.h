#pragma once

#include <set>
#include <iosfwd>

struct ranger {
    struct range;
    typedef int                       int_type;
    typedef std::set<range>           set_type;
    typedef set_type::iterator        iterator;

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
    struct iterator;
    typedef ranger::int_type int_type;

    range(int_type e) : _start(0), _end(e) {}
    range(int_type s, int_type e) : _start(s), _end(e) {}

    int_type size()           const { return _end - _start; }
    bool contains(int_type x) const { return _start <= x && x < _end; }

    // only for use in our disjoint ranger forest context
    bool operator< (const range &r2) const { return _end < r2._end; }

    inline iterator begin() const;
    inline iterator end()   const;

    // data members; for a range to be valid, safe to assume _start < _end
    int_type _start;
    int_type _end;
};

struct ranger::range::iterator {
    typedef ranger::int_type int_type;

    int_type i;

    iterator() : i(0) {}
    iterator(int_type n) : i(n) {}

    int_type  operator*()           const {      return i;     }
    iterator  operator+(int_type n) const {      return i+n;   }
    iterator  operator-(int_type n) const {      return i-n;   }
    iterator &operator++()                { ++i; return *this; }
    iterator &operator--()                { --i; return *this; }
    iterator  operator++(int)             {      return i++;   }
    iterator  operator--(int)             {      return i--;   }

    operator int_type()             const {      return i;     }
};

inline ranger::range::iterator ranger::range::begin() const { return _start; }
inline ranger::range::iterator ranger::range::end()   const { return _end;   }

std::ostream &operator<<(std::ostream &os, const ranger::range &ir);
std::ostream &operator<<(std::ostream &os, const ranger &r);

