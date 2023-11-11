#ifndef CPPFUSE_TFINDFILE_HPP
#define CPPFUSE_TFINDFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

class TFindFile {
    public:
    static ASharedFileVariant Find(const std::filesystem::path& path);
    static ASharedRwLock<TDirectory> FindDir(const std::filesystem::path& path);
    static ASharedRwLock<TLink> FindLink(const std::filesystem::path& path);
    static ASharedRwLock<TRegularFile> FindFile(const std::filesystem::path& path);

    protected:
    static ASharedFileVariant RecursiveFindStepOne(const std::filesystem::path& path,
        std::filesystem::path::iterator it, const ASharedRwLock<TDirectory>& dir);

    static ASharedFileVariant RecursiveFindStepTwo(const std::filesystem::path& path,
        std::filesystem::path::iterator it, const ASharedRwLock<TDirectory>& obj);

    static ASharedFileVariant RecursiveFindStepTwo(const std::filesystem::path& path,
        std::filesystem::path::iterator it, const ASharedFileVariant & obj);

};

}

#endif //CPPFUSE_TFINDFILE_HPP
