

set(SOURCE ${SOURCE}
	 				 ${CMAKE_CURRENT_SOURCE_DIR}/AddVertex.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/AddFiniteElement.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/AddGeometryElement.cpp
	                 ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplanebc.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplaneload.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/singleBC.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/singleLoad.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/linkDofs.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetBoundaryConditions.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetDegreeOfFreedom.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetMaterials.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS}
	          ${CMAKE_CURRENT_SOURCE_DIR}/AddVertex.h
 					  ${CMAKE_CURRENT_SOURCE_DIR}/AddFiniteElement.h
 					  ${CMAKE_CURRENT_SOURCE_DIR}/AddGeometryElement.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/Block.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/CommandTemplate.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/inplanebc.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/inplaneload.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/singleBC.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/singleLoad.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/linkDofs.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/meshCommandInclude.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/SetBoundaryConditions.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/SetDegreeOfFreedom.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/SetMaterials.h
					  PARENT_SCOPE)
