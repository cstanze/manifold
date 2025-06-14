cmake_minimum_required(VERSION 3.19.6)

project(Manifold CXX)

# Clobber existing timestamps of extracted files when using `FetchContent`
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Allow for forced colored output
option(ROOTS_FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." ON)
if(${FORCED_COLORED_OUTPUT})
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
  endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test Dependencies
include(FetchContent)
# v1.17.0
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

# for windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Source
add_subdirectory(lib)

# Tests
enable_testing()
add_subdirectory(test)
