#pragma once


#include <filesystem>
#include <vector>
#include <string>

#pragma warning(push, 0)
#include "inja.hpp"
#pragma warning(pop)

#include "asset_collection.h"
#include "gorg_asset.h"

class HtmlGenerator
{
public:
	HtmlGenerator(const std::filesystem::path& html_template);
	void AddAssetCollection(const AssetCollection& asset_collection);
	int Generate(const std::filesystem::path& output_path);

private:
	inja::Environment inja_env_;
	inja::Template inja_template_;
	nlohmann::json inja_data_;
	std::vector<GorgAsset> assets_;
	

};

