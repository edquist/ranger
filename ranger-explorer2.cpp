#include <stdio.h>
#include <string.h>
#include "ranger.h"
#include "ranger_persist.h"

// the persist/load version (ie, non ostream)

void help()
{
    printf("%s",
        "Commands:\n"
        "+ RANGE_SPEC       load range spec\n"
        "- RANGE_SPEC       remove range spec\n"
        "r/c                reset\n"
        "q                  quit\n"
        "p                  print current set of ranges\n"
        "?/h                print this help\n"
        "\n"
        "Note: RANGE_SPEC is one or more ';'-separated items of the form\n"
        "      N or N-M.  Eg, '2', '5-10', '4;7;10-20;44;50-60'\n"
        "\n");
}

void print(const ranger &r)
{
    std::string s;
    persist(s, r);
    printf("\"%s\"\n\n", s.c_str());
}

int update(ranger &r, const char *buf)
{
    char mode = buf[0];

    if (mode == '+') {
        int ret = load(r, buf+1);
        if (ret == 0) {
            return 0;
        } else {
            printf("parse error\n\n");
            return -1;
        }
    } else {
        ranger r2;
        int ret = load(r2, buf+1);
        if (ret != 0) {
            printf("parse error\n\n");
            return -1;
        }
        for (auto &rr : r2)
            r.erase(rr);
    }
    return 0;
}

void chomp(char *buf)
{
    size_t len = strlen(buf);
    if (buf[len-1] == '\n')
        buf[len-1] = 0;
}

int main()
{
    ranger r;
    char buf[256];

    help();

    while (fgets(buf, sizeof buf, stdin)) {
        chomp(buf);
        switch (buf[0]) {
        case '-':
        case '+':
            if (update(r, buf) < 0)
                break;
            print(r);
            break;
        case 'c':  
        case 'r':  
            r.clear();
            print(r);
            break;
        case 'p':  
            print(r);
            break;
        case 'q':  
            return 0;
        case 'h':
        case '?':
            help();
            break;
        case '\0':
        case '\n':
        case ' ':
        case '#':
            continue;
        default:
            printf("Command not understood: %s\n\n", buf);
            help();
        }
    }
    printf("Goodbye!\n");
}

