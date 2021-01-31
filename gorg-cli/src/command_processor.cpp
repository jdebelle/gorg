#include "command_processor.h"

#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <queue>
#include <ctime>




#pragma warning( push, 0 )
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "inja.hpp"
#pragma warning( pop )


#include "project_paths.h"
#include "gorg_asset_file.h"
#include "asset_collection.h"
#include "html_generator.h"
#include "makefile.h"
#include "help.h"

#include <windows.h>
#include <shellapi.h>

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
	commands_.insert(CommandPair("help", std::bind(&CommandProcessor::Help, this)));
	commands_.insert(CommandPair("asset", std::bind(&CommandProcessor::Asset, this)));
	commands_.insert(CommandPair("generate", std::bind(&CommandProcessor::Generate, this)));
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
	std::cout << help_main << std::endl;
}

void CommandProcessor::OpenHelpPage(std::filesystem::path path)
{
	std::cout << "Opening html help page..." << std::endl;
	auto file = executable_dir_ / path;
	std::cout << file << std::endl;
	ShellExecute(0, 0, file.string().c_str(), 0, 0, SW_SHOW);
}

int CommandProcessor::Help()
{
	PrintHelp();
	return 0;
}


static inline std::string GetDateString()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	return buffer;
}

bool CommandProcessor::CreateFromTemplateIfNotExist(const std::filesystem::path& template_file, const std::filesystem::path& path)
{
	if (std::filesystem::exists(path))
		return false;

	inja::Environment inja_env;
	auto inja_template = inja_env.parse_template(template_file.string());
	nlohmann::json inja_data;

	inja_data["date"] = GetDateString();

	try
	{
		inja_env.write(inja_template, inja_data, path.string());
		return true;
	}
	catch (const inja::RenderError& e)
	{
		throw ("Failed to generate template file: " + e.message);
		return false;
	}
	
	//std::filesystem::copy_file(template_file, path, error_code);
	//return true;
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
		std::cout << VERSION_STRING << std::endl;
		return 0;
	}

	PrintHelp();
	return 1;
}



int CommandProcessor::Asset()
{
	if (variables_map_.count("help") > 0)
	{
		OpenHelpPage(help_asset);
		return 0;
	}

	if (variables_map_.count("validate") > 0)
	{
		return Validate();
	}


	if (variables_map_.count("init") == 0)
	{
		std::cout << "The only implemented action is --init" << std::endl;
		return 1;
	}


	auto template_file = executable_dir_ / kGorgAssetTemplate;
	auto dst_file = working_dir_ / ".gorgasset";

	try
	{
		if (!CreateFromTemplateIfNotExist(template_file, dst_file))
			std::cout << "File already exists, not creating new one" << std::endl;
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
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

//
//	TODO - Validate method for asset should only validate the current asset.
//
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
	if (variables_map_.count("help") > 0)
	{
		OpenHelpPage(help_generate);
		return 0;
	}

	std::vector<std::filesystem::path> directories;

	if (variables_map_.count("root") > 0)
	{
		auto paths = variables_map_["root"].as<std::vector<std::string>>();
		for (auto& path : paths)
			directories.push_back(std::filesystem::path(path));
	}
	else
	{
		directories.push_back(working_dir_);
	}

	HtmlGenerator html_generator(executable_dir_ / kGorgIndexTemplate, working_dir_ / "gorgindex.html");

	for (auto& path : directories)
	{
		AssetCollection asset_collection(path);
		html_generator.AddAssetCollection(asset_collection);
	}

	return html_generator.Generate();
}