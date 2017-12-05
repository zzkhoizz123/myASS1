/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"

string fnameEventGB;
string idNinjaFirst;
string idNinjaLast;
int flat1 = 0; // kiem tra event 11 da goi chua
int flat2 = 0; // kiem tra event 12 da goi hay chua
L1List<string> *idNinjaLostList = new L1List<string>();

struct MapTime {
	char id[ID_MAX_LENGTH];
	double time;

	MapTime() :time(0.0) {
		strcpy(id, "");
	}

	MapTime(const char *newid, double newtime) :time(newtime) {
		strcpy(id, newid);
	}
};

struct MapRoad {
	char id[ID_MAX_LENGTH];
	double RoadLength;

	MapRoad() : RoadLength(0) {
		strcpy(id, "");
	}

	MapRoad(const char *idnew, double rLength) :RoadLength(rLength) {
		strcpy(id, idnew);
	}
};


// Khai bao nguyen mau ham

bool process0Event();

bool process1Event(L1List<NinjaInfo_t> &nList);

bool process2Event(L1List<NinjaInfo_t> &nList);

bool process3Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);
bool testId(const char *id, L1List<NinjaInfo_t> &list);

bool process4Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);

bool process5Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);

bool process6Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);

bool process7Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dblist);

bool process8Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dblist);

string id_maxRoad(L1List<MapRoad> &mapList);
bool checkId_mapRoad(char *id, L1List<MapRoad> &mapList);
double RoadLength(const char* id, L1List<NinjaInfo_t> &dbList);
bool process9Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);

double TimeGo(const char* id, L1List<NinjaInfo_t> &dbList);
bool checkId_mapTime(char * id, L1List<MapTime> &mapList);
string id_maxTime(L1List<MapTime> &mapList);
bool process10Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);


bool checkId_idList(char *id, L1List<string> &idList);
void RefineId(L1List<NinjaInfo_t> &dbList, L1List<string> &idList);
bool process11Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);


double TimeStop(const char *id, L1List<NinjaInfo_t> &dblist);
bool process12Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);


bool process14Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList);


bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
	// TODO: Your code comes here
	string str = event.code;
	string str_first = str.substr(0, 1); //---------------------------------------- take evey character from position one to over
	string str_first_last = str.substr(0, 2);

	if (str_first == "0" && str.size() == 1) {
		return process0Event();
	}
	else if (str_first == "1" && str.size() == 1) {
		if (flat1 == 0) {
			cout << "1: " << nList[0].id << '\n';
		}
		else {
			cout << "1: " << idNinjaFirst << '\n';
		}
		return true;
	}

	else if (str_first == "2" && str.size() == 1) {
		if (flat1 == 0) {
			cout << "2: " << nList[nList.getSize()-1].id << '\n';
		}
		else {
			cout << "2: " << idNinjaLast << '\n';
		}
		return true;
	}

	else if (str_first == "3" && str.size() == 1) {
		return process3Event(event, nList);
	}
	else if (str_first == "4" && str.size() == 1) {
		return process4Event(event, nList);
	}
	else if (str_first == "5") {
		return process5Event(event, nList);
	}
	else if (str_first == "6") {
		return process6Event(event, nList);
	}
	else if (str_first == "7") {
		return process7Event(event, nList);
	}
	else if (str_first == "8") {
		return process8Event(event, nList);
	}
	else if (str_first == "9" && str.size() == 1) {
		return process9Event(event, nList);
	}
	else if (str_first_last == "10" && str.size() == 2) {
		return process10Event(event, nList);
	}
	else if (str_first_last == "11") {
		if (flat1 == 0) {
			process1Event(nList);
			process2Event(nList);
			idNinjaLostList = new L1List<string>();
			process14Event(event,nList);
			flat1 = 1; flat2 = 1;
		}
		return process11Event(event, nList);
	}
	else if (str_first_last == "12" && str.size() == 2) {
		return process12Event(event, nList);
	}
	else if (str_first_last == "13" && str.size() != 2) {
		return true; /// Khong xu ly
	}
	else if (str_first_last == "14" && str.size() == 2) {
		if (flat2 == 0) { // chua goi event 14
			idNinjaLostList = new L1List<string>();
			process14Event(event, nList);
			L1Item<string> *p1 = idNinjaLostList->getHead();
			cout << event.code << ": ";
			if (p1 == NULL) {
				cout << "Non-lost\n";
			}
			else {
				while (p1) {
					if (p1->pNext == NULL) {
						cout << p1->data << '\n';
						break;
					}
					cout << p1->data << " ";
					p1 = p1->pNext;
				}
			}
			flat2 = 1;
		}
		else if (flat2 == 1 && flat1 == 0) { //da goi event 14 nhung chua goi event 11
			L1Item<string> *p1 = idNinjaLostList->getHead();
			cout << event.code << ": ";
			if (p1 == NULL) {
				cout << "Non-lost\n";
			}
			else {
				while (p1) {
					if (p1->pNext == NULL) {
						cout << p1->data << '\n';
						break;
					}
					cout << p1->data << " ";
					p1 = p1->pNext;
				}
			}
		}
		else { // da goi 14 va da goi 11 
			// da goi event 11
			idNinjaLostList = new L1List<string>();
			process14Event(event, nList);
			L1Item<string> *p1 = idNinjaLostList->getHead();
			cout << event.code << ": ";
			if (p1 == NULL) {
				cout << "Non-lost\n";
			}
			else {
				while (p1) {
					if (p1->pNext == NULL) {
						cout << p1->data << '\n';
						break;
					}
					cout << p1->data << " ";
					p1 = p1->pNext;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
	/// NOTE: The output of the event will be printed on one line
	/// end by the endline character.
}

bool process1Event(L1List<NinjaInfo_t> &nList) {
	//extern string idNinjaFirst;
	idNinjaFirst = nList[0].id;
	return true;
}

bool process2Event(L1List<NinjaInfo_t> &nList) {
	//extern string idNinjaLast;
	idNinjaLast = nList[nList.getSize() - 1].id;
	return true;
}

bool process0Event() {
	cout << "0: ";
	fstream eventFile;
	eventFile.open(fnameEventGB, ios::in);
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

			if (a[i] == ';') {
				cout << event << '\n';
				break;
			}

			cout << event << " ";
			strcpy(a, "");
			strcpy(event, "");
		}
	}
	eventFile.close();
	return true;
}

bool testId(const char *id, L1List<NinjaInfo_t> &list) {
	L1Item<NinjaInfo_t> *p = list.getHead();
	while (p) {
		if (strcmp(p->data.id, id) == 0)
			return false;
		p = p->pNext;
	}
	return true;
}

bool process3Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {

	L1Item<NinjaInfo_t> *p = dbList.getHead();
	long run = 0;
	L1List<NinjaInfo_t> newList;
	while (p) {
		if (testId(p->data.id, newList)) {
			newList.insertHead(p->data);
		}
		p = p->pNext;
	}
	cout << event.code << ": " << newList.getSize() << '\n';
	return true;
}

bool process4Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {
	char idMax[EVENT_CODE_SIZE];

	L1Item<NinjaInfo_t>* p = dbList.getHead();
	strcpy(idMax, p->data.id);
	p = p->pNext;
	while (p) {
		if (strcmp(idMax, p->data.id) < 0)
			strcpy(idMax, p->data.id);
		p = p->pNext;
	}
	cout << event.code << ": " << idMax << '\n';
	return true;
}

bool process5Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {

	string str = event.code;
	str = str.substr(1); //---------------------------------------- take evey character from position one to over
	const char *idcmp = str.c_str(); //--------------------------- convert string to const char*
	int flat = 0;
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	time_t timeMove;
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	NinjaInfo_t ninjaTemp;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaCur = ninjaTemp = p->data;
			flat = 1;
			break;
		}
		p = p->pNext;
	}
	if (flat == 0) {
		cout << event.code << ": -1\n";
		return true;
	}

	flat = 0;
	p = p->pNext;
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			if (distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude) <= 5.0 / 1000) {
				ninjaCur = ninjaPre;
				flat = 1;
			}
			else {
				if (flat == 0){
					timeMove = ninjaPre.timestamp;
					char *strTime = new char[26];
					strPrintTime(strTime, timeMove);
					cout << event.code << ": " << strTime << '\n';
					return true;
				}
				else {
					timeMove = ninjaCur.timestamp;
					char *strTime = new char[26];
					strPrintTime(strTime, timeMove);
					cout << event.code << ": " << strTime << '\n';
					return true;
				}
			}
		}
		p = p->pNext;
	}

	timeMove = ninjaTemp.timestamp;
	char *strTime = new char[26];
	strPrintTime(strTime, timeMove);
	cout << event.code << ": " << strTime << '\n';
	return true;
}


