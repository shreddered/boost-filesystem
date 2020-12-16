// Copyright 2018 Your Name <your_email>

// ftp analyzer
#include <ftp_analyzer.hpp>
// boost headers
#include <boost/filesystem.hpp>
// STL headers
#include <utility>
#include <iostream>

namespace fs = boost::filesystem;

FtpAnalyzer::FtpAnalyzer(const std::string& root)
    : root_(root), filter_("balance_(\\d+)_(\\d+)\\.txt") {}

std::multimap<std::string, BrokerStats> FtpAnalyzer::analyze(std::ostream& os) {
    fs::path p{root_};
    analyzeImpl(p, os);
    return stats;
}

void FtpAnalyzer::analyzeImpl(const fs::path& currPath, std::ostream& os) {
    const fs::directory_iterator it{currPath};
    for (const auto& entry : it) {
        if (fs::is_symlink(fs::symlink_status(entry.path()))) {
            auto linkPath = fs::read_symlink(entry.path());
            linkPath = fs::canonical(linkPath, currPath);
            analyzeImpl(linkPath, os);
        } else if (fs::is_directory(fs::status(entry.path()))) {
            analyzeImpl(entry.path(), os);
        } else if (fs::is_regular_file(fs::status(entry.path()))) {
            std::smatch match;
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, match, filter_)
                    && match.size() == 3) {
                std::string broker = entry.path()
                                .parent_path()
                                .filename()
                                .string(),
                            id = match[1].str(),
                            date = match[2].str();
                os << broker << ' ' << match[0].str() << std::endl;
                insert(broker, id, date);
            }
        }
    }
}

void FtpAnalyzer::insert(const std::string& broker, const std::string& account,
        const std::string& date) {
    if (stats.find(broker) == stats.end()) {
        stats.emplace(broker, BrokerStats{1, account, date});
        return;
    }
    auto range = stats.equal_range(broker);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.account == account) {
            it->second.total++;
            if (it->second.lastDate < date) {
                it->second.lastDate = date;
            }
            return;
        }
    }
    stats.emplace(broker, BrokerStats{1, account, date});
}
