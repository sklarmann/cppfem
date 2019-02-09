


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/Edge.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericGeometryElement.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GeometryTypes.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearTriangle.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Vertex.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearBrick.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearQuadrilateral.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/Edge.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericGeometryElement.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GeometryTypes.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearTriangle.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Vertex.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearBrick.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LinearQuadrilateral.h
					 PARENT_SCOPE)
