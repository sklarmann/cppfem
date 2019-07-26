


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/CommandHistory.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ComputeEigenValues.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ComputeConditionNumber.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Do.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/OpenFiles.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Output.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/OutputPrecision.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/printInfo.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintPropFunction.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintSolution.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintSpMat.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Processfiles.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/PropFunction.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/PropNames.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ReInput.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ResetSolution.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/RunFile.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetDt.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetUpSparseMatrix.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Solution.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Solver.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Tangent.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Threads.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/TimeIncr.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ValueToUserVar.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/UserVarToFile.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/CommandHistory.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/CommandTemplate.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ComputeEigenValues.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ComputeConditionNumber.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Do.h
			         ${CMAKE_CURRENT_SOURCE_DIR}/macroCommandInclude.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/OpenFiles.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Output.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/OutputPrecision.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/printInfo.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintPropFunction.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintSolution.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/PrintSpMat.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Processfiles.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/PropFunction.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/PropNames.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ReInput.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ResetSolution.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/RunFile.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetDt.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetUpSparseMatrix.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Solution.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Solver.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Tangent.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Threads.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/TimeIncr.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ValueToUserVar.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/UserVarToFile.h
					 PARENT_SCOPE)
