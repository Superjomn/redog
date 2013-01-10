/*
 * ProbeLoader.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "ProbeLoader.h"

namespace redog {

ProbeLoader::ProbeLoader() {
}

bool ProbeLoader::load(){
    ifstream file(probeset_file_path.c_str());
	if (!file.is_open()) { cout<<".. can't open probe file! "<<probeset_file_path<<endl; return false;}
    //start to parse 
    this->parse(file); 
    file.close();
    initProbeScores();
	return true;
}

bool ProbeLoader::parse(ifstream &file){
    int itemid;
    //parse content
    char strtem[256];
    while(file.getline(strtem, 256)){
    	string line(strtem);
    	int pos = line.find(":");
    	//find :
    	if(-1 != pos){
    		itemid = atoi(line.substr(0, pos).c_str());
    		assert(itemid != 0);
    		continue;
    	}
    	// parse record line
    	int userid = atoi(line.c_str());
    	// trans file userid to array userid
    	userid = this->uidtranser.f_to_a(userid);
    	// create new record and push
    	ProbeRecord r;
        //attention!!!!!!!
    	r = {itemid, userid, 0};
    	this->datas.push_back(r);
    }
    return true;
}

void ProbeLoader::initProbeScores(){
	cout<<"init Probes Scores"<<endl;
	ProbeRecord *cur;
	RateRecord *currate;
	for(uint i=0; i<probes.size(); ++i){
		cur = &probes[i];
		//find this item
		//已经根据itemid排序 最好是直接搜索得到！！！
		for(uint j=0; j<rateMatrix[cur->userid].size(); ++j){
			currate = &rateMatrix[cur->userid][j];
			if(currate->itemid == cur->itemid){
				cur->score = currate->score;
				break;
			}
		}
		assert(cur->score != 0);

	}
}

void ProbeLoader::show(){
    cout<<"show the data:"<<endl;
    for(unsigned int i=0; i<this->datas.size(); ++i)
    {
        cout<<"data: "<<i<<" :"<<this->datas[i].userid<<" -> "<<this->datas[i].itemid<<endl;
    }
    cout<<"show over"<<endl;
}


} /* namespace redog */
