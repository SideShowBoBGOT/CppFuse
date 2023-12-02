#ifndef CPPFUSE_NSHELPERFUNCS_HPP
#define CPPFUSE_NSHELPERFUNCS_HPP

#include <concepts>

namespace cppfuse::NSHelperFuncs {

    template<std::integral T>
    constexpr bool IsHasFlag(T value, T flag) {
        return (value & flag) == flag;
    }

}



#endif //CPPFUSE_NSHELPERFUNCS_HPP
