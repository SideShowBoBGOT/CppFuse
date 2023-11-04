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

struct SetName {
    void operator()(const ASharedRwLock<SDirectory>& var, const std::string& name);
    void operator()(const ASharedRwLock<SFile>& var, const std::string& name);
    void operator()(const ASharedRwLock<SLink>& var, const std::string& name);
    void operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const std::string& name);
    void operator()(const rwl::TRwLockWriteGuard<SFile>& var, const std::string& name);
    void operator()(const rwl::TRwLockWriteGuard<SLink>& var, const std::string& name);
};

struct SetMode {
    void operator()(const ASharedRwLock<SDirectory>& var, mode_t mode);
    void operator()(const ASharedRwLock<SFile>& var, mode_t mode);
    void operator()(const ASharedRwLock<SLink>& var, mode_t mode);
    void operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, mode_t mode);
    void operator()(const rwl::TRwLockWriteGuard<SFile>& var, mode_t mode);
    void operator()(const rwl::TRwLockWriteGuard<SLink>& var, mode_t mode);
};

struct GetType {
    NFileType operator()(const ASharedRwLock<SDirectory>& var);
    NFileType operator()(const ASharedRwLock<SFile>& var);
    NFileType operator()(const ASharedRwLock<SLink>& var);
    NFileType operator()(const rwl::TRwLockReadGuard<SDirectory>& var);
    NFileType operator()(const rwl::TRwLockReadGuard<SFile>& var);
    NFileType operator()(const rwl::TRwLockReadGuard<SLink>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SDirectory>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SFile>& var);
    NFileType operator()(const rwl::TRwLockWriteGuard<SLink>& var);
};

template<typename T>
struct SInfo {
    friend struct SetParent;
    friend struct SetName;
    friend struct SetMode;
    friend struct GetType;

    template<typename... Args>
    static ASharedRwLock<T> New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent, Args&&... args);

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    AWeakRwLock<SDirectory> m_pParent;
};

struct SDirectory : SInfo<SDirectory> {
    friend struct SInfo<SDirectory>;
    std::vector<ASharedFSVariant> Objects;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SDirectory>& var);
};

struct SFile : SInfo<SFile> {
    friend struct SInfo<SFile>;
    std::vector<char> Data;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SFile>& var);
};

struct SLink : SInfo<SLink> {
    friend struct SInfo<SLink>;
    std::filesystem::path LinkTo;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path);
};

template<typename T>
template<typename... Args>
ASharedRwLock<T> SInfo<T>::New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent, Args&&... args) {
    const auto obj = MakeSharedRwLock<SDirectory>();
    const auto objWrite = obj->Write();
    SetName{}(objWrite, name);
    SetMode{}(objWrite, mode);
    T::DoNew(objWrite, std::forward<Args>(args)...);
    SetParent{}(objWrite, parent);
}

}

#endif //CPPFUSE_TFILESYSTEMOBJECTS_HPP
