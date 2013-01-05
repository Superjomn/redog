/*
 * SVD.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "SVD.h"

namespace redog {

SVD::SVD() {
	// TODO Auto-generated constructor stub

}


void SVD::init(){
	//仅仅赋值为1
	//init p
	for(uint i=0; i<USER_NUM; ++i){
		for(uint j=0; j<K; ++j){
			p[i][j] = 0.0;
		}
	}
	//int q
	for(uint i=0; i<ITEM_NUM; ++i){
		for(uint j=0; j<K; ++j){
			p[i][j] = 0.0;
		}
	}
}

void SVD::iter(){

}

float SVD::_value(int i, int j){
	return 1.0;
}

} /* namespace redog */
