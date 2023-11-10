#ifndef CPPFUSE_TFINDER_HPP
#define CPPFUSE_TFINDER_HPP

#include <CppFuse/Errors/TFSException.hpp>
#include "CppFuse/Models/Objects/TFileObjects.hpp"

namespace cppfuse {

class TFinder {
    public:
    static ASharedFileVariant Find(const AStdPath& path);
    static ASharedRwLock<TDirectory> FindDir(const AStdPath& path);
    static ASharedRwLock<TLink> FindLink(const AStdPath& path);
    static ASharedRwLock<TFile> FindFile(const AStdPath& path);

    protected:
    template<typename T, auto FSExceptionValue>
    static ASharedRwLock<T> FindGeneral(const AStdPath& path);

    protected:
    static ASharedFileVariant RecursiveFindStepOne(const AStdPath& path, AStdPathIt it, const ASharedRwLock<TDirectory>& dir);

    static ASharedFileVariant RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedRwLock<TDirectory>& obj);

    static ASharedFileVariant RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedFileVariant & obj);

};

template<typename T, auto FSExceptionValue>
ASharedRwLock<T> TFinder::FindGeneral(const AStdPath& path) {
    const auto obj = Find(path);
    if(const auto t = std::get_if<ASharedRwLock<T>>(&obj)) {
        return *t;
    }
    throw TFSException(path.begin(), path.end(), FSExceptionValue);
}

}

#endif //CPPFUSE_TFINDER_HPP
