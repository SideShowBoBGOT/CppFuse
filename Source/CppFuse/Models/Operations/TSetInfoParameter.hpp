#ifndef CPPFUSE_TSETINFOPARAMETER_HPP
#define CPPFUSE_TSETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

template<typename ParamType>
class TSetInfoParameterMixin {
    public:
    TSetInfoParameterMixin(const ParamType& param) : m_xParam{param} {}
    void operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

    protected:
    const ParamType& m_xParam;
};

template<typename ParamType, typename DerivedType>
class TSetInfoParameterGeneralMixin : public TSetInfoParameterMixin<ParamType> {
    public:
    TSetInfoParameterGeneralMixin(const ParamType& param) : TSetInfoParameterMixin<ParamType>(param) {}

    public:
    using TSetInfoParameterMixin<ParamType>::operator();
    void operator()(const CSharedRwFileObject auto& var) {
        auto writeObj = var->Write();
        static_cast<DerivedType*>(this)->operator()(var->Write());
    }
};

#define DECLARE_CLASS(Name, ParamType)\
    class TSetInfo##Name : public TSetInfoParameterGeneralMixin<ParamType, TSetInfo##Name> {\
        public:\
        TSetInfo##Name(const ParamType& param); \
        using TSetInfoParameterGeneralMixin<ParamType, TSetInfo##Name>::operator();\
        void operator()(CWriteGuardFileObject auto& var);\
    };

    DECLARE_CLASS(Name, std::string)
    DECLARE_CLASS(Uid, uid_t)
    DECLARE_CLASS(Gid, gid_t)
    DECLARE_CLASS(Mode, mode_t)
#undef DECLARE_CLASS


class TSetInfoParent : public TSetInfoParameterMixin<ASharedRwLock<TDirectory>> {
    public:
    TSetInfoParent(const ASharedRwLock<TDirectory>& param);
    using TSetInfoParameterMixin<ASharedRwLock<TDirectory>>::operator();
    void operator()(const CSharedRwFileObject auto& var);

    protected:
    void operator()(CWriteGuardFileObject auto& var);
};

}

#endif //CPPFUSE_TSETINFOPARAMETER_HPP