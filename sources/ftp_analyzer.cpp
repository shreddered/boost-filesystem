// Copyright 2018 Your Name <your_email>

// ftp analyzer
#include <ftp_analyzer.hpp>
// boost headers
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

FtpAnalyzer::FtpAnalyzer(const std::string& root, const std::string& filter)
    : root_(root), filter_(filter) {}

std::map<std::string, BrokerStats> FtpAnalyzer::analyze(std::ostream& os) {
    std::map<std::string, BrokerStats> stats;
    fs::path p{root_};
    analyzeImpl(p, os, stats);
    return stats;
}

void FtpAnalyzer::analyzeImpl(const fs::path& currPath, std::ostream& os,
        std::map<std::string, BrokerStats>& stats) {
}
