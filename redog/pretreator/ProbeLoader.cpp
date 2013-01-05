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
	if (!file.is_open()) { cout<<".. can't open probe file!"<<endl; return false;}
    //start to parse 
    this->parse(file); 

    file.close();
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
    	// create new record and push
    	ProbeRecord r;
        //attention!!!!!!!
    	r = {itemid, userid, 0};
    	this->datas.push_back(r);
    }
    return true;
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
