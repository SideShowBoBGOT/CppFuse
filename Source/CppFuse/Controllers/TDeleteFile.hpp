#ifndef CPPFUSE_TDELETEFILE_HPP
#define CPPFUSE_TDELETEFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

class TDeleteFile {
    public:
    void operator()(const char* path);

    protected:
    void Delete(const ASharedRwLock<TDirectory>& var);
    void Delete(const ASharedRwLock<TRegularFile>& var);
    void Delete(const ASharedRwLock<TLink>& var);

    protected:

};

}

#endif //CPPFUSE_TDELETEFILE_HPP
