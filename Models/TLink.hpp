#ifndef CPPFUSE_TLINK_HPP
#define CPPFUSE_TLINK_HPP

#include "TDirectory.hpp"

namespace cppfuse {

class TLink : public TSpecializedObjectMixin<S_IFLNK, TDirectory> {
    public:
    TLink(const std::string& name, mode_t mode);
};

}

#endif //CPPFUSE_TLINK_HPP
