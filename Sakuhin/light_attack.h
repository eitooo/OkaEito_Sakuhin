#pragma once
#include "Attack.h"
class light_attack :public Attack
{
private:
	//�t���[��
	int all_Frame = 15;		//�S��
	int startup_Frame = 4;	//����
	int active_Frame = 4;	//����
	int recovery_Frame = 7;	//�d��

	int hit_Frame = 5;		//�q�b�g��
	int block_Frame = -1;	//�K�[�h��

	//�����蔻��
	float heiight;	//����
	float width;	//��

public:
	int Get_all_Frame();
};

