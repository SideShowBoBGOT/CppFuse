#ifndef CPPFUSE_SGETPARAMETER_HPP
#define CPPFUSE_SGETPARAMETER_HPP

#include <CppFuse/Models/Operations/SCommonParameter.hpp>
#include <CppFuse/Models/Objects/CFileObject.hpp>

namespace cppfuse {

template<typename Base>
struct SGetParameter : Base {
    const Base::InnerType& operator()(const ASharedFileVariant& var) { return std::visit(*this, var); };

    template<CFileObject T>
    const Base::InnerType& operator()(const ASharedRwLock<T>& var) { this->operator()(var->Read()); }

    template<CFileObject T>
    const Base::InnerType& operator()(const rwl::TRwLockReadGuard<T>& var) { return ((const SInfo*)(var.Get()))->*Base::s_pFieldPtr; }

    template<CFileObject T>
    Base::InnerType& operator()(const rwl::TRwLockWriteGuard<T>& var) { return ((SInfo*)(var.Get()))->*Base::s_pFieldPtr; }
};

#define DECLARE_STRUCT(Name) using AGet##Name = SGetParameter<SCommonParameter##Name>;
    DECLARE_STRUCT(Name)
    DECLARE_STRUCT(Mode)
    DECLARE_STRUCT(Parent)
    DECLARE_STRUCT(Uid)
    DECLARE_STRUCT(Gid)
#undef DECLARE_STRUCT

}

#endif //CPPFUSE_SGETPARAMETER_HPP
