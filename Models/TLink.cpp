#include "TLink.hpp"
#include <sys/stat.h>

namespace cppfuse {

cppfuse::TLink::TLink(const std::string& name, mode_t mode)
    : TFileSystemObject(name, mode | S_IFLNK) {}

void cppfuse::TLink::Mode(mode_t mode) {
    TFileSystemObject::Mode(mode | S_IFLNK);
}

}
