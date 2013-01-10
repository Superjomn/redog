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

//item from 1 to 17770
#define ITEM_NUM 17770
#define USER_NUM 480189
#define MAX_STEP 60
#define K 30
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
    float score;
} QualiRecord;

template<class Type>
void setValue(Type arr[], int size, Type v);


float dot(float puTemp[], float q[], int dim);

extern const string netflix_dir;
extern const string test_dir ;
//paths ----------------------------------------------------------------------------------
extern string qualify_data_path ;
extern string trainset_dir_path ;
extern string predict_data_path ;
//python 生成的file列表文件
extern string trainset_file_pathlist ;
//生成的二进制文件路径
extern string trainset_datas_path ;
extern string probeset_file_path ;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
//----------------------------------------------------------------------------------------
//training set data matrix
//need to initize space later
extern vector < vector<RateRecord> > rateMatrix;
//qualifying datas 评估数据
extern vector <QualiRecord> qualis;
//probe records
extern vector <ProbeRecord> probes;

//baseline for user u and item i
extern float bu[USER_NUM + 1] ;
extern float bi[ITEM_NUM + 1] ;
//用户u的评分数
extern uint buNum[USER_NUM] ;
//item i 的被评分数
extern uint biNum[ITEM_NUM] ;
//非负矩阵分解的两个特征向量 分别对应user item
//初始化为1
extern float puTemp[USER_NUM][K];
extern float p[USER_NUM][K] ;
extern float q[ITEM_NUM][K] ;
extern uint nuNum[USER_NUM];
//隐含模型 y
extern float y[ITEM_NUM][K];
//全局平均数
extern float mean ;

//系数 alpha需要在学习的时候修改学习速率
extern const float looseRate ;
extern const float alpha1 ;
extern const float alpha2 ;
extern const float beta1 ;
extern const float beta2 ;


};// end namespace Common

#endif /* COMMON_H_ */
