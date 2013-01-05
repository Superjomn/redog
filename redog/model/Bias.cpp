/*
 * Bias.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "Bias.h"

namespace redog {

Bias::Bias() {
	// TODO Auto-generated constructor stub
	this->bu = Common::bu;
	this->bi = Common::bi;
	this->biNum = Common::biNum;
	this->buNum = Common::buNum;
}

void Bias::init(){
	RateRecord *temrc;
	unsigned short tid;
	//user
    for(int i=0; i<USER_NUM; ++i)
    {//for each user
        for(int j=0; j<Common::rateMatrix[i].size(); ++j)
        {//for each item of user
        	temrc = &Common::rateMatrix[j][j];
        	bi[temrc->itemid] += temrc->score - Common::mean;
        	//num of item i's users
        	++biNum[temrc->itemid];
        }
    }
    //防止过度拟合
    for(int i=0; i<ITEM_NUM; ++i){
    	if(biNum[i] >= 1) bi[i] /= (biNum[i]+25);
    	else bi[i] = 0.0;
    }
    //for items
    for(int i=0; i<USER_NUM; ++i){
    	for(int j=0; j<Common::rateMatrix[i].size(); ++j){
    		bu[i] += Common::rateMatrix[i][j].score - Common::mean - bi[Common::rateMatrix[i][j].itemid];
    		//inc
    		++buNum[i];
    	}
    }
    //防止过度拟合
    for(int i=0; i<USER_NUM; ++i){
    	if(buNum[i]>1) bu[i] /= (buNum[i]+10);
    	else bu[i] = 0.0;
    }
}

void Bias::iter(){

}

Bias::~Bias() {
	// TODO Auto-generated destructor stub
}

} /* namespace redog */
