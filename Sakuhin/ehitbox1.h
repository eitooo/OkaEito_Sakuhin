#pragma once
#include "gameObject.h"
class Ehitbox1 :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	float xpos = 0;
	float ypos = 0;
	float ewidth = 0;
	float eheight = 0;

public:
	void Init();
	void Uninit();
	void Draw();
	void Update();

	void Set_xpos(float xp);
	void Set_ypos(float yp);
	void Set_ewidth(float ew);
	void Set_eheight(float eh);
};

