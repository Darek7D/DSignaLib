cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
project(dsignal)

##############################################################################
# OPTIONS
##############################################################################
# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)


# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

##############################################################################
# Installation 
##############################################################################
set(
  DSIGNAL_HEADERS
    include/dsignal/additionner.h
    include/dsignal/dcmeanremoval.h
    include/dsignal/decimator.h
    include/dsignal/filterfir.h
    include/dsignal/filteriir.h
    include/dsignal/rms.h
    include/dsignal/multiplier.h
    include/dsignal/sample.h
    include/dsignal/signalprocessor.h
    include/dsignal/signalprocessorsimple.h
    include/dsignal/signalprocessorbuffered.h
    include/dsignal/signalvector.h
    include/dsignal/signalsplitter.h
)

# Install header files
install(FILES ${DSIGNAL_HEADERS} DESTINATION include/dsignal)

##############################################################################
# MSVC 
##############################################################################
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)

# Max Warning level
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
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
