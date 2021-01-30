
#include <iostream>
#include <filesystem>

#pragma warning( push, 0 )
#include <boost/program_options.hpp>
#pragma warning( pop )

#include "command_processor.h"


namespace po = boost::program_options;



int main (int argc, char * argv[])
{
    std::filesystem::path executable_dir(argv[0]);
    executable_dir.remove_filename();

    po::options_description desc("Allowed Options");
    desc.add_options()
        ("help,h", "produce help message")
        ("version,v", "print gorg version")
        ("init,i", "initialize")
        ("validate", "validate that the asset is correctly formated")
        ("root", po::value<std::vector<std::string>>()->multitoken(), "path to act on")
        ("command", po::value<std::string>(), "command to execute")
        ("subargs", po::value<std::vector<std::string> >(), "Arguments for command");
        
    po::positional_options_description pos;
    pos.add("command", 1).
        add("subargs", -1);



    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv).
        options(desc).
        positional(pos).
        allow_unregistered().
        run();

    po::store(parsed, vm);
    po::notify(vm);

    std::optional<std::string> command;
    auto command_iterator = vm.find("command");
    if (command_iterator != vm.end())
        command.emplace(command_iterator->second.as<std::string>());
    
    
    CommandProcessor command_processor(
        executable_dir, 
        std::filesystem::current_path(), 
        desc, 
        command, 
        vm);

    return command_processor.Invoke();
    
}




