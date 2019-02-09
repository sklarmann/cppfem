


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/GaussPoints.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/KernelShape.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LagrangeShape.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Legendre.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Lobatto.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/GaussPoints.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/KernelShape.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LagrangeShape.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Legendre.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Lobatto.h
					 PARENT_SCOPE)
