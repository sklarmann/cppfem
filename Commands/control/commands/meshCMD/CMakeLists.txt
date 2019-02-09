

set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplanebc.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplaneload.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetDegreeOfFreedom.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetMaterials.cpp
					 PARENT_SCOPE)
					 
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/Block.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/CommandTemplate.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplanebc.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/inplaneload.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/meshCommandInclude.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetDegreeOfFreedom.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/SetMaterials.h
					 PARENT_SCOPE)
