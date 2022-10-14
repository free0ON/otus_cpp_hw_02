#include <algorithm>
#include <ostream>
#include "ipaddress.h"
/**
 * Split string StringToSplit by CharDelimiter and return by std::move to vector of strings
 * @param StringToSplit
 * @param CharDelimiter
 * @return
 */
IPAddress::TVectorOfString IPAddress::SplitString(const std::string& StringToSplit, const char CharDelimiter)
{
    TVectorOfString ReturnIPVector;
    TStringSize LastPosition = 0;
    TStringSize CurrentPosition = StringToSplit.find(CharDelimiter);
    while (CurrentPosition != std::string::npos)
    {
        ReturnIPVector.push_back(StringToSplit.substr(LastPosition, CurrentPosition - LastPosition));
        LastPosition = CurrentPosition + 1;
        CurrentPosition = StringToSplit.find(CharDelimiter, LastPosition);
    }
    ReturnIPVector.push_back(StringToSplit.substr(LastPosition));
    return std::move(ReturnIPVector);
}
/**
 * Split string InputIPString with IP address and other symbols by char CharDelimiter
 * and return only element at IpPositionInLine
 * @param InputIPString - Input string
 * @param CharDelimiter - delimiter
 * @param IpPositionInLine - position IP in splitted string
 * @return IpToReturn
 */
IPAddress IPAddress::SplitIP(const std::string& InputIPString, const char& CharDelimiter, const int& IpPositionInLine)
{
    TVectorOfString VectorOfIPStrings = SplitString(InputIPString, CharDelimiter);
    IPAddress IpToReturn;
    if (IpPositionInLine <= VectorOfIPStrings.size())
        for(int i = 0; i < VectorOfIPStrings.size(); i++)
        {
            if(i == IpPositionInLine)
                IpToReturn = IPAddress(VectorOfIPStrings[i]);
        }
    return std::move(IpToReturn);
}
/**
 * Filter vector of IPAddress elements by Filter "46.70.*.*" * - any number
 * @param VectorOfIP is input vector
 * @param Filter "46.70.*.*" where * is any number 46 and 70 are numbers to compare with ip
 * @return s output vector returned by std::move
 */
std::vector<IPAddress> IPAddress::filter(const std::vector<IPAddress>& VectorOfIP, const std::string& Filter) {
    std::vector<IPAddress> FilteredIP;
    std::copy_if(VectorOfIP.begin(), VectorOfIP.end(),\
                 std::back_inserter(FilteredIP),\
                 [&Filter](const IPAddress &ip) {\
                     return ip == Filter;\
                 });
    return std::move(FilteredIP);
}
/**
 * Reverse sort method in vector of IPAddress
 * @param VectorToSort - input vector
 * @return SortedIPVector - output vector, returned by move semantic method std::move
 */
std::vector<IPAddress> IPAddress::sort(const std::vector<IPAddress>& VectorToSort) {
    std::vector<IPAddress> SortedIPVector;
    std::copy(VectorToSort.begin(), VectorToSort.end(), std::back_inserter(SortedIPVector));

    std::sort(SortedIPVector.begin(), SortedIPVector.end(),
              [](const IPAddress& ip1, const IPAddress& ip2)
              {
                  return ip1 > ip2;
              }
    );
    return std::move(SortedIPVector);
}
/**
 */
