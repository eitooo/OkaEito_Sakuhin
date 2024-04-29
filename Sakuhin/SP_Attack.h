#pragma once
#include "Attack.h"
class SP_Attack :public Attack
{
private:
	//フレーム
	int all_Frame = 30;		//全体
	int startup_Frame = 5;	//発生
	int active_Frame = 5;	//持続
	int recovery_Frame = 20;//硬直

	int hit_Frame = 0;		//ヒット時
	int block_Frame = -20;	//ガード時

	//当たり判定
	float heiight;	//高さ
	float width;	//幅
};

