/*
 * SVD.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef SVD_H_
#define SVD_H_

#include "Character.h"
#include "../common.h"

namespace redog {

class SVD {
public:
	SVD();
	void init();
	void iter();
	float _value(int i, int j);
};

} /* namespace redog */
#endif /* SVD_H_ */
