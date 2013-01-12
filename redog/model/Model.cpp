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
	//setValue<double>(puTemp, USER_NUM, K, 0.0);
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
            y[i][k] = 1.0;
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
	for (step=0; step<MAX_STEP; ++step)
	{
        if(goodEnough()){
        //if(step == MAX_STEP){
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
        double status = double(userNum) / USER_NUM;
        cout<<"   status: "<<status<<endl;
    }
}


void Model::update(){
    //just one step
    cout<<"updating .."<<endl;
    cout<<"step: "<<step<<endl;
    uint remain = step % 10;
    uint _step = 0;
    //dealed
    uint usernum = 0;
    //通过随机数模拟随机梯度下降法
    //对每一条记录进行更新
    double rmse = 0.0;
    uint record_num = 0;
    RateRecord *curnode;
    for (uint rem = remain; _step<10; rem = (rem+1)%10, ++_step){
    	++ _step;
       // cout<<"rem: "<<rem<<endl;
    //	cout<<"stage: "<<_step<<endl;
    	//分批遍历user
    	for(uint u=0; u<USER_NUM; ++u){
    		if(u % 10 == rem){
               // cout<<"u: "<<u<<endl;
                ++usernum;
                cout<<"usernum >> "<<usernum<<endl;
                if(usernum % 5000 == 0)
                {
                    printf("step:%d  status: %f", step, double(usernum)/USER_NUM);
                }
    			//遍历user's item
    			for(uint i=0; i<rateMatrix[u].size(); ++i){
                   // cout<<"i: "<<i<<endl;
    				curnode = &rateMatrix[u][i];
    				uint itemID = curnode->itemid - 1;
    				double invSqrtNuNum = 1 / sqrt(double(nuNum[u]));
                    assert(!isnan(invSqrtNuNum) && invSqrtNuNum > 0.0);
    				double eui = predictRate(u, itemID, K) - rateMatrix[u][i].score;
    				/* score=0 则为 qualifying 附加在
    				 * 后面的记录， 需要跳过
    				 */
    				if(curnode->score != 0){
                       // cout<<"updating bu bi q p"<<endl;
    					++ record_num;
    					//顺便计算 rmse
    					rmse += eui * eui;
                        //对每个记录进行遍历
                        //update everything
                        //------------------------------
                        //update bu
                        bu[u] += alpha1 * (eui - beta1 * bu[u]);
                        assert(!isnan(bu[u]));
                        //update bi
                        bi[itemID] += alpha1 * (eui - beta1 * bi[itemID]);
                        assert(!isnan(bi[itemID]));
                       // cout<<"update q p"<<endl;
                        for(ushort k=0; k<K; ++k)
                        {
                        //	cout<<"dealing with q:"<<endl;
                            //update qi
                        	double sumnuy = sumNuY(u, k);
                        //	cout<<"eui p[u][k] invSqrtNuNum sumNuY q[itemID][k]"<<endl;
                           // cout<<eui<<" "<<p[u][k]<<" "<<invSqrtNuNum<<" "<<sumnuy<<" "<<q[itemID][k]<<endl;
                            q[itemID][k] += alpha2 * (eui *(p[u][k] + invSqrtNuNum * sumNuY(u, k))) - beta2 * q[itemID][k];
                           // cout<<q[itemID][k]<<endl;
                            //upate pu
                           // cout<<"dealing with p:"<<endl;
                            p[u][k] += alpha2 * (eui * q[itemID][k] - beta2 * p[u][k]);
                           // cout<<p[u][k]<<endl;
                            assert(!isnan(q[itemID][k]) && q[itemID][k] != 1/0.0);
                            if(isnan(q[itemID][k]))
                            {
                                scanf("u\ritemID\rk\rp[u][k]\reui\rq[itemID][k]\n");
                                scanf("%d\r%d\r%s\r%f\r%f\r%f\n",u, itemID, k, p[u][k], eui, q[itemID][k]);
                                exit(1);
                            }
                            assert(!isnan(p[u][k]) && q[itemID][k] != 1/0.0);
                            if(isnan(p[u][k]))
                            {
                                scanf("u\ritemID\rk\rp[u][k]\reui\rq[itemID][k]\n");
                                scanf("%d\r%d\r%s\r%f\r%f\r%f\n",u, itemID, k, p[u][k], eui, q[itemID][k]);
                                exit(1);
                            }
                        }
    				}
    				// for j in N(u)
    				//update y
                   // cout<<"updating y"<<endl;
    				for(ushort k=0; k<K; ++k)
    				{
                       // printf("y itemID k: %f %d %hd\n", y[itemID][k], itemID, k);
                        assert(y[itemID][k] != 0);
                       // printf("itemID\rk\ralpha2\reui\rinvSqrtNuNum\rq[itemID][k]\rbeta2\ry[itemID][k]\n");
                       // printf("%d\r%hd\r%f\r%f\r%f\r%f\r%f\r%f\n", itemID, k, alpha2, eui, invSqrtNuNum, q[itemID][k], beta2, y[itemID][k]);
                        double rest = alpha2 * (eui * invSqrtNuNum * q[itemID][k] - beta2 * y[itemID][k]);
                       // cout<<"rest: "<<rest<<endl;
    					y[itemID][k] =  y[itemID][k] + rest ;
                        assert(y[itemID][k] != 0.0);
                       // printf("y itemID k: %lf %d %hd\n", y[itemID][k], itemID, k);
    				}
    			}//end for item
                //cout<<"end item "<<endl;
    		}//end if u % 10
            //cout<<"end user interation"<<endl;
    	}//end for u
    }//end rem
    rmse /= record_num;
    rmse = sqrt(rmse);
    preRMSE = curRMSE;
    curRMSE = rmse;
    cout<<"step: "<<step<<" RMSE "<<curRMSE<<endl;
}//end update

