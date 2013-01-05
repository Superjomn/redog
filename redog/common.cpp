/*
 * common.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "common.h"

namespace redog{
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
