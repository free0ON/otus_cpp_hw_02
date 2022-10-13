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
int main(int argc, char *argv[])
{
    std::string arg = "";
    if (argc == 2) arg = argv[1];
    if (arg == "-h")
    {
        std::cout << "OTUS c++ hw 02 ip_filter: v " << PROJECT_VERSION << std::endl;
        std::cout << PRJ_DESCRIPTION << std::endl;
        std::cout << PRJ_HOMEPAGE_URL << std::endl;
        std::cout << "contacts: " << EMAIL_CONTACT << std::endl;
    }
    try {
        std::vector<IPAddress> VectorOfIP;
        std::cin >> VectorOfIP;
        std::vector<IPAddress> SortedIPVector = IPAddress::sort(VectorOfIP);
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