double Model::sumNuY(uint u, ushort k){
	double sum = 0.0;
	for(uint i=0; i< nuNum[u]; ++i){
		uint itemID = rateMatrix[u][i].itemid - 1;
		sum += y[itemID][k];
	}
	//cout<<"get sum: "<<sum<<endl;
	return sum;
}

void Model::initMean(){
    cout<<"init mean .."<<endl;
	unsigned long num = 0;
	unsigned long sum = 0;
	for(uint i=0; i<USER_NUM; ++i){
		for(uint j=0; j<rateMatrix[i].size(); ++j){
            if(rateMatrix[i][j].score == 0){
                //skip qualifying datas
                continue;
            }
			++num;
			sum += rateMatrix[i][j].score;
		}
	}
	mean = sum/double(num);
	cout<<".. mean: "<<mean<<endl;
}


//仅仅是测试精度
double Model::RMSEProbe(){
	uint size = probes.size();
	double rmse = 0.0;
	double prate = 0.0;
	double err = 0.0;
	for(uint i=0; i<size; ++i){
		//此处文件中的userid 需要进行转化
		prate = predictRate(probes[i].userid, probes[i].itemid-1, K);
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

double Model::predictRate(int u, int itemID, int dim)
{
    assert(0<=itemID && 17770> itemID);
    double invSqrtNuNum = 1 / sqrt(double(nuNum[u]));
    double puTem[K];
    double sumY;
    for(ushort k=0; k<K; ++k){
        sumY = sumNuY(u, k);
    	puTem[k] = invSqrtNuNum * sumY;
    }
    double ret;
    if(nuNum[u] >= 1){
    	ret = mean + bu[u] + bi[itemID] + dot((double *)puTem, (double*)q[itemID], K);
    }
    else ret  = mean + bu[u] + bi[itemID];
    if(ret < 1.0) ret = 1.0;
    if(ret > 5.0) ret = 5.0;
    return ret;
}


void Model::initNuNum(){
	//init nuNum
    cout<<"initNuNum .. "<<endl;
    for(uint u=0; u<USER_NUM; ++u)
    {
    	nuNum[u] = rateMatrix[u].size();
    	assert(nuNum[u]>0);
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
