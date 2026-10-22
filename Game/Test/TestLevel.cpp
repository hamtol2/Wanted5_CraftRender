#include "TestLevel.h"
#include "TestActor.h"
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>

#include <Component/CameraComponent.h>

#include <Graphics/StaticMesh.h>
#include <Graphics/Shader.h>
//#include <Graphics/Renderer.h>
//#include <Math/Matrix4.h>
//#include <Core/Engine.h>

using namespace Craft;
void TestLevel::Initialized()
{
	Level::Initialized();

	// 리소스 생성.
	auto triangle = StaticMesh::CreateTriangleMesh();
	auto quad = StaticMesh::CreateQuadMesh();

	// 셰이더 생성.
	auto shader = Shader::CreateDefaultShader();

	// 액터 생성.
	auto left = SpawnActor<TestActor>();
	left->GetTransform().scale = Vector3::One * 0.4f;
	left->GetTransform().position.x = -0.5f;

	// 액터에 스태틱 메시 설정.
	left->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);

	// 셰이더 설정.
	left->GetComponent<StaticMeshComponent>()->SetShader(shader);

	auto right = SpawnActor<TestActor>();
	right->GetTransform().scale = Vector3::One * 0.4f;
	right->GetTransform().position.x = 0.5f;

	// 액터에 메시 설정 - 삼각형 메시.
	right->GetComponent<StaticMeshComponent>()->SetStaticMesh(triangle);
	right->GetComponent<StaticMeshComponent>()->SetShader(shader);

	auto center = SpawnActor<TestActor>();
	center->GetTransform().scale = Vector3::One * 0.4f;
	center->GetComponent<StaticMeshComponent>()->SetStaticMesh(quad);
	center->GetComponent<StaticMeshComponent>()->SetShader(shader);

	// 카메라.
	auto camera = SpawnActor<Actor>();
	camera->AddComponent<CameraComponent>();
	camera->GetTransform().position.z = -1.0f;
}

//void TestLevel::Draw()
//{
//	Level::Draw();
//
//	// 화면 너비/높이 얻기.
//	float width = static_cast<float>(Engine::Get().GetClientWidth());
//	float height = static_cast<float>(Engine::Get().GetClientHeight());
//
//	if (width == 0.0f || height == 0.0f)
//	{
//		return;
//	}
//
//	// 뷰 행렬 제출.
//	Vector3 eye(-0.5f, 0.0f, -5.0f);
//	Vector3 target = eye + Vector3::Forward;
//	Matrix4 view = Matrix4::LookAt(eye, target, Vector3::Up);
//
//	// 투영 변환 행렬 제출.
//	Matrix4 projection = Matrix4::Perspective(
//		60.0f,
//		width,
//		height,
//		0.1f,
//		1000.0f
//	);
//	
//	Renderer::Get().SubmitCamera(view, projection);
//}
