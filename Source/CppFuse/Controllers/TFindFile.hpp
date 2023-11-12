#ifndef CPPFUSE_TFINDFILE_HPP
#define CPPFUSE_TFINDFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

class TFindFile {
    public:
    static ASharedFileVariant Find(const fs::path& path);
    static ASharedRwLock<TDirectory> FindDir(const fs::path& path);
    static ASharedRwLock<TLink> FindLink(const fs::path& path);
    static ASharedRwLock<TRegularFile> FindFile(const fs::path& path);

    protected:
    static ASharedFileVariant RecursiveFind(const fs::path& path,
        fs::path::iterator it, const rwl::TRwLockReadGuard<TDirectory>& dirRead);
};

}

#endif //CPPFUSE_TFINDFILE_HPP
