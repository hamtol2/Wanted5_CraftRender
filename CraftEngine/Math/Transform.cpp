#include "Transform.h"

namespace Craft
{
	Transform::Transform()
	{
		Update();
	}

	void Transform::Update()
	{
		// 월드 행렬 업데이트.
		// 변환 곱셈 순서 중요함 (SRT).
		// 그래픽스 면접 문제에 자주 출제.
		worldMatrix
			= Matrix4::Scale(scale)
			* Matrix4::Rotation(rotation)
			* Matrix4::Translation(position);
	}

	Vector3 Transform::Right() const
	{
		return Vector3::Right * Matrix4::Rotation(rotation);
	}

	Vector3 Transform::Up() const
	{
		return Vector3::Up * Matrix4::Rotation(rotation);
	}

	Vector3 Transform::Forward() const
	{
		return Vector3::Forward * Matrix4::Rotation(rotation);
	}
}