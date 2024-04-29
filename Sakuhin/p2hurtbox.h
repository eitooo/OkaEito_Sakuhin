#pragma once
#include "gameObject.h"
class P2hurtbox :public GameObject
{
private:
	float xpos = 0;
	float ypos = 0;
	float ewidth = 0;
	float eheight = 0;

public:
	void Init() override;
	void Update()override;

	void Set_xpos(float xp);
	void Set_ypos(float yp);
	void Set_ewidth(float ew);
	void Set_eheight(float eh);
};

