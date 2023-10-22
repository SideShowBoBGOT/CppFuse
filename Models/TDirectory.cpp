#include "TDirectory.hpp"
#include <sys/stat.h>

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode)
    : TSpecializedObjectMixin(name, mode) {}

const std::vector<TRwObject>& TDirectory::Objects() const { return m_vObjects; }

}
