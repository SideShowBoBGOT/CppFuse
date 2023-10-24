cmake_minimum_required(VERSION 3.26)
project(CppFuse)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(${PROJECT_NAME} main.cpp
        Models/TFileObjectMixin.hpp
        Models/TFile.cpp
        Models/TFile.hpp
        Models/TDirectory.cpp
        Models/TDirectory.hpp
        Models/TLink.cpp
        Models/TLink.hpp
        Controllers/TFileSystem.cpp
        Controllers/TFileSystem.hpp
        Models/TLink.cpp
        Errors/TFSException.hpp
        Errors/NNFSExceptionType.hpp
        Errors/TFSException.cpp
        Models/NNFileType.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE external/gsl/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/RppSync/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/magic_enum/include)

include(FindPkgConfig)
pkg_search_module(FUSE3 REQUIRED fuse3)
target_include_directories(${PROJECT_NAME} PUBLIC ${FUSE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})