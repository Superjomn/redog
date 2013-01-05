/*
 * TrainSetLoader.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef TRAINSETLOADER_H_
#define TRAINSETLOADER_H_

#include "../common.h"
#include <sstream>
#include "DataLoader.h"
#include "UserIDTransfer.h"
using namespace std;

namespace redog {

class TrainSetLoader {
private:
	string listpath;
	//前期生成
	vector<TrainRecord> datas;
	//从二进制文件中载入 生成rateMatrix
	TrainRecord *darr;
	int filenum;
public:
	TrainSetLoader();
	bool load();
	bool fromfile();
	bool tofile();
	// compare for sort ; first userid then itemid
	//bool _compare(const TrainRecord &a, const TrainRecord &b);
	//parse sigle training file
	bool parse(char *path);
    //sort datas: first userid then itemid
	void _sort();
	bool _split(const std::string &s, char delim, vector<string>&tem);
	//从 datas init rateMatrix
	void _initRateMatrix();
	void show();
    void showRateMatrix();
};

} /* namespace redog */
#endif /* TRAINSETLOADER_H_ */
