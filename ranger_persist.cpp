
#include <stdlib.h> // strtol
#include "ranger.h"

#include "stl_string_utils.h"

void persist(std::string &s, const ranger &r)
{
    formatstr(s, "%s", "");
    if (r.empty())
        return;

    for (auto &rr : r.forest)
        if (rr._start == rr._end - 1)
            formatstr_cat(s, "%d;", rr._start);
        else
            formatstr_cat(s, "%d-%d;", rr._start, rr._end - 1);

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
        } else if (*sp == ';' || *sp == '\0') {
            back = start;
        } else {
            return -1;
        }
        r.insert({start, back + 1});
        if (*s == ';')
            s++;
        else if (*s)
            return -1;  // expected either ';' or end of string
    }
    return 0;
}

