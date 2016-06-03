#include <fstream>
#include <string>
#include <list>
#include <fstream>
#include <conio.h>
#include <iterator>
#include <regex>
#include <Windows.h>
#include <iostream>
using namespace std;
#define PATH_PASSWORD_PC "C:\\USB\\password.txt"
#define PATH_OF_USB_ON_PC "C:\\USB\\path.txt"
#define WINLOGON_PATH "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
#define DEFAULT_USERINIT "C:\\Windows\\system32\\userinit.exe"
#define INTERFACE_EXE "C:\\USB\\InterFace.exe"

void menu();
void create();
bool getNumberOfUsb();
bool chooseUsb();
bool checkUsbExists();
void makePathOnUsb(int);
void makeFileonUsb();
void createPassword();
bool inputPassword();
void pushPasswordToPCfile();
bool checkingExistingFileOnUSB();
void makeFileWithUSBpath();
void setDefaultSettings();
void setDefaultRegistry();
void makeExeFile();
void warningMessage();

list<char> foundedUsb;
list<char>::iterator it; 
char* PathpasswordOnUsb;
string password;
list<string> listPasswords;
char letterOfUsb;

int main() {
	getNumberOfUsb();
	menu();
	return 0;
}

void menu() {
	makeExeFile();
	int k;
	while (true) {
		system("cls");
		cout << "Choose:" << endl;
		cout << "1 - Create USB-key" << endl;
		cout << "2 - Restore default settings" << endl;
		cout << "3 - Exit" << endl;
		do {
			cin >> k;
		} while (k < 0 || k>3);
		switch (k) {
		  case 1: { 
			create();
			break;
		  }
		  case 2: { 
			  setDefaultSettings();
			  break;
		  }
		  case 3: {			 
			  return;
		  }
		}
	}
}

bool getNumberOfUsb() {
	string letter = " :";
	bool usb_here = false;
	foundedUsb.clear();
	for (int i = 'A'; i <= 'Z'; i++) {
		letter[0] = i;
		if (GetDriveType(letter.c_str()) == DRIVER_USERMODE) {
			foundedUsb.push_back(letter[0]);
			usb_here = true;
		}
	}
	return usb_here;
}

bool checkUsbExists() {
	if (!getNumberOfUsb()) {
		cout << "USB not found" << endl;
		system("pause");
		return false;
	}
	return true;
}

void create() {
	if (checkUsbExists() == false) {
		return;
	}
	if (chooseUsb() == false) {
		return;
	}
	if (checkingExistingFileOnUSB() == true) {
		warningMessage();
		return;
	};
	createPassword();
	if (checkUsbExists() == false) {
		return;
	}
	makeFileWithUSBpath();
	makeFileonUsb();
	pushPasswordToPCfile();
}

bool chooseUsb() {
sure:
	int k;
	int i;
	it = foundedUsb.begin();
	system("cls");
	cout << "Choose USB:" << endl;
	for (i = 0; i < foundedUsb.size(), it != foundedUsb.end(); i++, ++it) {
		cout << i + 1 << ". " << *it << endl;
	}
	cout << i + 1 << ". Exit" << endl;
	do {
		cin >> k;
	} while (k < 1 || k > foundedUsb.size() + 1);
	if (k == foundedUsb.size() + 1) return false;
	int sure;
	cout << "Are you sure?" << endl << "Yes - 1" << endl << "No - 0" << endl;
	do {
		cin >> sure;
	} while (sure < 0 || sure > 1);
	if (sure == 0) {
		goto sure;
	}
	else {
		cout << "Let's start!" << endl;
		makePathOnUsb(k - 1);
		_getch();
	}
}

void warningMessage() {
	cout << "\tWARNING!\nYou have already created USB-key on your USB" << endl;
	cout << "Please,check again or remove file from USB and create it again" << endl;
	_getch();
}

void createPassword() {
	system("cls");	
	bool correctPassword = false;
	do {
		correctPassword = inputPassword();
	} while (!correctPassword);
	
}

bool inputPassword() {
	string pas;
	regex reg("[à-ÿÀ-ß]");
	bool flag = false;
	do
	{
		try
		{
			cout << "Enter a password (English symbols or numbers):" << endl;
			fflush(stdin);
			cin >> pas;
			if (regex_search(pas, reg)) {
				throw exception("Not correct password");
			}
			flag = true;
		}
		catch (exception ex) {
			cout << "Input correct password!" << endl;
			flag = false;
		}
	} while (!flag);
	password = pas;
	cout << "Password is correct" << endl;
	_getch();
	return true;
}

void pushPasswordToPCfile() {
	system("cls");
	fstream f;
	f.open(PATH_PASSWORD_PC, ios::out);
	SetFileAttributes(PATH_PASSWORD_PC, FILE_ATTRIBUTE_HIDDEN);
	f << password;
	f.close();
	cout << "File 'password.txt' is creating on your PC.\nPlease,wait..." << endl;
	_sleep(2000);
	

}

void makePathOnUsb(int k) {
	PathpasswordOnUsb = " ";
	it = foundedUsb.begin();
	int i = 0;
	while (i++ < k && it != foundedUsb.end()) {
		++it;
	}
	letterOfUsb = *it;
	char* str = (char*)calloc(sizeof(char),100);
	str[0] = letterOfUsb;
	strcat(str, ":\\mypw.txt");
	PathpasswordOnUsb = str;
}

void makeFileWithUSBpath() {
	fstream f;
	f.open(PATH_OF_USB_ON_PC, ios::out);
	SetFileAttributes(PATH_OF_USB_ON_PC, FILE_ATTRIBUTE_HIDDEN);
	f << letterOfUsb << ":\\mypw.txt";
	f.close();
}

void makeFileonUsb() {
	system("cls");
	fstream f;
	f.open(PathpasswordOnUsb, ios::out);
	SetFileAttributes(PathpasswordOnUsb, FILE_ATTRIBUTE_HIDDEN);
	f << password;
	f.close();
	cout << "Please, wait...\nFile 'mypw.txt' is creating on your chosen USB." << endl;
	_sleep(2000);
}

bool checkingExistingFileOnUSB() {
	FILE* f;
	f = fopen(PathpasswordOnUsb, "r");
	if (!f) {
		return false; 
	}
	else {
		fclose(f);
		return true;
	} 
}

void setDefaultSettings() {
	cout << "Please, wait..." << endl;
	setDefaultRegistry();	
	system("cls");
	cout << "All system settings has restored" << endl;
	_getch();
}

void setDefaultRegistry() {
	HKEY hKey;
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, WINLOGON_PATH, 0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
	RegSetValueExA(hKey, "Userinit", 0, REG_SZ, (LPBYTE)DEFAULT_USERINIT, lstrlenA(DEFAULT_USERINIT));
	RegCloseKey(hKey);
}

void makeExeFile() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	LPSTR path = (LPSTR)buffer;
	CopyFileA(path, INTERFACE_EXE, false);
}