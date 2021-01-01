#include "html_generator.h"





using json = nlohmann::json;


HtmlGenerator::HtmlGenerator(const std::filesystem::path& path)
{
	inja_template_ = inja_env_.parse_template(path.string());
}


