#pragma once
#include "Attack.h"
class Jump_Attack :public Attack
{
private:
	//�t���[��
	int all_Frame = 20;		//�S��
	int startup_Frame = 9;	//����
	int active_Frame = 4;	//����
	int recovery_Frame = 9;//�d��

	int hit_Frame = 15;		//�q�b�g��
	int block_Frame = 5;	//�K�[�h��

	//�����蔻��
	float heiight;	//����
	float width;	//��
};

