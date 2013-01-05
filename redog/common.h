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
#include <math.h>
#include <assert.h>

#define ITEM_NUM 17770
#define USER_NUM 480189
#define K 100
using namespace std;

namespace redog{
//types
typedef unsigned int uint;
typedef unsigned short ushort;

typedef enum{
	NetFlix,
	Test
}Mode;

typedef struct{
	uint userid;
	ushort itemid;
	char score;
} TrainRecord;

typedef struct{
	ushort itemid;
	char score;
} RateRecord;

typedef struct{
	ushort itemid;
	uint userid;
    char score;
} ProbeRecord;

typedef struct{
	ushort itemid;
	uint userid;
    unsigned float score;
} QualiRecord;

template<class Type>
void setValue(Type arr[], int size, Type v);


float dot(float puTemp[], float q[], int dim);

const static string netflix_dir = "/home/chunwei/NetFlixData/";
const static string test_dir = "/home/chunwei/SVDPPTest/";
//paths ----------------------------------------------------------------------------------
static string qualify_data_path = "qualifying.txt";
static string trainset_dir_path = "trainset_datas.red";
static string predict_data_path = "predict_datas.red";
//python 生成的file列表文件
static string trainset_file_pathlist = "trainset_paths.red";
//生成的二进制文件路径
static string trainset_datas_path = "trainset_datas.red";
static string probeset_file_path = "probe.txt";
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
//----------------------------------------------------------------------------------------
//training set data matrix
//need to initize space later
static vector < vector<RateRecord> > rateMatrix;
//qualifying datas 评估数据
static vector <QualiRecord> qualis;
//probe records
static vector <ProbeRecord> probes;

//baseline for user u and item i
static float bu[USER_NUM + 1] = {0};
static float bi[ITEM_NUM + 1] = {0};
//用户u的评分数
static uint buNum[USER_NUM] = {0};
//item i 的被评分数
static uint biNum[ITEM_NUM] = {0};
//非负矩阵分解的两个特征向量 分别对应user item
//初始化为1
static float p[USER_NUM][K] = {1.0};
static float q[ITEM_NUM][K] = {1.0};
//隐含模型 y
static float y[ITEM_NUM][K] = {1.0};
//全局平均数
static float mean = 0.0;

//系数 alpha需要在学习的时候修改学习速率
const static float looseRate = 0.99;
static float alpha1 = 0.01;
static float alpha2 = 0.01;
const static float beta1 = 0.05;
const static float beta2 = 0.05;


};// end namespace Common

#endif /* COMMON_H_ */
