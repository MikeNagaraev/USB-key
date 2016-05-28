#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include <string>
#include <list>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
using namespace std;


#define USB_LIST_TXT "/home/mikhail/interface_list_usb.txt"
#define PATH_TO_USBS "/media/mikhail/"
#define CHECKING_FILE "/home/mikhail/USB/path.txt"	
#define FOLDER_USB "/home/mikhail/USB/"
#define PATH_TO_BLOCK "/home/mikhail/USB-key/USB-key/Linux/block &"
#define TOUCH_FILE "touch /home/mikhail/USB/path.txt"
#define RM_FILE "rm /home/mikhail/interface_list_usb.txt"
#define MKDIR "mkdir /home/mikhail/USB/"

string global_path;
list<string> listOfUsb;
list<string>::iterator it;
pthread_t check_thread;
void menu();
void read_file_to_list(string );
void mkdir();
void mkfile();
void create();
void get_usb_list();
void show_list_and_choose();
void copy_usb_to_path_txt();
void rmfile();
void *show_list(void *);
void start_block();
void message_from_block();
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
		  //KILL BLCK
		  //RETURN BACK 	 
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
  rmfile();
  start_block();
  message_from_block();
}

void start_block() { 
  system(PATH_TO_BLOCK);
}

void message_from_block() {
  system("clear");
  cout << "WAIT FOR 5 SECONDS..." << endl;
  cout << "USB-KEY IS GOING TO START." << endl;
  sleep(5);
  system("clear");
  cout << "ALL THE BEST!!!" << endl;
  sleep(2);
}

void get_usb_list() {
  system("ls /media/mikhail/ > /home/mikhail/interface_list_usb.txt");
  read_file_to_list(USB_LIST_TXT);   //read to list from PATH_TO_USBS  
}

void read_file_to_list(string file_path) {
  string string;
  ifstream inFile;
  inFile.open(file_path.c_str());
  listOfUsb.clear();
  while(!inFile.eof()){
	getline(inFile, string);
	if(!inFile.eof()) {
	  listOfUsb.push_back(string);
    }
  }  
  inFile.close();
}

void *show_list(void *arg) {
	int n;                //cause in oder not to update INIFINITY
	n = 0; 				  // wait and compare with previous
  while(true) {
    get_usb_list(); 
    if(listOfUsb.size() == 0) { 
		n = 0;
	    system("clear");
	    cout << "Waiting for USB..." << endl;
        while(listOfUsb.size() == 0) {	  
          get_usb_list();
	  }
    }
    else if( n != listOfUsb.size()) { 
        system("clear");
        cout << "Choose USB: " << endl;
        it = listOfUsb.begin();
        for(int i = 0; i < listOfUsb.size(); i++, ++it) {
	      cout << i + 1 << ". " << *it << endl;	
        }
        n = listOfUsb.size();
    }
  }
}

void show_list_and_choose() {
  int n;
  do {	  
	pthread_create(&check_thread,NULL,show_list,NULL);	
	fflush(stdin);
	cin >> n;
  } while (n < 1 || n > listOfUsb.size());
  pthread_cancel(check_thread);
  it = listOfUsb.begin();
  for(int i = 1; i < n; i++) {
	++it;
  } 
  global_path = *it;
  return;
}

void mkdir() {
	system(MKDIR); 
}

void mkfile() {
	system(TOUCH_FILE); 
}

void rmfile() {
  system(RM_FILE);
}

void copy_usb_to_path_txt() {
    fstream f;
	f.open(CHECKING_FILE, ios::out);
	f << global_path;
	f.close();
}


