


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/EquationHandler.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericNodes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GeometryData.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/NodeSet.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Nodetypes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/DegreeOfFreedom.cpp
					 PARENT_SCOPE)
					 
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/DofStatus.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/EquationHandler.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericNodes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GeometryData.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/NodeSet.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Nodetypes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/DegreeOfFreedom.h
					 PARENT_SCOPE)
