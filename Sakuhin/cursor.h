#pragma once
#include "gameObject.h"
class Cursor :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	int Sentaku = 200;
public:
	void Init();
	void Uninit();
	void Draw();
	void Update();
	int GetSen();
};

