#ifndef CPPFUSE_NNFSEXCEPTIONTYPE_HPP
#define CPPFUSE_NNFSEXCEPTIONTYPE_HPP

#include <cerrno>

namespace cppfuse {

namespace NNFSExceptionType {
    enum NFSExceptionType {
        FileNotExist = -ENOENT,
        NotDirectory = -ENOTDIR,
        NotLink = -ENOLINK,
        NotFile = -ENOENT
    };
}

using NFSExceptionType = NNFSExceptionType::NFSExceptionType;

}

#endif //CPPFUSE_NNFSEXCEPTIONTYPE_HPP
