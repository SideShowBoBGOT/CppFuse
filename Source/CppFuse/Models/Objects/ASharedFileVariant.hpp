#ifndef CPPFUSE_ASHAREDFILEVARIANT_HPP
#define CPPFUSE_ASHAREDFILEVARIANT_HPP

#include <CppFuse/Helpers/ASharedLock.hpp>
#include <variant>

namespace cppfuse {

struct SDirectory;
struct SFile;
struct SLink;

using ASharedFileVariant = std::variant<
    ASharedRwLock<SDirectory>,
    ASharedRwLock<SFile>,
    ASharedRwLock<SLink>
>;

}

#endif //CPPFUSE_ASHAREDFILEVARIANT_HPP
