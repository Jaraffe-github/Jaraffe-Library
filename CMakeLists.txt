cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18)

project(JFL)
enable_language(C)
enable_language(CXX)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY Build/${CMAKE_BUILD_TYPE})
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY Build/${CMAKE_BUILD_TYPE})
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY Build/${CMAKE_BUILD_TYPE})

add_subdirectory(JFL)
add_subdirectory(ThirdParty)
add_subdirectory(UnitTest)