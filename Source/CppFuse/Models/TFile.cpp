#include "TFile.hpp"

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent)
    : TFileObjectMixin<TDirectory, NFileType::File>(name, mode, parent) {}

const std::vector<char>& TFile::Content() const { return m_vContent; }

void TFile::FillAttributes(struct stat* st) const {
    TFileObjectMixin<TDirectory, NFileType::File>::FillAttributes(st);
    st->st_nlink = 1;
    st->st_size = static_cast<off_t>(Content().size());
}

}



