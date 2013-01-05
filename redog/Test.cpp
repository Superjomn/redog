/*
 * Test.cpp
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#include "Test.h"

namespace redog {

Test::Test() {
	// TODO Auto-generated constructor stub

}

void Test::setMode(Mode mode, bool compress_trainset){
	switch(mode){
	case NetFlix:
        _changeDir(netflix_dir);
		break;
    case Test:
        _changeDir(test_dir);
        break;
    default:
        cout <<"Error: wrong mode! "<<endl;
        break;
	}
    if (compress_trainset)
    {
        //重新生成trainset的文件
        ts.load();
        ts.tofile();
    }
}

void Test::load(){
    ts.fromfile();
    cout<<".. trainset load OK!"<<endl;
    pl.load();
    cout<<".. probeset load OK!"<<endl;
    qs.load();
    cout<<".. qualiset load OK!"<<endl;
}

void Test::_changeDir(const string &dir)
{
    qualify_data_path = dir + qualify_data_path;
    trainset_dir_path = dir + trainset_dir_path;
    predict_data_path = dir + predict_data_path;
    //python 生成的file列表文件
    trainset_file_pathlist = dir +  trainset_file_pathlist;
    //生成的二进制文件路径
    trainset_datas_path = dir + trainset_datas_path ;
    probeset_file_path = dir + probeset_file_path;
}

void Test::run(){
	cout<<".. begin to run!"<<endl;
	model.iterate();
	cout<<".. end run"<<endl;
}


Test::~Test() {
	// TODO Auto-generated destructor stub
}

} /* namespace redog */
