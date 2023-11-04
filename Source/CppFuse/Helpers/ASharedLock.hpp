#ifndef CPPFUSE_ASHAREDLOCK_HPP
#define CPPFUSE_ASHAREDLOCK_HPP

#include <RwLock/TRwLock.hpp>

namespace cppfuse {

template<typename T>
using ASharedRwLock = std::shared_ptr<rwl::TRwLock<T>>;

template<typename T>
using AWeakRwLock = std::weak_ptr<rwl::TRwLock<T>>;

template<typename T, typename... Args>
inline ASharedRwLock<T> MakeSharedRwLock(Args... args) {
    return std::make_shared<rwl::TRwLock<T>>(args...);
}

}

#endif //CPPFUSE_ASHAREDLOCK_HPP
