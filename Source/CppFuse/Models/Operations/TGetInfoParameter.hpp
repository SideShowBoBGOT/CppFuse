#ifndef CPPFUSE_TGETINFOPARAMETER_HPP
#define CPPFUSE_TGETINFOPARAMETER_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

template<typename FieldType, typename Derived>
class TGetInfoParameter {
    public:
    TGetInfoParameter()=default;

    public:
    const FieldType& operator()(const ASharedFileVariant& var) const { return std::visit(*this, var); }
    const FieldType& operator()(const CSharedRwFileObject auto& var) const { return static_cast<const Derived*>(this)->operator()(var->Read()); }
};

#define DECLARE_CLASS(Name, FieldType)\
    class TGetInfo##Name : public TGetInfoParameter<FieldType, TGetInfo##Name> {\
        public:\
        using TGetInfoParameter<FieldType, TGetInfo##Name>::operator();\
        TGetInfo##Name()=default;\
        const FieldType& operator()(const CReadGuardFileObject auto& var) const;\
        FieldType& operator()(const CWriteGuardFileObject auto& var) const;\
    };

    DECLARE_CLASS(Name, std::string)
    DECLARE_CLASS(Uid, uid_t)
    DECLARE_CLASS(Gid, gid_t)
    DECLARE_CLASS(Mode, mode_t)
    DECLARE_CLASS(Parent, AWeakRwLock<TDirectory>)
#undef DECLARE_CLASS

}

#endif //CPPFUSE_TGETINFOPARAMETER_HPP
