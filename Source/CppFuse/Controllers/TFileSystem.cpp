#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Helpers/SOverloadVariant.hpp>
#include <CppFuse/Models/SDirectory.hpp>
#include <CppFuse/Models/SLink.hpp>
#include <CppFuse/Models/SFile.hpp>
#include <cstring>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    const auto result = TFinder::Find(path);
    if(!result) return result.error().Type();
    std::visit(SOverloadVariant{
        [st](const ASharedRwLock<SDirectory>& dir) {
            const auto dirRead = dir->Read();
            st->st_mode = AGetMode{}(dirRead);
            st->st_nlink = static_cast<nlink_t>(dirRead->Objects.size());
        },
        [st](const ASharedRwLock<SFile>& file) {
            const auto fileRead = file->Read();
            st->st_nlink = 1;
            st->st_size = static_cast<off_t>(fileRead->Data.size());
        },
        [st](const ASharedRwLock<SLink>& link) {
            const auto linkRead = link->Read();
            st->st_nlink = 1;
            st->st_size = static_cast<off_t>(std::string_view(linkRead->LinkTo.c_str()).size());
        }
    }, result.value());

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
    SDirectory::New(newDirPath.filename(), mode, parentDirRes.value());
    return 0;
}

int TFileSystem::Unlink(const char* path) {
    const auto objPath = std::filesystem::path(path);
    const auto objRes = TFinder::Find(objPath);
    if(!objRes) return objRes.error().Type();
    const auto& obj = objRes.value();
    if(std::holds_alternative<ASharedRwLock<SDirectory>>(obj)) {
        return NNFSExceptionType::NotFile;
    }
    std::visit([](const auto& obj) {
        const auto objRead = obj->Read();
        const auto parentDir = AGetParent{}(objRead).lock();
        if(!parentDir) return;
        const auto parentDirWrite = parentDir->Write();
        auto& fileObjects = parentDirWrite->Objects;
        const auto& objName = AGetName{}(objRead);
        fileObjects.erase(std::ranges::find_if(fileObjects, [&objName](const auto& el) {
            return std::visit(AGetName{}, el) == objName;
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
    ASetMode{}(var.value(), mode);
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
    return 0;
}

ASharedRwLock<SDirectory> TFileSystem::s_pRootDir = nullptr;

const ASharedRwLock<SDirectory>& TFileSystem::RootDir() { return s_pRootDir; }

void TFileSystem::FillerBuffer(const std::string_view& name, void* buffer, fuse_fill_dir_t filler) {
    filler(buffer, name.data(), NULL, 0, fuse_fill_dir_flags::FUSE_FILL_DIR_PLUS);
}

void TFileSystem::FillerDirectory(const ASharedRwLock<SDirectory>& dir, void* buffer, fuse_fill_dir_t filler) {
    const auto dirRead = dir->Read();
    for(const auto& var : dirRead->Objects) {
        const auto name = std::visit(AGetName{}, var);
        FillerBuffer(name, buffer, filler);
    }
}

void TFileSystem::Init() {
    ASetName::Init();
    ASetMode::Init();
    ASetParent::Init();
    ASetUid::Init();
    ASetGid::Init();
    AGetName::Init();
    AGetMode::Init();
    AGetParent::Init();
    AGetUid::Init();
    AGetGid::Init();
    s_pRootDir = SDirectory::New(s_sRootPath.data(), static_cast<mode_t>(0777), nullptr);
}

}