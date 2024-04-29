#pragma once
#include "gameObject.h"
class HPber2 : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	float MaxHp = 1000.0f;
	float NowHp = 1000.0f;
public:
	void Init();
	void Uninit();
	void Draw();
	void Update();
	void SetNowHp(float nhp);
	void DecNowHp(float nhp);
};

