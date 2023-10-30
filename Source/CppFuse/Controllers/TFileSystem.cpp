#include <CppFuse/Controllers/TFileSystem.hpp>
#include <array>
#include <algorithm>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
static const std::string_view s_sEmptyName = "";
static const std::string_view s_sSelfName = ".";
static const std::string_view s_sParentName = "..";

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

//TFSExpected<rppsync::TSharedRw<AFileObject>> TFileSystem::Find(const TStdPath& path) {
//    return DoFind(path, path.begin(), s_pRootDir);
//}
//
//TFSExpected<rppsync::TSharedRw<AFileObject>> TFileSystem::DoFind(const TStdPath& path,
//    TStdPathIt it, const rppsync::TSharedRw<TDirectory>& dir) {
//
//    const auto dirRead = dir->Read();
//    const auto ownName = std::string_view(dirRead->Name());
//    const auto itName = std::string_view(it->c_str());
//    const auto selfNames = std::array{s_sSelfName, s_sEmptyName, ownName};
//    if(std::ranges::contains(selfNames, itName)) {
//
//        continue;
//    }
//    const auto childIt = std::ranges::find_if(dirRead->FileObjects(),
//        [itName](const auto& f) { return f->Read()->Name() == itName; });
//    if(childIt == dirRead->FileObjects().end()) {
//        return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::FileNotExist));
//    }
//
//    const auto& file = *childIt;
//
//
//
//    return cppfuse::TFSExpected<rppsync::TSharedRw<AFileObject>>();
//}
//
//TFSExpected<rppsync::TSharedRw<AFileObject>> TFileSystem::ContinueFind(const TStdPath& path,
//    TStdPathIt it, const rppsync::TSharedRw<AFileObject>& obj) {
//
//    if(std::distance(it, path.end()) == 1) {
//        return obj;
//    }
//
//    if(obj->Read()->Type() == NFileType::Directory) {
//        DoFind(path, ++it, obj)
//    }
//    return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::NotDirectory));
//}

}