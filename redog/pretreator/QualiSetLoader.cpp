/*
 * QualiSetLoader.cpp
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#include "QualiSetLoader.h"

namespace redog {

bool QualiSetLoader::load(){
    cout<<"load qualifying data and trans userid .."<<endl;
    //string qualify_data_path = "/home/chunwei/NetFlixData/qualifying.txt";
    ifstream file(qualify_data_path.c_str());
    if (!file.is_open()) { cout<<".. can't open probe file! path:"<<qualify_data_path<<endl; return false;}
    //start to parse 
    this->parse(file); 
    file.close();
    return true;
}

bool QualiSetLoader::parse(ifstream &file){
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
    	QualiRecord r;
        //attention!!!!!!!
    	r = {itemid, userid, 0};
        //add to common dataset
    	qualis.push_back(r);
    }
    return true;
}

void QualiSetLoader::show(){
    cout<<"show the data:"<<endl;
    for(uint i=0; i<qualis.size(); ++i)
    {
        cout<<"data: "<<i<<" :"<<qualis[i].userid<<" -> "<<qualis[i].itemid<<endl;
    }
    cout<<"show over"<<endl;
}


} /* namespace redog */
