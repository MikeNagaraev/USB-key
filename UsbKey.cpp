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
#define WINLOGON_PATH "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"

string readFile(char* filePath);
void makeExeFile();
void changeRegistry();
char* usb;
string password;


int main() {

	//TODO: exe
	//TODO: connect with block
	changeRegistry();
	string path = readFile(PATH_OF_USB_ON_PC);
	password = readFile(PATH_PASSWORD_PC);
	usb = &path[0];
	return 0;
}

string readFile(char* filePath) { //+
	string string;
	ifstream inFile;
	inFile.open(filePath);
	getline(inFile, string);
	inFile.close();
	return string;
}

void changeRegistry() { //+
	HKEY hKey;
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, WINLOGON_PATH, 0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
	RegSetValueExA(hKey, "Userinit", 0, REG_SZ, (LPBYTE)USB_KEY_EXE, lstrlenA(USB_KEY_EXE));
	RegCloseKey(hKey);
}