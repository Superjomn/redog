/*
 * Model.cpp
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#include "Model.h"

namespace redog {

Model::Model() {
	preRMSE = 100000;
	curRMSE = 0.0;
	step = 0;
	//setValue<float>(puTemp, USER_NUM, K, 0.0);
	//init characters
	bias.init();
	implicit.init();
	svd.init();
}

void Model::iterate(){
	//init 需要train_set probe_set qualifying_set 的数据
	//均载入
	initMean();
	initPuTemp();
	initNuNum();
	//初始第一次升级各个参数
	update();
	if(goodEnough()){
		cout<<" .. succeed end"<<endl;
	}else{
		cout<<".. run step: "<<step<<endl;
		update();
	}
}

void Model::initMean(){
	unsigned long num = 0;
	unsigned long sum = 0;
	for(uint i=0; i<USER_NUM; ++i){
		for(uint j=0; j<rateMatrix[i].size(); ++j){
			++num;
			sum += rateMatrix[i][j].score;
		}
	}
	mean = sum/num;
}


//仅仅是测试精度
float Model::RMSEProbe(){
	uint size = probes.size();
	float rmse = 0.0;
	float prate = 0.0;
	float err = 0.0;
	for(uint i=0; i<size; ++i){
		//此处文件中的userid 需要进行转化
		prate = predictRate(probes[i].userid, probes[i].itemid, K);
		err = prate - probes[i].score;
		rmse += err*err;
	}
	rmse = sqrt(rmse / size);
	cout<<"RMSE:"<<rmse<<" probeNum:"<<size<<endl;
	return rmse;
}

void Model::calQualis(){
	uint size = qualis.size();
    //对每个记录遍历
	for(uint i=0; i<size; ++i){
		//此处文件中的userid 需要进行转化
		qualis[i].score = predictRate(qualis[i].userid, qualis[i].itemid, K);
	}
	cout<<".. predicted qualis size: "<<size<<endl;
}

float Model::predictRate(int user, int item, int dim)
{
    int RuNum = rateMatrix[user].size(); //the num of items rated by user
    double ret;
    if(RuNum >= 1) {
        ret = mean + bu[user] + bi[item] +  dot(puTemp[user], q[item], dim);
    }
    else ret  = mean + bu[user] + bi[item];
    if(ret < 1.0) ret = 1;
    if(ret > 5.0) ret = 5;
    return ret;
}

void Model::initPuTemp(){
	float sumy = 0.0;
	for(uint u=0; u<USER_NUM; ++u){
		for(uint k=0; k<K; ++k){
			for(uint i=0; i<buNum[i]; ++i){
				int itemI = rateMatrix[u][i].itemid;
				sumy += y[itemI][k];
			}
			puTemp[u][k] = p[u][k] + sqrt(buNum[u]) * sumy;
		}
	}
}

void Model::initNuNum(){
	//init nuNum
	for(uint i=0; i<USER_NUM; ++i){
		qualis[i] = 0;
	}
	//first from qualis
	for(uint i=0; i<qualis.size(); ++i){
		++nuNum[qualis[i].userid];
	}
	//from rateMatrix
	for(uint i=0; i<USER_NUM; ++i){
		nuNum[i] += rateMatrix[i].size();
	}
}

void Model::update(){
	//inc step
	++step;
	float rmse = 0.0;
	unsigned long record_num = 0;
	for(uint u=0; u<USER_NUM; ++u){
		float sumQE[K] = {0.0};
		uint isize = rateMatrix[u].size();
		for(uint i=0; i<isize; ++i){
			++record_num;
			//update every parameter
			uint itemI = rateMatrix[u][i].itemid;
			float pui = predictRate(u, itemI, K);
			float eui = rateMatrix[u][i].score - pui;
			rmse += eui * eui;
			//update bu bi
			bu[u] += alpha1 * (eui - beta1 * bu[u]);
			bi[itemI] += alpha1 * (eui - beta1 * bi[itemI]);
			//update p q
			for(uint k=0; k<K; ++k){
				p[u][k] += alpha2 * (eui * q[itemI][k] - beta2 * p[u][k]);
				q[itemI][k] += alpha2 * (eui * puTemp[u][k] - beta2 * q[itemI][k]);
				sumQE[k] += eui * q[itemI][k];
			}
		}// end item iter
		//update implicit parameter y
		for(uint j=0; j < nuNum[u]; ++j){
			int itemJ = rateMatrix[u][j].itemid;
			for(uint k=0; k<K; ++k){
				y[itemJ][k] += alpha2 * (sqrt(nuNum[u] * sumQE[k] - beta2*y[itemJ][k]));
			}
		}// end update y
		//计算Qualis 一直保存上一个状态
		//最终可以写入文件
		calQualis();
		//update rmse
		curRMSE = sqrt(rmse / record_num);
	}//end user iter
}

bool Model::goodEnough(){
	if(curRMSE >= preRMSE && step >= 3){
		return false;
	}
	else{
		preRMSE = curRMSE;
		// maybe should slow the study rate
		cout<<"RMSE:   from "<<preRMSE<<" to "<<curRMSE<<endl;
		return true;
	}
}
/*
Model::~Model() {
	// TODO Auto-generated destructor stub
}*/

} /* namespace redog */
