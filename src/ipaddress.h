#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <string_view>
#include <cassert>

/**
 * class IPAddress provide sort, filter, string parsing, operators compare and cin/cout
 */
class IPAddress {
private:
    using TStringSize = std::string::size_type;
    using TVectorOfString = std::vector<std::string>;
    using TVectorOfIPAddress = std::vector<IPAddress>;
    using TOctet = u_char;
    union
    {
        struct {
            uint32_t d:8;
            uint32_t c:8;
            uint32_t b:8;
            uint32_t a:8;
        } ABCD;
        uint32_t IP;
    } IPUnion;
    std::string StringIP;
    /**
     * Split string StringToSplit by CharDelimiter and return by std::move to vector of strings
     * @param StringToSplit
     * @param CharDelimiter
     * @return ReturnIPVector
     */
    static TVectorOfString SplitString(const std::string& StringToSplit, const char CharDelimiter);

    static auto IPIntToString(const TOctet& a, const TOctet& b, const TOctet& c, const TOctet& d)
    {
        return std::to_string(a) +'.' + std::to_string(b) + '.' +
               std::to_string(c) + '.' + std::to_string(d);
    }

    void SetIPFromString(const std::string InputStringIP)
    {
        StringIP = InputStringIP;
        TVectorOfString VectorOfIP = SplitString(StringIP, '.');
        IPUnion.ABCD.a = std::stoi(VectorOfIP[0]);
        IPUnion.ABCD.b = std::stoi(VectorOfIP[1]);
        IPUnion.ABCD.c = std::stoi(VectorOfIP[2]);
        IPUnion.ABCD.d = std::stoi(VectorOfIP[3]);
    }

public:

    IPAddress()
    {
        StringIP = "";
        IPUnion.ABCD.a = 0;
        IPUnion.ABCD.b = 0;
        IPUnion.ABCD.c = 0;
        IPUnion.ABCD.d = 0;
        IPUnion.IP = 0;
    }

    IPAddress(const TOctet& a, const TOctet& b, const TOctet& c, const TOctet& d)
    {
        IPUnion.ABCD.a = a;
        IPUnion.ABCD.b = b;
        IPUnion.ABCD.c = c;
        IPUnion.ABCD.d = d;
        StringIP = IPIntToString(a, b, c, d);
    }

    explicit IPAddress(const TOctet ABCD[4])
    {
        if(size_t(ABCD) == 4) {
            IPUnion.ABCD.a = ABCD[0];
            IPUnion.ABCD.b = ABCD[1];
            IPUnion.ABCD.c = ABCD[2];
            IPUnion.ABCD.d = ABCD[3];
            StringIP = IPIntToString(ABCD[0], ABCD[1], ABCD[2], ABCD[3]);
        }
    }

    explicit IPAddress(const std::string& InputStringIP) {
        SetIPFromString(InputStringIP);
    }

    std::string GetStringIP() const {
        return StringIP;
    }

    uint32_t GetIp() const {
        return IPUnion.IP;
    }

