#pragma once
#include "Attack.h"
class medium_attack :public Attack
{
private:
	//フレーム
	int all_Frame = 25;		//全体
	int startup_Frame = 7;	//発生	
	int active_Frame = 4;	//持続
	int recovery_Frame = 14;	//硬直

	int hit_Frame = 5;		//ヒット時
	int block_Frame = -4;	//ガード時

	//当たり判定
	float heiight;	//高さ
	float width;	//幅

public:
	int Get_all_Frame();
};

