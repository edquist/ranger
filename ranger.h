#pragma once

#include <set>

typedef struct ranger range_mask;

struct ranger {
    struct range;
    struct iterator;
    typedef int                 value_type;
    typedef std::set<range>     set_type;
    typedef set_type::iterator  set_iterator;

    ranger() {};
    ranger(const std::initializer_list<range> &il);

    set_iterator insert(range r);
    set_iterator erase(range r);

    std::pair<set_iterator, bool> find(value_type x) const;

    bool contains(value_type x) const { return find(x).second; }
    bool empty()                const { return forest.empty(); }
    void clear()                      { forest.clear(); }

    inline iterator begin() const;
    inline iterator end()   const;

    // the state of our ranger
    set_type forest;
};

struct ranger::range {
    struct iterator;
    typedef ranger::value_type value_type;

    range(value_type e) : _start(0), _end(e) {}
    range(value_type s, value_type e) : _start(s), _end(e) {}

    value_type size()             const { return _end - _start; }
    bool contains(value_type x)   const { return _start <= x && x < _end; }
    bool contains(const range &r) const
    { return _start <= r._start && r._end < _end; }

    // only for use in our disjoint ranger forest context
    bool operator< (const range &r2) const { return _end < r2._end; }

    inline iterator begin() const;
    inline iterator end()   const;

    // data members; a valid range in ranger forest context has _start < _end
    mutable value_type _start;
    mutable value_type _end;
};

struct ranger::range::iterator {
    typedef ranger::value_type value_type;

    iterator() : i(0) {}
    iterator(value_type n) : i(n) {}

    value_type  operator*()             const {      return i;     }
    iterator    operator+(value_type n) const {      return i+n;   }
    iterator    operator-(value_type n) const {      return i-n;   }
    iterator   &operator++()                  { ++i; return *this; }
    iterator   &operator--()                  { --i; return *this; }
    iterator    operator++(int)               {      return i++;   }
    iterator    operator--(int)               {      return i--;   }

    // takes care of rel ops :D
    operator value_type()               const {      return i;     }

    // this is both the iterator "position" and the value
    value_type i;
};

struct ranger::iterator {
    iterator(set_iterator si) : sit(si), rit_valid(0) {}
    iterator() : rit_valid(0) {}

    value_type operator*();
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

