#include <iostream>
#include "ranger.h"

void help()
{
    std::cout <<
        "Commands:\n"
        "+ START END        add range [START,END)\n"
        "- START END        remove range [START,END)\n"
        "q                  quit\n"
        "p                  print current set of ranges\n"
        "?/h                print this help\n"
        "\n";
}

void print(const ranger &r) { std::cout << r << "\n\n"; }

int update(ranger &r, char mode)
{
    int start, end;
    if (std::cin >> start >> end) {
        if (start >= end) {
            std::cout << "must specify START < END\n";
        } else {
            if (mode == '+') {
                r.insert({start, end});
            } else {
                r.erase({start, end});
            }
        }
    } else {
        return -1;
    }
    return 0;
}

int main()
{
    ranger r;
    char c;

    help();

    while (std::cin >> c) {
        switch (c) {
        case '-':
        case '+':
            if (update(r, c) < 0)
                return 1;
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
            std::cout << "Command '" << c << "' not understood\n\n";
            help();
        }
    }
    std::cout << "Goodbye!\n";
}

