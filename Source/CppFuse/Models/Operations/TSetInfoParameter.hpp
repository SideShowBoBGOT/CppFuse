#ifndef CPPFUSE_TSETINFOPARAMETER_HPP
#define CPPFUSE_TSETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/ASharedFileVariant.hpp>
#include <CppFuse/Models/Objects/CFileObject.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType, typename ParamType>
class TSetInfoParameter {
    public:
    TSetInfoParameter(const ParamType& param) : m_xParam{param} {}

    public:
    void operator()(const ASharedFileVariant& var) { std::visit(*this, var); };

    template<CFileObject T>
    void operator()(const ASharedRwLock<T>& var) { this->operator()(var->Write()); };

    template<CFileObject T>
    void operator()(const rwl::TRwLockWriteGuard<T>& var) { ((SInfo*)(var.Get()))->*s_Field = this->m_xParam; };

    protected:
    const ParamType& m_xParam;

    protected:
    static FieldType SInfo::* s_Field;
};

template<typename FieldType, typename ParamType>
FieldType SInfo::* TSetInfoParameter<FieldType, ParamType>::s_Field = nullptr;

#define DECLARE_CLASS(FieldType, ParamType, FieldName)\
    class TSetInfo##FieldName : public TSetInfoParameter<FieldType, ParamType> {\
        public:\
        static void Init();\
    };

    DECLARE_CLASS(std::string, std::string, Name)
    DECLARE_CLASS(mode_t, mode_t, Mode)
    DECLARE_CLASS(AWeakRwLock<SDirectory>, ASharedRwLock<SDirectory>, Parent)
    DECLARE_CLASS(uid_t, uid_t, Uid)
    DECLARE_CLASS(gid_t, gid_t, Gid)
#undef DECLARE_CLASS

}

#endif //CPPFUSE_TSETINFOPARAMETER_HPP