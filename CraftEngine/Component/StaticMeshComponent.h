#pragma once

#include <Component/Component.h>
#include <memory>

namespace Craft
{
	// 전방 선언.
	class StaticMesh;
	class Shader;
	class Texture;

	class StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent() = default;
		~StaticMeshComponent() = default;

		virtual void Draw() override;

		// Setter.
		inline void SetStaticMesh(const std::shared_ptr<StaticMesh>& newMesh)
		{
			staticMesh = newMesh;
		}

		inline void SetShader(const std::shared_ptr<Shader>& newShader)
		{
			shader = newShader;
		}

		inline void SetTexture(const std::shared_ptr<Texture>& newTexture)
		{
			texture = newTexture;
		}

	private:
		// 스태틱 메시.
		std::shared_ptr<StaticMesh> staticMesh;
		
		// 셰이더.
		std::shared_ptr<Shader> shader;

		// 텍스처.
		std::shared_ptr<Texture> texture;
	};
}
