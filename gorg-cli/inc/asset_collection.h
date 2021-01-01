#pragma once

#include <filesystem>
#include <vector>

#include "gorg_asset_file.h"

class AssetCollection
{
public:
	AssetCollection(const std::filesystem::path& path);
	const std::vector<GorgAssetFile>& GetAssets();

private:
	std::vector<GorgAssetFile> asset_files_;

};


