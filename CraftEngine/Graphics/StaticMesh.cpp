#include "StaticMesh.h"
#include "Renderer.h"
#include "Vertex.h"
#include "AssetManager.h"

#include <Core/Core.h>
#include <cassert>
#include <stdexcept>

namespace Craft
{
	StaticMesh::StaticMesh(
		const std::vector<Vertex>& vertices, 
		const std::vector<uint32_t>& indices)
	{
		// 정점/인덱스 배열의 항목 수가 0보다 큰지 확인.
		assert(vertices.size() > 0);
		assert(indices.size() > 0);

		// 인덱스 개수 설정.
		indexCount = static_cast<uint32_t>(indices.size());

		// 정점 데이터 바이트 너비 설정.
		stride = sizeof(vertices[0]);

		// 장치 얻어오기.
		auto& device = Renderer::Get().GetDevice();

		// 버퍼 구성 정보.
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = static_cast<uint32_t>(stride * vertices.size());
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 버퍼에 저장할 데이터.
		D3D11_SUBRESOURCE_DATA vertexBufferData = {};
		vertexBufferData.pSysMem = vertices.data();

		ThrowIfFailed(device.CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&vertexBuffer
		), L"Failed to create vertex buffer");

		// 버퍼 구성 정보.
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth 
			= sizeof(uint32_t) * static_cast<uint32_t>(indices.size());
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 버퍼에 저장할 데이터.
		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = indices.data();

		ThrowIfFailed(device.CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&indexBuffer
		), L"Failed to create index buffer");
	}

	StaticMesh::~StaticMesh()
	{
		// 리소스 해제.
		SafeRelease(vertexBuffer);
		SafeRelease(indexBuffer);
	}

	void StaticMesh::Bind() const
	{
		// 컨텍스트 가져오기.
		auto& context = Renderer::Get().GetContext();

		uint32_t offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		// 토폴로지 -> 정점을 어떻게 이어서 도형을 만들지 결정하는 방식.
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	std::shared_ptr<StaticMesh> StaticMesh::CreateTriangleMesh()
	{
		return std::make_shared<StaticMesh>(
			std::vector<Vertex> {
				Vertex{ Vector3(0.0f, 0.5f, 0.5f), Vector2(0.5f, 0.0f) },
				Vertex{ Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 1.0f) }, 
				Vertex{ Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 1.0f) }
			},
			std::vector<uint32_t> { 0, 1, 2 }
		);
	}

	std::shared_ptr<StaticMesh> StaticMesh::CreateQuadMesh()
	{
		return std::make_shared<StaticMesh>(
			std::vector<Vertex> {
				Vertex { Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f) },
				Vertex { Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f) },
				Vertex { Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 1.0f) },
				Vertex{ Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 1.0f) },
			}, 
			std::vector<uint32_t> { 0, 1, 2, 0, 2, 3 }
		);
	}

	std::shared_ptr<StaticMesh> StaticMesh::LoadFromFile(
		const std::string& path)
	{
		// 커스텀 cmesh 애셋 로드.
		const auto asset = AssetManager::Get().LoadMesh(path);

		// 로드 실패 처리.
		if (!asset)
		{
			throw std::runtime_error("Failed to load cmesh asset: " + path);
			return {};
		}

		// 정점/인덱스 배열이 제대로 설정됐는지 확인.
		if (asset->vertices.empty() || asset->indices.empty())
		{
			throw std::runtime_error("Asset has no vertices");
			return {};
		}

		// 커스텀 애셋 데이터를 엔진의 데이터로 변환.
		// 정점 배열 선언.
		std::vector<Vertex> vertices;

		// 정점 배열 크기 확보(재할당 방지).
		vertices.reserve(asset->vertices.size());

		// 애셋에서 엔진의 정점 데이터로 변환 및 배열에 추가.
		for (const AssetVertex& sourceVertex : asset->vertices)
		{
			// 정점 선언.
			Vertex vertex;

			// 위치 저장.
			vertex.position = {
				sourceVertex.position.x,
				sourceVertex.position.y,
				sourceVertex.position.z
			};

			// 텍스처 좌표(UV) 저장.
			vertex.uv = { sourceVertex.uv.x, sourceVertex.uv.y };

			// 배열에 추가.
			vertices.emplace_back(std::move(vertex));
		}

		// 스태틱 메시 생성 후 반환.
		return std::make_shared<StaticMesh>(vertices, asset->indices);
	}
}