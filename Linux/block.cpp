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

#define CHECKING_FILE "/home/mikhail/USB/path.txt"	
#define PATH_TO_BLOCK_SCRIPT "/home/mikhail/scripts/block.sh"
#define PATH_TO_UNBLOCK_SCRIPT "/home/mikhail/scripts/unblock.sh"
#define USB_LIST_TXT "/home/mikhail/usblist.txt"


void block();
void unblock();
string readFile(string);
void update();
void get_usb_list();
void read_file_to_list(string);
bool comare_path_with_list();

list<string> listOfUsb;
list<string>::iterator it;
string path;

int main() {
  path = readFile(CHECKING_FILE);
  update();	
  return 0;
}


void block() {
	system("/home/mikhail/scripts/block.sh");
}

void unblock() {
	system("/home/mikhail/scripts/unblock.sh");
}

string readFile(string filePath)
{
	string string;
	ifstream inFile;
	inFile.open(filePath.c_str());	
	getline(inFile, string);
	inFile.close();
	return string;
}

void update() {
  while(true) {
    get_usb_list();
    if(!comare_path_with_list()) {
	  block();
	} else {
	  unblock();
	}
  }
}

void get_usb_list() {
  system(" ls /media/mikhail/ > /home/mikhail/usblist.txt");
  read_file_to_list(USB_LIST_TXT);    
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

bool comare_path_with_list() {
  it = listOfUsb.begin();
  for(;it != listOfUsb.end(); ++it) {
    if(*it == path) {
	  return true;
	}	  
  }
  return false;
}

