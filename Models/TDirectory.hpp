#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TSpecializedObjectMixin.hpp"
#include <sys/stat.h>

namespace cppfuse {

class TDirectory : public TSpecializedObjectMixin<S_IFDIR, TDirectory> {
    public:
    TDirectory(const std::string& name, mode_t mode);


};

}

#endif //CPPFUSE_TDIRECTORY_HPP
