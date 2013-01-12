#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <map>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <dirent.h>
#include <malloc.h>
#include <errno.h>
#include <time.h>

#define USER_NUM 480189  //10K:943 1M:6040
#define ITEM_NUM 17770 //10K:1682 1M:3900
#define K_NUM  65
#define TRAINING_SET "../dataset/netflix/data_without_prob.txt"
#define QUALI_SET "../dataset/netflix/qualifing_t.txt"
#define PROBE_SET "../dataset/netflix/probe_real.txt"
#define RATE_SP ","  //rate Separator

using namespace std;

struct rateNode
{
    short item;
    short rate;
};

struct testSetNode
{
    int user;
    short item;
    short rate; // char is better
};

/**
 * calculate the mean of all the ratings
 */
float setMeanRating(int userNum, vector< vector<rateNode> > rateMatrixLocal)
{
    //calculate the mean
    double sum = 0;
    int num = 0;
    cout<<"beging mean:"<<endl;
    for(int i = 1; i < userNum+1; ++i){
        for(int j=0; j < rateMatrixLocal[i].size(); ++j) {
            sum += rateMatrixLocal[i][j].rate;
            ++num;
        }
    }
    cout<<"end mean!mean:"<<(sum/num)<<endl;
    return sum/num;
}

double get_rand(int dim)
{
    return 0.1 * (rand()/(double)RAND_MAX) / sqrt(dim);
}

/**
 * set the vector to random values
 */
void setRand(double  p[], int dim, float base)
{
    for(int i=1;i<dim+1;++i){
        //double temp = base+get_rand(dim);
        //p[i] = temp;
        p[i] = 1.0;
    }
}
double RMSEProbe(vector<testSetNode>& probeSet,int dim)
{
    int probeSize = probeSet.size();
    float pRate,err;
    long double rmse = 0;
    
    for(int i = 0; i < probeSize; ++i) {
        pRate = predictRate(probeSet[i].user,probeSet[i].item,dim);      //predict rate
        //cout<<pRate<<"    "<<probeSet[i].rate<<"    "<<probeSet[i].user<<"    "<<probeSet[i].item<<endl;
        err = pRate-probeSet[i].rate;
        rmse += err*err;
    }
    rmse = sqrt( rmse / probeSize);
    cout<<"RMSE:"<<rmse<<" probeNum:"<<probeSize<<endl;
    return rmse;
}

void loadRating(char * fileName, vector< vector<rateNode> >& rateMatrixLocal, const char* separator)
{
    cout<<"load Rating"<<endl;
    char rateStr[256];
    char* pch;    
    vector<string> rateDetail;
    int fileNum = 0;
    std::ifstream from (fileName);
    if (!from.is_open()) {
        cout << "can't open  operation failed!\n";
        exit(1);
    }
    
    int itemId = 0, userId = 0, rate = 0;
    while(from.getline(rateStr,256)){
        string strTemp(rateStr);
        int pos = strTemp.find(":");
        if(-1 != pos) {
            itemId = atoi(strTemp.substr(0,pos).c_str());
            ++fileNum;     
            if(fileNum %3000 ==0) {
                cout<<"read file "<<fileNum<<" sucessfully!"<<endl;
            }
            continue;
        }
        if(strTemp.length() < 3)continue;
        int i = 0;
        pch = strtok (rateStr,separator);
        while (pch != NULL) {
            if(0 == i) userId = atoi(pch);
            else if(1 == i) rate = atoi(pch);
            else if(i > 1) break;
            ++i;
            pch = strtok (NULL,separator);
        }
        //initialization rateMatrix
        try {
            rateNode tmpNode;
            tmpNode.item = itemId;
            tmpNode.rate = (short)rate;
            rateMatrixLocal[userId].push_back(tmpNode);
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            cout << "Can't allocate the momery!" << endl; exit(1);
        }
    }
    from.close();
       cout<<"read file sucessfully!"<<endl;
    return;
}


