#pragma once

#include<XInput.h>
#include "main.h"

#pragma comment (lib,"XInput.lib")

struct CONTROLLER {
	//ボタン類
	bool Button[14];
	//スティック
	float LStickX;
	float LStickY;
	float RStickX;
	float RStickY;
	//トリガーボタン
	float LTrigger;
	float RTrigger;
};

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	//コントローラー用構造体
	static CONTROLLER m_OldControllerState;
	static CONTROLLER m_NowControllerState;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	//コントローラー用
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
