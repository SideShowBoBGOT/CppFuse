#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Helpers/SOverloadVariant.hpp>

#include <cstring>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";

//const ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = MakeSharedRwLock<TDirectory>(s_sRootPath.data(), static_cast<mode_t>(0), nullptr);

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
//    const auto result = TFinder::Find(path);
//    if(!result) return result.error().Type();
//    std::visit(SOverloadVariant{
//        [st](const ASharedRwLock<TDirectory>& dir) {
//            const auto dirRead = dir->Read();
//            st->st_mode = dirRead->Mode();
//            st->st_nlink = static_cast<nlink_t>(dirRead->FileObjects().size());
//        },
//        [st](const ASharedRwLock<TFile>& file) {
//            const auto fileRead = file->Read();
//            st->st_nlink = 1;
//            st->st_size = static_cast<off_t>(fileRead->Content().size());
//        },
//        [st](const ASharedRwLock<TLink>& link) {
//            const auto linkRead = link->Read();
//            st->st_nlink = 1;
//            st->st_size = static_cast<off_t>(std::string_view(linkRead->LinkTo().c_str()).size());
//        }
//    }, result.value());

    return 0;
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
//    const auto linkRes = TFinder::FindLink(path);
//    if(!linkRes) return linkRes.error().Type();
//    const auto& link = linkRes.value();
//    std::memcpy(buffer, link->Read()->LinkTo().c_str(), size);
    return 0;
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
//    const auto newDirPath = std::filesystem::path(path);
//    auto parentDirRes = TFinder::FindDir(newDirPath.parent_path());
//    if(!parentDirRes) return parentDirRes.error().Type();
//    MakeSharedRwLock<TFile>(newDirPath.filename(), mode, parentDirRes.value());
    return 0;
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
//    const auto newDirPath = std::filesystem::path(path);
//    auto parentDirRes = TFinder::FindDir(newDirPath.parent_path());
//    if(!parentDirRes) return parentDirRes.error().Type();
//    MakeSharedRwLock<TDirectory>(newDirPath.filename(), mode, parentDirRes.value());
    return 0;
}

int TFileSystem::Unlink(const char* path) {
//    const auto objPath = std::filesystem::path(path);
//    const auto objRes = TFinder::Find(objPath);
//    if(!objRes) return objRes.error().Type();
//    const auto& obj = objRes.value();
//    if(std::holds_alternative<ASharedRwLock<TDirectory>>(obj)) {
//        return NNFSExceptionType::NotFile;
//    }
//    std::visit([](const auto& obj) {
//        const auto objRead = obj->Read();
//        const auto parentDir = objRead->Parent().lock();
//        if(!parentDir) return;
//        const auto parentDirWrite = parentDir->Write();
//        auto& fileObjects = parentDirWrite->FileObjects();
//        const auto& objName = objRead->Name();
//        fileObjects.erase(std::ranges::find_if(fileObjects, [&objName](const auto& el) {
//            return std::visit([](const auto& obj) { return obj->Read()->Name(); }, el) == objName;
//        }));
//    }, obj);

    return 0;
}

int TFileSystem::RmDir(const char* path) {
//    const auto objPath = std::filesystem::path(path);
//    const auto objRes = TFinder::FindDir(objPath);
//    if(!objRes) return objRes.error().Type();


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

//const ASharedRwLock<TDirectory>& TFileSystem::RootDir() {
//    return s_pRootDir;
//}

}