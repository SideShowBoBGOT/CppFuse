#ifndef CPPFUSE_TREADDIRECTORY_HPP
#define CPPFUSE_TREADDIRECTORY_HPP

#include <CppFuse/Models/Aliases/ASharedFileVariant.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <fuse3/fuse.h>
#include <string_view>

namespace cppfuse {

class TReadDirectory {
    public:
    static AFSExpected<std::monostate> Do(const char* path, void* buffer, fuse_fill_dir_t filler);

    protected:
    TReadDirectory(const char* path, void* buffer, fuse_fill_dir_t filler);

    protected:
    AFSExpected<std::monostate> operator()(const ASharedFileVariant& var);
    AFSExpected<std::monostate> operator()(const ASharedRwLock<TDirectory>& var);
    AFSExpected<std::monostate> operator()(const ASharedRwLock<SFile>& var);
    AFSExpected<std::monostate> operator()(const ASharedRwLock<SLink>& var);

    protected:
    void FillerBuffer(const std::string_view& name);
    void FillerDirectory(const ASharedRwLock<TDirectory>& dir);

    protected:
    const char* m_Path = nullptr;
    void* m_Buffer = nullptr;
    fuse_fill_dir_t m_Filler = nullptr;
};

}

#endif //CPPFUSE_TREADDIRECTORY_HPP
