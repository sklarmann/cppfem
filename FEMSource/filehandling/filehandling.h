/*
 * filehandling.h
 *
 *  Created on: 14.07.2016
 *      Author: simon
 */

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

#ifndef __LINUX_

#include <map>
#include <string>
#include <fstream>
#include <control/HandlingStructs.h>

namespace FEMProject{
	void set_files(std::map<FileHandling, std::string> &fileinformation);
}
#endif

#endif /* FILEHANDLING_H_ */
