#pragma once
#include "PlayerBase.h"
#include "imgui/imgui.h"

#define MaxN 10000
#define AFlame 1000
#define LAFlame 16
#define MAFlame 26
#define HAFlame 36
#define IDLEFlame 101
#define WALKFlame 101
#define JUMPFlame 41
#define CROUCHIFlame 101
#define GRAP_READY_Flame 31

struct e_data
{
	float hurtbox1_x_pos;
	float hurtbox1_y_pos;
	float hurtbox1_height_s;
	float hurtbox1_width_s;

	float hitbox1_x_pos;
	float hitbox1_y_pos;
	float hitbox1_height_s;
	float hitbox1_width_s;
};


class EPlayer :public PlayerBase
{
#pragma region ImGui
public:
	void ShowDebugWindow();
#pragma endregion


private:

	e_data edata[AFlame];
	e_data la_data[LAFlame];
	e_data ma_data[MAFlame];
	e_data ha_data[HAFlame];
	e_data idle_data[IDLEFlame];
	e_data walk_data[WALKFlame];
	e_data jump_data[JUMPFlame];
	e_data crouchi_data[CROUCHIFlame];
	e_data grap_ready_data[GRAP_READY_Flame];


	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};

	class AnimationModel* m_Model;
	int	m_Frame;
	int c_Frame;
	float	m_BlendRate;

	bool muki; //trueÇ≈âEÅ@falseÇ≈ç∂
	bool move;

	
	int hitflame = 20;
	int Guardflame = 20;
public:
	void Init() override;
	void Update() override;
	void PreDraw() override;

	void Set_move(bool bo);
	void Set_m_Flame(int mfl);
	int Get_m_Flame();

};

