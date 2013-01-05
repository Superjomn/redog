/*
 * UserIDTransfer.h
 *
 *  Created on: Jan 3, 2013
 *      Author: chunwei
 */

#ifndef USERIDTRANSFER_H_
#define USERIDTRANSFER_H_
#include "../common.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <assert.h>
using namespace std;
namespace redog {

class UserIDTransfer {
private:
	int fid[USER_NUM];
	ifstream file;
public:
	//从文件中载入 userids
	UserIDTransfer(char* path="/home/chunwei/NetFlixData/userids.red");
	//from array id to userid in file
	int a_to_f(int id);
	//from userid in file to array id
	int f_to_a(int id);
	void show(int mod = 0);
	virtual ~UserIDTransfer();
private:
	bool _compare(int i, int j);


};

} /* namespace redog */
#endif /* USERIDTRANSFER_H_ */
