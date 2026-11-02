#pragma once

#include <memory>	// 스마트 포인터 사용을 위해.
#include <string>	// 텍스처 경로 등 문자열 사용을 위해.

namespace Craft
{
	// 전방 선언.
	class Shader;
	class Texture;

	class Material
	{
	public:
		Material() = default;
		virtual ~Material() = default;

		// 순수 가상 함수.
		virtual void Bind() const = 0;
	};

	// Default 셰이더를 사용하는 머티리얼.
	class DefaultMaterial /*final*/ : public Material
	{
	public:
		DefaultMaterial();
		~DefaultMaterial() = default;

	private:
		// 필수 가상 함수 구현.
		virtual void Bind() const override;

	private:
		// 셰이더.
		std::shared_ptr<Shader> shader;
	};

	// TextureMapping 셰이더를 사용하는 머티리얼.
	class TextureMappingMaterial /*final*/ : public Material
	{
	public:
		TextureMappingMaterial(const std::string& texturePath);
		~TextureMappingMaterial() = default;

	private:
		virtual void Bind() const override;

	private:
		// 셰이더.
		std::shared_ptr<Shader> shader;

		// 텍스처.
		std::shared_ptr<Texture> texture;
	};
}