#include "TestActor.h"
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>
#include <Core/Input.h>
#include <iostream>

void TestActor::Initialized()
{
	Actor::Initialized();

	// 스태틱 메시 컴포넌트 추가.
	AddComponent<Craft::StaticMeshComponent>();
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	// 회전.
	GetTransform().rotation.z += 60.0f * deltaTime;

	// W키 입력 테스트.
	Craft::Input& input = Craft::Input::Get();

	if (input.GetKeyDown('W'))
	{
		std::cout << "W key down\n";
	}

	if (input.GetKeyUp('W'))
	{
		std::cout << "W key up\n";
	}

	if (input.GetKey('W'))
	{
		std::cout << "W key hold\n";
	}

	// 마우스 입력 테스트.
	if (input.GetMouseButtonDown(0))
	{
		std::cout << "Left Mouse Down\n";
	}

	if (input.GetMouseButtonUp(0))
	{
		std::cout << "Left Mouse Up\n";
	}

	// 버튼 누르고 있을 때는 마우스 위치.
	if (input.GetMouseButton(0))
	{
		std::cout
			<< "Mouse Delta: "
			<< input.GetMouseDeltaX()
			<< ", "
			<< input.GetMouseDeltaY()
			<< "\n";
	}
}