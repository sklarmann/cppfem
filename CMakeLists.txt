cmake_minimum_required (VERSION 2.8)
project (CPPFEM)

# cmake_policy(SET CMP0021 NEW)
#


#SET(PARAVIEW_ENABLE_COPROCESSING TRUE CACHE BOOL "Build Project with GUI")
set(USE_CATALYST ON CACHE BOOL "Link the simulator with Catalyst and enable postprocessing")
#
if(USE_CATALYST)
	find_package(Paraview REQUIRED)
  	include(${PARAVIEW_USE_FILE})
	add_definitions(/DUSE_VTK)
# 	vtk_module_config(__PV_VTK
# 		vtkPVCatalyst)
#
# 	include(vtkModuleMacros)
endif()
#
# #set(CMAKE_GENERATOR_TOOLSET "Intel C++ Compiler 16.0" CACHE STRING "Platform Toolset"  FORCE)
set(SpectraDir ${CMAKE_CURRENT_SOURCE_DIR}/spectra-master/include)
set(Eigen3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eigen3" "${CMAKE_CURRENT_SOURCE_DIR}/eigen3/unsupported" "${CMAKE_CURRENT_SOURCE_DIR}/eigen3/unsupported/test/mpreal")
# include(${CMAKE_CURRENT_SOURCE_DIR}/eigen3/cmake/FindEigen3.cmake)
#
# #set(CMAKE_AUTOMOC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#
# #SET(BUILD_SHARED_LIBRARIES OFF)
# #SET(CMAKE_EXE_LINKER_FLAGS "-static")
#
#
# if(WIN32)
#     SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
# else()
#     SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
# endif()
#
#
# Find and set up Intel MKL Variables
if(WIN32)
	set(MKL_ROOT $ENV{MKLROOT} CACHE PATH "MKL Folder")
	FIND_PATH(MKL_INCLUDE_DIR mkl.h
		PATHS ${MKL_ROOT}/include)
else()
	SET(INTEL_ROOT "/opt/intel" CACHE PATH "Folder contains intel libs")
	SET(MKL_ROOT ${INTEL_ROOT}/mkl CACHE PATH "Folder contains MKL")
	set(MKL_LIB_DIR ${MKL_ROOT}/lib/intel64)
	FIND_PATH(MKL_INCLUDE_DIR mkl.h
		PATHS ${MKL_ROOT}/include)
endif()
# message(${INTEL_ROOT})
# message(${MKL_ROOT})
# message(${MKL_INCLUDE_DIR})

SET(MKL_LIBRARIES ${MKL_ROOT}/lib/intel64)

if(WIN32)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /openmp /MP /bigobj")
	#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Xclang -fopenmp -std=c++14")
else()
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
endif()
# #set(Boost_ADDITIONAL_VERSIONS "1.63" "1.63.0")
find_package(Boost 1.69.0 REQUIRED)
# message(${Boost_INCLUDE_DIR})
#
# # Find include directory
# #  There is no include folder under linux
# if(WIN32)
# 	#set(INTEL_ROOT ${MKL_ROOT}/../compiler/)
#     #find_path(INTEL_INCLUDE_DIR omp.h
#     #    PATHS ${INTEL_ROOT}/include)
#     #set(MKL_INCLUDE_DIR ${MKL_INCLUDE_DIR})
# endif()
#
#
#
#
# SET(WITHGUI TRUE CACHE BOOL "Build Project with GUI")
# set(USE_CATALYST ON CACHE BOOL "Link the simulator with Catalyst")
#
#
# if(WITHGUI)
# SET(ASLIBRARY TRUE)
#     ADD_DEFINITIONS(-DWITHGUI)
#     find_package(ParaView REQUIRED vtkPVCatalyst)
# else()
# SET(ASLIBRARY FALSE)
# endif()

add_subdirectory(FEMSource)
add_subdirectory(Commands)
add_subdirectory(MainProgram)

# if(WITHGUI)
# add_subdirectory(qtinterface)
# endif(WITHGUI)
