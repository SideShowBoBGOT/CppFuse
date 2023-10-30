#ifndef CPPFUSE_TFILESYSTEM_HPP
#define CPPFUSE_TFILESYSTEM_HPP

#define FUSE_USE_VERSION 30

#include "../Models/TDirectory.hpp"

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
    static TFSExpected<rppsync::TSharedRw<TFileObject>> Find(const TStdPath& path);
    static TFSExpected<rppsync::TSharedRw<TFileObject>> DoFind(const TStdPath& path, TStdPathIt it,
        const rppsync::TSharedRw<TDirectory>& dir);
    static TFSExpected<rppsync::TSharedRw<TFileObject>> ContinueFind(const TStdPath& path, TStdPathIt it,
        const rppsync::TSharedRw<TFileObject>& obj);

    protected:
    static const rppsync::TSharedRw<TDirectory> s_pRootDir;
};

}



#endif //CPPFUSE_TFILESYSTEM_HPP
