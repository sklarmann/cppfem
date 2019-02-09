

set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/stringCommandHandler.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/HandlingStructs.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/OutputHandler.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/FEMExceptions.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} 
					 ${CMAKE_CURRENT_SOURCE_DIR}/HandlingStructs.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/OutputHandler.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/stringCommandHandler.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/FEMExceptions.h
					 PARENT_SCOPE)
