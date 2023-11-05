#include "TGetAttributes.hpp"
#include "SGetParameter.hpp"

namespace cppfuse {

TGetAttributes::TGetAttributes(struct stat* st) : m_pSt{st} {}

void TGetAttributes::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void TGetAttributes::operator()(const ASharedRwLock<SDirectory>& var) {
    UpdateAttr(var);
}

void TGetAttributes::operator()(const ASharedRwLock<SFile>& var) {
    UpdateAttr(var);
}

void TGetAttributes::operator()(const ASharedRwLock<SLink>& var) {
    UpdateAttr(var);
}

void TGetAttributes::UpdateAttr(const auto& var) {
    auto g = AGetMode{}(var);
}


}
