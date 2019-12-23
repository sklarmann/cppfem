

#include <include/MainProgramBase.h>
#include <include/MainProgram.h>

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>

//#include <boost/math/bindings/detail/>

int main(int argc, char** argv)
{
	FEMProject::MainProgramBase *prog;
    
    int i;
    if(argc<=1) {
        std::cout << "Choose precision: " << std::endl
            << "1: float" << std::endl
            << "2: double" << std::endl
            << "3: 32 Stellen" << std::endl
            << "4: 64 Stellen" << std::endl
            << "5: 128 Stellen" << std::endl << "Input: ";

        
        std::cin >> i;
    } else {
        std::stringstream a;
        a << argv[1];
        a>>i;
    }

	if (i == 1) {
		prog = new FEMProject::MainProgram<float, int>;
	}
	else if (i == 2) {
		prog = new FEMProject::MainProgram<double, int>;
	}
	else if (i == 3) {
		prog = new FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_32, int>;
	}
	else if (i == 4) {
		prog = new FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_64, int>;
	}
	else if (i == 5) {
		prog = new FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_128, int>;
	}

	//prog = new FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_100, int>;
	//prog = new FEMProject::MainProgram<double, int>;
	//prog = new FEMProject::MainProgram<float, int>;

	if(argc<=2){
        prog->run();
    } else {
        std::string filename(argv[2]);
        std::stringstream cmdarg;
        cmdarg << "open(" << filename << ")";
        std::string pass;
        cmdarg >> pass;
        prog->processExternalMacroCmd(pass);
        pass = "processfiles()";
        prog->processExternalMacroCmd(pass);
        pass = "printinfo()";
        prog->processExternalMacroCmd(pass);
        
        
    }
	
	//std::cout << test << std::endl;


	//FEMProject::InfoData infos;
	//FEMProject::PointerCollection<double, int> *pointers;
	//FEMProject::FEMProgram<double, int> *FEMProgram;
	//
	//pointers = new FEMProject::PointerCollection<double, int>;
	//pointers->setInfoData(&infos);
	//FEMProgram = new FEMProject::FEMProgram<double, int>(pointers);
	//FEMProgram->run(pointers);


}
