#include <CppFuse/Models/TDirectory.hpp>

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const TSharedRwLock<TDirectory>& parent)
    : TFileObject(name, mode, parent) {}

NFileType TDirectory::Type() const { return NFileType::Directory; }

const std::vector<TSharedRwLock<TFileObject>>& TDirectory::FileObjects() const { return m_vObjects; }

}
