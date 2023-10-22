#include "TFile.hpp"

#include <sys/stat.h>

namespace cppfuse {

cppfuse::TFile::TFile(const std::string& name, mode_t mode)
    : TSpecializedObjectMixin(name, mode) {}

}



