#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <winreg.h>
#include <tchar.h>
#include <conio.h>

using namespace std;
#define PATH_OF_USB_ON_PC "C:\\USB\\path.txt"
#define PATH_PASSWORD_PC "C:\\USB\\password.txt"
#define USB_KEY_EXE  "C:\\USB\\UsbKey.exe"
#define BLOCK_EXE "C:\\USB\\Block.exe"

void makeExeFile();
string readFile(char* );

HHOOK	hook;
int control = 0;
char* usb;
string password;

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	while (1)
	{
		BlockInput(true);
	}
	ExitThread(0);
}

LRESULT CALLBACK LowLevelKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	GetKeyState(NULL);
	if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
		if (ks->vkCode == VK_LCONTROL)
		{
			control++;
			cout << control;
		}
		else
		{
			cout << control;
			control = 0;
		}
		if (control == 3)
		{
			HANDLE threadID = CreateThread(NULL, 0, &ThreadProc, NULL, 0, NULL);
			while (true)
			{
				if (readFile(usb) == password)
				{
					TerminateThread(threadID, 0);
					CloseHandle(threadID);
					control = 0;
					break;
				}
			}
		}
	}
	if (GetKeyState(VK_LSHIFT) & GetKeyState(VK_RSHIFT) & 0x0100){
		PostQuitMessage(0);
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

string readFile(char* filePath)
{
	string string;
	ifstream inFile;
	inFile.open(filePath);
	getline(inFile, string);
	inFile.close();
	return string;
}

void makeExeFile()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	LPSTR path = (LPSTR)buffer;
	CopyFileA(path, BLOCK_EXE, false);
}

void main()
{
	string path = readFile(PATH_OF_USB_ON_PC);
	password = readFile(PATH_PASSWORD_PC);
	usb = &path[0];
	FreeConsole();
	makeExeFile();
	HINSTANCE instance = GetModuleHandle(NULL);
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardHook, instance, 0);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}