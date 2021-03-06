CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

PROJECT(sir VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FIND_PACKAGE(SFML 2.5 COMPONENTS graphics REQUIRED)

INCLUDE_DIRECTORIES(
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/Model"
        "${PROJECT_SOURCE_DIR}/src/Visualizer"
        "${PROJECT_SOURCE_DIR}/src/Parser"
        "${PROJECT_SOURCE_DIR}/dist"
)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -g -fsanitize=address")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
