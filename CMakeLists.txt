cmake_minimum_required(VERSION 3.3)
project(tetris C CXX)

list(
  APPEND
    CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules"
)

include(AutoInclude)

option(BUILD_TESTS "Build unit tests [for development]" OFF)

add_subdirectory("src")

set(TETRIS_LIBRARIES "")
set(TETRIS_INCLUDE_DIRS "")

find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
  list(
    APPEND
      TETRIS_LIBRARIES ${SDL2_LIBRARY}
  )

  list(
    APPEND
      TETRIS_INCLUDE_DIRS ${SDL2_INCLUDE_DIR}
  )
endif()

find_package(
  Boost
  REQUIRED
  COMPONENTS
    exception
    random
)

if(Boost_FOUND)
  list(
    APPEND
      TETRIS_LIBRARIES ${Boost_LIBRARIES}
  )

  list(
    APPEND
      TETRIS_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}
  )
endif()

find_package(
  GLEW
  REQUIRED
)

if(GLEW_FOUND)
  list(
    APPEND
      TETRIS_LIBRARIES ${GLEW_LIBRARIES}
  )

  list(
    APPEND
      TETRIS_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS}
  )
endif()

find_package(
  GLM
  REQUIRED
)

if(GLM_FOUND)
  list(
    APPEND
      TETRIS_INCLUDE_DIRS ${GLM_INCLUDE_DIRS}
  )
endif()

if(MSYS OR MINGW)
  list(
    APPEND
      TETRIS_LIBRARIES "opengl32"
  )
endif()


enable_cxx11()

set(tetris_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")

include_directories(
  "includes"
  ${TETRIS_INCLUDE_DIRS}
)

add_executable(
  tetris
  ${SRCS}
)

target_link_libraries(
  tetris
  ${TETRIS_LIBRARIES}
)

if(BUILD_TESTS)
  add_subdirectory("extlibs/gtest-1.7.0")

  include_directories(
    "${gtest_SOURCE_DIR}/include"
    "${gtest_SOURCE_DIR}"
  )

  enable_testing()
  add_subdirectory("tests")
endif()
