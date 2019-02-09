/*
 * HandlingStructs.h
 *
 *  Created on: 24.08.2016
 *      Author: Klarmann
 */

#ifndef HANDLINGSTRUCTS_HPP_
#define HANDLINGSTRUCTS_HPP_

#include<control/OutputHandler.h>
#include <map>

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



#endif /* HANDLINGSTRUCTS_HPP_ */
