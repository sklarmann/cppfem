# cmake_minimum_required (VERSION 2.8)
# project (CPPFEMControl)

#set(CMAKE_GENERATOR_TOOLSET "Intel C++ Compiler 16.0" CACHE STRING "Platform Toolset"  FORCE)
#set(SpectraDir D:/programming/Workspace/spectra-master/include PATH)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#SET(ASLIBRARY TRUE CACHE BOOL "Build project as library")

#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCEFILES ${SOURCEFILES})
set(HEADERS ${HEADERS})
set(INCDIRS ${INCDIRS} ${CMAKE_SOURCE_DIR}
					   ${CMAKE_CURRENT_SOURCE_DIR}/include
					   ${SpectraDir}
					   )


include(cmake.inc)

#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})

#find_package(Paraview REQUIRED)
#include(${PARAVIEW_USE_FILE})

# set(Boost_ADDITIONAL_VERSIONS "1.63" "1.63.0")
# find_package(Boost 1.63.0 REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})


#include_directories(${MKL_INCLUDE_DIR})
#link_directories(${MKL_LIBRARIES})
#add_definitions(/DEIGEN_USE_MKL_ALL)
#set(LIBS mkl_intel_lp64 mkl_intel_thread mkl_core)
if(WIN32)
  include_directories($ENV{MKLROOT}/include)
  add_definitions(/DEIGEN_USE_MKL_ALL)
  set(LIBS $ENV{MKLROOT}/lib/intel64_win/mkl_intel_lp64.lib $ENV{MKLROOT}/lib/intel64_win/mkl_intel_thread.lib $ENV{MKLROOT}/lib/intel64_win/mkl_core.lib "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2018.5.274/windows/compiler/lib/intel64_win/libiomp5md.lib")
else()
	include_directories(${MKL_INCLUDE_DIR})
	set(LIBS ${MKL_LIB_DIR}/libmkl_intel_lp64.so ${MKL_LIB_DIR}/libmkl_gnu_thread.so ${MKL_LIB_DIR}/libmkl_core.so "/opt/intel/compilers_and_libraries_2019.0.117/linux/compiler/lib/intel64/libiomp5.so")
endif()


# if(WIN32)
# 	set(INCDIRS ${INCDIRS} "C:/Program Files/Eigen/include/eigen3" PATH)
# endif(WIN32)
if(WIN32)
	set(INCDIRS ${INCDIRS} "${CMAKE_CURRENT_SOURCE_DIR}/eigen3/eigen/src/" )
endif(WIN32)
# include_directories("${INCDIRS}" "${Boost_INCLUDE_DIRS}")
include_directories("${INCDIRS}" "${Eigen3_DIR}" "${Boost_INCLUDE_DIR}")
message(${Eigen3_DIR})
# include_directories(${EIGEN3_INCLUDE_DIR})

if(ASLIBRARY)
set(NAME cppfemmain)
set(SOURCE ${SOURCEFILES})
#SET(BUILD_SHARED_LIBRARIES ON)
# add_library(${NAME} STATIC ${SOURCE} ${HEADERS})
# add_definitions(-DAPPLICATION)
#add_definitions(-DDLL_EXPORT)
else(ASLIBRARY)
set(NAME cppfemmain)
set(SOURCE ${SOURCE} main.cpp)
add_executable(${NAME} ${SOURCE} ${HEADERS})
add_definitions(-DAPPLICATION)
endif(ASLIBRARY)

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
       # set(GROUP "Header Files${GROUP}")
       set(GROUP "Source Files${GROUP}")
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
       # set(GROUP "Header Files${GROUP}")
       set(GROUP "Source Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
#target_link_libraries(${NAME}   cppfem cppfemcontrol) #
target_link_libraries(${NAME} LINK_PRIVATE ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${LIBS} ${VTK_LIBRARIES} cppfem cppfemcontrol) #
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
