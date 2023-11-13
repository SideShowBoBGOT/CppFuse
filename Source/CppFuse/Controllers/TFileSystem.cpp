#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <CppFuse/Controllers/NSFileAttributes.hpp>
#include <CppFuse/Controllers/TSetFileParameter.hpp>
#include <CppFuse/Controllers/TReadDirectory.hpp>
#include <CppFuse/Controllers/NSDeleteFile.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <cstring>
#include <iostream>
#include <span>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    try {
        const auto result = NSFindFile::Find(path);
        NSFileAttributes::Get(result, st);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
    try {
        const auto link = NSFindFile::FindLink(path);
        std::memcpy(buffer, link->Read()->LinkTo.c_str(), size);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
    try {
        const auto newDirPath = std::filesystem::path(path);
        auto parentDir = NSFindFile::FindDir(newDirPath.parent_path());
        TRegularFile::New(newDirPath.filename(), mode, parentDir);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
    try {
        const auto newDirPath = std::filesystem::path(path);
        auto parentDir = NSFindFile::FindDir(newDirPath.parent_path());
        TDirectory::New(newDirPath.filename(), mode, parentDir);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Unlink(const char* path) {
    try {
        NSDeleteFile::Delete(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::RmDir(const char* path) {
    try {
        NSDeleteFile::Delete(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    const auto linkPath = std::filesystem::path(link_path);
    try {
        const auto parentDir = NSFindFile::FindDir(linkPath.parent_path());
        TLink::New(linkPath.filename(), static_cast<mode_t>(0775), parentDir, target_path);
        return 0;
    } catch (const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ChMod(const char* path, mode_t mode, struct fuse_file_info* fi) {
    try {
        const auto var = NSFindFile::Find(path);
        TSetInfoMode{mode}(var);
    } catch (const TFSException& ex) {
        return ex.Type();
    }
    return 0;
}

int TFileSystem::Read(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    try {
        auto file = NSFindFile::FindRegularFile(path);
        const auto fileRead = file->Read();
        memcpy(buffer, fileRead->Data.data() + offset, size);
        return static_cast<int>(fileRead->Data.size() - offset);
    } catch (const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Write(const char* path, const char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    try {
        auto file = NSFindFile::FindRegularFile(path);
        auto fileWrite = file->Write();
        auto& data = fileWrite->Data;
        const auto src = std::span(buffer, size);
        if(info->flags & O_WRONLY) {
            std::cout << size << std::endl;
            const auto replaceSize = data.end() - (data.begin() + offset);
            if(replaceSize < size) {
                data.resize(data.size() + size - replaceSize);
            }
            std::copy(src.begin(), src.end(), data.begin() + offset);
        } else if(info->flags & O_APPEND) {
            data.insert(data.begin() + offset, src.begin(), src.end());
        }
        return static_cast<int>(size);
    } catch (const TFSException& ex) {
        return ex.Type();
    }
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