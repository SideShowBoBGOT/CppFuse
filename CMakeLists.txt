cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(${PROJECT_NAME} main.cpp
        Source/CppFuse/Controllers/TFileSystem.cpp
        Source/CppFuse/Errors/TFSException.cpp
        Source/CppFuse/Controllers/TFinder.cpp
        Source/CppFuse/Models/Objects/SDirectory.cpp
        Source/CppFuse/Models/Objects/SFile.cpp
        Source/CppFuse/Models/Objects/SLink.cpp
        Source/CppFuse/Models/Operations/TGetAttributes.cpp
        Source/CppFuse/Models/Operations/TSetInfoParameter.cpp
        Source/CppFuse/Models/Operations/TGetInfoParameter.cpp
        Source/CppFuse/Models/Operations/TGetInfoType.cpp)

add_subdirectory(external)
target_include_directories(${PROJECT_NAME} PRIVATE Source)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})