#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TFileSystemObject.hpp"

namespace cppfuse {

class TDirectory : TFileSystemObject {
    public:
    TDirectory(const std::string& name, mode_t mode);
    virtual void Mode(mode_t mode) override;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
