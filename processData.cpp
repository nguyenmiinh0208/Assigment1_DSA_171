/*
* =========================================================================================
* Name        : processData.cpp
* Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
* =========================================================================================
*/
#include "eventLib.h"
#include "dbLib.h"

#define MAX 25

bool codeEvent3(L1List<NinjaInfo_t>& nList) {
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	int count = 1;
	while (pCur)
	{
		if (strcmp(pPre->data.id, pCur->data.id) != 0) {
			count++;
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	cout << count << endl;
	return true;
}

bool codeEvent4(L1List<NinjaInfo_t>& nList) {
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	string maxID = "";
	while (pPre) {
		if (strcmp(maxID.c_str(), pPre->data.id) < 0) maxID = string(pPre->data.id);
		pPre = pPre->pNext;
	}
	cout << maxID << endl;
	return true;
}

bool codeEvent5(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	//Lấy ra 4 ký tự cuối (số hiệu ABCD) của mã yêu cầu
	bool checkNinja = false;//Biến này kiểm tra xem ninja ABCD có trong danh sách dữ liệu hay không ?
	bool CheckNinja_IsMove = false;//Kiểm tra xem ninja ABCD có di chuyển
	string strCode = string(event.code).substr(1);
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	while (pCur) {
		// Tìm được id của mã yêu cầu
		if (strcmp(pPre->data.id, strCode.c_str()) == 0) {
			// Nếu 2 id liền kề là của 1 ninja
			checkNinja = true;//Có ninja cần tìm
			if (strcmp(pPre->data.id, pCur->data.id) == 0) {
				if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) > 0.005) {
					CheckNinja_IsMove = true;//Có di chuyển
					char timeDes[MAX];
					strPrintTime(timeDes, pPre->data.timestamp);
					cout << timeDes << endl;
					return true;
				}
				else {
					L1Item<NinjaInfo_t> *kPre = pCur;
					L1Item<NinjaInfo_t> *kCur = pCur->pNext;
					while (strcmp(kCur->data.id, pPre->data.id) == 0) {
						if (distanceEarth(pPre->data.latitude, pPre->data.longitude, kCur->data.latitude, kCur->data.longitude) > 0.005) {
							CheckNinja_IsMove = true;//Có di chuyển
							char timeDes[MAX];
							strPrintTime(timeDes, kCur->data.timestamp);
							cout << timeDes << endl;
							return true;
						}
						kPre = kCur;
						kCur = kCur->pNext;
					}
				}
			}
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (checkNinja == true && CheckNinja_IsMove == false) cout << "empty" << endl;
	if (checkNinja == false && CheckNinja_IsMove == false) cout << -1 << endl;
	return true;
}

bool codeEvent6(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	//Lấy ra 4 ký tự cuối (số hiệu ABCD) của mã yêu cầu
	string strCode = string(event.code).substr(1);
	bool checkNinja = false;//Biến này kiểm tra xem ninja ABCD có trong danh sách dữ liệu hay không ?
	bool CheckNinja_IsStop = false;//Kiểm tra xem ninja ABCD có dừng ?
	time_t timeStop;
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, strCode.c_str()) == 0) {
			checkNinja = true;//có ninja ABCD cần tìm
			if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) <= 0.005) {
				timeStop = pPre->data.timestamp;
				CheckNinja_IsStop = true;// ninja ABCD có dừng lại
				for (L1Item<NinjaInfo_t> *k = pCur->pNext; k; k = k->pNext) {
					if (distanceEarth(pPre->data.latitude, pPre->data.longitude, k->data.latitude, k->data.longitude) > 0.005) {
						pCur = k;
						break;
					}
				}
			}
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (checkNinja == false && CheckNinja_IsStop == false) {
		cout << -1 << endl;
		return true;
	}
	if (checkNinja == true && CheckNinja_IsStop == false) {
		cout << "Non-stop" << endl;
		return true;
	}
	char timeDes[MAX];
	strPrintTime(timeDes, timeStop);
	cout << timeDes << endl;
	return true;
}

bool codeEvent7(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	bool checkNinja = false;//Biến này kiểm tra xem ninja ABCD có trong danh sách dữ liệu hay không ?
	string strCode = string(event.code).substr(1);
	int count = 0;
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, strCode.c_str()) == 0) {
			checkNinja = true;
			if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) <= 0.005) {
				for (L1Item<NinjaInfo_t> *k = pCur->pNext; k; k = k->pNext) {
					if (distanceEarth(pPre->data.latitude, pPre->data.longitude, k->data.latitude, k->data.longitude) > 0.005) {
						count++;
						pCur = k;
						break;
					}
				}
			}
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (checkNinja == false) {
		cout << -1 << endl;
		return true;
	}
	cout << count << endl;
	return true;
}

