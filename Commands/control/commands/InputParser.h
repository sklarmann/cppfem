
#pragma once

#include <forwarddeclaration.h>

#include <map>
#include <queue>
#include <string>

namespace FEMProject {
	namespace Commands {
		enum class macroCmd{
			mesh,plot,math,
			exit,
			output,
			openFiles,
			processfiles,
			reinput,
			solution,
			solver,
			threads,
			history,
			propnames,propfunction,printpropfunction,setdt,timeincr,
			setupsparsematrix,
			tangent, eigenval,
			prininfo
		};
		enum class plotCmd { exit,
			interact,
			mesh, solution
		};

		enum class mathCmd { exit, process, list };

		enum class meshCmd{exit,
			setmaterial,
			block,
			setDegreesOfFreedom,
			inplanebc, inplaneload
		};

		template<typename prec, typename uint>
		class InputParser {
		public:
			InputParser();
			~InputParser() {};
			void parseMacro(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue);
			void parseMesh(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue);
			void parsePlot(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue);
			void parseMath(stringCommandHandler &cmd, std::queue<GenericCommand<prec, uint>*> &cmdQueue);
		private:
			std::map<std::string, macroCmd> macroCommands;
			std::map<std::string, meshCmd> meshCommands;
			std::map<std::string, plotCmd> plotCommands;
			std::map<std::string, mathCmd> mathCommands;

		};
	}
}