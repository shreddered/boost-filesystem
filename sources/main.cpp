// Copyright 2018 Your Name <your_email>

// ftp analyzer
#include <ftp_analyzer.hpp>
// STL headers
#include <iostream>
// boost headers
#include <boost/program_options.hpp>

int main(int argc, char* argv[]) {
    boost::program_options::options_description desc("Allowed optoins");
    desc.add_options()
        ("help", "print help message and exit")
        ("path_to_ftp", boost::program_options::value<std::string>(),
         "path to FTP directory which will be analyzed");

    boost::program_options::variables_map vm;
    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (!vm.count("path_to_ftp")) {
        std::cout << desc << std::endl;
        return 1;
    }
    FtpAnalyzer analyzer(vm["path_to_ftp"].as<std::string>());
    auto stats = analyzer.analyze(std::cout);

    for (const auto& record : stats) {
        std::cout << "broker: " << record.first
            << " account: " << record.second.account
            << " files: " << record.second.total
            << " lastdate: " << record.second.lastDate
            << std::endl;
    }
    return 0;
}
