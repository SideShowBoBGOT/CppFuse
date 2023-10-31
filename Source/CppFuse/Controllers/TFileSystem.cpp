#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Models/TFile.hpp>
#include <CppFuse/Models/TLink.hpp>

#include <array>
#include <algorithm>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
static constexpr std::string_view s_sEmptyName = "";
static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

const ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = MakeSharedRwLock<TDirectory>(s_sRootPath.data(), static_cast<mode_t>(0), nullptr);

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    const auto read = s_pRootDir->Read();
    st->st_mode = read->Mode();
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

AFSExpected<ASharedFileVariant> TFileSystem::RecursiveFindStepOne(const AStdPath& path, AStdPathIt it, const ASharedRwLock<TDirectory>& dir) {

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

    if(obj->Read()->Type() == NFileType::Directory) {
        RecursiveFindStepOne(path, ++it, obj)
    }
    return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::NotDirectory));
}

}