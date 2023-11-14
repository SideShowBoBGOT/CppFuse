add_subdirectory(RwLock)
add_subdirectory(magic_enum)

target_link_libraries(${PROJECT_NAME} PRIVATE RwLock::RwLock)
target_link_libraries(${PROJECT_NAME} PRIVATE magic_enum::magic_enum)