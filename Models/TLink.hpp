#ifndef CPPFUSE_TLINK_HPP
#define CPPFUSE_TLINK_HPP

#include "TFileSystemObject.hpp"

namespace cppfuse {

class TLink : TFileSystemObject {
    public:
    TLink(const std::string& name, mode_t mode);
    virtual void Mode(mode_t mode) override;
};

}

#endif //CPPFUSE_TLINK_HPP
