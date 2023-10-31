#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Helpers/SOverloadVariant.hpp>
#include <CppFuse/Models/TFile.hpp>
#include <CppFuse/Models/TLink.hpp>

#include <algorithm>
#include <array>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
static constexpr std::string_view s_sEmptyName = "";
static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

const ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = MakeSharedRwLock<TDirectory>(s_sRootPath.data(), static_cast<mode_t>(0), nullptr);

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    const auto result = Find(path);
    if(!result) return result.error().Type();

    std::visit([st] (const auto& var) {
        var->Read()->FillAttributes(st);
    }, result.value());
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

AFSExpected<ASharedFileVariant> TFileSystem::Find(const AStdPath& path) {
    return RecursiveFindStepOne(path, path.begin(), s_pRootDir);
}

AFSExpected<ASharedFileVariant> TFileSystem::RecursiveFindStepOne(const AStdPath& path, const AStdPathIt& it, const ASharedRwLock<TDirectory>& dir) {
    const auto dirRead = dir->Read();
    const auto ownName = std::string_view(dirRead->Name());
    const auto itName = std::string_view(it->c_str());
    const auto selfNames = std::array{s_sSelfName, s_sEmptyName, ownName};

    if(std::ranges::contains(selfNames, itName)) {
        return RecursiveFindStepTwo(path, it, dir);
    }
    const auto& fileObjects = dirRead->FileObjects();
    const auto childIt = std::ranges::find_if(fileObjects,
        [&itName](const auto& f) {
            return std::visit([&itName](const auto& f) {
                return f->Read()->Name() == itName;
            }, f);
        });
    if(childIt == fileObjects.end()) {
        return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::FileNotExist));
    }
    return RecursiveFindStepTwo(path, it, *childIt);
}

AFSExpected<ASharedFileVariant> TFileSystem::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedFileVariant& obj) {
    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    if(const auto dir = std::get_if<ASharedRwLock<TDirectory>>(&obj)) {
        return RecursiveFindStepOne(path, ++it, *dir);
    }
    return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::NotDirectory));
}

AFSExpected<ASharedRwLock<TDirectory>> TFileSystem::FindDir(const AStdPath& path) {
    return FindGeneral<TDirectory, NFSExceptionType::NotDirectory>(path);
}

AFSExpected<ASharedRwLock<TLink>> TFileSystem::FindLink(const std::filesystem::path& path) {
    return FindGeneral<TLink, NFSExceptionType::NotLink>(path);
}

AFSExpected<ASharedRwLock<TFile>> TFileSystem::FindFile(const std::filesystem::path& path) {
    return FindGeneral<TFile, NFSExceptionType::NotFile>(path);
}

}