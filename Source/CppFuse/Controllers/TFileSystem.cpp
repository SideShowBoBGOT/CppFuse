#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/TFindFile.hpp>
#include <CppFuse/Controllers/TGetFileAttributes.hpp>
#include <CppFuse/Controllers/TSetFileParameter.hpp>
#include <CppFuse/Controllers/TReadDirectory.hpp>
#include <CppFuse/Controllers/TDeleteFile.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <cstring>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    try {
        const auto result = TFindFile::Find(path);
        TGetFileAttributes{st}(result);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
    try {
        const auto link = TFindFile::FindLink(path);
        std::memcpy(buffer, link->Read()->LinkTo.c_str(), size);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
    try {
        const auto newDirPath = std::filesystem::path(path);
        auto parentDir = TFindFile::FindDir(newDirPath.parent_path());
        TRegularFile::New(newDirPath.filename(), mode, parentDir);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
    try {
        const auto newDirPath = std::filesystem::path(path);
        auto parentDir = TFindFile::FindDir(newDirPath.parent_path());
        TDirectory::New(newDirPath.filename(), mode, parentDir);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Unlink(const char* path) {
    try {
        TDeleteFile{}(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::RmDir(const char* path) {
    try {
        TDeleteFile{}(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    const auto linkPath = std::filesystem::path(link_path);
    try {
        const auto parentDir = TFindFile::FindDir(linkPath.parent_path());
        TLink::New(linkPath.filename(), static_cast<mode_t>(0775), parentDir, target_path);
        return 0;
    } catch (const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ChMod(const char* path, mode_t mode, struct fuse_file_info* fi) {
    try {
        const auto var = TFindFile::Find(path);
        TSetInfoMode{mode}(var);
    } catch (const TFSException& ex) {
        return ex.Type();
    }
    return 0;
}

int TFileSystem::Read(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* fi) {
    try {
        auto file = TFindFile::FindFile(path);
        const auto fileRead = file->Read();
        memcpy(buffer, fileRead->Data.data() + offset, size);
        return static_cast<int>(fileRead->Data.size() - offset);
    } catch (const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Write(const char* path, const char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    // TODO: INCORRECT IMPLEMENTATION? How to erase data from file???
    return -1;
//    try {
//        auto fileRes = TFindFile::FindFile(path);
//        auto fileWrite = fileRes->Write();
//        fileWrite->Data.reserve(size);
//        for(auto i = 0u; i < size; ++i) {
//            fileWrite->Data.emplace_back(buffer[i]);
//        }
//        return static_cast<int>(size);
//    } catch (const TFSException& ex) {
//        return ex.Type();
//    }
}

int TFileSystem::ReadDir(const char* path, void* buffer, fuse_fill_dir_t filler, off_t offset,
    struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    try {
        TReadDirectory{path, buffer, filler}();
        return 0;
    } catch (const TFSException& ex) {
        return ex.Type();
    }
}

ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = TDirectory::New(s_sRootPath.data(), static_cast<mode_t>(0777), nullptr);

const ASharedRwLock<TDirectory>& TFileSystem::RootDir() { return s_pRootDir; }

}