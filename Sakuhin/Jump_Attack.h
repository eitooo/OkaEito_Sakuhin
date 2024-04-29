#pragma once
#include "Attack.h"
class Jump_Attack :public Attack
{
private:
	//フレーム
	int all_Frame = 20;		//全体
	int startup_Frame = 9;	//発生
	int active_Frame = 4;	//持続
	int recovery_Frame = 9;//硬直

	int hit_Frame = 15;		//ヒット時
	int block_Frame = 5;	//ガード時

	//当たり判定
	float heiight;	//高さ
	float width;	//幅
};

