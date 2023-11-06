#ifndef CPPFUSE_TGETINFOPARAMETER_HPP
#define CPPFUSE_TGETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/ASharedFileVariant.hpp>
#include <CppFuse/Models/Objects/CFileObject.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType>
class TGetInfoParameter {
    public:
    const FieldType& operator()(const ASharedFileVariant& var) { return std::visit(*this, var); };

    template<CFileObject T>
    const FieldType& operator()(const ASharedRwLock<T>& var) { this->operator()(var->Read()); }

    template<CFileObject T>
    const FieldType& operator()(const rwl::TRwLockReadGuard<T>& var) { return ((const SInfo*)(var.Get()))->*s_Field; }

    template<CFileObject T>
    FieldType& operator()(const rwl::TRwLockWriteGuard<T>& var) { return ((SInfo*)(var.Get()))->*s_Field; }

    protected:
    static FieldType SInfo::* s_Field;
};

template<typename FieldType>
FieldType SInfo::* TGetInfoParameter<FieldType>::s_Field = nullptr;

#define DECLARE_CLASS(FieldType, FieldName)\
    class TGetInfo##FieldName : public TGetInfoParameter<FieldType> {\
        public:\
        static void Init();\
    };

    DECLARE_CLASS(std::string, Name)
    DECLARE_CLASS(mode_t, Mode)
    DECLARE_CLASS(AWeakRwLock<SDirectory>, Parent)
    DECLARE_CLASS(uid_t, Uid)
    DECLARE_CLASS(gid_t, Gid)
#undef DECLARE_CLASS



}

#endif //CPPFUSE_TGETINFOPARAMETER_HPP
