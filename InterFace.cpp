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
#define PathpasswordOnPC  "C:\\USB\\password.txt"
#define PathUSBonPC "C:\\USB\\path.txt"
#define Winlogon_Path "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"

void menu();
void create();
bool getNumberOfUsb();
void chooseUsb();
bool checkUsbExists();
void makePathOnUsb(int);
void makeFileonUsb();
void createPassword();
bool inputPassword();
void pushPasswordToPCfile();
void makeFileonPC();
bool checkingExistingFileOnUSB();
void makeFileWithUSBpath(char);

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
		//cout << "2 - Change password" << endl;
		cout << "2 - Delete USB-key" << endl;
		cout << "3 - Exit" << endl;
		do {
			cin >> k;
		} while (k < 0 || k>3);
		switch (k) {
		case 1: create();
			break;
		case 2: //changePassword();
			break;
		case 3: return;
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
	chooseUsb();
	if (checkingExistingFileOnUSB()) {
		cout << "\tWARNING!\nYou have already created USB-key on your USB\nPlease,check again or remove file from USB and create it again" << endl;
		_getch();
		return;
	};
	createPassword();
	if (checkUsbExists() == false) {
		return;
	}
	makeFileonUsb();
	pushPasswordToPCfile();

	//Â ÎÒÄÅËÜÍÎÌ EXE ÊÎÒÎÐÛÉ ÌÛ ÇÀÏÓÑÊÀÅÌ
	//changeRegistry();
}

void chooseUsb() {
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
	FILE* f;
	f = fopen(PathpasswordOnPC,"r");
	if (!f) {
		makeFileonPC();		
		return;
	}
	fclose(f);
	ofstream write;
	write.open(PathpasswordOnPC, ios::app);
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
	makeFileWithUSBpath(*it);
	str += ":\\mypw.txt";
	PathpasswordOnUsb = str;
}

void makeFileWithUSBpath(char letterUSB) {
	fstream f;
	f.open(PathUSBonPC, ios::out);
	f << letterUSB << ":\\";
	f.close();
}

void makeFileonUsb() {
	system("cls");
	fstream f;
	f.open(PathpasswordOnUsb, ios::out);
	f << password;
	f.close();
	cout << "Please, wait...\nFile 'mypw.txt' is creating on your chosen USB." << endl;
	_sleep(2000);
}

void makeFileonPC() {
	system("cls");
	fstream f;
	f.open(PathpasswordOnPC, ios::out);
	f << password << "\n";
	f.close();
	cout << "File 'password.txt' is creating on your PC.\nPlease,wait..." << endl;
	_sleep(2000);
}

bool checkingExistingFileOnUSB() {
	FILE* f;
	f = fopen(PathpasswordOnUsb.c_str(), "r");
	if (!f) {
		//fclose(f);
		return false; // no file on usb
	}
	else {
		fclose(f);
		return true;
	} //file already has been created
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


/*string readFile()
{
int k;
string string;
ifstream inFile;
inFile.open(PathpasswordOnPC);
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