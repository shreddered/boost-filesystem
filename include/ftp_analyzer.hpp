// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_FTP_ANALYZER_HPP_
#define INCLUDE_FTP_ANALYZER_HPP_

// broker stats
#include <broker_stats.hpp>
// STL headers
#include <map>
#include <ostream>
#include <regex>
#include <string>

class FtpAnalyzer final {
public:
    explicit FtpAnalyzer(const std::string& root, const std::string& filter);
    std::map<std::string, BrokerStats> analyze(std::ostream& os);
private:
    std::string root_;
    std::regex filter_;
    void analyzeImpl(const fs::path& currPath, std::ostream& os,
            std::map<std::string, BrokerStats>& stats);
}; // class FtpAnalyzer

#endif // INCLUDE_FTP_ANALYZER_HPP_
