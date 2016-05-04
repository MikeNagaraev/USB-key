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

char* usb;
string password;

string readFile(char* filePath)//+
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
	cout << path;
	CopyFileA(path, BLOCK_EXE, false);
}

void main()//+
{
	string path = readFile(PATH_OF_USB_ON_PC);
	password = readFile(PATH_PASSWORD_PC);
	usb = &path[0];
	makeExeFile();
}

