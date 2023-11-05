#ifndef CPPFUSE_SSETPARAMETER_HPP
#define CPPFUSE_SSETPARAMETER_HPP

#include <CppFuse/Models/Operations/SCommonParameter.hpp>
#include <CppFuse/Models/Objects/CFileObject.hpp>

namespace cppfuse {

struct SInfo;

template<typename ParamType, typename Base>
struct SSetParameter : Base {
    SSetParameter(const ParamType& param) : m_xParam{m_xParam} {}

    public:
    void operator()(const ASharedFileVariant& var) { std::visit(*this, var); };

    template<CFileObject T>
    void operator()(const ASharedRwLock<T>& var) { this->operator()(var->Write()); };

    template<CFileObject T>
    void operator()(const rwl::TRwLockWriteGuard<T>& var) { ((SInfo*)(var.Get()))->*Base::s_pFieldPtr = this->m_xParam; };

    protected:
    const ParamType& m_xParam;
};

#define DECLARE_STRUCT(ParamType, Name) using ASet##Name = SSetParameter<ParamType, SCommonParameter##Name>;
    DECLARE_STRUCT(std::string, Name)
    DECLARE_STRUCT(mode_t, Mode)
    DECLARE_STRUCT(ASharedRwLock<SDirectory>, Parent)
    DECLARE_STRUCT(uid_t, Uid)
    DECLARE_STRUCT(gid_t, Gid)
#undef DECLARE_STRUCT

}

#endif //CPPFUSE_SSETPARAMETER_HPP