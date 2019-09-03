/*
 * Solutionstate.h
 *
 *  Created on: 08.08.2016
 *      Author: klari
 */

#pragma once

#include <forwarddeclaration.h>

#include <solver/GenericSolutionState.h>

#include <vector>

namespace FEMProject {
  
  template <typename prec, typename uint>
  class PointerCollection;
  
  template<typename prec, typename uint>
  class StaticSolutionState : public GenericSolutionState<prec,uint> {
  public:
    StaticSolutionState(PointerCollection<prec, uint> *pointers, std::map<std::string, prec> &parameter);
    ~StaticSolutionState();
    void setInitialValues(const uint &numberOfEquations, const uint &numberOfActiveEquations);
    
    void setTripletList(std::vector<DegreeOfFreedom<prec,uint>*> &Dofs);
    void setSparseMatrix();
    void insertStiffnessResidual(Eigen::Matrix<prec, Eigen::Dynamic, Eigen::Dynamic> &stiffness
    , Eigen::Matrix<prec, Eigen::Dynamic, 1> &residual
    , std::vector<DegreeOfFreedom<prec, uint>*> &Dofs);
    
    void computeLoads(PointerCollection<prec, uint> &pointers);
    virtual void assembleSystem();
    
    void factorize();
    void solve();
    prec residual() {prec residual = sqrt(this->Rhs.dot(this->Rhs)); return residual;};
    void setEquationZero();
    void updateSolution();
    void computeEigenValues(
      uint number,
      uint addNumber = 0,
      bool max = false,
      prec tol = 1e-10,
      prec shift = 1e-10);
    
    prec getSolution(const uint &globalId);
    virtual Eigen::Matrix<prec, Eigen::Dynamic, 1> getSolution(
      std::vector<DegreeOfFreedom<prec, uint>*> Dofs);
    
    void resetSolution();
    
    void printSpMat();
    
    void computeConditionNumber();
  private:
    
    Eigen::Matrix<prec, Eigen::Dynamic, 1> Solution, IncSolution, dIncSolution;
    
    //		Eigen::SparseLU<Eigen::SparseMatrix<prec, 0, uint>, Eigen::COLAMDOrdering<uint> > solver;
    
    
    
    Eigen::Matrix<prec, Eigen::Dynamic, 1> Rhs;
    Eigen::Matrix<prec, Eigen::Dynamic, 1> eqSol;
    std::vector<Eigen::Triplet<prec,uint>> tripletList;
    Eigen::SparseMatrix<prec, 0, uint> SpMat;
  };
} /* namespace FEMProject */
