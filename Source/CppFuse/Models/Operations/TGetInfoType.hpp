#ifndef CPPFUSE_TGETINFOTYPE_HPP
#define CPPFUSE_TGETINFOTYPE_HPP

#include <CppFuse/Models/Objects/ASharedFileVariant.hpp>
#include <CppFuse/Models/Objects/NNFileType.hpp>

namespace cppfuse {

class TGetInfoType {
    public:
    TGetInfoType()=default;

    public:
    NFileType operator()(const rwl::TRwLockReadGuard<SDirectory>& var);
    NFileType operator()(const rwl::TRwLockReadGuard<SFile>& var);
    NFileType operator()(const rwl::TRwLockReadGuard<SLink>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SDirectory>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SFile>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SLink>& var);
};

}

#endif //CPPFUSE_TGETINFOTYPE_HPP
