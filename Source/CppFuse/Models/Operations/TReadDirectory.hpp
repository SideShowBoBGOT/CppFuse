#ifndef CPPFUSE_TREADDIRECTORY_HPP
#define CPPFUSE_TREADDIRECTORY_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <fuse3/fuse.h>
#include <string_view>

namespace cppfuse {

class TReadDirectory {
    public:
    TReadDirectory(const char* path, void* buffer, fuse_fill_dir_t filler);

    void operator()();

    protected:
    void DoReadDir(const ASharedRwLock<TDirectory>& var);
    void DoReadDir(const ASharedRwLock<TFile>& var);
    void DoReadDir(const ASharedRwLock<TLink>& var);

    protected:
    void FillerBuffer(const std::string_view& name);
    void FillerDirectory(const ASharedRwLock<TDirectory>& dir);

    protected:
    const char* m_pPath = nullptr;
    void* m_pBuffer = nullptr;
    fuse_fill_dir_t m_xFiller = nullptr;
};

}

#endif //CPPFUSE_TREADDIRECTORY_HPP
