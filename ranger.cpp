#include <iostream>
#include <vector>

#include "ranger.h"

int main()
{
    ranger r;

    r.add({10,20});
    r.add({50,60});
    r.add({30,40});

    std::cout << r << "\n";

    for (int x = 5; x < 70; x += 5)
        std::cout << x << " ?  " << r.contains(x) << "\n";


    std::cout << "\n";
    std::cout << r << "\n";
    std::cout << "\n";

    std::vector<irange> vir = {
        {5,9}, {5,10}, {5,11}, {5,15}, {5,19}, {5,20}, {5,21},
        {10,11}, {10,15}, {10,19}, {10,20}, {10,21},
        {12,15}, {12,19}, {12,20}, {12,21}, {12,25}, {12,50}, {12,55},
        {12,60}, {12,65},
        {5,70}, {15,45}, {20,50}, {21,50}, {21,49}
    }; 
    for (irange ir : vir) {
        ranger r2 = r;
        r2.add(ir);
        std::cout << " + " << ir << " -> " << r2 << "\n";
    }
}
