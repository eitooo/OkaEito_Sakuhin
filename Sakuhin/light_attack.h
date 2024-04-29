#pragma once
#include "Attack.h"
class light_attack :public Attack
{
private:
	//フレーム
	int all_Frame = 15;		//全体
	int startup_Frame = 4;	//発生
	int active_Frame = 4;	//持続
	int recovery_Frame = 7;	//硬直

	int hit_Frame = 5;		//ヒット時
	int block_Frame = -1;	//ガード時

	//当たり判定
	float heiight;	//高さ
	float width;	//幅

public:
	int Get_all_Frame();
};

