#pragma once
#include "scene.h"
class stageSelect :public Scene
{
private:
	class Transition* m_Transition{};
	int Sentaku = 0;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};

