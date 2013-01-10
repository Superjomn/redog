/*
 * Model.cpp
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#include "Model.h"

namespace redog {

Model::Model() {
    cout<<"begin model .."<<endl;
	preRMSE = 100000;
	curRMSE = 0.0;
	step = 0;
	//setValue<float>(puTemp, USER_NUM, K, 0.0);
	//init characters
	bias.init();
	implicit.init();
	svd.init();
    for(int u=0; u<USER_NUM; ++u)
    {
        for(int k=0; k<K; ++k)
        {
            p[u][k] = 0.5;
        }
    }

    for(int i=0; i<ITEM_NUM; ++i)
    {
        for(int k=0; k<K; ++k)
        {
            q[i][k] = 0.5;
            y[i][k] = 0.5;
        }
    }
    cout<<"model init OK!"<<endl;
}

void Model::iterate(){
	//init 需要train_set probe_set qualifying_set 的数据
	//均载入
    cout<<"begin iterate .."<<endl;
	initMean();
	initNuNum();
	//初始第一次升级各个参数
	//update();
	for (uint step=0; step<MAX_STEP; ++step)
	{
        //if(goodEnough()){
        if(step == MAX_STEP){
            cout<<" .. succeed end"<<endl;
            //将上次最佳状态的数据写入文件
            //qualisToFile();
        }else{
            cout<<"------------------------------"<<endl;
            cout<<".. iterate step: "<<step<<endl;
            update();
        }
	}
}

void showStatus(string status, uint userNum, int step){
    if(userNum % 5000 == 0){
        cout<<status<<" "<<userNum<<"  step:"<<step<<endl;
        float status = userNum / USER_NUM;
        cout<<"   status: "<<status<<endl;
    }
}

void Model::update(){
    //just one step
    cout<<"updating .."<<endl;
	initPuTemp();
	double rmse = 0.0;
	unsigned long record_num = 0;
    cout<<"update, step: "<<step<<endl;
	for(uint u=0; u<USER_NUM; ++u){
		float sumQE[K] = {0.0};
		uint isize = rateMatrix[u].size();
        //console
        //showStatus("cal and update", u, step); 
        
        //console
		for(uint i=0; i<isize; ++i){
			++record_num;
			//update every parameter
			uint itemI = rateMatrix[u][i].itemid;
			float pui = predictRate(u, itemI, K);
			float eui = rateMatrix[u][i].score - pui;
            //cout<<"pui\teui"<<endl;
            //cout<<pui<<"\t"<<eui<<endl;

            assert(!isnan(pui) && !isnan(eui));
			rmse += eui * eui;
            //cout<<"rmse: "<<rmse<<endl;
            assert(!isnan(rmse));
			//update bu bi
			bu[u] += alpha1 * (eui - beta1 * bu[u]);
            assert(!isnan(bu[u]));
			bi[itemI] += alpha1 * (eui - beta1 * bi[itemI-1]);
            assert(!isnan(bi[itemI]));
			//update p q
			for(uint k=0; k<K; ++k){
				p[u][k] += alpha2 * (eui * q[itemI][k] - beta2 * p[u][k]);
                assert(!isnan(p[u][k]) && p[u][k] != 0);
				q[itemI][k] += alpha2 * (eui * puTemp[u][k] - beta2 * q[itemI-1][k]);
                assert(!isnan(q[itemI][k]) && q[itemI][k] != 0);
				sumQE[k] += eui * q[itemI][k];
                assert(!isnan(sumQE[k]) && sumQE[k] != 0.0);
			}
		}// end item iter
		//update implicit parameter y
		for(uint j=0; j < nuNum[u]; ++j){
			int itemJ = rateMatrix[u][j].itemid;
			for(uint k=0; k<K; ++k){
                float test = nuNum[u] * sumQE[k] - beta2*y[itemJ-1][k];
                /*
                 * nuNum sumQE = 0
                 */
                assert(!isnan(test) && test != 0.0);
				y[itemJ][k] += alpha2 * (sqrt(nuNum[u] * sumQE[k] - beta2*y[itemJ-1][k]));
                assert(!isnan(y[itemJ][k]));
			}
		}// end update y
		//计算Qualis 一直保存上一个状态
		//最终可以写入文件
	}//end user iter
    //calQualis();
    //update rmse
    assert(record_num != 0);
    curRMSE = sqrt(rmse / record_num);
    assert(!isnan(curRMSE));
    //curRMSE = RMSEProbe();
    cout<<"curRMSE: "<<rmse<< " " <<curRMSE<<endl;
}//end update


