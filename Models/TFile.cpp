#include "TFile.hpp"

#include <sys/stat.h>

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode)
    : TFileSystemObject(name, mode | S_IFREG) {}

void cppfuse::TFile::Mode(mode_t mode) {
    TFileSystemObject::Mode(mode | S_IFREG);
}

}



