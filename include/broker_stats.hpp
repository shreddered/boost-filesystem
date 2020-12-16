// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_BROKER_STATS_HPP_
#define INCLUDE_BROKER_STATS_HPP_

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

#endif // INCLUDE_BROKER_STATS_HPP_
