#include <CppFuse/Models/TDirectory.hpp>

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent)
    : AFileObject(name, mode, parent) {}

NFileType TDirectory::Type() const { return NFileType::Directory; }

const std::vector<ASharedRwLock<AFileObject>>& TDirectory::FileObjects() const { return m_vObjects; }

}
