#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Models/Objects/SDirectory.hpp>
#include <CppFuse/Models/Objects/SLink.hpp>
#include <CppFuse/Models/Objects/SFile.hpp>
#include <CppFuse/Models/Operations/TGetAttributes.hpp>
#include <CppFuse/Helpers/SOverloadVariant.hpp>
#include <cstring>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
const static constexpr std::string_view s_sCurrentPath = ".";
const static constexpr std::string_view s_sParentPath = "..";

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    const auto result = TFinder::Find(path);
    if(!result) return result.error().Type();
    TGetAttributes{st}(result.value());
    return 0;
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
    const auto linkRes = TFinder::FindLink(path);
    if(!linkRes) return linkRes.error().Type();
    const auto& link = linkRes.value();
    std::memcpy(buffer, link->Read()->LinkTo.c_str(), size);
    return 0;
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
    const auto newDirPath = std::filesystem::path(path);
    auto parentDirRes = TFinder::FindDir(newDirPath.parent_path());
    if(!parentDirRes) return parentDirRes.error().Type();
    SFile::New(newDirPath.filename(), mode, parentDirRes.value());
    return 0;
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
    const auto newDirPath = std::filesystem::path(path);
    auto parentDirRes = TFinder::FindDir(newDirPath.parent_path());
    if(!parentDirRes) return parentDirRes.error().Type();
    TDirectory::New(newDirPath.filename(), mode, parentDirRes.value());
    return 0;
}

int TFileSystem::Unlink(const char* path) {
    const auto objPath = std::filesystem::path(path);
    const auto objRes = TFinder::Find(objPath);
    if(!objRes) return objRes.error().Type();
    const auto& obj = objRes.value();
    if(std::holds_alternative<ASharedRwLock<TDirectory>>(obj)) {
        return NNFSExceptionType::NotFile;
    }
    std::visit([](const auto& obj) {
        const auto objRead = obj->Read();
        const auto parentDir = TGetInfoParent{}(objRead).lock();
        if(!parentDir) return;
        const auto parentDirWrite = parentDir->Write();
        auto& fileObjects = parentDirWrite->Objects;
        const auto& objName = TGetInfoName{}(objRead);
        fileObjects.erase(std::ranges::find_if(fileObjects, [&objName](const auto& el) {
            return std::visit(TGetInfoName{}, el) == objName;
        }));
    }, obj);

    return 0;
}

int TFileSystem::RmDir(const char* path) {
    const auto objPath = std::filesystem::path(path);
    const auto objRes = TFinder::FindDir(objPath);
    if(!objRes) return objRes.error().Type();
    const auto& obj = objRes.value();


    return 0;
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    const auto linkPath = std::filesystem::path(link_path);
    auto parentDirRes = TFinder::FindDir(linkPath.parent_path());
    if(!parentDirRes) return parentDirRes.error().Type();
    auto& parentDir = parentDirRes.value();
    const auto linkName = linkPath.filename().c_str();
    SLink::New(linkName, static_cast<mode_t>(0777), parentDir, target_path);
    return 0;
}

int TFileSystem::ChMod(const char* path, mode_t mode, struct fuse_file_info* fi) {
    const auto var = TFinder::Find(path);
    if(!var) return var.error().Type();
    TSetInfoMode{mode}(var.value());
    return 0;
}

int TFileSystem::Read(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* fi) {
    auto fileRes = TFinder::FindFile(path);
    if(!fileRes) return fileRes.error().Type();
    const auto fileRead = fileRes.value()->Read();
    memcpy(buffer, fileRead->Data.data() + offset, size);
    return static_cast<int>(fileRead->Data.size() - offset);
}

int TFileSystem::Write(const char* path, const char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    auto fileRes = TFinder::FindFile(path);
    if(!fileRes) return fileRes.error().Type();
    const auto& fileWrite = fileRes.value()->Write();
    fileWrite->Data.reserve(size);
    for(auto i = 0u; i < size; ++i) {
        fileWrite->Data.emplace_back(buffer[i]);
    }
    return static_cast<int>(size);
}

int TFileSystem::ReadDir(const char* path, void* buffer, fuse_fill_dir_t filler, off_t offset,
    struct fuse_file_info* fi, enum fuse_readdir_flags flags) {

    for(const auto& p : {s_sCurrentPath, s_sParentPath}) {
        FillerBuffer(p, buffer, filler);
    }
    const auto dirPath = std::filesystem::path(path);
    const auto& result = TFinder::Find(path);
    if(!result) return result.error().Type();

    return std::visit(SOverloadVariant {
        [buffer, filler](const TStDirectory& dir) {
            FillerDirectory(dir, buffer, filler);
            return 0;
        },
        [buffer, filler](const TStLink& link) {
            const auto dirRes = FindDir(link->LinkTo);
            if(!dirRes) return PrintErrGetVal(dirRes.error());
            FillerDirectory(dirRes.value(), buffer, filler);
            return 0;
        },
        [dirPath](const TStFile& file) {
            return PrintErrGetVal(TNotDirectoryException(dirPath.begin(), dirPath.end()));
        }
    }, result.value());
}

ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = TDirectory::New(s_sRootPath.data(), static_cast<mode_t>(0777), nullptr);

const ASharedRwLock<TDirectory>& TFileSystem::RootDir() { return s_pRootDir; }



}