#ifndef CPPFUSE_NSFILEATTRIBUTES_HPP
#define CPPFUSE_NSFILEATTRIBUTES_HPP

#include <CppFuse/Models/TFileObjects.hpp>
#include <sys/stat.h>

namespace cppfuse::NSFileAttributes {
    void Get(const ASharedFileVariant& var, struct stat* st);
}

#endif //CPPFUSE_NSFILEATTRIBUTES_HPP
