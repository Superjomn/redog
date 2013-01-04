/*
 * TrainSetLoader.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "TrainSetLoader.h"

namespace redog {

TrainSetLoader::TrainSetLoader(string listpath) {
	// TODO Auto-generated constructor stub
	this->listpath = listpath;
	this->filenum = 0;
}


bool TrainSetLoader::load() {
    // load path list file
	ifstream trainpaths(Common::trainset_file_pathlist.c_str());
	if (!trainpaths.is_open()) { cout<<".. can't open train paths list file!"<<endl; return false;}
	char strtem[256];
	while(trainpaths.getline(strtem, 256)){
		//get a path, open the path and start to parse
        if(!this->parse(strtem)) return false;
	}
    trainpaths.close();
    return true;
}

bool TrainSetLoader::parse(char *path){
    ifstream file(path);
    int itemid;

	if (!file.is_open()) { cout<<".. can't open "<<path<<endl; return false;}
    //parse content
    char strtem[256];
    while(file.getline(strtem, 256)){
    	string line(strtem);
    	int pos = line.find(":");
    	//find :
    	if(-1 != pos){
    		itemid = atoi(line.substr(0, pos).c_str());
    		assert(itemid != 0);
    		++ this->filenum;
    		if(this->filenum % 2000){cout<<".. parsed "<<this->filenum<<" files!"<<endl;}
    		// to following record lines
    		continue;
    	}
    	// parse record line
    	vector<string> parts;
    	this->_split(line, ',', parts);
    	int userid = atoi(parts[0].c_str());
    	short record = atoi(parts[1].c_str());
    	assert(userid > 0 && userid <= 2649429);
    	// create new record and push
    	TrainRecord r;
    	r = {userid, itemid, record};
    	this->datas.push_back(r);
    }
    file.close();
    return true;

}

bool mycompare(const TrainRecord &a,const TrainRecord &b){
    if (a.userid != b.userid) return a.userid < b.userid;
    else{
        return a.itemid < b.itemid;
    }
}

void TrainSetLoader::_sort(){
	cout<<".. begin sort"<<endl;
	std::sort (this->datas.begin(), this->datas.end(), mycompare);
	//std::sort (this->datas.begin(), this->datas.end(), this->_compare);
	cout<<".. end sort"<<endl;
}

bool TrainSetLoader::tofile(){
	//first sort then write to binary file
	this->_sort();
	const char* path = Common::trainset_datas_path.c_str();
	cout<<".. begin to write data to file : "<<path<<endl;
	ofstream file;
	file.open(path, ios::out|ios::binary);
	if(! file.is_open()){cout<<".. can't open file: "<<path<<endl; return false;}
	if(! this->datas.empty()){
		//需要对地址转化
		file.write((char *)&*this->datas.begin(), this->datas.size()* sizeof(TrainRecord));
	}
	file.close();
	cout<<".. succeed write file"<<endl;
	return true;
}

bool TrainSetLoader::fromfile()
{
	Common::rateMatrix.resize(USER_NUM);
    //open file
    ifstream file(Common::trainset_datas_path.c_str());
    if(!file.is_open()){cout<<"can't open file : "<<Common::trainset_datas_path<<endl; return false;}
    //clear datas
    this->datas.clear();
    //read binary file to datas
    file.seekg(0,ifstream::end);
    long size2 = file.tellg();
    cout<<".. get data size: "<<size2<<endl;
    long size = size2/sizeof(TrainRecord);
    file.seekg(0,ifstream::beg);
    this->darr = new TrainRecord[size];
    file.read((char*)this->darr, size2);
    //init rateMatrix
    /*
    for(int i=0; i<size; ++i){
    	TrainRecord t = this->darr[i];
    	cout<<i<<" :"<<t.userid<<" "<<t.itemid<<endl;
    }
    */
    delete this->darr;
    file.close();
    return true;
}

void TrainSetLoader::_initRateMatrix(){
    vector<RateRecord> temv;
    int a_userid = -1;
    int temuserid = -1;
    for(std::vector<TrainRecord>::iterator iter = this->datas.begin(); iter != this->datas.end(); ++iter)
    {	//first turn
    	if(temuserid == -1 || temuserid != iter->userid){
            //put temv to rateMatrix
            if(!temv.empty()){
            	//赋值到 rateMatrix
            	Common::rateMatrix[a_userid].assign(temv.begin(), temv.end());
            }
    		++a_userid;
    		temv.clear();
    		temuserid = iter->userid;
    	}
        //just add data
        RateRecord r = {iter->itemid, iter->score};
        temv.push_back(r);
    }
}

bool TrainSetLoader::_split(const std::string &s, char delim, vector<string>&elems){
    //vector<string> elems;
	elems.clear();
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    //return elems;
    return true;
}

void TrainSetLoader::show(){
    cout<<"------------------------------------------"<<endl;
    cout<<".. show datas:"<<endl;
    cout<<"------------------------------------------"<<endl;
	cout<<".. datas size: "<<this->datas.size()<<endl;
    for (long i=0; i<this->datas.size(); ++i){
        cout<<i<<" -> "<<this->datas[i].userid<<" : "<<this->datas[i].itemid<<" "<<this->datas[i].score<<endl;
    }
}

/*
bool _compare(const TrainRecord &a, const TrainRecord &b) {
    if (a.userid == b.userid){
    	return a.itemid < b.itemid;
    }
    return a.userid < b.userid;
}
*/


} /* namespace redog */
