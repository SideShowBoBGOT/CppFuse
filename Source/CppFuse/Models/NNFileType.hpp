#ifndef CPPFUSE_NNFILETYPE_HPP
#define CPPFUSE_NNFILETYPE_HPP

#include <sys/stat.h>

namespace cppfuse {

namespace NNFileType {
    enum NFileType {
        Directory = S_IFDIR,
        File = S_IFREG,
        Link = S_IFLNK
    };
}

using NFileType = NNFileType::NFileType;

}

#endif //CPPFUSE_NNFILETYPE_HPP
