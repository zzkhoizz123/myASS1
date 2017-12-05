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
	//extern string fnameEventGB;
	fnameEventGB = fName;

	fstream eventFile;
	eventFile.open(fName, ios::in);
	if (!eventFile) {
		DSAException *ex = new DSAException(-3, "can not open File !");
		throw ex;
	}
	string str;
	while (!eventFile.eof()) {
		getline(eventFile, str);
		if (str.empty())
			continue;
		stringstream ss(str);
		char a[EVENT_CODE_SIZE];
		char event[EVENT_CODE_SIZE];
		while (ss >> a) {
			int i = 0;
			while (a[i] != ';' && a[i] != '\0') {
				event[i] = a[i];
				i++;
			}
			event[i] = '\0';
			ninjaEvent ne(event);
			eList.push_back(ne);
			strcpy(a, "");
			strcpy(event, "");
		}
	}
	eventFile.close();
}
