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
private:
	float *bu, *bi;
	unsigned int *buNum, *biNum;
public:
	Bias();
	void init();
	void iter();
	virtual ~Bias();
};

} /* namespace redog */
#endif /* BIAS_H_ */
