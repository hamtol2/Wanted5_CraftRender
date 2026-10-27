#pragma once

#include <d3d11.h>
#include <cstdint>
#include <string>
#include <memory>

namespace Craft
{
	// 이미지 파일을 로드하고, D3D 텍스처를 관리하는 클래스.
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		static std::shared_ptr<Texture> Load(const std::string& path);

	private:
		void LoadFromFile(const std::string& path);

	private:
		// 이미지 너비 / 높이.
		uint32_t width = 0;
		uint32_t height = 0;

		// D3D 텍스처 리소스.
		ID3D11Texture2D* texture = nullptr;
	};
}