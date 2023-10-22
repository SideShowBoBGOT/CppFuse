#include "TLink.hpp"
#include <sys/stat.h>

namespace cppfuse {

cppfuse::TLink::TLink(const std::string& name, mode_t mode, const std::filesystem::path& linkTo)
    : TSpecializedObjectMixin(name, mode), m_xLinkTo{linkTo} {}

const std::filesystem::path& TLink::LinkTo() const { return m_xLinkTo; }

}
