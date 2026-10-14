#include "TestLevel.h"
#include "TestActor.h"
#include <Component/TransformComponent.h>
#include <Graphics/StaticMesh.h>

using namespace Craft;
void TestLevel::Initialized()
{
	Level::Initialized();

	// 리소스 생성.
	auto triangle = StaticMesh::CreateTriangleMesh();
	auto quad = StaticMesh::CreateQuadMesh();

	// 액터 생성.
	auto left = SpawnActor<TestActor>();
	left->GetTransform().scale = Vector3::One * 0.4f;
	left->GetTransform().position.x = -0.5f;
	
	// 액터에 스태틱 메시 설정.
	left->SetStaticMesh(quad);

	auto right = SpawnActor<TestActor>();
	right->GetTransform().scale = Vector3::One * 0.4f;
	right->GetTransform().position.x = 0.5f;

	// 액터에 메시 설정 - 삼각형 메시.
	right->SetStaticMesh(triangle);

	auto center = SpawnActor<TestActor>();
	center->GetTransform().scale = Vector3::One * 0.4f;
	center->SetStaticMesh(quad);
}
