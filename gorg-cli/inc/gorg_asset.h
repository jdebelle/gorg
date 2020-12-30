
#include <vector>
#include <optional>
#include <string>

class GorgAsset
{
public:
	GorgAsset(const std::string& title, const std::string& description);

	bool IsValid();

	std::string GetTitle();
	std::string GetDescription();


private:
	std::string title_;
	std::string description_;
	std::vector<std::string> keywords_;
};



