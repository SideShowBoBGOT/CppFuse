#include "TFile.hpp"

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent)
    : TFileObjectMixin<TDirectory, NFileType::File>(name, mode, parent) {}

std::vector<char>& TFile::Content() { return m_vContent; }
const std::vector<char>& TFile::Content() const { return m_vContent; }

}



