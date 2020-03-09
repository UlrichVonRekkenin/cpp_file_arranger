#include <iostream>
#include <boost/program_options.hpp>
#include "source/sorter.h"


int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    namespace fs = std::filesystem;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce this message")
            ("from,f", po::value<fs::path>(), "Directory to be sorted")
            ("to,t", po::value<fs::path>(), "Directory to be moved. Default value is `from`.")
            ("config,c", po::value<fs::path>(), "Path to config file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc==1) {
        std::cout << desc << std::endl;
        return 1;
    }

    const auto dest{vm["from"].as<fs::path>()};
    const auto to = vm.count("to") ? vm["to"].as<fs::path>() : dest;
    const auto conf = vm.count("conf") ? vm["conf"].as<fs::path>() : "";

    tools::Sorter::sort(dest, to, conf);

    return 0;
}
