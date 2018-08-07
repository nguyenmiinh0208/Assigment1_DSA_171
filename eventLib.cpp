/*
* =========================================================================================
* Name        : eventLib.cpp
* Author      : Duc Dung Nguyen, Nguyen Hoang Minh
* Email       : nddung@hcmut.edu.vn
* Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
* Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
*               This library contains functions used for event management
* =========================================================================================
*/

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	//TODO    
	char code[10];
	ifstream fileTxt;
	string str;
	fileTxt.open(fName);
	while (getline(fileTxt, str, ' '))
	{
		if (str[str.length() - 1] == ';') {
			strcpy(code, str.substr(0, str.length() - 1).c_str());
			ninjaEvent_t eventCode(code);
			eList.push_back(eventCode);
			break;
		}
		else {
			strcpy(code, str.c_str());
			ninjaEvent_t eventCode(code);
			eList.push_back(eventCode);
		}
	}
	fileTxt.close();
}
