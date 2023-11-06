#ifndef CPPFUSE_CRWGUARDFILEOBJECT_HPP
#define CPPFUSE_CRWGUARDFILEOBJECT_HPP

#include <RwLock/TRwLockReadGuard.hpp>
#include <RwLock/TRwLockWriteGuard.hpp>
#include <type_traits>

namespace cppfuse {

struct SDirectory;
struct SFile;
struct SLink;

template<typename T>
concept CReadGuardFileObject = std::is_same_v<T, rwl::TRwLockReadGuard<SDirectory>>
    || std::is_same_v<T, rwl::TRwLockReadGuard<SFile>>
    || std::is_same_v<T, rwl::TRwLockReadGuard<SLink>>;

template<typename T>
concept CWriteGuardFileObject = std::is_same_v<T, rwl::TRwLockWriteGuard<SDirectory>>
    || std::is_same_v<T, rwl::TRwLockWriteGuard<SFile>>
    || std::is_same_v<T, rwl::TRwLockWriteGuard<SLink>>;

}

#endif //CPPFUSE_CRWGUARDFILEOBJECT_HPP
