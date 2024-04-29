#pragma once
#include "scene.h"
class Edit :public Scene
{
private:
	class Transition* m_Transition{};
	class Audio* m_BGM{};
	bool m_Goal = false;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

