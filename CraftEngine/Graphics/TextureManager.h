#pragma once

#include <Core/Core.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace Craft
{
	// 전방 선언.
	class Texture;

	// 텍스처 리소스를 관리하는 관리자.
	class TextureManager : public TGlobalAccessible<TextureManager>
	{
	public:
		TextureManager() = default;
		~TextureManager() = default;

		// 텍스처 로드 함수.
		std::shared_ptr<Texture> LoadTexture(const std::string& texturePath);

	private:
		// 관리하는 텍스처 객체.
		std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
	};
}