bool codeEvent8(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	string strCode = string(event.code).substr(1);
	double s = 0;
	bool checkNinja = false; // biến này kiểm tra xem trong danh sách có ninja số hiệu là abcd không, nếu có thì check = true
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, strCode.c_str()) == 0) {
			checkNinja = true;
			if (strcmp(pPre->data.id, pCur->data.id) == 0)
				s += distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude);
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (checkNinja == false) {
		cout << -1 << endl;
		return true;
	}
	cout << s << endl;
	return true;
}

bool codeEvent9(L1List<NinjaInfo_t>& nList) {
	double maxS = 0;
	double s = 0;
	string idNinja;
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = nList.getHead()->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, pCur->data.id) == 0) {
			s += distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude);
		}
		else {
			if (s > maxS) {
				maxS = s;
				idNinja = string(pPre->data.id);
			}
			s = 0;
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	cout << idNinja << endl;
	return true;
}

bool codeEvent10(L1List<NinjaInfo_t>& nList) {
	string idNinja = "";
	time_t timeMove = 0; //Tính tổng thời gian của 1 ninja
	time_t maxtimeMove = 0;// Biến trung gian để so sánh
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = pPre->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, pCur->data.id) == 0) {
			if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) > 0.005) {
				timeMove += pCur->data.timestamp - pPre->data.timestamp;
			}
			else {
				for (L1Item<NinjaInfo_t> *k = pCur; k->pNext && strcmp(pPre->data.id, k->pNext->data.id) == 0; k = k->pNext) {
					if (distanceEarth(pPre->data.latitude, pPre->data.longitude, k->pNext->data.latitude, k->pNext->data.longitude) > 0.005) {
						timeMove += k->pNext->data.timestamp - k->data.timestamp;
						pCur = k->pNext;
						break;
					}
				}
			}
		}

		//Nếu đã duyệt hết thông tin của 1 ninja
		else {
			if (timeMove > maxtimeMove) {
				maxtimeMove = timeMove;
				idNinja = string(pPre->data.id);
			}
			timeMove = 0; // Reset timeMove = 0 để tính toán cho ninja tiếp theo 
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}

	cout << idNinja << endl;
	return true;
}

bool codeEvent11(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	string ninjaXYZT = string(event.code).substr(2);
	string iDNinja = "";//biến tạm để lấy ra id ninja --> xuất ra kết quả theo yêu cầu
	bool check = false;
	L1Item<NinjaInfo_t> *p = nList.getHead();
	while (p) {
		if (strcmp(p->data.id, ninjaXYZT.c_str()) < 0 && strcmp(p->data.id, iDNinja.c_str()) > 0){
			iDNinja = string(p->data.id);
			check = true;
		}
		p = p->pNext;
	}

	if (check == false) {
		cout << -1 << endl; // Nếu không có id thỏa yêu cầu
		return true;
	}
	else {// Nếu có id thỏa yêu cầu thì xóa id đó khỏi danh sách và in ra id đó
		L1Item<NinjaInfo_t> *p = nList.getHead();
		if (strcmp(p->data.id, iDNinja.c_str()) == 0) {
			while (strcmp(p->data.id, iDNinja.c_str()) == 0) {
				p = p->pNext;
				nList.removeHead();
			}
		}
		else {
			while (p->pNext) {
				if (strcmp(p->pNext->data.id, iDNinja.c_str()) == 0) {
					L1Item<NinjaInfo_t>	*tmp = p->pNext;
					p->pNext = tmp->pNext;
					delete tmp;
				}
				else p = p->pNext;
			}
		}
		cout << iDNinja << endl;
	}
	return true;
}

bool codeEvent12(L1List<NinjaInfo_t>& nList) {
	time_t maxTimeStop = 0;//Biến tạm để lưu thời gian dừng lại lớn nhất khi so sánh
	time_t timeMove = 0;//Thời gian di chuyển
	time_t timeStop = 0;//Thời gian dừng lại
	time_t sumTime = 0;//Tổng thời gian trong 1 ngày của ninja
	string idNinja = "";
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = pPre->pNext;
	while (pCur) {
		if (strcmp(pPre->data.id, pCur->data.id) == 0) {
			if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) > 0.005) {
				timeMove += pCur->data.timestamp - pPre->data.timestamp;
			}
			else {
				for (L1Item<NinjaInfo_t> *k = pCur; k->pNext && strcmp(pPre->data.id, k->pNext->data.id) == 0; k = k->pNext) {
					if (distanceEarth(pPre->data.latitude, pPre->data.longitude, k->pNext->data.latitude, k->pNext->data.longitude) > 0.005) {
						timeMove += k->pNext->data.timestamp - k->data.timestamp;
						pCur = k->pNext;
						break;
					}
				}
			}
			sumTime += pCur->data.timestamp - pPre->data.timestamp;//Cộng dồn để tính tổng thời gian trong 1 ngày của 1 ninja
		}

		else {
			timeStop = sumTime - timeMove;//Tính thời gian dừng lại bằng cách lấy thời gian của 1 ngày - thời gian di chuyển
			if (timeStop > maxTimeStop) {
				maxTimeStop = timeStop;
				idNinja = string(pPre->data.id);
			}
			//Reset tất cả các biến về 0 để tính cho các ninja tiếp theo
			timeStop = 0;
			sumTime = 0;
			timeMove = 0;
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	cout << idNinja << endl;
	return true;
}

