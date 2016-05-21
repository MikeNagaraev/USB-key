#include <windows.h>
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
#define ID_BUTTON_1 3000
#define ID_BUTTON_2 3001
#define ID_BUTTON_3 3002

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void createButtons(HWND);
void actionsOnButtons(WPARAM, HWND);
void create();
bool getNumberOfUsb();
bool chooseUsb();
bool checkUsbExists();
void makePathOnUsb(int);
void makeFileonUsb();
void createPassword();
bool inputPassword();
void pushPasswordToPCfile();
void makeFileonPC();
bool checkingExistingFileOnUSB();
void makeFileWithUSBpath();
void setDefaultSettings();
void setDefaultRegistry();
void makeExeFile();

HWND hBtn1;
HWND hBtn2;
HWND hBtn3;
HINSTANCE hInstance;
int window;
list<char> foundedUsb;
list<char>::iterator it;
char* PathpasswordOnUsb;
string password;
list<string> listPasswords;
char letterOfUsb;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hMainWnd; // хендл будущего окна
	char szClassName[] = "MyClass";
	MSG msg;
	WNDCLASSEX wc;

	// Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc; //WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	hInstance = hInst;
	// Регистрируем класс окна
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	// Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, "USB-key", WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX, 300, 300, 600, 400, NULL, NULL, hInstance, NULL);
	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}
	//Создаем кнопки hBtn1 и hBtn2;
	window = 1; //первое окно
	createButtons(hMainWnd);



	// Показываем окно
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(hMainWnd); // Уничтожаем основное окно
	UnregisterClass(szClassName, NULL); // Освобождаем память, отменяя регистрацию класса основного окна.
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE: {
		DestroyWindow(hMainWnd);
		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}


	case WM_COMMAND: {
		actionsOnButtons(wParam, hMainWnd);
		break;
	}
	case WM_PAINT: {
		if (window == 2) {
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = (HDC)GetDC(hMainWnd);
			/*SetTextColor(hdc, RGB(255, 0, 0));
			SetBkColor(hdc, RGB(0, 0, 0));*/
			hdc = BeginPaint(hMainWnd, &ps);
			::TextOut(hdc, 20, 20, "Choose USB:", lstrlen("Choose USB:"));
			EndPaint(hMainWnd, &ps);
		}
	}

	case WM_KEYDOWN: {
		switch (wParam) {
		case VK_ESCAPE:
			SendMessage(hMainWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	}

	default:
		return DefWindowProc(hMainWnd, msg, wParam, lParam);
	}
	return 0;
}

void createButtons(HWND hMainWnd) {
	int posX = 70;
	int posY[3] = { 45,100,200 };
	int width = 240;
	int height = 40;
	switch (window) {
	case 1: {

		hBtn1 = CreateWindow("BUTTON", "Create USB-key", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, posX, posY[0],
			width, height, hMainWnd, (HMENU)ID_BUTTON_1, hInstance, NULL);

		hBtn2 = CreateWindow("BUTTON", "Restore system", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, posX, posY[1],
			width, height, hMainWnd, (HMENU)ID_BUTTON_2, hInstance, NULL);
		hBtn3 = CreateWindow("BUTTON", "Exit", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, posX, posY[2],
			width, height, hMainWnd, (HMENU)ID_BUTTON_3, hInstance, NULL);

		break;
	}
	case 2: {

		hBtn3 = CreateWindow("BUTTON", "Cancel", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, posX, posY[2],
			width, height, hMainWnd, (HMENU)ID_BUTTON_3, hInstance, NULL);
		ShowWindow(hBtn3, SW_SHOW);
		break;
	}
	}
}

void actionsOnButtons(WPARAM wParam, HWND hMainWnd) {
	switch (wParam) {
	case ID_BUTTON_1: {
		switch (window) {
		case 1: {
			DestroyWindow(hBtn1);
			DestroyWindow(hBtn2);
			DestroyWindow(hBtn3);
			//DRAW NEW BACKGROUND
			window = 2;
			createButtons(hMainWnd);

			break;
		}
		case 2: {

			//choose usb
			break;
		}
		default: {
			break;
		}
		}
		return;
	}

	case ID_BUTTON_2: {
		switch (window) {
		case 1: {

			break;
		}
		case 2: {

			break;
		}
		default: {
			break;
		}
		}
		return;
	}
	case ID_BUTTON_3: {
		switch (window) {
		case 1: {
			PostQuitMessage(0);
			break;
		}
		case 2: {
			window = 1;
			createButtons(hMainWnd);
			break;
		}
		default: {
			break;
		}
		}
		return;
	}
	}
}

void create() {
	if (checkUsbExists() == false) {
		return;
	}
	if (chooseUsb() == false) {
		return;
	}
	if (checkingExistingFileOnUSB() == true) {
		//cout << "\tWARNING!\nYou have already created USB-key on your USB" << endl;
		//cout << "Please,check again or remove file from USB and create it again" << endl;
		//_getch();
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
		//cout << "USB not found" << endl;
		//system("pause");
		return false;
	}
	return true;
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

void createPassword() {
	system("cls");
	bool correctPassword = false;
	do {
		correctPassword = inputPassword();
	} while (!correctPassword);

}

bool inputPassword() {
	string pas;
	regex reg("[а-яА-Я]");
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
	f = fopen(PATH_PASSWORD_PC, "r");
	if (!f) {
		makeFileonPC();
		return;
	}
	fclose(f);
	ofstream write;
	write.open(PATH_PASSWORD_PC, ios::out);
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
	letterOfUsb = *it;
	char* str = (char*)calloc(sizeof(char), 100);
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

void makeFileonPC() {
	system("cls");
	fstream f;
	f.open(PATH_PASSWORD_PC, ios::out);
	SetFileAttributes(PATH_PASSWORD_PC, FILE_ATTRIBUTE_HIDDEN);
	f << password;
	f.close();
	cout << "File 'password.txt' is creating on your PC.\nPlease,wait..." << endl;
	_sleep(2000);
}

bool checkingExistingFileOnUSB() {
	FILE* f;
	f = fopen(PathpasswordOnUsb, "r");
	if (!f) {
		return false; // no file on usb
	}
	else {
		fclose(f);
		return true;
	} //file already has been created
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