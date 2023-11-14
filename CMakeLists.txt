cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(${PROJECT_NAME} main.cpp
        Source/CppFuse/Controllers/NSFileAttributes.cpp
        Source/CppFuse/Controllers/TReadDirectory.cpp
        Source/CppFuse/Controllers/TFileSystem.cpp
        Source/CppFuse/Errors/TFSException.cpp
        Source/CppFuse/Controllers/NSFindFile.cpp
        Source/CppFuse/Models/TFileObjects.cpp
        Source/CppFuse/Controllers/NSDeleteFile.cpp)

add_subdirectory(External)
target_include_directories(${PROJECT_NAME} PRIVATE Source)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})