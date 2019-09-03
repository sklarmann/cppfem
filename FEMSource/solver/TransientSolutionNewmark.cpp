#include <preprocessDefine.h>
#include <solver/TransientSolutionNewmark.h>
#include <solver/GenericSolver.h>

#include <pointercollection/pointercollection.h>

#include <equations/DofStatus.h>
#include <equations/DegreeOfFreedom.h>
#include <equations/EquationHandler.h>

#include <loads/LoadList.h>
#include <loads/PropfunctionHandler.h>


#include <finiteElements/ElementList.h>


#include <math/Userconstants.h>
namespace FEMProject {
  
  template<typename prec, typename uint>
  TransientSolutionNewmark<prec, uint>::TransientSolutionNewmark(PointerCollection<prec, uint> *pointers, std::map<std::string, prec> &parameter) : GenericSolutionState<prec, uint>(pointers, parameter) {
    
    typename std::map<std::string, prec>::iterator it;
    it = parameter.find("beta");
    it != parameter.end() ?
    this->beta = it->second :
    this->beta = (prec)1 / (prec)4;
    it = parameter.find("gamma");
    it != parameter.end() ?
    this->gamma = it->second :
    this->gamma = (prec)1 / (prec)2;
  }
  
  template<typename prec, typename uint>
  TransientSolutionNewmark<prec, uint>::~TransientSolutionNewmark() {
    
  }
  
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::setValues(std::map<std::string, prec> &values) {
    typename std::map<std::string, prec>::iterator it;
    it = values.find("beta");
    it != values.end() ?
    this->beta = it->second :
    this->beta = (prec)1 / (prec)4;
    it = values.find("gamma");
    it != values.end() ?
    this->gamma = it->second :
    this->gamma = (prec)1 / (prec)2;
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::setInitialValues(const uint & numberOfEquations, const uint & numberOfActiveEquations)
  {
    this->numberOfEquations = numberOfEquations;
    this->NumberOfActiveEquations = numberOfActiveEquations;
    this->Solution.resize(numberOfEquations);
    this->IncSolution.resize(numberOfEquations);
    this->dIncSolution.resize(numberOfEquations);
    this->vn.resize(numberOfEquations);
    this->vn1.resize(numberOfEquations);
    this->an.resize(numberOfEquations);
    this->an1.resize(numberOfEquations);
    
    this->SpMat.resize(this->NumberOfActiveEquations, this->NumberOfActiveEquations);
    this->Stiffness.resize(this->NumberOfActiveEquations, this->NumberOfActiveEquations);
    this->Mass.resize(this->NumberOfActiveEquations, this->NumberOfActiveEquations);
    this->Damping.resize(this->NumberOfActiveEquations, this->NumberOfActiveEquations);
    
    this->tripletList.reserve(numberOfActiveEquations);
    this->Rhs.resize(numberOfActiveEquations);
    this->eqSol.resize(numberOfActiveEquations);
    
    this->Solution.setZero();
    this->vn.setZero();
    this->vn1.setZero();
    this->an.setZero();
    this->an1.setZero();
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::setTripletList(std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
  {
    Eigen::Triplet<prec> test;
    test = Eigen::Triplet<prec>(1, 1, 0.0);
    for (auto i = 0; i < Dofs.size(); ++i) {
      if (Dofs[i]->getStatus() != dofStatus::inactive) {
        for (auto j = 0; j < Dofs.size(); ++j) {
          if (Dofs[j]->getStatus() != dofStatus::inactive) {
            if (this->symmetricSolver) {
              if (this->upper) {
                if (Dofs[i]->getEqId() <= Dofs[j]->getEqId()) this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
              }
              else {
                if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
              }
            }
            else {
              this->tripletList.push_back(Eigen::Triplet<prec, uint>(Dofs[i]->getEqId(), Dofs[j]->getEqId(), 0.0));
            }
          }
        }
      }
    }
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::setSparseMatrix()
  {
    this->SpMat.setFromTriplets(this->tripletList.begin(), this->tripletList.end());
    this->tripletList.clear();
    this->Mass = this->SpMat;
    this->Stiffness = this->SpMat;
    this->Damping = this->SpMat;
    this->solver->analyze(this->SpMat);
    std::cout << "Transient Algorthm: Newmark\n" << "Number of Equations: " << this->NumberOfActiveEquations << "\n" <<
    "Total number of degrees of Freedom: " << this->numberOfEquations << "\n" << 
    "Number of non-zero terms: " << this->SpMat.nonZeros() << std::endl;
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, Eigen::Matrix<prec, Eigen::Dynamic, 1>& residual, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
  {
    
    uint vsize = static_cast<uint>(Dofs.size());
    //this->assembleCsrMatrix(this->SpMat, stiffness, Dofs);
    this->modifyLinked(stiffness, residual, Dofs);
    #pragma omp critical
    for (uint i = 0; i < vsize; ++i) {
      if (Dofs[i]->getStatus() != dofStatus::inactive) {
        for (uint j = 0; j < vsize; ++j) {
          if (Dofs[j]->getStatus() != dofStatus::inactive) {
            if (this->symmetricSolver) {
              if (this->upper) {
                if (Dofs[i]->getEqId() <= Dofs[j]->getEqId()) {
                  #pragma omp critical (assembleOne)
                  this->Stiffness.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
                }
              }
              else {
                if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) {
                  #pragma omp critical (assembleTwo)
                  this->Stiffness.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
                }
              }
            }
            else {
              #pragma omp critical (assembleOne)
              this->Stiffness.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
            }
          }
          else {
            this->Rhs(Dofs[i]->getEqId()) -= stiffness(i, j) *this->dIncSolution(Dofs[j]->getId());
          }
        }
        #pragma omp critical (assembleThree)
        this->Rhs(Dofs[i]->getEqId()) -= residual(i);
      }
    }
    //Eigen::SparseMatrix<prec, 0, uint> SpMat
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::computeLoads(PointerCollection<prec, uint>& pointers)
  {
    std::vector<DegreeOfFreedom<prec, uint>> *temp = this->pointers->getEquationHandler()->getDofList();
    std::vector<DegreeOfFreedom<prec, uint>> &Dofs = *temp;
    std::vector<prec> load, loadinc;
    std::vector<uint> ids;
    
    this->pointers->getLoadList()->computeLoads(pointers, ids, load, loadinc);
    for (auto i = 0; i < ids.size(); ++i) {
      if (Dofs[ids[i]].getStatus() != dofStatus::inactive) {
        this->Rhs(Dofs[ids[i]].getEqId()) += load[i];
      }
      else {
        this->dIncSolution(Dofs[ids[i]].getId()) += loadinc[i];
      }
    }
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::assembleSystem()
  {
    uint numberOfElements;
    ElementList<prec, uint> *elemList = this->pointers->getElementList();
    numberOfElements = elemList->getNumberOfElements();
    GenericFiniteElement<prec, uint> *elem;
    this->setEquationZero();
    
    Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> stiffness;
    Eigen::Matrix<prec, Eigen::Dynamic, 1> residual;
    std::vector<DegreeOfFreedom<prec, uint>*> Dofs;
    
    this->computeLoads(*(this->pointers));
    
    //#pragma omp parallel for private(elem,stiffness,residual, Dofs) schedule(dynamic)
    for (uint i = 0; i < numberOfElements; ++i) {
      Dofs.clear();
      elem = elemList->getElement(i);
      elem->GenericSetTangentResidual(stiffness, residual, Dofs);
      this->insertStiffnessResidual(stiffness, residual, Dofs);
      stiffness.setZero(); residual.setZero(); Dofs.clear();
      elem->GenericSetMass(stiffness, residual, Dofs);
      this->insertMassMatrix(stiffness, Dofs);
      //			//		elementLibrary(*elem, ControlOptions::BuildStiffnessResidual);
    }
    //
    prec dt = this->props->getDt(*(this->pointers));
    this->SpMat = (prec)1 / this->beta / dt / dt * this->Mass + this->Stiffness;
    this->compressVector(this->compW,this->an1,true);
    //this->compW *= (prec) 1/beta/dt/dt;
    this->Rhs -= this->Mass*this->compW;
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::setEquationZero()
  {
    this->Stiffness.setZero();
    this->Damping.setZero();
    this->Mass.setZero();
    this->Rhs.setZero();
    this->dIncSolution.setZero();
    
    
  }
  
  template<typename prec, typename uint>
  Eigen::Matrix<prec, Eigen::Dynamic, 1> TransientSolutionNewmark<prec, uint>::getSolution(std::vector<DegreeOfFreedom<prec, uint>*> Dofs)
  {
    Eigen::Matrix<prec, Eigen::Dynamic, 1> RetVec;
    
    uint Size = Dofs.size();
    if (Size > 0) {
      RetVec.resize(Size);
      for (auto i = 0; i < Size; ++i) {
        RetVec(i) = this->Solution(Dofs[i]->getId());
      }
    }
    
    return RetVec;
  }
  
  template<typename prec, typename uint>
  void TransientSolutionNewmark<prec, uint>::insertMassMatrix(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic>& stiffness, std::vector<DegreeOfFreedom<prec, uint>*>& Dofs)
  {
    uint vsize = static_cast<uint>(Dofs.size());
    #pragma omp critical
    for (uint i = 0; i < vsize; ++i) {
      if (Dofs[i]->getStatus() != dofStatus::inactive) {
        for (uint j = 0; j < vsize; ++j) {
          if (Dofs[j]->getStatus() != dofStatus::inactive) {
            if (this->symmetricSolver) {
              if (this->upper) {
                if (Dofs[i]->getEqId() <= Dofs[j]->getEqId()) {
                  #pragma omp critical (MassassembleOne)
                  this->Mass.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
                }
              }
              else {
                if (Dofs[i]->getEqId() >= Dofs[j]->getEqId()) {
                  #pragma omp critical (MassassembleTwo)
                  this->Mass.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
                }
              }
            }
            else {
              #pragma omp critical (MassassembleOne)
              this->Mass.coeffRef(Dofs[i]->getEqId(), Dofs[j]->getEqId()) += stiffness(i, j);
            }
          }
        }
      }
    }
    //Eigen::SparseMatrix<prec, 0, uint> SpMat
  }
  
  template<typename prec, typename uint> 
  void TransientSolutionNewmark<prec, uint>::nextSolutionStep()
  {
    this->props->incrTime(*(this->pointers));
    prec dt = this->props->getDt(*(this->pointers));
    this->an = this->an1;
    this->vn = this->vn1;
    prec one = static_cast<prec>(1);
    prec two = static_cast<prec>(2);
    this->vn1 = (one-this->gamma/this->beta)*this->vn + (one-this->gamma/(prec)2/this->beta) *this->an*dt;
    this->an1 = (one-one/two/this->beta)*this->an - one/this->beta/dt*this->vn;
  }
  
  template<typename prec, typename uint> 
  void TransientSolutionNewmark<prec, uint>::factorize()
  {
    this->solver->factorize(this->SpMat);
  }
  
  template<typename prec, typename uint> 
  void TransientSolutionNewmark<prec, uint>::solve()
  {
    prec residual = this->Rhs.dot(this->Rhs);
    std::cout << "Residual norm: " << sqrt(residual) << std::endl;
    this->solver->solve(this->Rhs, this->eqSol);
    this->props->update();
  }

  template<typename prec, typename uint> 
  void FEMProject::TransientSolutionNewmark<prec, uint>::updateSolution()
  {
    prec dt = this->props->getDt(*(this->pointers));
    this->compressVector(this->eqSol,this->dIncSolution,false);
    this->IncSolution += this->dIncSolution;
    this->Solution += this->dIncSolution;
    this->vn1 += this->gamma/this->beta/dt * this->dIncSolution;
    this->an1 += (prec)1/this->beta/dt/dt*this->dIncSolution;
  }

  template<typename prec, typename uint> 
  prec FEMProject::TransientSolutionNewmark<prec, uint>::residual()
  {
    prec ret;
    ret = this->Rhs.dot(this->Rhs);
    ret = sqrt(ret);
    return ret;
  }
  
  template<typename prec, typename uint> 
  prec TransientSolutionNewmark<prec, uint>::getSolution(const uint& globalId)
  {
    return this->Solution(globalId);
  }


}


instantiate(TransientSolutionNewmark)
