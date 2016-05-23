#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <string>
#include <list>
#include <iterator>
#include <fstream>
#include <stdio.h>
using namespace std;


#define USB_LIST_TXT "/home/mikhail/usblist.txt"
#define PATH_TO_USBS "/media/mikhail/"
#define CHECKING_FILE "/home/mikhail/USB/path.txt"	
#define FOLDER_USB "/home/mikhail/USB/"

string global_path;
list<string> listOfUsb;
list<string>::iterator it;
void menu();
void read_file_to_list(string );
void mkdir();
void mkfile();
void create();
void get_usb_list();
void show_list_and_choose();
void copy_usb_to_path_txt();

int main() {
  menu();

  return 0;
}

void menu() {
  int n;
  while(true) {
    system("clear");
    cout << " 1. Create USB-key" << endl;
    cout << " 2. Restore system" << endl;
    cout << " 3. Exit" << endl;
    do {
	  cin >> n;
    } while (n < 1 || n > 3);
    switch(n) {
      case 1 : {
	      create();  //show files in PATH_TO_USBS 
	      break;
      }
      case 2 : {
	  
      }
      case 3 : {
	    return;
      }	
    }
  }
}

void create() {
  get_usb_list();
  show_list_and_choose();
  mkdir();
  copy_usb_to_path_txt();
}

void get_usb_list() {
  system(" ls /media/mikhail/ > /home/mikhail/usblist.txt");
  read_file_to_list(USB_LIST_TXT);   //read to list from PATH_TO_USBS  
}

void read_file_to_list(string file_path) {
  string string;
  ifstream inFile;
  inFile.open(file_path.c_str());
  while(!inFile.eof()){
	getline(inFile, string);
	if(!inFile.eof()) {
	  listOfUsb.push_back(string);
    }
  }  
  inFile.close();
}

void show_list_and_choose() {
  int n;
  while(true) {
	system("clear");
    cout << "Choose USB: " << endl;
    it = listOfUsb.begin();
    for(int i = 0; i < listOfUsb.size(); i++, ++it) {
	  cout << i + 1 << ". " << *it << endl;	
    }  
    do {
		cin >> n;
	} while (n < 1 || n > listOfUsb.size());
	it = listOfUsb.begin();
    for(int i = 1; i < n; i++) {
	  ++it;
	} 
	global_path = PATH_TO_USBS + *it;
	return;
  }
}

void mkdir() {
	system("mkdir /home/mikhail/USB/"); 
}

void mkfile() {
	system("touch /home/mikhail/USB/path.txt"); 
}

void copy_usb_to_path_txt() {
    fstream f;
	f.open(CHECKING_FILE, ios::out);
	f << global_path;
	f.close();
}
