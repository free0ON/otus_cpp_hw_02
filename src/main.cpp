#include <iostream>
#include <vector>
#include <algorithm>
#include "version.h"
#include "ipaddress.h"
/**
 * ip_filter program OTUS cpp hw 02
 * @param argc
 * @param argv "-h" option for help out
 * @return
 */
int main(void)
{
    try {
        std::vector<IPAddress> VectorOfIP;
        std::cin >> VectorOfIP;
        auto SortedIPVector = IPAddress::sort(VectorOfIP);
        std::cout   << SortedIPVector
                    << IPAddress::filter(SortedIPVector, "1.*.*.*")
                    << IPAddress::filter(SortedIPVector, "46.70.*.*")
                    << IPAddress::filter(SortedIPVector, "46");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}