bool process6Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {

	string str = event.code;
	str = str.substr(1); //---------------------------------------- take evey character from position one to over
	const char *idcmp = str.c_str(); //--------------------------- convert string to const char*
	int flat = 0;
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	time_t timeStop;
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaCur = p->data;
			flat = 1;
			break;
		}
		p = p->pNext;
	}
	if (flat == 0) {
		cout << event.code << ": -1\n";
		return true;
	}
	p = p->pNext;
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			if (distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude) <= 5.0 / 1000) {
				ninjaCur = ninjaPre;
				timeStop = ninjaPre.timestamp;
				flat = 0;
			}
		}
		p = p->pNext;
	}
	if (flat == 1) {
		cout << event.code << ": " << "Non-stop\n";
	}
	else {
		char *strTime = new char[26];
		strPrintTime(strTime, timeStop);
		cout << event.code << ": " << strTime << '\n';
	}
	return true;
}


bool process7Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dblist) {

	string str = event.code;
	str = str.substr(1); //---------------------------------------- take evey character from position one to over
	const char *idcmp = str.c_str(); //--------------------------- convert string to const char*
	int flat = 0;
	L1Item<NinjaInfo_t>*p = dblist.getHead();
	long ninjaStop_repeat = 0;
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaCur = p->data;
			flat = 1;
			break;
		}
		p = p->pNext;
	}
	if (flat == 0) {
		cout << event.code << ": -1\n";
		return true;
	}
	flat = 0;
	p = p->pNext;
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			if (distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude) <= 5.0 / 1000) {
				--flat;
				ninjaCur = ninjaPre;
			}
			else flat = 0;
			if (flat == -1) ninjaStop_repeat++;
		}
		p = p->pNext;
	}
	cout << event.code << ": " << ninjaStop_repeat << '\n';
	return true;
}


bool process8Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dblist) {
	string str = event.code;
	str = str.substr(1); //---------------------------------------- take evey character from position one to over
	const char *idcmp = str.c_str(); //--------------------------- convert string to const char*
	int flat = 0;
	L1Item<NinjaInfo_t>* p = dblist.getHead();
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(p->data.id,idcmp) == 0) {
			ninjaCur = p->data;
			flat = 1;
			break;
		}
		p = p->pNext;
	}
	if (flat == 0) {
		cout << event.code << ": -1\n";
		return true;
	}

	p = p->pNext;
	double roadLenght = 0;
	while (p) {
		if (strcmp(idcmp, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			double distance = distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude);
			roadLenght += distance;
		}
		p = p->pNext;
	}

	cout << event.code << ": " << roadLenght << "\n";
	return true;
}

double RoadLength(const char* id, L1List<NinjaInfo_t> &dbList) {
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(p->data.id,id) == 0 ) { //------------------------------- call operator == (ninja , char *)
			ninjaCur = p->data;
			break;
		}
		p = p->pNext;
	}
	p = p->pNext;
	double roadLenght = 0;
	while (p) {
		if (strcmp(p->data.id,id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			double distance = distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude);
			roadLenght += distance;
		}
		p = p->pNext;
	}
	return roadLenght;
}


bool checkId_mapRoad(char *id, L1List<MapRoad> &mapList) {
	L1Item<MapRoad> *p = mapList.getHead();
	while (p) {
		if (strcmp(p->data.id, id) == 0)
			return false;
		p = p->pNext;
	}
	return true;
}


string id_maxRoad(L1List<MapRoad> &mapList) {
	L1Item<MapRoad> *p = mapList.getHead();
	double maxLength = p->data.RoadLength;
	string str(p->data.id);
	p = p->pNext;
	while (p) {
		if (maxLength < p->data.RoadLength) {
			maxLength = p->data.RoadLength;
			str = string(p->data.id);
		}
		p = p->pNext;
	}
	return str;
}

