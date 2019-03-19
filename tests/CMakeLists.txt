set(UNIT_TEST_LIST
  abs
  additionner
  signalprocessorbuffered
  dcmeanremoval
  decimator
  decimatormean
  filterfir
  filteriir
  rms
  multiplier
  arithmeticmean
  min
  max
  signalvector
  signalvectormixer
  signalpipeline
  signalflow
  signalsplitter)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST
    ${NAME}.test.cpp)
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
  PUBLIC ${PROJECT_NAME} )

target_include_directories(${TARGET_NAME}
  PUBLIC ../3rdparty/catch2/ ../include ${CMAKE_BINARY_DIR}/exports)

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)
