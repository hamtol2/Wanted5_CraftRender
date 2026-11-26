#pragma once

#include <Core/Core.h>
#include <CraftAssets/AssetTypes.h>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace Craft
{
	class AssetManager : public TGlobalAccessible<AssetManager>
	{
	public:
		AssetManager(std::filesystem::path root = "Assets/Imported");
		~AssetManager();

		// 메시 로드 함수.
		std::shared_ptr<MeshAsset> LoadMesh(const std::string& assetName);

		// 텍스처 로드 함수.
		std::shared_ptr<TextureAsset> LoadTexture(const std::string& assetName);

	private:
		// 경로를 검색하는 함수.
		std::filesystem::path Resolve(const std::string& assetName) const;

	private:
		// 애셋 관리자가 사용하는 기본 루트 경로.
		std::filesystem::path root;

		// 커스텀 메시 테이블.
		std::unordered_map<std::string, std::shared_ptr<MeshAsset>> meshes;

		// 커스텀 텍스처 테이블.
		std::unordered_map<std::string, std::shared_ptr<TextureAsset>> textures;
	};
}