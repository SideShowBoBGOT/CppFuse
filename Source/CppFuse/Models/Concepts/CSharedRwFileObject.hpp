#ifndef CPPFUSE_CRWFILEOBJECT_HPP
#define CPPFUSE_CRWFILEOBJECT_HPP

#include <CppFuse/Helpers/ASharedLock.hpp>
#include <type_traits>

namespace cppfuse {

struct SDirectory;
struct SFile;
struct SLink;

template<typename T>
concept CSharedRwFileObject = std::is_same_v<T, ASharedRwLock<SDirectory>>
    || std::is_same_v<T, ASharedRwLock<SFile>> || std::is_same_v<T, ASharedRwLock<SLink>>;

}

#endif //CPPFUSE_CRWFILEOBJECT_HPP
