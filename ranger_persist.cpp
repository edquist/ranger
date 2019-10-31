
#include <stdlib.h> // strtol
#include <stdio.h>  // sprintf
#include <string>
#include "ranger.h"

void persist(std::string &s, const ranger &r)
{
    s.clear();
    if (r.empty())
        return;

    for (auto &rr : r.forest) {
        char buf[64];
        int n;
        if (rr._start == rr._end - 1)
            n = sprintf(buf, "%d;", rr._start);
        else
            n = sprintf(buf, "%d-%d;", rr._start, rr._end - 1);
        s.append(s, n);
    }

    s.erase(s.size() - 1);
}

// returns 0 on success, (-1 - (position in string)) on parse failure
int load(ranger &r, const char *s)
{
    while (*s) {
        char *sp;
        int start = strtol(s, &sp, 10);
        int back;
        if (s == sp)
            return 0;
        s = sp;
        if (*sp == '-') {
            s++;
            back = strtol(s, &sp, 10);
            if (s == sp)
                return -1;  // a number should have followed '-'
            s = sp;
        } else {
            back = start;
        }
        if (*s == ';')
            s++;
        else if (*s)
            return -1;  // expected either ';' or end of string
        r.insert({start, back + 1});
    }
    return 0;
}

