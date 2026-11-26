#include "AssetManager.h"

#include <fstream>
#include <stdexcept>
#include <cassert>

namespace Craft
{
	namespace
	{
		// 파일 읽기 함수.
		template<typename T>
		void ReadPod(std::ifstream& input, T& value)
		{
			input.read(reinterpret_cast<char*>(&value), sizeof(T));
		}

		// 문자열 읽는 함수.
		std::string ReadString(std::ifstream& input)
		{
			// 크기 읽기.
			uint32_t size = 0;
			ReadPod(input, size);

			// 문자 배열 읽어서 채우기.
			std::string value(size, 0);
			input.read(value.data(), size);

			return value;
		}
	}

	AssetManager::AssetManager(std::filesystem::path root)
		: root(root)
	{}

	AssetManager::~AssetManager()
	{}

	std::shared_ptr<MeshAsset> AssetManager::LoadMesh(const std::string& assetName)
	{
		// 메시를 가지고 있는지 확인.
		auto result = meshes.find(assetName);
		if (result != meshes.end())
		{
			return result->second;
		}

		// 없으면 파일에서 로드.
		std::ifstream input(Resolve(assetName), std::ios::binary);
		if (!input.is_open())
		{
			throw std::runtime_error("Failed to open mesh asset: " + assetName);
			return {};
		}

		// 메시 애셋을 구분하는 문자 값.
		char magic[4] = {};
		input.read(magic, sizeof(magic));

		// 애셋 버전.
		uint32_t version = 0;
		ReadPod(input, version);

		// 읽은 데이터 확인(무결성 검증).
		if (std::memcmp(magic, cMeshMagic, sizeof(cMeshMagic)) != 0
			|| version != assetVersion)
		{
			throw std::runtime_error("Invalid mesh asset: " + assetName);
			return {};
		}

		// 정점/인덱스 개수.
		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;
		ReadPod(input, vertexCount);
		ReadPod(input, indexCount);

		// 정점/인덱스 배열 정보를 로드해서 채우기.
		auto mesh = std::make_shared<MeshAsset>();

		mesh->vertices.resize(vertexCount);
		mesh->indices.resize(indexCount);

		input.read(
			reinterpret_cast<char*>(mesh->vertices.data()),
			sizeof(AssetVertex) * vertexCount
		);

		input.read(
			reinterpret_cast<char*>(mesh->indices.data()),
			sizeof(uint32_t) * indexCount
		);

		// 서브 메시 정보 로드.
		uint32_t subMeshCount = 0;
		ReadPod(input, subMeshCount);

		mesh->subMeshes.resize(subMeshCount);

		for (AssetSubMesh& subMesh : mesh->subMeshes)
		{
			ReadPod(input, subMesh.indexOffset);
			ReadPod(input, subMesh.indexCount);
			subMesh.textureAsset = ReadString(input);
		}

		// 테이블에 추가.
		meshes.emplace(assetName, mesh);
		return mesh;
	}

	std::shared_ptr<TextureAsset> AssetManager::LoadTexture(
		const std::string& assetName)
	{
		// 이미 가진 애셋인지 확인 후 반환.
		auto result = textures.find(assetName);
		if (result != textures.end())
		{
			return result->second;
		}

		// 이미 가지지 않았다면 로드 후 테이블에 추가하고 반환.
		// 파일 열기.
		std::ifstream input(Resolve(assetName), std::ios::binary);

		// 파일 읽기 확인.
		if (!input.is_open())
		{
			throw std::runtime_error("Failed to open texture asset: " + assetName);
			return {};
		}

		// 텍스처 애셋 저장한 순서대로 데이터 읽어오기.
		char magic[4] = {};
		input.read(magic, sizeof(magic));

		// 애셋 버전 로드.
		uint32_t version = 0;
		ReadPod(input, version);

		// 읽은 데이터 확인(무결성 검증).
		if (std::memcmp(magic, cTextureMagic, sizeof(cTextureMagic)) != 0
			|| version != assetVersion)
		{
			throw std::runtime_error("Invalid texture asset: " + assetName);
			return {};
		}

		// 텍스처 애셋 생성.
		auto texture = std::make_shared<TextureAsset>();

		// 기본 데이터 로드.
		ReadPod(input, texture->width);
		ReadPod(input, texture->height);
		ReadPod(input, texture->channels);

		// 픽셀 배열 데이터 읽기.
		const size_t byteCount
			= static_cast<size_t>(texture->width)
			* texture->height
			* texture->channels;

		texture->pixels.resize(byteCount);
		input.read(
			reinterpret_cast<char*>(texture->pixels.data()),
			static_cast<std::streamsize>(byteCount)
		);

		// 테이블에 추가.
		textures.emplace(assetName, texture);
		return texture;
	}

	std::filesystem::path AssetManager::Resolve(const std::string& assetName) const
	{
		// 전달 받은 값으로 경로 생성.
		std::filesystem::path path(assetName);

		// 절대 경로이면 그대로 반환
		if (path.is_absolute())
		{
			return path;
		}

		// 이미 찾을 수 있으면 반환.
		if (std::filesystem::exists(path))
		{
			return path;
		}

		// 루트 경로 고려해서 추가 검색.
		std::filesystem::path direct = root / path;
		if (std::filesystem::exists(direct))
		{
			return direct;
		}

		return direct;
	}
}