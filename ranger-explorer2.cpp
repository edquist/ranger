#include <stdio.h>
#include "ranger.h"
#include "ranger_persist.h"

// the persist/load version (ie, non ostream)

void help()
{
    printf("%s",
        "Commands:\n"
        "+ START BACK       add range [START,BACK]\n"
        "- START BACK       remove range [START,BACK]\n"
        "r/c                reset\n"
        "q                  quit\n"
        "p                  print current set of ranges\n"
        "?/h                print this help\n"
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
    int start, back;
    char mode = buf[0];

    switch (sscanf(buf+1, "%d-%d", &start, &back)) {
    case 1:
        back = start;
        // falls through
    case 2:
        if (start > back) {
            printf("must specify START <= BACK\n");
        } else {
            if (mode == '+') {
                r.insert({start, back+1});
            } else {
                r.erase({start, back+1});
            }
        }
        break;
    default:
        printf("bad add/remove command: '%s'\n\n", buf);
        return -1;
    }
    return 0;
}

int main()
{
    ranger r;
    char buf[256];

    help();

    while (fgets(buf, sizeof buf, stdin)) {
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
        case '\n':
        case ' ':
            continue;
        default:
            printf("Command not understood: %s\n\n", buf);
            help();
        }
    }
    printf("Goodbye!\n");
}

