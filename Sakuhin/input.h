#pragma once

#include<XInput.h>
#include "main.h"

#pragma comment (lib,"XInput.lib")

struct CONTROLLER {
	//�{�^����
	bool Button[14];
	//�X�e�B�b�N
	float LStickX;
	float LStickY;
	float RStickX;
	float RStickY;
	//�g���K�[�{�^��
	float LTrigger;
	float RTrigger;
};

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	//�R���g���[���[�p�\����
	static CONTROLLER m_OldControllerState;
	static CONTROLLER m_NowControllerState;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	//�R���g���[���[�p
	static bool GetControllerDown(int CODE);
	static bool GetControllerTrigger(int CODE);
	static float GetLeftTriggerDown();
	static bool GetLeftTriggerTrigger();
	static float GetRightTriggerDown();
	static bool GetRightTriggerTrigger();
	static float GetLeftStickX();
	static float GetLeftStickY();
	static float GetRightStickX();
	static float GetRightStickY();
};
