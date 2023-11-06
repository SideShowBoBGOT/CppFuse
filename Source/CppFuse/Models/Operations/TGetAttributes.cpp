#include <CppFuse/Models/Operations/TGetAttributes.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <CppFuse/Models/Objects/SFile.hpp>
#include <CppFuse/Models/Objects/SLink.hpp>

namespace cppfuse {

TGetAttributes::TGetAttributes(struct stat* st) : m_pSt{st} {}

void TGetAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void TGetAttributes::operator()(const ASharedRwLock<SDirectory>& var) { UpdateAttr(var); }

void TGetAttributes::operator()(const ASharedRwLock<SFile>& var) { UpdateAttr(var); }

void TGetAttributes::operator()(const ASharedRwLock<SLink>& var) { UpdateAttr(var); }

void TGetAttributes::UpdateAttr(const auto& var) {
    const auto varRead = var->Read();
    UpdateGeneralAttr(varRead);
    UpdateSize(varRead);
    m_pSt->st_nlink = static_cast<nlink_t>(var.use_count());
}

void TGetAttributes::UpdateGeneralAttr(const auto& varRead) {
    m_pSt->st_mode = TGetInfoMode{}(varRead);
    m_pSt->st_gid = TGetInfoGid{}(varRead);
    m_pSt->st_uid = TGetInfoUid{}(varRead);
}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SDirectory>& varRead) {}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SFile>& varRead) {
    m_pSt->st_size = static_cast<off_t>(varRead->Data.size());
}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SLink>& varRead) {
    m_pSt->st_size = static_cast<off_t>(std::string_view(varRead->LinkTo.c_str()).size());
}

}