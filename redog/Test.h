/*
 * Test.h
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#ifndef TEST_H_
#define TEST_H_
#include "common.h"
#include "pretreator/TrainSetLoader.h"
#include "pretreator/ProbeLoader.h"
#include "pretreator/QualiSetLoader.h"
namespace redog {

class Test {
    Test();
	void setMode(Mode mode);
	void load();
	void run();
    ~Test();
};

} /* namespace redog */
#endif /* TEST_H_ */
