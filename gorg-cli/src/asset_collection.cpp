#include "asset_collection.h"

#include <queue>

AssetCollection::AssetCollection(const std::filesystem::path& path)
{
	std::queue<std::filesystem::path> dir_queue;
	dir_queue.push(path);

	while (!dir_queue.empty())
	{
		const auto dir = dir_queue.front();
		dir_queue.pop();

		auto asset_path = dir / ".gorgasset";
		if (std::filesystem::exists(asset_path))
		{
			GorgAssetFile asset_file(asset_path);
			asset_files_.push_back(asset_file);
		}
		else
		{
			for (const auto& entry : std::filesystem::directory_iterator(dir))
			{
				if (entry.is_directory())
					dir_queue.push(entry.path());
			}
		}
	}
}

const std::vector<GorgAssetFile>& AssetCollection::GetAssets() const
{
	return asset_files_;
}


