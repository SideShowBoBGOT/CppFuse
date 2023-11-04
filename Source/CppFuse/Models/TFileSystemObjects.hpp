#ifndef CPPFUSE_TFILESYSTEMOBJECTS_HPP
#define CPPFUSE_TFILESYSTEMOBJECTS_HPP

#include <CppFuse/Models/NNFileType.hpp>
#include <CppFuse/Helpers/ASharedLock.hpp>

#include <filesystem>
#include <string>
#include <vector>
#include <variant>


namespace cppfuse {

struct SDirectory;
struct SFile;
struct SLink;

using ASharedFSVariant = std::variant<
    ASharedRwLock<SDirectory>,
    ASharedRwLock<SFile>,
    ASharedRwLock<SLink>
>;

using AReadGuardFSVariant = std::variant<
    rwl::TRwLockReadGuard<SDirectory>,
    rwl::TRwLockReadGuard<SFile>,
    rwl::TRwLockReadGuard<SLink>
>;

using AWriteGuardFSVariant = std::variant<
    rwl::TRwLockWriteGuard<SDirectory>,
    rwl::TRwLockWriteGuard<SFile>,
    rwl::TRwLockWriteGuard<SLink>
>;

struct SetParent {
    void operator()(const ASharedRwLock<SDirectory>& var, const ASharedRwLock<SDirectory>& parent);
    void operator()(const ASharedRwLock<SFile>& var, const ASharedRwLock<SDirectory>& parent);
    void operator()(const ASharedRwLock<SLink>& var, const ASharedRwLock<SDirectory>& parent);
    void operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const ASharedRwLock<SDirectory>& parent);
    void operator()(const rwl::TRwLockWriteGuard<SFile>& var, const ASharedRwLock<SDirectory>& parent);
    void operator()(const rwl::TRwLockWriteGuard<SLink>& var, const ASharedRwLock<SDirectory>& parent);
};

struct SInfo {
    friend struct SetParent;
    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    ASharedRwLock<SDirectory> m_pParent;
};

struct SDirectory : SInfo {
    std::vector<ASharedFSVariant> Objects;
};

struct SFile : SInfo {
    std::vector<char> Data;
};

struct SLink : SInfo {
    std::filesystem::path LinkTo;
};

}

#endif //CPPFUSE_TFILESYSTEMOBJECTS_HPP
