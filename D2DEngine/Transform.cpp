#include "pch.h"
#include "Transform.h"


void Transform::UpdateTrasnform()
{

	if (type == Type::World)
	{
		m_RelativeTransform =
			//D2D1::Matrix3x2F::Translation(m_CenterTransform.x, m_CenterTransform.y) *     // 얘는 렌더단계에서 따로 계산해야 맞음. 스프라이트 피벗
			D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
			D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
			D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);
	}
	else
	{
		m_RelativeTransform =
			//D2D1::Matrix3x2F::Translation(m_CenterTransform.x, m_CenterTransform.y) *     // 얘는 렌더단계에서 따로 계산해야 맞음. 스프라이트 피벗
			D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
			D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
			D2D1::Matrix3x2F::Translation({(pos.rectposition.leftBottom.x + pos.rectposition.rightTop.x) /2,
				(pos.rectposition.leftBottom.y + pos.rectposition.rightTop.y) / 2 } );
	}

	// 위와 같은 원리라면 렌더러도 매트릭스를 가지고 있고 (pivot, scale, rotation) 이 값에 transform의 matrix를 곱하여 표현해야 할거같다.

	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}