#include "TFileSystem.hpp"

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    return 0;
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
    return 0;
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
    return 0;
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
    return 0;
}

int TFileSystem::Unlink(const char* path) {
    return 0;
}

int TFileSystem::RmDir(const char* path) {
    return 0;
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    return 0;
}

int TFileSystem::ChMod(const char* path, mode_t mode, struct fuse_file_info* fi) {
    return 0;
}

int TFileSystem::Read(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* fi) {
    return 0;
}

int TFileSystem::Write(const char* path, const char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    return 0;
}

int TFileSystem::ReadDir(const char* path, void* buffer, fuse_fill_dir_t filler, off_t offset,
    struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    return 0;
}
