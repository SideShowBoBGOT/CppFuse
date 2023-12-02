#ifndef CPPFUSE_NNFILEACCESS_HPP
#define CPPFUSE_NNFILEACCESS_HPP

namespace cppfuse {

namespace NNFileAccess {
    enum NFileAccess {
        Ok = 0,
        Restricted = -1
    };
}

using NFileAccess = NNFileAccess::NFileAccess;

}

#endif //CPPFUSE_NNFILEACCESS_HPP
