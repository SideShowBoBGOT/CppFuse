#ifndef CPPFUSE_TGETINFOPARAMETER_HPP
#define CPPFUSE_TGETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

template<typename FieldType, typename Derived>
class TGetInfoParameter {
    public:
    TGetInfoParameter()=default;

    public:
    const FieldType& operator()(const ASharedFileVariant& var) {
        return std::visit(*this, var);
    }
    const FieldType& operator()(const CSharedRwFileObject auto& var) {
        return reinterpret_cast<Derived*>(this)->operator()(var->Read());
    }
};

class TGetInfoName : public TGetInfoParameter<std::string, TGetInfoName> {
    public:
    using TGetInfoParameter<std::string, TGetInfoName>::operator();
    TGetInfoName()=default;
    const std::string& operator()(const CReadGuardFileObject auto& var) {
        return reinterpret_cast<const TInfo<TDirectory>*>(var.GetPtr())->m_sName;
    }
    std::string& operator()(const CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TInfo<TDirectory>*>(var.GetPtr())->m_sName;
    }
};

class TGetInfoUid : public TGetInfoParameter<uid_t, TGetInfoUid> {
    public:
    using TGetInfoParameter<uid_t, TGetInfoUid>::operator();
    TGetInfoUid()=default;
    const uid_t& operator()(const CReadGuardFileObject auto& var) {
        return reinterpret_cast<const TInfo<TDirectory>*>(var.GetPtr())->m_uUid;
    }
    uid_t& operator()(const CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TInfo<TDirectory>*>(var.GetPtr())->m_uUid;
    }
};

class TGetInfoGid : public TGetInfoParameter<gid_t, TGetInfoGid> {
    public:
    using TGetInfoParameter<gid_t, TGetInfoGid>::operator();
    TGetInfoGid()=default;
    const gid_t& operator()(const CReadGuardFileObject auto& var) {
        return reinterpret_cast<const TInfo<TDirectory>*>(var.GetPtr())->m_uGid;
    }
    gid_t& operator()(const CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TInfo<TDirectory>*>(var.GetPtr())->m_uGid;
    }
};

class TGetInfoMode : public TGetInfoParameter<mode_t, TGetInfoMode> {
    public:
    using TGetInfoParameter<mode_t, TGetInfoMode>::operator();
    TGetInfoMode()=default;
    const mode_t& operator()(const CReadGuardFileObject auto& var) {
        return reinterpret_cast<const TInfo<TDirectory>*>(var.GetPtr())->m_uMode;
    }
    mode_t& operator()(const CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TInfo<TDirectory>*>(var.GetPtr())->m_uMode;
    }
};

class TGetInfoParent : public TGetInfoParameter<AWeakRwLock<TDirectory>, TGetInfoParent> {
    public:
    using TGetInfoParameter<AWeakRwLock<TDirectory>, TGetInfoParent>::operator();
    TGetInfoParent()=default;
    const AWeakRwLock<TDirectory>& operator()(const CReadGuardFileObject auto& var) {
        return reinterpret_cast<const TInfo<TDirectory>*>(var.GetPtr())->m_pParent;
    }
    AWeakRwLock<TDirectory>& operator()(const CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TInfo<TDirectory>*>(var.GetPtr())->m_pParent;
    }
};

}

#endif //CPPFUSE_TGETINFOPARAMETER_HPP
