// Copyright 2018 Your Name <your_email>

#include <cstdint>
#include <string>

struct BrokerStats final {
    std::string lastDate;
    std::string account;
    std::size_t total;
    BrokerStats(std::size_t total, const std::string& account,
            const std::string& lastDate);
}; // struct BrokerStats

bool operator==(const BrokerStats& lhs, const BrokerStats& rhs);
