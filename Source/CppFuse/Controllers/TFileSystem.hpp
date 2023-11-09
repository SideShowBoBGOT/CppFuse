#ifndef CPPFUSE_TFILESYSTEM_HPP
#define CPPFUSE_TFILESYSTEM_HPP

#define FUSE_USE_VERSION 30

#include <CppFuse/Helpers/ASharedLock.hpp>

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

    public:
    static const ASharedRwLock<TDirectory>& RootDir();

    protected:
    static void FillerBuffer(const std::string_view& name , void *buffer, fuse_fill_dir_t filler);
    static void FillerDirectory(const ASharedRwLock<TDirectory>& dir, void *buffer, fuse_fill_dir_t filler);

    protected:
    static ASharedRwLock<TDirectory> s_pRootDir;
};

}



#endif //CPPFUSE_TFILESYSTEM_HPP
