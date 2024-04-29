#pragma once

#include "gameObject.h"
#include "animationModel.h"
#include "PlayerBase.h"


struct p2_data
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

class Player2 : public PlayerBase
{
private:
	p2_data edata[AFlame];
	p2_data la_data[LAFlame];
	p2_data ma_data[MAFlame];
	p2_data ha_data[HAFlame];
	p2_data idle_data[IDLEFlame];
	p2_data crouchi_data[CROUCHIFlame];
	p2_data walk_data[WALKFlame];
	p2_data jump_data[JUMPFlame];
	p2_data grap_ready_data[GRAP_READY_Flame];

	DirectX::SimpleMath::Vector3		m_Velocity{};
	class Audio* m_SE{};

	class AnimationModel* m_Model;
	int	m_Frame;
	float	m_BlendRate;

	bool muki; //trueで右　falseで左

	int jumpflame = 40;
	int hitflame = 20;
	int guardflame = 20;

	//全体、発生、持続、硬直
	int latkflame[4] = { 15,4,8,15 };	//LightAttackのフレーム　
	int matkflame[4] = { 25,7,4,14 };//mediumAttackのフレーム
	int hatkflame[4] = { 35,11,4,20 };//heavyAttackのフレーム

	struct LightAttack_data
	{
		int hit_Frame = 25;		//ヒット時
		int guard_Frame = 10;	//ガード時

		int dmg = 100;
	};

	struct MediumAttack_data
	{
		int hit_Frame = 27;		//ヒット時
		int guard_Frame = 10;	//ガード時

		int dmg = 150;
	};

	struct HeavyAttack_data
	{
		int hit_Frame = 35;		//ヒット時
		int guard_Frame = 10;	//ガード時

		int dmg = 200;
	};

	struct Grap_data
	{
		int dmg = 200;
	};

public:
	void Init() override;
	void Update() override;
	void PreDraw() override;

	void Set_Guardflame(int gf);
	void Set_Hitflame(int hf);
};