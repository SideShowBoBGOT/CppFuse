add_subdirectory(RwLock)

target_link_libraries(${PROJECT_NAME} PRIVATE RwLock::RwLock)