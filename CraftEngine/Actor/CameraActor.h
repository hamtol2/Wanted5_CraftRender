#pragma once

#include <GameFramework/Actor.h>
#include <memory>

namespace Craft
{
	// 전방선언.
	class CameraComponent;

	// 카메라 컴포넌트를 갖는 카메라 액터.
	class CameraActor : public Actor
	{
	public:
		virtual void Initialized() override;

		// 투영 관련 속성 설정 함수.
		void SetProjection(
			float fieldOfView,
			float nearDistance = 0.1f,
			float farDistance = 1000.0f
		);

	private:
		std::shared_ptr<CameraComponent> cameraComponent;
	};
}