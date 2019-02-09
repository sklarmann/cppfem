

set(SOURCE ${SOURCE} 
					 ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/process.cpp
					 PARENT_SCOPE)
					 
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/CommandTemplate.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/list.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/mathCommandInclude.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/process.h
					 PARENT_SCOPE)
