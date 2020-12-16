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
// boost headers
#include <boost/filesystem.hpp>

class FtpAnalyzer final {
public:
    explicit FtpAnalyzer(const std::string& root);
    std::multimap<std::string, BrokerStats> analyze(std::ostream& os);
private:
    std::string root_;
    std::regex filter_;
    std::multimap<std::string, BrokerStats> stats;
    void analyzeImpl(const boost::filesystem::path& currPath,
            std::ostream& os);
    void insert(const std::string& broker, const std::string& id,
            const std::string& date);
}; // class FtpAnalyzer

#endif // INCLUDE_FTP_ANALYZER_HPP_
