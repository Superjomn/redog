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
	float puTemp[USER_NUM][K];
	float preRMSE;
	float curRMSE;
	uint nuNum[USER_NUM];
	uint step;
	//parameters
	Bias bias;
	Implicit implicit;
	SVD svd;
public:
	Model();
	float RMSEProbe();
	float predictRate(int user, int item, int dim);
	void iterate();
	bool goodEnough();
	//更新各个参数
	void update();
	void initPuTemp();
	//implicit
	void initNuNum();
	//virtual ~Model();
};

} /* namespace redog */
#endif /* MODEL_H_ */
