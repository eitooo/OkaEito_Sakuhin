#pragma once
#include "Attack.h"
class medium_attack :public Attack
{
private:
	//�t���[��
	int all_Frame = 25;		//�S��
	int startup_Frame = 7;	//����	
	int active_Frame = 4;	//����
	int recovery_Frame = 14;	//�d��

	int hit_Frame = 5;		//�q�b�g��
	int block_Frame = -4;	//�K�[�h��

	//�����蔻��
	float heiight;	//����
	float width;	//��

public:
	int Get_all_Frame();
};

