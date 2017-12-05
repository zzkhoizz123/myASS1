/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"
#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = localtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
	// TODO: write code to load information from file into db
	fstream dataFile;
	dataFile.open(fName, ios::in);
	if (!dataFile) {
		DSAException *ex = new DSAException(-3, "Can not open File!");
		throw ex;
	}
	string str;
	char ch;
	getline(dataFile, str); //------------------------------:::: abandon first line
	//getline(dataFile, str); // neu doc .csv thi bo dong nay

	while (!dataFile.eof()) {
		NinjaInfo_t ninja;
		getline(dataFile, str);		
		if (str.empty()) continue;
		stringstream ss(str);
		//--------------------------------------------------::: release the REV
		int ret;
		ss >> ret >> ch;

		// -------------------------------------------------:::: get local time
		tm tm_date = { 0 };
		char *date = new char[15];
		ss >> date;
		date[2] = date[5] = '\0';
		tm_date.tm_mon = atoi(&date[0]) - 1;
		tm_date.tm_mday = atoi(&date[3]);
		tm_date.tm_year = atoi(&date[6]) - 1900;

		// -------------------------------------------------:::: get local time
		int hour = 0, min = 0, sec = 0;
		ss >> hour >> ch >> min >> ch >> sec;

		tm_date.tm_hour = hour;
		tm_date.tm_min = min;
		tm_date.tm_sec = sec;

		ninja.timestamp = mktime(&tm_date);
		ss >> ch;
		
		//--------------------------------------------------:::: get id
		int run = 0;
		char ninjaret[ID_MAX_LENGTH];
		while (ss >> ch) {
			if (ch == ',')
				break;
			ninjaret[run] = ch;
			run++;
		}
		ninjaret[run] = '\0';

		if (run == 1) {
			string str2 = "000" + (string)ninjaret;
			const char *a = str2.c_str();
			strcpy(ninja.id, a);
		}
		else if (run == 2) {
			string str2 = "00" + (string)ninjaret;
			const char *a = str2.c_str();
			strcpy(ninja.id, a);
		}
		else if (run == 3) {
			string str2 = "0" + (string)ninjaret;
			const char *a = str2.c_str();
			strcpy(ninja.id, a);
		}
		else {
			strcpy(ninja.id, ninjaret);
		}

		//--------------------------------------------------:::: get Longitude and latitude

		ss >> ninja.longitude;
		ss >> ch >> ninja.latitude;
		//--------------------------------------------------:::: push into database					

		db.insertHead(ninja);

		//-------------------------------------------------- if using .csv is regardless this code
		/*if (!dataFile.eof()) {
			getline(dataFile, str);
		}*/
	}
	dataFile.close();
	db.Reverse();
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
    // TODO: write code to parse information from a string buffer, ignore if you don't use it
    return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
	void*   pGData = NULL;
	initNinjaGlobalData(&pGData);

	while (!eventList.isEmpty()) {
		if (!processEvent(eventList[0], bList, pGData))
			cout << eventList[0].code << " is an invalid event\n";
		eventList.removeHead();
	}
	releaseNinjaGlobalData(pGData);
}


bool initNinjaGlobalData(void** pGData) {
    /// TODO: You should define this function if you would like to use some extra data
    /// the data should be allocated and pass the address into pGData
    return true;
}

void releaseNinjaGlobalData(void* pGData) {
    /// TODO: You should define this function if you allocated extra data at initialization stage
    /// The data pointed by pGData should be released
}

void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}