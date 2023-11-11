#ifndef CPPFUSE_TDELETEFILE_HPP
#define CPPFUSE_TDELETEFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

class TDeleteFile {
    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const ASharedRwLock<TDirectory>& var);
    void operator()(const ASharedRwLock<TRegularFile>& var);
    void operator()(const ASharedRwLock<TLink>& var);

    protected:

};

}

#endif //CPPFUSE_TDELETEFILE_HPP
