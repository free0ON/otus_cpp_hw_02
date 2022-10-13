#include <string>
#include "version.h"
/**
 * version return PROJECT_VERSION imported from cmake
 * @return
 */
std::string Version() {
    return PROJECT_VERSION;
}

std::string Contacts()
{
    return EMAIL_CONTACT;
}

std::string Description()
{
    return PRJ_DESCRIPTION;
}

std::string HomePageUrl()
{
    return PRJ_HOMEPAGE_URL;
}