    TOctet GetIntIp(const int& i) const {
        switch (i)
        {
            case 0: return IPUnion.ABCD.a; break;
            case 1: return IPUnion.ABCD.b; break;
            case 2: return IPUnion.ABCD.c; break;
            case 3: return IPUnion.ABCD.d; break;
            default: return -1;
        }
    }
    /**
     * SplitIP - split InputIPString "1.2.3.4<tab>txt1<tab>txt2.." by CharDelimiter and return
     * IPAddress in IpPositionInLine
     * @param InputIPString - string with IP and some text delimited by <tab>
     * @param CharDelimiter - <tab>
     * @param IpPositionInLine - start with 0 position IP address in InputIPString
     * @return IpToReturn - returned IP by std::move
     */
    static IPAddress SplitIP(const std::string& InputIPString, const char& CharDelimiter, const int& IpPositionInLine);
    /**
     * operator <
     * @param first
     * @param second
     * @return bool
     */
    friend bool operator< (const IPAddress& first, const IPAddress& second) {
        return first.GetIp() < second.GetIp();
    }
    /**
     * operator >
     * @param first
     * @param second
     * @return bool
     */
    friend bool operator> (const IPAddress& first, const IPAddress& second) {
        return first.GetIp() > second.GetIp();
    }
    /**
     * operator ==
     * @param first
     * @param second
     * @return
     */
    friend bool operator== (const IPAddress& first, const IPAddress& second) {
        return first.GetIp() == second.GetIp();
    }
    /**
     * operator == to filter by std::copy_of
     * Filter format "1.*.*.*", where * is any number
     * @param first
     * @param Filter
     * @return bool
     */
    friend bool operator== (const IPAddress& first, const std::string& Filter ) {
        TVectorOfString VectorOfString = SplitString(Filter, '.');
        auto VectorSize = VectorOfString.size();
        if(VectorSize == 4)
        {
            TOctet ABCD[4];
            for(int i = 0; i < 4; i++)
            {
                if(VectorOfString[i] == "*")
                    ABCD[i] = first.GetIntIp(i);
                else {
                    TOctet octet = std::stoi(VectorOfString[i]);
                    ABCD[i] = octet;
                }
            }
            IPAddress second(ABCD[0], ABCD[1], ABCD[2], ABCD[3]);
            return first.GetIp() == second.GetIp();
        }
        if(VectorSize== 1)
        {
            return first == std::stoi(VectorOfString[0]);
        }
        else
        {
            return false;
        }
    }
    /**
     * operator == to filter by std::copy_of
     * Filter by any octet
     * @param first
     * @param Filter
     * @return
     */
    friend bool operator== (const IPAddress& first, const TOctet& Filter )
    {
        return  (first.GetIntIp(0) == Filter) ||
                (first.GetIntIp(1) == Filter) ||
                (first.GetIntIp(2) == Filter) ||
                (first.GetIntIp(3) == Filter);
    }
    /**
     * stream out from IPAddress
     * @param OutStream
     * @param IPToPrint
     * @return
     */
    friend std::ostream & operator<<(std::ostream& OutStream, const IPAddress& IPToPrint)
    {
        OutStream << IPToPrint.GetStringIP();
        return OutStream;
    }
    /**
     * Stream in to IPAddress
     * @param InStream
     * @param IPToPrint
     * @return
     */
    friend std::istream & operator>>(std::istream& InStream, IPAddress& IPToPrint)
    {
        std::string line;
        InStream >> line;
        IPToPrint = IPAddress::SplitIP(line, '\t', 0);
        return InStream;
    }
    /**
     * Stream in to Vector of IPAddress
     * @param InStream
     * @param VectorIPToScan
     * @return
     */
    friend std::istream& operator>>(std::istream& InStream, TVectorOfIPAddress& VectorIPToScan)
    {
        for(std::string line; std::getline(InStream, line);)
        {
            VectorIPToScan.push_back(IPAddress::SplitIP(line, '\t', 0));
        }
        return InStream;
    }
    /**
     * Stream out from Vector of IPAddress
     * @param OutStream
     * @param VectorIPToPrint
     * @return
     */
    friend std::ostream& operator<<(std::ostream& OutStream, const TVectorOfIPAddress& VectorIPToPrint)
    {
        for(IPAddress IPToPrint: VectorIPToPrint)
            OutStream << IPToPrint << std::endl;
        return OutStream;
    }
    /**
     * operator= set IP from input const string
     * @param InputStringIP
     * @return
     */
    IPAddress& operator= (const std::string& InputStringIP)
    {
        SetIPFromString(InputStringIP);
        return *this;
    }
    /**
     * operator[] return octer at position i, where "1.2.3.4" i = 0 -> 1 and i = 3 -> 4
     * @param i
     * @return TOctet
     */
    TOctet operator[] (int i)
    {
        return this->GetIntIp(i);
    }
    /**
     * Reverse sort method in vector of IPAddress
     * @param VectorToSort
     * @return
     */
    static std::vector<IPAddress> sort(const std::vector<IPAddress>& VectorToSort);
    /**
     * Filter vector of IPAddress elements by Filter "46.70.*.*" where * is any number
     * 46 and 70 are numbers to compare with ip
     * VectorOfIP is input vector
     * FilteredIP is output vector returned by std::move
     * @param VectorOfIP
     * @param Filter
     * @return
     */
    static std::vector<IPAddress> filter(const TVectorOfIPAddress& VectorOfIP, const std::string& Filter);
};