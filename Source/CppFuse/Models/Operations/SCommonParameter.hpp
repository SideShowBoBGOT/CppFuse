#ifndef CPPFUSE_SCOMMONPARAMETER_HPP
#define CPPFUSE_SCOMMONPARAMETER_HPP

#include <CppFuse/Models/Objects/ASharedFileVariant.hpp>

namespace cppfuse {

struct SInfo;

template<typename FieldType, typename Derived>
struct SCommonParameter {
    using InnerType = FieldType;
    static void Init() { Derived::DoInit(); };

    protected:
    static FieldType SInfo::* s_pFieldPtr;
};

#define DECLARE_STRUCT(Name, FieldType)\
    struct SCommonParameter##Name : SCommonParameter<FieldType, SCommonParameter##Name> { \
        friend struct SCommonParameter<FieldType, SCommonParameter##Name>;                \
        protected:                                                                        \
        static void DoInit();                                                             \
    };\

    DECLARE_STRUCT(Parent, AWeakRwLock<SDirectory>);
    DECLARE_STRUCT(Name, std::string);
    DECLARE_STRUCT(Mode, mode_t);
    DECLARE_STRUCT(Uid, uid_t);
    DECLARE_STRUCT(Gid, gid_t);

#undef DECLARE_STRUCT

}

#endif //CPPFUSE_SCOMMONPARAMETER_HPP
