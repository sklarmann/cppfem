/**
 * @page 1mainpage Start of the documentation of the program.
 * @tableofcontents
 * Table of Contents.
 * @section meshcommands Mesh Commands
 * @subsection bla hanswurst
 *
 */

//
///**
// * @file main.cpp
// *
// */
//

//#include <control/HandlingStructs.hpp>
//#include <control/MainProgram.h>
//#include <control/ControlProgram.h>
//#include <boost/multiprecision/cpp_bin_float.hpp>
//#include "mainwindow.h"
//#include <QApplication>
//#include <qt_interface.h>
////#include "qtfirstapp.h"
////#include <QApplication>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include <control/FEMProgram.h>
#include <control/HandlingStructs.h>
#include <pointercollection/pointercollection.h>

int main(int argc, char* argv[])
{
	FEMProject::InfoData infos;
	FEMProject::PointerCollection<double, int> *pointers;
	pointers = new FEMProject::PointerCollection<double, int>;
	pointers->setInfoData(&infos);

	typedef FEMProject::FEMProgram<double, int> FEMProg;
	typedef FEMProject::FEMProgram<float, int> FEMProgFloat;

	//FEMProject::FEMProgram<double, int> *programStart;
	//FEMProject::FEMProgram<boost::multiprecision::cpp_bin_float_100, int> programStart;
	FEMProg *programStart;
	//
	//programStart = new FEMProject::FEMProgram<double, int>(pointers);
	programStart = new FEMProg(pointers);
	programStart->run(pointers);


	//QApplication a(argc, argv);
	//FEMProject::QTInterFace w;
	////w.setUpMenu();
	//w.show();
	//
	//
	//
	//return a.exec();
	//w.hide();
	
	//boost::multiprecision::cpp_bin_float_100 b = 2;
	//FEMProject::PointerCollection<double, int> bla;
	//FEMProject::StaticSolutionState<double, int> testsol(&bla);
	//testsol.computeLoads();


	//FEMProject::InfoData info;
	//info.Log.setLogLevel(FEMProject::BasicLog, FEMProject::NoLog);
	////FEMProject::MainProgram<boost::multiprecision::cpp_bin_float_100, int> program(&info);
	//FEMProject::MainProgram<double, long long> program(&info);
	//
	//bool start = false;
	//if (start) program.run();

	//try {
	//	program.run();
	//}
	//catch (const std::exception &e) {
	//	std::cout << e.what() << std::endl;
	//}
	

//	FEMProject::ControlProgram<float, int> *testprogam;


//	std::cout << sizeof(testprogam) << std::endl;
//
//	testprogam = new FEMProject::ControlProgram<float, int> ;
//
//	std::vector<std::vector<double>> bla;
//
//	FEMProject::Timer<FEMProject::sec> testtimer;
//
//	testtimer.start();
//
//	bla.resize(4);
//	for(auto i=0;i<4;++i){
//		bla[i].resize(3);
//	}
//
//
//
//	try{
//		for(auto i= 0;i<1;++i){
//			bla[0][0]=0;
//			bla[0][1]=0;
//			bla[0][2]=0;
//
//			bla[1][0]=1;
//			bla[1][1]=0;
//			bla[1][2]=0;
//
//
//			bla[2][0]=1;
//			bla[2][1]=1;
//			bla[2][2]=0;
//
//
//			bla[3][0]=0;
//			bla[3][1]=1;
//			bla[3][2]=0;
//			delete testprogam;
//			testprogam = new FEMProject::ControlProgram<double,long int> ;
//			testprogam->blockGeneration(FEMProject::blockTypes::quadlinear
//							  ,FEMProject::Elementtypes::LinearTriangle
//							  ,bla,1000,1000,0,0);
//
//			testprogam->setMaterialProperties();
//			testprogam->setDegreesOfFreedom();
//
//			std::vector<double> normal, point;
//			std::vector<long int> bc;
//			bc.resize(2);
//			bc[0] = 1; bc[1] = 1;
//			
//			
//			normal.resize(3); normal[0] = 1.0; normal[1] = 0.0; normal[2] = 0.0;
//			point.resize(3); point[0] = 0.0; point[1] = 0.0; point[2] = 0.0;
//			//testprogam->setBoundaryConditionsInPlane(normal, point, GeometryTypes::Vertex, bc, 0);
//			testprogam->checkData();
//			testprogam->setUpSparseMatrix();
//			testprogam->setUpStiffnessResidual();
//			testprogam->displayMesh();
//
//			bla[0][0]=1;
//			bla[0][1]=0;
//			bla[0][2]=0;
//
//			bla[1][0]=2;
//			bla[1][1]=0;
//			bla[1][2]=0;
//
//
//			bla[2][0]=2;
//			bla[2][1]=1;
//			bla[2][2]=0;
//
//			bla[3][0]=1;
//			bla[3][1]=1;
//			bla[3][2]=0;
//
//			testprogam->blockGeneration(FEMProject::blockTypes::quadlinear
//							  ,FEMProject::Elementtypes::LinearTriangle
//							  ,bla,2,2,0);
//		}
//	}catch (const std::exception &e) {
//		std::cout << e.what() << std::endl;
//	}
//
//	
//
////	testprogam->displayMesh();
//
//	testtimer.stop();
//
//	std::cout << testtimer << std::endl;
//	testprogam->displayMesh();
//
//	int ijk;
//
//	std::cin >> ijk;


	return 0;
}

