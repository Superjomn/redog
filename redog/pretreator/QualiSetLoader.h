/*
 * QualiSetLoader.h
 *
 *  Created on: Jan 5, 2013
 *      Author: chunwei
 */

#ifndef QUALISETLOADER_H_
#define QUALISETLOADER_H_
#include "../common.h"
#include "UserIDTransfer.h"

namespace redog {

class QualiSetLoader {
private:
    UserIDTransfer uidtranser;
public:
    bool load();
    bool parse(ifstream &file);
    void show();
};

} /* namespace redog */
#endif /* QUALISETLOADER_H_ */
