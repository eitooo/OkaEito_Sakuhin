#pragma once
#include "gameObject.h"
#include "animationModel.h"
#include "collision.h"

#define COMBO_MAX 5
#define GRAP_GRACE_Flame 10

#define MaxN 10000
#define AFlame 1000
#define LAFlame 16
#define MAFlame 26
#define HAFlame 36
#define IDLEFlame 100
#define CROUCHIFlame 100
#define WALKFlame 100
#define JUMPFlame 40
#define GRAP_READY_Flame 31

#define CriticalFlame 30

class PlayerBase :public GameObject
{
private:

	float NowHp = 1000.0f;

public:

	//移動距離限界
	float movelimit = 10.0f;

	int combo_count;

	int	grap_Frame = 0;

	void Move(GameObject p1);
	void Push();

	void SetNowHP(float shp);
	float GetNowHp();
	void DecNowHp(float dmg);

	bool Action = false;	//アクション中か
	bool Attackflg = false;	//攻撃中かどうか

	bool Grap_hit = false;

	bool dmage_hit = false;

	bool Block = false;

	bool Push_Flg = false;
	void Set_Push(bool ph);

	//プレイヤーの状態
	enum player_ste
	{
		Idle,
		Walk,
		Jump,
		Crouchi,
		Light_Attack,
		Medium_Attack,
		Heavy_Attack,
		Jump_Attack,
		SP_Attack,
		Hit,
		CriticalHit,
		Dying,
		Win,
		Guard,
		Grap_ready,
		Grap_motion
	};

	player_ste ste = Idle;

	void Combo_add() { combo_count++; }
	void Set_Combo(int cm) { combo_count = cm; }
	int Get_Combo_count() { return combo_count; }

	bool Get_Attackflg() { return Attackflg; }
	void Set_Attackflg(bool at) { Attackflg = at; };

	bool Get_Grap_hit() { return Grap_hit; };
	void Set_Grap_hit(bool gh) { Grap_hit = gh; };

	bool Get_grap_Frame() { return grap_Frame; };

	player_ste Get_status() { return ste; }
	void Set_status(player_ste st);

	player_ste old_ste;

	AABB player_Attackbox;	//攻撃判定
	AABB player_Hurtbox;	//やられ判定

	AABB Get_Attackbox() { return player_Attackbox; }
	AABB Get_Hurtbox() { return player_Hurtbox; }

	bool Get_Block() { return Block; }
};

