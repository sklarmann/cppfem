# cmake_minimum_required (VERSION 2.8)
# project (CPPFEM)

#set(CMAKE_GENERATOR_TOOLSET "Intel C++ Compiler 16.0" CACHE STRING "Platform Toolset"  FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})

#SET(PARAVIEW_ENABLE_COPROCESSING TRUE CACHE BOOL "Build Project with GUI")
# set(USE_CATALYST ON CACHE BOOL "Link the simulator with Catalyst")
#
# if(USE_CATALYST)
# 	include(${PARAVIEW_USE_FILE})
# 	vtk_module_config(__PV_VTK
# 		vtkPVCatalyst)
#
# 	include(vtkModuleMacros)
# endif()




#SET(ASLIBRARY TRUE CACHE BOOL "Build project as library")

#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCEFILES ${SOURCEFILES})
set(HEADERS ${HEADERS}
	  ${CMAKE_CURRENT_SOURCE_DIR}/preprocessDefine.h
		${CMAKE_CURRENT_SOURCE_DIR}/forwarddeclaration.h
		)
set(INCDIRS ${INCDIRS}
					   # ${CMAKE_CURRENT_SOURCE_DIR}/include
					   # ${EIGEN3_INCLUDE_DIR}
					   )

						 add_compile_definitions(USE_MKL)


add_subdirectory(stringoperations)
add_subdirectory(control)
add_subdirectory(filehandling)
add_subdirectory(elementFormulations)
add_subdirectory(equations)
add_subdirectory(finiteElements)
add_subdirectory(geometry)
add_subdirectory(loads)
add_subdirectory(materials)
add_subdirectory(math)
add_subdirectory(plot)
add_subdirectory(pointercollection)
add_subdirectory(shapefunctions)
add_subdirectory(solver)
# add_subdirectory(wrapper)



# include_directories(${Boost_INCLUDE_DIRS})
# include_directories(${SpectraDir})

# find_package(MKL REQUIRED)
# include_directories(${MKL_INCLUDE_DIR})
	# message(${MKL_INCLUDE_DIR})
link_directories(${MKL_LIBRARIES})
add_definitions(/DEIGEN_USE_MKL_ALL)

# if(WIN32)
# 	# link_directories(${MKL_ROOT}/../compiler/lib/intel64)
# 	# set(LIBS mkl_intel_lp64  mkl_core mkl_intel_thread libiomp5md)
# else()
# 	set(LIBS mkl_intel_lp64  mkl_core mkl_gnu_thread)
# endif()

# include_directories($ENV{MKLROOT}/include)
add_definitions(/DEIGEN_USE_MKL_ALL)
# set(LIBS $ENV{MKLROOT}/lib/intel64_win/mkl_intel_lp64.lib $ENV{MKLROOT}/lib/intel64_win/mkl_intel_thread.lib $ENV{MKLROOT}/lib/intel64_win/mkl_core.lib
#     D:/intel/mkl/compilers_and_libraries_2017.2.187/windows/compiler/lib/intel64_win/libiomp5md.lib)

# find_package(Eigen3 REQUIRED)

if(WIN32)
	set(INCDIRS ${INCDIRS} "${CMAKE_CURRENT_SOURCE_DIR}/eigen3/eigen/src/")
endif(WIN32)

# include_directories("${PROJECT_BINARY_DIR}" "${INCDIRS}" "${Boost_INCLUDE_DIRS}")
include_directories(${INCDIRS} ${Eigen3_DIR} ${MKL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

#include_directories()

#if(ASLIBRARY)
set(NAME cppfem)
set(SOURCE ${SOURCEFILES})
#SET(BUILD_SHARED_LIBRARIES ON)
add_library(${NAME} STATIC ${SOURCE} ${HEADERS})
add_definitions(-DAPPLICATION)
#add_definitions(-DDLL_EXPORT)
#else(ASLIBRARY)
#set(NAME cppfem)
#set(SOURCE ${SOURCE})
#add_executable(${NAME} ${SOURCE} ${HEADERS})
#add_definitions(-DAPPLICATION)
#endif(ASLIBRARY)

foreach(FILE ${SOURCE})
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${HEADERS})
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
target_link_libraries(${NAME} LINK_PRIVATE
			# ${VTK_LIBRARIES}
			# ${Qt5Widgets_LIBRARIES}
			# ${Qt5Core_LIBRARIES}
			${LIBS}
			# vtkPVCatalyst
		)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR})
