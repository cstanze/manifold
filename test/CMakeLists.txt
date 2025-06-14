include(GoogleTest)

set(MANIFOLD_TESTS "bitflags;env;fs;str")

foreach(mtest ${MANIFOLD_TESTS})
  set(test_name ${mtest}_test)

  add_executable(
    ${test_name}
    ${mtest}.cpp
  )

  target_link_libraries(
    ${test_name}
    PRIVATE
    GTest::gtest_main
    manifold::manifold
  )

  target_include_directories(
    ${test_name}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  gtest_discover_tests(${test_name})
endforeach()
