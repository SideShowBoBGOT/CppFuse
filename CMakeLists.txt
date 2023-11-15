cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

add_library(${PROJECT_NAME} STATIC
        Source/${PROJECT_NAME}/Controllers/NSFileAttributes.cpp
        Source/${PROJECT_NAME}/Controllers/TReadDirectory.cpp
        Source/${PROJECT_NAME}/Controllers/TFileSystem.cpp
        Source/${PROJECT_NAME}/Errors/TFSException.cpp
        Source/${PROJECT_NAME}/Controllers/NSFindFile.cpp
        Source/${PROJECT_NAME}/Models/TFileObjects.cpp
        Source/${PROJECT_NAME}/Controllers/NSDeleteFile.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC Source)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${FUSE3_LIBRARIES})

add_subdirectory(External)

add_executable(MainExecutable main.cpp)
target_link_libraries(MainExecutable PRIVATE ${PROJECT_NAME})

add_subdirectory(Tests)


