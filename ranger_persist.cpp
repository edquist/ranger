
#include <stdlib.h> // strtol
#include <stdio.h>  // sprintf
#include <string>
#include "ranger.h"

/*  persist / load ranger objects
 *
 *  The serialized format is one or more sub-ranges, separated by semicolons,
 *  where each sub-range is either N-M (for inclusive N..M) or N for a single
 *  integer.  Eg, "2", "5-10", "4;7;10-20;44;50-60"
 */

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
        s.append(buf, n);
    }

    s.erase(s.size() - 1);
}

// returns 0 on success, (-1 - (position in string)) on parse failure
int load(ranger &r, const char *s)
{
    const char *sstart = s;
    while (*s) {
        char *sp;
        int start = strtol(s, &sp, 10);
        int back;
        if (s == sp)
            // no int parsed is ok as long as we're at the end
            return *s ? -1 - int(s - sstart) : 0;
        s = sp;
        if (*sp == '-') {
            s++;
            back = strtol(s, &sp, 10);
            if (s == sp)
                // a number should have followed '-'
                return -1 - int(s - sstart);
            s = sp;
        } else {
            back = start;
        }
        if (*s == ';')
            s++;
        else if (*s)
            // expected either ';' or end of string
            return -1 - int(s - sstart);
        r.insert({start, back + 1});
    }
    return 0;
}

