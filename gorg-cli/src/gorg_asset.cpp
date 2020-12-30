#include "gorg_asset.h"


GorgAsset::GorgAsset(const std::string& title, const std::string& description)
{
	title_ = title;
	description_ = description;
}

std::string GorgAsset::GetTitle()
{
	return title_;
}

std::string GorgAsset::GetDescription()
{
	return description_;
}

bool GorgAsset::IsValid()
{
	if (title_.length() == 0)
		return false;

	if (description_.length() == 0)
		return false;

	return true;
}



