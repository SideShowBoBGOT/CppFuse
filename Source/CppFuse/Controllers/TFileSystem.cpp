#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/TFindFile.hpp>
#include "TGetFileAttributes.hpp"
#include "TGetFileParameter.hpp"
#include "TSetFileParameter.hpp"
#include "TReadDirectory.hpp"
#include <cstring>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
const static constexpr std::string_view s_sCurrentPath = ".";
const static constexpr std::string_view s_sParentPath = "..";

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
    // TODO: INCORRECT IMPLEMENTATION? Is there possibility of deadlock???
    return -1;
//    const auto objPath = std::filesystem::path(path);
//    const auto objRes = TFindFile::Find(objPath);
//    if(!objRes) return objRes.error().Type();
//    const auto& obj = objRes.value();
//    if(std::holds_alternative<ASharedRwLock<TDirectory>>(obj)) {
//        return NNFSExceptionType::NotFile;
//    }
//    std::visit([](const auto& obj) {
//        const auto objRead = obj->Read();
//        const auto parentDir = TGetInfoParent{}(objRead).lock();
//        if(!parentDir) return;
//        const auto parentDirWrite = parentDir->Write();
//        auto& fileObjects = parentDirWrite->Objects;
//        const auto& objName = TGetInfoName{}(objRead);
//        fileObjects.erase(std::ranges::find_if(fileObjects, [&objName](const auto& el) {
//            return std::visit(TGetInfoName{}, el) == objName;
//        }));
//    }, obj);
//
//    return 0;
}

int TFileSystem::RmDir(const char* path) {
    // TODO: INCORRECT IMPLEMENTATION? Need to call DELETE OBJECT recursively on each file object???
    return -1;
//    const auto objPath = std::filesystem::path(path);
//    ASharedRwLock<TDirectory> parentDir = nullptr;
//    try {
//        parentDir = TFindFile::FindDir(objPath.parent_path());
//    } catch (const TFSException& ex) {
//        return ex.Type();
//    }
//    auto parentDirWrite = parentDir->Write();
//    auto& objs = parentDirWrite->Objects;
//    objs.erase(std::remove_if(objs.begin(), objs.end(),
//        [name=objPath.filename().c_str()](const auto& child) {
//            return name == TGetInfoName{}(child);
//        }
//    ), objs.end());
//    return 0;
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    const auto linkPath = std::filesystem::path(link_path);
    const auto linkName = linkPath.filename().c_str();
    try {
        const auto parentDir = TFindFile::FindDir(linkPath.parent_path());
        TLink::New(linkName, static_cast<mode_t>(0777), parentDir, target_path);
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