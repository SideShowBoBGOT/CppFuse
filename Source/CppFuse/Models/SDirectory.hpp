#ifndef CPPFUSE_SDIRECTORY_HPP
#define CPPFUSE_SDIRECTORY_HPP

#include <CppFuse/Models/SInfoMixin.hpp>
#include <vector>

namespace cppfuse {

struct SDirectory : SInfoMixin<SDirectory> {
    friend struct SInfoMixin<SDirectory>;
    std::vector<ASharedFileVariant> Objects;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SDirectory>& var);
};

}

#endif //CPPFUSE_SDIRECTORY_HPP
