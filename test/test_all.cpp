#include <gtest/gtest.h>
#include "ipaddress.h"

/**
 * Google tests
 * ip compare
 * ip sort
 */

TEST(ip_test, test_ip_compare) {
//    ASSERT_GT(version(), 0) << "version() is not > 0";
    IPAddress ip1("0.0.0.1"), ip2("0.0.0.1"), ip3("0.0.0.2");
    IPAddress ip4("1.2.1.1");
    IPAddress ip5("1.10.1.1");
    ASSERT_TRUE(ip1 == "0.0.0.1") << "0.0.0.1 == 0.0.0.1";
    ASSERT_TRUE(ip1 == "0.0.*.1") << "0.0.0.1 == 0.0.*.1";
    ASSERT_TRUE(ip1 == "1");
    ASSERT_TRUE(ip3 > ip1) << "0.0.0.2 > 0.0.0.1";
    ASSERT_TRUE(ip1 < ip3) << "0.0.0.1 < 0.0.0.1";
    ASSERT_TRUE(ip4 < ip5);
}

TEST(ip_test, test_ip_sotr)
{
    // TODO sort test
    IPAddress ip1("0.0.0.1"), ip2("0.0.0.1"), ip3("0.0.0.2");
    IPAddress ip4("1.2.1.1");
    IPAddress ip5("1.10.1.1");
    std::vector<IPAddress> vip1;
    vip1.push_back(ip1);
    vip1.push_back(ip2);
    vip1.push_back(ip3);
    vip1.push_back(ip4);
    vip1.push_back(ip5);
}