#pragma once

#include <cstdint>
#include <vector>

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
}