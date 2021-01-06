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
	HtmlGenerator(const std::filesystem::path& html_template, const std::filesystem::path& output_path);
	void AddAssetCollection(const AssetCollection& asset_collection);
	int Generate();

private:
	std::filesystem::path output_file_;
	inja::Environment inja_env_;
	inja::Template inja_template_;
	nlohmann::json inja_data_;
	std::vector<GorgAsset> assets_;
	

};

