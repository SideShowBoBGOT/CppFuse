#ifndef CPPFUSE_TGETINFOPARAMETER_HPP
#define CPPFUSE_TGETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

template<typename FieldType, typename Derived>
class TGetInfoParameter {
    public:
    TGetInfoParameter()=default;

    public:
    const FieldType& operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
    const FieldType& operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
    const FieldType& operator()(const CReadGuardFileObject auto& var) { return static_cast<const Derived&>(*this).operator()(var); }
    FieldType& operator()(const CWriteGuardFileObject auto& var) { return static_cast<Derived&>(*this).operator()(var); }
};

#define DECLARE_CLASS(Name, FieldType)\
    class TGetInfo##Name : public TGetInfoParameter<FieldType, TGetInfo##Name> {\
        public:\
        TGetInfo##Name()=default;\
        const FieldType& operator()(const CReadGuardFileObject auto& var);\
        FieldType& operator()(const CWriteGuardFileObject auto& var);\
    };

    DECLARE_CLASS(Name, std::string)
    DECLARE_CLASS(Uid, uid_t)
    DECLARE_CLASS(Gid, gid_t)
    DECLARE_CLASS(Mode, mode_t)
    DECLARE_CLASS(Parent, AWeakRwLock<TDirectory>)
#undef DECLARE_CLASS

}

#endif //CPPFUSE_TGETINFOPARAMETER_HPP
