#include "TGetFileAttributes.hpp"

namespace cppfuse {

TGetFileAttributes::TGetFileAttributes(struct stat* st) : m_pSt{st} {}

void TGetFileAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void TGetFileAttributes::UpdateSize(const rwl::TRwLockReadGuard<TDirectory>& varRead) {
    m_pSt->st_size = 0;
}

void TGetFileAttributes::UpdateSize(const rwl::TRwLockReadGuard<TRegularFile>& varRead) {
    m_pSt->st_size = static_cast<off_t>(varRead->Data.size());
}

void TGetFileAttributes::UpdateSize(const rwl::TRwLockReadGuard<TLink>& varRead) {
    m_pSt->st_size = static_cast<off_t>(std::string_view(varRead->LinkTo.c_str()).size());
}

}
