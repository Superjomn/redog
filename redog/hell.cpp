/*
 * hell.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: chunwei
 */
#include <iostream>
#include <vector>
#include "UserIDTransfer.h"
using namespace std;
using namespace redog;

void testUserIDTransfer(){
	UserIDTransfer it;
    it.show(1);
	vector<int> uids;
	uids.push_back(685);
	uids.push_back(6510);
	for(int i=0; i<uids.size(); ++i){
		int pos = it.f_to_a(uids[i]);
		cout<<"find "<<uids[i]<<"  pos: "<<pos<<endl;
	}
}


int main(){
	cout<<"hello"<<endl;
	testUserIDTransfer();
	return 0;
}




