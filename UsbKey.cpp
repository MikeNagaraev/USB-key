#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <winreg.h>
#include <tchar.h>

using namespace std;

#define PATH_OF_USB_ON_PC "C:\\USB\\path.txt"
#define PATH_PASSWORD_PC "C:\\USB\\password.txt"
#define USB_KEY_EXE  "C:\\USB\\UsbKey.exe"
#define BLOCK_EXE "C:\\USB\\Block.exe"
#define WINLOGON_PATH "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
#define DEFAULT_USERINIT "C:\\Windows\\system32\\userinit.exe"

string readFile(char* filePath);
void makeExeFile();
void changeRegistry();
void open();
char* usb;
string password;


int main()
{
	makeExeFile();
	changeRegistry();
	FreeConsole();
	string path = readFile(PATH_OF_USB_ON_PC);
	password = readFile(PATH_PASSWORD_PC);
	usb = &path[0];
	while (true)
	{
		if (readFile(usb) == password)
		{
			open();
			break;
		}
		else {
			MessageBox(NULL, "INSERT USB-key for correct working!", "WARNING!", MB_OK | MB_ICONERROR);
		}
	}

	return 0;
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

void makeExeFile() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	LPSTR path = (LPSTR)buffer;
	CopyFileA(path, USB_KEY_EXE, false);
}

void changeRegistry() {
	HKEY hKey;
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, WINLOGON_PATH, 0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
	RegSetValueExA(hKey, "Userinit", 0, REG_SZ, (LPBYTE)USB_KEY_EXE, lstrlenA(USB_KEY_EXE));
	RegCloseKey(hKey);
}

void open()
{
	WinExec(DEFAULT_USERINIT, 1);

	SHELLEXECUTEINFO sei = { sizeof(sei) };

	sei.lpVerb = "runas";
	sei.lpFile = BLOCK_EXE;
	sei.hwnd = NULL; 
	sei.nShow = SW_NORMAL;

	ShellExecuteEx(&sei);
}