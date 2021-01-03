#include "html_generator.h"





using json = nlohmann::json;


HtmlGenerator::HtmlGenerator(const std::filesystem::path& path)
{
	inja_template_ = inja_env_.parse_template(path.string());
	inja_data_["assetdata"] = json::array();
}


void HtmlGenerator::AddAssetCollection(const AssetCollection& asset_collection)
{
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
		
		inja_data_["asset_data"].push_back(json_asset);
	}
}

int HtmlGenerator::Generate(const std::filesystem::path& path)
{
	//
	//	TODO - Proper error management
	//
	try
	{
		inja_env_.write(inja_template_, inja_data_, path.string());
		return 0;
	}
	catch (const inja::RenderError& e)
	{
		std::cout << "Failed to generate html file: " << e.message << std::endl;
		return 1;
	}
}

