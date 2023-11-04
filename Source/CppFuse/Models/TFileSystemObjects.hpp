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

using ASharedFileVariant = std::variant<
    ASharedRwLock<SDirectory>,
    ASharedRwLock<SFile>,
    ASharedRwLock<SLink>
>;

struct SInfo;

template<typename FieldType>
class TGetParameter {
    public:
    const FieldType& operator()(const ASharedRwLock<SDirectory>& var) { TGetParameter{}(var->Read()); };
    const FieldType& operator()(const ASharedRwLock<SFile>& var) { TGetParameter{}(var->Read()); };
    const FieldType& operator()(const ASharedRwLock<SLink>& var) { TGetParameter{}(var->Read()); };
    const FieldType& operator()(const rwl::TRwLockReadGuard<SDirectory>& var) { return ((*var).*s_pFieldPtr); }
    const FieldType& operator()(const rwl::TRwLockReadGuard<SFile>& var) { return ((*var).*s_pFieldPtr); }
    const FieldType& operator()(const rwl::TRwLockReadGuard<SLink>& var) { return ((*var).*s_pFieldPtr); }
    FieldType& operator()(const rwl::TRwLockWriteGuard<SDirectory>& var) { return ((*var).*s_pFieldPtr); }
    FieldType& operator()(const rwl::TRwLockWriteGuard<SFile>& var) { return ((*var).*s_pFieldPtr); }
    FieldType& operator()(const rwl::TRwLockWriteGuard<SLink>& var) { return ((*var).*s_pFieldPtr); }

    public:
    static int Init() { return 0; };

    protected:
    static FieldType SInfo::* s_pFieldPtr;
};

using AGetName = TGetParameter<std::string>;
using AGetMode = TGetParameter<mode_t>;
using AGetParent = TGetParameter<AWeakRwLock<SDirectory>>;

template<typename FieldType, typename ParamType>
class TSetParameter {
    public:
    void operator()(const ASharedRwLock<SDirectory>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const ASharedRwLock<SFile>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const ASharedRwLock<SLink>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }
    void operator()(const rwl::TRwLockWriteGuard<SFile>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }
    void operator()(const rwl::TRwLockWriteGuard<SLink>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }

    public:
    static int Init() { return 0; };

    protected:
    template<typename T>
    static void Update(FieldType& field, const ParamType& param, const rwl::TRwLockWriteGuard<T>& var) { field = param; };

    protected:
    static FieldType SInfo::* s_pFieldPtr;
};

template<>
template<typename T>
void TSetParameter<mode_t, mode_t>::Update(mode_t& field, const mode_t& param, const rwl::TRwLockWriteGuard<T>& var) {
    field = param | AGetMode{}(var);
}

using ASetParent = TSetParameter<AWeakRwLock<SDirectory>, ASharedRwLock<SDirectory>>;
using ASetName = TSetParameter<std::string, std::string>;
using ASetMode = TSetParameter<mode_t, mode_t>;

struct SInfo {
    friend AGetName;
    friend AGetMode;
    friend AGetParent;
    friend ASetName;
    friend ASetMode;
    friend ASetParent;

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    AWeakRwLock<SDirectory> m_pParent;
};

template<typename T>
struct SInfoMixin : SInfo {
    friend struct SInfo;

    template<typename... Args>
    static ASharedRwLock<T> New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent, Args&&... args);
};

struct SDirectory : SInfoMixin<SDirectory> {
    friend struct SInfoMixin<SDirectory>;
    std::vector<ASharedFileVariant> Objects;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SDirectory>& var);
};

struct SFile : SInfoMixin<SFile> {
    friend struct SInfoMixin<SFile>;
    std::vector<char> Data;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SFile>& var);
};

struct SLink : SInfoMixin<SLink> {
    friend struct SInfoMixin<SLink>;
    std::filesystem::path LinkTo;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path);
};

template<typename T>
template<typename... Args>
ASharedRwLock<T> SInfoMixin<T>::New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent, Args&&... args) {
    const auto obj = MakeSharedRwLock<SDirectory>();
    const auto objWrite = obj->Write();
    ASetName{}(objWrite, name);
    ASetMode{}(objWrite, mode);
    T::DoNew(objWrite, std::forward<Args>(args)...);
    ASetParent{}(objWrite, parent);
    return obj;
}

}

#endif //CPPFUSE_TFILESYSTEMOBJECTS_HPP
