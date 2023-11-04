#ifndef CPPFUSE_SLINK_HPP
#define CPPFUSE_SLINK_HPP

#include <CppFuse/Models/SInfoMixin.hpp>
#include <filesystem>

namespace cppfuse {

struct SLink : SInfoMixin<SLink> {
    friend struct SInfoMixin<SLink>;
    std::filesystem::path LinkTo;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path);
};

}

#endif //CPPFUSE_SLINK_HPP
