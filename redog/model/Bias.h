/*
 * Bias.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef BIAS_H_
#define BIAS_H_
#include "../common.h"

namespace redog {

class Bias {
public:
	Bias();
	void init();
	//初始化商品被打分数目
	//初始化用户打分数目
	void _initBiBuNum();
	void iter();
	virtual ~Bias();
};

} /* namespace redog */
#endif /* BIAS_H_ */
