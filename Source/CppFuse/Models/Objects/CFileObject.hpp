#ifndef CPPFUSE_CFILEOBJECT_HPP
#define CPPFUSE_CFILEOBJECT_HPP

#include <type_traits>

namespace cppfuse {

struct SDirectory;
struct SFile;
struct SLink;

template<typename T>
concept CFileObject = std::is_same_v<T, SDirectory> || std::is_same_v<T, SFile> || std::is_same_v<T, SLink>;

}

#endif //CPPFUSE_CFILEOBJECT_HPP
