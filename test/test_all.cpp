#include <gtest/gtest.h>
#include "ipaddress.h"

/**
 * Google tests
 * ip compare
 * ip sort
 * ip filter
 */

TEST(ip_test, test_ip_compare) {
    ASSERT_TRUE(IPAddress("0.0.0.1") == IPAddress("0.0.0.1"));
    ASSERT_TRUE(IPAddress("0.0.0.1") == "0.0.*.1");
    ASSERT_TRUE(IPAddress("0.0.0.1") == "1");
    ASSERT_TRUE(IPAddress("0.0.0.2") > IPAddress("0.0.0.1"));
    ASSERT_TRUE(IPAddress("0.0.0.1") < IPAddress("0.0.0.2"));
    ASSERT_TRUE(IPAddress("1.2.1.1") < IPAddress("1.10.1.1"));
    ASSERT_TRUE(IPAddress("0.0.0.0") == IPAddress("0.0.0.0"));
}

TEST(ip_test, test_ip_sotr)
{
    std::vector<IPAddress> NotSortedVector;
    NotSortedVector.resize(5);
    NotSortedVector[0] = "0.0.0.1";
    NotSortedVector[1] = "0.0.1.0";
    NotSortedVector[2] = "0.1.0.0";
    NotSortedVector[3] = "1.0.0.0";
    NotSortedVector[4] = "1.0.0.1";
    auto SortedVector = IPAddress::sort(NotSortedVector);
    ASSERT_TRUE(SortedVector[0] == "1.0.0.1");
    ASSERT_TRUE(SortedVector[1] == "1.0.0.0");
    ASSERT_TRUE(SortedVector[2] == "0.1.0.0");
    ASSERT_TRUE(SortedVector[3] == "0.0.1.0");
    ASSERT_TRUE(SortedVector[4] == "0.0.0.1");
}

TEST(ip_test, test_ip_filter)
{
    std::vector<IPAddress> NotFiltredVector;
    NotFiltredVector.resize(5);
    NotFiltredVector[0] = "1.0.0.46";
    NotFiltredVector[1] = "1.0.1.0";
    NotFiltredVector[2] = "46.1.0.0";
    NotFiltredVector[3] = "46.70.0.0";
    NotFiltredVector[4] = "1.70.46.1";
    auto Filtred1 = IPAddress::filter(NotFiltredVector, "1.*.*.*");
    auto Filtred2 = IPAddress::filter(NotFiltredVector, "46.70.*.*");
    auto Filtred3 = IPAddress::filter(NotFiltredVector, "46");
    ASSERT_TRUE(Filtred1[0] == "1.0.0.46");
    ASSERT_TRUE(Filtred1[1] == "1.0.1.0");
    ASSERT_TRUE(Filtred1[2] == "1.70.46.1");
    ASSERT_TRUE(Filtred2[0] == "46.70.0.0");
    ASSERT_TRUE(Filtred3[0] == "1.0.0.46");
    ASSERT_TRUE(Filtred3[1] == "46.1.0.0");
    ASSERT_TRUE(Filtred3[2] == "46.70.0.0");
    ASSERT_TRUE(Filtred3[3] == "1.70.46.1");
}