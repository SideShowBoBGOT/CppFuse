#ifndef CPPFUSE_TSETFILEPARAMETER_HPP
#define CPPFUSE_TSETFILEPARAMETER_HPP

#include <CppFuse/Models/TFileObjects.hpp>
#include <CppFuse/Controllers/NSFileType.hpp>

namespace cppfuse {

template<typename ParamType, typename DerivedType>
class TSetInfoParameterMixin {
    public:
    TSetInfoParameterMixin(const ParamType& param) : m_xParam{param} {}
    void operator()(const ASharedFileVariant& var) { std::visit(*Self(), var); }

    protected:
    constexpr DerivedType* Self() { return reinterpret_cast<DerivedType*>(this); }
    TFile<TDirectory>* FileBase(CWriteGuardFileObject auto& var) {
        return reinterpret_cast<TFile<TDirectory>*>(var.GetPtr());
    }

    protected:
    const ParamType& m_xParam;
};

template<typename ParamType, typename DerivedType>
class TSetInfoParameterGeneralMixin : public TSetInfoParameterMixin<ParamType, DerivedType> {
    public:
    TSetInfoParameterGeneralMixin(const ParamType& param)
        : TSetInfoParameterMixin<ParamType, DerivedType>(param) {}

    public:
    using TSetInfoParameterMixin<ParamType, DerivedType>::operator();
    void operator()(const CSharedRwFileObject auto& var) {
        auto varWrite = var->Write();
        this->Self()->operator()(varWrite);
    }
};

class TSetInfoName : public TSetInfoParameterGeneralMixin<std::string, TSetInfoName> {
    public:
    TSetInfoName(const std::string& param)
        : TSetInfoParameterGeneralMixin<std::string, TSetInfoName>(param) {}
    using TSetInfoParameterGeneralMixin<std::string, TSetInfoName>::operator();
    void operator()(CWriteGuardFileObject auto& var) {
        this->FileBase(var)->m_sName = m_xParam;
    }
};

class TSetInfoUid : public TSetInfoParameterGeneralMixin<uid_t, TSetInfoUid> {
    public:
    TSetInfoUid(const uid_t& param)
        : TSetInfoParameterGeneralMixin<uid_t, TSetInfoUid>(param) {}
    using TSetInfoParameterGeneralMixin<uid_t, TSetInfoUid>::operator();
    void operator()(CWriteGuardFileObject auto& var) {
        this->FileBase(var)->m_uUid = m_xParam;
    }
};

class TSetInfoGid : public TSetInfoParameterGeneralMixin<gid_t, TSetInfoGid> {
    public:
    TSetInfoGid(const gid_t& param)
        : TSetInfoParameterGeneralMixin<gid_t, TSetInfoGid>(param) {}
    using TSetInfoParameterGeneralMixin<gid_t, TSetInfoGid>::operator();
    void operator()(CWriteGuardFileObject auto& var) {
        this->FileBase(var)->m_uGid = m_xParam;
    }
};

class TSetInfoMode : public TSetInfoParameterGeneralMixin<mode_t, TSetInfoMode> {
    public:
    TSetInfoMode(const mode_t& param)
        : TSetInfoParameterGeneralMixin<mode_t, TSetInfoMode>(param) {}
    using TSetInfoParameterGeneralMixin<mode_t, TSetInfoMode>::operator();
    void operator()(CWriteGuardFileObject auto& var) {
        this->FileBase(var)->m_uMode = m_xParam | NSFileType::Get(var);
    }
};

class TSetInfoParent : public TSetInfoParameterMixin<ASharedRwLock<TDirectory>, TSetInfoParent> {
    public:
    TSetInfoParent(const ASharedRwLock<TDirectory>& param)
        : TSetInfoParameterMixin<ASharedRwLock<TDirectory>, TSetInfoParent>(param) {}
    using TSetInfoParameterMixin<ASharedRwLock<TDirectory>, TSetInfoParent>::operator();
    void operator()(const CSharedRwFileObject auto& var) {
        {
            auto varWrite = var->Write();
            this->operator()(varWrite);
        }
        if(m_xParam) {
            auto writeParam = m_xParam->Write();
            writeParam->Files.push_back(var);
        }
    }

    protected:
    void operator()(CWriteGuardFileObject auto& var) {
        this->FileBase(var)->m_pParent = m_xParam;
    }
};

}

#endif //CPPFUSE_TSETFILEPARAMETER_HPP