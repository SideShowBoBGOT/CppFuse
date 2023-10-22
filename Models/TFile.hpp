#ifndef CPPFUSE_TFILE_HPP
#define CPPFUSE_TFILE_HPP

#include "TFileSystemObject.hpp"

namespace cppfuse {

class TFile : public TFileSystemObject {
    public:
    TFile(const std::string& name, mode_t mode);
    virtual void Mode(mode_t mode) override;
};

}




#endif //CPPFUSE_TFILE_HPP
