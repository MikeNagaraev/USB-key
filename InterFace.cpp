#include <fstream>
#include <string>
#include <list>
#include <fstream>
#include <conio.h>
#include <iterator>
#include <Windows.h>
#include <iostream>
using namespace std;
#define passwordPathOnPC  "C:\\USB\\password.txt"
#define Winlogon_Path "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"

void menu();
void create();
void changePassword();
void getNumberOfUsb();
void chooseUsb();
bool checkUsbExists();
void checkAlreadyExistedPasswordonPc();
void checkAlreadyExistedPasswordonUSB();
void makePathOnUsb(int);
void makeFileonUsb();
void createPassword();
void pushPasswordToPCfile();
void makeFileonPC();
string readFile();

list<char> foundedUsb;
list<char>::iterator it; 
string PathpasswordOnUsb;
string password;
list<string> listPasswords;
int main() {
	getNumberOfUsb();
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
		//cout << "3 - Delete USB-key" << endl;
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

void getNumberOfUsb() {
	string letter = " :";
	for (int i = 'A'; i <= 'Z'; i++) {
		letter[0] = i;
		if (GetDriveType(letter.c_str()) == DRIVER_USERMODE) {
			foundedUsb.push_back(letter[0]);
		}
	}
}

void create() {
	chooseUsb();
	createPassword();
	makeFileonUsb();
	pushPasswordToPCfile();

	//Â ÎÒÄÅËÜÍÎÌ EXE ÊÎÒÎÐÛÉ ÌÛ ÇÀÏÓÑÊÀÅÌ
	//changeRegistry();
}

void chooseUsb() {
	if (checkUsbExists() == false) {
		return;
	}
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
	if (k == foundedUsb.size() + 1) return;
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

void createPassword() {
	system("cls");
	string pas;
	cout << "Enter a password:" << endl;
	fflush(stdin);
	cin >> pas;
	password = pas;
}

bool checkUsbExists() {
	if (!foundedUsb.size()) {
		cout << "USB not found" << endl;
		system("pause");
		return false;
	}
	return true;
}

void pushPasswordToPCfile() {
	FILE* f;
	f = fopen(passwordPathOnPC,"r");
	if (!f) {
		makeFileonPC();		
		return;
	}
	fclose(f);
	fstream write;
	write.open(PathpasswordOnUsb, ios::out,ios::app);
	write << password;
	write.close();

}

void makePathOnUsb(int k) {
	PathpasswordOnUsb = " ";
	it = foundedUsb.begin();
	int i = 0;
	while (i++ < k && it != foundedUsb.end()) {
		++it;
	}
	string str = " ";
	str[0] = *it;
	str += ":\\USBpassword.txt";
	PathpasswordOnUsb = str;
}


void makeFileonUsb() {
	system("cls");
	//TODO: create if it doesn't exist, or open,check and return;
	fstream f;
	f.open(PathpasswordOnUsb, ios::out);
	f << password;
	f.close();
	cout << "File 'USBpassword.txt' is created on your chosen USB" << endl;



}

void makeFileonPC() {
	system("cls");

	//TODO: create if it doesn't exist, or open,check and return;
	fstream f;
	f.open(passwordPathOnPC, ios::out);
	f << password;
	f.close();
	cout << "File 'password.txt' is created on your PC" << endl;

}






/*void changeRegistry() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	LPSTR path = (LPSTR)buffer;
	CopyFileA(path, USB_EXE, false);
	HKEY hKey;
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, Winlogon_Path, 0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
	//TODO: setValue to Registry
	RegCloseKey(hKey);
}*/

void changePassword() {
	//TODO: doMETHOD
}
void inputPassword() {
	//TODO: creating file in USB and in Window's path
}

/*string readFile()
{
int k;
string string;
ifstream inFile;
inFile.open(passwordPathOnPC);
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
}*/