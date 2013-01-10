/*
 * common.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "common.h"

namespace redog{

const string netflix_dir = "/home/chunwei/NetFlixData/";
const string test_dir = "/home/chunwei/SVDPPTest/";
//paths ----------------------------------------------------------------------------------
string qualify_data_path = "/home/chunwei/NetFlixData/qualifying.txt";
string trainset_dir_path =  "/home/chunwei/NetFlixData/trainset_datas.red";
string predict_data_path =  "/home/chunwei/NetFlixData/predict_datas.red";
//python 生成的file列表文件
string trainset_file_pathlist =  "/home/chunwei/NetFlixData/trainset_paths.red";
//生成的二进制文件路径
string trainset_datas_path ="/home/chunwei/NetFlixData/trainset_datas.red";
string probeset_file_path = "/home/chunwei/NetFlixData/probe.txt";
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
//----------------------------------------------------------------------------------------
//training set data matrix
//need to initize space later
vector < vector<RateRecord> > rateMatrix;
//qualifying datas 评估数据
vector <QualiRecord> qualis;
//probe records
 vector <ProbeRecord> probes;

//baseline for user u and item i
float bu[USER_NUM + 1] = {0};
float bi[ITEM_NUM + 1] = {0};
//用户u的评分数
uint buNum[USER_NUM] = {0};
//item i 的被评分数
uint biNum[ITEM_NUM] = {0};
//非负矩阵分解的两个特征向量 分别对应user item
//初始化为1
float p[USER_NUM][K] = {1.0};
float q[ITEM_NUM][K] = {1.0};
//隐含模型 y
float y[ITEM_NUM][K] = {1.0};
//tem 
float puTemp[USER_NUM][K] = {0.0};
uint nuNum[USER_NUM] = {0};
//全局平均数
float mean = 0.0;

//系数 alpha需要在学习的时候修改学习速率
const float looseRate = 0.99;
const float alpha1 = 0.01;
const float alpha2 = 0.01;
const float beta1 = 0.05;
const float beta2 = 0.05;



//paths
template<class Type>
void setValue(Type arr[], int size, Type v){
	for(uint i=0; i<size; ++i){
		arr[i] = v;
	}
}

float dot(float puTemp[], float q[], int dim){
	float res = 0.0;
	for(uint i=0; i<dim; ++i){
		res += puTemp[i] * q[i];
	}
	return res;
}

};//namespace
