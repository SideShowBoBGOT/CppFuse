#include <CppFuse/Models/TDirectory.hpp>

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent)
    : TFileObjectMixin<TDirectory, NFileType::Directory>(name, mode, parent) {}

const std::vector<ASharedFileVariant>& TDirectory::FileObjects() const { return m_vObjects; }

}
