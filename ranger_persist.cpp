
#include "ranger.h"

#include "stl_string_utils.h"

void persist(std::string &s, const ranger &r)
{
    formatstr(s, "%s", "");
    if (r.empty())
        return;

    for (auto &rr : r.forest)
        if (rr._start == rr._end - 1)
            formatstr_cat(s, "%d", rr._start);
        else
            formatstr_cat(s, "%d-%d;", rr._start, rr._end);

    s.erase(s.size() - 1);
}

// returns 0 on success, (-1 - (position in string)) on parse failure
int load(ranger &r, const char *s)
{
    static const char start_back_sep = '-';
    static const char range_sep = ';';

    const char *sstart;
    int pos;
    int start, back;
    int ret;
    char c;

    for (;;) {
        // get range start
        ret = sscanf(s, "%d%n", &start, &pos);
        if (ret != 2)
            return 0;  // OK, we hit the end
        s += pos;
        ret = sscanf(s, "%c%n", &c, &pos);
        if (ret != 2) {
            back = start;
            r.insert({start, back + 1});
            return 0;  // OK, we hit the end
        }
        s += pos;
        switch (c) {
        case range_sep:
            back = start;
            r.insert({start, back + 1});
            break;
        case start_back_sep:
            // get range back
            ret = sscanf(s, "%d%n", &back, &pos);
            if (ret != 2)
                return -1 - int(s - sstart);
            s += pos;
            r.insert({start, back + 1});
            ret = sscanf(s, "%c%n", &c, &pos);
            if (ret != 2)
                return 0;  // OK, we hit the end
            s += pos;
            if (c != range_sep)
                return -1 - int(s - sstart);
        default:
            return -1 - int(s - sstart);
        }
    }
}

