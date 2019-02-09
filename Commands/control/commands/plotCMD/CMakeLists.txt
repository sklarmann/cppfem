


set(SOURCE ${SOURCE} 
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotInteract.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotmesh.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotSolution.cpp
					 PARENT_SCOPE)


set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/CommandTemplate.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotCommandInclude.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotInteract.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotmesh.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/plotSolution.h
					 PARENT_SCOPE)
