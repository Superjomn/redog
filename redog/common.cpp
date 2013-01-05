/*
 * common.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "common.h"
//types
typedef unsigned int uint;
typedef unsigned short ushort;

namespace redog{
//paths

//只初始化一次
string Common::trainset_dir_path = "/home/chunwei/NetFlixData/trainset_datas.red";
string Common::trainset_file_pathlist = "/home/chunwei/NetFlixData/trainset_paths.red";
string Common::trainset_datas_path = "/home/chunwei/NetFlixData/trainset_datas.red";
string Common::probeset_file_path = "/home/chunwei/NetFlixData/probe.txt";
//init data
float Common::mean = 0.0;
//init others
vector < vector<RateRecord> > Common::rateMatrix;
/*
vector <ProbeRecord> probes;
//baseline for user u and item i
float bu[USER_NUM + 1];
float bi[ITEM_NUM + 1];
//用户u的评分数
unsigned int buNum[USER_NUM];
//item i 的被评分数
unsigned int biNum[ITEM_NUM];
//非负矩阵分解的两个特征向量 分别对应user item
//初始化为1
float p[USER_NUM][K] = {1};
float q[ITEM_NUM][K] = {1};
//隐含模型 y x
//全局平均数
 */
template<class Type>
void setValue(Type **arr, int size, int dim, Type (*Value)(int i, int j)){
	for(uint i=0; i<size; ++i){
		for(uint j=0; j<dim; ++j){
			arr[i][j] = Value(i, j);
		}
	}
}




};//namespace
