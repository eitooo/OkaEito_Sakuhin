#pragma once

#include "scene.h"

class Title : public Scene
{
private:
	class Transition* m_Transition{};
	int Sentaku = 0;

public:
	void Init() override;
	void Update() override;

};