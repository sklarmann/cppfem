


set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/Material.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/MaterialList.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericMaterialFormulation.cpp
					 ${CMAKE_CURRENT_SOURCE_DIR}/MaterialFormulation1.cpp
					 PARENT_SCOPE)

set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/Material.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/MaterialList.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/GenericMaterialFormulation.h
					 ${CMAKE_CURRENT_SOURCE_DIR}/MaterialFormulation1.h
					 PARENT_SCOPE)
