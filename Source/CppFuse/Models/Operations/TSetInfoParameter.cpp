#include <CppFuse/Models/Operations/TSetInfoParameter.hpp>
#include <CppFuse/Models/Objects/SInfo.hpp>

namespace cppfuse {

#define DEFINE_CLASS(FieldName) void TSetInfo##FieldName::Init() { s_Field = &SInfo::m_##FieldName; }
    DEFINE_CLASS(Name)
    DEFINE_CLASS(Mode)
    DEFINE_CLASS(Parent)
    DEFINE_CLASS(Uid)
    DEFINE_CLASS(Gid)
    DEFINE_CLASS(ATime)
    DEFINE_CLASS(MTime)
    DEFINE_CLASS(CTime)
#undef DEFINE_CLASS

}