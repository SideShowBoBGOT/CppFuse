#ifndef CPPFUSE_TDELETEFILE_HPP
#define CPPFUSE_TDELETEFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

class TDeleteFile {
    public:
    void operator()(const fs::path& path);

    protected:
    void DeleteDir(const ASharedRwLock<TDirectory>& dir);
};

}

#endif //CPPFUSE_TDELETEFILE_HPP
