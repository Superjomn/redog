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
#define K 100

using namespace std;

namespace redog{
typedef struct{
	unsigned int userid;
	unsigned short itemid;
	char score;
} TrainRecord;

typedef struct{
	unsigned short itemid;
	char score;
} RateRecord;

typedef struct{
	unsigned short itemid;
	unsigned int userid;
    char score;
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
    //probe
    static string probeset_file_path;

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//training set data matrix
    //need to initize space later
	static vector < vector<RateRecord> > rateMatrix;
    //probe records
    static vector <ProbeRecord> probes;
    //baseline for user u and item i
    static float bu[USER_NUM + 1];
    static float bi[ITEM_NUM + 1];
    //用户u的评分数
    static unsigned int buNum[USER_NUM];
    //item i 的被评分数
    static unsigned int biNum[ITEM_NUM];
    //非负矩阵分解的两个特征向量 分别对应user item
    //初始化为1
    static float p[USER_NUM][K];
    static float q[ITEM_NUM][K];
    //隐含模型 y
    static float y[ITEM_NUM][K];
    //全局平均数
    static float mean;
};

template<class Type>
void setValue(Type **arr, int size, int dim, Type (*Value)(int i, int j));









}; /* namespace redog */




#endif /* COMMON_H_ */
