#include "Matrix4.h"
#include <algorithm>
#include <cstring>

namespace Craft
{
	// 단위 행렬 상수 값 설정.
	const Matrix4 Matrix4::Identity = Matrix4();

	Matrix4::Matrix4()
	{
		// 단위 행렬로 만들어서 생성.
		// 1. 모든 성분을 0으로 설정.
		memset(elements, 0, sizeof(elements));

		// 2. 대각 성분만 1로 설정.
		// 대각 성분 -> 행과 열의 순번이 같은 성분.
		m00 = 1.0f;
		m11 = 1.0f;
		m22 = 1.0f;
		m33 = 1.0f;
	}

	Matrix4::Matrix4(const Matrix4& other)
	{
		// 메모리 통복사.
		memcpy(elements, other.elements, sizeof(elements));
	}

	Matrix4& Matrix4::operator=(const Matrix4& other)
	{
		memcpy(elements, other.elements, sizeof(elements));
		return *this;
	}

	Matrix4 Matrix4::Transpose(const Matrix4& matrix)
	{
		// 반환할 행렬 선언.
		Matrix4 m;

		/*
		* float m00, m01, m02, m03;		// 1행.
		  float m10, m11, m12, m13;		// 2행.
		  float m20, m21, m22, m23;		// 3행.
		  float m30, m31, m32, m33;		// 4행.
		* 
		*/

		// 대각 성분을 기준으로 행과 열을 교환.
		std::swap(m.m01, m.m10);
		std::swap(m.m02, m.m20);
		std::swap(m.m03, m.m30);
		std::swap(m.m12, m.m21);
		std::swap(m.m13, m.m31);
		std::swap(m.m23, m.m32);

		return m;
	}

	Matrix4 Matrix4::InverseRotation(const Matrix4& matrix)
	{
		return Transpose(matrix);
	}
}