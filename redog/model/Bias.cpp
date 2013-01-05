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
	this->bu = bu;
	this->bi = bi;
	this->biNum = biNum;
	this->buNum = buNum;
	//init buNum biNum
	//setValue<uint>(biNum, ITEM_NUM, 0);
	//setValue<uint>(buNum, USER_NUM, 0);
}

void Bias::init(){
	RateRecord *temrc;
	//user
    for(int i=0; i<USER_NUM; ++i)
    {//for each user
        for(uint j=0; j<rateMatrix[i].size(); ++j)
        {//for each item of user
        	temrc = &rateMatrix[j][j];
        	bi[temrc->itemid] += temrc->score - mean;
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
    	for(int j=0; j<rateMatrix[i].size(); ++j){
    		bu[i] += rateMatrix[i][j].score - mean - bi[rateMatrix[i][j].itemid];
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

void Bias::_initBiBuNum(){
	for(uint i=0; i<USER_NUM; ++i){
		ushort itemnum = rateMatrix[i].size();
		//set num of user u 's rates
		buNum[i] = itemnum;
		for(uint j=0; j<itemnum; ++j){
			//inc num of item i's rates
			++ biNum[j];
		}
	}
}

void Bias::iter(){

}

Bias::~Bias() {
	// TODO Auto-generated destructor stub
}

} /* namespace redog */
