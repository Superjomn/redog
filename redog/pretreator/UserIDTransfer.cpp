/*
 * UserIDTransfer.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: chunwei
 */

#include "UserIDTransfer.h"

namespace redog {

UserIDTransfer::UserIDTransfer(char* path) {
	// TODO Auto-generated constructor stub
	ifstream file(path);
	string svalue;
	char strtem[256];
	if (!file.is_open()) {
		cout<<"Error: file can't be opened!"<<endl;
		return;
	}
	for(int i=0; file.getline(strtem, 256); ++i){
		//parse to int
		svalue = string(strtem);
		this->fid[i] = atoi(strtem);
	}
	cout<<".. succeed load userid dic!"<<endl;
	file.close();
}

int UserIDTransfer::a_to_f(int id){
	assert(id>-1 && id <= USER_NUM);
	return this->fid[id];
}

int UserIDTransfer::f_to_a(int id){
	int* fpos = lower_bound(this->fid, this->fid+USER_NUM, id);
	int pos = fpos - this->fid;
	assert(pos != USER_NUM);
	return pos;
}

void UserIDTransfer::show(int mod){
    cout<<".. show first 20 records"<<endl;
    switch(mod){
        case 0:
        for(int i=0; i<20; ++i){
            cout<<this->fid[i]<<endl;
        }
        break;
        case 1:
        for(int i=0; i<USER_NUM; ++i){
            if (i % 1000 == 0)
            {
                cout<<i<<" -> "<<this->fid[i]<<endl;
            }
        }
        break;
    }
    cout<<".. end show"<<endl;
}

bool UserIDTransfer::_compare(int i, int j){
	return i<j;
}

UserIDTransfer::~UserIDTransfer() {
	// TODO Auto-generated destructor stub

}

} /* namespace redog */
