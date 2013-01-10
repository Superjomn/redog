/*
 * Model.h
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "../common.h"
#include "Bias.h"
#include "Implicit.h"
#include "SVD.h"

namespace redog {

class Model {
private:
	//putem = pu + sqrt(Nu) * \sum{y_i)
	float preRMSE;
	float curRMSE;
	uint step;
	//parameters
	Bias bias;
	Implicit implicit;
	SVD svd;

public:
	Model();
    //test complete
    void run();
	float RMSEProbe();
	float predictRate(int user, int item, int dim);
	//main function
	void iterate();
	bool goodEnough();
	//更新各个参数
	void update();
	void initPuTemp();
	//implicit
	void initNuNum();
	void initMean();
	//预测qualis的score 并写入中央公共数据集
	//之后可以写入文件
	float sumNuY(uint u, ushort k);
	void calQualis();
    //将qualis写入文件 最好写一个专门的类
    bool qualisToFile();
	//virtual ~Model();
};

} /* namespace redog */
#endif /* MODEL_H_ */
