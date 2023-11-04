#ifndef CPPFUSE_TSETPARAMETER_HPP
#define CPPFUSE_TSETPARAMETER_HPP

#include <CppFuse/Models/ASharedFileVariant.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType, typename ParamType>
class TSetParameter {
    public:
    void operator()(const ASharedFileVariant& var, const ParamType& param) { std::visit([&param](const auto& var) { TSetParameter{}(var, param); }, var); };
    void operator()(const ASharedRwLock<SDirectory>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const ASharedRwLock<SFile>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const ASharedRwLock<SLink>& var, const ParamType& param) { TSetParameter{}(var->Write(), param); };
    void operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }
    void operator()(const rwl::TRwLockWriteGuard<SFile>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }
    void operator()(const rwl::TRwLockWriteGuard<SLink>& var, const ParamType& param) { Update(((*var).*s_pFieldPtr), param, var); }

    public:
    static void Init() {};

    protected:
    template<typename T>
    static void Update(FieldType& field, const ParamType& param, const rwl::TRwLockWriteGuard<T>& var) { field = param; };

    protected:
    static FieldType SInfo::* s_pFieldPtr;
};

template<>
template<typename T>
void TSetParameter<mode_t, mode_t>::Update(mode_t& field, const mode_t& param, const rwl::TRwLockWriteGuard<T>& var) {
     field = param | 0777;
}

using ASetParent = TSetParameter<AWeakRwLock<SDirectory>, ASharedRwLock<SDirectory>>;
using ASetName = TSetParameter<std::string, std::string>;
using ASetMode = TSetParameter<mode_t, mode_t>;
using ASetUid = TSetParameter<uid_t, uid_t>;
using ASetGid = TSetParameter<gid_t, gid_t>;

}

#endif //CPPFUSE_TSETPARAMETER_HPP