bool process9Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {
	L1List<MapRoad> mapList;
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	while (p) {
		if (checkId_mapRoad(p->data.id, mapList)) {
			double rLength = RoadLength(p->data.id, dbList);
			MapRoad map(p->data.id, rLength);
			mapList.insertHead(map); //
		}
		p = p->pNext;
	}
	string str = id_maxRoad(mapList);
	cout << event.code << ": " << str << '\n';
	return true;
}

// 1->2 : dung 
// 1->3 : dung
// 1->4 : di chuyen
//=> thoi gan di chuyen : 3->4
double TimeGo(const char* id, L1List<NinjaInfo_t> &dbList) {
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	NinjaInfo_t ninjaNext;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(p->data.id,id) == 0) { //------------------------------- call operator == (ninja , char *)
			ninjaNext = p->data;
			break;
		}
		p = p->pNext;
	}
	p = p->pNext;
	double time = 0;
	ninjaCur = ninjaNext;
	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			ninjaPre = ninjaNext;
			ninjaNext = p->data;

			double distance = distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaNext.latitude, ninjaNext.longitude);
			if (distance <= 5.0 / 1000) {
				ninjaCur = ninjaNext;
				ninjaNext = ninjaPre;
			}
			else {
				time += difftime(ninjaNext.timestamp,ninjaCur.timestamp);
				ninjaCur = ninjaNext;
			}
		}
		p = p->pNext;
	}
	return time;
}


bool checkId_mapTime(char * id, L1List<MapTime> &mapList) {
	L1Item<MapTime>*p = mapList.getHead();
	while (p) {
		if (strcmp(p->data.id, id) == 0)
			return false;
		p = p->pNext;
	}
	return true;
}

string id_maxTime(L1List<MapTime> &mapList) {
	L1Item<MapTime>*p = mapList.getHead();
	double maxtime = p->data.time;
	string str(p->data.id);
	p = p->pNext;
	while (p) {
		if (maxtime < p->data.time) {
			maxtime = p->data.time;
			str = string(p->data.id);
		}
		p = p->pNext;
	}
	return str;
}

bool process10Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {

	L1List<MapTime> mapList;
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	while (p) {
		if (checkId_mapTime(p->data.id, mapList)) {
			double time = TimeGo(p->data.id, dbList);
			MapTime map(p->data.id, time);
			mapList.insertHead(map);
		}
		p = p->pNext;
	}
	string str = id_maxTime(mapList);
	cout << event.code << ": " << str << '\n';
	return true;
}

bool checkId_idList(char *id, L1List<string> &idList) {
	L1Item<string>*p = idList.getHead();
	while (p) {
		const char *cstr = p->data.c_str();
		if (strcmp(id, cstr) == 0) {
			return false;
		}
		p = p->pNext;
	}
	return true;
}

void RefineId(L1List<NinjaInfo_t> &dbList, L1List<string> &idList) {
	L1Item<NinjaInfo_t>*p = dbList.getHead();
	while (p) {
		if (checkId_idList(p->data.id, idList)) {
			string str = p->data.id;
			idList.insertHead(str);
		}
		p = p->pNext;
	}
}

void RemoveNinjaPseudo(const char * idRemove, L1List<NinjaInfo_t> &dbList) {
	L1Item<NinjaInfo_t> *p = dbList.getHead();
	L1Item<NinjaInfo_t> *pRev = p;
	int i = 0;
	while (p) {
		if (strcmp(idRemove, p->data.id) == 0) {
			if (i == 0) {
				dbList.setHead(p->pNext);
				p = p->pNext;
				dbList.downSize();
				i = 0;
				continue;
			}
			else {
				pRev->pNext = p->pNext;
				p = p->pNext;
				dbList.downSize();
				i = 1;
			}
		}
		else {
			pRev = p;
			p = p->pNext;
			i = 1;
		}
	}
}

bool process11Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {
	string str = event.code;
	string strcmp = str.substr(2); //---------------------------------------- take evey character from position one to over

	L1List<string> idList;
	RefineId(dbList, idList);
	L1Item<string> *p = idList.getHead();
	string strPseudo = "";
	int flat = 0;
	while (p) {
		if (p->data < strcmp) {
			strPseudo = p->data;
			flat = 1;
			break;
		}
		p = p->pNext;
	}
	if (flat == 0) {
		cout << event.code << ": -1\n";
		return true;
	}

	p = p->pNext;
	while (p) {
		if (p->data < strcmp) {
			if (p->data > strPseudo) {
				strPseudo = p->data;
			}
		}
		p = p->pNext;
	}

	const char* cPseudo = strPseudo.c_str();
	RemoveNinjaPseudo(cPseudo, dbList);
	cout << event.code << ": " << strPseudo << '\n';
	return true;
}


