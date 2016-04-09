#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>
using namespace std;
#define passwordPath "C:\\password.txt"
#define USB_EXE "E:\\Projects\\C++ - Visual Studio\\Usb\\Usb-key\\Debug\\USB.exe"
#define Winlogon_Path "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"

void menu();
void create();
void changePassword();

string readFile();


int main() {
  menu();
  return 0;
}
void menu() {
	int k;
	while (true) {
		system("cls");
		cout << "Choose:" << endl;
		cout << "1 - Create USB-key" << endl;
		cout << "2 - Change password" << endl;
		cout << "3 - Exit" << endl;
		do {
			cin >> k;
		} while (k < 0 || k>3);
		switch (k) {
		case 1: create();
			break;
		case 2: changePassword();
			break;
		case 3: return;
		}
	}
}

void create() {
	changeRegistry();
}

void changeRegistry() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	LPSTR path = (LPSTR)buffer;
	CopyFileA(path, USB_EXE, false);
	HKEY hKey;
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, Winlogon_Path, 0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
	//TODO: setValue to Registry
	RegCloseKey(hKey);
}

void changePassword() {
	//TODO: doMETHOD
}
void inputPassword() {
	//TODO: creating file in USB and in Window's path
}

string readFile()
{
	int k;
	string string;
	ifstream inFile;
	inFile.open(passwordPath);
	getline(inFile, string);
	if (string == "\n") {
		cout << "You have no password" << endl;
		cout << "Create USB-key password?1/0" << endl;
		do {
			cin >> k;
		} while (k < 0 || k>1);
		if (k == 0) return;
	}
	inputPassword();
	inFile.close();
	return string;
}