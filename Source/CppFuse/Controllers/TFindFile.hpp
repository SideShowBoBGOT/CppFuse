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
    static ASharedFileVariant RecursiveFindStepOne(const fs::path& path,
        fs::path::iterator it, const ASharedRwLock<TDirectory>& dir);

    static ASharedFileVariant RecursiveFindStepTwo(const fs::path& path,
        fs::path::iterator it, const ASharedRwLock<TDirectory>& obj);

    static ASharedFileVariant RecursiveFindStepTwo(const fs::path& path,
        fs::path::iterator it, const ASharedFileVariant & obj);

};

}

#endif //CPPFUSE_TFINDFILE_HPP
