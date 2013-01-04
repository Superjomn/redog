/*
 * DataLoader.h
 *
 *  Created on: Jan 4, 2013
 *      Author: chunwei
 */

#ifndef DATALOADER_H_
#define DATALOADER_H_

namespace redog {

class DataLoader {
public:
	DataLoader();
	//载入数据
	virtual bool load();
	//从已经压缩的二进制文件中载入数据
	virtual bool fromfile();
	//输出压缩的二进制文件
	virtual bool tofile();
	virtual ~DataLoader();
};

} /* namespace redog */
#endif /* DATALOADER_H_ */
