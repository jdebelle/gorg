#pragma once

#include <vector>
#include <optional>
#include <string>

class GorgAsset
{
public:
	GorgAsset(const std::string& title, const std::string& description);

	bool IsValid();

	std::string GetTitle() const;
	std::string GetDescription() const;

	void AddKeyword(const std::string& keyword);
	const std::vector<std::string>& GetKeywords() const;

private:
	std::string title_;
	std::string description_;

	std::string absolute_path_;
	std::string relative_path_;

	std::vector<std::string> keywords_;
};



