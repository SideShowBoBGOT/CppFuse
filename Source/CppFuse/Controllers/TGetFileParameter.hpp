#ifndef CPPFUSE_TGETFILEPARAMETER_HPP
#define CPPFUSE_TGETFILEPARAMETER_HPP

#include "CppFuse/Models/TFileObjects.hpp"

namespace cppfuse {

template<typename FieldType, typename Derived>
class TGetFileParameter {
    public:
    TGetFileParameter()=default;

    public:
    const FieldType& operator()(const ASharedFileVariant& var) {
        return std::visit(*this, var);
    }
    const FieldType& operator()(const CSharedRwFileObject auto& var) {
        return reinterpret_cast<Derived*>(this)->operator()(var->Read());
    }
};

class TGetInfoName : public TGetFileParameter<std::string, TGetInfoName> {
    public:
    using TGetFileParameter<std::string, TGetInfoName>::operator();
    TGetInfoName()=default;
    const std::string& operator()(const CGuardFileObject auto& var) {
        return reinterpret_cast<const TFile<TDirectory>*>(var.GetPtr())->m_sName;
    }
    std::string& operator()(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr())->m_sName;
    }
};

class TGetInfoUid : public TGetFileParameter<uid_t, TGetInfoUid> {
    public:
    using TGetFileParameter<uid_t, TGetInfoUid>::operator();
    TGetInfoUid()=default;
    const uid_t& operator()(const CGuardFileObject auto& var) {
        return reinterpret_cast<const TFile<TDirectory>*>(var.GetPtr())->m_uUid;
    }
    uid_t& operator()(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr())->m_uUid;
    }
};

class TGetInfoGid : public TGetFileParameter<gid_t, TGetInfoGid> {
    public:
    using TGetFileParameter<gid_t, TGetInfoGid>::operator();
    TGetInfoGid()=default;
    const gid_t& operator()(const CGuardFileObject auto& var) {
        return reinterpret_cast<const TFile<TDirectory>*>(var.GetPtr())->m_uGid;
    }
    gid_t& operator()(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr())->m_uGid;
    }
};

class TGetInfoMode : public TGetFileParameter<mode_t, TGetInfoMode> {
    public:
    using TGetFileParameter<mode_t, TGetInfoMode>::operator();
    TGetInfoMode()=default;
    const mode_t& operator()(const CGuardFileObject auto& var) {
        return reinterpret_cast<const TFile<TDirectory>*>(var.GetPtr())->m_uMode;
    }
    mode_t& operator()(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr())->m_uMode;
    }
};

class TGetInfoParent : public TGetFileParameter<AWeakRwLock<TDirectory>, TGetInfoParent> {
    public:
    using TGetFileParameter<AWeakRwLock<TDirectory>, TGetInfoParent>::operator();
    TGetInfoParent()=default;
    const AWeakRwLock<TDirectory>& operator()(const CGuardFileObject auto& var) {
        return reinterpret_cast<const TFile<TDirectory>*>(var.GetPtr())->m_pParent;
    }
    AWeakRwLock<TDirectory>& operator()(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr())->m_pParent;
    }
};

}

#endif //CPPFUSE_TGETFILEPARAMETER_HPP
