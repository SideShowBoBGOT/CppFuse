#ifndef CPPFUSE_ASHAREDFILEVARIANT_HPP
#define CPPFUSE_ASHAREDFILEVARIANT_HPP

#include <CppFuse/Helpers/ASharedLock.hpp>
#include <variant>

namespace cppfuse {

class TDirectory;
class TFile;
class TLink;

using ASharedFileVariant = std::variant<
    ASharedRwLock<TDirectory>,
    ASharedRwLock<TFile>,
    ASharedRwLock<TLink>
>;

}

#endif //CPPFUSE_ASHAREDFILEVARIANT_HPP
