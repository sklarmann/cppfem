


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/ElementList.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ElementTypes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericFiniteElement.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearTriangleElement.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/ElementList.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/ElementTypes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericFiniteElement.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearTriangleElement.h
					 PARENT_SCOPE)