//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
////#define vtkRenderingCore_AutoInit 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL2)
////#define vtkRenderingVolume_AutoInit 1(vtkRenderingVolumeOpenGL)
//
//
//#include <vtkVersion.h>
//#include <vtkSmartPointer.h>
//#include <vtkTetra.h>
//#include <vtkCellArray.h>
//#include <vtkXMLUnstructuredGridReader.h>
//#include <vtkDataSetMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkXMLUnstructuredGridWriter.h>
//#include <vtkUnstructuredGrid.h>
//#include <vtkPointData.h>
//#include <vtkVertexGlyphFilter.h>
//#include <vtkDoubleArray.h>
//
//
//
//int main(int argc, char *argv[])
//{
//
//  // Parse command line arguments
//  if(argc != 2)
//    {
//    std::cout << "Required arguments: OutputFilename" << std::endl;
//    return EXIT_FAILURE;
//    }
//
//  std::string filename = argv[1];
//
//  vtkSmartPointer<vtkPoints> points =
//    vtkSmartPointer<vtkPoints>::New();
//  points->InsertNextPoint(0, 0, 0);
//  points->InsertNextPoint(10.1, 0, 0);
//  points->InsertNextPoint(1, 1, 0);
//  points->InsertNextPoint(0, 1, 1);
//
//  vtkSmartPointer<vtkDoubleArray> weights =
//		  vtkSmartPointer<vtkDoubleArray>::New();
//
//  weights->SetNumberOfValues(4);
//  weights->SetValue(0,1.0);
//  weights->SetValue(1,2.0);
//  weights->SetValue(2,3.0);
//  weights->SetValue(3,4.0);
//
//   vtkSmartPointer<vtkTetra> tetra =
//    vtkSmartPointer<vtkTetra>::New();
//
//  tetra->GetPointIds()->SetId(0, 0);
//  tetra->GetPointIds()->SetId(1, 1);
//  tetra->GetPointIds()->SetId(2, 2);
//  tetra->GetPointIds()->SetId(3, 3);
//
//
//
//  vtkSmartPointer<vtkCellArray> cellArray =
//    vtkSmartPointer<vtkCellArray>::New();
//  cellArray->InsertNextCell(tetra);
//
//
//
//
//  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
//    vtkSmartPointer<vtkUnstructuredGrid>::New();
//  unstructuredGrid->SetPoints(points);
//  unstructuredGrid->SetCells(VTK_TETRA, cellArray);
//
//  unstructuredGrid->GetPointData()->SetScalars(weights);
//
//  // Write file
//  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
//    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
//  writer->SetFileName(filename.c_str());
//#if VTK_MAJOR_VERSION <= 5
//  writer->SetInput(unstructuredGrid);
//#else
//  writer->SetInputData(unstructuredGrid);
//#endif
//  writer->Write();
//
//  // Read and display file for verification that it was written correclty
//  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
//    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
//  reader->SetFileName(filename.c_str());
//  reader->Update();
//
//  vtkSmartPointer<vtkDataSetMapper> mapper =
//    vtkSmartPointer<vtkDataSetMapper>::New();
//  mapper->SetInputConnection(reader->GetOutputPort());
//
//  vtkSmartPointer<vtkActor> actor =
//    vtkSmartPointer<vtkActor>::New();
//  actor->SetMapper(mapper);
//
//  vtkSmartPointer<vtkRenderer> renderer =
//    vtkSmartPointer<vtkRenderer>::New();
//  vtkSmartPointer<vtkRenderWindow> renderWindow =
//    vtkSmartPointer<vtkRenderWindow>::New();
//  renderWindow->AddRenderer(renderer);
//  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//    vtkSmartPointer<vtkRenderWindowInteractor>::New();
//  renderWindowInteractor->SetRenderWindow(renderWindow);
//
//
//  std::cout << "test1" << std::endl;
//  renderer->AddActor(actor);
//  renderer->SetBackground(.3, .6, .3); // Background color green
//  std::cout << "test2" << std::endl;
//
//  renderWindow->Render();
//  std::cout << "test3" << std::endl;
//  renderWindowInteractor->Initialize();
//  renderWindowInteractor->Start();
//  std::cout << "test3" << std::endl;
//  std::string a;
//  std::cin >> a;
//  return EXIT_SUCCESS;
//}
//
