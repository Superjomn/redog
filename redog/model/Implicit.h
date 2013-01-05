/*
 * Implicit.h
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#ifndef IMPLICIT_H_
#define IMPLICIT_H_
#include "../common.h"
namespace redog {

class Implicit {
public:
	Implicit();
	void init();
	void iter();
};

} /* namespace redog */
#endif /* IMPLICIT_H_ */
