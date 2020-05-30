add_executable(ordermatch_ut ordermatch_ut.cpp Market.cpp OrderMatcherTestCase.cpp)

target_include_directories(ordermatch_ut PRIVATE 
  ${PROJECT_SOURCE_DIR}/src/C++ ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/examples/ordermatch
  ${PROJECT_SOURCE_DIR}/UnitTest++/src
  ${PROJECT_SOURCE_DIR}/googletest)

target_link_libraries(ordermatch_ut ${PROJECT_NAME})




