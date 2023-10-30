add_subdirectory(gsl)
add_subdirectory(magic_enum)
add_subdirectory(RwLock)

target_include_directories(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)
target_link_libraries(${PROJECT_NAME} PRIVATE magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME} PRIVATE RwLock::RwLock)