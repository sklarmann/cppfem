
#include <preprocessDefine.h>

#include <control/commands/macroCMD/UserVarToFile.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <math/Userconstants.h>
#include <control/HandlingStructs.h>

#include <iostream>
#include <fstream>
#include <iomanip>

namespace FEMProject {
    namespace Commands {
        namespace Macro {
            
            template<typename prec, typename uint>
            UserVarToFile<prec, uint>::UserVarToFile(stringCommandHandler &cmd) {
                this->varName = cmd.getRhs("var");
                this->fileName = cmd.getRhs("file");
                this->newFile = cmd.getRhs("new");
                this->all = cmd.getRhs("all");
                
            }
            
            template<typename prec, typename uint>
            std::string UserVarToFile<prec, uint>::printCommand() {
                std::string ret;
                return ret;
            }
            
            template<typename prec, typename uint>
            void UserVarToFile<prec, uint>::help()
            {
                std::cout << "\nWrites a userconstant to a specific file, the value is appended to the file content.\n\n" <<
                "Command: vartofile(var=varname;file=filename;)\n\n" <<
                "var: varname is the variable name equal to the specific user constant in math mode\n" <<
                "file: filename is the name of the file in the folder of the input file to write to\n\n" <<
                "If \nvartofile(file=filename;)\nis called, the contents of the file are deleted!\n" <<
                std::endl;
            }
            
            template<typename prec, typename uint>
            void UserVarToFile<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
                InfoData *out = pointers.getInfoData();
                if(!this->all.empty()){
                    std::string fName;
                    fName = out->fileNames[FileHandling::directory] + "UserConstants.log";
                    pointers.getUserConstants()->allToFile(fName);
                }
                else {
                    if (!this->fileName.empty()) {
                        std::ofstream myFile;
                        std::string fName;
                        fName = out->fileNames[FileHandling::directory] + this->fileName;
                        if (this->varName.empty()) {
                            myFile.open(fName, std::ofstream::out | std::ofstream::trunc);
                        }
                        else {
                            prec value = pointers.getUserConstants()->process(this->varName);
                            
                            myFile.open(fName, std::ofstream::out | std::ofstream::app);
                            myFile << std::setprecision(out->Log.getNumberPrecision()) << value << std::endl;
                        }
                        myFile.close();
                    }
                    else {
                        out->Log(LogLevel::NoLog, LogLevel::FullLog) << "In command vartofile no output file name was specified!" << std::endl;
                    }
                }
                
                
                
                
            }
        }
    }
}

instantiate(Commands::Macro::UserVarToFile)
