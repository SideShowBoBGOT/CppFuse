cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

# Creating library

add_subdirectory(External)

add_library(${PROJECT_NAME} STATIC
        Source/${PROJECT_NAME}/Controllers/NSFileAttributes.cpp
        Source/${PROJECT_NAME}/Controllers/TReadDirectory.cpp
        Source/${PROJECT_NAME}/Controllers/TFileSystem.cpp
        Source/${PROJECT_NAME}/Errors/TFSException.cpp
        Source/${PROJECT_NAME}/Controllers/NSFindFile.cpp
        Source/${PROJECT_NAME}/Models/TFileObjects.cpp
        Source/${PROJECT_NAME}/Controllers/NSDeleteFile.cpp
        Source/${PROJECT_NAME}/Views/TFileSystemCLI.cpp
        Source/${PROJECT_NAME}/Views/TFileSystemClientCLI.cpp
        Source/CppFuse/Controllers/NSAccessFile.cpp
        Source/CppFuse/Helpers/NSHelperFuncs.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_link_libraries(${PROJECT_NAME} PUBLIC RwLock::RwLock)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)
target_include_directories(${PROJECT_NAME} PUBLIC External/CLI11/include)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${FUSE3_LIBRARIES})

# Linking project library to main executable

add_executable(MainExecutable main.cpp)
target_link_libraries(MainExecutable PRIVATE ${PROJECT_NAME})

add_executable(FindByName FindByName.cpp)
target_link_libraries(FindByName PRIVATE ${PROJECT_NAME})

add_subdirectory(Tests)

