/*
 * common.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#include "common.h"

namespace redog{
//paths
string Common::trainset_dir_path = "/home/chunwei/NetFlixData/trainset_datas.red";
string Common::trainset_file_pathlist = "/home/chunwei/NetFlixData/trainset_paths.red";
string Common::trainset_datas_path = "/home/chunwei/NetFlixData/trainset_datas.red";
vector < vector<RateRecord> > Common::rateMatrix;
};//namespace