#include <CppFuse/Models/Operations/TGetAttributes.hpp>

namespace cppfuse {

TGetAttributes::TGetAttributes(struct stat* st) : m_pSt{st} {}

void TGetAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

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
