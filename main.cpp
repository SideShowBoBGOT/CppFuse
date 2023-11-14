#include <CppFuse/Controllers/TFileSystem.hpp>
#include <iostream>
#include <thread>

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
//    std::jthread([]() {
//        auto start = std::chrono::system_clock::now();
//        auto file = cppfuse::TRegularFile::New("text.txt", 0755, cppfuse::TFileSystem::RootDir());
//        auto fileWrite = file->Write();
//
//        fileWrite->Data.reserve(1000000);
//        for(int i = 0; i < 1000000; ++i) {
//            fileWrite->Data.push_back(45);
//        }
//
//        auto duration = std::chrono::system_clock::now() - start;
//        auto millisecs = duration_cast<std::chrono::milliseconds>(duration).count();
//        std::cout << millisecs << std::endl;
//    });
    return fuse_main(argc, argv, &FileSystemOperations, nullptr);
}