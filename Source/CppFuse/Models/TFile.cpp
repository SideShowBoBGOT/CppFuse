#include "TFile.hpp"

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode, const TSharedRwLock<TDirectory>& parent)
    : TFileObject(name, mode, parent) {}

NFileType TFile::Type() const { return NFileType::File; }

const std::vector<char>& TFile::Content() const { return m_vContent; }

}



