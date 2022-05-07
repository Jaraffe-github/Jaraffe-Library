cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18)

project(JFL)
enable_language(C)
enable_language(CXX)

# cmake -DBUILD_SHARED_LIBS=YES (Shared build)
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" OFF)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Build/${CMAKE_BUILD_TYPE})
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Build/${CMAKE_BUILD_TYPE})
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Build/${CMAKE_BUILD_TYPE})

add_subdirectory(JFL)
add_subdirectory(ThirdParty)
add_subdirectory(UnitTest)