

#include <include/MainProgramBase.h>
#include <include/MainProgram.h>

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>

//#include <boost/math/bindings/detail/>

int main()
{
	FEMProject::MainProgramBase *prog;

	std::cout << "Choose precision: " << std::endl
		<< "1: float" << std::endl
		<< "2: double" << std::endl
		<< "3: 32 Stellen" << std::endl
		<< "4: 64 Stellen" << std::endl
		<< "5: 128 Stellen" << std::endl << "Input: ";

	int i;
	std::cin >> i;

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
