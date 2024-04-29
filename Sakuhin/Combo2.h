#pragma once
#include "gameObject.h"
class Combo2 :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	int m_Count;
	int count = 0;

public:
	void Init();
	void Update();
	void Uninit();
	void Draw();
	void DecCount
	(int Count) {
		m_Count -= Count;
	}
};

