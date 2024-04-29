#pragma once
#include	"gameObject.h"
class HPcover : public GameObject
{
private:
	float Maxhp = 300.0f;
public:
	void Init();
	void Uninit();
	void Update();
};

