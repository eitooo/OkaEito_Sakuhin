#pragma once
#include "Attack.h"
class heavy_attack :public Attack
{
private:
	//�t���[��
	int all_Frame = 35;		//�S��
	int startup_Frame = 11;	//����
	int active_Frame = 4;	//����
	int recovery_Frame = 20;//�d��

	int hit_Frame = 8;		//�q�b�g��
	int block_Frame = -7;	//�K�[�h��

	//�����蔻��
	float heiight;	//����
	float width;	//��

public:
	int Get_all_Frame();
};

