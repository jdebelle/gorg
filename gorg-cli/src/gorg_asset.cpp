#include "gorg_asset.h"


GorgAsset::GorgAsset(const std::string& title, const std::string& description)
{
	title_ = title;
	description_ = description;
}

std::string GorgAsset::GetTitle() const
{
	return title_;
}

std::string GorgAsset::GetDescription() const
{
	return description_;
}

void GorgAsset::SetTags(const std::vector<std::string>& tags)
{
	tags_ = tags;
}

const std::vector<std::string>& GorgAsset::GetTags() const
{
	return tags_;
}

bool GorgAsset::IsValid() const
{
	if (title_.length() == 0)
		return false;

	if (description_.length() == 0)
		return false;

	return true;
}

void GorgAsset::AddKeyword(const std::string& keyword)
{
	keywords_.push_back(keyword);
}

const std::vector<std::string>& GorgAsset::GetKeywords() const
{
	return keywords_;
}


