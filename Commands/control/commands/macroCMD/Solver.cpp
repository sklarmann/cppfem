
#include <preprocessDefine.h>

#include <control/commands/macroCMD/Solver.h>

#include <pointercollection/pointercollection.h>
#include <control/stringCommandHandler.h>

#include <solver/GenericSolutionState.h>
#include <solver/SolverTypes.h>



namespace FEMProject {
	namespace Commands {
		namespace Macro {

			template<typename prec, typename uint>
			Solver<prec, uint>::Solver(stringCommandHandler &cmd) {
				this->solver = cmd.getStringTillDelim();
			}

			template<typename prec, typename uint>
			std::string Solver<prec, uint>::printCommand() {
				std::string ret;
				ret = "solver(" + this->solver + ")";
				return ret;
			}

			template<typename prec, typename uint>
			void Solver<prec, uint>::help()
			{
				std::cout << "The solver command specifies the solver used for the factorization of the tangential stiffness matrix." << std::endl;
				std::cout << std::endl;
				std::cout << "Currently the following solvers can be set with the command:" << std::endl;
				std::cout << std::endl;
				std::cout << "solver(eigenpardisoldlt):    If linked against the MKL library, activates the Pardiso LDLT solver!" << std::endl;
				std::cout << "solver(eigenpardisollt):     If linked against the MKL library, activates the Pardiso LLT solver!" << std::endl;
				std::cout << "solver(eigenpardisolu):      If linked against the MKL library, activates the Pardiso LU solver!" << std::endl;
				std::cout << "solver(eigensimplicialldlt): Activates Eigen Librarys own LDLT solver!" << std::endl;
				std::cout << "solver(eigensimplicialllt):  Activates Eigen Librarys own LLT solver!" << std::endl;
				std::cout << "solver(eigensparselu):       Activates Eigen Librarys own LU solver!" << std::endl;
				std::cout << "solver(eigensparseqr):       Activates Eigen Librarys own QR solver!" << std::endl;
				std::cout << std::endl;
				std::cout << "If you are performing an analysis with arbitrary precision, only the solvers from the Eigen Library can be used!" << std::endl;

			}

			template<typename prec, typename uint>
			void Solver<prec, uint>::run(PointerCollection<prec, uint> &pointers, FEMProgram<prec, uint> *program) {
				SolverTypes type;
				if (this->solver.compare("eigenpardisoldlt")==0) {
					type = SolverTypes::EigenPardisoLDLT;
				}
				else if (this->solver.compare("eigenpardisollt")==0) {
					type = SolverTypes::EigenPardisoLLT;
				}
				else if (this->solver.compare("eigenpardisolu")==0) {
					type = SolverTypes::EigenPardisoLU;
				}
				else if (this->solver.compare("eigensimplicialldlt")==0) {
					type = SolverTypes::EigenSimplicialLDLT;
				}
				else if (this->solver.compare("eigensimplicialllt")==0) {
					type = SolverTypes::EigenSimplicialLLT;
				}
				else if (this->solver.compare("eigensparselu")==0) {
					type = SolverTypes::EigenSparseLU;
				}
				else if (this->solver.compare("eigensparseqr") == 0) {
					type = SolverTypes::EigenSparseQR;
				}

				pointers.getSolutionState()->setSolver(type);

			}

#undef NAME
		}
	}
}

instantiate(Commands::Macro::Solver)