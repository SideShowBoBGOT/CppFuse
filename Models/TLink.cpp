#include "TLink.hpp"
#include <sys/stat.h>

namespace cppfuse {

cppfuse::TLink::TLink(const std::string& name, mode_t mode)
    : TSpecializedObjectMixin(name, mode) {}

}
