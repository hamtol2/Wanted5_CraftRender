#pragma once

#include <cstdint>
#include <vector>
#include <string>

// 임포터 및 엔진에서 사용할 커스텀 공용 애셋 타입.
namespace Craft
{
	// 시그니처(텍스처/메시 구분 용도).
	inline constexpr char cMeshMagic[4] = { 'M', 'E', 'S', 'H'};
	inline constexpr char cTextureMagic[4] = { 'C', 'T', 'E', 'X'};
	inline constexpr uint32_t assetVersion = 1;

	// 텍스처 애셋 정의.
	struct TextureAsset
	{
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t channels = 4;
		std::vector<uint8_t> pixels;
	};

	// 애셋에서 사용할 Vector.
	struct AssetVector2
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	struct AssetVector3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	// 애셋에 저장할 정점 구조체.
	struct AssetVertex
	{
		AssetVector3 position;
		AssetVector2 uv;
		AssetVector3 normal;
		AssetVector3 tangent;
		AssetVector3 bitangent;
	};

	// 서브 메시 구조체.
	// -> 메시 구조 안에 정의되어 있는 하위 메시 정보.
	// [][][][][][]->0 [][][][][]->1 [][][][]->2...
	struct AssetSubMesh
	{
		uint32_t indexOffset = 0;
		uint32_t indexCount = 0;
		std::string textureAsset;
	};

	// 메시 애셋 구조체.
	struct MeshAsset
	{
		// 정점 배열 정보.
		std::vector<AssetVertex> vertices;

		// 인덱스 배열 정보.
		std::vector<uint32_t> indices;

		// 서브 메시 배열 정보.
		std::vector<AssetSubMesh> subMeshes;
	};
}