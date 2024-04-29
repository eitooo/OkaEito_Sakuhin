#pragma once
#include "gameObject.h"
#include	<SimpleMath.h>
class ECamera :public GameObject
{
private:

	DirectX::SimpleMath::Vector3	m_Target{};
	DirectX::SimpleMath::Matrix		m_ViewMatrix{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	DirectX::SimpleMath::Matrix GetViewMatrix()
	{
		return m_ViewMatrix;
	}
};

