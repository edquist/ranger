#include <initializer_list>
#include <stdio.h>
#include <string>
#include "ranger.h"
#include "ranger_persist.h"

enum Action { Erase, Insert };

struct testcase {
    Action action;
    const char *input;
    const char *expected_result;
};

const std::initializer_list<testcase> test_table = {
    {Insert, "2",                         "2"                          },
    {Insert, "2",                         "2"                          },
    {Insert, "5-10",                      "2;5-10"                     },
    {Insert, "4;7;10-20;44;50-60",        "2;4-20;44;50-60"            },
    {Erase,  "55",                        "2;4-20;44;50-54;56-60"      },
    {Erase,  "56",                        "2;4-20;44;50-54;57-60"      },
    {Insert, "61",                        "2;4-20;44;50-54;57-61"      },
    {Insert, "56",                        "2;4-20;44;50-54;56-61"      },
    {Erase,  "61",                        "2;4-20;44;50-54;56-60"      },
    {Insert, "55",                        "2;4-20;44;50-60"            },
    {Insert, "3-43",                      "2-44;50-60"                 },
    {Insert, "70-80",                     "2-44;50-60;70-80"           },
    {Insert, "10-75",                     "2-80"                       },
    {Erase,  "5;10;20-30;41;42;45;50-55", "2-4;6-9;11-19;31-40;"
                                          "43-44;46-49;56-80"          },
    {Insert, "5-35",                      "2-40;43-44;46-49;56-80"     },
    {Erase,  "5-35",                      "2-4;36-40;43-44;46-49;56-80"},
    {Erase,  "85",                        "2-4;36-40;43-44;46-49;56-80"},
    {Erase,  "85-90",                     "2-4;36-40;43-44;46-49;56-80"},
    {Erase,  "1-5",                       "36-40;43-44;46-49;56-80"    },
    {Erase,  "2-3",                       "36-40;43-44;46-49;56-80"    },
    {Erase,  "1-100",                     ""                           },
    {Erase,  "2",                         ""                           },
    {Erase,  "2-4",                       ""                           }
};

int main()
{
    ranger r;
    std::string s;
    s.reserve(256);

    for (auto &t : test_table) {
        if (t.action == Insert) {
            if (load(r, t.input) < 0) {
                fprintf(stderr, "error loading range spec: '%s'\n", t.input);
                printf("FAIL\n");
                return 1;
            }
        } else {  // t.action == Erase
            ranger e;
            if (load(e, t.input) < 0) {
                fprintf(stderr, "error loading range spec: '%s'\n", t.input);
                printf("FAIL\n");
                return 1;
            }
            for (auto &range : e.forest)
                r.erase(range);
        }
        persist(s, r);
        if (s != t.expected_result) {
            fprintf(stderr, "unexpected result after %s '%s';\n"
                            "Expected: '%s'\n"
                            "Got:      '%s'\n",
                    (t.action == Insert ? "inserting" : "erasing"),
                    t.input, t.expected_result, s.c_str());
            printf("FAIL\n");
            return 1;
        }
    }
    printf("PASS\n");
    return 0;
}

