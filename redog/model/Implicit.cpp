/*
 * Implicit.cpp
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#include "Implicit.h"

namespace redog {

Implicit::Implicit() {
	// TODO Auto-generated constructor stub

}

void Implicit::init(){
	for(uint i=0; i<ITEM_NUM; ++i){
		for(uint j=0; j<K; ++j){
			Common::y[i][j] = 0.0;
		}
	}
}

void Implicit::iter(){

}

} /* namespace redog */
