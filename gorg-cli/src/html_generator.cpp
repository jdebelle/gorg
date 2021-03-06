#include "html_generator.h"

#include <algorithm>




using json = nlohmann::json;


HtmlGenerator::HtmlGenerator(const std::filesystem::path& path, const std::filesystem::path& output_path)
{
	output_file_ = output_path;
	inja_template_ = inja_env_.parse_template(path.string());
	inja_data_["assetdata"] = json::array();
}

static inline std::string FormatPathURI(std::filesystem::path path)
{
	std::string result;
	bool isRelative = path.is_relative();

	if (isRelative)
		result = path.relative_path().string();
	else
		result = path.string();

	std::replace(result.begin(), result.end(), '\\', '/');

	if (!isRelative)
		result = "file:///" + result;

	return result;
}

void HtmlGenerator::AddAssetCollection(const AssetCollection& asset_collection)
{
	std::filesystem::path root = output_file_;
	root.remove_filename();

	for (const auto& asset_file : asset_collection.GetAssets())
	{
		if (!asset_file.IsValid())
		{
			std::cout << "Invalid asset file: " << asset_file.GetPath() << std::endl;
			continue;
		}

		const GorgAsset& asset = asset_file.GetAsset();
		json json_asset;
		
		json_asset["title"] = asset.GetTitle();
		json_asset["description"] = asset.GetDescription();

		const auto& tags = asset.GetTags();
		if (tags.size() > 0)
			json_asset["tags"] = tags;

		auto asset_folder = asset_file.GetPath();
		asset_folder.remove_filename();
		
		std::filesystem::path path;
		if (asset_folder.root_path() == root.root_path())
			path = std::filesystem::relative(asset_folder, root);
		else
			path = std::filesystem::absolute(asset_folder);
			
		json_asset["path"] = FormatPathURI(path);
		
		
		inja_data_["asset_data"].push_back(json_asset);
	}
}

int HtmlGenerator::Generate()
{
	//
	//	TODO - Proper error management
	//
	try
	{
		inja_env_.write(inja_template_, inja_data_, output_file_.string());
		return 0;
	}
	catch (const inja::RenderError& e)
	{
		std::cout << "Failed to generate html file: " << e.message << std::endl;
		return 1;
	}
}