bool codeEvent14(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList) {
	bool checkNinjaIsMove = true;//xét trạng thái hiện tại của ninja đang di chuyển hay dừng, true: di chuyển ; false: dừng
	bool ninja_astray = false;//Xét trạng thái của ninja đã bị lạc hay chưa
	bool checkList = false;//Xét xem trong list có ninja bị lạc hay không
	NinjaInfo_t stop;//Lưu lại tọa độ điểm dừng
	L1List<NinjaInfo_t> njMove_point;//List này sẽ chứa những điểm di chuyển của ninja đang xét
	L1Item<NinjaInfo_t> *pPre = nList.getHead();
	L1Item<NinjaInfo_t> *pCur = pPre->pNext;
	njMove_point.push_back(pPre->data);
	cout << event.code << ":";
	while (pCur) {
		if (strcmp(pPre->data.id, pCur->data.id) == 0) {
			if (!ninja_astray) {//Ninja chưa bị lạc
				if (checkNinjaIsMove == true) { //Ninja đang di chuyển
					if (distanceEarth(pPre->data.latitude, pPre->data.longitude, pCur->data.latitude, pCur->data.longitude) <= 0.005) {
						checkNinjaIsMove = false;
						stop = pPre->data;
					}
					else {
						//pCur là điểm di chuyển
						checkNinjaIsMove = true;
						for (L1Item<NinjaInfo_t> *k = njMove_point.getHead(); k; k = k->pNext) {
							if (distanceEarth(k->data.latitude, k->data.longitude, pCur->data.latitude, pCur->data.longitude) <= 0.005) {
								checkList = true;//Có ninja bị lạc
								ninja_astray = true; //ninja đã bị lạc
								cout << " " << pPre->data.id;
								break;
							}
						}
						njMove_point.push_back(pCur->data);
					}
				}
				else { //Ninja đang dừng
					if (distanceEarth(stop.latitude, stop.longitude, pCur->data.latitude, pCur->data.longitude) > 0.005) {
						checkNinjaIsMove = true;//Ninja di chuyển
						for (L1Item<NinjaInfo_t> *k = njMove_point.getHead(); k; k = k->pNext) {
							if (distanceEarth(k->data.latitude, k->data.longitude, pCur->data.latitude, pCur->data.longitude) <= 0.005) {
								checkList = true;//Có ninja bị lạc
								ninja_astray = true;//Ninja đã bị lạc
								cout << " " << pPre->data.id;
								break;
							}
						}
						njMove_point.push_back(pCur->data);
					}
				}
			}
		}

		else {//Đã xét hết 1 ninja và xét cho ninja tiếp theo
			checkNinjaIsMove = true;
			ninja_astray = false;
			//reset lại list để xét cho ninja tiếp theo
			njMove_point.~L1List();
			njMove_point.push_back(pCur->data);
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}

	if (!checkList) cout << -1;
	cout << endl;
	return true;
}


bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
	// TODO: Your code comes here
	if (string(event.code) == "3") { cout << event.code << ": "; codeEvent3(nList); return true; }
	if (string(event.code) == "4") { cout << event.code << ": "; codeEvent4(nList); return true; }
	if (string(event.code) == "9") { cout << event.code << ": "; codeEvent9(nList); return true; }
	if (string(event.code) == "10") { cout << event.code << ": "; codeEvent10(nList); return true; }
	if (string(event.code) == "12") { cout << event.code << ": "; codeEvent12(nList); return true; }
	if (string(event.code) == "14") { codeEvent14(event, nList); return true; }
	if (string(event.code).length() > 1)
	{
		if (event.code[0] == '5') { cout << event.code << ": "; codeEvent5(event, nList); return true; }
		if (event.code[0] == '6') { cout << event.code << ": "; codeEvent6(event, nList); return true; }
		if (event.code[0] == '7') { cout << event.code << ": "; codeEvent7(event, nList); return true; }
		if (event.code[0] == '8') { cout << event.code << ": "; codeEvent8(event, nList); return true; }
	}
	if (string(event.code).length() > 2)
	{
		string code;
		code = string(event.code).substr(0, 2);
		if (code == "11") { cout << event.code << ": "; codeEvent11(event, nList); return true; }
	}
	if (string(event.code).length() > 2 && string(event.code).length() <= 18)
	{
		string code;
		code = string(event.code).substr(0, 2);
		if (code == "13") return true;
	}
	return false;
	/// NOTE: The output of the event will be printed on one line
	/// end by the endline character.
}

