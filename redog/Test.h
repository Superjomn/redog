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
#include "model/Model.h"

namespace redog {

class Test {
private:
    TrainSetLoader ts;
    ProbeLoader pl;
    QualiSetLoader qs;
    Model model;

public:
	Test();
	void setMode(Mode mode, bool compress_trainset);
	void load();
    //将数据根目录修改 以实现测试目的
    void _changeDir(const string &dir);
	void run();
	virtual ~Test();
};

} /* namespace redog */
#endif /* TEST_H_ */