// like question 10
// using checkId_mapTime function and id_maxTime function from question 10
// 1->2 : dung 
// 1->3 : dung
// 1->4 : di chuyen
//=> thoi gian dung : 1->3

double TimeStop(const char *id, L1List<NinjaInfo_t> &dblist) {
	L1Item<NinjaInfo_t> *p = dblist.getHead();
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;
	//------------------------------------------------------------ get the ninja into ninjaCur and set a flat
	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			ninjaCur = p->data;
			break;
		}
		p = p->pNext;
	}

	p = p->pNext;
	double timeStop = 0;
	double timetemp = 0;
	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			double distance = distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude);
			if (distance <= 5.0 / 1000) {
				timetemp = difftime(ninjaCur.timestamp, ninjaPre.timestamp);
				ninjaCur = ninjaPre;
			}
			else {
				timeStop += timetemp;
				timetemp = 0;
			}
		}
		if (p->pNext == NULL) {
			timeStop += timetemp;
		}
		p = p->pNext;
	}
	return timeStop;
}

bool process12Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {
	L1List<MapTime> mapList;
	L1Item<NinjaInfo_t>*p = dbList.getHead();
	while (p) {
		if (checkId_mapTime(p->data.id, mapList)) {
			double time = TimeStop(p->data.id, dbList);
			MapTime map(p->data.id, time);
			mapList.insertHead(map);
		}
		p = p->pNext;
	}
	string str = id_maxTime(mapList);
	cout << event.code << ": " << str << '\n';
	return true;
}

bool checkninjaLost(NinjaInfo_t ninja, L1List<NinjaInfo_t> &ninjaLostList) {
	L1Item<NinjaInfo_t> *p = ninjaLostList.getHead();
	while (p) {
		double distance = distanceEarth(p->data.latitude, p->data.longitude, ninja.latitude, ninja.longitude);
		if (distance <= 5.0 / 1000) {
			return true; // bi lac
		}
		p = p->pNext;
	}
	return false; // khong bi lac
}

bool checkninjaLost(char *id, L1List<NinjaInfo_t> &dbList) {

	L1List<NinjaInfo_t> ninjaMoveList;

	L1Item<NinjaInfo_t> *p = dbList.getHead();
	NinjaInfo_t ninjaPre;
	NinjaInfo_t ninjaCur;

	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			ninjaCur = p->data;
			ninjaMoveList.insertHead(ninjaCur);
			break;
		}
		p = p->pNext;
	}

	p = p->pNext;
	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			ninjaPre = ninjaCur;
			ninjaCur = p->data;
			double distance = distanceEarth(ninjaPre.latitude, ninjaPre.longitude, ninjaCur.latitude, ninjaCur.longitude);
			if (distance <= 5.0 / 1000) {
				ninjaCur = ninjaPre;
			}
			else {
				if (checkninjaLost(ninjaCur, ninjaMoveList) == true)
					return true; // bi lac
				else
					ninjaMoveList.insertHead(ninjaCur);
			}
		}
		p = p->pNext;
	}
	return false;
}

bool checkId_List(char * id, L1List<NinjaInfo_t> &listTemp) {
	L1Item<NinjaInfo_t> *p = listTemp.getHead();
	while (p) {
		if (strcmp(id, p->data.id) == 0) {
			return false; // co roi 
		}
		p = p->pNext;
	}
	return true; // chua co
}

bool process14Event(ninjaEvent_t event, L1List<NinjaInfo_t> &dbList) {

	L1Item<NinjaInfo_t> *p = dbList.getHead();

	L1List<NinjaInfo_t> listTemp;

	while (p) {
		if (checkId_List(p->data.id, listTemp) == true) {
			listTemp.insertHead(p->data);
			if (checkninjaLost(p->data.id, dbList) == true) {
				string str = p->data.id;
				idNinjaLostList->push_back(str);
			}
		}
		p = p->pNext;
	}
	return true;
}