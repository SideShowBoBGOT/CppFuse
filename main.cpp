#include "Controllers/TFileSystem.hpp"

fuse_operations FileSystemOperations = {
    .getattr = TFileSystem::GetAttr,
    .readlink = TFileSystem::ReadLink,
    .mknod = TFileSystem::MkNod,
    .mkdir = TFileSystem::MkDir,
    .unlink = TFileSystem::Unlink,
    .rmdir = TFileSystem::RmDir,
    .symlink = TFileSystem::SymLink,
    .chmod = TFileSystem::ChMod,
    .read = TFileSystem::Read,
    .write = TFileSystem::Write,
    .readdir = TFileSystem::ReadDir,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &FileSystemOperations, nullptr);
}