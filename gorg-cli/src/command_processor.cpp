#include "command_processor.h"

#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <queue>

#pragma warning( push, 0 )
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#pragma warning( pop )


#include "project_paths.h"
#include "gorg_asset_file.h"
#include "asset_collection.h"

enum class Status
{
	kCancelled,
	kComplete,
	kInProgress,
};

static const std::string kInvalidCommand = "gorg: '%1%' is not a gorg command. See gorg --help";

using CommandPair = std::pair<std::string, std::function<int()>>;
using boost::format;

CommandProcessor::CommandProcessor(
	const std::filesystem::path& executable_dir,
	const std::filesystem::path& working_dir,
	const po::options_description& options_description,
	const Command& command,
	const po::variables_map& variables_map) :
	executable_dir_(executable_dir),
	working_dir_(working_dir),
	command_(command),
	options_description_(options_description),
	variables_map_(variables_map)
{
	commands_.insert(CommandPair("init", std::bind(&CommandProcessor::Init, this)));
	commands_.insert(CommandPair("validate", std::bind(&CommandProcessor::Validate, this)));
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

bool CommandProcessor::CreateFromTemplateIfNotExist(const std::filesystem::path& template_file, const std::filesystem::path& path, std::error_code& error_code)
{
	if (std::filesystem::exists(path))
		return false;
	
	std::filesystem::copy_file(template_file, path, error_code);
	return true;
}

int CommandProcessor::EditTextFile(const std::filesystem::path& path)
{
	//
	//	TODO - Make the editor configurable
	//
	std::cout.flush();
	std::string command = str(format("notepad \"%1%\"") % path.string());
	int exit_status = std::system(command.c_str());
	std::cout.flush();

	return exit_status;
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
	auto template_file = executable_dir_ / kGorgAssetTemplate;
	auto dst_file = working_dir_ / ".gorgasset";

	std::error_code error_code;
	if (!CreateFromTemplateIfNotExist(template_file, dst_file, error_code))
		std::cout << "File already exists, not creating new one" << std::endl;

	if (error_code.value() != 0)
	{
		std::cout << error_code.message() << std::endl;
		return 1;
	}

	Status status = Status::kInProgress;

	while (status == Status::kInProgress)
	{

		int exit_status = EditTextFile(dst_file);

		if (exit_status != 0)
		{
			std::cout << "Text editor returned status code " << exit_status << std::endl;
			return 1;
		}

		GorgAssetFile asset_file(dst_file);

		if (!asset_file.IsValid())
		{
			std::cout << asset_file.GetErrorMsg() << std::endl;

			std::cout << "Would you like to edit the file again? (Y/n) : ";

			std::string response;
			std::getline(std::cin, response);

			if (response == "n")
				status = Status::kCancelled;
		}
		else
		{
			status = Status::kComplete;
		}
	}

	assert(status != Status::kInProgress);

	if (status == Status::kCancelled)
	{
		std::cout << "gorgasset initialization cancelled" << std::endl;
		std::filesystem::remove(dst_file);
		return 1;
	}

	std::cout << "gorgasset created successfully" << std::endl;
	return 0;
}

int CommandProcessor::Validate()
{
	AssetCollection asset_collection(working_dir_);

	for (const auto& asset : asset_collection.GetAssets())
	{
		if (!asset.IsValid())
		{
			std::cout << "Error found in " << asset.GetPath() << std::endl;
			std::cout << asset.GetErrorMsg() << std::endl;
			return 1;
		}
	}
	
	std::cout << "Scanned " << asset_collection.GetAssets().size() << " gorgassets" << std::endl;
	std::cout << "No Errors Found" << std::endl;
	return 0;
}

int CommandProcessor::Generate()
{
	std::cout << "Run Generate" << std::endl;

	return 0;
}