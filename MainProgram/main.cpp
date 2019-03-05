

#include <include/MainProgramBase.h>
#include <include/MainProgram.h>

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>
//#include <boost/math/bindings/detail/>

int main()
{
	FEMProject::MainProgramBase *prog;

	prog = new FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_100, int>;
	//prog = new FEMProject::MainProgram<double, int>;
	
	prog->run();
	
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