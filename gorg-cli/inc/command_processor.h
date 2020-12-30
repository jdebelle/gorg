
#include <map>
#include <string>
#include <optional>

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using Command = std::optional<std::string>;

class CommandProcessor
{
public:
	CommandProcessor(po::options_description options_description, Command command, po::variables_map variables_map);

	int Invoke();

private:
	const Command command_;
	const po::variables_map variables_map_;
	const po::options_description options_description_;
	std::map<std::string, std::function<int()>> commands_;


	int EmptyCommand();
	void PrintHelp();
	int Init();
};

