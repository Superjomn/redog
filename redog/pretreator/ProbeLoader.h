/*
 * ProbeLoader.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef PROBELOADER_H_
#define PROBELOADER_H_

#include "../common.h"

namespace redog {

class ProbeLoader {
public:
	ProbeLoader();
    bool load();
	bool fromfile();
	bool tofile();


};

} /* namespace redog */
#endif /* PROBELOADER_H_ */
