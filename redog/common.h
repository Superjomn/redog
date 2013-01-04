/*
 * common.h
 *
 *  Created on: Jan 3, 2013
 *      Author: chunwei
 */

#ifndef COMMON_H_
#define COMMON_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <assert.h>

#define ITEM_NUM 17770
#define USER_NUM 480189
using namespace std;

namespace redog{
typedef struct{
	int userid;
	int itemid;
	short score;
} TrainRecord;

typedef struct{
	int itemid;
	short score;
} RateRecord;

typedef struct{
	int itemid;
	int userid;
} ProbeRecord;


//包含公共数据
class Common{
public:
	//paths --------------------------------------
	//train_set 文件夹路径
	string static trainset_dir_path;
	//python 生成的file列表文件
	static string trainset_file_pathlist;
	//生成的二进制文件路径
	static string trainset_datas_path;

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//training set data matrix
    //need to initize space later
	static vector < vector<RateRecord> > rateMatrix;
};







}; /* namespace redog */




#endif /* COMMON_H_ */
