﻿// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
#include <Windows.h>

HHOOK hHook;
HMODULE hDll;

LRESULT CALLBACK HookFunction(int Code, WPARAM wParam, LPARAM lParam) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (Code >= 0) {
		if (Code == HCBT_DESTROYWND)
		{
			wchar_t winName[512];
			GetWindowText((HWND)wParam, LPWSTR(winName), 512);
			MessageBox(NULL, L"Пользователь закрыл окно!", L"Уведомление!", NULL);
		}
	}
	else {
		return CallNextHookEx(hHook, Code, wParam, lParam);
	}
	CallNextHookEx(hHook, Code, wParam, lParam);
	return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hDll = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;

}

__declspec(dllexport) BOOL SetHook() {
	if (hHook = SetWindowsHookEx(WH_CBT, HookFunction, hDll, 0))
		return true;
	else
		return false;
}

__declspec(dllexport) BOOL DeleteHook() {
	if (UnhookWindowsHookEx(hHook))
		return true;
	else
		return false;
}



