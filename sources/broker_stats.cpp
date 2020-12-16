// Copyright 2018 Your Name <your_email>

#include <broker_stats.hpp>

BrokerStats::BrokerStats(std::size_t total_, const std::string& account_,
        const std::string& lastDate_)
    : lastDate(lastDate_), account(account_), total(total_) {}
