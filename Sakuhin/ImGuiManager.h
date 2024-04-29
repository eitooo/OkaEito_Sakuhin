#ifndef _IMGUIMANAGER_H_
#define _IMGUIMANAGER_H_

#include <Windows.h>

class ImGuiManager
{
public:
	static void Init(HWND hWnd);
	static void PreRender();
	static void Render();
	static void Shutdown();
};

#endif