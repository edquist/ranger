#include <iostream>
#include <vector>

#include "ranger.h"

int main()
{
    ranger r;

    r.insert({10,20});
    r.insert({50,60});
    r.insert({30,40});

    std::cout << r << "\n\n";

    for (int x = 5; x < 70; x += 5)
        std::cout << "contains " << x << " ?  "
                  << (r.contains(x) ? "yes" : "no") << "\n";


    std::cout << "\n---\n";
    std::cout << "\n";
    std::cout << "Arithmetic on: " << r << "\n";
    std::cout << "\n";

    std::vector<int> ints = {
        8,9,10,11,12,
        18,19,20,21,22,
        28,29,30,31,32,
        38,39,40,41,42,
        48,49,50,51,52,
        58,59,60,61,62
    };

    for (int s : ints)
    for (int e : ints) {
        if (s >= e)
            continue;
        ranger::range rr = {s,e};
        ranger r2 = r;
        r2.insert(rr);
        std::cout << " + " << rr << " -> " << r2 << "\n";
    }
}

