#include <CppFuse/Models/Operations/TGetAttributes.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <CppFuse/Models/Operations/TGetInfoType.hpp>

namespace cppfuse {

TGetAttributes::TGetAttributes(struct stat* st) : m_pSt{st} {}

void TGetAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void TGetAttributes::operator()(const CSharedRwFileObject auto& var) {
    const auto varRead = var->Read();
    m_pSt->st_mode = TGetInfoMode{}(varRead);
    m_pSt->st_gid = TGetInfoGid{}(varRead);
    m_pSt->st_uid = TGetInfoUid{}(varRead);
    m_pSt->st_nlink = var.use_count();
    UpdateSize(varRead);
}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<TDirectory>& varRead) {
    m_pSt->st_size = 0;
}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<TFile>& varRead) {
    m_pSt->st_size = static_cast<off_t>(varRead->Data.size());
}

void TGetAttributes::UpdateSize(const rwl::TRwLockReadGuard<TLink>& varRead) {
    m_pSt->st_size = static_cast<off_t>(std::string_view(varRead->LinkTo.c_str()).size());
}

}
