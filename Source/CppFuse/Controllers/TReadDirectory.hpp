#ifndef CPPFUSE_TREADDIRECTORY_HPP
#define CPPFUSE_TREADDIRECTORY_HPP

#define FUSE_USE_VERSION 30

#include <CppFuse/Models/TFileObjects.hpp>
#include <fuse3/fuse.h>
#include <string_view>

namespace cppfuse {

class TReadDirectory {
    public:
    TReadDirectory(const fs::path& path, void* buffer, fuse_fill_dir_t filler);

    void operator()();

    protected:
    void DoReadDir(const ASharedRwLock<TDirectory>& var);
    void DoReadDir(const ASharedRwLock<TRegularFile>& var);
    void DoReadDir(const ASharedRwLock<TLink>& var);

    protected:
    void FillerBuffer(const std::string_view& name);
    void FillerDirectory(const ASharedRwLock<TDirectory>& dir);

    protected:
    const fs::path& m_pPath;
    void* m_pBuffer = nullptr;
    fuse_fill_dir_t m_xFiller = nullptr;
};

}

#endif //CPPFUSE_TREADDIRECTORY_HPP
