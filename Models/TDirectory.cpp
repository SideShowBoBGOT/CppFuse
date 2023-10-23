#include "TDirectory.hpp"

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent)
    : TSpecializedObjectMixin(name, mode, parent) {}

const std::vector<rppsync::TSharedRw<TFileObject>>& TDirectory::Objects() const { return m_vObjects; }

}
