#ifndef CPPFUSE_TSETINFOPARAMETER_HPP
#define CPPFUSE_TSETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

template<typename ParamType>
class TSetInfoParameterMixin {
    public:
    TSetInfoParameterMixin(const ParamType& param) : m_Param{param} {}
    void operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

    protected:
    const ParamType& m_Param;
};

template<typename ParamType, typename DerivedType>
class TSetInfoParameterGeneralMixin : public TSetInfoParameterMixin<ParamType> {
    public:
    TSetInfoParameterGeneralMixin(const ParamType& param) : TSetInfoParameterMixin<ParamType>(param) {}

    public:
    void operator()(const CSharedRwFileObject auto& var) {
        auto writeObj = var->Write();
        static_cast<DerivedType*>(this)->operator()(var->Write());
    }
};

class TSetInfoName : public TSetInfoParameterGeneralMixin<std::string, TSetInfoName> {
    public:
    TSetInfoName(const std::string& param);
    void operator()(CWriteGuardFileObject auto& var);
};

class TSetInfoUid : public TSetInfoParameterGeneralMixin<uid_t, TSetInfoUid> {
    public:
    TSetInfoUid(const uid_t & param);
    void operator()(CWriteGuardFileObject auto& var);
};

class TSetInfoGid : public TSetInfoParameterGeneralMixin<gid_t, TSetInfoGid> {
    public:
    TSetInfoGid(const gid_t & param);
    void operator()(CWriteGuardFileObject auto& var);
};

class TSetInfoMode : public TSetInfoParameterGeneralMixin<uid_t, TSetInfoMode> {
    public:
    TSetInfoMode(const mode_t& param);
    void operator()(CWriteGuardFileObject auto& var);
};

class TSetInfoParent : public TSetInfoParameterMixin<ASharedRwLock<TDirectory>> {
    public:
    TSetInfoParent(const ASharedRwLock<TDirectory>& param);
    void operator()(const CSharedRwFileObject auto& var);

    protected:
    void operator()(CWriteGuardFileObject auto& var);
};

}

#endif //CPPFUSE_TSETINFOPARAMETER_HPP