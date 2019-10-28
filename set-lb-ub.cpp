#include <set>
#include <iostream>
#include <cstdlib>

bool usage(const char *prog)
{
    std::cout << "usage: " << prog << " N NUMBERS...\n\n"
              << "shows lower_bound / upper_bound of N in NUMBERS\n";
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        usage(argv[0]);

    int N = atoi(argv[1]);
    std::set<int> setty;
    for (int i = 2; i < argc; i++)
        setty.insert(atoi(argv[i]));

    // gross, i know
    auto lb = setty.lower_bound(N);
    auto ub = setty.upper_bound(N);
    std::cout << "lower_bound: ";
    if (lb == setty.end())
        std::cout << "END\n";
    else
        std::cout << *lb << "\n";

    std::cout << "upper_bound: ";
    if (ub == setty.end())
        std::cout << "END\n";
    else
        std::cout << *ub << "\n";
}

