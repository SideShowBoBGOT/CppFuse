#ifndef CPPFUSE_TFILE_HPP
#define CPPFUSE_TFILE_HPP

#include "TDirectory.hpp"

namespace cppfuse {

class TFile : public TSpecializedObjectMixin<S_IFREG, TDirectory> {
    public:
    TFile(const std::string& name, mode_t mode);
};

}




#endif //CPPFUSE_TFILE_HPP
