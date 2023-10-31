#ifndef CPPFUSE_TFILESYSTEM_HPP
#define CPPFUSE_TFILESYSTEM_HPP

#define FUSE_USE_VERSION 30

#include <CppFuse/Models/ASharedFileVariant.hpp>
#include <CppFuse/Errors/TFSException.hpp>

#include <fuse3/fuse.h>
#include <filesystem>

namespace cppfuse {

class TFileSystem {
    public:
    static int GetAttr(const char *path, struct stat *st, struct fuse_file_info *fi);
    static int ReadLink(const char *path, char *buffer, size_t size);
    static int MkNod(const char *path, mode_t mode, dev_t rdev);
    static int MkDir(const char *path, mode_t mode);
    static int Unlink(const char* path);
    static int RmDir(const char* path);
    static int SymLink(const char *target_path, const char *link_path);
    static int ChMod(const char *path, mode_t mode, struct fuse_file_info *fi);
    static int Read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi);
    static int Write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info);
    static int ReadDir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags);

    protected:
    // Find
    static AFSExpected<ASharedFileVariant> Find(const AStdPath& path);
    static AFSExpected<ASharedFileVariant> RecursiveFindStepOne(const AStdPath& path, const AStdPathIt& it,
        const ASharedRwLock<TDirectory>& dir);
    static AFSExpected<ASharedFileVariant> RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it,
        const ASharedFileVariant& obj);

    protected:
    template<typename T, auto FSExceptionValue>
    static AFSExpected<ASharedRwLock<T>> FindGeneral(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TDirectory>> FindDir(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TLink>> FindLink(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TFile>> FindFile(const AStdPath& path);

    protected:
    static const ASharedRwLock<TDirectory> s_pRootDir;
};

template<typename T, auto FSExceptionValue>
AFSExpected<ASharedRwLock<T>> TFileSystem::FindGeneral(const AStdPath& path) {
    const auto result = Find(path);
    if(!result) return std::unexpected(result.error());
    if(const auto t = std::get_if<ASharedRwLock<T>>(&result.value())) {
        return *t;
    }
    return std::unexpected(TFSException(path.begin(), path.end(), FSExceptionValue));
}

}



#endif //CPPFUSE_TFILESYSTEM_HPP
