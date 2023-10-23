#include "Controllers/TFileSystem.hpp"

fuse_operations FileSystemOperations = {
    .getattr = cppfuse::TFileSystem::GetAttr,
    .readlink = cppfuse::TFileSystem::ReadLink,
    .mknod = cppfuse::TFileSystem::MkNod,
    .mkdir = cppfuse::TFileSystem::MkDir,
    .unlink = cppfuse::TFileSystem::Unlink,
    .rmdir = cppfuse::TFileSystem::RmDir,
    .symlink = cppfuse::TFileSystem::SymLink,
    .chmod = cppfuse::TFileSystem::ChMod,
    .read = cppfuse::TFileSystem::Read,
    .write = cppfuse::TFileSystem::Write,
    .readdir = cppfuse::TFileSystem::ReadDir,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &FileSystemOperations, nullptr);
}