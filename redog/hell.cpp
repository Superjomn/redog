/*
 * hell.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: chunwei
 */
#include <iostream>
#include <vector>
#include "pretreator/UserIDTransfer.h"
#include "pretreator/TrainSetLoader.h"
#include "pretreator/ProbeLoader.h"
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


void testTrainSetLoader(){
    TrainSetLoader tl;
    //tl.load();
    //tl.show();
    //tl._sort();
    //tl.show();
    //tl.tofile();
    tl.fromfile();
    tl.showRateMatrix();
}

void testProbeLoader()
{
    ProbeLoader pl;
    pl.load();
    pl.show();
}


int main(){

	cout<<"hello"<<endl;
	//testUserIDTransfer();
	//testTrainSetLoader();
    testProbeLoader();
	return 0;
}




