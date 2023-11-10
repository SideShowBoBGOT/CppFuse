#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>

namespace cppfuse {

const std::string& TGetInfoName::operator()(const CReadGuardFileObject auto& var) const { return ((const TInfo<TDirectory>*)var.Get())->m_sName; }
std::string& TGetInfoName::operator()(const CWriteGuardFileObject auto& var) const { return ((TInfo<TDirectory>*)var.Get())->m_sName; }

const uid_t& TGetInfoUid::operator()(const CReadGuardFileObject auto& var) const { return ((const TInfo<TDirectory>*)var.Get())->m_uUid; }
uid_t& TGetInfoUid::operator()(const CWriteGuardFileObject auto& var) const { return ((TInfo<TDirectory>*)var.Get())->m_uUid; }

const gid_t& TGetInfoGid::operator()(const CReadGuardFileObject auto& var) const { return ((const TInfo<TDirectory>*)var.Get())->m_uGid; }
gid_t& TGetInfoGid::operator()(const CWriteGuardFileObject auto& var) const { return ((TInfo<TDirectory>*)var.Get())->m_uGid; }

const mode_t& TGetInfoMode::operator()(const CReadGuardFileObject auto& var) const { return ((const TInfo<TDirectory>*)var.Get())->m_uMode; }
mode_t& TGetInfoMode::operator()(const CWriteGuardFileObject auto& var) const { return ((TInfo<TDirectory>*)var.Get())->m_uMode; }

const AWeakRwLock<TDirectory>& TGetInfoParent::operator()(const CReadGuardFileObject auto& var) const { return ((const TInfo<TDirectory>*)var.Get())->m_pParent; }
AWeakRwLock<TDirectory>& TGetInfoParent::operator()(const CWriteGuardFileObject auto& var) const { return ((TInfo<TDirectory>*)var.Get())->m_pParent; }

}
