#include "gorg_asset_file.h"

#include <filesystem>
#include <iostream>

#pragma warning( push, 0 )
#include "yaml-cpp/yaml.h"
#pragma warning( pop ) 



using namespace std::filesystem;



GorgAssetFile::GorgAssetFile(const path& path) : 
	path_(path)
{
	try
	{
		YAML::Node node = YAML::LoadFile(path.string());

		if (!node.IsMap())
			return;

		auto title = node["title"];
		auto description = node["description"];

		bool valid_title = (title.IsDefined() && title.IsScalar());
		bool valid_description = (description.IsDefined() && description.IsScalar());

		if (!valid_title)
		{
			error_msg_ = "Missing or invalid title";
			return;
		}

		if (!valid_description)
		{
			error_msg_ = "Missing or invalid description";
			return;
		}

		auto keywords = node["keywords"];

		if (keywords.IsDefined() && !keywords.IsSequence())
		{
			error_msg_ = "Invalid Keywords Definition";
			return;
		}

		if (keywords.IsDefined())
		{
			for (auto keyword : keywords)
			{
				if (!keyword.IsDefined() || !keyword.IsScalar())
				{
					error_msg_ = "Invalid Keywords Definition";
					return;
				}
			}
		}

		gorg_asset_ = GorgAsset(
			title.as<std::string>(),
			description.as<std::string>());

		if (keywords.IsDefined())
		{
			for (auto keyword : keywords)
				gorg_asset_->AddKeyword(keyword.as<std::string>());
		}



	}
	catch (const YAML::ParserException& e)
	{
		gorg_asset_.reset();
		error_msg_ = e.msg;
	}
	//std::cout << ((keywords.IsDefined() &&  ?  : "NOT DEFINED") << std::endl;
}

bool GorgAssetFile::IsValid() const
{
	if (!gorg_asset_.has_value())
		return false;

	return gorg_asset_->IsValid();
}

std::string GorgAssetFile::GetErrorMsg() const
{
	return error_msg_.value_or("OK");
}

const GorgAsset& GorgAssetFile::GetAsset() const
{
	return gorg_asset_.value();
}

const std::filesystem::path& GorgAssetFile::GetPath() const
{
	return path_;
}