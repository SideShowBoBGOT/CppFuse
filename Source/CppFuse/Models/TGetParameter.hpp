#ifndef CPPFUSE_TGETPARAMETER_HPP
#define CPPFUSE_TGETPARAMETER_HPP

#include <CppFuse/Models/ASharedFileVariant.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType>
class TGetParameter {
    public:
    const FieldType& operator()(const ASharedFileVariant& var) { return std::visit(TGetParameter{}, var); };
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
    static void Init() {};

    protected:
    static FieldType SInfo::* s_pFieldPtr;
};

using AGetName = TGetParameter<std::string>;
using AGetMode = TGetParameter<mode_t>;
using AGetParent = TGetParameter<AWeakRwLock<SDirectory>>;
using AGetUid = TGetParameter<uid_t>;
using AGetGid = TGetParameter<gid_t>;

}

#endif //CPPFUSE_TGETPARAMETER_HPP
