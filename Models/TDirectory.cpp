#include "TDirectory.hpp"
#include <sys/stat.h>

namespace cppfuse {

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode)
    : TFileSystemObject(name, mode | S_IFDIR) {}

void cppfuse::TDirectory::Mode(mode_t mode) {
    TFileSystemObject::Mode(mode | S_IFDIR);
}

}
