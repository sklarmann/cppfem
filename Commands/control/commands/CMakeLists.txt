add_subdirectory(macroCMD)
add_subdirectory(meshCMD)
add_subdirectory(plotCMD)
add_subdirectory(mathCMD)


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/GenericCommand.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/InputParser.cpp
					 #${CMAKE_CURRENT_SOURCE_DIR}/quitCommands.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/GenericCommand.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/InputParser.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/quitCommands.h
					 PARENT_SCOPE)
