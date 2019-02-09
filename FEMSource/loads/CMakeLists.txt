


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/PropfunctionHandler.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/Timefunction.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericLoad.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/DofLoad.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/LoadList.cpp
					 PARENT_SCOPE)
					 
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/PropfunctionHandler.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/Timefunction.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericLoad.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/DofLoad.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/LoadList.h
					 PARENT_SCOPE)