//load test set of netflix dataset
void loadProbe(char * fileName,vector<testSetNode>& probeSet, const char* separator)
{
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "can't open test set file!\n";
        exit(1);
    }
    char rateStr[256];
    char* pch ; // store a token of a string

    string strTemp;
    int rateValue,itemId,userId,probeNum=0;
    
    while(in.getline(rateStr,256)){
        strTemp = rateStr;
        if(strTemp.length() < 4) continue;
        int i = 0;
        pch = strtok (rateStr,separator);
        while (pch != NULL) {
            if(0 == i) itemId = atoi(pch);
            else if(1 == i) userId = atoi(pch);
            else if(2 == i) rateValue = atoi(pch);
            else if(i > 2) break;
            ++i;
            pch = strtok (NULL,separator);
        }
        try {
            testSetNode tmpNode;
            tmpNode.item = itemId;
            tmpNode.rate = (short)rateValue;
            tmpNode.user = userId;
            probeSet.push_back(tmpNode);
            ++probeNum;
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            cout << "Can't allocate the momery!" << endl; exit(1);
        }
    }
    cout << "Load " << probeNum << " test ratings successfully!"<<endl;
    in.close(); 
}

void loadQualis(char * fileName,vector<testSetNode>& probeSet, const char* separator)
{
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "can't open test set file!\n";
        exit(1);
    }
    char rateStr[256];
    char* pch ; // store a token of a string

    string strTemp;
    int rateValue,itemId,userId,probeNum=0;
    
    while(in.getline(rateStr,256)){
        strTemp = rateStr;
        if(strTemp.length() < 4) continue;
        int i = 0;
        pch = strtok (rateStr,separator);
        while (pch != NULL) {
            if(0 == i) itemId = atoi(pch);
            else if(1 == i) userId = atoi(pch);
            else if(2 == i) rateValue = atoi(pch);
            else if(i > 2) break;
            ++i;
            pch = strtok (NULL,separator);
        }
        try {
            testSetNode tmpNode;
            tmpNode.item = itemId;
            tmpNode.rate = (short)rateValue;
            tmpNode.user = userId;
            probeSet.push_back(tmpNode);
            ++probeNum;
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            cout << "Can't allocate the momery!" << endl; exit(1);
        }
    }
    cout << "Load " << probeNum << " qualis ratings successfully!"<<endl;
    in.close(); 
}


bool outputQualis(string fileName ,vector<testSetNode>& qualis)
{
    cout<<".. predict data to "<<fileName<<endl;
ofstream file;
    file.open(fileName.c_str());
if(! file.is_open()){cout<<".. can't open predict file: "<<fileName<<endl; return false;}
    //write data to file
    unsigned int curItem = -1;
    testSetNode *cur;
    float prate;
    for(uint i=0; i<qualis.size(); ++i)
    {
        cur = &qualis[i];
        prate = predictRate(cur->user, cur->item, 50);
        if(cur->item != curItem)
        {
            file<<cur->item<<":"<<endl;
            curItem = cur->item;
        }
        file<<prate<<endl;
        /*
        if(i%1000 == 0)
        {
            cout<<"predict "<<i<<" -> "<<prate<<endl;
        }
        */
    }
    //end write
    file.close();
    cout<<".. end predict"<<endl;
    cout<<".. program halt!"<<endl;
    return true;     
}


int main()
{
    time_t start,end;
    struct tm* startInfo;
    struct tm* endInfo;
    double duration;
    start = time(NULL);
    startInfo = localtime(&start);
    string startStr = asctime(startInfo);
    float alpha1 = 0.008;    
    float alpha2 = 0.008;   
    float beta1  = 0.01;   
    float beta2  = 0.01;  
    //for(int i=0; i < 10; i++)
    {
        //    beta = i*0.001 + 0.002;
        //    cout << beta << endl;
        svd::model(K_NUM,alpha1,alpha2,beta1,beta2,60,0.9);
    }
    cout<<"succeed end ..."
    return 0;
}
