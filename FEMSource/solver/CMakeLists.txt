


set(SOURCEFILES ${SOURCEFILES}
	         ${CMAKE_CURRENT_SOURCE_DIR}/GenericSolver.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSimplicialLDLT.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSimplicialLLT.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSparseLU.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSparseQR.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLDLT.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLLT.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLU.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SolverTypes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/StaticSolutionState.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericSolutionState.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SolutionTypes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/TransientSolutionNewmark.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/GenericSolver.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSimplicialLDLT.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSimplicialLLT.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSparseLU.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenSparseQR.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLDLT.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLLT.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EigenPardisoLU.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SolverTypes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/StaticSolutionState.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericSolutionState.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SolutionTypes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/TransientSolutionNewmark.h
					 PARENT_SCOPE)
