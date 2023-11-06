#ifndef CPPFUSE_TSETINFOPARAMETER_HPP
#define CPPFUSE_TSETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/ASharedFileVariant.hpp>
#include <CppFuse/Models/Objects/CFileObject.hpp>
#include <CppFuse/Models/Operations/TGetInfoType.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType, typename ParamType, typename Derived>
class TSetInfoParameter {
    public:
    TSetInfoParameter(const ParamType& param) : m_xParam{param} {}

    public:
    void operator()(const ASharedFileVariant& var) { std::visit(*this, var); };

    template<CFileObject T>
    void operator()(const ASharedRwLock<T>& var) { this->operator()(var->Write()); };

    // This method is specialized for "mode" field. Look at the end of the file.
    template<CFileObject T>
    void operator()(const rwl::TRwLockWriteGuard<T>& var) { GetField(var) = this->m_xParam; };

    protected:
    template<CFileObject T>
    inline FieldType& GetField(const rwl::TRwLockWriteGuard<T>& var) { return ((SInfo*)(var.Get()))->*s_Field; }

    protected:
    const ParamType& m_xParam;

    protected:
    static FieldType SInfo::* s_Field;
};

template<typename FieldType, typename ParamType, typename Derived>
FieldType SInfo::* TSetInfoParameter<FieldType, ParamType, Derived>::s_Field = nullptr;

#define DECLARE_CLASS(FieldType, ParamType, FieldName)\
    class TSetInfo##FieldName : public TSetInfoParameter<FieldType, ParamType, TSetInfo##FieldName> {\
        public:\
        static void Init();\
    };

    DECLARE_CLASS(std::string, std::string, Name)
    DECLARE_CLASS(mode_t, mode_t, Mode)
    DECLARE_CLASS(AWeakRwLock<SDirectory>, ASharedRwLock<SDirectory>, Parent)
    DECLARE_CLASS(uid_t, uid_t, Uid)
    DECLARE_CLASS(gid_t, gid_t, Gid)
    DECLARE_CLASS(time_t, time_t, ATime)
    DECLARE_CLASS(time_t, time_t, MTime)
    DECLARE_CLASS(time_t, time_t, CTime)
#undef DECLARE_CLASS

template<>
template<CFileObject T>
void TSetInfoParameter<mode_t, mode_t, TSetInfoMode>::operator()(const rwl::TRwLockWriteGuard<T>& var) {
    GetField(var) = this->m_xParam | TGetInfoType{}(var);
}




}

#endif //CPPFUSE_TSETINFOPARAMETER_HPP