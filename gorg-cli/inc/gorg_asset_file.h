#pragma once

#include <filesystem>
#include <optional>

#include "gorg_asset.h"

class GorgAssetFile
{
public:
	GorgAssetFile(const std::filesystem::path& path);
	bool IsValid() const;
	std::string GetErrorMsg() const;
	const GorgAsset& GetAsset() const;
	const std::filesystem::path& GetPath() const;

private:
	const std::filesystem::path path_;
	std::optional<GorgAsset> gorg_asset_;
	std::optional<std::string> error_msg_;
	
};




