#include "ProcMem.h"
#include "Triggerbot.h"
#include <iostream> 

Triggerbot::Triggerbot()
{
}

void Triggerbot::AttachProcess() //VK_MENu
{
	Mem.Process((char*)"csgo.exe");
}

void Triggerbot::Trigger()
{
	DWORD dwClientDLL = Mem.Module((char*)"client.dll");

	for (;;)
	{
		DWORD LocalPlayer = Mem.Read<DWORD>(dwClientDLL + playerBase);
		int LocalTeam = Mem.Read<int>(LocalPlayer + teamOffset);
		int CrosshairID = Mem.Read<int>(LocalPlayer + crosshairOffset);
		DWORD EnemyInCrosshair = Mem.Read<DWORD>(dwClientDLL + entityBase + ((CrosshairID - 1) * EntLoopDist));
		int EnemyHealth = Mem.Read<int>(EnemyInCrosshair + healthOffset);
		int EnemyTeam = Mem.Read<int>(EnemyInCrosshair + teamOffset);

	
		if (GetAsyncKeyState(VK_MENU) && LocalTeam != EnemyTeam && EnemyHealth > 0)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(1);
		}

	}
}

Triggerbot::~Triggerbot()
{
}
