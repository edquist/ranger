#pragma once

#include <set>
#include <iosfwd>

struct ranger {
    struct range;
    struct iterator;
    typedef int                 int_type;
    typedef std::set<range>     set_type;
    typedef set_type::iterator  set_iterator;

    ranger() {};
    ranger(const std::initializer_list<range> &il);

    set_iterator insert(range r);
    set_iterator erase(range r);

    std::pair<set_iterator, bool> find(int_type x) const;

    bool contains(int_type x) const { return find(x).second; }
    bool empty()              const { return forest.empty(); }
    void clear()                    { forest.clear(); }

    inline iterator begin() const;
    inline iterator end()   const;

    friend std::ostream &operator<<(std::ostream &os, const ranger &r);

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
    bool contains(const range &r) const
    { return _start <= r._start && r._end < _end; }

    // only for use in our disjoint ranger forest context
    bool operator< (const range &r2) const { return _end < r2._end; }

    inline iterator begin() const;
    inline iterator end()   const;

    friend std::ostream &operator<<(std::ostream &os, const range &rr);

    // data members; a valid range in ranger forest context has _start < _end
    int_type _start;
    int_type _end;
};

struct ranger::range::iterator {
    typedef ranger::int_type int_type;
    typedef int_type         value_type;

    iterator() : i(0) {}
    iterator(int_type n) : i(n) {}

    int_type  operator*()           const {      return i;     }
    iterator  operator+(int_type n) const {      return i+n;   }
    iterator  operator-(int_type n) const {      return i-n;   }
    iterator &operator++()                { ++i; return *this; }
    iterator &operator--()                { --i; return *this; }
    iterator  operator++(int)             {      return i++;   }
    iterator  operator--(int)             {      return i--;   }

    // takes care of rel ops :D
    operator int_type()             const {      return i;     }

    // this is both the iterator "position" and the value
    int_type i;
};

struct ranger::iterator {
    typedef int_type value_type;

    iterator(set_iterator si) : sit(si), rit_valid(0) {}
    iterator() : rit_valid(0) {}

    int_type operator*();
    iterator &operator++();
    iterator &operator--();
    bool operator==(iterator &it);
    bool operator!=(iterator &it);

    private:
    void mk_valid();

    set_iterator sit;
    range::iterator rit;
    bool rit_valid;
};


inline ranger::iterator ranger::begin() const { return forest.begin(); }
inline ranger::iterator ranger::end()   const { return forest.end();   }

inline ranger::range::iterator ranger::range::begin() const { return _start; }
inline ranger::range::iterator ranger::range::end()   const { return _end;   }

