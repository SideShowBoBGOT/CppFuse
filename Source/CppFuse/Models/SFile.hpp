#ifndef CPPFUSE_SFILE_HPP
#define CPPFUSE_SFILE_HPP

#include <CppFuse/Models/SInfoMixin.hpp>
#include <vector>

namespace cppfuse {

struct SFile : SInfoMixin<SFile> {
    friend struct SInfoMixin<SFile>;
    std::vector<char> Data;

    protected:
    static void DoNew(const rwl::TRwLockWriteGuard<SFile>& var);
};


}

#endif //CPPFUSE_SFILE_HPP
