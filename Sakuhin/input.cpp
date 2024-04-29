
#include "main.h"
#include "input.h"

#define MAX_CONTROLLER_BUTTON 14
#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_START 4
#define BUTTON_BACK 5
#define BUTTON_LSTICK 6
#define BUTTON_RSTICK 7
#define BUTTON_LSHOULDER 8
#define BUTTON_RSHOULDER 9
#define BUTTON_A 10
#define BUTTON_B 11
#define BUTTON_X 12
#define BUTTON_Y 13

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
CONTROLLER Input::m_OldControllerState;
CONTROLLER Input::m_NowControllerState;

void Input::Init() {
	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);
	//コントローラー構造体初期化
	m_NowControllerState = { {false,false,false,false,false,false,false,false,false,false,false,false,false,false},0,0,0,0,0,0 };
	m_OldControllerState = m_NowControllerState;

}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);
	//コントローラー処理
	//今のコントローラー状態を1フレーム前として保存
	m_OldControllerState = m_NowControllerState;

	//コントローラー用ローカル変数
	DWORD dwResult;
	XINPUT_STATE NowControllerState;
	//XINPUT_STATEの初期化
	ZeroMemory(&NowControllerState, sizeof(XINPUT_STATE));

	//コントローラー状態取得
	dwResult = XInputGetState(0, &NowControllerState);
	if (dwResult == ERROR_SUCCESS) {
		//stateにwButtonsをコピー　ビット演算でシフトするので念のため
		WORD state = NowControllerState.Gamepad.wButtons;
		//ボタン
		for (int i = 0; i < MAX_CONTROLLER_BUTTON; i++) {
			//最下位ビットの論理和を取る
			if (state & 0x0001) m_NowControllerState.Button[i] = true;
			else m_NowControllerState.Button[i] = false;
			//右に論理シフト
			state = state >> 1;

			if (i == 9) {
				state = state >> 2;
			}

		}
		//スティック、トリガー
		//Lスティック
		if ((NowControllerState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			&& NowControllerState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(NowControllerState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				&& NowControllerState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) {
			m_NowControllerState.LStickX = 0;
			m_NowControllerState.LStickY = 0;
		}
		else {	//1~-1に正規化
			m_NowControllerState.LStickX = (float)NowControllerState.Gamepad.sThumbLX / 32767.f;
			m_NowControllerState.LStickY = (float)NowControllerState.Gamepad.sThumbLY / 32767.f;
		}
		//Rスティック
		if ((NowControllerState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
			&& NowControllerState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(NowControllerState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
				&& NowControllerState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) {
			m_NowControllerState.RStickX = 0;
			m_NowControllerState.RStickY = 0;
		}
		else {	//1~-1に正規化
			m_NowControllerState.RStickX = (float)NowControllerState.Gamepad.sThumbRX / 32767.f;
			m_NowControllerState.RStickY = (float)NowControllerState.Gamepad.sThumbRY / 32767.f;
		}
		//左トリガー
		if (NowControllerState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_NowControllerState.LTrigger = 0;
		}
		else {
			m_NowControllerState.LTrigger = (float)NowControllerState.Gamepad.bLeftTrigger;
		}
		//右トリガー
		if (NowControllerState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_NowControllerState.RTrigger = 0;
		}
		else {
			m_NowControllerState.RTrigger = (float)NowControllerState.Gamepad.bRightTrigger;
		}
	}
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetControllerDown(int CODE) {
	return m_NowControllerState.Button[CODE];
}

bool Input::GetControllerTrigger(int CODE) {
	return ((!m_OldControllerState.Button[CODE]) && m_NowControllerState.Button[CODE]);
}

float Input::GetLeftTriggerDown() {
	return m_NowControllerState.LTrigger;
}

bool Input::GetLeftTriggerTrigger() {
	return (m_NowControllerState.LTrigger > 0 && m_OldControllerState.LTrigger == 0);
}

float Input::GetRightTriggerDown() {
	return m_NowControllerState.RTrigger;
}

bool Input::GetRightTriggerTrigger() {
	return (m_NowControllerState.RTrigger > 0 && m_OldControllerState.RTrigger == 0);
}

float Input::GetLeftStickX() {
	return m_NowControllerState.LStickX;
}

float Input::GetLeftStickY() {
	return m_NowControllerState.LStickY;
}

float Input::GetRightStickX() {
	return m_NowControllerState.RStickX;
}

float Input::GetRightStickY() {
	return m_NowControllerState.RStickY;
}

