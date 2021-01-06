#pragma once

#include <map>
#include <string>
#include <optional>
#include <filesystem>

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using Command = std::optional<std::string>;

class CommandProcessor
{
public:
	CommandProcessor(
		const std::filesystem::path& executable_dir,
		const std::filesystem::path& working_dir,
		const po::options_description& options_description, 
		const Command& command, 
		const po::variables_map& variables_map);

	int Invoke();

private:
	const std::filesystem::path executable_dir_;
	const std::filesystem::path working_dir_;
	const Command command_;
	const po::variables_map variables_map_;
	const po::options_description options_description_;
	std::map<std::string, std::function<int()>> commands_;


	int EmptyCommand();
	void PrintHelp();
	int Asset();
	int Validate();
	int Generate();

	int EditTextFile(const std::filesystem::path& path);
	bool CreateFromTemplateIfNotExist(const std::filesystem::path& template_file, const std::filesystem::path& path) throw(std::string);
};

