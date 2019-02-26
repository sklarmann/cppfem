set(CDIR ${CMAKE_CURRENT_SOURCE_DIR}/elementFormulations)


set(SOURCEFILES ${SOURCEFILES}
	         ${CMAKE_CURRENT_SOURCE_DIR}/GenericElementFormulation.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation201.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS}
	          ${CMAKE_CURRENT_SOURCE_DIR}/GenericElementFormulation.h
					  ${CMAKE_CURRENT_SOURCE_DIR}/ElementFormulation201.h
					  PARENT_SCOPE)
