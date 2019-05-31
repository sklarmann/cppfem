/*
 * HandlingStructs.h
 *
 *  Created on: 24.08.2016
 *      Author: Klarmann
 */

#pragma once

#include <preprocessDefine.h>

#include<control/OutputHandler.h>
#include <map>

instantiateHeader(FEMProgram)

namespace FEMProject {

	/**
	* @brief Contains informational datas.
	* @param ifile Input file for reading.
	* @param ofile Output file for reading
	* @param fileNames Map which contains data about the files.
	*/
	enum class FileHandling {infile, outfile, directory};

	struct InfoData {
		std::map<FileHandling, std::string> fileNames;
		OutputHandler Log;
		bool runProg;
		

	};


} /*End of namespace*/

