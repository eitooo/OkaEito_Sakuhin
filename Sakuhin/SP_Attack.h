#pragma once
#include "Attack.h"
class SP_Attack :public Attack
{
private:
	//�t���[��
	int all_Frame = 30;		//�S��
	int startup_Frame = 5;	//����
	int active_Frame = 5;	//����
	int recovery_Frame = 20;//�d��

	int hit_Frame = 0;		//�q�b�g��
	int block_Frame = -20;	//�K�[�h��

	//�����蔻��
	float heiight;	//����
	float width;	//��
};

