#pragma once

#include <Core/Core.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace Craft
{
	// 전방 선언.
	class Shader;

	// 엔진에서 사용하는 셰이더를 관리하는 관리자.
	class ShaderManager : public TGlobalAccessible<ShaderManager>
	{
	public:
		ShaderManager() = default;
		~ShaderManager() = default;

		// 셰이더 로드(또는 반환) 함수.
		std::shared_ptr<Shader> LoadShader(const std::wstring& name);

	private:
		// 관리하는 셰이더 객체.
		std::unordered_map<std::wstring, std::shared_ptr<Shader>> shaders;
	};
}