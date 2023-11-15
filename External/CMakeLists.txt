add_subdirectory(RwLock)
add_subdirectory(magic_enum)

target_link_libraries(${PROJECT_NAME} PUBLIC RwLock::RwLock)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)