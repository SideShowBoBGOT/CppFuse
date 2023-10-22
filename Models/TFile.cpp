#include "TFile.hpp"

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode)
    : TSpecializedObjectMixin(name, mode) {}

const std::vector<char>& TFile::Content() const { return m_vContent; }

}



