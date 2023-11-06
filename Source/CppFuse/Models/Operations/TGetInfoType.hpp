#ifndef CPPFUSE_TGETINFOTYPE_HPP
#define CPPFUSE_TGETINFOTYPE_HPP

#include <CppFuse/Models/Concepts/CSharedRwFileObject.hpp>
#include <CppFuse/Models/Concepts/CRwGuardFileObject.hpp>
#include <CppFuse/Models/Objects/NNFileType.hpp>

namespace cppfuse {

class TGetInfoType {
    public:
    constexpr TGetInfoType()=default;

    public:
    constexpr NFileType operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
    constexpr NFileType operator()(const ASharedRwLock<SDirectory>& var) { return NFileType::Directory; }
    constexpr NFileType operator()(const ASharedRwLock<SFile>& var) { return NFileType::File; }
    constexpr NFileType operator()(const ASharedRwLock<SLink>& var) { return NFileType::Link; }
    constexpr NFileType operator()(const rwl::TRwLockReadGuard<SDirectory>& var) { return NFileType::Directory; }
    constexpr NFileType operator()(const rwl::TRwLockReadGuard<SFile>& var) { return NFileType::File; }
    constexpr NFileType operator()(const rwl::TRwLockReadGuard<SLink>& var) { return NFileType::Link; }
    constexpr NFileType operator()(const rwl::TRwLockWriteGuard<SDirectory>& var) { return NFileType::Directory; }
    constexpr NFileType operator()(const rwl::TRwLockWriteGuard<SFile>& var) { return NFileType::File; }
    constexpr NFileType operator()(const rwl::TRwLockWriteGuard<SLink>& var) { return NFileType::Link; }
};

}

#endif //CPPFUSE_TGETINFOTYPE_HPP
