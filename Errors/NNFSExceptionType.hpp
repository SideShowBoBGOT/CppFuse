#ifndef CPPFUSE_NNFSEXCEPTIONTYPE_HPP
#define CPPFUSE_NNFSEXCEPTIONTYPE_HPP

namespace cppfuse {

namespace NNFSExceptionType {
    enum NFSExceptionType {
        FileNotExist,
        NotDirectory
    };
}

using NFSExceptionType = NNFSExceptionType::NFSExceptionType;

}

#endif //CPPFUSE_NNFSEXCEPTIONTYPE_HPP
