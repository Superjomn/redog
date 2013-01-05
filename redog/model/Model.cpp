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
	//setValue<float>(puTemp, USER_NUM, K, 0.0);
	//init characters
	bias.init();
	implicit.init();
	svd.init();
}


float Model::RMSEProbe(){
	uint size = probes.size();
	float rmse = 0.0;
	float prate = 0.0;
	float err = 0.0;
	for(uint i=0; i<size; ++i){
		prate = predictRate(probes[i].userid, probes[i].itemid, K);
		err = prate - probes[i].score;
		rmse += err*err;
	}
	rmse = sqrt(rmse / size);
	return rmse;
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

}


Model::~Model() {
	// TODO Auto-generated destructor stub
}

} /* namespace redog */
