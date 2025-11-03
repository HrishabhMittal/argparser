#include "argparse.hpp"
#include <iostream>

int main(int argc, char** argv) {
    ArgParser parser(argc, argv);
    parser.addHelp();
    parser.addArg("input", 'i', "Input file path", "default.txt");
    parser.addFlag('v');
    parser.addArg("output", 'o', "Output file path", "output.txt");
    if (!parser.parse()) {
        std::cout << "Error parsing arguments.\n";
        std::cout << parser.getHelpMessage();
        return 1;
    }
    const auto& args = parser.Args();
    const auto& flags = parser.Flags();
    std::cout << "Input: " << args.at("input") << "\n";
    std::cout << "Output: " << args.at("output") << "\n";
    std::cout << "Verbose flag: " << (flags.at('v') ? "set" : "not set") << "\n";
    const auto& others = parser.Others();
    if (!others.empty()) {
        std::cout << "Other arguments:\n";
        for (const auto& other : others) {
            std::cout << "  " << other << "\n";
        }
    }
    return 0;
}