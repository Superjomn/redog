/*
 * ProbeLoader.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef PROBELOADER_H_
#define PROBELOADER_H_

#include "../common.h"
#include "UserIDTransfer.h"
namespace redog {

class ProbeLoader {
private:
    vector<ProbeRecord> datas;
    UserIDTransfer uidtranser;
public:
	ProbeLoader();
    bool load();
    bool parse(ifstream &file);
    //直接将probe的score从rateMatix中查询写入
    void initProbeScores();
    void show();
	//bool fromfile();
	//bool tofile();
};

} /* namespace redog */
#endif /* PROBELOADER_H_ */