void Model::initMean(){
    cout<<"init mean .."<<endl;
	unsigned long num = 0;
	unsigned long sum = 0;
	for(uint i=0; i<USER_NUM; ++i){
		for(uint j=0; j<rateMatrix[i].size(); ++j){
			++num;
			sum += rateMatrix[i][j].score;
		}
	}
	mean = sum/num;
	cout<<".. mean: "<<mean<<endl;
}


//仅仅是测试精度
float Model::RMSEProbe(){
	uint size = probes.size();
	float rmse = 0.0;
	float prate = 0.0;
	float err = 0.0;
	for(uint i=0; i<size; ++i){
		//此处文件中的userid 需要进行转化
		prate = predictRate(probes[i].userid, probes[i].itemid, K);
		//!!! probe的score需要提前初始化
		err = prate - probes[i].score;
		rmse += err*err;
	}
	rmse = sqrt(rmse / size);
	cout<<"RMSE:"<<rmse<<" probeNum:"<<size<<endl;
	return rmse;
}

void Model::calQualis(){
    cout<<"cal qualis .."<<endl;
	uint size = qualis.size();
    //对每个记录遍历
	for(uint i=0; i<size; ++i){
		//此处文件中的userid 需要进行转化
		qualis[i].score = predictRate(qualis[i].userid, qualis[i].itemid, K);
	}
    cout<<"end qualis .."<<endl;
}

float Model::predictRate(int user, int item, int dim)
{
    int RuNum = rateMatrix[user].size(); //the num of items rated by user
    double ret;
    if(RuNum >= 1) {
        ret = mean + bu[user] + bi[item] +  dot(puTemp[user], q[item], dim);
    }
    else ret  = mean + bu[user] + bi[item];
    if(ret < 1.0) ret = 1.0;
    if(ret > 5.0) ret = 5.0;
    return ret;
}


void Model::initPuTemp(){
    cout<<"initPuTemp .."<<endl;
    float sqrtRuNum = 0.0;

	for(uint u=0; u<USER_NUM; ++u){
        //console
        //showStatus("init puTemp", u, step); 
        int ruNum = rateMatrix[u].size();
        if (ruNum>1) sqrtRuNum = 1.0/sqrt(ruNum);
        assert(sqrtRuNum >= 0.0);
		for(uint k=0; k<K; ++k){
            float sumy = 0.0;
			for(uint i=0; i<ruNum; ++i){
				int itemI = rateMatrix[u][i].itemid;
                if(y[itemI][k] == 0) y[itemI][k] = 0.5;
                assert(1<=itemI && 17770>= itemI);
                assert(y[itemI][k] != 0 && !isnan(y[itemI][k]));
				sumy += y[itemI][k];
			}
			puTemp[u][k] = p[u][k] + sqrtRuNum * sumy;
            assert(puTemp[u][k] != 0);
		}
	}
    cout<<"end initPuTemp .."<<endl;
}

void Model::initNuNum(){
	//init nuNum
    cout<<"initNuNum .. "<<endl;
	for(uint i=0; i<USER_NUM; ++i){
		nuNum[i] = 0;
	}
	//first from qualis
	for(uint i=0; i<qualis.size(); ++i){
		++nuNum[qualis[i].userid];
	}
	//from rateMatrix
	for(uint i=0; i<USER_NUM; ++i){
		nuNum[i] += rateMatrix[i].size();
	}
    cout<<"end initNuNum .. "<<endl;
}


bool Model::goodEnough(){
	if(curRMSE >= preRMSE && step >= 3){
		return false;
	}
	else{
		preRMSE = curRMSE;
		// maybe should slow the study rate
		cout<<"RMSE:   from "<<preRMSE<<" to "<<curRMSE<<endl;
		return true;
	}
}

bool Model::qualisToFile()
{
    cout<<".. predict data to "<<predict_data_path<<endl;
	ofstream file;
    file.open(predict_data_path.c_str());
	if(! file.is_open()){cout<<".. can't open predict file: "<<predict_data_path<<endl; return false;}
    //write data to file
    uint curItem = -1;
    QualiRecord *cur;
    for(uint i=0; i<qualis.size(); ++i)
    {
        cur = &qualis[i];
        assert(0<cur->score && cur->score <= 5.0);
        if(cur->itemid != curItem)
        {
            file<<cur->itemid<<":"<<endl;
            curItem = cur->itemid;
        }
        file<<cur->score<<endl;
    }
    //end write
    file.close();
    cout<<".. end predict"<<endl;
    cout<<".. program halt!"<<endl;
    return true;
}


} /* namespace redog */
