#include <CppFuse/Models/Operations/SCommonParameter.hpp>
#include <CppFuse/Models/Objects/SInfo.hpp>

namespace cppfuse {

#define DEFINE_STRUCT(Name, FieldType, FieldName)\
    template<> FieldType SInfo::* SCommonParameter<FieldType, SCommonParameter##Name>::s_pFieldPtr = nullptr;\
    void SCommonParameter##Name::DoInit() { s_pFieldPtr = &SInfo::FieldName; }

    DEFINE_STRUCT(Parent, AWeakRwLock<SDirectory>, m_pParent);
    DEFINE_STRUCT(Name, std::string, m_sName);
    DEFINE_STRUCT(Mode, mode_t, m_uMode);
    DEFINE_STRUCT(Uid, uid_t, m_uUid);
    DEFINE_STRUCT(Gid, gid_t, m_uGid);

#undef DEFINE_STRUCT


}