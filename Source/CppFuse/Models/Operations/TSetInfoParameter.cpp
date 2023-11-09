#include <CppFuse/Models/Operations/TSetInfoParameter.hpp>
#include <CppFuse/Models/Operations/TGetInfoType.hpp>

namespace cppfuse {

TSetInfoName::TSetInfoName(const std::string& param) : TSetInfoParameterGeneralMixin<std::string, TSetInfoName>(param) {}
void TSetInfoName::operator()(CWriteGuardFileObject auto& var) { ((TInfo<TDirectory>*)var.Get())->m_sName = m_Param; }

TSetInfoUid::TSetInfoUid(const uid_t& param) : TSetInfoParameterGeneralMixin<uid_t, TSetInfoUid>(param) {}
void TSetInfoUid::operator()(CWriteGuardFileObject auto& var) { ((TInfo<TDirectory>*)var.Get())->m_uUid = m_Param; }

TSetInfoGid::TSetInfoGid(const uid_t& param) : TSetInfoParameterGeneralMixin<gid_t, TSetInfoGid>(param) {}
void TSetInfoGid::operator()(CWriteGuardFileObject auto& var) { ((TInfo<TDirectory>*)var.Get())->m_uGid = m_Param; }

TSetInfoMode::TSetInfoMode(const mode_t& param) : TSetInfoParameterGeneralMixin<uid_t, TSetInfoMode>(param) {}
void TSetInfoMode::operator()(CWriteGuardFileObject auto& var) { ((TInfo<TDirectory>*)var.Get())->m_uMode = m_Param | TGetInfoType{}(var); }

TSetInfoParent::TSetInfoParent(const ASharedRwLock<TDirectory>& param) : TSetInfoParameterMixin<ASharedRwLock<TDirectory>>(param) {}

void TSetInfoParent::operator()(const CSharedRwFileObject auto& var) {
    static_cast<TSetInfoParent*>(this)->operator()(var->Write());
    if(m_Param) {
        m_Param->Write()->Objects.push_back(var);
    }
}

void TSetInfoParent::operator()(CWriteGuardFileObject auto& var) { ((TInfo<TDirectory>*)var.Get())->m_pParent = m_Param; }

}