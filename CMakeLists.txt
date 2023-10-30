cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(${PROJECT_NAME} main.cpp
        CppFuse/Models/TFile.cpp
        CppFuse/Models/TDirectory.cpp
        CppFuse/Models/TLink.cpp
        CppFuse/Controllers/TFileSystem.cpp
        CppFuse/Models/TLink.cpp
        CppFuse/Errors/TFSException.cpp)

add_subdirectory(external)

target_include_directories(${PROJECT_NAME} PRIVATE CppFuse)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})