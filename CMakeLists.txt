cmake_minimum_required(VERSION 2.8)
project(dsignal)
set (CMAKE_CXX_STANDARD 11)

##############################################################################
# LIBRARY VERSION
##############################################################################
SET (DSIGNAL_VERSION_MAJOR 0)
SET (DSIGNAL_VERSION_MINOR 3)
SET (DSIGNAL_VERSION_FIX 0)

configure_file("${CMAKE_SOURCE_DIR}/include/dsignal/version.h.in" "${CMAKE_BINARY_DIR}/include/dsignal/version.h" @ONLY)

##############################################################################
# OPTIONS
##############################################################################
# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
OPTION (USE_FENV_ACCESS "Use access to floating point environment" ON)
OPTION (TESTS_ENABLED "Tests enabled" OFF)

##############################################################################
# Setup library type
##############################################################################
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

IF (USE_FENV_ACCESS)
add_definitions(-DUSE_FENV_ACCESS)
ENDIF (USE_FENV_ACCESS)

##############################################################################
# Installation 
##############################################################################
set(
  DSIGNAL_HEADERS
    include/dsignal/abs.h
    include/dsignal/additionner.h
    include/dsignal/dcmeanremoval.h
    include/dsignal/decimator.h
    include/dsignal/decimatormean.h
    include/dsignal/filterfir.h
    include/dsignal/filteriir.h
    include/dsignal/rms.h
    include/dsignal/multiplier.h
    include/dsignal/arithmeticmean.h
    include/dsignal/min.h
    include/dsignal/max.h
    include/dsignal/sample.h
    include/dsignal/signalprocessor.h
    include/dsignal/signalprocessorsimple.h
    include/dsignal/signalprocessorbuffered.h
    include/dsignal/signalvector.h
    include/dsignal/signalvectormixer.h
    include/dsignal/mixeroperation.h
    include/dsignal/mixeroperationsubtract.h
    include/dsignal/signalsplitter.h
    include/dsignal/signalflow.h
    include/dsignal/signalflowsession.h
    "${CMAKE_BINARY_DIR}/include/dsignal/version.h"
)

# Install header files
install(FILES ${DSIGNAL_HEADERS} DESTINATION include/dsignal)

##############################################################################
# Output directories
##############################################################################
# Libraries
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
  CACHE PATH "Directory for all libraries"
  )

# Executables
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
  CACHE PATH "Directory for all executables."
  )

# Static libraries
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
  CACHE PATH "Directory for all static libraries."
  )

##############################################################################
# Max Warning level
##############################################################################
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
 elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic --std=c++11")
endif()

##############################################################################
# Target library
##############################################################################
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

##############################################################################
# Testing
##############################################################################
IF(TESTS_ENABLED)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
ENDIF(TESTS_ENABLED)
