set(CDIR ${CMAKE_CURRENT_SOURCE_DIR}/elementFormulations)


set(SOURCEFILES ${SOURCEFILES}
	         ${CMAKE_CURRENT_SOURCE_DIR}/GenericElementFormulation.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation201.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/FiniteRotation2DTimoshenko.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation2DGreenBeam.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LSFEMBernoulli.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS}
	          ${CMAKE_CURRENT_SOURCE_DIR}/GenericElementFormulation.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation201.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteRotation2DTimoshenko.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation2DGreenBeam.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/LSFEMBernoulli.h
					  PARENT_SCOPE)
