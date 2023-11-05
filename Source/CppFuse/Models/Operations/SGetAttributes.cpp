#include <CppFuse/Models/Operations/SGetAttributes.hpp>
#include <CppFuse/Models/Operations/SGetParameter.hpp>
#include <CppFuse/Models/Objects/SFile.hpp>
#include <CppFuse/Models/Objects/SLink.hpp>

namespace cppfuse {

SGetAttributes::SGetAttributes(struct stat* st) : m_pSt{st} {}

void SGetAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void SGetAttributes::operator()(const ASharedRwLock<SDirectory>& var) { UpdateAttr(var); }

void SGetAttributes::operator()(const ASharedRwLock<SFile>& var) { UpdateAttr(var); }

void SGetAttributes::operator()(const ASharedRwLock<SLink>& var) { UpdateAttr(var); }

void SGetAttributes::UpdateAttr(const auto& var) {
    const auto varRead = var->Read();
    UpdateGeneralAttr(varRead);
    UpdateSize(varRead);
    m_pSt->st_nlink = static_cast<nlink_t>(var.use_count());
}

void SGetAttributes::UpdateGeneralAttr(const auto& varRead) {
    m_pSt->st_mode = AGetMode{}(varRead);
    m_pSt->st_gid = AGetGid{}(varRead);
    m_pSt->st_uid = AGetUid{}(varRead);
}

void SGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SDirectory>& varRead) {}

void SGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SFile>& varRead) {
    m_pSt->st_size = static_cast<off_t>(varRead->Data.size());
}

void SGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<SLink>& varRead) {
    m_pSt->st_size = static_cast<off_t>(std::string_view(varRead->LinkTo.c_str()).size());
}

}
