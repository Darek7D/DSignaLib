cmake_minimum_required(VERSION 2.8)
include (GenerateExportHeader)

##############################################################################
# Source files
##############################################################################
set(
  DSIGNAL_SOURCES
      additionner.cpp
      dcmeanremoval.cpp
      decimator.cpp
      filterfir.cpp
      filteriir.cpp
      rms.cpp
      multiplier.cpp
      sample.cpp
      signalprocessorsimple.cpp
      signalprocessorbuffered.cpp
      signalvector.cpp
      signalflow.cpp
      signalflowsession.cpp
      signalsplitter.cpp
)

##############################################################################
# Create library 
##############################################################################
add_library(${PROJECT_NAME} ${LIB_TYPE}	${DSIGNAL_SOURCES})

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/dsignal_export.h)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${CMAKE_BINARY_DIR}/exports)

##############################################################################
# Install library 
##############################################################################
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
  
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(FILES ${CMAKE_BINARY_DIR}/exports/dsignal_export.h
    DESTINATION include
)

install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

