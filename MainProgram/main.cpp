

#include <include/MainProgramBase.h>
#include <include/MainProgram.h>


int main()
{
	FEMProject::MainProgramBase *prog;

	prog = new FEMProject::MainProgram<double, int>;
	
	prog->run();
	
	//FEMProject::InfoData infos;
	//FEMProject::PointerCollection<double, int> *pointers;
	//FEMProject::FEMProgram<double, int> *FEMProgram;
	//
	//pointers = new FEMProject::PointerCollection<double, int>;
	//pointers->setInfoData(&infos);
	//FEMProgram = new FEMProject::FEMProgram<double, int>(pointers);
	//FEMProgram->run(pointers);

	
}