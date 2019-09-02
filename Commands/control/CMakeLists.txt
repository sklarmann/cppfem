
add_subdirectory(commands)

set(SOURCE ${SOURCE} 
					 ${CMAKE_CURRENT_SOURCE_DIR}/FEMProgram.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/globals.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_SOURCE_DIR}/preprocessDefine.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/forwarddeclaration.h
					${CMAKE_CURRENT_SOURCE_DIR}/FEMProgram.h
					${CMAKE_CURRENT_SOURCE_DIR}/Timer.h
					PARENT_SCOPE)
