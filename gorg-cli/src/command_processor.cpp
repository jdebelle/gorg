#include "command_processor.h"

#include <iostream>
#include <boost/format.hpp>

static const std::string kInvalidCommand = "gorg: '%1%' is not a gorg command. See gorg --help";

using CommandPair = std::pair<std::string, std::function<int()>>;
using boost::format;

CommandProcessor::CommandProcessor(
	po::options_description options_description, 
	Command command, 
	po::variables_map variables_map) :
	command_(command),
	options_description_(options_description),
	variables_map_(variables_map)
{
	commands_.insert(CommandPair("init", std::bind(&CommandProcessor::Init, this)));
}

int CommandProcessor::Invoke()
{
	//
	//	If the command string is empty, run the global empty command
	//	method.
	//
	if (!command_.has_value())
		return EmptyCommand();

	//
	//	If the command cannot be found, show invalid command text
	//
	auto command_iterator = commands_.find(command_.value());
	if (command_iterator == commands_.end())
	{
		std::cout << format(kInvalidCommand) % command_.value() << std::endl;
		return -1;
	}

	//
	//	If the command has been found, run the associated method
	//
	return command_iterator->second();
}

void CommandProcessor::PrintHelp()
{
	std::cout << options_description_ << std::endl;
}



int CommandProcessor::EmptyCommand()
{
	if (variables_map_.count("help"))
	{
		PrintHelp();
		return 0;
	}

	if (variables_map_.count("version"))
	{
		std::cout << "THE VERSION STRING" << std::endl;
		return 0;
	}

	PrintHelp();
	return 1;
}


int CommandProcessor::Init()
{
	std::cout << "Run the init function!" << std::endl;
	return 0;
}
