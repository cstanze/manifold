file(GLOB_RECURSE HEADERS_PUBLIC
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

add_library(manifold
  STATIC
  
  os/env.cpp
  os/fs.cpp
  os/str.cpp
  ${HEADERS_PUBLIC}
)

add_library(manifold::manifold ALIAS manifold)
option(MANIFOLD_DEBUG "Enable (simple) debugging fixture" OFF)

if(${MANIFOLD_DEBUG} OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_definitions(manifold
    PUBLIC
    ManifoldIsDebug
  )
endif()

target_include_directories(
  manifold 
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

install(
  TARGETS manifold
  EXPORT manifold-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include/manifold
)

install(
  FILES ${HEADERS_PUBLIC}
  DESTINATION include/manifold
  COMPONENT Headers
)
