#pragma once

#include <Math/Vector3.h>

namespace Craft
{
	// 변환(Transform) 함수를 제공하는 4x4 행렬.
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		// 전치 함수 - 행과 열을 바꾸는 동작 처리.
		static Matrix4 Transpose(const Matrix4& matrix);

		// 회전 행렬의 역행렬 함수 - 전치 동작을 역행렬 동작으로 구현.
		// 주의! -> 기저 축이 서로 직교(90도)일 때만 처리.
		// 이유1: 역행렬 구하기 복잡.
		// 이유2: 모든 상황에서 해가 있는 것이 아님.
		static Matrix4 InverseRotation(const Matrix4& matrix);

		// 변환 행렬 생성 함수.

		// 이동 변환 행렬.
		static Matrix4 Translation(float x, float y, float z);
		static Matrix4 Translation(const Vector3& translation);

		// 크기 변환 행렬.
		static Matrix4 Scale(float x, float y, float z);
		static Matrix4 Scale(const Vector3& scale);
		static Matrix4 Scale(float scale);

		// 회전 변환 행렬.
		static Matrix4 RotationX(float angle);
		static Matrix4 RotationY(float angle);
		static Matrix4 RotationZ(float angle);
		static Matrix4 Rotation(float x, float y, float z);
		static Matrix4 Rotation(const Vector3& rotation);

		// 내부에서 관리하는 배열의 원시 포인터 반환 함수.
		const float* Data() const { return elements; }

		Matrix4& operator=(const Matrix4& other);

		// 행렬 곱 연산자 오버로딩.
		Matrix4 operator*(const Matrix4& other) const;
		Matrix4& operator*=(const Matrix4& other);

		// 벡터와 행렬 곱.
		// 벡터와 행렬 곱을 처리할 때 행벡터로 사용해서 처리.
		// 행벡터를 사용하는 경우 벡터가 왼쪽에 배치되도록 처리.
		friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);

	public:
		// 단위 행렬 상수.
		// -> 대각 성분이 1이고, 나머지 성분이 0인 행렬.
		// -> 행렬의 곱을 했을 때 원래 행렬을 반환하게 해줌.
		// -> 행렬 곱의 항등원.
		static const Matrix4 Identity;

	private:
		// 4x4 행렬 변수 선언.
		// 공용체-> 여러 변수가 같은 메모리 공간을 함께 사용.
		union
		{
			struct
			{
				float m00, m01, m02, m03;		// 1행.
				float m10, m11, m12, m13;		// 2행.
				float m20, m21, m22, m23;		// 3행.
				float m30, m31, m32, m33;		// 4행.
			};

			// 배열을 한 번에 선언.
			float elements[4 * 4];
		};
	};
}
