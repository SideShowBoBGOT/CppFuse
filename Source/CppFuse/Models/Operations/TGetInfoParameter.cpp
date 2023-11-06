#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <CppFuse/Models/Objects/SInfo.hpp>

namespace cppfuse {

const std::string& TGetInfoName::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
const std::string& TGetInfoName::operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
const std::string& TGetInfoName::operator()(const CReadGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Name; }
std::string& TGetInfoName::operator()(const CWriteGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Name; }

const uid_t& TGetInfoUid::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
const uid_t& TGetInfoUid::operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
const uid_t& TGetInfoUid::operator()(const CReadGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Uid; }
uid_t& TGetInfoUid::operator()(const CWriteGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Uid; }

const gid_t& TGetInfoGid::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
const gid_t& TGetInfoGid::operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
const gid_t& TGetInfoGid::operator()(const CReadGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Gid; }
gid_t& TGetInfoGid::operator()(const CWriteGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Gid; }

const mode_t& TGetInfoMode::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
const mode_t& TGetInfoMode::operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
const mode_t& TGetInfoMode::operator()(const CReadGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Mode; }
mode_t& TGetInfoMode::operator()(const CWriteGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Mode; }

const AWeakRwLock<SDirectory>& TGetInfoParent::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
const AWeakRwLock<SDirectory>& TGetInfoParent::operator()(const CSharedRwFileObject auto& var) { return operator()(var->Read()); }
const AWeakRwLock<SDirectory>& TGetInfoParent::operator()(const CReadGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Parent; }
AWeakRwLock<SDirectory>& TGetInfoParent::operator()(const CWriteGuardFileObject auto& var) { return ((SInfo*)var.Get())->m_Parent; }

}
