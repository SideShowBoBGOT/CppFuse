#include <CppFuse/Models/Operations/TSetInfoParameter.hpp>
#include <CppFuse/Models/Objects/SDirectory.hpp>
#include <CppFuse/Models/Operations/TGetInfoType.hpp>

namespace cppfuse {

TSetInfoName::TSetInfoName(const std::string& param) : m_Param{param} {}
void TSetInfoName::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }
void TSetInfoName::operator()(const CSharedRwFileObject auto& var) { this->operator()(var->Write()); }
void TSetInfoName::operator()(const CWriteGuardFileObject auto& var) { ((SInfo*)var.Get())->m_Name = m_Param; }

TSetInfoUid::TSetInfoUid(const uid_t& param) : m_Param{param} {}
void TSetInfoUid::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }
void TSetInfoUid::operator()(const CSharedRwFileObject auto& var) { this->operator()(var->Write()); }
void TSetInfoUid::operator()(const CWriteGuardFileObject auto& var) { ((SInfo*)var.Get())->m_Uid = m_Param; }

TSetInfoGid::TSetInfoGid(const uid_t& param) : m_Param{param} {}
void TSetInfoGid::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }
void TSetInfoGid::operator()(const CSharedRwFileObject auto& var) { this->operator()(var->Write()); }
void TSetInfoGid::operator()(const CWriteGuardFileObject auto& var) { ((SInfo*)var.Get())->m_Gid = m_Param; }

TSetInfoMode::TSetInfoMode(const mode_t& param) : m_Param{param} {}
void TSetInfoMode::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }
void TSetInfoMode::operator()(const CSharedRwFileObject auto& var) { this->operator()(var->Write()); }
void TSetInfoMode::operator()(const CWriteGuardFileObject auto& var) { ((SInfo*)var.Get())->m_Mode = m_Param | TGetInfoType{}(var); }

TSetInfoParent::TSetInfoParent(const ASharedRwLock<SDirectory>& param) : m_Param{param} {}
void TSetInfoParent::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }
void TSetInfoParent::operator()(const CSharedRwFileObject auto& var) {
    this->operator()(var->Write());
    if(m_Param) {
        m_Param->Write()->Objects.push_back(var);
    }
}
void TSetInfoParent::operator()(const CWriteGuardFileObject auto& var) { ((SInfo*)var.Get())->m_Parent = m_Param; }



}